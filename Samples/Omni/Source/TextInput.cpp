/*
 * TextInput.cpp
 *
 *  Created on: Dec 6, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <map>
#include <string>

std::map<int, std::string> key_names =
{
	{0, ""},
	{TK_MOUSE_LEFT, "LMB"},
	{TK_MOUSE_RIGHT, "RMB"},
	{TK_MOUSE_MIDDLE, "MMB"},
	{TK_CLOSE, "Close"},
	{TK_BACKSPACE, "Backspace"},
	{TK_TAB, "Tab"},
	{TK_RETURN, "Enter"},
	{TK_SHIFT, "Shift"},
	{TK_CONTROL, "Ctrl"},
	{TK_PAUSE, "Pause"},
	{TK_ESCAPE, "Escape"},
	{TK_PAGEUP, "Page Up"},
	{TK_PAGEDOWN, "Page Down"},
	{TK_END, "End"},
	{TK_HOME, "Home"},
	{TK_LEFT, "Left"},
	{TK_UP, "Up"},
	{TK_RIGHT, "Right"},
	{TK_DOWN, "Down"},
	{TK_INSERT, "Insert"},
	{TK_DELETE, "Delete"},
	{TK_F1, "F1"},
	{TK_F2, "F2"},
	{TK_F3, "F3"},
	{TK_F4, "F4"},
	{TK_F5, "F5"},
	{TK_F6, "F6"},
	{TK_F7, "F7"},
	{TK_F8, "F8"},
	{TK_F9, "F9"},
	{TK_F10, "F10"},
	{TK_F11, "F11"},
	{TK_F12, "F12"},
	{TK_KP_DIVIDE, "Keypad /"},
	{TK_KP_MULTIPLY, "Keypad *"},
	{TK_KP_MINUS, "Keypad -"},
	{TK_KP_PLUS, "Keypad +"},
	{TK_KP_ENTER, "Keypad Enter"},
	{TK_KP_0, "Keypad 0"},
	{TK_KP_1, "Keypad 1"},
	{TK_KP_2, "Keypad 2"},
	{TK_KP_3, "Keypad 3"},
	{TK_KP_4, "Keypad 4"},
	{TK_KP_5, "Keypad 5"},
	{TK_KP_6, "Keypad 6"},
	{TK_KP_7, "Keypad 7"},
	{TK_KP_8, "Keypad 8"},
	{TK_KP_9, "Keypad 9"},
	{TK_KP_PERIOD, "Keypad ."},
};

void DrawFrame(int x, int y, int w, int h)
{
    TerminalClearArea( x, y, w, h );

	for (int i=x; i<x+w; i++)
	{
        TerminalPut( i, y, L'─' );
        TerminalPut( i, y + h - 1, L'─' );
	}

	for (int j=y; j<y+h; j++)
	{
        TerminalPut( x, j, L'│' );
        TerminalPut( x + w - 1, j, L'│' );
	}

    TerminalPut( x, y, L'┌' );
    TerminalPut( x + w - 1, y, L'┐' );
    TerminalPut( x, y + h - 1, L'└' );
    TerminalPut( x + w - 1, y + h - 1, L'┘' );
}

void TestTextInput()
{
    TerminalSet( "window.title='Omni: text input'" );
    TerminalComposition( TK_OFF );

	const int max_chars = 32;
	wchar_t buffer[max_chars+1] = {0};
	wchar_t character = L' ';
	int result = 0;
	int char_result = 0;

	while (true)
	{
        TerminalClear( );
        TerminalColor( "white" );

        TerminalPrint( 2, 1, "Select different input tests by pressing corresponding number:" );

        TerminalPrint( 2, 3, "[color=orange]1.[/color] TerminalReadStr" );
		DrawFrame(5, 4, max_chars+2, 3);
        TerminalPrintF( 6, 5, L"%ls", buffer );
        TerminalPrintF( 5 + max_chars + 2 + 1, 5, "[color=gray] %s", result >= 0 ? "OK" : "Cancelled" );

        TerminalPrint( 2, 8, "[color=orange]2.[/color] terminal_read_char" );
		DrawFrame(5, 9, 5, 3);
        TerminalPut( 7, 10, character );
        TerminalPrintF( 5 + 3 + 2 + 1, 10, "[color=gray]%s",
                        ( key_names.count( char_result ) ? key_names[ char_result ] : to_string(
                                char_result )).c_str( ));

        TerminalRefresh( );

		int key = TerminalRead( );

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
		else if (key == TK_1)
		{
            TerminalColor( "orange" );
			DrawFrame(5, 4, max_chars+2, 3);
			result = TerminalReadWStr( 6, 5, buffer, max_chars );
		}
		else if (key == TK_2)
		{
            TerminalColor( "orange" );
			DrawFrame(5, 9, 5, 3);

			do
			{
                TerminalPut( 7, 10, character );
                TerminalClearArea( 5 + 3 + 2 + 1, 10, 16, 1 );
                TerminalPrintF( 5 + 3 + 2 + 1, 10, "[color=gray]%s",
                                ( key_names.count( char_result ) ? key_names[ char_result ] : to_string(
                                        char_result )).c_str( ));
                TerminalRefresh( );

				character = L' ';
				int key = TerminalRead( );
				if (key == TK_ESCAPE || key == TK_CLOSE || key == TK_RETURN)
				{
					break;
				}
				else if ( TerminalCheck( TK_WCHAR ))
				{
					character = TerminalState( TK_WCHAR );
					char_result = key;
				}
				else if (key < TK_KEY_RELEASED)
				{
					char_result = key;
				}
			}
			while (true);
		}
	}
}
