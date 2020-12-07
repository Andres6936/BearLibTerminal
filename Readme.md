![SeeWiki](/Documentation/Screenshots/SeeWiki.png)
###### Please, See Wiki

BearLibTerminal provides a pseudoterminal window with a grid of character cells and a simple yet powerful API for flexible textual output and uncomplicated input processing.

### Features

* Unicode support: you can use UTF-8 or UTF-16/32 wide strings easily.
* Support for bitmap and vector (TrueType) fonts and tilesets.
* Extended output facilities: tile composition, alignment, offsets.
* High performance (uses OpenGL).
* Keyboard and mouse support.
* Bindings for several programming languages: С/С++, C#, Go, Lua, Pascal, Python, Ruby.
* Windows, Linux and OS X support.


### Documentation

* [Reference](http://foo.wyrd.name/en%3Abearlibterminal%3Areference) (functions, constants, behaviour)
* [Design overview](http://foo.wyrd.name/en%3Abearlibterminal%3Adesign)


### Using

Some notes about using it with various languages or compilers:


#### C/C++

With the arrival of CMake 14, a script was added that allows to get 
repositories from the Internet, taking into account this the user 
[TheLartians](https://github.com/TheLartians) decided to write a script 
for CMake that acts as a package manager. In my opinion, this marks a 
new step for C++ and CMake, allowing work with libraries that are 
downloaded and updated without direct intervention of the user.

To use this library, you need the script written by [TheLartians](https://github.com/TheLartians),
named [CPM.cmake](https://github.com/TheLartians/CPM.cmake) (acronym for CMake
Package Manager). Add it to your project, for example, under the directory
`CMakeModules` and then in your `CMakeFiles.txt` write the following:

```cmake
Include(CMakeModules/CPM.cmake)

CPMAddPackage(
  NAME BearLibTerminal
  VERSION 2020.12
  GITHUB_REPOSITORY Andres6936/BearLibTerminal
)
 
TARGET_LINK_LIBRARIES(<TARGET> PRIVATE BearLibTerminal::Framework)
```

- The directory `CMakeModules` should be created in case it does not exist.
- `<TARGET>` must be replaced by the executable to which you will link BearLibTerminal. 

#### Python

Python packages are available. You can install everything you need to use the library with

```sh
pip install bearlibterminal
```

Depending on the OS and Python installation, you might also want to

- Replace `pip` with `pip3` or `python3 -m pip` to select a correct version of Python.
- Add `--user` flag to install package locally (i. e. user-wide).

Package contains both wrapper and an appropriate binary for the platform, so you do not need to copy anything else anywhere. Just import the library in the source:

```python
from bearlibterminal import terminal

terminal.open()
terminal.printf(2, 1, "Hello, world!")
terminal.refresh()
while terminal.read() != terminal.TK_CLOSE:
    pass
terminal.close()
```

#### Lua

Wrapper for Lua is built-in. You need to use a regular (dynamic) Lua runtime and place BearLibTerminal binary
in a suitable location (e. g. in the same directory as script). For Linux you'll also need to rename the .so
to just 'BearLibTerminal.so' (dropping the 'lib' prefix). After that it would be possible to import the library
the usual way:

```lua
local terminal = require "BearLibTerminal" 
```

### Building

BearLibTerminal is a language-agnostic dynamic-link library (.dll/.so/.dylib), therefore you generally do not have
to build it yourself and may simply use the [prebuilt binaries](http://foo.wyrd.name/en:bearlibterminal#download).

To build BearLibTerminal you will need CMake and a recent GCC/MinGW compiler. For Linux any GCC version 4.6.3 and above
will do. For Windows there are several MinGW builds with various quirks, using [TDM-GCC](http://tdm-gcc.tdragon.net/) or
[mingw-builds](http://mingw-w64.org/doku.php/download/mingw-builds) (a flavour of mingw-w64) is recommended.
MinGW compiler MUST use Posix thread model.


### License

The library is licensed mainly under the MIT license with a few parts under other permissive licenses.
