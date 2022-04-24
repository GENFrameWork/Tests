/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests.h
*
* @class      UNITTEST
* @brief      GEN Unit Tests class
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

#ifndef _UNITTEST_H_
#define _UNITTEST_H_

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

enum UNITTESTXFSMEVENTS
{
  UNITTEST_XFSMEVENT_NONE              = 0 ,
  UNITTEST_XFSMEVENT_INI                   ,
  UNITTEST_XFSMEVENT_UPDATE                ,
  UNITTEST_XFSMEVENT_END                   ,

  UNITTEST_LASTEVENT
};


enum UNITTESTXFSMSTATES
{
  UNITTEST_XFSMSTATE_NONE              = 0 ,
  UNITTEST_XFSMSTATE_INI                   ,
  UNITTEST_XFSMSTATE_UPDATE                ,
  UNITTEST_XFSMSTATE_END                   ,

  UNITTEST_LASTSTATE
};



enum UNITTEST_GPIOENTRYID
{
  UNITTEST_GPIOENTRYID_TESTGPIO             = DIOGPIO_ID_NOTDEFINED + 1 ,   
  UNITTEST_GPIOENTRYID_LED_NEOPIXEL                                             
};



#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("unittests")
#define APPLICATION_NAMEFILE                      __L("Unit tests")

#define APPLICATION_YEAROFCREATION                2019

#define UNITTEST_ENTERPRISE                       __L("GEN Group")

//#define UNITTEST_NOKEY


class UNITTEST;
typedef bool (*UNITTEST_FUNCTION)(UNITTEST* tests);


typedef struct
{
  bool            active;
  UNITTEST_FUNCTION  function;
  XCHAR*          namefunction;

} UNITTEST_LIST_FUNCTION;


class UNITTEST_PROPERTY
{ 
  public:                                     
                      UNITTEST_PROPERTY          () : x(this), y(this), z(this)
                      {
                        x_ = 0.0f;
                        y_ = 0.0f;
                        z_ = 10.0f;
                      }

                      UNITTEST_PROPERTY          (double x0, double y0) : x_(x0), y_(y0), x(this), y(this), z(this)
                      {
                        z_ = 10.0f;
                      } 

    void              SetX                    (double x) 
                      { 
                        x_ = x; 
                      }

    double            GetX                    () 
                      { 
                        return x_; 
                      } 

    XPROPERTY<UNITTEST_PROPERTY, double, &UNITTEST_PROPERTY::GetX, &UNITTEST_PROPERTY::SetX> x;

    void              SetY                    (double y) 
                      { 
                        y_ = y;                       
                      }

    double            GetY                    () 
                      { 
                        return y_; 
                      }

   
    XPROPERTY<UNITTEST_PROPERTY, double, &UNITTEST_PROPERTY::GetY, &UNITTEST_PROPERTY::SetY> y;


    double            GetZ                    ()
                      {
                        return z_;
                      }


    XPROPERTYG<UNITTEST_PROPERTY, double, &UNITTEST_PROPERTY::GetZ> z;

    double            x_;
    double            y_;
    double            z_;   
};



class UNITTEST_PROPERTY2
{
  public:
                      UNITTEST_PROPERTY2         () :  data(this)
                      {

                      }

                      UNITTEST_PROPERTY2         (UNITTEST_PROPERTY data0) : data_(data0), data(this)
                      {
                      }

    void              SetX                    (UNITTEST_PROPERTY data)
                      {
                        data_.x = data.x;
                      }

    UNITTEST_PROPERTY GetX                     ()
                      {
                        return data_;
                      }

    
    XPROPERTY<UNITTEST_PROPERTY2, UNITTEST_PROPERTY, &UNITTEST_PROPERTY2::GetX, &UNITTEST_PROPERTY2::SetX>  data;

    UNITTEST_PROPERTY data2;


  private:

    UNITTEST_PROPERTY data_;

};



#define UNITTEST_MAXNTHREADS                      5


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


class UNITTEST : public APPCONSOLE, public XFSMACHINE
{
  public:
                                    UNITTEST                            ();
    virtual                        ~UNITTEST                            ();

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

