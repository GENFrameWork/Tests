/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Devices.h
*
* @class      DEVTESTS_DEVICES
* @brief      Developed tests devices I/O UART USB I2C GPIO class
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
#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XBuffer.h"
#include "APPFlowBase.h"

#include "DIOGPIO.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DEVTESTS_DEVICES_VERSION            0
#define DEVTESTS_DEVICES_SUBVERSION         1
#define DEVTESTS_DEVICES_SUBVERSIONERR      0
#define DEVTESTS_DEVICES_NAMEAPP            __L("DevTests_Devices")


class DEVTESTS_DEVICES;
typedef bool (*DEVTESTS_DEVICES_FUNCTION)(DEVTESTS_DEVICES* tests);

typedef struct
{
  bool                      active;
  DEVTESTS_DEVICES_FUNCTION  function;
  XCHAR*                    namefunction;

} DEVTESTS_CONSOLE_LIST_FUNCTION;


enum DEVTESTS_DEVICES_GPIOENTRYID
{
  DEVTESTS_DEVICES_GPIOENTRYID_LED_RED                  = DIOGPIO_ID_NOTDEFINED + 1 ,
  DEVTESTS_DEVICES_GPIOENTRYID_LED_BLUE                                             ,
  DEVTESTS_DEVICES_GPIOENTRYID_LED_ORANGE                                           ,
  DEVTESTS_DEVICES_GPIOENTRYID_LED_GREEN                                            ,
  DEVTESTS_DEVICES_GPIOENTRYID_BTN_BLUE                                             ,  

  DEVTESTS_DEVICES_GPIOENTRYID_FATSD_CS                                             ,  
  DEVTESTS_DEVICES_GPIOENTRYID_FATSD_SWITCH                                         ,  
   
  DEVTESTS_DEVICES_GPIOENTRYID_LED_NEOPIXEL                                         ,  

  DEVTESTS_DEVICES_GPIOENTRYID_TEST_INTERRUPT                                       ,  

  DEVTESTS_DEVICES_GPIOENTRYID_I2C_CCS811_WAKEUP                                    ,
  
  DEVTESTS_DEVICES_GPIOENTRYID_SPI_DISPLAY_CS                                       ,                                                      
  DEVTESTS_DEVICES_GPIOENTRYID_SPI_DISPLAY_RESET                                    ,  
  DEVTESTS_DEVICES_GPIOENTRYID_SPI_DISPLAY_DC                                       ,
  DEVTESTS_DEVICES_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT                  
};


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;
class MAIN;

class DEVTESTS_DEVICES : public APPFLOWBASE
{
  public:
                        DEVTESTS_DEVICES                     ();
    virtual            ~DEVTESTS_DEVICES                     ();

    bool                AppProc_PlatformIni                 ();
    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_LastUpdate                  ();  
    bool                AppProc_End                         ();
    bool                AppProc_PlatformEnd                 ();

    static bool         Test_Random                         (DEVTESTS_DEVICES* tests);
    static bool         Test_DIOStreamUART                  (DEVTESTS_DEVICES* tests);
    static bool         Test_DIOStreamUSBReadCommand        (DEVTESTS_DEVICES* tests, DIOSTREAM* diostream, XBUFFER& command);
    static bool         Test_DIOStreamUSB                   (DEVTESTS_DEVICES* tests);

    static bool         I2CTest_6AxisTrackingLSM303DLHC     (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_6AxisTrackingBMI270         (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_AxisTrackingMPU9150         (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_ADDAConverterPCF8591        (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_AirQualityCCS811            (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_EEprom24XXX                 (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_GPIOMCP2317                 (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_GPIOPCF8574                 (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_LightSensorTSL2561          (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_OLEDDisplaySSD1306          (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_PWMControlerPCA9685         (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_TemHumSensorAM2315          (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_TemHumSensorSHT20           (DEVTESTS_DEVICES* tests, int port, int timeout);    
    static bool         I2CTest_MonitorGaugeLTC2942         (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_BatteryChargerBQ24295       (DEVTESTS_DEVICES* tests, int port, int timeout);
    static bool         I2CTest_TouchSensorAT42QT1060       (DEVTESTS_DEVICES* tests, int port, int timeout);    
    static bool         Test_DIOStreamI2C                   (DEVTESTS_DEVICES* tests);

    static bool         SPITest_GPIOMCP23S17                (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_LCDDisplayPCF8833           (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_OLEDDisplaySSD1306          (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_OLEDDisplaySSD1331          (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout);   
    static bool         SPITest_TFTDisplayILI9341           (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_TFTDisplayST7789            (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_TouchScreenSTMPE610         (DEVTESTS_DEVICES* tests, int port, int chipselect, int timeout);         
    static bool         Test_DIOStreamSPI                   (DEVTESTS_DEVICES* tests);    

    static bool         Test_DIOGPIO                        (DEVTESTS_DEVICES* tests); 
    static bool         Test_DIOGPIO_Interrupt              (DEVTESTS_DEVICES* tests);
    static bool         Test_EEPROMMemory                   (DEVTESTS_DEVICES* tests);
    static bool         Test_DIONeoPixel                    (DEVTESTS_DEVICES* tests);
    static bool         Test_DirFunctions                   (DEVTESTS_DEVICES* tests);
    static bool         Test_FileFunctions                  (DEVTESTS_DEVICES* tests);

    static void         Test_Callback_Interrupt             (void* param);

  private:

    void                Clean                               ();

};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/


