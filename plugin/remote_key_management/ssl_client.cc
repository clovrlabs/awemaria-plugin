/* Copyright (c) 2020 Clovr.
 *
 *   ____  __    __    ___  ___ ___   ____  ____   ____   ____
 *  /    ||  |__|  |  /  _]|   |   | /    ||    \ |    | /    |
 * |  o  ||  |  |  | /  [_ | _   _ ||  o  ||  D  ) |  | |  o  |
 * |     ||  |  |  ||    _]|  \_/  ||     ||    /  |  | |     |
 * |  _  ||  `  '  ||   [_ |   |   ||  _  ||    \  |  | |  _  |
 * |  |  | \      / |     ||   |   ||  |  ||  .  \ |  | |  |  |
 * |__|__|  \_/\_/  |_____||___|___||__|__||__|\_||____||__|__|
 *
 */

#include "ssl_client.h"

#include <stdexcept>
#include <utility>
#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>

#include <sys/socket.h>
#include <openssl/err.h>

#define FILE_PREFIX "FILE:"

struct file_desc
{
  file_desc(int fd) : _desc(fd) {}
  file_desc() : _desc(-1) {}
  file_desc(std::nullptr_t) : _desc(-1) {}

  operator int() {return _desc;}

  bool operator ==(const file_desc &other) const {return _desc == other._desc;}
  bool operator !=(const file_desc &other) const {return _desc != other._desc;}
  bool operator ==(std::nullptr_t) const {return _desc == -1;}
  bool operator !=(std::nullptr_t) const {return _desc != -1;}

  int _desc;
};

struct deleter
{
  typedef file_desc pointer;
  void operator()(int desc) { close(desc); }
};


int open_connection(const char *hostname, unsigned int port)
{
  int sd;
  struct hostent *host;
  struct sockaddr_in addr;
  struct timeval tv;
  tv.tv_sec=20;

  if ((host = gethostbyname(hostname)) == nullptr)
    throw std::runtime_error(strerror(errno));

  sd=socket(PF_INET, SOCK_STREAM, 0);

  std::memset(&addr, 0, sizeof(addr));
  addr.sin_family= AF_INET;
  addr.sin_port= htons(port);
  addr.sin_addr.s_addr= *(long *) (host->h_addr);
  if (connect(sd, (struct sockaddr *) &addr, sizeof(addr)) != 0)
  {
    close(sd);
    throw std::runtime_error(strerror(errno));
  }

  // set timeout in recv
  setsockopt(sd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv,
             sizeof(struct timeval));

  return sd;
}

void from_hex(const std::string &in, void *const data)
{
  size_t length=in.length();
  auto *byteData = reinterpret_cast<unsigned char*>(data);

  std::stringstream hexStringStream;
  hexStringStream >> std::hex;
  for(size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex)
  {
    // two characters at a time
    const char tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };

    // Reset and fill the string stream
    hexStringStream.clear();
    hexStringStream.str(tmpStr);

    // Do the conversion
    int tmpValue = 0;
    hexStringStream >> tmpValue;
    byteData[dataIndex] = static_cast<unsigned char>(tmpValue);
  }
}

SSL_CTX *SSLClient::InitCtx(void)
{
  OpenSSL_add_all_algorithms();
  SSL_load_error_strings();
  const SSL_METHOD *method= TLS_client_method();
  SSL_CTX * ret= SSL_CTX_new(method);
  if (ctx != nullptr)
    SSL_CTX_set_max_proto_version(ret, TLS1_2_VERSION);
  return ret;
}

SSLClient::SSLClient(std::string hst, unsigned int prt, std::string key)
    : hostname(std::move(hst)), port(prt), filekey(std::move(key)),
      ctx(InitCtx(), SSL_CTX_free)
{
  // read the secret from file, if the key was stored in a file
  if (filekey.find(FILE_PREFIX, 0) == 0)
  {
    filekey= ReadSecretFromFile(filekey.substr(strlen(FILE_PREFIX)));
  }
}

auto SSLClient::GetKeys() -> std::unordered_map<unsigned int, keyentry>
{
  unsigned int bytes=0;
  char buf[1024];
  std::unordered_map<unsigned int, keyentry> ret;

  // open the socket toward the server
  std::unique_ptr<file_desc, deleter> server(open_connection(hostname.c_str(), port));

  // init ssl
  auto ssl_init= [&server, this]() {
    SSL *ret = SSL_new(ctx.get());
    SSL_set_fd(ret, server.get());
    return ret;
  };
  std::unique_ptr<SSL, decltype(&SSL_free)> ssl(ssl_init(), SSL_free);

  // connect
  int r = SSL_connect(ssl.get());
  switch (SSL_get_error(ssl.get(), r))
  {
    case SSL_ERROR_NONE:
      break;

    case SSL_ERROR_SYSCALL:
      strcpy(buf, r == 0 ? "Server sent illegal EOF! Shamir server probably misconfigured" : strerror(errno));
      throw std::runtime_error(buf);

    default:
      ERR_error_string_n(ERR_get_error(), buf, sizeof(buf));
      throw std::runtime_error(buf);
  }

  // send command get key
  sprintf(buf, "GET KEY %s\n", filekey.c_str());
  r= SSL_write(ssl.get(), buf, strlen(buf));
  if (r < 0) {
    throw std::runtime_error("Error in sending the command GET KEY to the shamir server");
  }

  // read the key
  bytes=SSL_read(ssl.get(), buf, sizeof(buf));
  if (bytes > 0) {
    buf[bytes]=0;
  } else {
    throw std::runtime_error("Error in reading the key from the shamir server");
  }

  // check if the string we read from the server is actually an error message
  if (buf[0] == '-') {
    throw std::runtime_error(buf);
  }

  // all ok, the buffer contains the key so we convert it from string to bytes
  keyentry key = {100, {}, bytes/2};
  from_hex(buf, &key.key);

  // add the key to the map (only one key for the moment though)
  ret[key.id]=key;

  return ret;
}

std::string SSLClient::ReadSecretFromFile(const std::string &fk)
{
  std::ifstream t(fk.c_str());
  std::stringstream buffer;
  buffer << t.rdbuf();
  auto secret= buffer.str();
  secret.erase(std::remove(secret.begin(), secret.end(), '\n'), secret.end());
  return secret;
}
