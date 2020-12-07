CMAKE_MINIMUM_REQUIRED(VERSION 3.5 FATAL_ERROR)

IF (UNIX AND NOT APPLE)
    SET(LINUX TRUE)
ENDIF ()

OPTION(BUILD_SHARED_LIBS "Build dynamic version of library" ON)

# Define the library FreeType2
ADD_SUBDIRECTORY(Dependencies/FreeType)

# Define the library PicoPNG
ADD_SUBDIRECTORY(Dependencies/PicoPNG)

PROJECT(BearLibTerminal VERSION 2020.4 LANGUAGES CXX)

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

FILE(GLOB TERMINAL_HEADERS ./Source/*.hpp ./Source/*.h)

# Common flags
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fvisibility=hidden")
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


### Definition of Files Includes
INCLUDE_DIRECTORIES(./Dependencies/NanoJPEG/Include)


### Definition of <BearLibTerminal> Library

ADD_LIBRARY(BearLibTerminal
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


### Definition of Properties of <BearLibTerminal> Library

# Support to compiler on mode C++ 17 standard.
SET_TARGET_PROPERTIES(BearLibTerminal PROPERTIES CXX_STANDARD 17)
# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
TARGET_INCLUDE_DIRECTORIES(BearLibTerminal
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source/>
        $<INSTALL_INTERFACE:Include/>
        )

# <OUTPUT_DIR> is a variable that define the directory where the binaries are stored
SET(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/${CMAKE_SYSTEM_NAME}${BITNESS})
SET_TARGET_PROPERTIES(BearLibTerminal PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# Set a definition [TERMINAL_VERSION] with the version of this library (BearLibTerminal)
TARGET_COMPILE_DEFINITIONS(BearLibTerminal PRIVATE
        TERMINAL_VERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\")

### Link of Dependencies for <BearLibTerminal> Library

TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE FreeType2)
TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE PicoPNG)
TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE ${OPENGL_gl_LIBRARY})

IF (WIN32)
    TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE winmm.lib)
    TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE ${PROJECT_SOURCE_DIR}/Resource/Terminal-${BITNESS}bit.res)
ELSEIF (LINUX)
    TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE pthread)
ELSEIF (APPLE)
    TARGET_LINK_LIBRARIES(BearLibTerminal PRIVATE ${COCOA_LIBRARY})
ENDIF ()


### Support to Command <make install>

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
INCLUDE(GNUInstallDirs)

# 'make install' to the correct locations (provided by GNUInstallDirs).
INSTALL(TARGETS BearLibTerminal
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# This is for Windows
INSTALL(DIRECTORY Include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
