/*
 * CTimer.h
 *
 *  Description  :
 *  Created on   : 05-Mar-2022
 *      Author   : shashiwakale
 *  Organization : 
 */

#ifndef INCLUDE_CTIMER_H_
#define INCLUDE_CTIMER_H_
/******************************************************************************
 * System Includes
 *****************************************************************************/
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <iostream>

/******************************************************************************
 * Local Includes
 *****************************************************************************/

/******************************************************************************
 * Macros
 *****************************************************************************/
#define CLOCKID     CLOCK_REALTIME
#define SIG         SIGRTMIN
/******************************************************************************
 * Global Variables
 *****************************************************************************/
static uint32_t g_stat_u32TimerFrequency;

/**\enum
 * \brief eTimerNumber
 */
typedef enum
{
    TIMER_1,
    TIMER_2,
    TIMER_3,
    TIMER_4,
    TIMER_5,
    TIMER_MAX,
}eTimerNumber;

/**\enum
 * \brief eTimerType
 */
typedef enum
{
    PERIODIC_TIMER,
    NON_PERIODIC_TIMER,
}eTimerType;

/**\enum
 * \brief eTimerStatus
 */
typedef enum
{
    ENABLE_TIMER,
    DISABLE_TIMER,
    PROCESSING_TIMER,
}eTimerStatus;

/**\struct
 * \brief stTimer_t
 */
typedef struct
{
    eTimerNumber m_eTimerNumber;
    eTimerType m_eTimerType;
    eTimerStatus m_eTimerStatus;
    uint32_t m_u32Period;
    uint32_t m_u32PeriodCount;
    void (*m_pvCallback)(void*);
    void* m_pvData;
}stTimer_t;

/**\struct
 * \brief g_astTimer
 */
stTimer_t g_astTimer[] =
{
        {TIMER_1,   NON_PERIODIC_TIMER, DISABLE_TIMER,  0,  0,  NULL,   NULL},
        {TIMER_2,   NON_PERIODIC_TIMER, DISABLE_TIMER,  0,  0,  NULL,   NULL},
        {TIMER_3,   NON_PERIODIC_TIMER, DISABLE_TIMER,  0,  0,  NULL,   NULL},
        {TIMER_4,   NON_PERIODIC_TIMER, DISABLE_TIMER,  0,  0,  NULL,   NULL},
        {TIMER_5,   NON_PERIODIC_TIMER, DISABLE_TIMER,  0,  0,  NULL,   NULL},
};

/******************************************************************************
 * Classes
 *****************************************************************************/
class CTimer
{
public:
    /*
     * Function Name            : CTimer
     * Function Id              : CTIMER_FUNC_01
     * Description              : CTimer constructor
     * Author                   : shashiwakale
     * Date                     : 05-03-2022
     * Global Variable Refereed : m_tmTimerID
     * Global Variable Modified : g_stat_u32TimerFrequency, m_tmTimerID
     * Variable Passed          : p_u32TimerFrequency - Timer frequency in ms
     * Return Value             : -
     */
    CTimer(uint32_t p_u32TimerFrequency = 1):m_u32TimerFrequency(p_u32TimerFrequency)
    {
        struct sigevent l_stSignalEvent;
        struct itimerspec l_stTimerSpec;
        struct sigaction l_stSignalAction;
        g_stat_u32TimerFrequency = p_u32TimerFrequency;

        /* Establish handler for timer signal. */
        l_stSignalAction.sa_flags = SA_SIGINFO;
        l_stSignalAction.sa_handler = this->TimerCallback;
        sigemptyset(&l_stSignalAction.sa_mask);
        if (sigaction(SIG, &l_stSignalAction, NULL) == -1)
        {

        }
        else
        {
            /* Create the timer. */
            l_stSignalEvent.sigev_notify = SIGEV_SIGNAL;
            l_stSignalEvent.sigev_signo = SIG;
            l_stSignalEvent.sigev_value.sival_ptr = &m_tmTimerID;
            if (timer_create(CLOCKID, &l_stSignalEvent, &m_tmTimerID) == -1)
            {
                std::cout<<"[CTimer]:timer_create error\n";
            }
            else
            {
                std::cout<<"[CTimer]:timer ID is "<<std::hex<<(uintmax_t) m_tmTimerID<<std::endl;

                /* Start the timer. */
                l_stTimerSpec.it_value.tv_sec = m_u32TimerFrequency / 1000;
                l_stTimerSpec.it_value.tv_nsec = m_u32TimerFrequency * 1000000;
                l_stTimerSpec.it_interval.tv_sec = l_stTimerSpec.it_value.tv_sec;
                l_stTimerSpec.it_interval.tv_nsec = l_stTimerSpec.it_value.tv_nsec;

                if (timer_settime(m_tmTimerID, 0, &l_stTimerSpec, NULL) == -1)
                {
                    std::cout<<"[CTimer]:timer_settime error\n";
                }
            }
        }
    }

