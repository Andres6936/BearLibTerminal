CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(freetype2)

SET(SOURCES ./Source/autofit/autofit.c
        ./Source/base/ftbase.c
        ./Source/base/ftbbox.c
        ./Source/base/ftdebug.c
        ./Source/base/ftfstype.c
        ./Source/base/ftgasp.c
        ./Source/base/ftglyph.c
        ./Source/base/ftinit.c
        ./Source/base/ftlcdfil.c
        ./Source/base/ftmm.c
        ./Source/base/ftsystem.c
        ./Source/raster/raster.c
        ./Source/sfnt/sfnt.c
        ./Source/smooth/smooth.c
        ./Source/truetype/truetype.c)

INCLUDE_DIRECTORIES(./Include)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFT2_BUILD_LIBRARY")
IF (UNIX)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
ENDIF ()

ADD_LIBRARY(freetype2 STATIC ${SOURCES})
