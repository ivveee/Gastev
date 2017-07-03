// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _Gastev_H_
#define _Gastev_H_
#include "Arduino.h"
#include "C:\\AWorkspace2\\Gastev\\libraries\\Grove_Serial_MP3_Player-master\\libraries\\Grove_Serial_MP3_Player\\MP3.h"
#include "Button.h"
#include "Relay.h"
#include "C:\\AWorkspace2\\Gastev\\libraries\\TimerOne\\TimerOne.h"

#define DEBUG 1

#ifdef DEBUG
 #define DEBUG_PRINT(x)  Serial.println (x)
 #define DEBUG_PRINT_S(x,y)  Serial.println (x,y)
#else
 #define DEBUG_PRINT(x)
 #define DEBUG_PRINT_S(x,y)
#endif

void waitButton(uint32_t curTime);
//add your includes for the project Gastev here


//end of add your includes here


//add your function definitions for the project Gastev here




//Do not add code below this line
#endif /* _Gastev_H_ */
