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
float roadwidth_float;

void oneTimebuild() //track and background creation
	{
		int y,x;
		//All tracksegments in the track with curvature and length
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

		//background starry night
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
        	
			//draws horizon
	  	for (x = 0; x < 128; x++) bit_decision(x, 7, 1, screen);
	}

void renderBackground() // creates and curves the road
	{
		if (((getbtns() >> 2) & 0x1) == 0x1) { //if gas pedal is down
			// 19 och 128 när roadwidth_float är 0.5, 32 och 96 när rw_float är 0.3
			if ((*pCharacter).x < (-64 * (-0.8f +  roadwidth_float)) || (*pCharacter).x+15.0f > (76.8f + 64 * roadwidth_float)) {
				speed += 0.025f; // acceleration on grass
			} else {
				speed += 0.05f; // acceleration on road
			}
		} else {
			if ((*pCharacter).x < (-64 * (-0.8f +  roadwidth_float)) || (*pCharacter).x+15.0f > (76.8f + 64 * roadwidth_float)) {
				speed -= 0.04f; //deceleration on grass
			} else {
				speed -= 0.02f;; //deceleration on road
			}
		}
		
		//speed min and max
		if (speed < 0.0f) speed = 0.0f;
		if (speed > 1.0f) speed = 1.0f;

		(*pCharacter).x -= curvature*speed*7.0f; // player moves automatically out of the road in a curve
		
		if ((*pCharacter).x < (-64 * (-0.8f +  roadwidth_float)) || (*pCharacter).x+15.0f > (76.8f + 64 * roadwidth_float)) {
			speed *= 0.90f;
		}

		distance += 2.9f*speed;//ändrat här, det var 2.2f innan

		int selectedSection = 0;
		float sectionCheck = 0;
		
		if (distance > 955) { //one lap
			distance = 0;
			selectedSection = 0;
			sectionCheck = 0;
			timeArray[lapcount-1] = mytime;
			mytime = 0x0000; 
			lapcount++;
		}

		while (selectedSection < 14 && sectionCheck <= distance) { // next trackpart
			sectionCheck += trackParts[selectedSection].distance;
			selectedSection++;
		}

		if (selectedSection-1 == 0){ //finnish line turns black (new lap)
			lapbit = 0;
		}
		else 
			lapbit = 1;

		float targetCurvature = trackParts[selectedSection-1].curve; //previous curve

		float targetCuvatureD = (targetCurvature-curvature) * 0.1f; // creates smooth transition
		curvature += targetCuvatureD;
		
		
		int y, x, xco, width, sideColor;

		if (curvature > 0) { //optimization so that the for loop doesnt go through redundant screen space
			xco = 19;
			width = 128;
		} else if (curvature < 0) {
			xco = 0;
			width = 109;
		} else {
			xco = 19;
			width = 109;
		}
		
		for (y = 0; y < 24; y++) //create road
		{
			float perspective = (float) y / 24;
			float screenMid = 0.5f + curvature*(1.0f - perspective)*(1.0f - perspective)*(1.0f - perspective); //road curves more farther away
			float roadWidth = 0.2f + perspective*roadwidth_float;// road is thinner at the horizon
			roadWidth *= 0.5f;

			int row = y + 8;
			//coordinates for left and right side of the road
			int leftDirt = (screenMid-roadWidth)*128;
			int rightDirt = (screenMid+roadWidth)*128;
			int border = 24*roadWidth; //thickness of the side lines

			for (x = xco; x < width; x++)
			{

				if (x >= leftDirt && x < leftDirt+border) { //creates sidelines on the left
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + ((int)distance%26)) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen); //draws a pixel
				}

				if (x >= leftDirt+border && x < rightDirt-border) bit_decision(x, row, lapbit, screen);//creates road

				if (x >= rightDirt-border && x < rightDirt) {//sidelines on the right
					sideColor = sinf(40.0f * ((1.0f - perspective)*(1.0f - perspective)) + ((int)distance%26)) > 0.0f ? 1 : 0;
					bit_decision(x, row, sideColor, screen);
				}

			}
		}
	}




