#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <math.h>
#include "mipslab.h" /* Declatations for these labs */
#include "charstructs.h"
#include "gamestates.h"
#include "menu.h"
#include <string.h>

int mytime = 0x0000;
int timeArray[3];
int timeoutcount = 0;
char textstring[] = "      ";
int menustate = 0;
float dvdX = 54.0f;
float dvdY = 6.0f;
float xspeed = 1.0f;
float yspeed = 1.0f;
extern struct Kart bowser;
extern struct Kart mario;
extern struct Kart *pCharacter;

char lap_char[] = "LAP";
char* lapcount_char = "1";

void title_screen(void) {
    draw(0, 0, 95, 32, logo, 0);
    display_screen(screen);
    if (((getbtns() >> 2) & 0x1) == 0x1) {
        delay(1000);
        gamestate = 4;
        screen_clear(0, screen);

    }
};

void menu(void) {
    if (menustate == 0) {
        pCharacter = choose_character();
    }
}

void game(void) {
    if ((getbtns() & 0x1) == 0x1) {
			(*pCharacter).x += 2.5f;
      draw((int)(*pCharacter).x, 16, 15, 17, (*pCharacter).rightturn, 0);

	  } else if (((getbtns() >> 1) & 0x1) == 0x1) {
		  (*pCharacter).x -= 2.5f;
      draw((int)(*pCharacter).x, 16, 15, 17, (*pCharacter).leftturn, 0);
    } else
      draw((int)(*pCharacter).x, 16, 15, 17, (*pCharacter).normal, 0);

    display_screen(screen);
    screen_clear(128, screen);

    renderBackground();

    if (lapcount > 3) {
        delay(200);
      	gamestate = 3;
				screen_clear(0, screen);
    }
    
    if (timeoutcount == 10)
    {
      time2string(textstring, mytime);
      tick(&mytime);
      timeoutcount = 0;  
      lapcount_char = itoaconv(lapcount);
    }
    timeoutcount++;
    display_update(2, 0, 15, 5);   
    display_string(2, textstring);
    //För varv: 
    display_update(3, 99, 15, 4);
    display_string(3, lap_char);
    //sprintf(lapcount_char, "%d", lapcount);
    display_update(1, 121, 15, 2);
    display_string(1, lapcount_char);
};

void high_score(void) {
  screen_clear(0, screen);
  display_string(0, "Here are your times");
  display_update(0, 0, 0, 20);

  char textstring1[] = "    ";
  char textstring2[] = "    ";
  char textstring3[] = "    ";

  time2string(textstring1, timeArray[0]);
  time2string(textstring2, timeArray[1]);
  time2string(textstring3, timeArray[2]);

  char lap1[] = "Lap 1: ";
  strcat(lap1, textstring1);

  display_string(1, lap1);
  display_update(1, 0, 8, 13);

  char lap2[] = "Lap 2: ";
  strcat(lap2, textstring2);
  
  display_string(2, lap2);
  display_update(2, 0, 16, 13);

  char lap3[] = "Lap 3: ";
  strcat(lap3, textstring3);

  display_string(3, lap3);
  display_update(3, 0, 24, 13);

  display_screen(screen);

  if (((getbtns() >> 2) & 0x1) == 0x1) {
        gamestate = 4;
        screen_clear(0, screen);

    }
}

void end_screen(void){
  if (dvdY + 14 >= 32) {
    yspeed = -yspeed;
  }

  if (dvdY <= 0) {
    yspeed = -yspeed;
  }

  if (dvdX + 20 >= 128) {
    xspeed = -xspeed;
  }

  if (dvdX <= 0) {
    xspeed = -xspeed;
  }

  dvdY += yspeed;
  dvdX += xspeed;

  draw((int)dvdX, (int)dvdY, 20, 20, dvd, 0);

  display_screen(screen);
  screen_clear(0, screen);

}
