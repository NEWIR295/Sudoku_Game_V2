# pull our base image : osrf/ros:humble-desktop-full for ROS2 humble GUI usage 
#                                               -> my storage is full so i didn't use another image :)
# FROM osrf/ros:humble-desktop-full 


FROM ubuntu:22.04 

# use bash as default shell
SHELL ["/bin/bash", "-c"]

# download and install dependencies
RUN apt-get update && apt-get install -y \
    wget \
    build-essential \
    libgl1-mesa-dev \
    cmake \
    ninja-build \
    qt6-base-dev \
    qt6-base-dev-tools\
    qt6-declarative-dev \
    qt6-multimedia-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    libqt6core6 libqt6gui6 libqt6widgets6 \
    nlohmann-json3-dev \
    python3-pip \
    nano \
    xz-utils \ 
    libgl1 \
    libxkbcommon-x11-0 \
    libxcb-cursor0 \
    libxcb-icccm4 \
    libxcb-image0 \
    libxcb-keysyms1 \
    libxcb-randr0 \
    libxcb-render-util0 \
    libxcb-shape0 \
    libxcb-xinerama0 \
    libxcb-xinput0 \
    libxcb-xfixes0 \
    libxcb-sync1 \
    libxcb-xkb1 \
    libxcb-util1 \
    libxcb-shm0 \
    libxcb-render0 \
    libxcb1 \
    libxrender1 \
    libxi6 \
    libxrandr2 \
    libegl1 \  
    && rm -rf /var/lib/apt/lists/*

RUN apt install -y wget xz-utils libgl1

# RUN wget https://download.qt.io/official_releases/qt/6.9/6.9.2/qt-unified-linux-x64-6.9.2-online.run   
# RUN chmod +x qt-unified-linux-x64-6.9.2-online.run
# RUN ./qt-unified-linux-x64-6.9.2-online.run  --silent

RUN wget https://download.qt.io/official_releases/qt/6.9/6.9.2/single/qt-everywhere-src-6.9.2.tar.xz
RUN tar -xf qt-everywhere-src-6.9.2.tar.xz && \
    cd qt-everywhere-src-6.9.2 && \
    ./configure && \
    cmake --build . --parallel && \
    cmake --install .



# # create a workspace
WORKDIR /sudoku_ws

# # copy temp_server, temp_interface and packages into workspace
COPY GAME_GUI/ ./GAME_GUI/

# # #build the workspace and source the setup file
# RUN cd GAME_GUI && \
#     rm -rf build/Desktop_Qt_6_9_1-Debug && \
#     cmake -S . -B build/Desktop_Qt_6_9_1-Debug && \
#     cmake --build build/Desktop_Qt_6_9_1-Debug --target all


# CMD ["/bin/bash", "-c", "PATH=/usr/local/Qt-6.5.1/bin:$PATH && export PATH && ./GAME_GUI/game/Sudoku"]

ENV PATH="/usr/local/Qt-6.9.2/bin:${PATH}"
ENV LD_LIBRARY_PATH="/usr/local/Qt-6.9.2/lib:${LD_LIBRARY_PATH}"
CMD ["./GAME_GUI/game/Sudoku"]