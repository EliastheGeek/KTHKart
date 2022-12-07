#include <stdint.h>  
#include <pic32mx.h> 
#include <math.h>
#include "mipslab.h" 
#include "charstructs.h"
#include "gamestates.h"
#include "menu.h"


extern struct Kart bowser;
extern struct Kart mario;

struct Kart choose_character(void) {
    display_string(0, "Choose character");
    display_update(0, 15, 0, 17);
    draw(39, 12, 20, 20, mario_logo, 0);
    draw(69, 12, 20, 20, bowser_logo, 0);
    display_screen(screen);
    screen_clear(0, screen);
    struct Kart character;


    
}
