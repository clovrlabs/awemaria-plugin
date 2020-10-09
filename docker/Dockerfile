FROM debian:stable-slim as build

RUN apt update && apt install -y build-essential \
  && apt install -y cmake \
  && apt install -y git \
  && apt install -y libncurses5-dev libssl-dev bison \
  && apt install -y chrpath cmake cmake-data comerr-dev debhelper \
  dh-apparmor dh-autoreconf dh-exec dh-strip-nondeterminism dwz gdb \
  icu-devtools intltool-debian krb5-multidev libaio-dev libarchive-dev \
  libarchive-zip-perl libbabeltrace1 libboost-dev libboost1.67-dev \
  libcrack2-dev dh-perl6 \
  libfile-stripnondeterminism-perl libgnutls-openssl27 libgnutls28-dev \
  libgnutlsxx28 libgssrpc4 libicu-dev libidn2-dev libipt2 libjemalloc-dev \
  libjemalloc2 libjudy-dev libkadm5clnt-mit11 libkadm5srv-mit11 libkdb5-9 \
  libkrb5-dev libp11-kit-dev libpam0g-dev libpcre16-3 libpcre3-dev libpcre32-3 \
  libpcrecpp0v5 libreadline-gplv2-dev librhash0 libsnappy-dev libsource-highlight-common libsource-highlight4v5 libsub-override-perl libsystemd-dev libtasn1-6-dev libxml2-dev libzstd-dev nettle-dev po-debconf unixodbc-dev

RUN mkdir -p /builds/clovrlabs/awemaria

COPY . /builds/clovrlabs/awemaria/

RUN gcc -v \
  && mkdir -p /builds/clovrlabs/awemaria/build

RUN cd /builds/clovrlabs/awemaria/build \
  && cmake .. -DCMAKE_BUILD_TYPE=Release \
  && make remote_key_management

FROM mariadb:10.5

COPY conf/my.cnf /etc/mysql/my.cnf
COPY --from=build /builds/clovrlabs/awemaria/build/plugin/remote_key_management/remote_key_management.so /usr/lib/mysql/plugin/

