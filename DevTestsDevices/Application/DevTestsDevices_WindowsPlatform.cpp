/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsDevices_WindowsPlatform.cpp
* 
* @class      DEVTESTSDEVICES_WINDOWSPLATFORM
* @brief      Developed Tests Devices I/O  UART / USB / I2C / GPIO WINDOWS Platform functions
* @ingroup    TESTS
* 
* @copyright  GEN Group. All rights reserved.
* 
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
* 
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DevTestsDevices_WindowsPlatform.h"

#include "DIOGPIO.h"

#include "DevTestsDevices.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int Windows_Platform_Main(void)
* @brief      Windows_Platform_Main
* @ingroup    DATAIO
*
* @param[in]  void :
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int Windows_Platform_Ini(void)
{
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_LED_RED                , 1);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_LED_BLUE               , 2);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_LED_ORANGE             , 3);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_LED_GREEN              , 4);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_BTN_BLUE               , 5);

  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_FATSD_CS               , 7); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_FATSD_SWITCH           , 8); 

  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_TEST_INTERRUPT         , 6); 
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_LED_NEOPIXEL           , 6); 

  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_I2C_CCS811_WAKEUP      , 6);
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_RESET      , 5);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_DC         , 6);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT  , 7);

  return 1;
}


#pragma endregion









