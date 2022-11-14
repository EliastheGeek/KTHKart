#include <stdint.h>
#include <pic32mx.h> 
#include "mipslab.h" 

float fWorldX = 1000.0f;
float fWorldY = 1000.0f;
float fWorldA = 0.1f;
float fNear = 0.005f;
float fFar = 0.03f;
float fFoVHalf = 3.14159f / 4.0f;

int nMapSize = 1024;