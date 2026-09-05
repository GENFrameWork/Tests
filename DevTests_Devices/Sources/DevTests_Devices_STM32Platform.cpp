/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Devices_STM32Platform.cpp
*
* @class      DEVTESTS_DEVICES_STM32PLATFORM
* @brief      Developed tests devices STM32 platform functions
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
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

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "DevTests_Devices_STM32Platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "XSTM32Trace.h"
#include "XSTM32_FATSD_SPI.h"
#include "DIOSTM32GPIO.h"
#include "DIOSTM32StreamI2C.h"
#include "DIOSTM32StreamSPI.h"

#include "MainProcSTM32.h"

#include "XTrace.h"
#include "XThreadListNonPreemptive.h"

#include "main.h"
#include "DevTests_Devices.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

XSTM32_FATSD_SPI  FATSD_SPI;


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int STM32_Platform_Ini(void)
* @brief      Initializes STM32 platform resources.
* @ingroup    TESTS
*
* @return     int : non-zero if the platform initialization is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
int STM32_Platform_Ini(void)
{
  _main();
  
  #ifdef XTRACE_ACTIVE
  STM32trace.SetHuart(&huart1);
  #endif
    
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_LED_RED                , GPIO_PIN_6  , DIOGPIO_PINSGROUP_C);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_LED_BLUE               , GPIO_PIN_7  , DIOGPIO_PINSGROUP_C); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_LED_ORANGE             , GPIO_PIN_8  , DIOGPIO_PINSGROUP_C); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_LED_GREEN              , GPIO_PIN_9  , DIOGPIO_PINSGROUP_C);   
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_BTN_BLUE               , GPIO_PIN_10 , DIOGPIO_PINSGROUP_C); 
 
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_FATSD_CS               , GPIO_PIN_4  , DIOGPIO_PINSGROUP_A); 
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_FATSD_SWITCH           , GPIO_PIN_8  , DIOGPIO_PINSGROUP_A); 
  
  FATSD_SPI.Ini(&hspi1, DevTests_Devices_GPIOENTRYID_FATSD_CS, DevTests_Devices_GPIOENTRYID_FATSD_SWITCH);
  
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_LED_NEOPIXEL           , GPIO_PIN_0  , DIOGPIO_PINSGROUP_A); 
  
  //-------------------------------------------------------------------------------------------------------------------

  DIOGPIO_ENTRY* int_entry = GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_TEST_INTERRUPT, GPIO_PIN_2, DIOGPIO_PINSGROUP_A);  
  if(int_entry) 
    {
      int_entry->SetIntIRQ(EXTI2_IRQn);
      int_entry->SetIntPriority(2);
    }

  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_I2C_CCS811_WAKEUP      , GPIO_PIN_9  , DIOGPIO_PINSGROUP_A);   
  
  //-------------------------------------------------------------------------------------------------------------------
  
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_SPI_DISPLAY_CS         , GPIO_PIN_4  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_SPI_DISPLAY_RESET      , GPIO_PIN_0  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_SPI_DISPLAY_DC         , GPIO_PIN_2  , DIOGPIO_PINSGROUP_A);
  GEN_DIOGPIO.GPIOEntry_CreateByPin(DevTests_Devices_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT  , GPIO_PIN_3  , DIOGPIO_PINSGROUP_A);
  
  //-------------------------------------------------------------------------------------------------------------------  
  
  return 1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void STM32_Platform_NonPreemptiveDoTasks(void)
