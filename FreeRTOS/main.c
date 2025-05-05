/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/semphr.h"
#include "FreeRTOS/Source/include/task.h"
#include "FreeRTOS/Source/include/queue.h"

#include </usr/local/Cellar/avr-gcc@9/9.3.0_2/avr/include/avr/io.h>

#include "FreeRTOS/Source/include/extras/serial.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define sbi(x,y) x |= _BV(y) //set bit
#define cbi(x,y) x &= ~(_BV(y)) //clear bit
#define ibi(x,y) x ^= _BV(y) //flip bit

#define my_TASK_PRIORITY   (tskIDLE_PRIORITY)

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vTask1(void* pvParameters);
static void vTask2(void* pvParameters);
//static void vTask3(void* pvParameters);

/**************************************************************************//**
 * \fn int main(void)
 *
 * \brief Main function.
 *
 * \return
 ******************************************************************************/


int main(void)
{
    xTaskHandle handle1;
    xTaskHandle handle2;
    // xTaskHandle handle3;
    xTaskCreate( vTask1, (signed char*)"task01", configMINIMAL_STACK_SIZE, NULL, my_TASK_PRIORITY + 0, &handle1);
    xTaskCreate( vTask2, (signed char*)"task02", configMINIMAL_STACK_SIZE, NULL, my_TASK_PRIORITY + 1, &handle2);
    //xTaskCreate( vTask3, (signed char*)"task03", configMINIMAL_STACK_SIZE, NULL, my_TASK_PRIORITY + 3, &handle3);
    
    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static vApplicationIdleHook(void)
 *
 * \brief
 ******************************************************************************/

void vApplicationIdleHook(void)
{

}

/******************************************************************************
 * Private function definitions.
 ******************************************************************************/

/**************************************************************************//**
 * \fn static void vBlinkLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/

static void vTask1(void* pvParameters)
{
    //(void) pvParameters;
  
    while (1)
    {   
    }

    vTaskDelete( NULL);
}

static void vTask2(void* pvParameters)
{ 
    DDRB=32;
    while (1)
    {
        PORTB=32;
    }

    vTaskDelete( NULL);
}

static void vTask3(void* pvParameters)
{
    for(;;)
    {
        //...
    }

    vTaskDelete( NULL);
}
// avr-gcc -mmcu=atmega328p main.o FreeRTOS/Source/tasks.o FreeRTOS/Source/croutine.o FreeRTOS/Source/list.o FreeRTOS/Source/queue.o FreeRTOS/Source/timers.o -o main
// avr-gcc -mmcu=atmega328p -c port.c
