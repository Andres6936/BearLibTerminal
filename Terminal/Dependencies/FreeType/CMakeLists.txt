CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(FreeType2 VERSION 2.0.0 LANGUAGES C)

INCLUDE_DIRECTORIES(./Include)

ADD_LIBRARY(FreeType2 STATIC
        Source/autofit/autofit.c
        Source/base/ftbase.c
        Source/base/ftbbox.c
        Source/base/ftdebug.c
        Source/base/ftfstype.c
        Source/base/ftgasp.c
        Source/base/ftglyph.c
        Source/base/ftinit.c
        Source/base/ftlcdfil.c
        Source/base/ftmm.c
        Source/base/ftsystem.c
        Source/raster/raster.c
        Source/sfnt/sfnt.c
        Source/smooth/smooth.c
        Source/truetype/truetype.c)

# Support to compiler on mode C 11 standard.
TARGET_COMPILE_FEATURES(FreeType2 PRIVATE c_std_11)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DFT2_BUILD_LIBRARY")
IF (UNIX)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
ENDIF ()
