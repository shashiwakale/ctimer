/*
 * main.cpp
 *
 *  Description  :
 *  Created on   : 05-Mar-2022
 *      Author   : shashiwakale
 *  Organization : 
 */
/******************************************************************************
 * System Includes
 *****************************************************************************/
#include <iostream>
#include <unistd.h>
/******************************************************************************
 * Local Includes
 *****************************************************************************/
#include "CTimer.h"

/******************************************************************************
 * Macros
 *****************************************************************************/

/******************************************************************************
 * Global Variables
 *****************************************************************************/

/******************************************************************************
 * Functions
 *****************************************************************************/
/*
 * Function Name            : Timer1Callback
 * Function Id              : CTIMER_MAIN_01
 * Description              : Timer 1 callback function
 * Author                   : shashiwakale
 * Date                     : 05-03-2022
 * Global Variable Refereed : -
 * Global Variable Modified : -
 * Variable Passed          : p_pvData - Data Pointer
 * Return Value             : -
 */
void Timer1Callback(void *p_pvData)
{
    std::cout<<"Timer 1 Callback, Data is "<<(char*)p_pvData<<std::endl;
}

/*
 * Function Name            : Timer2Callback
 * Function Id              : CTIMER_MAIN_02
 * Description              : Timer 2 callback function
 * Author                   : shashiwakale
 * Date                     : 05-03-2022
 * Global Variable Refereed : -
 * Global Variable Modified : -
 * Variable Passed          : p_pvData - Data Pointer
 * Return Value             : -
 */
void Timer2Callback(void *p_pvData)
{
    std::cout<<"Timer 2 Callback, Data is "<<(char*)p_pvData<<std::endl;
}

/*
 * Function Name            : main
 * Function Id              : CTIMER_MAIN_03
 * Description              : Application entry point
 * Author                   : shashiwakale
 * Date                     : 05-03-2022
 * Global Variable Refereed : -
 * Global Variable Modified : -
 * Variable Passed          : arc - Argument count
 *                            arv - Argument pointer
 * Return Value             : 0
 */
int main(int arc, char** arv)
{
    /*Create CTimer Object*/
    CTimer l_CTimer;

    /*Start timer 1 which will execute Timer1Callback periodically after every 1 second*/
    l_CTimer.StartTimer(TIMER_1, PERIODIC_TIMER, 1000, Timer1Callback, (char*)"Hello CTimer");

    /*Start timer 2 which will execute Timer2Callback non-periodically after 5 seconds*/
    l_CTimer.StartTimer(TIMER_2, NON_PERIODIC_TIMER, 5000, Timer2Callback, (char*)"Hello CTimer");

    /*run infinitely*/
    while(1)
    {
        /*sleep to avoid CPU load*/
        sleep(5);
    }
    return 0;
}
