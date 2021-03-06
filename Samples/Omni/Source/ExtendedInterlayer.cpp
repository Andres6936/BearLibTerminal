/*
 * ExtendedInterlayer.cpp
 *
 *  Created on: Nov 28, 2013
 *      Author: cfyz
 */

#include "Common.hpp"
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>

const float pi = 3.141592654f;
const int duration = 1;
const int fps = 25;
const int radius = 2;
const int base_layer = 0;
const int animation_layer = 1;
const int map_width = 16;
const int map_height = 8;

int player_x = 1;
int player_y = 1;
int foe_x = 0;
int foe_y = 0;
int foe_hp = 0;

void AnimateDamage(int x, int y, int damage)
{
	std::ostringstream ss;
	ss << damage;
	std::string s = ss.str();

	int n_steps = duration * fps;
	float angle_delta = 2.0f * pi / n_steps;

    TerminalLayer( animation_layer );
	for (int i=0; i<n_steps; i++)
	{
		if ( TerminalHasInput( )) break;
        TerminalClearArea( 0, 0, TerminalState( TK_WIDTH ), TerminalState( TK_HEIGHT ));
		float dx = std::sin(i*angle_delta) * radius * TerminalState( TK_CELL_WIDTH ) + i*2;
		float dy = -2.0f * radius * TerminalState( TK_CELL_WIDTH ) / n_steps * i - TerminalState( TK_CELL_HEIGHT )/2;
        TerminalColor( ColorFromARGB( 255 / n_steps * ( n_steps - i ), 255, 64, 0 ));
        TerminalPrintF( x, y, "[offset=%dx%d]%s", ( int ) dx, ( int ) dy, s.c_str( ));
        TerminalRefresh( );
        TerminalDelay( 1000 / fps );
	}
    TerminalColor( "white" );
}

std::vector<int> PrepareMap()
{
	std::vector<int> result(map_width*map_height, 0);
	for (int x=0; x<map_width; x++)
	{
		result[x] = result[(map_height-1)*map_width+x] = L'─';
	}
	for (int y=0; y<map_height; y++)
	{
		result[y*map_width] = result[(y+1)*map_width-1] = L'│';
	}
	result[0] = L'┌';
	result[map_width-1] = L'┐';
	result[(map_height-1)*map_width] = L'└';
	result[map_height*map_width-1] = L'┘';

	return result;
}

void PlaceFoe()
{
	do
	{
		foe_x = 1+rand()%(map_width-2);
		foe_y = 1+rand()%(map_height-2);
		if (foe_x != player_x && foe_y != player_y) break;
	}
	while (true);

	foe_hp = 25;
}

void DrawMap(int x, int y, std::vector<int>& map)
{
    TerminalLayer( base_layer );
	for (int j=0; j<map_height; j++)
	{
		for (int i=0; i<map_width; i++)
		{
			int v = map[j*map_width+i];
			if (i == player_x && j == player_y)
			{
                TerminalColor( "orange" );
                TerminalPut( x + i, y + j, '@' );
			}
			else if (i == foe_x && j == foe_y && foe_hp > 0)
			{
                TerminalColor( "white" );
                TerminalPut( x + i, y + j, 'g' );
			}
			else if (v == 0 || v == 1)
			{
                TerminalColor( v ? "red" : "gray" );
                TerminalPut( x + i, y + j, 0x2219 );
			}
			else
			{
                TerminalColor( "white" );
                TerminalPut( x + i, y + j, v );
			}
		}
	}
}

void TestExtendedInterlayer()
{
	// Setup
    TerminalSet( "window.title='Omni: extended output / interlayer animation'" );
    TerminalComposition( TK_ON );

	int map_left = TerminalState( TK_WIDTH )/2 - map_width/2;
	int map_top = TerminalState( TK_HEIGHT )/2 - map_height/2;

	std::srand(std::time(nullptr));
	auto map = PrepareMap();
	PlaceFoe();

	auto Attack = [&]
	{
		int damage = 1+std::rand()%10;
		foe_hp -= damage;
		int x = foe_x, y = foe_y;
		if (foe_hp <= 0)
		{
			map[foe_y*map_width+foe_x] = 1;
			PlaceFoe();
            TerminalClear( );
			DrawMap(map_left, map_top, map);
		}
		AnimateDamage(map_left+x, map_top+y, -damage);
	};

	auto Step = [&](int dx, int dy)
	{
		if (player_x+dx == foe_x && player_y+dy == foe_y)
		{
			Attack();
		}
		else if (map[(player_y+dy)*map_width+player_x+dx] <= 1)
		{
			player_x += dx;
			player_y += dy;
		}
	};

	for (bool proceed=true; proceed;)
	{
        TerminalClear( );
		DrawMap(map_left, map_top, map);
        TerminalRefresh( );

		do
		{
			int key = TerminalRead( );
			if (key == TK_CLOSE || key == TK_ESCAPE)
			{
				proceed = false;
			}
			else if (key == TK_LEFT)
			{
				Step(-1, 0);
			}
			else if (key == TK_UP)
			{
				Step(0, -1);
			}
			else if (key == TK_RIGHT)
			{
				Step(1, 0);
			}
			else if (key == TK_DOWN)
			{
				Step(0, 1);
			}
		}
		while (proceed && TerminalHasInput( ));
	}

	// Clean up
    TerminalComposition( TK_OFF );
    TerminalClear( );
    TerminalLayer( 0 );
}
