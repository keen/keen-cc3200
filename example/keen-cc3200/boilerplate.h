/*
 * bp.h
 *
 *  Created on: Mar 26, 2015
 *      Author: Doug Cox
 */

#ifndef BP_H_
#define BP_H_

#define DATE                18    /* Current Date */
#define MONTH               6     /* Month 1-12 */
#define YEAR                2014  /* Current year */
#define HOUR                12    /* Time - hours */
#define MINUTE              32    /* Time - minutes */
#define SECOND              0     /* Time - seconds */

// Simplelink includes
#include "simplelink.h"

//Driverlib includes
#include "hw_types.h"
#include "hw_ints.h"
#include "rom.h"
#include "rom_map.h"
#include "interrupt.h"
#include "prcm.h"
#include "utils.h"

//Common interface includes
#include "pinmux.h"
#include "gpio_if.h"
#include "common.h"
#ifndef NOTERM
#include "uart_if.h"
#endif

// Application specific status/error codes
typedef enum{
    // Choosing -0x7D0 to avoid overlap w/ host-driver's error codes
    LAN_CONNECTION_FAILED = -0x7D0,
    INTERNET_CONNECTION_FAILED = LAN_CONNECTION_FAILED - 1,
    DEVICE_NOT_IN_STATION_MODE = INTERNET_CONNECTION_FAILED - 1,

    STATUS_CODE_MAX = -0xBB8
}e_AppStatusCodes;

typedef struct
{
   /* time */
   unsigned long tm_sec;
   unsigned long tm_min;
   unsigned long tm_hour;
   /* date */
   unsigned long tm_day;
   unsigned long tm_mon;
   unsigned long tm_year;
   unsigned long tm_week_day; //not required
   unsigned long tm_year_day; //not required
   unsigned long reserved[3];
}SlDateTime;

int set_time();
long WlanConnect();
void BoardInit(void);
long InitializeAppVariables();
long ConfigureSimpleLinkToDefaultState();

#endif /* BP_H_ */
