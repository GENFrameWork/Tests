/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole_LinuxPlatform.cpp
* 
* @class      DEVTESTSCONSOLE_LINUXPLATFORM
* @brief      Developed Tests console LINUX Platform functions
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

#include "DevTestsConsole_LinuxPlatform.h"

#include "DIOGPIO.h"

#include "DevTestsConsole.h"

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
* @fn         int Linux_Platform_Ini(void);
* @brief      inux_Platform_Ini
* @ingroup    DATAIO
* 
* 
* @param[in]  void) : 
* 
* @return     int : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
int Linux_Platform_Ini(void)
{

  // -----------------------------------------------------------------------

  #ifdef HW_INTEL

  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO               , 1);  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DEVTESTSCONSOLE_GPIOENTRYID_LED_NEOPIXEL           , 6); 
   
  #endif

  // -----------------------------------------------------------------------

  #ifdef HW_RASPBERRYPI

  GEN_DIOGPIO.GPIOEntry_SetIDByGPIO(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO               , 17);  
  GEN_DIOGPIO.GPIOEntry_SetIDByGPIO(DEVTESTSCONSOLE_GPIOENTRYID_LED_NEOPIXEL           , 18);

  #endif

  // -----------------------------------------------------------------------

  #ifdef HW_ARM64

  GEN_DIOGPIO.GPIOEntry_CreateByGPIO(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO              , 73);  
  GEN_DIOGPIO.GPIOEntry_CreateByGPIO(DEVTESTSCONSOLE_GPIOENTRYID_LED_NEOPIXEL          , 73);
 
  #endif

  // -----------------------------------------------------------------------
  
  return 1;
}

#pragma endregion

