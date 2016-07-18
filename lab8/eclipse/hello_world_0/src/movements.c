#include <stdio.h>
#include <stdlib.h>
#include "bitmask.h"
#include "globals.h"

direction alien_direction;
position tank_bullet;
short tank_bullet_exists;
alien_bullet bullets[4];
int right_alien_block_edge, left_alien_block_edge;

position tank;
block alien_block;
UFO ufo;
int alien_sound_counter=4;

void move_tank()
{
	draw_tank(0x00000000);

	if (tank_direction == LEFT) // Move left
	{
		tank.x -= 4;
		if (tank.x < 10)
			tank.x = 10;
	}
	else // move right
	{
		tank.x += 4;
		if (tank.x > 598)
			tank.x = 598;
	}

	draw_tank(0x0000FF00);
}

void moveBullets()
{
	// Clear bullets
	drawBullets(0x00000000);

	// Update positions
	if (tank_bullet_exists)
	{
		tank_bullet.y -= 4;
		if (tank_bullet.y <= 25)
		{
			tank_bullet_exists = 0;
			tank_bullet.y = 6969;
		}
	}

	int bullet_index;
	for (bullet_index = 0; bullet_index < 4; bullet_index++)
	{
		if(bullets[bullet_index].exists)
		{
			bullets[bullet_index].state++;
			if (bullets[bullet_index].state > 3)
				bullets[bullet_index].state = 0;

			bullets[bullet_index].pos.y += 4;
			if (bullets[bullet_index].pos.y >= 465)
			{
				bullets[bullet_index].exists = 0;
				bullets[bullet_index].pos.x= 6969;
				bullets[bullet_index].pos.y= 6969;
			}
		}
	}

	// Update alien bullet symbol

	// redraw bullets
	checkCollisions();
	drawBullets(0x00FF0000);
}

void check_lowest_row()
{
	int lowest_row=4;
		int row, column;
		for (row=4; row>=0;row--)
		{
			int found =0;
			for (column = 0; column < 10; column++)
			{

				if(alien_life[column + (row*11)] == 1 )
				{
					found =1;
					break;
				}

			}
			if (!found)
			{
				lowest_row--;
			}
		}

		int end_game_y;
		switch(lowest_row)
		{
		case 0:
			end_game_y=386;
			break;
		case 1:
			end_game_y =362 ;
			break;
		case 2:
			end_game_y= 338;
			break;
		case 3:
			end_game_y=314;
			break;

		default:
			end_game_y= 290;
			break;
		}

		//gameover
		if (alien_block.y >= end_game_y)
		{
			play_game_over();
		}
}

void move_aliens()
{
	playSound(alien_sound_counter);
	alien_sound_counter++;
	if (alien_sound_counter==8)
	{
		alien_sound_counter=4;
	}

	clearAliens();

	alien_block.state = !alien_block.state;

	if (alien_direction == RIGHT)
	{
		alien_block.x += 8;
		if (alien_block.x >= right_alien_block_edge) // 280
		{
			alien_block.x -= 8;
			alien_block.y += ALIEN_HEIGHT + ALIEN_Y_GAP;
			alien_direction = LEFT;

		}
	}
	else
	{
		alien_block.x -= 8;
		if (alien_block.x <= left_alien_block_edge)
		{
			alien_block.x += 8;
			alien_block.y += ALIEN_HEIGHT + ALIEN_Y_GAP;
			alien_direction = RIGHT;
		}

	}
	if(alien_block.y > 230)
	{
		draw_bunker(0x0000FF00);
	}

	drawAliens();
	check_lowest_row();
}

void moveUFO()
{
	if (ufo.exists)
	{
		//playSound(3);
		draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH, ALIEN_HEIGHT, 0x0000000);
		if (ufo.ufo_direction == RIGHT)
		{
			ufo.pos.x += 2;

			if (ufo.pos.x > 610)
			{
				draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH, ALIEN_HEIGHT, 0x0000000);
				ufo.pos.x = 6969;
				ufo.pos.y = 6969;
				ufo.exists = 0;
				ufo.ufo_direction = LEFT;
			}
			else
			{
				draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH,
						ALIEN_HEIGHT, 0xFF00000);
			}
		}
		else
		{
			ufo.pos.x -= 2;

			if (ufo.pos.x < 15)
			{
				draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH,
						ALIEN_HEIGHT, 0x0000000);
				ufo.pos.x = 6969;
				ufo.pos.y = 6969;
				ufo.exists = 0;
				ufo.ufo_direction = RIGHT;
			}
			else
			{
				draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH,
						ALIEN_HEIGHT, 0xFF00000);
			}
		}
	}
}
