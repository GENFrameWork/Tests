/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTestsConsole.h
*
* @class      DEVTESTSCONSOLE
* @brief      Dev Tests Console class
* @ingroup    TESTS
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/

#ifndef _DEVTESTSCONSOLE_H_
#define _DEVTESTSCONSOLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XTree.h"
#include "XProperty.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOPCap.h"
#include "DIOURL.h"
#include "DIOGPIO.h"

#include "APPConsole.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DEVTESTSCONSOLEXFSMEVENTS
{
  DEVTESTSCONSOLE_XFSMEVENT_NONE              = 0 ,
  DEVTESTSCONSOLE_XFSMEVENT_INI                   ,
  DEVTESTSCONSOLE_XFSMEVENT_UPDATE                ,
  DEVTESTSCONSOLE_XFSMEVENT_END                   ,

  DEVTESTSCONSOLE_LASTEVENT
};


enum DEVTESTSCONSOLEXFSMSTATES
{
  DEVTESTSCONSOLE_XFSMSTATE_NONE              = 0 ,
  DEVTESTSCONSOLE_XFSMSTATE_INI                   ,
  DEVTESTSCONSOLE_XFSMSTATE_UPDATE                ,
  DEVTESTSCONSOLE_XFSMSTATE_END                   ,

  DEVTESTSCONSOLE_LASTSTATE
};



enum DEVTESTSCONSOLE_GPIOENTRYID
{
  DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO             = DIOGPIO_ID_NOTDEFINED + 1 ,   
  DEVTESTSCONSOLE_GPIOENTRYID_LED_NEOPIXEL                                             
};



#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("devtestsconsole")
#define APPLICATION_NAMEFILE                      __L("Unit tests")

#define APPLICATION_YEAROFCREATION                2022

#define DEVTESTSCONSOLE_ENTERPRISE                __L("GEN Group")

//#define DEVTESTSCONSOLE_NOKEY


class DEVTESTSCONSOLE;
typedef bool (*DEVTESTSCONSOLE_FUNCTION)(DEVTESTSCONSOLE* tests);


typedef struct
{
  bool            active;
  DEVTESTSCONSOLE_FUNCTION  function;
  XCHAR*          namefunction;

} DEVTESTSCONSOLE_LIST_FUNCTION;


class DEVTESTSCONSOLE_PROPERTY
{ 
  public:                                     
                      DEVTESTSCONSOLE_PROPERTY        () : x(this), y(this), z(this)
                      {
                        x_ = 0.0f;
                        y_ = 0.0f;
                        z_ = 10.0f;
                      }
                      /*
                      DEVTESTSCONSOLE_PROPERTY        (double x0, double y0) : x_(x0), y_(y0), x(this), y(this), z(this)
                      {
                        z_ = 10.0f;
                      } 
                      */

    void              SetX                            (double x) 
                      { 
                        x_ = x; 
                      }

    double            GetX                            () 
                      { 
                        return x_; 
                      } 

    XPROPERTY<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetX, &DEVTESTSCONSOLE_PROPERTY::SetX> x;

    void              SetY                            (double y) 
                      { 
                        y_ = y;                       
                      }

    double            GetY                            () 
                      { 
                        return y_; 
                      }

   
    XPROPERTY<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetY, &DEVTESTSCONSOLE_PROPERTY::SetY> y;


    double            GetZ                            ()
                      {
                        return z_;
                      }


    XPROPERTYG<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetZ> z;

    double            x_;
    double            y_;
    double            z_;   
};



class DEVTESTSCONSOLE_PROPERTY2
{
  public:
                      DEVTESTSCONSOLE_PROPERTY2         () :  data(this)
                      {

                      }

                      /*
                      DEVTESTSCONSOLE_PROPERTY2         (DEVTESTSCONSOLE_PROPERTY data0) : data_(data0), data(this)
                      {
                      }
                      */

    void              SetX                              (DEVTESTSCONSOLE_PROPERTY data)
                      {
                        data_.x = data.x;
                      }

    DEVTESTSCONSOLE_PROPERTY GetX                       ()
                      {
                        return data_;
                      }

    
    XPROPERTY<DEVTESTSCONSOLE_PROPERTY2, DEVTESTSCONSOLE_PROPERTY, &DEVTESTSCONSOLE_PROPERTY2::GetX, &DEVTESTSCONSOLE_PROPERTY2::SetX>  data;

    DEVTESTSCONSOLE_PROPERTY data2;


  private:

    DEVTESTSCONSOLE_PROPERTY data_;

};



#define DEVTESTSCONSOLE_MAXNTHREADS                      5


typedef XTREE_NODE<XSTRING*>                      XTREE_NODE_TEST;
typedef XTREE_NODE_ITERATOR<XSTRING*>             XTREE_NODE_ITERATOR_TEST;
typedef XTREE<XSTRING*>                           XTREE_TEST;

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class HASH;
class DIOWEBCLIENT_XEVENT;
class APPCHECKRESOURCESHARDWARE;
class APPINTERNETSERVICES;
class APPALERTS;


