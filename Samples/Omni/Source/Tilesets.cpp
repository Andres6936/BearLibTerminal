/*
 * Tilesets.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <vector>

void TestTilesets()
{
    TerminalSet( "window.title='Omni: tilesets'" );
    TerminalComposition( TK_ON );

	// Load tilesets
    TerminalSet( "U+E100: ../Media/Runic.png, size=8x16" );
    TerminalSet( "U+E200: ../Media/Tiles.png, size=32x32, align=top-left" );
    TerminalSet(
            "U+E300: ../Media/fontawesome-webfont.ttf, size=24x24, spacing=3x2, codepage=../Media/fontawesome-codepage.txt" );
    TerminalSet( "zodiac font: ../Media/Zodiac-S.ttf, size=24x36, spacing=3x3, codepage=437" );

    TerminalClear( );
    TerminalColor( "white" );

    TerminalPrint( 2, 1, "[color=orange]1.[/color] Of course, there is default font tileset." );

    TerminalPrint( 2, 3, "[color=orange]2.[/color] You can load some arbitrary tiles and use them as glyphs:" );
    TerminalPrint
            (
                    2 + 3, 4,
                    "Fire rune ([color=red][U+E102][/color]), "
                    "water rune ([color=lighter blue][U+E103][/color]), "
                    "earth rune ([color=darker green][U+E104][/color])"
            );

    TerminalPrint( 2, 6, "[color=orange]3.[/color] Tiles are not required to be of the same size as font symbols:" );
    TerminalPut( 2 + 3 + 0, 7, 0xE200 + 7 );
    TerminalPut( 2 + 3 + 5, 7, 0xE200 + 8 );
    TerminalPut( 2 + 3 + 10, 7, 0xE200 + 9 );

    TerminalPrint( 2, 10, "[color=orange]4.[/color] Like font characters, tiles may be freely colored and combined:" );
    TerminalPut( 2 + 3 + 0, 11, 0xE200 + 8 );
    TerminalColor( "lighter orange" );
    TerminalPut( 2 + 3 + 5, 11, 0xE200 + 8 );
    TerminalColor( "orange" );
    TerminalPut( 2 + 3 + 10, 11, 0xE200 + 8 );
    TerminalColor( "dark orange" );
    TerminalPut( 2 + 3 + 15, 11, 0xE200 + 8 );

    TerminalColor( "white" );
	std::vector<int> order = {11, 10, 14, 12, 13};
	for (int i=0; i<order.size(); i++)
	{
        TerminalPut( 2 + 3 + 25 + i * 4, 11, 0xE200 + order[ i ] );
        TerminalPut( 2 + 3 + 25 + ( order.size( ) + 1 ) * 4, 11, 0xE200 + order[ i ] );
	}
    TerminalPut( 2 + 3 + 25 + order.size( ) * 4, 11, 0xE200 + 15 );

    TerminalPrint( 2, 14, "[color=orange]5.[/color] And tiles can even come from TrueType fonts like this:" );
	for (int i=0; i<6; i++)
	{
        TerminalPut( 2 + 3 + i * 5, 15, 0xE300 + i );
	}

    TerminalPrint( 2 + 3, 18, "...or like this:\n[font=zodiac]D F G S C" );

    TerminalRefresh( );

	for (int key=0; key!=TK_CLOSE && key!=TK_ESCAPE; key= TerminalRead( ));

	// Clean up
    TerminalSet( "U+E100: none; U+E200: none; U+E300: none; zodiac font: none" );
    TerminalComposition( TK_OFF );
}
