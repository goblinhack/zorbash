#
# Fedora Dockerfile
#
FROM fedora:latest

ARG SSH_KEY
ARG SSH_KEY_PASSPHRASE

# avoid prompting for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN yum update -y
RUN dnf install -y findutils
RUN dnf install -y SDL2_mixer-devel SDL2_mixer
RUN dnf install -y SDL2_ttf-devel SDL2_ttf
RUN dnf install -y SDL2 SDL2-devel
RUN dnf install -y SDL2_image SDL2_image-devel
RUN dnf install -y python3
RUN dnf install -y python3-devel
RUN dnf install -y git
RUN dnf install -y make automake gcc-c++
RUN dnf install -y vim
RUN dnf install -y libmikmod-devel
RUN dnf install -y libfishsound-devel

# missing?
#RUN dnf install -y smpeg-devel
#RUN dnf install -y liboggz2-devel
#RUN dnf install -y libflac-devel
#RUN dnf install -y libfluidsynth-devel
#RUN dnf install -y libfreetype-devel
#RUN dnf install -y ssh
#RUN dnf install -y xutils-devel
#RUN dnf install -y libglvnd0
#RUN dnf install -y libgl1
#RUN dnf install -y libglx0
#RUN dnf install -y libegl1
#RUN dnf install -y libxext6
#RUN dnf install -y libx11-6

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

RUN cd zorbash && sh ./RUNME && ./zorbash
RUN bash
