/*
 * utils.c
 *
 *  Created on: Oct 1, 2014
 *      Author: superman
 */

#include <stdio.h>
#include "globals.h"

char getKeyChar()
{
	return getchar();
}

void processKeyPress(char input)
{
	if(input == '4')
	{
		tank_direction = LEFT;
		move_tank();
	}
	else if(input == '6')
	{
		tank_direction = RIGHT;
		move_tank();
	}
	else if(input == '8')
	{
		move_aliens();
	}
	else if(input == '2')
	{
		char str[2];
		char c;
		int index = 0;
		while(1)
		{
			c = getchar();
			if(c == 13)
			{
				xil_printf("ENTERED\n");
				break;
			}
			else if(c <= '9' && c >= '0') // Check if number
			{
				str[index] = c;
				str[index+1] = 0;
				index++;
			}
			if(index >= 2)
				break;
		}
		int number = 0;

		int len = 0;
		int i;
		for(i = 0; i < 2; i++)
		{
			if(str[i] != 0)
				len++;
		}

		for(i = 0; i < len; i++)
		{
			number = number * 10 + (str[i] - '0');
		}

		xil_printf("%d\n", number);

		if(number < 55)
		{
			alien_life[number] = 0;
			drawAliens();
		}
	}
	else if(input == '5')
	{
		shootTankBullet();
	}
	else if(input == '3')
	{
		shootAlienBullet();
	}
	else if(input == '9')
	{
		moveBullets();
	}
	else if(input == '7')
	{
		char c;

		int num = 0;
		while(1)
		{
			c = getchar();
			if(c <= '3' && c >= '0')
			{
				num = c - '0';
				break;
			}
		}

		erode_bunkers(num);
	}
}
