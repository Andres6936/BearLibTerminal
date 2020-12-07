CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(PicoPNG VERSION 1.0.0 LANGUAGES CXX)

ADD_LIBRARY(PicoPNG STATIC Source/PicoPNG.cpp)

# The POSITION_INDEPENDENT_CODE property determines whether position
# independent executables or shared libraries will be created. This
# property is True by default for SHARED and MODULE library targets
# and False otherwise.
SET_TARGET_PROPERTIES(PicoPNG PROPERTIES POSITION_INDEPENDENT_CODE ON)
# Support to compiler on mode C++ 17 standard.
SET_TARGET_PROPERTIES(PicoPNG PROPERTIES CXX_STANDARD 17)
TARGET_INCLUDE_DIRECTORIES(PicoPNG PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>)