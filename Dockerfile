FROM ubuntu:24.04
MAINTAINER Yegor Bugayenko <yegor256@gmail.com>
LABEL Alexander Ocheretin <mobidev@yandex.ru>
WORKDIR /tmp

RUN apt update -y
RUN apt install -y build-essential
RUN apt install -y cmake ninja-build

COPY . /tmp
RUN cd /tmp
RUN cmake . && make

ENTRYPOINT ["/tmp/carts"]
