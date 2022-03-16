# OpenGL Demo
A demonstration of opengl

## Used libraries
* OpenGL
* GLFW
* GLEW
* STB_IMAGE (as only headerfile "libs/stb_image.h" into in this project) - http://nothings.org/stb
* GLM
* OpenAL
* LibSndFile

## Build
```bash
git clone https://github.com/ThKattanek/opengl_demo.git
cd opengl_demo
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

```
Optional can use -DCMAKE_INSTALL_PREFIX=[InstallPfad]

## Uninstall
```bash
xargs rm < install_manifest.txt
```
Warning! Directories created by the installation are not removed, but only all files created.

## Compiling for Windows x32 with MXE (Crossdev)


### Set Envoriment Varibale Path to MXE
```bash
#### export PATH=~/mxe/usr/bin:$PATH
```

```bash
cd ~
git clone https://github.com/ThKattanek/opengl_demo.git
cd opengl_demo
mkdir build-win-x32
cd build-win-x32
[MXE-PATH]/usr/bin/i686-w64-mingw32.static-cmake .. -DWIN32_STATIC_BUILD=TRUE -DCMAKE_INSTALL_PREFIX=../install-win-x32
make
make install
```
## Compiling for Windows x64 with MXE (Crossdev)
```bash
cd ~
git clone https://github.com/ThKattanek/opengl_demo.git
cd opengl_demo
mkdir build-win-x64
cd build-win-x64
[MXE-PATH]/usr/bin/x86_64-w64-mingw32.static-cmake .. -DWIN32_STATIC_BUILD=TRUE -DCMAKE_INSTALL_PREFIX=../install-win-x64
make
make install
```
