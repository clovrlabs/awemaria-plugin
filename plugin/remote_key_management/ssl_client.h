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

#ifndef MYSQL_SSLCLIENT_H
#define MYSQL_SSLCLIENT_H

#include <my_crypt.h>
#include <unordered_map>
#include <string>
#include <openssl/ssl.h>
#include <memory>

 struct keyentry {
  unsigned int id;
  unsigned char key[MY_AES_MAX_KEY_LENGTH];
  unsigned int length;
};

class SSLClient
{
public:
  SSLClient(std::string hostname, unsigned int port, std::string key);
  auto GetKeys() -> std::unordered_map<unsigned int, keyentry>;

private:
  std::string hostname;
  unsigned int port;
  std::string filekey;
  std::unique_ptr<SSL_CTX, decltype(&SSL_CTX_free)> ctx;

private:
  SSL_CTX *InitCtx();
  std::string ReadSecretFromFile(const std::string &fk);
};

#endif // MYSQL_SSLCLIENT_H
