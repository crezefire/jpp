#JPP : JSON in C++

Write (almost) JSON in C++, using any types and access it like a JSON document.

[![Build Status](https://travis-ci.org/crezefire/jpp.svg?branch=master)](https://travis-ci.org/crezefire/jpp) [![Build status](https://ci.appveyor.com/api/projects/status/3mjmih723iqtgpc5?svg=true)](https://ci.appveyor.com/project/crezefire/jpp)

##Table of Contents
- [Overview](#overview)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Planned Features](https://github.com/crezefire/jpp/projects/1)
- [Submitting Issues](#submitting-issues)

##Overview
 The following JSON:
 
 ```JSON
 {
    "string"    : "this is a string",
    "double"    : 3.14159265,
    "integer"   : 12345,
    "boolean"   : true,
    "null"      : null,
    "array-str" : ["var1", "var2", "var3"],
    "object"    : {
        "sub-object" : {
            "sub-sub-object" : 666
        },
        "sub-object-str" : "hello" 
    },
    "array-any" : [1, true, null, "valid", 2.222],
    "array-objects" : [
        {
            "obj1" : true
        },
        {
            "obj2" : null
        },
        {
            "obj3" : "hahaha"
        }
    ]
}
 ```
 
 Could be wrriten as such in C++ (Syntax subject to change):
 
 ```cpp
 {
    "string"_f    = "this is a string",
    "double"_f    = 3.14159265,
    "integer"_f   = 12345,
    "boolean"_f   = true,
    "null"_f      = nullptr,
    "array-str"_f = ["var1", "var2", "var3"],
    "object"_f    = {
        "sub-object"_f = {
            "sub-sub-object"_f = 666
        },
        "sub-object-str"_f = "hello" 
    },
    "array-any"_f = [1, true, nullptr, "valid", 2.222],
    "array-objects"_f = [
        {
            "obj1"_f = true
        },
        {
            "obj2"_f = null
        },
        {
            "obj3"_f = "hahaha"
        }
    ]
}
 ```

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
