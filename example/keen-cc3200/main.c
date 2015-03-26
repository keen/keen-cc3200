//*****************************************************************************
//
// Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/ 
// 
// 
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//    Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the   
//    distribution.
//
//    Neither the name of Texas Instruments Incorporated nor the names of
//    its contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************


//*****************************************************************************
//
//! \addtogroup keen
//! @{
//
//*****************************************************************************

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

#include "boilerplate.h"

#include "http_client.h"
#include "keen_client.h"

#define APPLICATION_NAME        "KeenExample"
#define APPLICATION_VERSION     "1.0"

extern unsigned long  g_ulStatus;//SimpleLink Status

//*****************************************************************************
//                 GLOBAL VARIABLES -- Start
//*****************************************************************************

char *api_version = "3.0";
char *project_id = "000000000000000000000000";
char *write_key = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
char *read_key = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
char *master_key = "00000000000000000000000000000000";

//*****************************************************************************
//                 GLOBAL VARIABLES -- End
//*****************************************************************************


//****************************************************************************
//                      LOCAL FUNCTION PROTOTYPES
//****************************************************************************
static long keen();

//*****************************************************************************
//
//! This function demonstrates how certificate can be used with SSL.
//! The procedure includes the following steps:
//! 1) connect to an open AP
//! 2) get the server name via a DNS request
//! 3) define all socket options and point to the CA certificate
//! 4) connect to the server via TCP
//!
//! \param None
//!
//! \return  0 on success else error code
//! \return  LED1 is turned solid in case of success
//!    LED2 is turned solid in case of failure
//!
//*****************************************************************************
static long keen()
{
    long error_code;

    GPIO_IF_LedConfigure(LED1|LED3);

    GPIO_IF_LedOff(MCU_RED_LED_GPIO);
    GPIO_IF_LedOff(MCU_GREEN_LED_GPIO); 

    error_code = InitializeAppVariables();
    ASSERT_ON_ERROR(error_code);

    //
    // Following function configure the device to default state by cleaning
    // the persistent settings stored in NVMEM (viz. connection profiles &
    // policies, power policy etc)
    //
    // Applications may choose to skip this step if the developer is sure
    // that the device is in its default state at start of applicaton
    //
    // Note that all profiles and persistent settings that were done on the
    // device will be lost
    //
    error_code = ConfigureSimpleLinkToDefaultState();
    if(error_code < 0)
    {
      if (DEVICE_NOT_IN_STATION_MODE == error_code)
          UART_PRINT("Failed to configure the device in its default state \n\r");

      return error_code;
    }

    UART_PRINT("Device is configured in default state \n\r");

    CLR_STATUS_BIT_ALL(g_ulStatus);

    ///
    // Assumption is that the device is configured in station mode already
    // and it is in its default state
    //
    error_code = sl_Start(0, 0, 0);
    if (error_code < 0 || ROLE_STA != error_code)
    {
        UART_PRINT("Failed to start the device \n\r");
        return error_code;
    }

    UART_PRINT("Device started as STATION \n\r");

    //
    //Connecting to WLAN AP
    //
    error_code = WlanConnect();
    if(error_code < 0)
    {
        UART_PRINT("Failed to establish connection w/ an AP \n\r");
        GPIO_IF_LedOn(MCU_RED_LED_GPIO);
        return error_code;
    }

    UART_PRINT("Connection established w/ AP and IP is aquired \n\r");

    //Set time of the device for certificate verification.
    error_code = set_time();
    if(error_code < 0)
    {
        UART_PRINT("Unable to set time in the device");
        return error_code;
    }

    //Set time of the device for certificate verification.
    error_code = add_event("ayuns", "{}");

    if (error_code < 0) {
        UART_PRINT("Error posting event to API \n\r");
        return error_code;
    }

    UART_PRINT(request_buffer);
    UART_PRINT("\n\r");

    return SUCCESS;
}


//*****************************************************************************
//
//! Main 
//!
//! \param  none
//!
//! \return None
//!
//*****************************************************************************
void main()
    {
    long lRetVal = -1;
    //
    // Initialize board configuration
    //
    BoardInit();

    PinMuxConfig();

    #ifndef NOTERM
        InitTerm();
    #endif

    lRetVal = keen();
    if(lRetVal < 0)
    {
        ERR_PRINT(lRetVal);
    }

    //
    // power off network processor
    //
    sl_Stop(SL_STOP_TIMEOUT);
    LOOP_FOREVER();
}
//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************
