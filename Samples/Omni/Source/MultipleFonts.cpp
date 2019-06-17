/*
 * MultipleFonts.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: cfyz
 */

#include "Common.hpp"

void TestMultipleFonts()
{
    TerminalSet( "window.title='Omni: multiple fonts in scene'" );

	// Load several fonts
    TerminalSet( "window.size=64x20; font: ../Media/VeraMono.ttf, size=10x20" );
    TerminalSet( "italic font: ../Media/VeraMoIt.ttf, size=10x20" );
    TerminalSet( "bold font: ../Media/VeraMoBd.ttf, size=10x20" );
    TerminalSet( "huge font: ../Media/VeraMono.ttf, size=20x40, spacing=2x2" );

    TerminalClear( );
    TerminalColor( "white" );
	int h = TerminalPrintExt
            (
                    2, 1, 60, 0, TK_ALIGN_DEFAULT,
                    "If you [color=orange][font=italic]really[/font][/color] want, "
                    "you can even put [color=orange][font=bold]emphasis[/font][/color] on a text. "
                    "This works by loading several truetype tilesets with custom codepages to an "
                    "unused code points and using [color=orange]font[/color] postformatting tag."
            ).height;

    TerminalPrintExt
            (
                    2, 1 + h + 1, 60, 0, TK_ALIGN_DEFAULT,
                    "[font=huge]It's pretty easy to print in bigger fonts as well."
            );
    TerminalRefresh( );

	for (int key=0; key!=TK_CLOSE && key!=TK_ESCAPE; key= TerminalRead( ));

	// Clean up
    TerminalSet( "window.size=80x25; font: default; italic font: none; bold font: none; huge font: none" );
}
