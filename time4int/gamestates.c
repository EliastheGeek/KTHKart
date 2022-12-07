#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <math.h>
#include "mipslab.h" /* Declatations for these labs */
#include "charstructs.h"
#include "gamestates.h"
#include "menu.h"

int mytime = 0x0000;
int timeoutcount = 0;
char textstring[] = "      ";
int menustate = 0;
extern struct Kart bowser;
extern struct Kart mario;
struct Kart pcharacter;

void title_screen(void) {
    draw(0, 0, 95, 32, logo, 0);
    display_screen(screen);
    if (((getbtns() >> 2) & 0x1) == 0x1) {
        gamestate = 1;
        screen_clear(0, screen);

    }
};

void menu(void) {
    if (menustate == 0) {
        choose_character();
    }
}

void game(void) {
    if ((getbtns() & 0x1) == 0x1) {
			mario.x += 2.5f;
      draw((int)mario.x, 16, 15, 17, bowser.rightturn, 0);

	  } else if (((getbtns() >> 1) & 0x1) == 0x1) {
		  mario.x -= 2.5f;
      draw((int)mario.x, 16, 15, 17, bowser.leftturn, 0);
    } else
      draw((int)mario.x, 16, 15, 17, bowser.normal, 0);

    display_screen(screen);
    screen_clear(128, screen);

    renderBackground(); 
    
    if (timeoutcount == 10)
    {
      time2string(textstring, mytime);
      tick(&mytime);
      timeoutcount = 0;  
    }
    timeoutcount++;
    display_update(2, 0, 15, 5);   
    display_string(2, textstring);
};