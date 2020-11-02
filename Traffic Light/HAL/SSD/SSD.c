/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
typedef enum{
        SSD_TENS = 0,
        SSD_UNITS
}SSD_t;
/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID);
static void SSD_Off(const SSD_t SSD_ID);
static void SSD_Update_Symbol(const u8_t SYMBOL);
static void SSD_Refesh(void);
void SSD_Set_Symbol(const u8_t SYMBOL);
/******************************************************************************/
static u8_t SSD_Symbol = 0;
/******************************************************************************/
void SSD_Init(void){
                    /* Init Data Lines */
     GPIO_SetPinDirection(SSD_A_PORT_ID, SSD_A_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_B_PORT_ID, SSD_B_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_C_PORT_ID, SSD_C_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_D_PORT_ID, SSD_D_PIN_ID, SSD_DIRECTION_ID);
                    /* Init Control Lines */
     GPIO_SetPinDirection(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_DIRECTION_ID);
     GPIO_SetPinDirection(SSD_UNITS_PORT_ID, SSD_UNITS_PIN_ID, SSD_DIRECTION_ID);
}
/******************************************************************************/
static void SSD_On(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_TENS:
                   GPIO_SetPinValue(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_STATE_ON);
                   break;
              case SSD_UNITS:
                   GPIO_SetPinValue(SSD_UNITS_PORT_ID, SSD_UNITS_PIN_ID, SSD_STATE_ON);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
} 
/******************************************************************************/
static void SSD_Off(const SSD_t SSD_ID){
       switch(SSD_ID){
              case SSD_TENS:
                   GPIO_SetPinValue(SSD_TENS_PORT_ID, SSD_TENS_PIN_ID, SSD_STATE_OFF);
                   break;
              case SSD_UNITS:
                   GPIO_SetPinValue(SSD_UNITS_PORT_ID, SSD_UNITS_PIN_ID, SSD_STATE_OFF);
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}
/******************************************************************************/
static void SSD_Update_Symbol(const u8_t SYMBOL){
       GPIO_SetPinValue(SSD_A_PORT_ID, SSD_A_PIN_ID, GET_BIT(SYMBOL, 0));
       GPIO_SetPinValue(SSD_B_PORT_ID, SSD_B_PIN_ID, GET_BIT(SYMBOL, 1));
       GPIO_SetPinValue(SSD_C_PORT_ID, SSD_C_PIN_ID, GET_BIT(SYMBOL, 2));
       GPIO_SetPinValue(SSD_D_PORT_ID, SSD_D_PIN_ID, GET_BIT(SYMBOL, 3));
}
/******************************************************************************/
static void SSD_Refesh(void){
       static SSD_t SSD_Id = SSD_TENS;
       SSD_Off(SSD_TENS);
       SSD_Off(SSD_UNITS);
       switch(SSD_Id){
              case SSD_TENS:
                   SSD_Update_Symbol(SSD_Symbol / 10);
                   SSD_On(SSD_TENS);
                   SSD_Id = SSD_UNITS;
                   break;
              case SSD_UNITS:
                   SSD_Update_Symbol(SSD_Symbol % 10);
                   SSD_On(SSD_UNITS);
                   SSD_Id = SSD_TENS;
                   break;
              default:
                   /* Error: Undefined SSD */
                   break;
       }
}
/******************************************************************************/
void SSD_Update(void){
     SSD_Refesh();
}
/******************************************************************************/
void SSD_Set_Symbol(const u8_t SYMBOL){
     SSD_Symbol = SYMBOL;
}
/******************************************************************************/