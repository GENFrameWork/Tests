/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole.h
* 
* @class      DEVTESTSCONSOLE
* @brief      Dev Tests Console class
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

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XTree.h"
#include "XScheduler.h"

#include "DIOStream.h"
#ifdef DIO_PCAP_ACTIVE
#include "DIOPCap.h"
#endif
#include "DIOURL.h"
#include "DIOGPIO.h"

#include "APPFlowConsole.h"

#include "DevTestsConsole_XSerializable.h"



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

#define APPLICATION_NAMEAPP                       __L("Developed Tests Console")
#define APPLICATION_NAMEFILE                      __L("devtestsconsole")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2022

//#define DEVTESTSCONSOLE_NOKEY

#define DEVTESTSCONSOLE_TASKID_TEST               1000


class DEVTESTSCONSOLE;
typedef bool (*DEVTESTSCONSOLE_FUNCTION)(DEVTESTSCONSOLE* tests);

typedef struct
{
  bool                      active;
  DEVTESTSCONSOLE_FUNCTION  function;
  XCHAR*                    namefunction;

} DEVTESTSCONSOLE_LIST_FUNCTION;


typedef struct
{
  int                       index;
  XTHREADCOLLECTED*         thread;
  DEVTESTSCONSOLE*          devtestconsole; 

} DEVTESTSCONSOLE_XTHREADPARAM;

#define DEVTESTSCONSOLE_MAXNTHREADS               5


typedef XTREE_NODE<XSTRING*>                      XTREE_NODE_TEST;
typedef XTREE_NODE_ITERATOR<XSTRING*>             XTREE_NODE_ITERATOR_TEST;
typedef XTREE<XSTRING*>                           XTREE_TEST;




/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIMER;
class XRAND;
class XMUTEX;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class HASH;
class CIPHER;
class DIOWEBCLIENT_XEVENT;
class DIODNSPROTOCOL_MITM_SERVER_XEVENT;
class DIOSTREAM_XEVENT;
class SNDITEM;
class SNDFACTORY_XEVENT;
class APPFLOWCHECKRESOURCESHARDWARE;
class APPFLOWINTERNETSERVICES;
class APPFLOWALERTS;


