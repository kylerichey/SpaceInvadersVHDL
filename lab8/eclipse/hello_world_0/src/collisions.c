#include <stdio.h>
#include <stdlib.h>
#include "bitmask.h"
#include "globals.h"

alien_bullet bullets[4];
bunker bunkers[4];
short alien_columns[11];

int left_alien_block_edge, right_alien_block_edge;
int remaining_aliens;
UFO ufo;

void checkCollisions()
{
	checkBunkerAlienBlockCollision();
	checkBunkerAlienBulletCollision();
	checkBunkerTankBulletCollision();
	checkAlienBlockCollision();
	checkTankCollision();
	checkUFOCollision();
}

void checkBunkerAlienBulletCollision()
{
	int alien_bullet_index = 0;
	for(alien_bullet_index = 0; alien_bullet_index < 4; alien_bullet_index++)
	{
		alien_bullet* curr_bullet = &bullets[alien_bullet_index];
		int bunker_index;

		if(curr_bullet->exists)
		{
			if ((curr_bullet->pos.y > 350) && (curr_bullet->pos.y < 386))
			{
				for (bunker_index = 0; bunker_index <= 3; bunker_index++)
				{
					if ((bunkers[bunker_index].exists) && (curr_bullet->pos.x
							> bunkers[bunker_index].pos.x - 5) && (curr_bullet->pos.x
							< (bunkers[bunker_index].pos.x + 45)) && (curr_bullet->pos.y
							> bunkers[bunker_index].pos.y) && (curr_bullet->pos.y
							< (bunkers[bunker_index].pos.y + 36)))
					{

						int blockx = bunkers[bunker_index].pos.x;
						int blocky = bunkers[bunker_index].pos.y;
						int count = 0;

						int block_index;
						for (block_index = 0; block_index < 10; block_index++)
						{

							if (count > 3)
							{
								blockx = bunkers[bunker_index].pos.x;
								blocky += 12;
								count = 0;
							}
							if (block_index == 9)
							{
								blockx+=24;
							}

							if (bunkers[bunker_index].erosion_state[block_index] != 4 &&
									(curr_bullet->pos.x > blockx - 5) && (curr_bullet->pos.x < blockx + 9) &&
									(curr_bullet->pos.y > blocky) && (curr_bullet->pos.y < blocky + 12))
							{
								// clear block (bunker_index, block_index)
								drawBlock(bunker_index, block_index, blockx, blocky, 0x00000000);
								bunkers[bunker_index].erosion_state[block_index]++;

								if (bunkers[bunker_index].erosion_state[block_index] == 4)
									bunkers[bunker_index].num_blocks_remaining--;

								curr_bullet->pos.x = 6969;
								curr_bullet->pos.y = 6969;
								curr_bullet->exists = 0;
								// draw block (bunker_index, block_index)
								drawBlock(bunker_index, block_index, blockx, blocky, 0x0000FF00);

							}

							if (count <= 3)
							{
								blockx += 12;
								count++;
							}
						}

						if(bunkers[bunker_index].num_blocks_remaining == 0)
							bunkers[bunker_index].exists = 0;
					} // end if in bunker
				} // end bunker for loop
			} // end check y pos
		} // end if exists
	} // end alien bullet for loop
}

void checkBunkerTankBulletCollision()
{
	int bunker_index;

	if ((tank_bullet.y > 350) && (tank_bullet.y < 386))
	{
		for (bunker_index = 0; bunker_index <= 3; bunker_index++)
		{
			if ((bunkers[bunker_index].exists) && (tank_bullet.x
					> bunkers[bunker_index].pos.x - 4) && (tank_bullet.x
					< (bunkers[bunker_index].pos.x + 45)) && (tank_bullet.y
					> bunkers[bunker_index].pos.y) && (tank_bullet.y
					< (bunkers[bunker_index].pos.y + 36)))
			{

				int blockx = bunkers[bunker_index].pos.x;
				int blocky = bunkers[bunker_index].pos.y;
				int count = 0;

				int block_index;
				for (block_index = 0; block_index < 10; block_index++)
				{

					if (count > 3)
					{
						blockx = bunkers[bunker_index].pos.x;
						blocky += 12;
						count = 0;
					}
					if (block_index == 9)
					{
						blockx+=24;
					}

					if (bunkers[bunker_index].erosion_state[block_index] != 4 &&
							(tank_bullet.x > blockx - 4) && (tank_bullet.x < blockx + 8) &&
							(tank_bullet.y > blocky) && (tank_bullet.y < blocky + 11))
					{
						// clear block (bunker_index, block_index)
						drawBlock(bunker_index, block_index, blockx, blocky, 0x00000000);
						bunkers[bunker_index].erosion_state[block_index]++;

						if (bunkers[bunker_index].erosion_state[block_index] == 4)
							bunkers[bunker_index].num_blocks_remaining--;

						tank_bullet.x = 6969;
						tank_bullet.y = 6969;
						tank_bullet_exists = 0;
						// draw block (bunker_index, block_index)
						drawBlock(bunker_index, block_index, blockx, blocky, 0x0000FF00);
					}

					if (count <= 3)
					{
						blockx += 12;
						count++;
					}
				}

				if(bunkers[bunker_index].num_blocks_remaining == 0)
					bunkers[bunker_index].exists = 0;
			}
		}
	}
}

void checkBunkerAlienBlockCollision()
{

}

