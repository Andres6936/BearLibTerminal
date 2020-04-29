CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

PROJECT(BearLibTerminal VERSION 2020.4 LANGUAGES CXX )

# Include guards, avoid called to cmake from the main directory
# For a correct use, is better create an new directory (called
# <Build> for example) and call to cmake
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

ADD_SUBDIRECTORY(./Terminal)

IF (IS_DIRECTORY "${CMAKE_SOURCE_DIR}/Samples")
    ADD_SUBDIRECTORY(./Samples/Omni)
ENDIF ()