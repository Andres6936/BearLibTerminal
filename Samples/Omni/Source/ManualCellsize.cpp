/*
 * TestManualCellsize.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <string>
#include <vector>

void TestManualCellsize()
{
    TerminalSet( "window.title='Omni: manual cellsize'" );

	const char* font_name = "../Media/VeraMono.ttf";
	std::vector<std::string> font_hintings = {"normal", "autohint", "none"};
	int font_hinting = 0;
	int font_size = 12;
	int cell_width = 8;
	int cell_height = 16;

	auto setup_font = [&](){
        TerminalSetF( "font: %s, size=%d, hinting=%s", font_name, font_size, font_hintings[ font_hinting ].c_str( ));};
	auto setup_cellsize = [&](){ TerminalSetF( "window: cellsize=%dx%d", cell_width, cell_height );};

	setup_cellsize();
	setup_font();

	while (true)
	{
        TerminalClear( );
        TerminalColor( "white" );

        TerminalPrintF( 2, 1, "Hello, world!" );
        TerminalPrintF( 2, 3, "[color=orange]Font size:[/color] %d", font_size );
        TerminalPrintF( 2, 4, "[color=orange]Font hinting:[/color] %s", font_hintings[ font_hinting ].c_str( ));
        TerminalPrintF( 2, 5, "[color=orange]Cell size:[/color] %dx%d", cell_width, cell_height );
        TerminalPrintF( 2, 7, "[color=orange]TIP:[/color] Use arrow keys to change cell size" );
        TerminalPrintF( 2, 8, "[color=orange]TIP:[/color] Use Shift+Up/Down arrow keys to change font size" );
        TerminalPrintF( 2, 9, "[color=orange]TIP:[/color] Use TAB to switch font hinting mode" );

        TerminalRefresh( );

		int key = TerminalRead( );

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
		else if (key == TK_LEFT && !TerminalState( TK_SHIFT ) && cell_width > 4)
		{
			cell_width -= 1;
			setup_cellsize();
		}
		else if (key == TK_RIGHT && !TerminalState( TK_SHIFT ) && cell_width < 24)
		{
			cell_width += 1;
			setup_cellsize();
		}
		else if (key == TK_DOWN && !TerminalState( TK_SHIFT ) && cell_height < 24)
		{
			cell_height += 1;
			setup_cellsize();
		}
		else if (key == TK_UP && !TerminalState( TK_SHIFT ) && cell_height > 4)
		{
			cell_height -= 1;
			setup_cellsize();
		}
		else if (key == TK_UP && TerminalState( TK_SHIFT ) && font_size < 64)
		{
			font_size += 1;
			setup_font();
		}
		else if (key == TK_DOWN && TerminalState( TK_SHIFT ) && font_size > 4)
		{
			font_size -= 1;
			setup_font();
		}
		else if (key == TK_TAB)
		{
			font_hinting = (font_hinting + 1) % font_hintings.size();
			setup_font();
		}
	}

    TerminalSet( "font: default; window.cellsize=auto" );
}