* @brief      Executes STM32 non-preemptive tasks.
* @ingroup    TESTS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void STM32_Platform_NonPreemptiveDoTasks(void)
{
  __disable_irq();

  XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions();

  __enable_irq();   
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* STM32_Platform_GetI2C1(void)
* @brief      Gets the STM32 I2C1 handle.
* @ingroup    TESTS
*
* @return     void* : pointer to the requested platform handle.
*
* --------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetI2C1(void)
{
  if(!DIOSTM32STREAMI2C::ports[0]) return NULL; 
  return DIOSTM32STREAMI2C::ports[0]->GetHandleI2C();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* STM32_Platform_GetI2C3(void)
* @brief      Gets the STM32 I2C3 handle.
* @ingroup    TESTS
*
* @return     void* : pointer to the requested platform handle.
*
* --------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetI2C3(void)
{
  if(!DIOSTM32STREAMI2C::ports[2]) return NULL; 
  return DIOSTM32STREAMI2C::ports[2]->GetHandleI2C();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* STM32_Platform_GetSPI1(void)
* @brief      Gets the STM32 SPI1 handle.
* @ingroup    TESTS
*
* @return     void* : pointer to the requested platform handle.
*
* --------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetSPI1(void)
{
  if(!DIOSTM32STREAMSPI::ports[0]) return NULL; 
  return DIOSTM32STREAMSPI::ports[0]->GetHandleSPI();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void* STM32_Platform_GetSPI2(void)
* @brief      Gets the STM32 SPI2 handle.
* @ingroup    TESTS
*
* @return     void* : pointer to the requested platform handle.
*
* --------------------------------------------------------------------------------------------------------------------*/
void* STM32_Platform_GetSPI2(void)
{
  if(!DIOSTM32STREAMSPI::ports[1]) return NULL; 
  return DIOSTM32STREAMSPI::ports[1]->GetHandleSPI();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DSTATUS STM32_SD_Disk_Initialize(BYTE drive)
* @brief      Initializes the STM32 SD disk.
* @ingroup    TESTS
*
* @param[in]  drive : logical drive number.
*
* @return     DSTATUS : disk status returned by the operation.
*
* --------------------------------------------------------------------------------------------------------------------*/
DSTATUS STM32_SD_Disk_Initialize(BYTE drive)
{
  return FATSD_SPI.Disk_Initialize((XBYTE)drive);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DSTATUS STM32_SD_Disk_Status(BYTE drive)
* @brief      Gets the STM32 SD disk status.
* @ingroup    TESTS
*
* @param[in]  drive : logical drive number.
*
* @return     DSTATUS : disk status returned by the operation.
*
* --------------------------------------------------------------------------------------------------------------------*/
DSTATUS STM32_SD_Disk_Status(BYTE drive)
{
  return FATSD_SPI.Disk_Status((XBYTE)drive);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DRESULT STM32_SD_Disk_Read(BYTE pdrive, BYTE* buffer, DWORD sector, UINT count)
* @brief      Reads sectors from the STM32 SD disk.
* @ingroup    TESTS
*
* @param[in]  pdrive : physical drive number.
* @param[out]  buffer : buffer filled with the sectors read from the disk.
* @param[in]  sector : first sector used by the disk operation.
* @param[in]  count : number of sectors to process.
*
* @return     DRESULT : disk result returned by the operation.
*
* --------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_Read(BYTE pdrive, BYTE* buffer, DWORD sector, UINT count)
{
  return FATSD_SPI.Disk_Read((XBYTE)pdrive, (XBYTE*)buffer, (XDWORD)sector, (XDWORD)count);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DRESULT STM32_SD_Disk_Write(BYTE pdrive, const BYTE* buffer, DWORD sector, UINT count)
* @brief      Writes sectors to the STM32 SD disk.
* @ingroup    TESTS
*
* @param[in]  pdrive : physical drive number.
* @param[in]  buffer : buffer that contains the sectors to write to the disk.
* @param[in]  sector : first sector used by the disk operation.
* @param[in]  count : number of sectors to process.
*
* @return     DRESULT : disk result returned by the operation.
*
* --------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_Write(BYTE pdrive, const BYTE* buffer, DWORD sector, UINT count)
{
  return FATSD_SPI.Disk_Write((XBYTE)pdrive, (const XBYTE*)buffer, (XDWORD)sector, (XDWORD) count);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DRESULT STM32_SD_Disk_IOTCL(BYTE drive, BYTE ctrl, void* buffer)
* @brief      Executes an STM32 SD disk I/O control command.
* @ingroup    TESTS
*
* @param[in]  drive : logical drive number.
* @param[in]  ctrl : control command for the disk I/O operation.
* @param[out]  buffer : data buffer used by the disk operation.
*
* @return     DRESULT : disk result returned by the operation.
*
* --------------------------------------------------------------------------------------------------------------------*/
DRESULT STM32_SD_Disk_IOTCL(BYTE drive, BYTE ctrl, void* buffer)
{
  return FATSD_SPI.Disk_IOTCL((XBYTE)drive, (XBYTE)ctrl, buffer);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void STM32_Platform_Trace(int iserror, const char* mask, ...)
* @brief      Writes an STM32 platform trace message.
* @ingroup    TESTS
*
* @param[in]  iserror : true when the trace must be emitted as an error.
* @param[in]  mask : format mask used to build the trace text.
* @param[in]  ... : variable arguments used to format the trace text.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void STM32_Platform_Trace(int iserror, const char* mask, ...)
{
  XSTRING   concat;
  XSTRING   _mask;
  va_list   arg;

  _mask = mask;
  
  va_start(arg, mask);

  concat.FormatArg(_mask.Get(), &arg);

  va_end(arg);
   
  XTRACE_PRINTCOLOR((iserror == TRUE?XTRACE_COLOR_RED:XTRACE_COLOR_BLUE), __L("%s"), concat.Get());                   
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void STM32_Heap_Usage()
* @brief      Shows the STM32 heap usage.
* @ingroup    TESTS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void STM32_Heap_Usage()
{    
  struct mallinfo m;
  m = __iar_dlmallinfo();
  
  XDWORD total = m.uordblks + m.fordblks;
  XDWORD free  = m.fordblks;
    
  STM32_Platform_Trace(FALSE,"RAM Memory Total %u, (%uk) / Free: %u, (%uk)" , total, (total/1024), free, (free/1024));
    
  // __iar_dlmalloc_stats();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int STM32_Platform_End(void)
* @brief      Ends STM32 platform resources.
* @ingroup    TESTS
*
* @return     int : non-zero if the platform end operation is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
int STM32_Platform_End(void)
{
  return 1;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
* @brief      Handles the HAL GPIO external interrupt callback.
* @ingroup    TESTS
*
* @param[in]  GPIO_pin : GPIO pin that generated the interrupt.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_pin)
{
  DIOGPIO_ENTRY* int_GPIOentry = GEN_DIOGPIO.GPIOEntry_GetInterruptByPin(GPIO_pin);
  if(int_GPIOentry) 
    {
      DIOGPIO_INT_FUNCPTR funcptr = int_GPIOentry->GetIntFunctionPointer();
      if(funcptr) funcptr(int_GPIOentry->GetIntParamPointer());
    }  
}


