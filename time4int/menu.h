#include <stdint.h> 
#include <pic32mx.h>
#include <math.h>
#include "mipslab.h" 

struct Kart* choose_character(void);
void choose_difficulty(void);
void display_instructions(void);

extern int menustate;
extern float roadwidth_float;