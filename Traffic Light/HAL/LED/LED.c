/******************************************************************************/
#ifndef LED_H
#include "LED.h"
#endif
/******************************************************************************/
typedef enum{
        TLS_RED = 0,
        TLS_YELLOW,
        TLS_GREEN
}TLS_t;
/******************************************************************************/
static void LED_On(const LED_t LED_ID);
static void LED_Off(const LED_t LED_ID);
/******************************************************************************/
void LED_Init(void){
     GPIO_SetPinDirection(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_PIN_DIRECTION_ID);
     GPIO_SetPinDirection(LED_YELLOW_PORT_ID, LED_YELLOW_PIN_ID, LED_PIN_DIRECTION_ID);
     GPIO_SetPinDirection(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_PIN_DIRECTION_ID);
}
/******************************************************************************/
static void LED_On(const LED_t LED_ID){
       switch(LED_ID){
              case LED_RED:
                   GPIO_SetPinValue(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_STATE_ON);
                   break;
              case LED_YELLOW:
                   GPIO_SetPinValue(LED_YELLOW_PORT_ID, LED_YELLOW_PIN_ID, LED_STATE_ON);
                   break;
              case LED_GREEN:
                   GPIO_SetPinValue(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_STATE_ON);
                   break;
              default:
                   /* Error: Undefined LED */
                   break;
       }
}
/******************************************************************************/
static void LED_Off(const LED_t LED_ID){
       switch(LED_ID){
              case LED_RED:
                   GPIO_SetPinValue(LED_RED_PORT_ID, LED_RED_PIN_ID, LED_STATE_OFF);
                   break;
              case LED_YELLOW:
                   GPIO_SetPinValue(LED_YELLOW_PORT_ID, LED_YELLOW_PIN_ID, LED_STATE_OFF);
                   break;
              case LED_GREEN:
                   GPIO_SetPinValue(LED_GREEN_PORT_ID, LED_GREEN_PIN_ID, LED_STATE_OFF);
                   break;
              default:
                   /* Error: Undefined LED */
                   break;
       }
}
/******************************************************************************/
void LED_Update(void){
     static TLS_t TLS_Mode = TLS_RED;
     switch(TLS_Mode){
            case TLS_RED:
                 LED_On(LED_RED);
                 LED_Off(LED_YELLOW);
                 LED_Off(LED_GREEN);
                 TLS_Mode = TLS_YELLOW;
                 break;
            case TLS_YELLOW:
                 LED_Off(LED_RED);
                 LED_On(LED_YELLOW);
                 LED_Off(LED_GREEN);
                 TLS_Mode = TLS_GREEN;
                 break;
            case TLS_GREEN:
                 LED_Off(LED_RED);
                 LED_Off(LED_YELLOW);
                 LED_On(LED_GREEN);
                 TLS_Mode = TLS_RED;
                 break;
            default:
                 /* Error: Undefined TLS_Mode */
                 break;
     }
}
/******************************************************************************/