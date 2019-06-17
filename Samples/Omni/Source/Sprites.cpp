/*
 * Sprites.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"

void TestSprites()
{
    TerminalSet( "window.title='Omni: sprites'" );

    TerminalSet( "U+E000: ../Media/Background.jpg" );
    TerminalSet( "U+E001: ../Media/EasternDragon.png, resize=128x128, resize-filter=nearest" );
    TerminalSet( "U+E002: ../Media/FiveElements.bmp, resize=128x128, resize-filter=bilinear" );

	color_t c[] =
	{
            ColorFromARGB( 128, 192, 64, 64 ),
        ColorFromARGB( 128, 64, 192, 64 ),
        ColorFromARGB( 128, 64, 64, 192 ),
        ColorFromARGB( 128, 192, 192, 64 )
	};
    TerminalSetF( "U+E003: %#p, raw-size=2x2, resize=128x128, resize-filter=bicubic", &c );

    TerminalClear( );

    TerminalColor( "black" );
    TerminalPrint( 2, 1, "[color=black]This primarily serves as a quick test of image format support" );
    TerminalPrint( 2, 3, "1. Background is loaded from a JPEG file" );
    TerminalPrint( 2, 5,
                   "2. Dragon sprite is loaded from a PNG file\n   image is upscaled 2x with nearest neighbourhood filter" );
    TerminalPrint( 2, 8,
                   "3. Five elements diagram is loaded from BMP file\n   image is downscaled with bilinear filer" );
    TerminalPrint( 2, 11,
                   "4. Color gradient is loaded from 2x2 in-memory buffer\n   image is upscaled 64x with bicubic filter" );

    TerminalColor( "white" );
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

    TerminalSet( "U+E000: none; U+E001: none; U+E002: none; U+E003: none" );
}
