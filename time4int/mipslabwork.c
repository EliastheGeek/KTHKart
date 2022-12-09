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
#include "gamestates.h"

int gamestate = 0;

/* Interrupt Service Routine */
void user_isr(void)
{
  if (IFS(0) & 0x800)
  {
    IFSCLR(0) = 0x800;
  }

  if (IFS(0) & 0x100)
  {

    if(gamestate == 0) {
      title_screen();
    } else if(gamestate == 1) {
      menu();
      
    } else if(gamestate == 2) {
      oneTimebuild();
      game();
    } else if (gamestate == 3) {
      high_score();
    } else if (gamestate == 4) {
      end_screen();
    }

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
  return;
}
/* This function is called repetitively from the main program */
void labwork(void)
{
}