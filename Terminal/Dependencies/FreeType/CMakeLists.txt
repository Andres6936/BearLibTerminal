CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(FreeType2 VERSION 2.0.0 LANGUAGES C)

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

# The POSITION_INDEPENDENT_CODE property determines whether position
# independent executables or shared libraries will be created. This
# property is True by default for SHARED and MODULE library targets
# and False otherwise.
SET_TARGET_PROPERTIES(FreeType2 PROPERTIES POSITION_INDEPENDENT_CODE ON)
# Support to compiler on mode C 11 standard.
SET_TARGET_PROPERTIES(FreeType2 PROPERTIES C_STANDARD 11)
TARGET_COMPILE_DEFINITIONS(FreeType2 PRIVATE -DFT2_BUILD_LIBRARY)
# Adding the install interface generator expression makes sure
# that the include file are installed to the proper location (provided
# by GNUInstallDirs.
TARGET_INCLUDE_DIRECTORIES(FreeType2 PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include/>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
