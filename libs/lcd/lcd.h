#ifndef LCD_H
#define LCD_H

#include "main.h"

void initializeLCD();
void configurePort();
void clearLCD();
void setCursorPosition(unsigned char, unsigned char);
void sendByte(char, unsigned char);
void pulseLCD();
void printStr(char*);

#endif //LCD_DRIVER_H