    /*
     * Function Name            : CTimer
     * Function Id              : CTIMER_FUNC_02
     * Description              : CTimer destructor
     * Author                   : shashiwakale
     * Date                     : 05-03-2022
     * Global Variable Refereed : m_tmTimerID
     * Global Variable Modified : -
     * Variable Passed          : -
     * Return Value             : -
     */
    ~CTimer()
    {
        if(-1 == timer_delete(m_tmTimerID))
        {
            std::cout<<"[CTimer]:timer_delete error\n";
        }
    }

    /*
     * Function Name            : StartTimer
     * Function Id              : CTIMER_FUNC_03
     * Description              : Function to start/enable timer
     * Author                   : shashiwakale
     * Date                     : 05-03-2022
     * Global Variable Refereed : g_astTimer
     * Global Variable Modified : -
     * Variable Passed          : p_eTimerNumber - Timer Number
     *                            p_eTimerType - Timer Type
     *                            p_u32Period - Timer period in ms
     *                            p_pvCallback - Callback function i.e. void callback(void*)
     *                            p_pvData - User data pointer
     * Return Value             : -
     */
    void StartTimer(eTimerNumber p_eTimerNumber, eTimerType p_eTimerType, \
            uint32_t p_u32Period, void (*p_pvCallback)(void*), void* p_pvData = NULL)
    {
        g_astTimer[p_eTimerNumber].m_eTimerType = p_eTimerType;
        g_astTimer[p_eTimerNumber].m_u32Period = p_u32Period;
        g_astTimer[p_eTimerNumber].m_u32PeriodCount = 0;
        g_astTimer[p_eTimerNumber].m_pvCallback = p_pvCallback;
        g_astTimer[p_eTimerNumber].m_pvData = p_pvData;
        g_astTimer[p_eTimerNumber].m_eTimerStatus = ENABLE_TIMER;
    }

    /*
     * Function Name            : DisableTimer
     * Function Id              : CTIMER_FUNC_04
     * Description              : Function to disable timer
     * Author                   : shashiwakale
     * Date                     : 05-03-2022
     * Global Variable Refereed : g_astTimer
     * Global Variable Modified : -
     * Variable Passed          : p_eTimerNumber - Timer Number
     * Return Value             : -
     */
    void DisableTimer(eTimerNumber p_eTimerNumber)
    {
        g_astTimer[p_eTimerNumber].m_eTimerStatus = DISABLE_TIMER;
    }

private:
    uint32_t m_u32TimerFrequency;
    timer_t m_tmTimerID;

    /*
     * Function Name            : TimerCallback
     * Function Id              : CTIMER_FUNC_05
     * Description              : Main timer callback
     * Author                   : shashiwakale
     * Date                     : 05-03-2022
     * Global Variable Refereed : g_astTimer
     * Global Variable Modified : g_stat_u32TimerFrequency
     * Variable Passed          : p_nSigNumber - Signal Number
     * Return Value             : 0
     */
    static void TimerCallback(int p_nSigNumber)
    {
        for(uint32_t TimerNumber = 0; TimerNumber < TIMER_MAX; TimerNumber++)
        {
            if(ENABLE_TIMER == g_astTimer[TimerNumber].m_eTimerStatus)
            {
                if(g_astTimer[TimerNumber].m_u32Period <= g_astTimer[TimerNumber].m_u32PeriodCount)
                {
                    g_astTimer[TimerNumber].m_eTimerStatus = PROCESSING_TIMER;

                    g_astTimer[TimerNumber].m_u32PeriodCount = 0;

                    if(NULL != g_astTimer[TimerNumber].m_pvCallback)
                    {
                        g_astTimer[TimerNumber].m_pvCallback(g_astTimer[TimerNumber].m_pvData);
                    }

                    if(NON_PERIODIC_TIMER == g_astTimer[TimerNumber].m_eTimerType)
                    {
                        g_astTimer[TimerNumber].m_eTimerStatus = DISABLE_TIMER;
                    }
                    else
                    {
                        g_astTimer[TimerNumber].m_eTimerStatus = ENABLE_TIMER;
                    }
                }
                else
                {
                    g_astTimer[TimerNumber].m_u32PeriodCount += g_stat_u32TimerFrequency;
                }
            }
        }
    }
};



#endif /* INCLUDE_CTIMER_H_ */