    static bool                     Test_XString                        (UNITTEST* tests);
    static bool                     Test_XBuffer                        (UNITTEST* tests);
    static bool                     Test_XRand                          (UNITTEST* tests);
    static bool                     Test_XTrace                         (UNITTEST* tests);
    static bool                     Test_XLogs                          (UNITTEST* tests);
    static bool                     Test_XVector                        (UNITTEST* tests);
    bool                            Test_XTree_AddChilds                (XTREE_NODE_TEST* node, int nchild);
    bool                            Test_XTree_InsertChilds             (XTREE_NODE_TEST* node, int indexchild);
    static bool                     Test_XTree                          (UNITTEST* tests);
    static bool                     Test_XDir                           (UNITTEST* tests);
    static bool                     Test_Threads                        (UNITTEST* tests);
    static bool                     Test_DateTime                       (UNITTEST* tests);
    static bool                     Test_HASH                           (UNITTEST* tests);
    static bool                     Test_DIOStreamTCPIPConnection       (UNITTEST* tests);
    static bool                     Test_XSystem                        (UNITTEST* tests);
    static bool                     Test_SharedMemory                   (UNITTEST* tests);    
    static bool                     Test_GPIO                           (UNITTEST* tests);
    static bool                     Test_WebClient                      (UNITTEST* tests);
    static bool                     Test_ScraperWeb                     (UNITTEST* tests);
    static bool                     Test_MPSSE                          (UNITTEST* tests);
    static bool                     Test_DNSProtocol                    (UNITTEST* tests);
    static bool                     Test_DIOCheckTCPIPConnections       (UNITTEST* tests);
    static bool                     Test_WifiEnum                       (UNITTEST* tests);
    static bool                     Test_WakeOnLAN                      (UNITTEST* tests);
    static bool                     Test_DIOStreamTLS                   (UNITTEST* tests);
    static bool                     Test_SystemCPUUsage                 (UNITTEST* tests);
    static bool                     Test_AppAlerts                      (UNITTEST* tests);
    static bool                     Test_BluetoothEnum                  (UNITTEST* tests);
    static bool                     Test_BluetoothLEEnum                (UNITTEST* tests);
    static bool                     Test_NTP_InternetServices           (UNITTEST* tests);
    static bool                     Test_Sound                          (UNITTEST* tests);
    static bool                     Test_ProcessManager                 (UNITTEST* tests);
    static bool                     Test_GetUserAndDomain               (UNITTEST* tests);  
    static bool                     Test_I2C_GPIO_MCP2317               (UNITTEST* tests);
    static bool                     Test_SPI_GPIO_MCP2317               (UNITTEST* tests);
    static bool                     Test_WifiManagerMode                (UNITTEST* tests);
    static bool                     Test_NotificationsManager           (UNITTEST* tests);
    static bool                     Test_ATCommandGSM                   (UNITTEST* tests);
    static bool                     Test_SNMP                           (UNITTEST* tests);
    static bool                     Test_XFileXML                       (UNITTEST* tests);
    static bool                     Test_XFileRIFF                      (UNITTEST* tests);
    static bool                     Test_DIOStreamUSBConnection         (UNITTEST* tests);
    static bool                     Test_XFileDFU                       (UNITTEST* tests);  
    static bool                     Test_SystemHostFile                 (UNITTEST* tests);  
    static bool                     Test_SystemBatteryLevel             (UNITTEST* tests);      
    static bool                     Test_LedNeoPixelWS2812B             (UNITTEST* tests);  
    static bool                     Test_DIOPCap                        (UNITTEST* tests);
    static bool                     Test_XProperty                      (UNITTEST* tests);
    static bool                     Test_XLicense                       (UNITTEST* tests);

    #ifdef WINDOWS
    static bool                     Test_WindowsACL                     (UNITTEST* tests);
    #endif

    #ifdef LINUX
    static bool                     Test_DBUS                           (UNITTEST* tests); 
    static bool                     Test_NetWorkManager                 (UNITTEST* tests);
    static bool                     Test_DeviceBusInputFile             (UNITTEST* tests);   
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

