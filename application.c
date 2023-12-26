#include "application.h"

typedef enum {
    STATE_INITIAL,
    STATE_WAITING_FOR_OPERAND,
    STATE_WAITING_FOR_OPERATOR,
    STATE_END,
} CalculatorState;

#define MAX_BUFFER 100
uint8 val = ZERO_INIT;
char infix[MAX_BUFFER];
char postfix[MAX_BUFFER];
float result;
uint8 arr[11];
uint8 start_flag = 0, flag = 0, pos = 1, res_counter = 0, equal_flag = 0;
uint8 op[2] = "\0";
uint8 operators[8] = {'/', 'E', '*', '-', '+', '=', 'D', 'C'};
uint32 num_1 = 0;
CalculatorState calcState = STATE_INITIAL;
float previousResult = 0;  // Store the result of the previous calculation

int main() {
    Std_ReturnType ret = E_NOT_OK;
    application_intialize();

    while (1) {
        ret = keypad_get_value(&pad1, &val);
        if (val == 'A' && start_flag == 0) {           
            ret = calculation_start(&val);
        } else if (val == 'A' && start_flag == 1) {
            val = '#';
            ret = lcd_4bit_send_command(&my_lcd, _LCD_CLEAR);
            memset(infix, '\0', MAX_BUFFER);
            memset(postfix, '\0', MAX_BUFFER);
            res_counter = 0;
            pos = 1;
            equal_flag = 0;
            calcState = STATE_INITIAL;
            previousResult = 0;  // Reset previous result
        } else {/*Nothing*/}

        for (int i = 0; i < 8; i++) {
            if (val == operators[i]) {
                flag = 1;
            } else {/*Nothing*/}
        }
        if(flag == 1 && calcState == STATE_END){
            calcState = STATE_WAITING_FOR_OPERAND;
            lcd_4bit_send_command(&my_lcd,_LCD_CLEAR);
            memset(infix, '\0', MAX_BUFFER);
            memset(postfix, '\0', MAX_BUFFER);
            res_counter = 0;
            for(uint8 i = 0; i<strlen(arr); i++){
                infix[i] = arr[i];
                lcd_4bit_send_char_data(&my_lcd,infix[i]);
                res_counter++;
            }         
            pos = strlen(arr)+1;
            memset(arr , '\0',11);
            equal_flag = 0;
        }
        

        if (flag != 1 && start_flag == 1 && val != '#') {
            if (equal_flag == 1 || calcState == STATE_INITIAL) {
                ret = lcd_4bit_send_command(&my_lcd, _LCD_CLEAR);
                memset(infix, '\0', MAX_BUFFER);
                memset(postfix, '\0', MAX_BUFFER);
                res_counter = 0;
                pos = 1;
                equal_flag = 0;
                calcState = STATE_WAITING_FOR_OPERATOR;
            }

            infix[res_counter] = val;
            ret = lcd_4bit_send_char_data_pos(&my_lcd, 1, pos, val);
            res_counter++;
            pos++;
        } else if (flag == 1 && start_flag == 1) {
            switch (val) {
                case ('/'):
                case ('*'):
                case ('-'):
                case ('+'):
                    op[0] = val;
                    infix[res_counter] = val;
                    res_counter++;
                    break;
                case ('='):
                    op[0] = '=';
                    equal_flag = 1;
                    infix[res_counter] = '\0';
                    calcState = STATE_END;
                    break;
                default:;
            }

            ret = lcd_4bit_send_char_data_pos(&my_lcd, 1, pos++, op[0]);

            if (op[0] == '=' && calcState == STATE_END) {
                infixToPostfix(infix, postfix);
                evaluatePostfix(postfix, &result);

                // Use previousResult in calculations
                sprintf(arr, "%.5f", result);
                ret = lcd_4bit_send_string_pos(&my_lcd, 4, 20 - strlen(arr), arr);
            }

        }

        flag = 0;
        val = '#';
    }

    return (EXIT_SUCCESS);
}

void application_intialize(void) {
    Std_ReturnType ret = E_NOT_OK;
    ecu_layer_intialize();
}


Std_ReturnType calculation_start(uint8 *value){
    Std_ReturnType ret = E_NOT_OK;
    *value = '#';
    ret = lcd_4bit_send_string_pos(&my_lcd, 1, 1, (uint8 *)"BASEM");
    __delay_ms(100);
    for (int i = 0; i < 6; i++) {
        ret = lcd_4bit_send_char_data(&my_lcd, '.');
        __delay_ms(50);
    }   
    ret = lcd_4bit_send_command(&my_lcd, _LCD_CLEAR);
    calcState = STATE_INITIAL;
    start_flag++;
    return ret;
}
