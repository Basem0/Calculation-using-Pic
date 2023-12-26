/* 
 * File:   application.h
 * Author: Ahmed Basem
 * LinkedIn : https://www.linkedin.com/in/ahmed-basem-988529272/
 * Created on 25 december 2023, 02:23
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"

/* Section: Macro Declarations */

/* Section: Macro Functions Declarations */

/* Section: Data Type Declarations */
extern chr_lcd_4bit_t my_lcd;
extern keypad_t pad1;
/* Section: Function Declarations */
void application_intialize(void);
Std_ReturnType calculation_start(uint8 *value);

#endif	/* APPLICATION_H */

