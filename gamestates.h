#include<stdint.h>

void title_screen(void);
void menu(void);
void game(void);
void high_score(void);
void end_screen(void);

extern int gamestate;
extern int mytime;
extern int lapcount;
extern int timeArray[3];