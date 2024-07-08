/* 
 * File:   ecu_lcd.h
 * Author: Mohamed Tarek
 *
 * Created on July 5, 2024, 6:53 AM
 */

#ifndef ECU_LCD_H
#define	ECU_LCD_H
/*Section : includes */
#include "ecu_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*Section : Macro Declarations */
#define CLEAR_LCD 0x01
#define RETURN_HOME 0x02
#define LCD_INCREAMENT_SHIFT_OFF 0x06
#define LCD_INCREAMENT_SHIFT_On 0x07
#define LCD_DECREAMENT_SHIFT_OFF 0x04
#define LCD_DECREAMENT_SHIFT_On 0x05
#define LCD_DISPLAY_OFF 0X08
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_OFF 0x0E
#define LCD_DISPLAY_ON_CURSOR_ON_BLINKING_ON 0x0F
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINKING_OFF 0x0C
#define LCD_DISPLAY_ON_CURSOR_OFF_BLINKING_ON 0x0D
#define DISPLAY_SHIFT_OFF 0x10
#define DISPLAY_SHIFT_ON_RIGHT 0x1C
#define DISPLAY_SHIFT_ON_LEFT 0x18
#define LCD_8BIT_1_LINE 0x30
#define LCD_8BIT_2_LINES 0x38
#define LCD_4BIT_1_LINE 0x20
#define LCD_4BIT_2_LINES 0x28
#define _LCD_CGRAM_START 0x40
#define _LCD_DDRAM_START 0x80


#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4

/*Section : Macro Functions Declarations */



/*Section : Data Type Declarations */
typedef struct{
    pin_config_t rs;
    pin_config_t enable;
    pin_config_t data_pins[8];
}lcd_8bits_t;

typedef struct{
    pin_config_t rs;
    pin_config_t enable;
    pin_config_t data_pins[4];
}lcd_4bits_t;
/*Section : Function Declarartions */
std_ReturnType lcd_8bit_initialize(const lcd_8bits_t *lcd);
std_ReturnType lcd_8bit_send_command(const lcd_8bits_t *lcd,uint8 command);
std_ReturnType lcd_8bit_send_char(const lcd_8bits_t *lcd,uint8 _char);
std_ReturnType lcd_8bit_send_char_pos(const lcd_8bits_t *lcd,uint8 Row,uint8 coloumns,uint8 _char);
std_ReturnType lcd_8bit_send_string(const lcd_8bits_t *lcd,uint8 *str);
std_ReturnType lcd_8bit_send_string_pos(const lcd_8bits_t *lcd,uint8 Row,uint8 coloumns,uint8 *str);
std_ReturnType lcd_8bit_custom_character(const lcd_8bits_t *lcd,uint8 Row,uint8 coloumns,uint8 chr[],uint8 mempos);


std_ReturnType lcd_4bit_initialize(const lcd_4bits_t *lcd);
std_ReturnType lcd_4bit_send_command(const lcd_4bits_t *lcd,uint8 command);
std_ReturnType lcd_4bit_send_char(const lcd_4bits_t *lcd,uint8 _char);
std_ReturnType lcd_4bit_send_char_pos(const lcd_4bits_t *lcd,uint8 Row,uint8 coloumn,uint8 _char);
std_ReturnType lcd_4bit_send_string(const lcd_4bits_t *lcd,uint8 *str);
std_ReturnType lcd_4bit_send_string_pos(const lcd_4bits_t *lcd,uint8 Row,uint8 coloumn,uint8 *str);
std_ReturnType lcd_4bit_custom_character(const lcd_4bits_t *lcd,uint8 Row,uint8 coloumns,uint8 chr[],uint8 mempos);



std_ReturnType convert_uint8_to_string(uint8 value,const uint8 *str);
std_ReturnType convert_uint16_to_string(uint16 value,uint8 *str);
std_ReturnType convert_uint32_to_string(uint32 value,uint8 *str);

#endif	/* ECU_LCD_H */