class DEVTESTSCONSOLE : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    DEVTESTSCONSOLE                     ();
    virtual                        ~DEVTESTSCONSOLE                     ();

    bool                            InitFSMachine                       ();

    bool                            AppProc_PlatformIni                 ();
    bool                            AppProc_Ini                         ();
    bool                            AppProc_FirstUpdate                 ();
    bool                            AppProc_Update                      ();
    bool                            AppProc_End                         ();
    bool                            AppProc_PlatformEnd                 ();

    bool                            KeyValidSecuences                   (int key);

    bool                            Show_Line                           (XSTRING& string, XSTRING& string2, int tab = 3, bool linefeed = true);
    bool                            Show_Header                         (bool separator);
    bool                            Show_AppStatus                      ();
    bool                            Show_AllStatus                      ();

    bool                            Do_Tests                            ();

    bool                            Params_IsModeServer                 ();

    static bool                     Test_XString                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XBuffer                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XRand                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XTrace                         (DEVTESTSCONSOLE* tests);
    static bool                     Test_XLogs                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XVector                        (DEVTESTSCONSOLE* tests);
    bool                            Test_XTree_AddChilds                (XTREE_NODE_TEST* node, int nchild);
    bool                            Test_XTree_InsertChilds             (XTREE_NODE_TEST* node, int indexchild);
    static bool                     Test_XTree                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XDir                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_Threads                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_DateTime                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_HASH                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamTCPIPConnection       (DEVTESTSCONSOLE* tests);
    static bool                     Test_XSystem                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_SharedMemory                   (DEVTESTSCONSOLE* tests);    
    static bool                     Test_GPIO                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_WebClient                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_ScraperWeb                     (DEVTESTSCONSOLE* tests);
    static bool                     Test_MPSSE                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_DNSProtocol                    (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOCheckTCPIPConnections       (DEVTESTSCONSOLE* tests);
    static bool                     Test_WifiEnum                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_WakeOnLAN                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamTLS                   (DEVTESTSCONSOLE* tests);
    static bool                     Test_SystemCPUUsage                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_AppAlerts                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_BluetoothEnum                  (DEVTESTSCONSOLE* tests);
    static bool                     Test_BluetoothLEEnum                (DEVTESTSCONSOLE* tests);
    static bool                     Test_NTP_InternetServices           (DEVTESTSCONSOLE* tests);
    static bool                     Test_Sound                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_ProcessManager                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_GetUserAndDomain               (DEVTESTSCONSOLE* tests);  
    static bool                     Test_I2C_GPIO_MCP2317               (DEVTESTSCONSOLE* tests);
    static bool                     Test_SPI_GPIO_MCP2317               (DEVTESTSCONSOLE* tests);
    static bool                     Test_WifiManagerMode                (DEVTESTSCONSOLE* tests);
    static bool                     Test_NotificationsManager           (DEVTESTSCONSOLE* tests);
    static bool                     Test_ATCommandGSM                   (DEVTESTSCONSOLE* tests);
    static bool                     Test_SNMP                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileXML                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileRIFF                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamUSBConnection         (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileDFU                       (DEVTESTSCONSOLE* tests);  
    static bool                     Test_SystemHostFile                 (DEVTESTSCONSOLE* tests);  
    static bool                     Test_SystemBatteryLevel             (DEVTESTSCONSOLE* tests);      
    static bool                     Test_LedNeoPixelWS2812B             (DEVTESTSCONSOLE* tests);  
    static bool                     Test_DIOPCap                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XProperty                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_XLicense                       (DEVTESTSCONSOLE* tests);

    #ifdef WINDOWS
    static bool                     Test_WindowsACL                     (DEVTESTSCONSOLE* tests);
    #endif

    #ifdef LINUX
    static bool                     Test_DBUS                           (DEVTESTSCONSOLE* tests); 
    static bool                     Test_NetWorkManager                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_DeviceBusInputFile             (DEVTESTSCONSOLE* tests);   
    #endif


  private:

    bool                            Test_Hash                           (HASH* HASH, XBUFFER& input, XCHAR* leyend);

    void                            HandleEvent_Scheduler               (XSCHEDULER_XEVENT* event);
    void                            HandleEvent_WebClient               (DIOWEBCLIENT_XEVENT* event);
    void                            HandleEvent                         (XEVENT* xevent);

    static void                     ThreadRunFunction                   (void* param);

    void                            Clean                               ();
    
    APPCHECKRESOURCESHARDWARE*      appcheckresourceshardware;
    APPINTERNETSERVICES*            appinternetservices;

    XTIMER*                         xtimerupdateconsole;
    XMUTEX*                         xmutexshowallstatus;
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif
