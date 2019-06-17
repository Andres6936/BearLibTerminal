#include "Common.hpp"
#include <cstdlib>
#include <ctime>

void TestPick()
{
	terminal_set("window.title='Omni: examining cell contents'");
	terminal_set("input.filter={keyboard, mouse}"); // Enable mouse events.

    TerminalClear( );
	terminal_color("white");
	terminal_printf(2, 1, "Move mouse over characters:");

	terminal_bkcolor("darkest gray");
    TerminalClearArea( 2, 3, 76, 19 );
	terminal_bkcolor("none");

	const char* colors[] = {"red", "orange", "yellow", "green", "cyan", "light blue", "violet"};
	int combining[] = {0x02C6, 0x02C9, 0x02DC, 0x2014, 0x2044, 0x2017, 0x203E};

	std::srand(std::time(nullptr));
	for (int i = 0; i < 100; i++)
	{
		bool combined = (rand() % 5 == 0);
		int n = combined? (rand() % 2) + 2: 1;
		int x = 2 + (rand() % 76);
		int y = 3 + (rand() % 19);

		terminal_color(colors[rand() % 7]);
        TerminalPut( x, y, 'a' + ( rand( ) % 26 ));

        TerminalComposition( TK_ON );
		for (int i = 1; i < n; i++)
		{
			terminal_color(colors[rand() % 7]);
            TerminalPut( x, y, combining[ rand( ) % 7 ] );
		}
        TerminalComposition( TK_OFF );
	}

	terminal_color("white");

	while (true)
	{
		int x = TerminalState( TK_MOUSE_X );
		int y = TerminalState( TK_MOUSE_Y );

        TerminalClearArea( 2, 23, 76, 1 );
		if (x >= 2 && x < 78 && y >= 3 && y < 22)
		{
			int n = 0;

			do
			{
				int code = TerminalPick( x, y, n );
				if (code == 0) break;

				color_t color = TerminalPickColor( x, y, n );
				terminal_printf(2+n*2, 23, L"[color=%d]%lc", color, (wchar_t)code);

				n += 1;
			}
			while (true);

			if (n == 0)
			{
				terminal_printf(2, 23, "Empty cell");
			}
		}

        TerminalRefresh( );

		int key = terminal_read();

		if (key == TK_CLOSE || key == TK_ESCAPE)
		{
			break;
		}
	}
}
