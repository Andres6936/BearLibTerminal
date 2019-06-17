/*
 * Sprites.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"

void TestSprites()
{
	terminal_set("window.title='Omni: sprites'");

	terminal_set("U+E000: ../Media/Background.jpg");
	terminal_set("U+E001: ../Media/EasternDragon.png, resize=128x128, resize-filter=nearest");
	terminal_set("U+E002: ../Media/FiveElements.bmp, resize=128x128, resize-filter=bilinear");

	color_t c[] =
	{
		color_from_argb(128, 192, 64, 64),
		color_from_argb(128, 64, 192, 64),
		color_from_argb(128, 64, 64, 192),
		color_from_argb(128, 192, 192, 64)
	};
	terminal_setf("U+E003: %#p, raw-size=2x2, resize=128x128, resize-filter=bicubic", &c);

    TerminalClear( );

	terminal_color("black");
	terminal_print(2, 1, "[color=black]This primarily serves as a quick test of image format support");
	terminal_print(2, 3, "1. Background is loaded from a JPEG file");
	terminal_print(2, 5, "2. Dragon sprite is loaded from a PNG file\n   image is upscaled 2x with nearest neighbourhood filter");
	terminal_print(2, 8, "3. Five elements diagram is loaded from BMP file\n   image is downscaled with bilinear filer");
	terminal_print(2, 11, "4. Color gradient is loaded from 2x2 in-memory buffer\n   image is upscaled 64x with bicubic filter");

	terminal_color("white");
    TerminalPut( 0, 0, 0xE000 ); // Background
    TerminalPut( 5, 14, 0xE001 ); // Dragon
    TerminalPut( 5 + 18 * 1, 14, 0xE002 ); // FiveElements
    TerminalPut( 5 + 18 * 2, 14, 0xE003 ); // Gradient

    TerminalRefresh( );

	while (true)
	{
		int key = TerminalRead( );

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
	}

	terminal_set("U+E000: none; U+E001: none; U+E002: none; U+E003: none");
}
