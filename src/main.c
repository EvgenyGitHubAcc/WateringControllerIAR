#include "main.h"

volatile uint32_t SysTickDelayMsec = 0;

void SysTick_Handler(void)
{
    --SysTickDelayMsec;
}

int main(void)
{
    clockInit();                                                //Инициализируем контроллер
    portInit();                                                 //Инициализация портов

//    uint8_t user_char[8]; //Сюда будем записывать пользовательский символ
    lcd_init();                                                 //Инициализируем дисплей
//    user_char[0]=0b01110;                                       //А вот тут
//    user_char[1]=0b10001;                                       // рисуем
//    user_char[2]=0b10001;                                       // наш символ
//    user_char[3]=0b10001;                                       //
//    user_char[4]=0b10001;                                       // Это типа рыба <img draggable="false" class="emoji" alt="🙂" src="https://s.w.org/images/core/emoji/11.2.0/svg/1f642.svg">
//    user_char[5]=0b01010;
//    user_char[6]=0b10001;
//    user_char[7]=0b10001;
//    lcd_set_user_char(0, user_char);                            // Наша рыба это символ номер ноль
    lcd_out("This is fish");                                    //Выводим надпись в нулевую строку
    lcd_set_xy(0,1);                                            //переводим курсор в первую строку
    lcd_send(0,DATA);                                           //Выводим символ номер ноль
    lcd_set_state(LCD_ENABLE, CURSOR_ENABLE, BLINK);            //Включаем курсор и мигалку


    while(1)
    {
        delayMs(1000);
        GPIOC->BSRR = GPIO_BSRR_BR13;
        delayMs(1000);
        GPIOC->BSRR = GPIO_BSRR_BS13;
    }
    return 0;
}



/*
OSC - 8 MHz
PLLSRC - 8 MHz
SYSCLK - 16 MHz

PLL - 2
AHB - 1/16
*/
int clockInit()
{
    RCC->CR |= RCC_CR_HSEON;                                    //Запускаем генератор HSE
    for(volatile int StartUpCounter = 0; ; ++StartUpCounter)    //Ждем успешного запуска или окончания тайм-аута
    {
        if(RCC->CR & RCC_CR_HSERDY)                             //Если успешно запустилось, то выходим из цикла
        {
            break;
        }
        if(StartUpCounter > 4096)                               //Если не запустилось, то отключаем все, что включили и возвращаем ошибку
        {
            RCC->CR &= ~RCC_CR_HSEON;                           //Останавливаем HSE
            return 1;
        }
    }
    RCC->CFGR &= ~(RCC_CFGR_PLLMULL_0 |
                   RCC_CFGR_PLLMULL_1 |
                   RCC_CFGR_PLLMULL_2 |
                   RCC_CFGR_PLLMULL_3);                         //PLL множитель равен 2
    RCC->CFGR |= RCC_CFGR_PLLSRC;                               //Тактирование PLL от HSE
    RCC->CR |= RCC_CR_PLLON;                                    //Запускаем PLL
    for(volatile int StartUpCounter = 0; ; ++StartUpCounter)    //Ждем успешного запуска или окончания тайм-аута
    {
        if(RCC->CR & RCC_CR_PLLRDY)                             //Если успешно запустилось, то выходим из цикла
        {
            break;
        }
        if(StartUpCounter > 4096)                               //Если по каким-то причинам не запустился PLL, то все отключаеми возвращаем ошибку
        {
            RCC->CR &= ~RCC_CR_HSEON;                           //Останавливаем HSE
            RCC->CR &= ~RCC_CR_PLLON;                           //Останавливаем PLL
            return 2;
        }
    }
    FLASH->ACR |= FLASH_ACR_LATENCY;                            //Устанавливаем 0 циклов ожидания для Flash, частота ядра 16 МГц
    RCC->CFGR |= RCC_CFGR_PPRE2;                                //Делитель шины APB2 отключен (оставляем 0 по умолчанию)
    RCC->CFGR |= RCC_CFGR_HPRE_3 |
            RCC_CFGR_HPRE_1 |
            RCC_CFGR_HPRE_0;                                    //Делитель AHB 16
    RCC->CFGR |= RCC_CFGR_SW_1;                                 //Переключаемся на работу от PLL
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);      //Ждем, пока переключимся на PLL
    RCC->CR &= ~RCC_CR_HSION;                                   //Отключаем внутренний RC-генератор для экономии энергии
    SystemCoreClockUpdate();                                    //Применить изменения генератора
    SysTick_Config(SystemCoreClock/1000);                       //Инициализация прерывания таймера(1 мс)
    return 0;                                                   //Возвращаем 0, если все прошло успешно
}

void portInit()
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;                         //Включаем тактирование порта GPIOB
    GPIOB->CRL = 0;                                             //Обнуление параметров порта GPIOB
    GPIOB->CRH = 0;
    GPIOB->BSRR = 0;

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;                         //Включаем тактирование порта GPIOC
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |=  GPIO_CRH_MODE13;
}

void delayMs(uint16_t msec)
{
    SysTickDelayMsec = msec;
    while (SysTickDelayMsec);
}
