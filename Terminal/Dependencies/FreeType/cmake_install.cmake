# Install script for directory: /home/andres6936/CLionProjects/BearLibTerminal/Terminal/Dependencies/FreeType

# Set the install prefix
IF (NOT DEFINED CMAKE_INSTALL_PREFIX)
    SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF ()
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF (NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
    IF (BUILD_TYPE)
        STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
                CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
    ELSE ()
        SET(CMAKE_INSTALL_CONFIG_NAME "Release")
    ENDIF ()
    MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF ()

# Set the component getting installed.
IF (NOT CMAKE_INSTALL_COMPONENT)
    IF (COMPONENT)
        MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
        SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
    ELSE ()
        SET(CMAKE_INSTALL_COMPONENT)
    ENDIF ()
ENDIF ()

# Install shared libraries without execute permission?
IF (NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
    SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF ()

# Is this installation the result of a crosscompile?
IF (NOT DEFINED CMAKE_CROSSCOMPILING)
    SET(CMAKE_CROSSCOMPILING "FALSE")
ENDIF ()

