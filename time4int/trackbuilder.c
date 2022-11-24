#include <stdint.h>
#include <pic32mx.h> 
#include <math.h>
#include "mipslab.h"

void skybox()
	{
		int y,x;
		uint8_t mountain_bit[9] = {0x1c, 0x02, 0x01, 0x0d, 0x01, 0x0d, 0x01, 0x02, 0x1c};
		bit_decision(20, 4, 1, screen);
		bit_decision(117, 3, 1, screen);
		bit_decision(60, 5, 1, screen);
		bit_decision(1, 2, 1, screen);
		bit_decision(45, 4, 1, screen);
		bit_decision(90, 1, 1, screen);
		bit_decision(33, 1, 1, screen);
		bit_decision(80, 0, 1, screen);
		bit_decision(105, 5, 1, screen);
		bit_decision(125, 0, 1, screen);
		bit_decision(123, 6, 1, screen);
		bit_decision(14, 1, 1, screen);
		bit_decision(51, 1, 1, screen);
		bit_decision(98, 0, 1, screen);
		bit_decision(69, 1, 1, screen);
		bit_decision(75, 4, 1, screen);
		bit_decision(85, 3, 1, screen);

		draw(20,2, 9, 5, mountain_bit);
		draw(91,0, 9, 5, mountain_bit);
		
		bit_decision(91, 5, 1, screen);
		bit_decision(91, 6, 1, screen);
		bit_decision(99, 5, 1, screen);
		bit_decision(99, 6, 1, screen);
        	
	  	for (x = 0; x < 51; x++) bit_decision(x, 7, 1, screen);
		for (x = 77; x < 128; x++) bit_decision(x, 7, 1, screen);
	}

float distance = 0.0f;
int distanceCount = 0;

void renderBackground()
	{
		if (((getbtns() >> 2) & 0x1) == 0x1)
		  distance += 1.0f;

		if (distance == 160.0f) {
			distance = 0;
			distanceCount++;

		}
		int y, x;

		
		for (y = 0; y < 24; y++)
		{
			for (x = 19; x < 109; x++)
			{
				float perspective = (float) y / 24;
				float screenMid = 0.5f;
				float roadWidth = 0.2f + perspective*0.5f;

				roadWidth *= 0.5f;

				int leftDirt = (screenMid-roadWidth)*128;
				int rightDirt = (screenMid+roadWidth)*128;
				int border = 24*roadWidth;

				int row = y + 8;

				int sideColor;

				if (x >= leftDirt && x < leftDirt+border) {
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + distance) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

				if (x >= leftDirt+border && x < rightDirt-border) bit_decision(x, row, 1, screen);

				if (x >= rightDirt-border && x < rightDirt) {
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + distance) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

			}
		}
	}




