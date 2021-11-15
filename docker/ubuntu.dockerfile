#
# Ubuntu Dockerfile
#
# https://github.com/dockerfile/ubuntu
#
FROM ubuntu:latest

ARG SSH_KEY
ARG SSH_KEY_PASSPHRASE

# avoid prompting for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get -qq --no-install-recommends -y upgrade
RUN apt-get install -y build-essential
RUN apt-get install -y g++
RUN apt-get install -y git
RUN apt-get install -y libegl1
RUN apt-get install -y libfishsound1-dev
RUN apt-get install -y libflac-dev
RUN apt-get install -y libfluidsynth-dev
RUN apt-get install -y libfreetype6-dev
RUN apt-get install -y libgl1
RUN apt-get install -y libglvnd0
RUN apt-get install -y libglx0
RUN apt-get install -y libmikmod-dev
RUN apt-get install -y liboggz2-dev
RUN apt-get install -y libsdl2-2.0-0
RUN apt-get install -y libsdl2-dev
RUN apt-get install -y libsdl2-mixer-2.0-0
RUN apt-get install -y libsdl2-mixer-dev
RUN apt-get install -y libsdl2-ttf-2.0-0
RUN apt-get install -y libsdl2-ttf-dev
RUN apt-get install -y libsmpeg-dev
RUN apt-get install -y libx11-6
RUN apt-get install -y libxext6
RUN apt-get install -y python3
RUN apt-get install -y python3-dev
RUN apt-get install -y ssh
RUN apt-get install -y vim
RUN apt-get install -y xutils-dev

ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute
RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p $HOME/.ssh/                                                      && \
    echo "$SSH_KEY" > $HOME/.ssh/id_rsa                                       && \
    echo "IdentityFile ~/.ssh/id_rsa" >> /etc/ssh/ssh_config                  && \
    echo "Host github.com\n\tStrictHostKeyChecking no\n" >> $HOME/.ssh/config && \
    chmod -R 600 $HOME/.ssh/                                                  && \
    ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts                       && \
    eval `ssh-agent -s`                                                       && \
    printf "${SSH_KEY_PASSPHRASE}\n" | ssh-add $HOME/.ssh/id_rsa              && \
    git clone git@github.com:goblinhack/zorbash.git                           && \
    rm -rf $HOME/.ssh/

RUN cd zorbash && sh ./RUNME && ./zorbash-game
RUN bash
