FROM ubuntu:xenial

RUN apt-get update -y && apt-get dist-upgrade -y && apt-get install -y build-essential vim-nox llvm-3.6 wget curl git autoconf cmake zlib1g-dev libedit-dev libboost-program-options-dev \
    time unzip clang-3.6 graphviz \
    && ln -s /usr/bin/llvm-config-3.6 /usr/bin/llvm-config \
    && ln -s /usr/bin/clang-3.6 /usr/bin/clang \
    && echo 'export LD_LIBRARY_PATH="/usr/local/lib"' >> /root/.bashrc \
    && echo 'export PATH="$PATH:/usr/lib/llvm-3.6/bin"' >> /root/.bashrc
