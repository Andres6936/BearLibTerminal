/*
 * Layers.cpp
 *
 *  Created on: Dec 9, 2013
 *      Author: Cfyz
 */

#include "Common.hpp"

void TestLayers()
{
    TerminalSet( "window.title='Omni: layers'" );

	color_t pixel = ColorFromName( "dark gray" );
	terminal_setf("U+E000: %#p, raw-size=1x1, resize=48x48, resize-filter=nearest", &pixel);

	while (true)
	{
        TerminalClear( );
		terminal_color("white");

		terminal_print(2, 1, "[color=orange]1.[/color] Without layers:");
        TerminalPut( 7, 3, 0xE000 );
		terminal_print(5, 4, "[color=dark green]abcdefghij");

		terminal_print(2, 8, "[color=orange]2.[/color] With layers:");
        TerminalLayer( 1 );
        TerminalPut( 7, 10, 0xE000 );
        TerminalLayer( 0 );
		terminal_print(5, 11, "[color=dark green]abcdefghij");

        TerminalRefresh( );

		int key = TerminalRead( );

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
	}

    TerminalSet( "U+E000: none" );
}