void checkAlienBlockCollision()
{
	int far_right_column = 10;
	int far_left_column = 0;
	int column = 0;
	// Check alien collisions
	// WRONG
	if (((tank_bullet.y > alien_block.y) && tank_bullet.y < (alien_block.y + 121)) &&
			((tank_bullet.x > alien_block.x - 4) && tank_bullet.x < (alien_block.x + 352)))
	{
		int col_left_side = alien_block.x + far_left_column * ALIEN_WIDTH;
		int col_right_side = alien_block.x + 24 + (far_left_column * ALIEN_WIDTH);
		for (column = far_left_column; column <= far_right_column; column++)
		{
			if (tank_bullet.x > col_left_side && tank_bullet.x < col_right_side)
			{
				int row = 0;
				//int row_top = alien_block.y - 7;
				//int row_bot = alien_block.y + 15;
				int alien_block_height = 96;
				int row_top =alien_block.y -7 + alien_block_height ;
				int row_bot=alien_block.y +15 + alien_block_height;
				for (row = 4; row >= 0; row--)
				{
					// If the alien is alive/exists there
					if(alien_life[row*11 + column]==1)
					{
						if (tank_bullet.y > row_top && tank_bullet.y < row_bot)
						{
							//xil_printf("COL: %d ROW: %d ROW_TOP: %d ROW_BOT: %d TANK_X: %d TANK_Y: %d\n", column, row, row_top, row_bot, tank_bullet.x, tank_bullet.y);
							tank_bullet.x = 6969;
							tank_bullet.y = 6969;
							// top row
							if(row == 0){
								updateScore(40);
							}
							//middle rows
							else if(row == 1 || row == 2){
								updateScore(20);
							}
							//bottom row
							else{
								updateScore(10);
							}
							tank_bullet_exists = 0;
							alien_life[row * 11 + column] = 2;
							alien_columns[column]--;

							int new_left_edge = 8;
							int new_right_edge = 280;
							int j;
							int found_left = 0;
							int found_right = 0;
							for(j = 0; j < 11; j++)
							{
								if(alien_columns[j] == 0 && !found_left)
									new_left_edge -= 32;
								else if(alien_columns[j])
									found_left = 1;

								if(alien_columns[10-j] == 0 && !found_right)
									new_right_edge += 32;
								else if(alien_columns[10-j])
									found_right = 1;
							}

							left_alien_block_edge = new_left_edge;
							right_alien_block_edge = new_right_edge;
							//xil_printf("LEFT: %d\nRIGHT: %d\nALIEN_COL: %d\n", left_alien_block_edge, right_alien_block_edge, alien_columns[column]);

							//drawAliens();
							if ( alien_delay_speed >20)
							{
								alien_delay_speed-=2;
							}
							remaining_aliens--;
							//xil_printf("Remaining: %d\n", remaining_aliens);
							draw(col_left_side, row_top + 7 , blankAlienSymbol, ALIEN_WIDTH, ALIEN_HEIGHT, 0x0000000);
							draw(col_left_side, row_top + 7 , alienDeath, ALIEN_WIDTH, ALIEN_HEIGHT, 0xFF00000);
							return;
						}
					}
					row_top -= ALIEN_HEIGHT + ALIEN_Y_GAP;
					row_bot -= ALIEN_HEIGHT + ALIEN_Y_GAP;
				} // end for row
			}
			col_left_side += ALIEN_WIDTH;
			col_right_side += ALIEN_WIDTH;
		} // end for column
	}
}

void checkTankCollision()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		if (bullets[i].exists)
		{
			if (bullets[i].pos.x > (tank.x - 5) && bullets[i].pos.x < (tank.x + 31))
			{
				if (bullets[i].pos.y > (tank.y - 7) && bullets[i].pos.y < (tank.y + 15))
				{
					// destroy tank

					bullets[i].exists = 0;
					bullets[i].pos.x = 6969;
					bullets[i].pos.y = 6969;
					tank_hit = 1;
					playSound(2);

				}
			}
		}
	}
}

void checkUFOCollision()
{
	//Check UFO collisions
	//check if it is exist
	//check if it is n the y range
	//delete bullet and update score
	if (ufo.exists && tank_bullet_exists == 1)
	{
		if (tank_bullet.y <= 44)
		{
			if (tank_bullet.x > (ufo.pos.x - 5) && tank_bullet.x < ufo.pos.x + 31)
			{
				draw(ufo.pos.x, ufo.pos.y, ufoSymbol, ALIEN_WIDTH, ALIEN_HEIGHT, 0x0000000);
				playSound(8);
				int random = rand() % 7 ;

				switch (random)
		{
				case 0:
					//draw(ufo.pos.x, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
					draw(ufo.pos.x + 15, ufo.pos.y, numb_5, 12, 12, 0x00FF0FF);
					draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
					updateScore(50);
					break;
			case 1:
				draw(ufo.pos.x, ufo.pos.y, numb_1, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(100);
				break;
			case 2:
				draw(ufo.pos.x, ufo.pos.y, numb_1, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_5, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(150);
				break;
			case 3:
				draw(ufo.pos.x, ufo.pos.y, numb_2, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(200);
				break;
			case 4:
				draw(ufo.pos.x, ufo.pos.y, numb_2, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_5, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(250);
				 break;
			case 5:
				draw(ufo.pos.x, ufo.pos.y, numb_3, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(300);
				 break;
			case 6:
				draw(ufo.pos.x, ufo.pos.y, numb_3, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_5, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				updateScore(350);
				break;
			default:
				//draw(ufo.pos.x, ufo.pos.y, numb_0, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 15, ufo.pos.y, numb_6, 12, 12, 0x00FF0FF);
				draw(ufo.pos.x + 30, ufo.pos.y, numb_9, 12, 12, 0x00FF0FF);
				updateScore(69);
				break;


	}

				ufo.exists = 0;

				tank_bullet.x = 6969;
				tank_bullet.y = 6969;
				tank_bullet_exists = 0;
				ufoDie = 1;
			}
		}
	}
}
