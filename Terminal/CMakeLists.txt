CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)

### Support to Command <make install>

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
INCLUDE(GNUInstallDirs)

IF (UNIX AND NOT APPLE)
    SET(LINUX TRUE)
ENDIF ()


# CMake link shared library on Windows
# Ref: https://stackoverflow.com/a/41618677
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

OPTION(BUILD_SHARED_LIBS "Build dynamic version of library" ON)

ADD_SUBDIRECTORY(Dependencies/FreeType)
ADD_SUBDIRECTORY(Dependencies/NanoJPEG)
ADD_SUBDIRECTORY(Dependencies/PicoPNG)

PROJECT(BearLibTerminal VERSION 2020.12 LANGUAGES CXX)

#[[
Objective: Detect system bitness

The function <MATH> evaluate a mathematical <expression> and sets
 <variable> to the resulting value.

The mathematical expression must be given as a string (i.e.
 enclosed in double quotation marks). An example is "5 * (10 + 13)".

The variable <CMAKE_SIZEOF_VOID_P> is size of a void pointer.

This variable is set to the size of a pointer on the target machine, and
 is determined by a try compile. If a 64-bit size is found, then
 the library search path is modified to look for 64-bit  libraries
 first.

Possibles values of expression: 32, 64
]]

MATH(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

# Common flags
IF (WIN32)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DUNICODE")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static")
ELSEIF (LINUX)
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc")
ENDIF ()
IF (NOT BUILD_SHARED_LIBS)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBEARLIBTERMINAL_STATIC_BUILD")
ENDIF ()

FIND_PACKAGE(OpenGL)

IF (APPLE)
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
ENDIF ()

### Definition of <BearLibTerminal> Library

ADD_LIBRARY(BearLibTerminal.Framework
        Source/Atlas.cpp
        Source/Base64.cpp
        Source/BearLibTerminal.cpp
        Source/Bitmap.cpp
        Source/BitmapTileset.cpp
        Source/BOM.cpp
        Source/Config.cpp
        Source/DynamicTileset.cpp
        Source/Encoding.cpp
        Source/Keystroke.cpp
        Source/LoadBitmap.cpp
        Source/LoadBMP.cpp
        Source/LoadJPEG.cpp
        Source/LoadPNG.cpp
        Source/Log.cpp
        Source/Luaopen.cpp
        Source/OpenGL.cpp
        Source/OptionGroup.cpp
        Source/Options.cpp
        Source/Palette.cpp
        Source/Platform.cpp
        Source/Resource.cpp
        Source/SaveBMP.cpp
        Source/Stage.cpp
        Source/Terminal.cpp
        Source/Texture.cpp
        Source/Tileset.cpp
        Source/TrueTypeTileset.cpp
        Source/Utility.cpp
        Source/WinApiWindow.cpp
        Source/Window.cpp
        Source/X11Window.cpp
        # Insert source code only if the platform is Apple (macOS)
        $<$<PLATFORM_ID:Darwin>:Source/CocoaWindow.mm>
        )

ADD_LIBRARY(BearLibTerminal::Framework ALIAS BearLibTerminal.Framework)


### Definition of Properties of <BearLibTerminal> Library

# Support to compiler on mode C++ 17 standard.
SET_TARGET_PROPERTIES(BearLibTerminal.Framework PROPERTIES CXX_STANDARD 17)
# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
# Adding the install interface generator expression makes sure
# that the include file are installed to the proper location (provided
# by GNUInstallDirs.
TARGET_INCLUDE_DIRECTORIES(BearLibTerminal.Framework
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/>
        )

# Set a definition [TERMINAL_VERSION] with the version of this library (BearLibTerminal)
TARGET_COMPILE_DEFINITIONS(BearLibTerminal.Framework PRIVATE
        TERMINAL_VERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\")

### Link of Dependencies for <BearLibTerminal> Library

TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE FreeType2)
TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE BearLibTerminal::NanoPNG)
TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE PicoPNG)
TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE ${OPENGL_gl_LIBRARY})

IF (WIN32)
    TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE winmm.lib)
    TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE ${PROJECT_SOURCE_DIR}/Resource/Terminal-${BITNESS}bit.res)
ELSEIF (LINUX)
    TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE pthread)
ELSEIF (APPLE)
    TARGET_LINK_LIBRARIES(BearLibTerminal.Framework PRIVATE ${COCOA_LIBRARY})
ENDIF ()

# 'make install' to the correct locations (provided by GNUInstallDirs).
INSTALL(TARGETS BearLibTerminal.Framework
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# This is for Windows
INSTALL(DIRECTORY Include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
