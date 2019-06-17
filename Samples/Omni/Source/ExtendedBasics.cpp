/*
 * ExtendedBasics.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <cmath>
#include <vector>

const float g_pi = 3.141592654f;

void TestExtendedBasics()
{
	// Setup
    TerminalSet( "window.title='Omni: extended output / basics'" );
    TerminalSet( "0xE000: ../Media/Tiles.png, size=32x32, align=top-left" );
    TerminalComposition( TK_ON );

	int cx = 10, cy = 5;
	int n_symbols = 10;
	int radius = 5;
	float angle = 0.0f;
	int fps = 25;
	color_t transparent = 0x00FFFFFF, opaque = 0xFFFFFFFF;

	color_t m00[] = {0xFFFF0000, 0xFF00FF00, 0xFF0000FF, 0xFFFFFF00};
	color_t m01[] = {opaque, opaque, transparent, transparent};

	color_t m11[] = {transparent, transparent, opaque, transparent};
	color_t m12[] = {transparent, opaque, transparent, transparent};
	color_t m21[] = {transparent, transparent, transparent, opaque};
	color_t m22[] = {opaque, transparent, transparent, transparent};

	for (bool proceed=true; proceed;)
	{
        TerminalClear( );
        TerminalColor( "white" );

        TerminalPrint( 2, 1,
                       "[color=orange]1.[/color] TerminalPutExt(x, y, [color=orange]dx[/color], [color=orange]dy[/color], code, corners);" );
		for (int i=0; i<n_symbols; i++)
		{
			float angle_delta = 2.0f*g_pi/n_symbols;
			float dx = std::cos(angle+i*angle_delta)*radius* TerminalState( TK_CELL_WIDTH );
			float dy = std::sin(angle+i*angle_delta)*radius* TerminalState( TK_CELL_WIDTH )-4;
            TerminalColor( i ? "white" : "orange" );
            TerminalPutExt( cx, cy, dx, dy, 'a' + i, nullptr );
		}
		angle += 2.0f*g_pi / (2*fps);

        TerminalPrint( 2, 9,
                       "[color=orange]2.[/color] TerminalPutExt(x, y, dx, dy, code, [color=orange]corners[/color]);" );
        TerminalPutExt( 5, 11, 0, 0, 0xE000 + 19, m00 );
        TerminalPutExt( 10, 11, 0, 0, 0xE000 + 19, m01 );

        TerminalPrint( 2, 14, "[color=orange]3.[/color] TerminalPutExt + composition" );
		int x1 = 5;
		int y1 = 16;
        TerminalPut( x1 + 0, y1 + 0, 0xE000 + 19 );
        TerminalPut( x1 + 0, y1 + 2, 0xE000 + 8 );
        TerminalPut( x1 + 5, y1 + 0, 0xE000 + 19 );
        TerminalPut( x1 + 9, y1 + 0, 0xE000 + 19 );
        TerminalPut( x1 + 5, y1 + 2, 0xE000 + 19 );
        TerminalPut( x1 + 9, y1 + 2, 0xE000 + 19 );
        TerminalPutExt( x1 + 5, y1 + 0, 0, 0, 0xE000 + 8, m11 );
        TerminalPutExt( x1 + 9, y1 + 0, 0, 0, 0xE000 + 8, m12 );
        TerminalPutExt( x1 + 5, y1 + 2, 0, 0, 0xE000 + 8, m21 );
        TerminalPutExt( x1 + 9, y1 + 2, 0, 0, 0xE000 + 8, m22 );

        TerminalRefresh( );

		while ( TerminalHasInput( ))
		{
			int key = TerminalRead( );
			if (key == TK_CLOSE || key == TK_ESCAPE)
			{
				proceed = false;
				break;
			}
		}

        TerminalDelay( 1000 / fps );
	}

	// Clean up
    TerminalComposition( TK_OFF );
    TerminalSet( "0xE000: none" );
}
