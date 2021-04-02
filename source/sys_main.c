/** @file sys_main.c
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/*
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "rti.h"
#include "het.h"
#include "gio.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/
typedef struct timer{
    uint16_t set;
    uint16_t count;
    bool state;
    uint16_t counter;
}Timers;

Timers led_1;      //Timer to Wait for all Sensors
Timers led_2;      //Timer to turn led on when sensor detected
Timers led_3;       //Timer to turn led on when system INIt is done

uint16 led_1_counter;      //Timer to Wait for all Sensors

bool tick=false;
/* USER CODE BEGIN (2) */
/* USER CODE END */
uint16 dizi[3];
int main(void)
{
/* USER CODE BEGIN (3) */

    /* Initialize RTI driver */
    rtiInit();
    gioInit();

    /* Set high end timer GIO port hetPort pin direction to all output */
    gioSetDirection(hetPORT1, 0xFFFFFFFF);

    /* Enable RTI Compare 0 interrupt notification */
    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);

    /* Enable IRQ - Clear I flag in CPS register */
    /* Note: This is usually done by the OS or in an svc dispatcher */
    _enable_IRQ();
    /* Start RTI Counter Block 0 */
    rtiStartCounter(rtiCOUNTER_BLOCK0);

    /* Run forever */
    while(1){
        if(gioGetBit(gioPORTA, 4)){
            led_1.set = 5;
        }else if (gioGetBit(gioPORTA, 6)) {
            led_2.set = 2;
        }else if (gioGetBit(gioPORTA, 7)) {
            led_3.set = 2;

        }

        if(tick){
            tick=false;




            if(led_1.set != 0){
                if(++led_1.count >= led_1.set){

                    led_1.state=!led_1.state;
                    led_1.count = 0;

                    if(led_1.state){
                        gioSetBit(hetPORT1, 8, 1);
                        led_1.counter++;
                    }else{
                        gioSetBit(hetPORT1, 8, 0);
                        if(led_1.counter>=2){
                            led_1.set = 0;
                            led_1.counter = 0;
                        }
                    }
                }
            }


            if(led_2.set != 0){
                if(++led_2.count >= led_2.set){

                    led_2.state=!led_2.state;
                    led_2.count = 0;

                    if(led_2.state){
                        gioSetBit(hetPORT1, 8, 1);
                        led_2.counter++;
                    }else{
                        gioSetBit(hetPORT1, 8, 0);
                        if(led_2.counter>=2){
                            led_2.set = 0;
                            led_2.counter = 0;
                        }
                    }
                }
            }

            if(led_3.set != 0){
                if(++led_3.count >= led_3.set){

                    led_3.state=!led_3.state;
                    led_3.count = 0;

                    if(led_3.state){
                        gioSetBit(hetPORT1, 8, 1);
                        led_3.counter++;
                    }else{
                        gioSetBit(hetPORT1, 8, 0);
                        if(led_3.counter>=4){
                            led_3.set = 0;
                            led_3.counter = 0;
                        }
                    }
                }
            }

        }

    }

/* USER CODE END */

}


/* USER CODE BEGIN (4) */
/* Note-You need to remove rtiNotification from notification.c to avoid redefinition */
void rtiNotification(uint32 notification)
{
    tick=true;

}
/* USER CODE END */
