#JPP : JSON in C++

Write JSON like code in C++ and access it like a JSON document

[![Build Status](https://travis-ci.org/crezefire/jpp.svg?branch=master)](https://travis-ci.org/crezefire/jpp)
 
[![Build status](https://ci.appveyor.com/api/projects/status/pbtyp3c8hte6739i?svg=true)](https://ci.appveyor.com/project/crezefire/jpp)

##Table of Contents
- [Overview](#overview)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Planned Features](https://github.com/crezefire/jpp/projects/1)
- [Submitting Issues](#submitting-issues)

##Overview
More to come....

##Requirements
Common:
- [CMake](https://cmake.org/download/) >= 3.4
- bash (On Windows use MinGW installed via [Git for Windows](https://git-scm.com/downloads))

Windows:
- [Visual Studio 2015](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)

Linux:
- GCC or [Clang](http://llvm.org/releases/) (>= 5.4 or >= 3.8)
- [Visual Studio Code](https://code.visualstudio.com/download) (Optional, Requires GCC + GDB)
- [VSCode C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) (Optional, Required with VSCode)

##Getting Started
To build the project as is run:

```shell
./create.sh
```
This script detects which OS you are running and runs the default CMake project generate command. It supports the following flags:
- `-h|--help` to print help
- `-f|--folder=<folder>` name of the folder to store build files. **Default: build**
- `-G="Generator Name"` for custom generator. **Default: "Visual Studio 14 Win64" or "Unix Makefiles"**
- `-m|--make=<extra CMake params>` Eg: `-m='-DVAR_SETUP=1 -DVAR2_SETUP=0`

Linux only:
- `-b|--build=<build type>` CMake build type. **Default: Debug**
- `-c|--clang` Uses the Clang compiler instead of GCC. **Default: Don't use Clang**
- `-v|--vscode` Skip setting up VSCode configs. **Default: Setup VSCode configs**

Note: Using Clang will still show CMake as setting up GCC but it will definitely be using Clang

##Submitting Issues
If you have any feature requests, suggestions or bugs please submit them to the [Issues](https://github.com/crezefire/cxp/issues) page where they will be tracked and updated.

If requesting a feature remember to:
- Explain how the feature will help
- Any examples of this feature

If reporting a bug remember to:
- Clearly explain / outline the reporoduction steps
- Mention the reproduction rate
- Mention your working environment, OS, CMake version etc
- Screenshots if possible / required
