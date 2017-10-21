# BrainHarmonics
# This file forms the basis of build requirements to get the software to compile.

For cross-platform compatibility

```
ln -s /home /Users
```

For Mac Users:
Ensure the xcode command line tools are installed using:  xcode-select --install
The preference for compilation tools is to use MacPorts. Download from MacPorts.org
After installing macports run:

```
sudo port selfupdate
sudo port upgrade outdated
sudo port install gcc5
```
Agree to all dependency install requirements
```
sudo port install git cmake
```
Agree to all dependency install requirements



Base folder is ~/Developer
Folders created
~/Developer/CMakeFiles
~/Developer/BrainHarmonics

Install CMake

```
sudo apt-get update
sudo apt-get upgrade

sudo apt-get install build-essential git gcc-5 cmake pkg-config libgl1-mesa-dev libxt-dev libpcap-dev libmxml-dev libuv1-dev libusb-1.0-0-dev liballegro5-dev liballegro-ttf5-dev libjpeg-dev libjpeg8-dev libtiff-dev libtiff5-dev libjasper-dev libpng-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk-3-dev libatlas-base-dev gfortran python-dev python-numpy python2.7-dev python3.5-dev libgtk2.0-dev libtbb2 libtbb-dev libdc1394-22-dev

```

Install the QT/VTK toolkit

```
cd ~/Developer
git clone git://vtk.org/VTK.git

mkdir ~/Developer/VTK-build
mkdir ~/Developer/VTK-Release-build
mkdir ~/Developer/QT
cd ~/Developer/VTK-build
cmake ~/Developer/VTK

```
(Ubuntu element)
```
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

(MacOS element)
```
wget http://download.qt.io/official_releases/qt/5.9/5.9.2/qt-opensource-mac-x64-5.9.2.dmg

```
Run the dmg to open the QT installer (skip account creation) and then install VTK (the make process is a Very long process)
```
cd ~/Developer/VTK-build
sudo make install

```

Install OpenCV specifics
```
cd ~/Developer
git clone https://github.com/opencv/opencv.git
cd ~/Developer/opencv
mkdir release
cd release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_CXX_FLAGS=-std=c++11 ..
make
sudo make install
```

Install libcaer and its dependencies

```
cd ~/Developer
git clone https://github.com/inilabs/libcaer.git
cd libcaer
cmake -DENABLE_OPENCV=1 -DCMAKE_INSTALL_PREFIX=/usr .
make
sudo make install
```


      
How to build...

