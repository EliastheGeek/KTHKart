#include <stdint.h>
#include <pic32mx.h> 
#include <math.h>
#include "charstructs.h"
#include "mipslab.h"
#include "gamestates.h"

typedef struct Vector {
	float curve;
	float distance;
} Vector;

float distance = 0.0f;
float speed = 0.0f;
int lapbit = 1;
int lapcount = 1;
float curvature = 0.0f;
float trackcurvation = 0.0f;
Vector trackParts[14];
extern struct Kart *pCharacter;

void oneTimebuild()
	{
		int y,x;

		trackParts[0] = (Vector) {0.0f, 10.0f};
		trackParts[1] = (Vector) {0.0f, 100.0f};
		trackParts[2] = (Vector) {0.5f, 80.0f};
		trackParts[3] = (Vector) {0.0f, 150.0f};
		trackParts[4] = (Vector) {1.0f, 50.0f};
		trackParts[5] = (Vector) {-1.0f, 30.0f};
		trackParts[6] = (Vector) {0.0f, 120.0f};
		trackParts[7] = (Vector) {1.0f, 15.0f};
		trackParts[8] = (Vector) {0.0f, 60.0f};
		trackParts[9] = (Vector) {-0.6f, 50.0f};
		trackParts[10] = (Vector) {0.2f, 80.0f};
		trackParts[11] = (Vector) {1.0f, 30.0f};
		trackParts[12] = (Vector) {0.0f, 100.0f};
		trackParts[13] = (Vector) {-0.7f, 80.0f};

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

		draw(20,2, 9, 5, mountain_bit, 0);
		draw(91,0, 9, 5, mountain_bit, 0);
		
		bit_decision(91, 5, 1, screen);
		bit_decision(91, 6, 1, screen);
		bit_decision(99, 5, 1, screen);
		bit_decision(99, 6, 1, screen);
        	
	  	for (x = 0; x < 128; x++) bit_decision(x, 7, 1, screen);
	}

void renderBackground()
	{
		if (((getbtns() >> 2) & 0x1) == 0x1) {
			if ((*pCharacter).x < 19.0f || (*pCharacter).x+15.0f > 108) {
				speed += 0.025f;
			} else {
				speed += 0.05f;
			}
		} else {
			if ((*pCharacter).x < 19.0f || (*pCharacter).x+15.0f > 108) {
				speed -= 0.04f;
			} else {
				speed -= 0.02f;;
			}
		}
		

		if (speed < 0.0f) speed = 0.0f;
		if (speed > 1.0f) speed = 1.0f;

		(*pCharacter).x -= curvature*speed*7.0f;
		
		if ((*pCharacter).x < 19.0f || (*pCharacter).x+15.0f > 108) {
			speed *= 0.90f;
		}

		distance += 2.2f*speed;

		int selectedSection = 0;
		float sectionCheck = 0;

		if (distance > 100) {
			distance = 0;
			selectedSection = 0;
			sectionCheck = 0;
			timeArray[lapcount-1] = mytime;
			mytime = 0x0000;
			lapcount++;
		}

		while (selectedSection < 14 && sectionCheck <= distance) {
			sectionCheck += trackParts[selectedSection].distance;
			selectedSection++;
		}

		if (selectedSection-1 == 0){
			lapbit = 0;
		}
		else 
			lapbit = 1;

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

				if (x >= leftDirt+border && x < rightDirt-border) bit_decision(x, row, lapbit, screen);

				if (x >= rightDirt-border && x < rightDirt) {
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + ((int)distance%26)) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

			}
		}
	}




