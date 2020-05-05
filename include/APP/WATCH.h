#ifndef WATCH_H
#define WATCH_H


/**
 * @brief This API is used to initialize watch elements.
 *
 */
void WATCH_Initialization(void);


/**
 * @brief This API is the runnable of the Watch that calls other functions to fully control the system.
 * It's called every 50 ms. If periodicity is to be changed. Change WATCH_SEC_MULTIPLIER to a proper value accordingly.
 *
 * WATCH_SEC_MULTIPLIER * periodicity = 1 second
 *
 */
void WATCH_Main_Runnable(void);

#endif
