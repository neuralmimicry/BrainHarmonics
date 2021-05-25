# BrainHarmonics
\#\# This file forms the basis of build requirements to get the software to compile.
\#\#\# Original code created by the NeuralMimicry Project, Paul Isaac's.
\#\#\# 
\#\# (c) Paul Isaac's 2021.
\#\# May be freely copied whilst maintaining reference to origin and copyright.
\#\#\#\# Based on an original idea: https://www.researchgate.net/publication/325069661_An_Outline_of_Artificial_Intelligence_and_Neuromorphic_technology_to_introduce_Auto-Asynchronous_Recursive_Neural_Networks_AARNN

\#\#\# NOTE: This is pre-alpha raw software in active development. At least 50% of which
\#\#\# is still needed to be written down. It will break/is broken but you are welcome to
\#\#\# join in the journey of development. The goal IS aspirational!

BrainHarmonics is the first code designed to implement Autonomic Asynchronous
Recursive Neuromorphic Network. It is an infrastructure designed to enable
the creation of emergent properties.

Stimuli are represented as spatio-temporal activations that cause interaction with
emulated oscillations existing in loops of simulated neurons. When different groups of neurons
are oscillating at different frequencies there will still be moments when points
on the waveforms are in phase. This combined simulated energy combination causes
onward stimuli to occur.

The software aims to make use of available scalability options such as Open MP for
multi-threading on the same node; Open MPI for inter-node communication; Heterogeneous
accelerators where available and appropriate.

Ensure you are using CMAKE v3.12 or greater.
When libraries for the respective distro are not found, they should be compiled from source.

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
sudo port install atlas cmake doxygen gcc5 graphviz gtk2 gtk3 libdc1394 libpcap libpng libusb libuv mesa opencv pkgconfig python27 py27-numpy python36 py36-numpy tbb xorg-libXt x264 XviD
```
For Ubuntu Users
```
sudo apt-get update
sudo apt-get upgrade

(for Ubuntu 14.x)
sudo apt-get install build-essential git gcc-5 cmake pkg-config libgl1-mesa-dev libxt-dev libpcap-dev libmxml-dev libuv1-dev libusb-1.0-0-dev liballegro5-dev liballegro-ttf5-dev libjpeg-dev libjpeg8-dev libtiff-dev libtiff5-dev libjasper-dev libpng-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk-3-dev libatlas-base-dev gfortran python-dev python-numpy python2.7-dev python3.5-dev libgtk2.0-dev libtbb2 libtbb-dev libdc1394-22-dev

(for Ubuntu 18.x)
sudo apt-get install build-essential git gcc cmake pkg-config libglfw3-dev libgl1-mesa-dev libxt-dev libpcap-dev libmxml-dev libuv1-dev libusb-1.0-0-dev liballegro5-dev liballegro-ttf5-dev libjpeg-dev libjpeg8-dev libtiff-dev libtiff5-dev libjasper-dev libpng-dev libpng12-dev libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libgtk-3-dev libatlas-base-dev gfortran python-dev python-numpy python2.7-dev python3.5-dev libgtk2.0-dev libtbb2 libtbb-dev libdc1394-22-dev

```
For Red Hat Users
```
(for RHEL 8.x)
sudo dnf update

sudo dnf group install "System Tools" "Development Tools"

There are Many libraries that can be interdependent for successful operation. Please refer to RHEL8.2-aarch64.txt for an indication of libraries that will be installed from a base OS.

sudo dnf install glfw-devel opencv-devel libpcap-devel git autoconf automake meson ninja-build parallel rubygem-sass sassc optipng libffi-devel gcc redhat-rpm-config inkscape gtk3-devel gdk-pixbuf2-xlib glib2-devel glib2 libxml2-devel librsvg2-devel gnome-themes-standard gtk-murrine-engine gtk2-engines google-roboto-fonts google-noto-sans-fonts google-noto-sans-mono-fonts
```

Agree to all dependency install requirements

Base folder is ~/Developer

git clone git@github.com:Linaro/BrainHarmonics.git

Folders created
~/Developer/BrainHarmonics

Install the VTK toolkit

```
cd ~/Developer
git clone https://gitlab.kitware.com/vtk/vtk.git

mkdir ~/Developer/VTK-build
mkdir ~/Developer/VTK-Release-build
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
```
(Common)
```

make -j2
sudo make install
```

Install OpenCV specifics (Linux only)
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

(MacOS element)
```
wget http://download.qt.io/official_releases/qt/5.9/5.9.2/qt-opensource-mac-x64-5.9.2.dmg

```
Run the dmg to open the QT installer (skip account creation) and then install VTK (the make process is a Very long process)
```
cd ~/Developer/VTK-build
sudo make install

```

Install libcaer and its dependencies (Linux & MacOS)

```
cd ~/Developer
git clone https://github.com/inilabs/libcaer.git
cd libcaer
cmake -DENABLE_OPENCV=1 -DCMAKE_INSTALL_PREFIX=/usr .
make
sudo make install
```

Build procedure.

```
mkdir ~/Developer/BrainHarmonics/build
cd ~/Developer/BrainHarmonics/build
cmake ../
make all

```

How to run...

Once built, execute ./build/BrainHarmonics from the ~/Developer/BrainHarmonics folder.

Overview:
Creates a number of simulation universes from which to create neurons/synapses.

Skeletal framework exists to call Python routines if required.
Currently minimal parameterisation files but elements are there.



Running inside a VM
===================

BrainHarmonics execution relies on a graphical interface and it uses OpenGL. Although it
is possible to implement support entirely in software, it has been designed to be mostly or
entirely in hardware. There exist several options when working with BrainHarmonics inside a VM:

 1) assign a graphics card device to the VM.
 2) use X forwarding with ssh.
 3) use virtio VGA drivers.

From a performance point of view 1) is the best option. Note this can require to assign a full
device or just partially through SRIOV (VFs or mediated devices). If there is not support for
SRIOV, assigning the device to the VM implies the Host not being able to use it which can be
problematic in most desktop systems.

X forwarding has a main problem: apps using DRI calls after. This option allows an X server in
the Host doing the rendering, but that is helpless if X clients go straight to the device through
DRI before redirecting to the X server.

Virtio-gpu is likely the best/easiest option as it is a mature technology now thanks to the
Virgil3d project.

Using this option requires a QEMU executable supporting SDL and OpenGL, options "--enable-sdl" and
"--enable-opengl" when configuring sources before compilation. With that support, qemu needs to be
launched with "-device virtio-gpu-pci -display sdl,gl=on". A graphical interface is created and it
will be used for showing BH window.

Running a graphical app is not usually supported by default if you are using an image offered by
distributions to be used on VMs. If that is the case the X11 server package needs to be installed.
But you do not need a full graphical interface but just to run the X server for BH:

startx "${HOME}/Developer/BrainHarmonics/build/BrainHarmonics"

This requires to give permissions for using the graphical console to the user running that command.
Adding next line to /etc/X11/Xwrapper.config will solve the problem:

allowed_users = anybody
