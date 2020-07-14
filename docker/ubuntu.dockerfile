#
# Ubuntu Dockerfile
#
# https://github.com/dockerfile/ubuntu
#
FROM ubuntu:20.04

ARG SSH_KEY
# avoid prompting for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update
RUN apt-get -qq --no-install-recommends -y upgrade
RUN apt install -y build-essential
#RUN apt install -y vim
RUN apt install -y g++
RUN apt install -y libsdl2-dev libsdl2-2.0-0
#RUN apt install -y libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0
RUN apt install -y libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0
RUN apt install -y libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0
RUN apt install -y python3 python3-dev
RUN apt install -y git ssh xutils-dev

#
# This doesn't seem to work yet, so commented out
#
#ENV NVIDIA_VISIBLE_DEVICES all
#ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute
#RUN apt install -y libglvnd0 libgl1 libglx0 libegl1 libxext6 libx11-6

RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p /root/.ssh/ && \
    echo "$SSH_KEY" > /root/.ssh/id_rsa && \
    chmod -R 600 /root/.ssh/ && \
    ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts

RUN git clone git@github.com:goblinhack/zorbash.git
RUN /bin/rm -rf /root/.ssh/id_rsa
RUN cd zorbash && sh ./RUNME && ./zorbash
RUN bash
