# BrainHarmonics
# This file forms the basis of build requirements to get the software to compile.

For cross-platform compatibility

```
ln -s /home /Users
```

Base folder is ~/Developer
Folders created
~/Developer/CMakeFiles
~/Developer/BrainHarmonics

Install CMake

```
sudo apt-get update
sudo apt-get upgrade

sudo apt-get install build-essential libgl1-mesa-dev libxt-dev libpcap-dev gcc-5 cmake libmxml-dev libuv1-dev libusb-1.0-0-dev liballegro5-dev liballegro-ttf5-dev libjpeg8-dev libtiff5-dev libjasper-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk-3-dev libatlas-base-dev gfortran python2.7-dev python3.5-dev
```

Install OpenCV specifics
```
cd ~/Developer
git clone https://github.com/opencv/opencv.git
```

Install libcaer

```
cd ~/Developer
git clone https://github.com/inilabs/libcaer.git
cd libcaer
cmake -DENABLE_OPENCV=1 -DCMAKE_INSTALL_PREFIX=/usr .
make
sudo make install
```

Install the VTK toolkit

```
cd ~/Developer
git clone git://vtk.org/VTK.git

mkdir ~/Developer/VTK-build
mkdir ~/Developer/VTK-Release-build
mkdir ~/Developer/QT
cd ~/Developer/VTK-build
cmake ~/Developer/VTK

cd ~/Developer/VTK-Release-build
cmake -DCMAKE_BUILD_TYPE:STRING=Release ~/Developer/VTK

cd ~/Developer/QT
wget http://download.qt-project.org/official_releases/qt/5.9/5.9.2/qt-opensource-linux-x64-5.9.2.run
chmod +x qt-opensource-linux-x64-5.9.2.run
./qt-opensource-linux-x64-5.9.2.run

cd ~/Developer/VTK-Release-build
cmake -DVTK_QT_VERSION:STRING=5 \
      -DQT_QMAKE_EXECUTABLE:PATH=~/Qt5.9.2/5.9.2/gcc_64/bin/qmake \
      -DVTK_Group_Qt:BOOL=ON \
      -DCMAKE_PREFIX_PATH:PATH=~/Qt5.9.2/5.9.2/gcc_64/lib/cmake  \
      -DBUILD_SHARED_LIBS:BOOL=ON \
      ~/Developer/VTK

make -j2
sudo make install
```


      
How to build...

