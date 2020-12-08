#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include "stm32f1xx.h"

/////should be defined by user /////
#define LCD_PORT GPIOB
#define LCD_CD 9
#define LCD_EN 8
#define LCD_DB4 7
#define LCD_DB5 6
#define LCD_DB6 5
#define LCD_DB7 4
///////////////////////////////////

enum dat_or_comm{
    COMMAND,
    DATA
};

enum lcd_state{
    LCD_DISABLE,
    LCD_ENABLE
};

enum cursor_state{
    CURSOR_DISABLE,
    CURSOR_ENABLE
};

enum cursor_mode{
    NO_BLINK,
    BLINK
};

#define LCD_EN_BS (1 << LCD_EN)
#define LCD_CD_BS (1 << LCD_CD)
#define LCD_DB4_BS (1 << LCD_DB4)
#define LCD_DB5_BS (1 << LCD_DB5)
#define LCD_DB6_BS (1 << LCD_DB6)
#define LCD_DB7_BS (1 << LCD_DB7)

#define LCD_EN_BC (1 << (LCD_EN+16))
#define LCD_CD_BC (1 << (LCD_CD+16))
#define LCD_DB4_BC (1 << (LCD_DB4+16))
#define LCD_DB5_BC (1 << (LCD_DB5+16))
#define LCD_DB6_BC (1 << (LCD_DB6+16))
#define LCD_DB7_BC (1 << (LCD_DB7+16))

#if LCD_EN > 7
#define LCD_EN_H  (1 << (LCD_EN-8) * 4)
#define C_LCD_EN_H (7 << ((LCD_EN-8) * 4 + 1))
#else
#define LCD_EN_L (1 << LCD_EN * 4)
#define C_LCD_EN_L (7 << (LCD_EN  * 4 + 1))
#endif

#if LCD_CD > 7
#define LCD_CD_H  (1 << (LCD_CD-8) * 4)
#define C_LCD_CD_H  (7 << ((LCD_CD-8) * 4 + 1))
#else
#define LCD_CD_L (1 << LCD_CD * 4)
#define C_LCD_CD_L (7 << (LCD_CD * 4 + 1))
#endif

#if LCD_DB4 > 7
#define DB4_H  (1 << (LCD_DB4-8) * 4)
#define C_DB4_H  (7 << ((LCD_DB4-8) * 4 + 1))
#else
#define DB4_L (1 << LCD_DB4 * 4)
#define C_DB4_L  (7 << (LCD_DB4 * 4 + 1))
#endif

#if LCD_DB5 > 7
#define DB5_H  (1 << (LCD_DB5-8) * 4)
#define C_DB5_H  (7 << ((LCD_DB5-8) * 4 + 1))
#else
#define DB5_L (1 << LCD_DB5 * 4)
#define C_DB5_L  (7 << (LCD_DB5 * 4 + 1))
#endif

#if LCD_DB6 > 7
#define DB6_H  (1 << (LCD_DB6-8) * 4)
#define C_DB6_H  (7 << ((LCD_DB6-8) * 4 + 1))
#else
#define DB6_L (1<< LCD_DB6 * 4)
#define C_DB6_L  (7 << (LCD_DB6 * 4 + 1))
#endif

#if LCD_DB7 > 7
#define DB7_H  (1 << (LCD_DB7-8) * 4)
#define C_DB7_H  (7 << ((LCD_DB7-8) * 4 + 1))
#else
#define DB7_L (1 << LCD_DB7 * 4)
#define C_DB7_L  (7 << (LCD_DB7 * 4 + 1))
#endif


#ifndef DB4_H
#define DB4_H 0
#endif

#ifndef DB5_H
#define DB5_H 0
#endif

#ifndef DB6_H
#define DB6_H 0
#endif

#ifndef DB7_H
#define DB7_H 0
#endif

#ifndef DB4_L
#define DB4_L 0
#endif

#ifndef DB5_L
#define DB5_L 0
#endif

#ifndef DB6_L
#define DB6_L 0
#endif

#ifndef DB7_L
#define DB7_L 0
#endif

#ifndef LCD_CD_L
#define LCD_CD_L 0
#endif

#ifndef LCD_CD_H
#define LCD_CD_H 0
#endif

#ifndef LCD_EN_L
#define LCD_EN_L 0
#endif

#ifndef LCD_EN_H
#define LCD_EN_H 0
#endif

////////////////////////

#ifndef C_DB4_H
#define C_DB4_H 0
#endif

#ifndef C_DB5_H
#define C_DB5_H 0
#endif

#ifndef C_DB6_H
#define C_DB6_H 0
#endif

#ifndef C_DB7_H
#define C_DB7_H 0
#endif

#ifndef C_DB4_L
#define C_DB4_L 0
#endif

#ifndef C_DB5_L
#define C_DB5_L 0
#endif

#ifndef C_DB6_L
#define C_DB6_L 0
#endif

#ifndef C_DB7_L
#define C_DB7_L 0
#endif


#ifndef C_LCD_CD_L
#define C_LCD_CD_L 0
#endif

#ifndef C_LCD_CD_H
#define C_LCD_CD_H 0
#endif

#ifndef C_LCD_EN_L
#define C_LCD_EN_L 0
#endif

#ifndef C_LCD_EN_H
#define C_LCD_EN_H 0
#endif

#define LCD_PORT_CRH_S (DB4_H | DB5_H | DB6_H | DB7_H | LCD_EN_H | LCD_CD_H)
#define LCD_PORT_CRL_S (DB4_L | DB5_L | DB6_L | DB7_L | LCD_EN_L | LCD_CD_L)

#define LCD_PORT_CRH_C (C_DB4_H | C_DB5_H | C_DB6_H | C_DB7_H | C_LCD_EN_H | C_LCD_CD_H)
#define LCD_PORT_CRL_C (C_DB4_L | C_DB5_L | C_DB6_L | C_DB7_L | C_LCD_EN_L | C_LCD_CD_L)



void lcd_init();
void lcd_send(unsigned char byte, enum dat_or_comm dc);
void lcd_set_4bit_mode(void);
void lcd_set_state(enum lcd_state state, enum cursor_state cur_state, enum cursor_mode cur_mode);
void lcd_clear(void);
void lcd_out(char* txt);
void lcd_set_xy(unsigned char x, unsigned char y);
void lcd_set_user_char(unsigned char char_num, unsigned char* char_data);
void lcd_delay(void);


#endif //LCD_DRIVER_H
