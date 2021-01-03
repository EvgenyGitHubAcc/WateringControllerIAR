#include "lcd.h"


/*
 MODE*_1: выход с максимальной частотой 2 МГц
 CNF: режим push-pull
*/
void configurePort()
{
    GPIOB->CRL |= (GPIO_CRL_MODE4_1 | GPIO_CRL_MODE5_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE7_1);       //Старшие биты
    GPIOB->CRL |= (GPIO_CRL_CNF4 | GPIO_CRL_CNF5 | GPIO_CRL_CNF6 | GPIO_CRL_CNF7);                   //Младшие биты
    GPIOB->CRH |= (GPIO_CRH_MODE8_1 | GPIO_CRH_MODE9_1);
    GPIOB->CRH |= (GPIO_CRH_CNF8 | GPIO_CRH_CNF9);
}

void initializeLCD()
{
    configurePort();
    delayMs(15);                                        //Задержка
    GPIOB->BSRR &= ~GPIO_BSRR_BS9;                      //RS
    GPIOB->BSRR &= ~GPIO_BSRR_BS8;                      //EN
    GPIOB->BSRR |= (GPIO_BSRR_BR7 | GPIO_BSRR_BR6);
    delayMs(15);                                        //Задержка
    pulseLCD();
    //    sendByte(0x28, 0);
    //    sendByte(0x0E, 0);
    //    sendByte(0x06, 0);

}

void pulseLCD()
{
    GPIOB->BSRR &= ~GPIO_BSRR_BS8;
    delayMs(15);
    GPIOB->BSRR |= GPIO_BSRR_BR8;
    delayMs(15);
    GPIOB->BSRR &= ~GPIO_BSRR_BS8;
    delayMs(15);
}
