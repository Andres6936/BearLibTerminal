CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(NanoPNG VERSION 2.0.0 LANGUAGES C)

ADD_LIBRARY(BearLibTerminal.NanoPNG INTERFACE)
ADD_LIBRARY(BearLibTerminal::NanoPNG ALIAS BearLibTerminal.NanoPNG)

TARGET_COMPILE_DEFINITIONS(BearLibTerminal.NanoPNG INTERFACE CXX_STD_17)
# Adding the install interface generator expression makes sure
# that the include file are installed to the proper location (provided
# by GNUInstallDirs.
TARGET_INCLUDE_DIRECTORIES(BearLibTerminal.NanoPNG INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)