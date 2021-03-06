/*
 * ExtendedSmoothScroll.cpp
 *
 *  Created on: Dec 3, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

const int fps = 40;
const int speed_cap = 25;
const int map_size = 64;
const int tile_size = 32;

template <typename T> int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

void TestExtendedSmoothScroll()
{
	std::srand(std::time(nullptr));

    TerminalSet( "window.title='Omni: extended output / smooth scroll'" );
    TerminalSet( "input.filter={keyboard+}" ); // Enable key-release events.
    TerminalComposition( TK_ON );

	// Load resources
    TerminalSet( "U+E000: ../Media/Tiles.png, size=32x32, alignment=top-left" );

	int screen_width = TerminalState( TK_WIDTH )* TerminalState( TK_CELL_WIDTH );
	int screen_height = TerminalState( TK_HEIGHT )* TerminalState( TK_CELL_HEIGHT );
	int hspeed = 0, vspeed = 0;
	int hoffset = 0, voffset = 0;

	std::vector<int> map(map_size*map_size, 0);
	for (int i=0; i<map_size*map_size/10; i++)
	{
		int x = std::rand()%map_size;
		int y = std::rand()%map_size;
		map[y*map_size+x] = std::rand()%8;
	}

	for (bool proceed=true; proceed;)
	{
		hoffset -= hspeed;
		voffset -= vspeed;

        TerminalClear( );

		int tx = hoffset%tile_size, ty = voffset%tile_size;
		int ix = (hoffset-tx)/tile_size, iy = (voffset-ty)/tile_size;
		int jx = ix < 0? (-ix)%map_size: map_size-(ix%map_size);
		int jy = iy < 0? (-iy)%map_size: map_size-(iy%map_size);
		int hc = std::ceil((screen_width+tile_size-tx)/(float)tile_size);
		int vc = std::ceil((screen_height+tile_size-ty)/(float)tile_size);

        TerminalPrintF( 2, 1, "speed: %d, %d", hspeed, vspeed );
        TerminalPrintF( 2, 2, "offset: %d/%d, %d/%d", ix, jx, iy, jy );

		for (int y=0; y<=vc; y++)
		{
			for (int x=0; x<=hc; x++)
			{
				int mx = (jx+x)%map_size;
				int my = (jy+y)%map_size;
				int c = map[my*map_size+mx];
                TerminalPutExt( 0, 0, ( x - 1 ) * tile_size + tx, ( y - 1 ) * tile_size + ty, 0xE000 + c, nullptr );
			}
		}

        TerminalRefresh( );

		while (proceed && TerminalHasInput( ))
		{
			int key = TerminalRead( );
			if (key == TK_CLOSE || key == TK_ESCAPE)
			{
				proceed = false;
			}
		}

		if ( TerminalState( TK_LEFT ))
		{
			if (hspeed > -speed_cap) hspeed -= 1;
		}
		else if ( TerminalState( TK_RIGHT ))
		{
			if (hspeed < speed_cap) hspeed += 1;
		}
		else
		{
			hspeed -= sgn(hspeed);
		}

		if ( TerminalState( TK_UP ))
		{
			if (vspeed > -speed_cap) vspeed -= 1;
		}
		else if ( TerminalState( TK_DOWN ))
		{
			if (vspeed < speed_cap) vspeed += 1;
		}
		else
		{
			vspeed -= sgn(vspeed);
		}

        TerminalDelay( 1000 / fps );
	}

    TerminalSet( "U+E000: none" );
    TerminalComposition( TK_OFF );
}
