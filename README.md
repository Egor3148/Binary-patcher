# Binary files patcher

## Author
 - George Kobrusev, gr. 12b, course 3, FAMCS 2025

## Overview
 - A simple tool for patching binary executables
 - Basic signature applying is also provided
 - For now it's oriented on working with Windows
 
## Usage
 - The apps can be distributed via single executable file with no additional libraries each. You can find the executables in <br> the corresponding folder in <code>out</code>
 - The project contains two apps: ***Text printer*** prints out the place where the patch should be, ***Exe patcher*** patches the target file and signs the result via signtool

## Building
 - This project uses <code>CMake</code> for building. See <code>CMakeLists.txt</code> for build specifications.
 - Change <code>USE_FLTK</code> option to build a CLI or GUI version
 - **WARNING!** After changing this option make sure that CMake cache gets cleaned. Removing <code>out/build</code> folder is the simplest way to do that

## Additional notes
 - This project contains dependencies written by other deverlopers:
    * [FLTK v1.5.0](https://github.com/fltk/fltk) for GUI
 - Current solution uses **signtool** for signing files. Its absense isn't supposed to break the app, but the patched file won't be signed at all.
    * To make signtool work properly in this app, you'll need to specify path to it in the **PATH** variable.
