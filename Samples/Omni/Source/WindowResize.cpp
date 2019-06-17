/*
 * WindowResize.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: cfyz
 */

#include "Common.hpp"

void TestWindowResize()
{
	terminal_set("window: title='Omni: window resizing', resizeable=true, minimum-size=27x5");

	const int symbol = 0x2588;

	while (true)
	{
        TerminalClear( );
		int w = terminal_state(TK_WIDTH);
		int h = terminal_state(TK_HEIGHT);
		for (int x=0; x<w; x++)
		{
            TerminalPut( x, 0, x % 2 ? symbol : ( int ) '#' );
            TerminalPut( x, h - 1, x % 2 ? symbol : ( int ) '#' );
		}
		for (int y=0; y<h; y++)
		{
            TerminalPut( 0, y, y % 2 ? symbol : ( int ) '#' );
            TerminalPut( w - 1, y, y % 2 ? symbol : ( int ) '#' );
		}
		terminal_printf(3, 2, "Terminal size is %dx%d", w, h);
        TerminalRefresh( );

		int key = terminal_read();

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
	}

	terminal_set("window: resizeable=false");
}
