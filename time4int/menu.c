#include <stdint.h>  
#include <pic32mx.h> 
#include <math.h>
#include "mipslab.h" 
#include "charstructs.h"
#include "gamestates.h"
#include "menu.h"


extern struct Kart bowser;
extern struct Kart mario;
int left_right = 0;

struct Kart* choose_character(void) {
    display_string(0, "Choose character");
    display_update(0, 15, 0, 17);
    //screen_clear(0, screen);
    if (left_right == 0){
        draw(39, 12, 20, 20, mario_logo, 1);
        draw(69, 12, 20, 20, bowser_logo,0);
        display_screen(screen);
        screen_clear(0, screen);
    }
    else if (left_right == 1){
        draw(39, 12, 20, 20, mario_logo, 0);
        draw(69, 12, 20, 20, bowser_logo, 1);
        display_screen(screen);
        screen_clear(0, screen);
        
    }
    if (((getbtns() & 0x1) == 0x1)| (((getbtns() >> 1) & 0x1) == 0x1)){
        left_right = (left_right + 1 )% 2;
        delay(100);
    }
    
    if (((getbtns() >> 2) & 0x1) == 0x1) {
        gamestate = 2;
        delay(1000);
        screen_clear(0, screen);

        if (left_right == 0)
            return &mario;
        else
            return &bowser;
    }
}


