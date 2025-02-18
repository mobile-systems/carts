FROM ubuntu:24.04
LABEL "org.opencontainers.vendor"="Yegor Bugayenko"
LABEL org.opencontainers.image.authors="yegor256@gmail.com"
LABEL "org.opencontainers.image.vendor"="Alexander Ocheretin <mobidev@yandex.ru>"
WORKDIR /tmp

RUN apt update -y && apt upgrade -y
RUN apt install -y build-essential
RUN apt install -y cmake ninja-build

COPY . /tmp
RUN cd /tmp
RUN cmake . && make

ENTRYPOINT ["/tmp/carts"]
