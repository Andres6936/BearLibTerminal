/*
 * TextAlignment.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: cfyz
 */

#include "Common.hpp"

#include <cmath>
#include <map>

namespace { // anonymous

enum Alignment
{
	Left   = 1,
	Center = 2,
	Right  = 3,
	Top    = 1,
	Bottom = 3
};

const char* lorem_ipsum =
	"[c=orange]Lorem[/c] ipsum dolor sit amet, consectetur adipisicing elit, "
	"sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
	"[c=orange]Ut[/c] enim ad minim veniam, quis nostrud exercitation ullamco "
	"laboris nisi ut aliquip ex ea commodo consequat. [c=orange]Duis[/c] aute "
	"irure dolor in reprehenderit in voluptate velit esse cillum dolore eu "
	"fugiat nulla pariatur. [c=orange]Excepteur[/c] sint occaecat cupidatat "
	"non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

const int padding_h = 4;
const int padding_v = 2;

int frame_left = 0;
int frame_top = 0;
int frame_width = 0;
int frame_height = 0;

void UpdateGeometry()
{
	frame_left = padding_h;
	frame_top = padding_v * 2 + 2;
	frame_width = TerminalState( TK_WIDTH ) - frame_left - padding_h;
	frame_height = TerminalState( TK_HEIGHT ) - frame_top - padding_v;
}

} // namespace anonymous

void TestTextAlignment()
{
    TerminalSet( "window.title='Omni: text alignment', resizeable=true, minimum-size=44x12" );
    TerminalComposition( TK_ON );

	std::map<int, std::string> names =
	{
		{TK_ALIGN_LEFT, "TK_ALIGN_LEFT"},
		{TK_ALIGN_CENTER, "TK_ALIGN_CENTER"},
		{TK_ALIGN_RIGHT, "TK_ALIGN_RIGHT"},
		{TK_ALIGN_TOP, "TK_ALIGN_TOP"},
		{TK_ALIGN_MIDDLE, "TK_ALIGN_MIDDLE"},
		{TK_ALIGN_BOTTOM, "TK_ALIGN_BOTTOM"},
	};
	int horisontal_align = TK_ALIGN_LEFT;
	int vertical_align = TK_ALIGN_TOP;

	UpdateGeometry();

	while (true)
	{
        TerminalClear( );

		// Background square
        TerminalBackColor( "darkest gray" );
        TerminalClearArea( frame_left, frame_top, frame_width, frame_height );
        TerminalBackColor( "none" );

		// Comment
        TerminalPrintF
                (
                        frame_left,
                        frame_top - padding_v - 2,
                        "Use arrows to change text alignment.\n"
                        "Current alignment is [c=orange]%s[/c] | [c=orange]%s[/c].",
                        names[ vertical_align ].c_str( ),
                        names[ horisontal_align ].c_str( )
                );

		// Text origin
		int x = frame_left, y = frame_top;

        TerminalColor( "white" );
        TerminalPrintExt( x, y, frame_width, frame_height, vertical_align | horisontal_align, lorem_ipsum );

        TerminalPrint( 80 - 14, 3, "[c=orange][U+2588]" );
        TerminalPrintExt( 80 - 14, 3, 0, 0, vertical_align | horisontal_align, "12345\nabc\n-=#=-" );

        TerminalRefresh( );

		int key = TerminalRead( );

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
		else if (key == TK_LEFT)
		{
			horisontal_align = (horisontal_align == TK_ALIGN_RIGHT)? TK_ALIGN_CENTER: TK_ALIGN_LEFT;
		}
		else if (key == TK_RIGHT)
		{
			horisontal_align = (horisontal_align == TK_ALIGN_LEFT)? TK_ALIGN_CENTER: TK_ALIGN_RIGHT;
		}
		else if (key == TK_UP)
		{
			vertical_align = (vertical_align == TK_ALIGN_BOTTOM)? TK_ALIGN_MIDDLE: TK_ALIGN_TOP;
		}
		else if (key == TK_DOWN)
		{
			vertical_align = (vertical_align == TK_ALIGN_TOP)? TK_ALIGN_MIDDLE: TK_ALIGN_BOTTOM;
		}
		else if (key == TK_RESIZED)
		{
			UpdateGeometry();
		}
	}

    TerminalComposition( TK_OFF );
    TerminalSet( "window.resizeable=false" );
}
