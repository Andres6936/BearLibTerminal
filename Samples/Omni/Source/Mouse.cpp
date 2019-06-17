/*
 * Mouse.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <sstream>

struct
{
	int x, y, width, height;
}
double_click_area = {1, 11, 17, 4}; // FIXME: common rectangle struct

void TestMouse()
{
    TerminalSet( "window.title='Omni: mouse input'" );
    TerminalSet( "input.filter={keyboard, mouse+}" );
    TerminalComposition( TK_ON );

	bool precise_mouse = false;
	bool cursor_visible = true;
	int mlx = -1, mly = -1;
	int mrx = -1, mry = -1;
	int scroll = 0;
	bool plate = false;

	// Flush input
	while ( TerminalHasInput( ))
	{
        TerminalRead( );
	}

	int counter = 0;

	for (bool proceed=true; proceed;)
	{
        TerminalClear( );

        TerminalColor( "white" );
        TerminalPrintF( 1, 1, "Received [color=orange]%d[/color] %s", counter, counter == 1 ? "event" : "events" );

        TerminalColor( "white" );
        TerminalPrintF
                (
                        1, 3,
                        "Buttons: "
                        "[color=%s]left "
                        "[color=%s]middle "
                        "[color=%s]right "
                        "[color=%s]x1 "
                        "[color=%s]x2 ",
                        TerminalState( TK_MOUSE_LEFT ) ? "orange" : "dark gray",
                        TerminalState( TK_MOUSE_MIDDLE ) ? "orange" : "dark gray",
                        TerminalState( TK_MOUSE_RIGHT ) ? "orange" : "dark gray",
                        TerminalState( TK_MOUSE_X1 ) ? "orange" : "dark gray",
                        TerminalState( TK_MOUSE_X2 ) ? "orange" : "dark gray"
                );

        TerminalPrintF
                (
                        1, 4,
                        "Cursor: [color=orange]%d:%d[/color] [color=dark gray]cells[/color]"
                        ", [color=orange]%d:%d[/color] [color=dark gray]pixels[/color]",
                        TerminalState( TK_MOUSE_X ),
                        TerminalState( TK_MOUSE_Y ),
                        TerminalState( TK_MOUSE_PIXEL_X ),
                        TerminalState( TK_MOUSE_PIXEL_Y )
                );

        TerminalPrintF
                (
                        1, 5,
                        "Wheel: [color=orange]%d[/color] [color=dark gray]delta[/color]"
                        ", [color=orange]%d[/color] [color=dark gray]cumulative",
                        TerminalState( TK_MOUSE_WHEEL ), scroll
                );

        TerminalPrintF
                (
                        1, 7, "[color=%s][U+25CF][/color] Precise mouse movement",
                        precise_mouse ? "orange" : "black"
                );
        TerminalPut( 1, 7, 0x25CB );

        TerminalPrintF
                (
                        1, 8, "[color=%s][U+25CF][/color] Mouse cursor is visible",
                        cursor_visible ? "orange" : "black"
                );
        TerminalPut( 1, 8, 0x25CB );

        TerminalPrint( double_click_area.x, double_click_area.y - 1, "Double-click here:" );
        TerminalColor( plate ? "darker orange" : "darker gray" );
		for (int x=double_click_area.x; x<=double_click_area.x+double_click_area.width; x++)
		{
			for (int y=double_click_area.y; y<=double_click_area.y+double_click_area.height; y++)
			{
                TerminalPut( x, y, 0x2588 ); // FIXME: fill_area
			}
		}

		int mx = TerminalState( TK_MOUSE_X );
		int my = TerminalState( TK_MOUSE_Y );
        TerminalColor( 0x60FFFFFF );
		for (int x = 0; x < 80; x++) TerminalPut( x, my, 0x2588 );
		for (int y = 0; y < 25; y++) if (y != my) TerminalPut( mx, y, 0x2588 );

        TerminalColor( 0x8000FF00 );
        TerminalPut( mlx, mly, 0x2588 );

        TerminalColor( 0x80FF00FF );
        TerminalPut( mrx, mry, 0x2588 );

        TerminalRefresh( );

		do
		{
			int code = TerminalRead( );
			counter += 1;

			if (code == TK_ESCAPE || code == TK_CLOSE)
			{
				proceed = false;
			}
			else if (code == TK_MOUSE_LEFT)
			{
				int x = TerminalState( TK_MOUSE_X );
				int y = TerminalState( TK_MOUSE_Y );

				if (x == 1 && (y == 7 || y == 8))
				{
					if (y == 7)
					{
						precise_mouse = !precise_mouse;
                        TerminalSetF( "input.precise-mouse=%s", precise_mouse ? "true" : "false" );
					}
					else
					{
						cursor_visible = !cursor_visible;
                        TerminalSetF( "input.mouse-cursor=%s", cursor_visible ? "true" : "false" );
					}
				}
				else if (x >= double_click_area.x && x <= (double_click_area.x+double_click_area.width) &&
						 y >= double_click_area.y && y <= (double_click_area.y+double_click_area.height))
				{
					int clicks = TerminalState( TK_MOUSE_CLICKS );
					if (clicks > 0 && clicks%2 == 0)
					{
						plate = !plate;
					}
				}
				else
				{
					mlx = x;
					mly = y;
				}
			}
			else if (code == TK_MOUSE_RIGHT)
			{
				mrx = TerminalState( TK_MOUSE_X );
				mry = TerminalState( TK_MOUSE_Y );
			}
			else if (code == TK_MOUSE_SCROLL)
			{
				scroll += TerminalState( TK_MOUSE_WHEEL );
			}
			else if (code == TK_SPACE)
			{
				cursor_visible = !cursor_visible;
                TerminalSetF( "input.mouse-cursor=%s", cursor_visible ? "true" : "false" );
			}
		}
		while (proceed && TerminalHasInput( ));
	}

    TerminalColor( "white" );
    TerminalComposition( TK_OFF );
    TerminalSet( "input: precise-mouse=false, mouse-cursor=true, filter={keyboard}" );
}
