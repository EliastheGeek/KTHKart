/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include <math.h>
#include "mipslab.h" /* Declatations for these labs */
#include "charstructs.h"

int mytime = 0x0000;
int prime = 1234567;
int timeoutcount = 0;
char textstring[] = "";
extern struct Kart bowser;
extern struct Kart mario;

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0) & 0x800)
  {
    mytime += 2;
    IFSCLR(0) = 0x800;
  }

  if (IFS(0) & 0x100)
  {
  
    if ((getbtns() & 0x1) == 0x1) {
			mario.x += 2.5f;
      draw((int)mario.x, 16, 15, 17, bowser.rightturn);

	  } else if (((getbtns() >> 1) & 0x1) == 0x1) {
		  mario.x -= 2.5f;
      draw((int)mario.x, 16, 15, 17, bowser.leftturn);
    } else
      draw((int)mario.x, 16, 15, 17, bowser.normal);

    display_screen(screen);
    screen_clear(screen);

    renderBackground(); 
    
    if (timeoutcount == 10)
    {
      time2string(textstring, mytime);
      tick(&mytime);
      timeoutcount = 0;  
    }
    timeoutcount++;
    display_string(2, textstring);
    display_update(2, 0, 15, 5);   

    IFSCLR(0) = 0x100;
  }

  return;
}

/* Lab-specific initialization goes here */
void labinit(void)
{
  volatile int *trise = (volatile int *)0xbf886100;
  *trise &= ~0xff;

  TRISD |= 0xfe0;

  T2CON = 0x70;
  PR2 = (80000000 / 256) / 10;
  TMR2 = 0;
  T2CONSET = 0x8000;

  IEC(0) = 0x900;
  IPC(2) = 0x4000004;
  enable_interrupt();
  oneTimebuild();

  return;
}
/* This function is called repetitively from the main program */
void labwork(void)
{
}