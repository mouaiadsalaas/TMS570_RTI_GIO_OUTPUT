#include "sys_common.h"

#include "rti.h"
#include "het.h"
#include "gio.h"

#include "stdio.h"
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
bool tick2=false;

int main(void)
{

    rtiInit();
    gioInit();

    gioSetDirection(hetPORT1, 0xFFFFFFFF);

    rtiEnableNotification(rtiNOTIFICATION_COMPARE0);

    _enable_IRQ();
    rtiStartCounter(rtiCOUNTER_BLOCK0);

    rtiEnableNotification(rtiNOTIFICATION_COMPARE1);

    _enable_IRQ();
    rtiStartCounter(rtiCOUNTER_BLOCK0);


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


}


void rtiNotification(uint32 notification)
{
    if(notification ==rtiNOTIFICATION_COMPARE0){
        tick=true;
        printf("%d \n",1);
    }

    if(notification ==rtiNOTIFICATION_COMPARE1){
        tick2=true;
        printf("%d \n",2);

    }
}
