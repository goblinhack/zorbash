#
# Ubuntu Dockerfile
#
# https://github.com/dockerfile/ubuntu
#
FROM ubuntu:19.10

ARG SSH_KEY

# Env vars for the nvidia-container-runtime.
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute

RUN apt-get update
RUN apt-get -y upgrade
RUN apt install -y build-essential
RUN apt install -y vim
RUN apt install -y g++
RUN apt install -y libsdl2-dev libsdl2-2.0-0
RUN apt install -y libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0
RUN apt install -y libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0
RUN apt install -y libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0
RUN apt install -y python3 python3-dev python3-pip
RUN apt install -y git
RUN apt install -y ssh
RUN apt install -y xutils-dev

# opengl
RUN apt-get install -y -qq --no-install-recommends \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6

#RUN apt-get update && apt-get install -y --no-install-recommends \
#        mesa-utils \
#        ocl-icd-libopencl1 \
#        clinfo && \
#    rm -rf /var/lib/apt/lists/*
#RUN mkdir -p /etc/OpenCL/vendors && \
#    echo "libnvidia-opencl.so.1" > /etc/OpenCL/vendors/nvidia.icd

# opengl test - but so far I can't get this to work
#RUN apt-get install -y -qq glmark2 && glmark2

RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p /root/.ssh/ && \
    echo "$SSH_KEY" > /root/.ssh/id_rsa && \
    chmod -R 600 /root/.ssh/ && \
    ssh-keyscan -t rsa github.com >> ~/.ssh/known_hosts

RUN git clone git@github.com:goblinhack/zorbash.git
RUN /bin/rm -rf /root/.ssh/id_rsa
RUN cd zorbash && sh ./RUNME && ./zorbash
RUN bash
