/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsDevices.h
* 
* @class      DEVTESTSDEVICES
* @brief      Developed Tests Devices I/O  UART / USB / I2C / GPIO  class
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

#define DEVTESTSDEVICES_VERSION            0
#define DEVTESTSDEVICES_SUBVERSION         1
#define DEVTESTSDEVICES_SUBVERSIONERR      0
#define DEVTESTSDEVICES_NAMEAPP            __L("DevTestsDevices")


class DEVTESTSDEVICES;
typedef bool (*DEVTESTSDEVICES_FUNCTION)(DEVTESTSDEVICES* tests);

typedef struct
{
  bool                      active;
  DEVTESTSDEVICES_FUNCTION  function;
  XCHAR*                    namefunction;

} DEVTESTSCONSOLE_LIST_FUNCTION;


enum DEVTESTSDEVICES_GPIOENTRYID
{
  DEVTESTSDEVICES_GPIOENTRYID_LED_RED                  = DIOGPIO_ID_NOTDEFINED + 1 ,
  DEVTESTSDEVICES_GPIOENTRYID_LED_BLUE                                             ,
  DEVTESTSDEVICES_GPIOENTRYID_LED_ORANGE                                           ,
  DEVTESTSDEVICES_GPIOENTRYID_LED_GREEN                                            ,
  DEVTESTSDEVICES_GPIOENTRYID_BTN_BLUE                                             ,  

  DEVTESTSDEVICES_GPIOENTRYID_FATSD_CS                                             ,  
  DEVTESTSDEVICES_GPIOENTRYID_FATSD_SWITCH                                         ,  
   
  DEVTESTSDEVICES_GPIOENTRYID_LED_NEOPIXEL                                         ,  

  DEVTESTSDEVICES_GPIOENTRYID_TEST_INTERRUPT                                       ,  

  DEVTESTSDEVICES_GPIOENTRYID_I2C_CCS811_WAKEUP                                    ,
  
  DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_CS                                       ,                                                      
  DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_RESET                                    ,  
  DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_DC                                       ,
  DEVTESTSDEVICES_GPIOENTRYID_SPI_DISPLAY_BACKLIGHT                  
};



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DIOSTREAM;
class MAIN;

class DEVTESTSDEVICES : public APPFLOWBASE
{
  public:
                        DEVTESTSDEVICES                     ();
    virtual            ~DEVTESTSDEVICES                     ();

    bool                AppProc_PlatformIni                 ();
    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_LastUpdate                  ();  
    bool                AppProc_End                         ();
    bool                AppProc_PlatformEnd                 ();

    static bool         Test_Random                         (DEVTESTSDEVICES* tests);
    static bool         Test_DIOStreamUART                  (DEVTESTSDEVICES* tests);
    static bool         Test_DIOStreamUSBReadCommand        (DEVTESTSDEVICES* tests, DIOSTREAM* diostream, XBUFFER& command);
    static bool         Test_DIOStreamUSB                   (DEVTESTSDEVICES* tests);

    static bool         I2CTest_6AxisTrackingLSM303DLHC     (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_6AxisTrackingBMI270         (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_AxisTrackingMPU9150         (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_ADDAConverterPCF8591        (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_AirQualityCCS811            (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_EEprom24XXX                 (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_GPIOMCP2317                 (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_GPIOPCF8574                 (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_LightSensorTSL2561          (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_OLEDDisplaySSD1306          (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_PWMControlerPCA9685         (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_TemHumSensorAM2315          (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_TemHumSensorSHT20           (DEVTESTSDEVICES* tests, int port, int timeout);    
    static bool         I2CTest_MonitorGaugeLTC2942         (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_BatteryChargerBQ24295       (DEVTESTSDEVICES* tests, int port, int timeout);
    static bool         I2CTest_TouchSensorAT42QT1060       (DEVTESTSDEVICES* tests, int port, int timeout);    
    static bool         Test_DIOStreamI2C                   (DEVTESTSDEVICES* tests);

    static bool         SPITest_GPIOMCP23S17                (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_LCDDisplayPCF8833           (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_OLEDDisplaySSD1306          (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_OLEDDisplaySSD1331          (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout);   
    static bool         SPITest_TFTDisplayILI9341           (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_TFTDisplayST7789            (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout); 
    static bool         SPITest_TouchScreenSTMPE610         (DEVTESTSDEVICES* tests, int port, int chipselect, int timeout);         
    static bool         Test_DIOStreamSPI                   (DEVTESTSDEVICES* tests);    

    static bool         Test_DIOGPIO                        (DEVTESTSDEVICES* tests); 
    static bool         Test_DIOGPIO_Interrupt              (DEVTESTSDEVICES* tests);
    static bool         Test_EEPROMMemory                   (DEVTESTSDEVICES* tests);
    static bool         Test_DIONeoPixel                    (DEVTESTSDEVICES* tests);
    static bool         Test_DirFunctions                   (DEVTESTSDEVICES* tests);
    static bool         Test_FileFunctions                  (DEVTESTSDEVICES* tests);

    static void         Test_Callback_Interrupt             (void* param);

  private:

    void                Clean                               ();

};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