class DEVTESTSCONSOLE : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    DEVTESTSCONSOLE                     ();
    virtual                        ~DEVTESTSCONSOLE                     ();

    bool                            IniFSMachine                        ();

    bool                            AppProc_PlatformIni                 ();
    bool                            AppProc_Ini                         ();
    bool                            AppProc_FirstUpdate                 ();
    bool                            AppProc_Update                      ();
    bool                            AppProc_End                         ();
    bool                            AppProc_PlatformEnd                 ();

    bool                            KeyValidSecuences                   (int key);

    bool                            Show_PlaySound                      ();
    
    bool                            Do_Tests                            ();

    bool                            Params_IsModeServer                 ();

    static bool                     Test_XString                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XBuffer                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XRand                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XTrace                         (DEVTESTSCONSOLE* tests);
    static bool                     Test_XLogs                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XTimer                         (DEVTESTSCONSOLE* tests);
    static bool                     Test_XVector                        (DEVTESTSCONSOLE* tests);
  //static bool                     Test_XVectorSTL                     (DEVTESTSCONSOLE* tests);
    bool                            Test_XTree_AddChilds                (XTREE_NODE_TEST* node, int nchild);
    bool                            Test_XTree_InsertChilds             (XTREE_NODE_TEST* node, int indexchild);
    static bool                     Test_XTree                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_XDir                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_XVariant                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_Threads                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_DateTime                       (DEVTESTSCONSOLE* tests);    
    static bool                     Test_DIOStreamTCPIPConnection       (DEVTESTSCONSOLE* tests);
    static bool                     Test_XSystem                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_SharedMemory                   (DEVTESTSCONSOLE* tests);    
    static bool                     Test_GPIO                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_WebClient                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_ScraperWeb                     (DEVTESTSCONSOLE* tests);
    static bool                     Test_MPSSE                          (DEVTESTSCONSOLE* tests);
    static bool                     Test_DNSResolver                    (DEVTESTSCONSOLE* tests);
    static bool                     Test_DNSProtocolMitMServer          (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOCheckTCPIPConnections       (DEVTESTSCONSOLE* tests);
    static bool                     Test_WifiEnum                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_WakeOnLAN                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_Hash                           (DEVTESTSCONSOLE* tests);
    static bool                     Test_OneCipher_Simetric             (DEVTESTSCONSOLE* tests, bool operation, CIPHER* cipher, XBUFFER& input, XBUFFER& result);
    static bool                     Test_Cipher_Simetric                (DEVTESTSCONSOLE* tests);
    static bool                     Test_CipherFileKeys                 (DEVTESTSCONSOLE* tests);
    static bool							        Test_CipherRSA				   	          (DEVTESTSCONSOLE* tests);
    static bool                     Test_CipherECDSAX25519              (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamTCPIP                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamTLS                   (DEVTESTSCONSOLE* tests);
    static bool                     Test_SystemCPUUsage                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_AppAlerts                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_BluetoothEnum                  (DEVTESTSCONSOLE* tests);
    static bool                     Test_BluetoothLEEnum                (DEVTESTSCONSOLE* tests);
    static bool                     Test_NTP_Protocol                   (DEVTESTSCONSOLE* tests);
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
    static bool                     Test_XFileJSON                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileXML                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileRIFF                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamUSBConnection         (DEVTESTSCONSOLE* tests);
    static bool                     Test_XFileDFU                       (DEVTESTSCONSOLE* tests);  
    static bool                     Test_SystemHostFile                 (DEVTESTSCONSOLE* tests);  
    static bool                     Test_SystemBatteryLevel             (DEVTESTSCONSOLE* tests);      
    static bool                     Test_LedNeoPixelWS2812B             (DEVTESTSCONSOLE* tests);  
    static bool                     Test_DIOPCap                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_XLicense                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_XSerializable                  (DEVTESTSCONSOLE* tests);
    static bool                     Test_InputSimulate                  (DEVTESTSCONSOLE* tests);
    static bool                     Test_Scheduler                      (DEVTESTSCONSOLE* tests);
    static bool                     Test_DynDNS                         (DEVTESTSCONSOLE* tests);
    static bool                     Test_ID_IBAN                        (DEVTESTSCONSOLE* tests);
    static bool                     Test_Compress                       (DEVTESTSCONSOLE* tests);
    static bool                     Test_DIOStreamTCPIPServer           (DEVTESTSCONSOLE* tests);
    static bool                     Test_XPath                          (DEVTESTSCONSOLE* tests);
    
    #ifdef WINDOWS
    static bool                     Test_WindowsACL                     (DEVTESTSCONSOLE* tests);
    static bool                     Test_WindowsRegistry                (DEVTESTSCONSOLE* tests);
    static bool                     Test_WindowsWinget                  (DEVTESTSCONSOLE* tests);
    #endif

    #ifdef LINUX
    static bool                     Test_DBUS                           (DEVTESTSCONSOLE* tests); 
    static bool                     Test_NetWorkManager                 (DEVTESTSCONSOLE* tests);
    static bool                     Test_DeviceBusInputFile             (DEVTESTSCONSOLE* tests);   
    #endif


  private:

    bool                            Test_Hash                           (HASH* HASH, XBUFFER& input, XCHAR* leyend);

    static bool                     Test_WaitSound                      (SNDITEM* item);   

    void                            HandleEvent_Scheduler               (XSCHEDULER_XEVENT* event);
    void                            HandleEvent_Sound                   (SNDFACTORY_XEVENT* event);
    void                            HandleEvent_WebClient               (DIOWEBCLIENT_XEVENT* event);
    void                            HandleEvent_DNSProtocol_MitM_Server (DIODNSPROTOCOL_MITM_SERVER_XEVENT* event);
    void                            HandleEvent_DIOStream               (DIOSTREAM_XEVENT* event);
    void                            HandleEvent                         (XEVENT* xevent);

    static void                     ThreadRunFunction                   (void* param);

    void                            Clean                               ();
    
   
    XTIMER*                         xtimerupdateconsole;    
    XMUTEX*                         xmutexthread;    
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





