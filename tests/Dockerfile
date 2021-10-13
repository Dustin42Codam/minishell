FROM ubuntu:14.04

# sudo docker build -t minishell .
# sudo docker run -it --rm minishell 

RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN apt-get install -y valgrind
# RUN apt-get install -y ltrace
RUN apt-get install -y libc6-dev-i386
# RUN apt-get install -y libssl-dev
# RUN apt-get install -y nasm
RUN apt-get install -y libreadline-dev
RUN apt-get install -y vim
RUN apt-get install -y git
RUN apt-get install -y clang
RUN apt-get install -y bash
RUN apt-get install -y libncurses5-dev libncursesw5-dev

RUN git clone https://github.com/Dustin42Codam/minishell.git

# RUN make -C minishell

WORKDIR /minishell

ENTRYPOINT ["/bin/bash"]
