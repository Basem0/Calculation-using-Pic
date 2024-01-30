/* 
 * File:   ecu_keypad.h
 * Author: Ahmed Basem
 * LinkedIn : https://www.linkedin.com/in/ahmed-basem-988529272/
 * Created on 25 december 2023, 02:23
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* ----------------- Includes -----------------*/
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ----------------- Macro Declarations -----------------*/
#define ECU_KEYPAD_ROWS     4

#if Type == Small_Calc
#define ECU_KEYPAD_COLUMNS  4
#endif

#if Type == Big_Clac
#define ECU_KEYPAD_COLUMNS  6
#endif

/* ----------------- Macro Functions Declarations -----------------*/

/* ----------------- Data Type Declarations -----------------*/
typedef struct{
    pin_config_t keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
}keypad_t;

/* ----------------- Software Interfaces Declarations -----------------*/
Std_ReturnType keypad_initialize(const keypad_t *_keypad_obj);
Std_ReturnType keypad_get_value(const keypad_t *_keypad_obj, uint8 *value);

#endif	/* ECU_KEYPAD_H */

