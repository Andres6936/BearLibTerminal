/*
 * Common.hpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include "BearLibTerminal/BearLibTerminal.hpp"
#include <stdint.h>
#include <sstream>

template<typename T> std::string to_string(const T& value)
{
	std::ostringstream ss;
	ss << value;
	return ss.str();
}

void TestBasicOutput();
void TestDefaultFont();
void TestTilesets();
void TestSprites();
void TestManualCellsize();
void TestAutoGenerated();
void TestMultipleFonts();
void TestTextAlignment();
void TestFormattedLog();
void TestFontViewer();
void TestLayers();
void TestExtendedBasics();
void TestExtendedInterlayer();
void TestExtendedSmoothScroll();
void TestDynamicSprites();
void TestSpeed();
void TestKeyboard();
void TestMouse();
void TestTextInput();
void TestInputFiltering();
void TestWindowResize();
void TestPick();

#endif /* COMMON_HPP_ */
