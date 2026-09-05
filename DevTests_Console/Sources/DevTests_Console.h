/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Console.h
*
* @class      DEVTESTS_CONSOLE
* @brief      Developed tests console class
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
#ifdef DIO_STREAMTLS_ACTIVE
#include "DIOStreamTLS13KeySchedule.h"
#include "DIOStreamTLS13Session.h"
#endif

#include "APPFlowConsole.h"

#include "DevTests_Console_XSerializable.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum DEVTESTS_CONSOLEXFSMEVENTS
{
  DEVTESTS_CONSOLE_XFSMEVENT_NONE              = 0 ,
  DEVTESTS_CONSOLE_XFSMEVENT_INI                   ,
  DEVTESTS_CONSOLE_XFSMEVENT_UPDATE                ,
  DEVTESTS_CONSOLE_XFSMEVENT_END                   ,

  DEVTESTS_CONSOLE_LASTEVENT
};


enum DEVTESTS_CONSOLEXFSMSTATES
{
  DEVTESTS_CONSOLE_XFSMSTATE_NONE              = 0 ,
  DEVTESTS_CONSOLE_XFSMSTATE_INI                   ,
  DEVTESTS_CONSOLE_XFSMSTATE_UPDATE                ,
  DEVTESTS_CONSOLE_XFSMSTATE_END                   ,

  DEVTESTS_CONSOLE_LASTSTATE
};


enum DEVTESTS_CONSOLE_GPIOENTRYID
{
  DEVTESTS_CONSOLE_GPIOENTRYID_TESTGPIO             = DIOGPIO_ID_NOTDEFINED + 1 ,   
  DEVTESTS_CONSOLE_GPIOENTRYID_LED_NEOPIXEL                                             
};


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("Developed Tests Console")
#define APPLICATION_NAMEFILE                      __L("devtests_console")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2022

//#define DEVTESTS_CONSOLE_NOKEY

#define DEVTESTS_CONSOLE_TASKID_TEST               1000


class DEVTESTS_CONSOLE;
typedef bool (*DEVTESTS_CONSOLE_FUNCTION)(DEVTESTS_CONSOLE* tests);

typedef struct
{
  bool                      active;
  DEVTESTS_CONSOLE_FUNCTION  function;
  XCHAR*                    namefunction;

} DEVTESTS_CONSOLE_LIST_FUNCTION;


typedef struct
{
  int                       index;
  XTHREADCOLLECTED*         thread;
  DEVTESTS_CONSOLE*          devtest_console; 

} DEVTESTS_CONSOLE_XTHREADPARAM;

#define DEVTESTS_CONSOLE_MAXNTHREADS               5


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


class DEVTESTS_CONSOLE : public APPFLOWCONSOLE, public XOBSERVER, public XFSMACHINE
{
  public:
                                    DEVTESTS_CONSOLE                     ();
    virtual                        ~DEVTESTS_CONSOLE                     ();

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

