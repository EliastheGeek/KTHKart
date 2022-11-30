#include <stdint.h>
#include <pic32mx.h> 
#include <math.h>
#include "mipslab.h"

typedef struct Vector {
	float curve;
	float distance;
} Vector;

float distance = 0.0f;
float speed = 0.0f;
float curvature = 0.0f;
Vector trackParts[13];

void oneTimebuild()
	{
		int y,x;

		trackParts[0] = (Vector) {0.0f, 10.0f};
		trackParts[1] = (Vector) {0.0f, 10.0f};
		trackParts[2] = (Vector) {0.5f, 200.0f};
		trackParts[3] = (Vector) {0.0f, 30.0f};
		trackParts[4] = (Vector) {1.0f, 20.0f};
		trackParts[5] = (Vector) {-1.0f, 10.0f};
		trackParts[6] = (Vector) {0.0f, 20.0f};
		trackParts[7] = (Vector) {1.0f, 15.0f};
		trackParts[8] = (Vector) {0.0f, 40.0f};
		trackParts[9] = (Vector) {-1.0f, 10.0f};
		trackParts[10] = (Vector) {0.2f, 20.0f};
		trackParts[11] = (Vector) {1.0f, 15.0f};
		trackParts[12] = (Vector) {0.0f, 500.0f};

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
        	
	  	for (x = 0; x < 128; x++) bit_decision(x, 7, 1, screen);
	}

void renderBackground()
	{
		if (((getbtns() >> 2) & 0x1) == 0x1)
		  	speed += 0.05f;
		else 
			speed -= 0.02f;
		
		if (speed < 0.0f) speed = 0.0f;
		if (speed > 1.0f) speed = 1.0f;

		distance += 2.0f*speed;

		int selectedSection = 0;
		float sectionCheck = 0;

		while (selectedSection < 14 && sectionCheck <= distance) {
			sectionCheck += trackParts[selectedSection].distance;
			selectedSection++;
		}

		float targetCurvature = trackParts[selectedSection-1].curve;

		float targetCuvatureD = (targetCurvature-curvature) * 0.1f;
		curvature += targetCuvatureD;

		int y, x, xco, width, sideColor;

		if (curvature > 0) {
			xco = 19;
			width = 128;
		} else if (curvature < 0) {
			xco = 0;
			width = 109;
		} else {
			xco = 19;
			width = 109;
		}
		
		for (y = 0; y < 24; y++)
		{
			float perspective = (float) y / 24;
			float screenMid = 0.5f + curvature*(1.0f - perspective)*(1.0f - perspective)*(1.0f - perspective);
			float roadWidth = 0.2f + perspective*0.5f;
			roadWidth *= 0.5f;

			int row = y + 8;

			int leftDirt = (screenMid-roadWidth)*128;
			int rightDirt = (screenMid+roadWidth)*128;
			int border = 24*roadWidth;

			for (x = xco; x < width; x++)
			{

				if (x >= leftDirt && x < leftDirt+border) {
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + ((int)distance%26)) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

				if (x >= leftDirt+border && x < rightDirt-border) bit_decision(x, row, 1, screen);

				if (x >= rightDirt-border && x < rightDirt) {
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + ((int)distance%26)) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

			}
		}
	}




