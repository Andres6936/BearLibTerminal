CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

IF (UNIX AND NOT APPLE)
    SET(LINUX TRUE)
ENDIF ()

OPTION(BUILD_SHARED_LIBS "Build dynamic version of library" ON)

# Define the library FreeType2
ADD_SUBDIRECTORY(Dependencies/FreeType)

# Define the library PicoPNG
ADD_SUBDIRECTORY(Dependencies/PicoPNG)

PROJECT(BearLibTerminal VERSION 2020.4 LANGUAGES CXX)

#[=[
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
]=]#
MATH(EXPR BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

FILE(GLOB TERMINAL_HEADERS ./Source/*.hpp ./Source/*.h)
LIST(APPEND TERMINAL_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/Include/C/BearLibTerminal.hpp")
IF (APPLE)
    FILE(GLOB TERMINAL_SOURCES ./Source/*.cpp ./Source/*.mm)
ELSE ()
    FILE(GLOB TERMINAL_SOURCES ./Source/*.cpp) # FIXME: manual selection
ENDIF ()

# Common flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
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

INCLUDE_DIRECTORIES(./Include/C)
INCLUDE_DIRECTORIES(./Dependencies/FreeType/Include)
INCLUDE_DIRECTORIES(./Dependencies/PicoPNG/Include)
INCLUDE_DIRECTORIES(./Dependencies/NanoJPEG/Include)

ADD_LIBRARY(BearLibTerminal ${TERMINAL_SOURCES} ${TERMINAL_HEADERS})

# Set a definition [TERMINAL_VERSION] with the version of this library (BearLibTerminal)
TARGET_COMPILE_DEFINITIONS(BearLibTerminal PRIVATE
        TERMINAL_VERSION=\"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}\")

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

SET(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/Output/${CMAKE_SYSTEM_NAME}${BITNESS})

SET_TARGET_PROPERTIES(BearLibTerminal PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}
        ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