    static bool                     Test_XString                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XBuffer                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XRand                          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XTrace                         (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XLogs                          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XTimer                         (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XVector                        (DEVTESTS_CONSOLE* tests);
  
    bool                            Test_XTree_AddChilds                (XTREE_NODE_TEST* node, int nchild);
    bool                            Test_XTree_InsertChilds             (XTREE_NODE_TEST* node, int indexchild);
    static bool                     Test_XTree                          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XDir                           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XVariant                       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Threads                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DateTime                       (DEVTESTS_CONSOLE* tests);    
    static bool                     Test_DIOStreamTCPIPConnection       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XSystem                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_SharedMemory                   (DEVTESTS_CONSOLE* tests);    
    static bool                     Test_GPIO                           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WebClient                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_ScraperWeb                     (DEVTESTS_CONSOLE* tests);
    static bool                     Test_MPSSE                          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DNSResolver                    (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DNSProtocolMitMServer          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOCheckTCPIPConnections       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WifiEnum                       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WakeOnLAN                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Hash                           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_OneCipher_Simetric             (DEVTESTS_CONSOLE* tests, bool operation, CIPHER* cipher, XBUFFER& input, XBUFFER& result);
    static bool                     Test_Cipher_Simetric                (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Cipher_HKDF                    (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Cipher_AESGCM                  (DEVTESTS_CONSOLE* tests);
    static bool                     Test_CipherFileKeys                 (DEVTESTS_CONSOLE* tests);
    static bool							        Test_CipherRSA				   	          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_CipherECDSAX25519              (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamTCPIP                 (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamTLS                   (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamTLS_KeySchedule       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamTLS_Record            (DEVTESTS_CONSOLE* tests);
    static bool                     Test_SystemCPUUsage                 (DEVTESTS_CONSOLE* tests);
    static bool                     Test_AppAlerts                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_BluetoothEnum                  (DEVTESTS_CONSOLE* tests);
    static bool                     Test_BluetoothLEEnum                (DEVTESTS_CONSOLE* tests);
    static bool                     Test_NTP_Protocol                   (DEVTESTS_CONSOLE* tests);
    static bool                     Test_NTP_InternetServices           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Sound                          (DEVTESTS_CONSOLE* tests);
    static bool                     Test_ProcessManager                 (DEVTESTS_CONSOLE* tests);
    static bool                     Test_GetUserAndDomain               (DEVTESTS_CONSOLE* tests);  
    static bool                     Test_I2C_GPIO_MCP2317               (DEVTESTS_CONSOLE* tests);
    static bool                     Test_SPI_GPIO_MCP2317               (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WifiManagerMode                (DEVTESTS_CONSOLE* tests);
    static bool                     Test_NotificationsManager           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_ATCommandGSM                   (DEVTESTS_CONSOLE* tests);
    static bool                     Test_SNMP                           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XFileJSON                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XFileXML                       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XFileRIFF                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamUSBConnection         (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XFileDFU                       (DEVTESTS_CONSOLE* tests);  
    static bool                     Test_SystemHostFile                 (DEVTESTS_CONSOLE* tests);  
    static bool                     Test_SystemBatteryLevel             (DEVTESTS_CONSOLE* tests);      
    static bool                     Test_LedNeoPixelWS2812B             (DEVTESTS_CONSOLE* tests);  
    static bool                     Test_DIOPCap                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XLicense                       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XSerializable                  (DEVTESTS_CONSOLE* tests);
    static bool                     Test_InputSimulate                  (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Scheduler                      (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DynDNS                         (DEVTESTS_CONSOLE* tests);
    static bool                     Test_ID_IBAN                        (DEVTESTS_CONSOLE* tests);
    static bool                     Test_Compress                       (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DIOStreamTCPIPServer           (DEVTESTS_CONSOLE* tests);
    static bool                     Test_XPath                          (DEVTESTS_CONSOLE* tests);
    
    #ifdef WINDOWS
    static bool                     Test_WindowsACL                     (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WindowsRegistry                (DEVTESTS_CONSOLE* tests);
    static bool                     Test_WindowsWinget                  (DEVTESTS_CONSOLE* tests);
    #endif

    #ifdef LINUX
    static bool                     Test_DBUS                           (DEVTESTS_CONSOLE* tests); 
    static bool                     Test_NetWorkManager                 (DEVTESTS_CONSOLE* tests);
    static bool                     Test_DeviceBusInputFile             (DEVTESTS_CONSOLE* tests);   
    #endif

  private:

    bool                            Test_Hash                           (HASH* HASH, XBUFFER& input, XCHAR* leyend);

    static bool                     Test_DIOStreamTLS_Check             (DEVTESTS_CONSOLE* tests, XCHAR* leyend, XBUFFER& got, XBYTE* expected, XDWORD sizeexpected);
    static bool                     Test_DIOStreamTLS_BuildKeySchedule  (DIOSTREAMTLS13KEYSCHEDULE& keyschedule, DIOSTREAMTLSKEYSCHEDULE_ROLE role);
    static bool                     Test_DIOStreamTLS_SessionIni        (DIOSTREAMTLS13SESSION& session, DIOSTREAMTLSKEYSCHEDULE_ROLE role);

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
