/******************************************************************************/
#ifndef LED_H
#include "LED.h"
#endif
/******************************************************************************/
#ifndef TIME_H
#include "TIME.h"
#endif
/******************************************************************************/
#ifndef SSD_H
#include "SSD.h"
#endif
/******************************************************************************/
#ifndef CO_SCH_H
#include "CO_SCH.h"
#endif
/******************************************************************************/
void main() {
     CO_SCH_Init(); /* Tick = 5 ms */
     LED_Init();
     SSD_Init();
     CO_SCH_Add_Task(LED_Update, 0, 200);    /* Every 200 Tick = 1000 ms */
     CO_SCH_Add_Task(TIME_Update, 200, 200); /* Every 200 Tick = 1000 ms*/
     CO_SCH_Add_Task(SSD_Update, 0, 1);      /* Every 1 Tick = 5 ms */
     CO_SCH_Start();
     while(1){
              CO_SCH_Dispatch_Tasks();
     }
}
/******************************************************************************/