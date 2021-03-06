/*
 * BasicOutput.cpp
 *
 *  Created on: Nov 27, 2013
 *      Author: cfyz
 */

#include "Common.hpp"

void TestBasicOutput()
{
    TerminalSet( "window.title='Omni: basic output'" );
    TerminalClear( );
    TerminalColor( "white" );

	// Wide color range
	int n = TerminalPrintF( 2, 1, "[color=orange]1.[/color] Wide color range: " ).width;
	const char long_word[] = "antidisestablishmentarianism.";
	const size_t long_word_length = sizeof(long_word)-1;
	for (size_t i = 0; i < long_word_length; i++)
	{
		float factor = float(i)/long_word_length;
		int red = (1.0f - factor) * 255;
		int green = factor * 255;
        TerminalColor( ColorFromARGB( 255, red, green, 0 ));
        TerminalPut( 2 + n + i, 1, long_word[ i ] );
	}
    TerminalColor( "white" );

    TerminalPrint( 2, 3,
                   "[color=orange]2.[/color] Backgrounds: [color=black][bkcolor=gray] grey [/bkcolor] [bkcolor=red] red " );

    TerminalPrint( 2, 5, L"[color=orange]3.[/color] Unicode support: Кириллица Ελληνικά α=β²±2°" );

    TerminalPrint( 2, 7,
                   L"[color=orange]4.[/color] Tile composition: a + [color=red]/[/color] = a[+][color=red]/[/color], a vs. a[+][color=red]¨[/color]" );

    TerminalPrintF( 2, 9, "[color=orange]5.[/color] Box drawing symbols:" );

    TerminalPrint
            (
                    5, 11,
                    L"   ┌────────┐  \n"
                    L"   │!......s└─┐\n"
                    L"┌──┘........s.│\n"
                    L"│............>│\n"
                    L"│...........┌─┘\n"
                    L"│<.@..┌─────┘  \n"
                    L"└─────┘        \n"
            );

    TerminalRefresh( );
	for (int key=0; key!=TK_CLOSE && key!=TK_ESCAPE; key= TerminalRead( ));
}
