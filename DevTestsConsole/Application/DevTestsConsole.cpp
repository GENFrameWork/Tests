/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole.cpp
* 
* @class      DEVTESTSCONSOLE
* @brief      Developed Tests console class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DevTestsConsole.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XFactory.h"
#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XDir.h"
#include "XRand.h"
#include "XVector.h"
//#include "XVectorSTL.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XFileRIFF.h"
#include "XFileDFU.h"
#include "XFileZIP.h"
#include "XVariant.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XLanguage_ISO_639_3.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XThread.h"
#include "XTrace.h"
#include "XObserver.h"
#include "XSharedMemoryManager.h"
#include "XProcessManager.h"
#include "XLicense.h"
#include "XOrderedList.h"
#include "XSerializable.h"

#include "HashMD5.h"
#include "HashSHA1.h"
#include "HashSHA2.h"
#include "HashWhirlpool.h"
#include "CipherDES.h"
#include "Cipher3DES.h"
#include "CipherAES.h"
#include "CipherBlowfish.h"
#include "CipherKeySymmetrical.h"
#include "CipherKeysFileGKF.h"
#include "CipherKeysFilePEM.h"
#include "CipherTrustedRootCertificatesX509.h"
#include "CipherRSA.h"
#include "CipherECDSAX25519.h"

#include "CompressManager.h"

#include "DIOFactory.h"
#include "DIOStreamConfig.h"
#include "DIOStream.h"
#include "DIOStream_XEvent.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamDeviceWifi.h"
#include "DIOStreamDeviceBluetooth.h"
#include "DIOStreamDeviceBluetoothLE.h"
#include "DIOStreamDeviceUSB.h"
#include "DIOStreamUARTConfig.h"
#include "DIOStreamUART.h"
#include "DIOStreamUSBLocalEnumDevices.h"
#include "DIOStreamUSBConfig.h"
#include "DIOStreamUSB.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"
#include "DIOStreamTCPIPServer.h"
#include "DIOStreamBluetoothLocalEnumDevices.h"
#include "DIOStreamBluetoothRemoteEnumDevices.h"
#include "DIOStreamBluetoothLERemoteEnumDevices.h"
#include "DIOStreamI2CConfig.h"
#include "DIOStreamI2C.h"
#include "DIOI2C_Devices.h"
#include "DIOStreamSPIConfig.h"
#include "DIOStreamSPI.h"
#include "DIOSPI_Devices.h"
#include "DIOStreamTLSConfig.h"
#include "DIOStreamTLS.h"
#include "DIONTP.h"
#include "DIOGPIO.h"
#include "DIOMPSSE.h"
#include "DIODNSProtocol_Client.h"
#include "DIODNSResolver.h"
#include "DIODNSProtocol_MitM_Server_XEvent.h"
#include "DIODNSProtocol_MitM_Server.h"
#include "DIOStreamWifiRemoteEnumDevices.h"
#include "DIOWakeOnLAN.h"
#include "DIONotificationsManager.h"
#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"
#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"
#include "DIOScraperWeb.h"
#include "DIOScraperWebCache.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebMACManufacturer.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebSexName.h"
#include "DIOScraperWebTranslation.h"
#include "DIOScraperWebUserAgentID.h"
#include "DIOScraperWebWeather.h"
#include "DIOWifiManagerMode.h"
#include "DIOATCMDS.h"
#include "DIOATCMDGSM.h"
#include "DIOSNMP.h"
#include "DIOLedNeoPixelWS2812B.h"
#include "DIOAlerts.h"
#include "DIODynDNS_Manager.h"
#include "DIOCoreProtocol_CFG.h"
#include "DIOCoreProtocol_Header.h"
#include "DIOCoreProtocol.h"
#include "DIOCoreProtocol_ConnectionsManager.h"

#ifdef SND_ACTIVE
#include "SNDFactory_XEvent.h"
#include "SNDItem.h"
#include "SNDFactory.h"
#endif

#include "INPFactory.h"
#include "INPSimulate.h"

#include "APPFlowLog.h"
#include "APPFlowCheckResourcesHardware_XEvent.h"
#include "APPFlowCheckResourcesHardware.h"
#include "APPFlowInternetServices.h"
#include "APPFlowAlerts.h"
#include "APPFlowExtended.h"
#include "APPFlowExtended_ApplicationStatus.h"
#include "APPFlowExtended_InternetStatus.h"

#include "ID_IBAN.h"

#ifdef WINDOWS
  #include "XWINDOWSAccessControlLists.h"
  #include "XWINDOWSRegistryManager.h"
  #include "XWINDOWSWinget.h"
  #include "DIOWINDOWSStreamWifiRemoteEnumDevices.h"     
  #include "DevTestsConsole_WindowsPlatform.h"  
  #include "MainProcWINDOWS.h" 
#endif


#ifdef LINUX
  #include "DevTestsConsole_LinuxPlatform.h"
  #include "INPLINUXDeviceID.h"
  #include "DIOLINUXDBus.h"
  #include "DIOLINUXNetworkManager.h"
#endif


#include "DevTestsConsole_CFG.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(DEVTESTSCONSOLE, devtestsconsole)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DEVTESTSCONSOLE::DEVTESTSCONSOLE()
* @brief      Constructor
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCONSOLE::DEVTESTSCONSOLE() : XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DEVTESTSCONSOLE::~DEVTESTSCONSOLE()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    APPLICATION
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCONSOLE::~DEVTESTSCONSOLE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::IniFSMachine()
* @brief      IniFSMachine
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::IniFSMachine()
{
  if(!AddState( DEVTESTSCONSOLE_XFSMSTATE_NONE            ,
                DEVTESTSCONSOLE_XFSMEVENT_INI             , DEVTESTSCONSOLE_XFSMSTATE_INI           ,
                DEVTESTSCONSOLE_XFSMEVENT_END             , DEVTESTSCONSOLE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCONSOLE_XFSMSTATE_INI             ,
                DEVTESTSCONSOLE_XFSMEVENT_UPDATE          , DEVTESTSCONSOLE_XFSMSTATE_UPDATE        ,
                DEVTESTSCONSOLE_XFSMEVENT_END             , DEVTESTSCONSOLE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCONSOLE_XFSMSTATE_UPDATE          ,
                DEVTESTSCONSOLE_XFSMEVENT_NONE            , DEVTESTSCONSOLE_XFSMSTATE_NONE          ,                
                DEVTESTSCONSOLE_XFSMEVENT_END             , DEVTESTSCONSOLE_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCONSOLE_XFSMSTATE_END             ,
                DEVTESTSCONSOLE_XFSMEVENT_NONE            , DEVTESTSCONSOLE_XFSMSTATE_NONE          ,
                DEVTESTSCONSOLE_XFSMEVENT_INI             , DEVTESTSCONSOLE_XFSMSTATE_INI           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::AppProc_PlatformIni()
* @brief      AppProc_PlatformIni
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_PlatformIni()
{
  //--------------------------------------------------------------------------------------
  
  #ifdef WINDOWS
  Windows_Platform_Ini();
  #endif  

  //--------------------------------------------------------------------------------------
  
  #ifdef LINUX
  Linux_Platform_Ini();    
  #endif  
    
  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_Ini()
{
  XSTRING string;
  XSTRING stringresult;
  XPATH   xpathsection;
  XPATH   xpath;
  bool    status = false;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);
  Application_GetExecutable()->Set(APPLICATION_NAMEFILE);

  //--------------------------------------------------------------------------------------------------

  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_SCHEDULER);
  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_DIOSTREAM);
  //ACTIVATEXTHREADGROUP(XTHREADGROUPID_APPOWNER);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS      , APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SOUNDS        , APPFLOW_DEFAULT_DIRECTORY_SOUNDS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_DATABASES     , APPFLOW_DEFAULT_DIRECTORY_DATABASES);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_WEB           , APPFLOW_DEFAULT_DIRECTORY_WEB);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FIRMWARE      , APPFLOW_DEFAULT_DIRECTORY_FIRMWARE);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_CERTIFICATES  , APPFLOW_DEFAULT_DIRECTORY_CERTIFICATES);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  IniFSMachine();

  //--------------------------------------------------------------------------------------

  //Test_DIOWifiManagerMode(this);

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);
  //XTRACE_SETLOCALIPFILTER(172);

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), DEVTESTSCONSOLE_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }

  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA); 

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG, this);

  //--------------------------------------------------------------------------------------
  
  #ifdef SND_ACTIVE

  SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_INI   , &GEN_SNDFACTORY.GetInstance());
  SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PLAY  , &GEN_SNDFACTORY.GetInstance());
  SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE , &GEN_SNDFACTORY.GetInstance());
  SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_STOP  , &GEN_SNDFACTORY.GetInstance());
  SubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_END   , &GEN_SNDFACTORY.GetInstance());

  #endif

  //--------------------------------------------------------------------------------------


  SetEvent(DEVTESTSCONSOLE_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  GEN_XFACTORY_CREATE(xtimerupdateconsole,CreateTimer())
  if(!xtimerupdateconsole) return false;

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_Update()
{
  if(GetEvent()==DEVTESTSCONSOLE_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case DEVTESTSCONSOLE_XFSMSTATE_NONE         : break;

          case DEVTESTSCONSOLE_XFSMSTATE_INI          : SetEvent(DEVTESTSCONSOLE_XFSMEVENT_UPDATE);
                                                        break;

          case DEVTESTSCONSOLE_XFSMSTATE_UPDATE       : switch(GetExitType())
                                                          { 
                                                            case APPFLOWBASE_EXITTYPE_BY_USER : SetEvent(DEVTESTSCONSOLE_XFSMEVENT_END);
                                                                                                APPFLOW_EXTENDED.ShowAll();
                                                                                                break;

                                                            case APPFLOWBASE_EXITTYPE_UNKNOWN : if(xtimerupdateconsole)
                                                                                                  {
                                                                                                    if(xtimerupdateconsole->GetMeasureSeconds() >= 1)
                                                                                                      {
                                                                                                        APPFLOW_EXTENDED.ShowAll();

                                                                                                        xtimerupdateconsole->Reset();
                                                                                                      }
                                                    
                                                                                                    if(console->KBHit())
                                                                                                      {
                                                                                                        //XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[press key]"));

                                                                                                        int key = console->GetChar();
                                                                                                        KeyValidSecuences(key);
                                                                                                      }
                                                                       
                                                                                                    #ifdef DEVTESTSCONSOLE_NOKEY                                                    
                                                                                                    Do_Tests(); 
                                                                                                    #endif                  
                                                                                                  }                                                          
                                                                                                break;
                                                            
                                                              
                                                            
                                                          }
                                                        break;

          case DEVTESTSCONSOLE_XFSMSTATE_END          : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<DEVTESTSCONSOLE_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DEVTESTSCONSOLE_XFSMSTATE_NONE     : break;
              
              case DEVTESTSCONSOLE_XFSMSTATE_INI      : break;
              
              case DEVTESTSCONSOLE_XFSMSTATE_UPDATE   : APPFLOW_EXTENDED.ShowAll();
                                                        break;
                                                        
              case DEVTESTSCONSOLE_XFSMSTATE_END      : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCONSOLE::AppProc_End
* @brief      End Application
* @ingroup
*
* @param
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetEvent(DEVTESTSCONSOLE_XFSMEVENT_END);

  //--------------------------------------------------------------------------------------
  #ifdef SND_ACTIVE

  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_INI   , &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PLAY  , &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE , &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_STOP  , &GEN_SNDFACTORY.GetInstance());
  UnSubscribeEvent(SNDFACTORY_XEVENT_TYPE_SOUND_END   , &GEN_SNDFACTORY.GetInstance());

  #endif


  //--------------------------------------------------------------------------------------

  if(xtimerupdateconsole)
    {
      GEN_XFACTORY.DeleteTimer(xtimerupdateconsole);
      xtimerupdateconsole = NULL;
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();

  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::AppProc_PlatformEnd()
* @brief      AppProc_PlatformEnd
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::AppProc_PlatformEnd()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::KeyValidSecuences(int key)
* @brief      KeyValidSecuences
* @ingroup    APPLICATION
*
* @param[in]  key :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::KeyValidSecuences(int key)
{
  XCHAR character = (XCHAR)key;

  if((character<32) || (character>127)) character = __C('?');
  APPFLOW_LOG_ENTRY(XLOGLEVEL_WARNING, APPFLOW_CFG_LOG_SECTIONID_STATUSAPP, false, __L("Key pressed: 0x%02X [%c]"), key, character);

  console->Printf(__L("\r    \r"));
  console->Printf(__L("\n"));

  switch(key)
    {
      case 0x1B : // ESC Exit application
                  SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                  break;

      #ifndef DEVTESTSCONSOLE_NOKEY
      
      case 'T'  : Do_Tests();
                  break;
      #endif                       
    }


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Show_PlaySound()
* @brief      Show_PlaySound
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Show_PlaySound()
{
  #ifdef SND_ACTIVE

  XTIMER* timer = NULL;
  timer = GEN_XFACTORY.CreateTimer();
  if(!timer) 
    {
      return false;
    }

  for(XDWORD c=0; c<GEN_SNDFACTORY.GetItems()->GetSize(); c++)
    {
      SNDITEM* item = GEN_SNDFACTORY.GetItems()->Get(c);
      if(item)
        {
          XSTRING typestr;  
          XSTRING statusstr;
          XSTRING ntimesstr;
          XSTRING measure;
          XSTRING resorcestr;
                        
          item->GetType(typestr);
          item->GetStatus(statusstr);

          if(item->GetNTimesToPlay() != SNDFACTORY_INLOOP)
            {
              ntimesstr.Format(__L("ntimes [%d of %d]"), (item->GetNTimesToPlay() - item->GetCounterPlay()), item->GetNTimesToPlay());
            }
           else
            {
              ntimesstr.Format(__L("ntimes [infinite]"));
            }   

          timer->Reset();
          timer->AddMilliSeconds(item->GetPlayingTime());
          timer->GetMeasureString(measure);

          resorcestr = item->GetID()->Get();       

          console->Printf(__L("   %02d %-10s %-10s %s %s [%s]\n"), c+1, typestr.Get(), statusstr.Get(), ntimesstr.Get(), measure.Get(), resorcestr.Get());                                       
        }       
    }

  console->Printf(__L("\n"));

  GEN_XFACTORY.DeleteTimer(timer);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Do_Tests()
* @brief      Do_Tests
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Do_Tests()
{
  DEVTESTSCONSOLE_LIST_FUNCTION listfunctions[] = {   { false  , Test_XString                       , __L("Test XString")                         },
                                                      { false  , Test_XBuffer                       , __L("Test XBuffer")                         },
                                                      { false  , Test_XVector                       , __L("Test XVector")                         },
                                                    //{ false  , Test_XVectorSTL                    , __L("Test XVector STL")                     },
                                                      { false  , Test_XRand                         , __L("Test_XRand")                           },
                                                      { false  , Test_XTrace                        , __L("Test XTrace")                          },
                                                      { false  , Test_XLogs                         , __L("Test XLogs")                           },
                                                      { false  , Test_XTimer                        , __L("Test XTimer")                          },
                                                      { false  , Test_XTree                         , __L("Test XTree")                           },
                                                      { false  , Test_XDir                          , __L("Test XDir")                            },
                                                      { false  , Test_XVariant                      , __L("Test XVariant")                        },
                                                      { false  , Test_Threads                       , __L("Test_Threads")                         },
                                                      { false  , Test_DateTime                      , __L("Test_DateTime")                        },                                                      
                                                      { false  , Test_DIOStreamTCPIPConnection      , __L("Test DIOStreamTCPIPConnection")        },
                                                      { false  , Test_XSystem                       , __L("Test System")                          },                                          
                                                      { false  , Test_SharedMemory                  , __L("Test SharedMemory")                    },
                                                      { false  , Test_GPIO                          , __L("Test GPIO")                            },
                                                      { false  , Test_WebClient                     , __L("Test WebClient")                       },
                                                      { false  , Test_ScraperWeb                    , __L("Test Scraper Web")                     },
                                                      { false  , Test_MPSSE                         , __L("Test MPSSE")                           },
                                                      { false  , Test_DNSResolver                   , __L("Test DNS Resolver")                    },
                                                      { false  , Test_DNSProtocolMitMServer         , __L("Test DNS Protocol MitM Server")        },
                                                      { false  , Test_DIOCheckTCPIPConnections      , __L("Test DIOCheckTCPIPConnections")        },
                                                      { false  , Test_WifiEnum                      , __L("Test Wifi Enum")                       },                                          
                                                      { false  , Test_WakeOnLAN                     , __L("Test Wake On LAN")                     }, 
                                                      { false  , Test_Hash                          , __L("Test Hash")                            },
                                                      { false  , Test_Cipher_Simetric               , __L("Test Cipher Simetric")                 }, 
                                                      { false  , Test_CipherFileKeys                , __L("Test Cipher File Keys")                },         
                                                      { false  , Test_CipherRSA                     , __L("Test Cipher RSA")                      },         
                                                      { false  , Test_CipherECDSAX25519              , __L("Test Cipher Curve 25519")              },         
                                                      { false  , Test_DIOStreamTCPIP                , __L("Test DIO Stream TCPIP")                },
                                                      { false  , Test_DIOStreamTLS                  , __L("Test DIO Stream TLS")                  },        
                                                      { false  , Test_SystemCPUUsage                , __L("Test System CPU Usage")                },         
                                                      { false  , Test_AppAlerts                     , __L("Test App Alerts")                      },  
                                                      { false  , Test_BluetoothEnum                 , __L("Test Bluetooth Enum")                  },                                          
                                                      { false  , Test_BluetoothLEEnum               , __L("Test Bluetooth LE Enum")               },                                          
                                                      { false  , Test_NTP_Protocol                  , __L("Test_NTP_Protocol")                    },                                              
                                                      { false  , Test_NTP_InternetServices          , __L("Test_NTP_InternetServices")            },                                              
                                                      { false  , Test_Sound                         , __L("Test Sound")                           },       
                                                      { false  , Test_ProcessManager                , __L("Test Process Manager")                 },
                                                      { false  , Test_GetUserAndDomain              , __L("Test Get User And Domain")             },
                                                      { false  , Test_I2C_GPIO_MCP2317              , __L("Test I2C GPIO MCP2317")                },
                                                      { false  , Test_SPI_GPIO_MCP2317              , __L("Test SPI GPIO MCP2317")                },
                                                      { false  , Test_WifiManagerMode               , __L("Test Wifi Manager Mode")               }, 
                                                      { false  , Test_NotificationsManager          , __L("Test Notifications Manager")           }, 
                                                      { false  , Test_ATCommandGSM                  , __L("Test AT Command GSM ")                 }, 
                                                      { false  , Test_SNMP                          , __L("Test SNMP ")                           },
                                                      { false  , Test_XFileJSON                     , __L("Test XFile JSON")                      },  
                                                      { false  , Test_XFileXML                      , __L("Test XFile XML")                       },  
                                                      { false  , Test_XFileRIFF                     , __L("Test XFile RIFF")                      },
                                                      { false  , Test_DIOStreamUSBConnection        , __L("Test DIOStreamConnection")             },
                                                      { false  , Test_XFileDFU                      , __L("Test XFile DFU")                       },
                                                      { false  , Test_SystemHostFile                , __L("Test System Host File")                },
                                                      { false  , Test_SystemBatteryLevel            , __L("Test System Battery Level")            },
                                                      { false  , Test_LedNeoPixelWS2812B            , __L("Test Led NeoPixel WS2812B")            }, 
                                                      { false  , Test_DIOPCap                       , __L("Test DIO PCap")                        },                                                      
                                                      { false  , Test_XLicense                      , __L("Test XLicense")                        },
                                                      { false  , Test_XSerializable                 , __L("Test XSerializable")                   },
                                                      { false  , Test_InputSimulate                 , __L("Test Input Simulate")                  },
                                                      { false  , Test_Scheduler                     , __L("Test Scheduler")                       },
                                                      { false  , Test_DynDNS                        , __L("Test DynDNS")                          }, 
                                                      { false  , Test_ID_IBAN                       , __L("Test ID IBAN")                         }, 
                                                      { false  , Test_Compress                      , __L("Test Compress")                        }, 
                                                      { false  , Test_DIOStreamTCPIPServer          , __L("Test DIO Stream TCPIP Server")         },  
                                                      { true   , Test_XPath                         , __L("Test eXtended Path")                   },  
                                                      
                                                      #ifdef WINDOWS
                                                      { false  , Test_WindowsACL                    , __L("Test Windows ACL")                     },
                                                      { false  , Test_WindowsRegistry               , __L("Test Windows Registry")                },                                                              
                                                      { false  , Test_WindowsWinget                 , __L("Test Windows WinGet")                  },                                                              
                                                      #endif

                                                      #ifdef LINUX
                                                      { false  , Test_DBUS                          , __L("Test DBUS")                            },
                                                      { false  , Test_NetWorkManager                , __L("Test Network Manager")                 },
                                                      { false  , Test_DeviceBusInputFile            , __L("Test Device Bus Input File")           },
                                                      #endif                                          
                                                  };

  bool status = false;
  
  for(int c=0; c<(sizeof(listfunctions)/sizeof(DEVTESTSCONSOLE_LIST_FUNCTION)); c++)
    {
       if(listfunctions[c].active)
         {
           status = listfunctions[c].function(this);

           devtestsconsole->console->Printf(__L("\n"));
           devtestsconsole->console->Printf(__L("   [%02d] Test %-32s : %s \n"), c, listfunctions[c].namefunction, (status?__L("Ok."):__L("Error!")));
         }
    }

  //--------------------------------------------------------------------------------------------------

  console->PrintMessage(__L(" "), 0, false, true);

  #ifndef DEVTESTSCONSOLE_NOKEY
  console->WaitKey(__L("  Pulsa una tecla para continuar... (%d)"), 1, false, 5);
  #else
  if(!status)
    {
      SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
    }
  #endif
  
  //--------------------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Params_IsModeServer()
* @brief      IsModeServer
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Params_IsModeServer()
{
  bool modeserver = false;

  if(devtestsconsole->GetExecParams())
    {
      XSTRING* param = (XSTRING*)devtestsconsole->GetExecParams()->Get(0);
      if(param)
        {
          if(!param->Compare(__L("SERVER"), true))
            {
              modeserver = true;
            }
        }
    }

  return modeserver;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XString(DEVTESTSCONSOLE* tests)
* @brief      Test_XString
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XString(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  XSTRING string;
  XSTRING substring;

  string = __L("hola radiola");
  string += __L(" mas... ");

  int index = string.Find(__L("mas"), true);
  if(index == XSTRING_NOTFOUND) return false;

  XBUFFER charstr;
  
  string.ConvertToASCII(charstr);
  printf("%s", charstr.GetPtrChar());

  substring.AdjustSize(32);

  string.Format(__L("esto es una prueba %d"), 10);
  string.UnFormat(__L("esto es una %s"), substring.Get());

  substring.AdjustSize();
  
  XVECTOR<XSTRING*> results;

  //string = __L("hola;Radiola;Prueba de example;mas");

  string = __L("[123|321][234|432][hola]");
  string.Split(__C('['), results, false);


  string.Format(__L("Pruebá de %3.2f%%"), 10.11f);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, string.Get());


  XBUFFER xbuffer;

  string.ConvertToASCII(xbuffer);
  substring.Empty();
  substring.ConvertFromASCII(xbuffer);

  string = __L("𠜎𠜱𠝹𠱓𠱸𠲖𠳏𠳕𠴕𠵼𠵿𠸎𠸏𠹷𠺝𠺢𠻗𠻹𠻺𠼭𠼮𠽌𠾴𠾼𠿪");
  substring.Empty();
  string.ConvertToUTF8(xbuffer, false);
  substring.ConvertFromUTF8(xbuffer);

  string = __L("แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช");
  substring.Empty();
  string.ConvertToUTF16(xbuffer);  
  substring.ConvertFromXBuffer(xbuffer, XSTRINGCODING_UTF16);

  string = __L("ᚻᛖ ᚳᚹᚫᚦ ᚦᚫᛏ ᚻᛖ ᛒᚢᛞᛖ ᚩᚾ ᚦᚫᛗ ᛚᚪᚾᛞᛖ ᚾᚩᚱᚦᚹᛖᚪᚱᛞᚢᛗ ᚹᛁᚦ ᚦᚪ ᚹᛖᛥᚫ");
  substring.Empty();
  string.ConvertToUTF32(xbuffer);  
  substring.ConvertFromXBuffer(xbuffer, XSTRINGCODING_UTF32);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XBuffer(DEVTESTSCONSOLE* tests)
* @brief      Test_XBuffer
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XBuffer(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  XBUFFER   buffer;
  XWORD     valueword  = 0;
  XDWORD    valuedword = 0;
  XVARIANT  variant;
  XSTRING   string;
 
  buffer.Resize(32);

  buffer.Set((XBYTE)0x01, 0);
  buffer.Set((XWORD)0x0203, 1);
  buffer.Set((XDWORD)0x55AA55AA, 3);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  buffer.SetWithMask(__L("D"), 3, 0xAAAAAAAA);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  buffer.InsertWithMask(__L("W"), 3, 0xCAFE);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  valueword = 0;
  buffer.GetWithMask(__L("W"), 3, &valueword);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  valueword  = 0;
  valuedword = 0;
  buffer.ExtractWithMask(__L("WD"), 3, &valueword, &valuedword);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  XBYTE array[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
  buffer.InsertWithMask(__L("A8"), 3, array);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  memset(array, 0, sizeof(array));
  buffer.InsertWithMask(__L("AX"), 3, array, sizeof(array));

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  memset(array, 0, sizeof(array));
  buffer.ExtractWithMask(__L("AX"), 3, array, sizeof(array));

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  variant = (XDWORD)10;
  buffer.InsertWithMask(__L("V"), 3, &variant);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  variant = (XDWORD)00;
  buffer.ExtractWithMask(__L("V"), 3, &variant);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  string = __L("hola radiola");
  buffer.InsertWithMask(__L("S"), 3, &string);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  string.Empty();
  buffer.ExtractWithMask(__L("S"), 3, &string);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);
  
  /*
  buffer.Bit_SetNBits(31);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  buffer.Bit_AddData(0xFFFFFFFF);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);

  XDWORD data = buffer.Bit_GetData(0);

  XTRACE_PRINTCOLOR(1, __L("%X"), data);

  data = 0xFFFF55AA;

  buffer.Bit_SetData(data, 0);

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, buffer, 1, 16);
  */

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XRand(DEVTESTSCONSOLE* tests)
* @brief      Test_XRand
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XRand(DEVTESTSCONSOLE* tests)
{
  GEN_XRAND.Ini();

  for(int c=0; c<10; c++)
    {
      int value = GEN_XRAND.Between(0, 10);
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   [%2d] Random value: %d"), c, value);
    }

  for(int c=0; c<10; c++)
    {
      float value = ((float)GEN_XRAND.Between(0, 50) / (float)GEN_XRAND.Between(2, 9));
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   [%2d] Random value: %f"), c, value);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XVector(DEVTESTSCONSOLE* tests)
* @brief      Test_XVector
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XVector(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  /*
  XVECTOR<int>  vector;

  //vector.SetIsMulti(true);

  vector.Add(10);
  vector.Add(50);
  vector.Add(10);

  int number = vector.Get(1);

  vector.Delete(50);

  vector.DeleteAll();
  */

  XVECTOR<XSTRING*>  vector;

  for(int c=0; c<11; c++)
    {
      XSTRING* string = new XSTRING();
      if(string)
        {
          string->Set(__L("hola"));
        }

      vector.Add(string);
    }

  vector.DeleteContents();
  vector.DeleteAll();


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn             bool DEVTESTSCONSOLE::Test_XVectorSTL(DEVTESTSCONSOLE* tests)
* @brief       Test_XVectorSTL
* @ingroup     APPLICATION
* 
* @param[in]   tests : 
* 
* @return         bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
/*
bool DEVTESTSCONSOLE::Test_XVectorSTL(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;
 
  XVECTORSTL<int>  vector;
 
  vector.Add(10);
  vector.Add(50);
  vector.Add(10);

  int number = vector.Get(1);

  vector.Delete(50);

  vector.DeleteAll();

  return true;
}
*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XTrace()
* @brief      Test_XDebugTrace
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XTrace(DEVTESTSCONSOLE* tests)
{
  XDWORD counter = 10;

  if(!tests->console) return false;

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLACK  , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE   , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_GREEN  , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_RED    , __L("[%d] Linea de DEBUG .... "), counter);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_GRAY   , __L("[%d] Linea de DEBUG .... "), counter);

  for(int c=0; c<5000; c++)
    {
      XTRACE_PRINTTAB(c, __L("[%d] Linea de DEBUG .... "), counter);
    }

  for(int c=0; c<5000; c++)
    {
      XTRACE_PRINTCODE(c, __L("[%d] Linea de DEBUG .... "), counter);
    }

  XBUFFER xbuffer;

  for(int c=0; c<1000; c++)
    {
      xbuffer.Add((XBYTE)0xFF);
    }

  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLACK  , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE   , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_GREEN  , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_PURPLE , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_RED    , xbuffer);
  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_GRAY   , xbuffer);


   for(int c=0; c<1000; c++)
    {
      XTRACE_PRINTDATABLOCKTAB(c, xbuffer);
    }

  for(int c=0; c<1000; c++)
    {
      XTRACE_PRINTDATABLOCKCODE(c, xbuffer);
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XLogs(DEVTESTSCONSOLE* tests)
* @brief      Test_XLogs
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XLogs(DEVTESTSCONSOLE* tests)
{
  if(!APPFLOW_CFG.Log_IsActive()) 
    {
      return false;
    }

  XBUFFER  xbuffer;
  XRAND*   xrand = GEN_XFACTORY.CreateRand();
  int      index = 0;

  if(!xrand) return false;

  xrand->Ini();

  for(int d=0; d<100; d++)
    {   
      int ndata = xrand->Between(16, 64);

      for(int c=0; c<100; c++)
        {         
          if(tests->console->KBHit()) break;
            
          xbuffer.Delete();         
          for(int e=0; e<ndata; e++)
            {
              xbuffer.Add((XBYTE)xrand->Max(255));
            }       

          APPFLOW_LOG_ENTRY(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_GENERIC, false, __L("%08d %s"), index, __L("Entrada en memoria del LOG"));          
          APPFLOW_LOG_ENTRY(XLOGLEVEL_INFO, APPFLOW_CFG_LOG_SECTIONID_GENERIC, false, xbuffer);

          index++;
        }     
    }

  GEN_XFACTORY.DeleteRand(xrand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XTimer(DEVTESTSCONSOLE* tests)
* @brief      Test_XTimer
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XTimer(DEVTESTSCONSOLE* tests)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  
  XQWORD  timer_sec1 = 0;
  XQWORD  timer_sec2 = 0;
  XSTRING measure;

  xtimer->AddSeconds(100000000L);  
  timer_sec1 = xtimer->GetMeasureSeconds();

  xtimer->AddSeconds(750000L);
  timer_sec2 = xtimer->GetMeasureSeconds();

  if(xtimer)
    {   
      xtimer->GetMeasureString(measure, true);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XTree_AddChilds(XTREENODE_TEST* node, int nchild)
* @brief      Test_XTree_AddChilds
* @ingroup    APPLICATION
*
* @param[in]  node :
* @param[in]  nchild :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XTree_AddChilds(XTREE_NODE_TEST* node, int nchild)
{
  bool status = true;

  for(int c=0; c<nchild; c++)
    {
      XSTRING* subnodedata = new XSTRING();
      if(subnodedata)
        {
          subnodedata->Format(__L("%2d Child"), c+1);

          XTREE_NODE_TEST* subnode = new XTREE_NODE_TEST(subnodedata);
          if(subnode)
            {
              node->AddChild(subnode);
            }
           else
            {
              status = false;
              break;
            }
        }
       else
        {
          status = false;
          break;
        }
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XTree_InsertChilds(XTREE_NODE_TEST* node, int indexchild)
* @brief      Test_XTree_InsertChilds
* @ingroup    APPLICATION
*
* @param[in]  node :
* @param[in]  indexchild :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XTree_InsertChilds(XTREE_NODE_TEST* node, int indexchild)
{
  XSTRING* subnodedata = new XSTRING();
  if(!subnodedata) return false;

  subnodedata->Format(__L("%2d Insert Child"), indexchild);

  XTREE_NODE_TEST* subnode = new XTREE_NODE_TEST(subnodedata);
  if(subnode)
    {
      Test_XTree_AddChilds(subnode, 5);

      return node->InsertChild(indexchild, subnode);
    }

  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XTree(DEVTESTSCONSOLE* tests)
* @brief      Test_XTree
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XTree(DEVTESTSCONSOLE* tests)
{
  XTREE_TEST        xtree;
  XSTRING*          rootdata  = NULL;
  XTREE_NODE_TEST*  root      = NULL;

  rootdata = new XSTRING();
  if(!rootdata) return false;

  rootdata->Set("Root");

  root = new XTREE_NODE_TEST(rootdata);
  if(!root)
    {
      delete rootdata;
      return false;
    }

  tests->Test_XTree_AddChilds(root, 3);

  for(int c=0; c<root->GetNChildren(); c++)
    {
      XTREE_NODE_TEST* subnode = root->GetChild(c);
      if(subnode)
        {
          tests->Test_XTree_AddChilds(subnode, 2);

          for(int d=0; d<subnode->GetNChildren(); d++)
            {
              XTREE_NODE_TEST* subnode2 = subnode->GetChild(d);
              if(subnode2)
                {
                  if((c == 2) && (d == 0))
                        tests->Test_XTree_InsertChilds(subnode, 1);
                   else tests->Test_XTree_AddChilds(subnode2, 1);
                }
            }
        }
    }

  xtree.SetRoot(root);

  //--------------------------------------------------------
  // Show content

  XTREE_NODE_ITERATOR_TEST  it(xtree.Begin());
  XTREE_NODE_ITERATOR_TEST  it_end(xtree.End());

  while(it != it_end)
    {
      XTREE_NODE_TEST*  node   = it.GetCurrent();
      XSTRING           string;
      if(node)
        {
          if(node->GetLevel())
            {
              XSTRING tabsstr;

              tabsstr.Empty();
              for(int c=0; c<node->GetLevel()-1; c++)
                {
                  tabsstr.Add(__L("  "));
                }

              string.Format(__L("%s|- [%02d]"), tabsstr.Get(), node->GetLevel());
            }

          string.AddFormat(__L("%s"), (*it)->Get());

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%s"), string.Get());          
        }

      ++it;
    }

  //--------------------------------------------------------
  // Delete all

  xtree.DeleteContents();
  xtree.DeleteAll();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_XDir(DEVTESTSCONSOLE* tests)
* @brief      Test_XDir
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XDir(DEVTESTSCONSOLE* tests)
{
  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  if(!xdir) return false;

  XPATH         xpath;
  XDIRELEMENT   element;

  xdir->GetActual(xpath);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Current DIR: [%s]"), xpath.Get());

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
      
  if(xdir->FirstSearch(xpath.Get(), __L("*"), &element))
    {
      do{ XSTRING datetimestr;
              
          element.GetDateTimeFile_LastAccess()->GetDateTimeToString((XDATETIME_FORMAT_ADDDATE | XDATETIME_FORMAT_ADDTIME | XDATETIME_FORMAT_TIMEWITHSECONDS | XDATETIME_FORMAT_TEXTMONTH), datetimestr);

          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Elements DIR: [%s] %s"), element.GetNameFile()->Get(), datetimestr.Get());
           
        } while(xdir->NextSearch(&element));
    }            
    

  GEN_XFACTORY.Delete_Dir(xdir);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XVariant(DEVTESTSCONSOLE* tests)
* @brief      Test_XVariant
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XVariant(DEVTESTSCONSOLE* tests)
{
  XVARIANT variant;
  XBUFFER  buffer;
  XSTRING  string;

  buffer.Add((XBYTE)0xAA);
  buffer.Add((XBYTE)0x55);
  buffer.Add((XBYTE)0xCA);
  buffer.Add((XBYTE)0xFE);
  
  variant = buffer;

  variant.ToString(string);

  buffer.Empty();
  buffer.ConvertFromBase64(string);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_Threads(DEVTESTSCONSOLE* tests)
* @brief      Test_Threads
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Threads(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  DEVTESTSCONSOLE_XTHREADPARAM listthread[DEVTESTSCONSOLE_MAXNTHREADS];
  XTHREADCOLLECTED*            threads[DEVTESTSCONSOLE_MAXNTHREADS];

  memset(listthread , 0, DEVTESTSCONSOLE_MAXNTHREADS * sizeof(DEVTESTSCONSOLE_XTHREADPARAM));
  memset(threads    , 0, DEVTESTSCONSOLE_MAXNTHREADS * sizeof(XTHREADCOLLECTED*));

  tests->xmutexthread = GEN_XFACTORY.Create_Mutex();
  if(!tests->xmutexthread) return false;

  for(int c=0; c<DEVTESTSCONSOLE_MAXNTHREADS; c++)
    {
      threads[c] = CREATEXTHREAD(XTHREADGROUPID_APPOWNER, __L("DEVTESTSCONSOLE::Test_Threads"), ThreadRunFunction, (void*)&listthread[c]);
      if(!threads[c]) return false;    

      listthread[c].index           = c;
      listthread[c].thread          = threads[c];
      listthread[c].devtestconsole  = tests;

      switch(c)
        {        
          case 0  : threads[c]->SetPriority(XTHREADPRIORITY_LOW);       break;
          case 1  : threads[c]->SetPriority(XTHREADPRIORITY_LOW);       break;
          case 2  : threads[c]->SetPriority(XTHREADPRIORITY_LOW);       break;
          case 3  : threads[c]->SetPriority(XTHREADPRIORITY_REALTIME);  break;
          case 4  : threads[c]->SetPriority(XTHREADPRIORITY_LOW);       break;
          default : break;
        }

      threads[c]->Ini();      
    }

  GEN_XSLEEP.Seconds(5);

  for(int c=0; c<DEVTESTSCONSOLE_MAXNTHREADS; c++)
    {
      DELETEXTHREAD(XTHREADGROUPID_APPOWNER, threads[c]);
    }

  GEN_XFACTORY.Delete_Mutex(tests->xmutexthread);  

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_DateTime(DEVTESTSCONSOLE* tests)
* @brief      Test_DateTime
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DateTime(DEVTESTSCONSOLE* tests)
{  
  XSTRING     datetimestring;
  XSTRING     dayofweek;
  XDATETIME*  datetime = GEN_XFACTORY.CreateDateTime();
  if(!datetime) return false;

  // --- Local Date --------------------------------------------------------------------    

  XSTRING function =  GEN_FUNCTION_EXEC;
  XSTRING module   =  GEN_MODULE_EXEC;
  int     line     =  GEN_LINE_EXEC;


  datetime->Read();

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestring);

  datetime->GetDayOfWeekString(dayofweek);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DateTime] Date %s [%s] Number of Week %d, Number of Day: %d"), datetimestring.Get(), dayofweek.Get(), datetime->GetWeekOfYear(), datetime->GetDayOfYear());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DateTime] Date EPOCH: %d"), datetime->GetEPOCHFormat());

  // --- UTC Date -----------------------------------------------------------------------    
  
  datetime->Read(false);

  datetime->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD, datetimestring);  
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DateTime] Date ISO8601 (UTC) %s"), datetimestring.Get());
  
  datetime->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_ISO8601_ADDHOUROFFSET, datetimestring);  
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DateTime] Date ISO8601 (UTC + Offset) %s"), datetimestring.Get());

  // --- File Date ----------------------------------------------------------------------    

  XPATH xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(APPLICATION_NAMEFILE);
  xpath.Add(XFILECFG_EXTENSIONFILE);

  datetime->GetFileDateTime(xpath);
  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestring);
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DateTime] Date %s:%d of the file %s"), datetimestring.Get(), datetime->GetMilliSeconds(), xpath.Get());

  GEN_XFACTORY.DeleteDateTime(datetime);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_DIOStreamTCPIPConnection(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOStreamTCPIPConnection
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOStreamTCPIPConnection(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  DIOSTREAMTCPIPCONFIG diostreamcfg;
  DIOSTREAM*           diostream    = NULL;
  bool                 status       = false;

  diostreamcfg.SetMode(DIOSTREAMMODE_SERVER);
  diostreamcfg.SetRemotePort(23);

  tests->console->Printf(__L("\n\nAbriendo servidor local  %s : %d\n\n"), diostreamcfg.GetLocalIP()->Get(), diostreamcfg.GetRemotePort());

  diostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(diostream)
    {
      int c=0;
      while(!tests->console->KBHit())
        {
          if(diostream->Open())
            {
              status = diostream->WaitToConnected(1);

              tests->console->Printf(__L("\r\nConexion %d estado: %s"), c, status?__L("Connected.       "):__L("Waiting...    "));

              while(diostream->GetStatus()==DIOSTREAMSTATUS_CONNECTED)
                {
                  tests->console->Printf    (__L("\r\n    Sending packet(%d)"), c++);

                  diostream->WriteStr (__L("Hello Jello!\r\n"));
                  diostream->WaitToFlushOutXBuffer();
                }

              if(diostream->GetStatus() !=  DIOSTREAMSTATUS_GETTINGCONNECTION) tests->console->Printf(__L("\r\nConexion %d estado: Disconnected"), c);

              diostream->Close();
              c=0;

              status = true;
            }
        }

      DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_System(DEVTESTSCONSOLE* tests)
* @brief      Test_System
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XSystem(DEVTESTSCONSOLE* tests)
{
  XSTRING   plataform_name;
  XSTRING   OS_ID;
  XSTRING*  BIOSserialnumber;
  XSTRING*  CPUserialnumber;

  GEN_XSYSTEM.GetPlatform(&plataform_name);
  GEN_XSYSTEM.GetOperativeSystemID(OS_ID);

  BIOSserialnumber = GEN_XSYSTEM.GetBIOSSerialNumber();
  CPUserialnumber  = GEN_XSYSTEM.GetCPUSerialNumber();

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   Plataform                :  %s"), plataform_name.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   Operative System Version :  %s"), OS_ID.Get());

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   BIOS serial number       :  %s"), BIOSserialnumber->Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   CPU serial number        :  %s"), CPUserialnumber->Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("   CPU temperature          :  %3.2f Cº"), GEN_XSYSTEM.GetCPUTemperature());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_SharedMemory(DEVTESTSCONSOLE* tests)
* @brief      Test_SharedMemory
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SharedMemory(DEVTESTSCONSOLE* tests)
{
  #define SHAREDMEMORYID __L("SharedMemoryID")

  if(!tests->console) return false;

  bool modeserver = tests->Params_IsModeServer();

  tests->console->Printf(__L("   Creating Shared Memory: %s \n"), (modeserver?__L("[Master]"):__L("[Slave]")));
  
  XBYTE*    pointer = NULL;
  XDWORD    size    = 0;
  XDWORD*   data    = 0;
  bool      status  = true;
  bool      exit    = false;

  if(modeserver)
    {
      size = 32;
      pointer = GEN_XSHAREDMEMORYMANAGER.Create(SHAREDMEMORYID, size);
    }
   else 
    {
      pointer = GEN_XSHAREDMEMORYMANAGER.Open(SHAREDMEMORYID, size);
    }

  tests->console->Printf(__L("   Create Shared Memory %d bytes: %s\n"), size, pointer?__L("Ok"):__L("Error!"));

  data = (XDWORD*)pointer;

  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(xrand)
    {
      if(pointer)
        {
          status = true;  
          
          do{
              if(tests->console->KBHit())
                {
                  switch(tests->console->GetChar())
                    {
                     case 0x1B : 
                                  #ifdef DEVTESTSCONSOLE_NOKEY
                                  tests->SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);     
                                  #endif
                                  exit = true;
                                  break;

                        default : (*data) = (XDWORD)xrand->Max(100000000);              
                                  break;
                    }
                }

              tests->console->Printf(__L("   Data Shared Memory: %04X     \r"), (*data));

            } while(!exit);

          GEN_XSHAREDMEMORYMANAGER.Close();
        }
       else 
        { 
          status = false;
        }

      GEN_XFACTORY.DeleteRand(xrand);
    }

  
  tests->console->Printf(__L("\n   Delete Shared Memory: Ok\n"));

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_GPIO(DEVTESTSCONSOLE* tests)
* @brief      Test_GPIO
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_GPIO(DEVTESTSCONSOLE* tests)
{   
  bool status = false;  

  #ifdef DIOGPIO_ACTIVE
  
  GEN_DIOGPIO.SetMode(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO, DIOGPIO_MODE_OUTPUT);
         
  while(!tests->console->KBHit())
    {
      GEN_DIOGPIO.SetValue(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO, true);
      GEN_XSLEEP.MilliSeconds(50);
             
      GEN_DIOGPIO.SetValue(DEVTESTSCONSOLE_GPIOENTRYID_TESTGPIO, false);
      GEN_XSLEEP.MilliSeconds(50);
    }
          
  status = true;

  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_WebClient(DEVTESTSCONSOLE* tests)
* @brief      Test_WebClient
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WebClient(DEVTESTSCONSOLE* tests)
{
  DIOWEBCLIENT  webclient;
  DIOURL        url;
  XBUFFER       webpage;
  bool          status;

  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER      , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   , &webclient);
  tests->SubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        , &webclient);

  //url = __L("http://ovh.net/files/10Mio.dat");
  url = __L("http://ovh.net/files/1Gio.dat");
  webclient.Set_Port(80);

  status =  webclient.Get(url, webpage, NULL, 60);
  XTRACE_PRINTCOLOR((status?1:4), __L("GET Web Client %s: %s"), url.Get(), status?__L("Ok!"):__L("Error!"));
  if(status)
    {
      XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, webpage);
    }

  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READHEADER      , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   , &webclient);
  tests->UnSubscribeEvent(DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        , &webclient);


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_ScrapersWeb()
* @brief      Test_ScrapersWeb
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_ScraperWeb(DEVTESTSCONSOLE* tests)
{
  DIOSCRAPERWEBPUBLICIP*        publicip        = new DIOSCRAPERWEBPUBLICIP;
  DIOSCRAPERWEBGEOLOCATIONIP*   geolocationip   = new DIOSCRAPERWEBGEOLOCATIONIP;
  DIOSCRAPERWEBSEXNAME*         sexname         = new DIOSCRAPERWEBSEXNAME;
  DIOSCRAPERWEBUSERAGENTID*     useragentID     = new DIOSCRAPERWEBUSERAGENTID;
  DIOSCRAPERWEBTRANSLATION*     translation     = new DIOSCRAPERWEBTRANSLATION;
  DIOSCRAPERWEBMACMANUFACTURER* macmanufactured = new DIOSCRAPERWEBMACMANUFACTURER;
  DIOSCRAPERWEBWEATHER*         weather         = new DIOSCRAPERWEBWEATHER;

  XSTRING localIP;

  localIP = __L("192.168.1.3");

  //webclient->GetProxyURL()->Set(__L("10.155.192.17"));
  //webclient->SetProxyPort(8080);

    for(int c=0; c<10; c++)
      {
        if(publicip)
          {
            DIOIP ip;

            if(publicip->Get(ip, 5, &localIP))
              {
                XSTRING IPstring;

                ip.GetXString(IPstring);

                tests->console->Printf(__L("Public IP : %s\n\n"), IPstring.Get());

                if(geolocationip)
                  {
                    DIOGEOLOCATIONIP_RESULT geoIP;

                    if(geolocationip->Get(ip, geoIP, 5, &localIP))
                      {
                        tests->console->Printf(__L("City         : %s\n"),  geoIP.GetCity());
                        tests->console->Printf(__L("State        : %s\n"),  geoIP.GetState());
                        tests->console->Printf(__L("Contry       : %s\n"),  geoIP.GetCountry());
                        tests->console->Printf(__L("ISP          : %s\n"),  geoIP.GetISP());
                        tests->console->Printf(__L("Organization : %s\n"),  geoIP.GetOrganization());

                      } else tests->console->Printf(__L("Error!!!!\n"));

                    tests->console->Printf(__L("\n"));
                  }
              }
          }

        if(sexname)
          {
            DIOSCRAPERWEBSEXNAMETYPE sextype;
            XSTRING                  name;

            sexname->Get(__L("Alai"), sextype, &name,  5, &localIP);
            tests->console->Printf(__L("El nombre %.15s "), name.Get());

            switch(sextype)
              {
                case DIOSCRAPERWEBSEXNAMETYPE_NOTOBTAINED : tests->console->Printf(__L("no obtenido."));              break;
                case DIOSCRAPERWEBSEXNAMETYPE_NONAME      : tests->console->Printf(__L("no es un nombre propio."));   break;
                case DIOSCRAPERWEBSEXNAMETYPE_MALE        : tests->console->Printf(__L("es de hombre"));              break;
                case DIOSCRAPERWEBSEXNAMETYPE_FEMALE      : tests->console->Printf(__L("es de mujer"));               break;
              }

            tests->console->Printf(__L("\n\n"));
          }

        if(useragentID)
          {
            XSTRING browser;
            XSTRING SO;

            useragentID->Get(__L("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.31 (KHTML, like Gecko) Chrome/26.0.1410.64 Safari/537.31"), browser, SO, 5, &localIP);

            tests->console->Printf(__L("Browser          : %s\n"), browser.Get());
            tests->console->Printf(__L("System Operative : %s\n"), SO.Get());

            tests->console->Printf(__L("\n"));
          }

        if(translation)
          {
            XSTRING        translate;
            XLANGUAGE_CODE languajes[] = {  XLANGUAGE_ISO_639_3_CODE_AFR     , //   Afrikaans
                                            XLANGUAGE_ISO_639_3_CODE_ALB     , //   Albanian
                                            XLANGUAGE_ISO_639_3_CODE_ARA     , //   Arabic
                                            XLANGUAGE_ISO_639_3_CODE_AZE     , //   Azerbaijani
                                            XLANGUAGE_ISO_639_3_CODE_BAQ     , //   Basque
                                            XLANGUAGE_ISO_639_3_CODE_BEL     , //   Belarusian
                                            XLANGUAGE_ISO_639_3_CODE_BEN     , //   Bengali
                                            XLANGUAGE_ISO_639_3_CODE_BUL     , //   Bulgarian
                                            XLANGUAGE_ISO_639_3_CODE_CAT     , //   Catalan
                                            XLANGUAGE_ISO_639_3_CODE_CHI     , //   Chinese    CHINESE_SIMPLIFIED  __L("zh-CN") CHINESE_TRADITIONAL __L("zh-TW")
                                            XLANGUAGE_ISO_639_3_CODE_CZE     , //   Czech
                                            XLANGUAGE_ISO_639_3_CODE_DAN     , //   Danish
                                            XLANGUAGE_ISO_639_3_CODE_DUT     , //   Dutch
                                            XLANGUAGE_ISO_639_3_CODE_ENG     , //   English
                                            XLANGUAGE_ISO_639_3_CODE_EPO     , //   Esperanto
                                            XLANGUAGE_ISO_639_3_CODE_EST     , //   Estonian
                                            XLANGUAGE_ISO_639_3_CODE_FIN     , //   Finnish
                                            XLANGUAGE_ISO_639_3_CODE_FRE     , //   French
                                            XLANGUAGE_ISO_639_3_CODE_GEO     , //   Georgian
                                            XLANGUAGE_ISO_639_3_CODE_GER     , //   German
                                            XLANGUAGE_ISO_639_3_CODE_GLE     , //   Irish
                                            XLANGUAGE_ISO_639_3_CODE_GLG     , //   Galician
                                            XLANGUAGE_ISO_639_3_CODE_GRE     , //   Greek Modern (1453-)
                                            XLANGUAGE_ISO_639_3_CODE_GUJ     , //   Gujarati
                                            XLANGUAGE_ISO_639_3_CODE_HAT     , //   Haitian
                                            XLANGUAGE_ISO_639_3_CODE_HEB     , //   Hebrew
                                            XLANGUAGE_ISO_639_3_CODE_HIN     , //   Hindi
                                            XLANGUAGE_ISO_639_3_CODE_HRV     , //   Croatian
                                            XLANGUAGE_ISO_639_3_CODE_HUN     , //   Hungarian
                                            XLANGUAGE_ISO_639_3_CODE_ICE     , //   Icelandic
                                            XLANGUAGE_ISO_639_3_CODE_IND     , //   Indonesian
                                            XLANGUAGE_ISO_639_3_CODE_ITA     , //   Italian
                                            XLANGUAGE_ISO_639_3_CODE_JPN     , //   Japanese
                                            XLANGUAGE_ISO_639_3_CODE_KAN     , //   Kannada
                                            XLANGUAGE_ISO_639_3_CODE_KOR     , //   Korean
                                            XLANGUAGE_ISO_639_3_CODE_LAT     , //   Latin
                                            XLANGUAGE_ISO_639_3_CODE_LAV     , //   Latvian
                                            XLANGUAGE_ISO_639_3_CODE_LIT     , //   Lithuanian
                                            XLANGUAGE_ISO_639_3_CODE_MAC     , //   Macedonian
                                            XLANGUAGE_ISO_639_3_CODE_MAY     , //   Malay
                                            XLANGUAGE_ISO_639_3_CODE_MLT     , //   Maltese
                                            XLANGUAGE_ISO_639_3_CODE_NOR     , //   Norwegian
                                            XLANGUAGE_ISO_639_3_CODE_PER     , //   Persian
                                            XLANGUAGE_ISO_639_3_CODE_POL     , //   Polish
                                            XLANGUAGE_ISO_639_3_CODE_POR     , //   Portuguese
                                            XLANGUAGE_ISO_639_3_CODE_RUM     , //   Romanian
                                            XLANGUAGE_ISO_639_3_CODE_RUS     , //   Russian
                                            XLANGUAGE_ISO_639_3_CODE_SLO     , //   Slovak
                                            XLANGUAGE_ISO_639_3_CODE_SLV     , //   Slovenian
                                            XLANGUAGE_ISO_639_3_CODE_SPA     , //   Spanish
                                            XLANGUAGE_ISO_639_3_CODE_SRP     , //   Serbian
                                            XLANGUAGE_ISO_639_3_CODE_SWA     , //   Swahili
                                            XLANGUAGE_ISO_639_3_CODE_SWE     , //   Swedish
                                            XLANGUAGE_ISO_639_3_CODE_TAM     , //   Tamil
                                            XLANGUAGE_ISO_639_3_CODE_TEL     , //   Telugu
                                            XLANGUAGE_ISO_639_3_CODE_THA     , //   Thai
                                            XLANGUAGE_ISO_639_3_CODE_TUR     , //   Turkish
                                            XLANGUAGE_ISO_639_3_CODE_UKR     , //   Ukrainian
                                            XLANGUAGE_ISO_639_3_CODE_URD     , //   Urdu
                                            XLANGUAGE_ISO_639_3_CODE_VIE     , //   Vietnamese
                                            XLANGUAGE_ISO_639_3_CODE_WEL     , //   Welsh
                                            XLANGUAGE_ISO_639_3_CODE_YID     , //   Yiddish
                                         };

            XSTRING origin;
          //int     index = 0;

            origin = __L("La mesa de mi casa es roja");
            tests->console->Printf(__L("> %s\n"),origin.Get());

            for(int c=0;c<(sizeof(languajes)/sizeof(int))-1;c++)
              {
                if(translation->Get(origin.Get(), XLANGUAGE_ISO_639_3_CODE_SPA , languajes[c], translate, 5, &localIP))
                  {
                    if(translate.IsValidASCII())
                           tests->console->Printf(__L("> %s\n"),translate.Get());
                      else tests->console->Printf(__L("> (Special chars)\n"));

                    origin = translate.Get();
                    //index = c+1;
                  }
              }

            tests->console->Printf(__L("\n"));
          }

        if(macmanufactured)
          {
            XBYTE    MAC[DIOMAC_MAXSIZE] = { 0x00, 0x04, 0x20, 0x11, 0x22, 0x33 };
            DIOMAC   deviceMAC;
            XSTRING  manufactured;

            deviceMAC.Set(MAC);

            tests->console->Printf(__L("MAC Manufactured: [%02X%02X%02X] "), deviceMAC.Get()[0], deviceMAC.Get()[1], deviceMAC.Get()[2]);

            if(macmanufactured->Get(deviceMAC, manufactured, 5, &localIP))
                  tests->console->Printf(__L("%s")      , manufactured.Get());
             else tests->console->Printf(__L("Unknow"));

            tests->console->Printf(__L("\n"));
          }

        if(weather)
          {
            XSTRING condition;
            float   temperature;
            float   humidity;

            tests->console->Printf(__L("Estado del tiempo: "));

            if(weather->Get(__L("SPXX0016"), true, condition, temperature,  humidity, 5, &localIP))
                    tests->console->Printf(__L("[%s] Temperatura %3.2f, humedad %3.2f%%%%. \n"), condition.Get(), temperature, humidity);
              else  tests->console->Printf(__L("no obtenido.\n"));

            tests->console->Printf(__L("\n"));
          }


      }

  delete publicip;
  delete geolocationip;
  delete sexname;
  delete useragentID;
  delete translation;
  delete macmanufactured;
  delete weather;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_MPSSE(DEVTESTSCONSOLE* tests)
* @brief      Test_FT232H
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_MPSSE(DEVTESTSCONSOLE* tests)
{
  DIOMPSSE* MPSSE = new DIOMPSSE();
  if(!MPSSE)  return false;

  bool status = false;

  if(MPSSE->Open(0))
    {
      tests->console->Printf(__L("   Device found FT%s \n"), MPSSE->GetChipTypeName());

      status = true;

      MPSSE->Close();
    }

  delete MPSSE;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DNSResolver(DEVTESTSCONSOLE* tests)
* @brief      Test_DNSResolver
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DNSResolver(DEVTESTSCONSOLE* tests)
{
  DIOURL  URL;
  DIOIP   ipresolved;
  bool    status      = false;

  //URL = __L("www.google.es");

  URL = __L("members.dyndns.org");

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] Ini ..."),  URL.Get());

  status = GEN_DIODNSRESOLVER.ResolveURL(URL.Get(), ipresolved);
  if(status)
    {
      XSTRING IPstring;

      ipresolved.GetXString(IPstring);

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] IP resuelve %s  (%s) "), URL.Get(), IPstring.Get(), (URL.IsLocalAddress()?__L("Local"):__L("Internet")));

    }
   else
    {
      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DNS Resolve %s] Not Found DNS URL!!!"), URL.Get());
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[DNS Resolve %s] End."), URL.Get());

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DNSProtocolMitMServer(DEVTESTSCONSOLE* tests)
* @brief      Test_DNSProtocolMitMServer
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DNSProtocolMitMServer(DEVTESTSCONSOLE* tests)
{
  bool status = false;
  
  DIODNSPROTOCOL_MITM_SERVER* mitmserver = new DIODNSPROTOCOL_MITM_SERVER();
  if(!mitmserver)
    {
      return status;
    }

  if(mitmserver->Ini())
    {
      tests->console->Printf(__L("  Activate DNS Protocol MitM Server..."));

      tests->SubscribeEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS, mitmserver);
      tests->SubscribeEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ANSWERDNS, mitmserver);
    
  
      if(mitmserver->Activate(true))
        {        
          status = true;

          tests->console->Printf(__L("  [Ok]\n"));  

          while(!tests->console->KBHit())
            {
              GEN_XSLEEP.MilliSeconds(50);  
            }
        }
       else
        {
          tests->console->Printf(__L("  [Error!]\n"));  
        }

      tests->UnSubscribeEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS, mitmserver);
      tests->UnSubscribeEvent(DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ANSWERDNS, mitmserver);
      
      tests->console->Printf(__L("  Deactivate DNS Protocol MitM Server...\n"));    

      mitmserver->End();

      tests->console->GetChar();
    }


  delete mitmserver;  

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_DIOCheckTCPIPConnections(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOCheckTCPIPConnections
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOCheckTCPIPConnections(DEVTESTSCONSOLE* tests)
{
  DIOCHECKINTERNETCONNECTION* checkinternetconnection       = NULL;
  DIOCHECKTCPIPCONNECTIONS*   checkTCPIPconnections         = NULL;
  bool                        status                        = false;

  checkinternetconnection = new DIOCHECKINTERNETCONNECTION(10);
  if(checkinternetconnection)
    {
      //haveinternetconnection = checkinternetconnection->Check();
    }

  checkTCPIPconnections = new DIOCHECKTCPIPCONNECTIONS();
  if(checkTCPIPconnections)
    {
      XDWORD connectionID = 0x55AA55AA;

      status = checkTCPIPconnections->Ini(5, true, true);
      if(status)
        {
          status = checkTCPIPconnections->Connection_Add(__L("172.18.0.1"), connectionID);

          while(!tests->console->KBHit())
            {
              GEN_XSLEEP.Seconds(1);
            }

          checkTCPIPconnections->End();
        }
    }

  if(checkTCPIPconnections)
    {
      delete checkTCPIPconnections;
      checkTCPIPconnections = NULL;
    }


  if(checkinternetconnection)
    {
      delete checkinternetconnection;
      checkinternetconnection = NULL;
    }


  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_WifiEnum(DEVTESTSCONSOLE* tests)
* @brief      Test_WifiEnum
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WifiEnum(DEVTESTSCONSOLE* tests)
{
  bool                            status            = false;
  #ifdef DIOWIFI_ACTIVE
  DIOSTREAMWIFIREMOTEENUMDEVICES* wifiremotedevices = NULL;

  wifiremotedevices = (DIOSTREAMWIFIREMOTEENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_WIFI_REMOTE);
  if(!wifiremotedevices) return false;

  status = wifiremotedevices->Search();

  for(XDWORD c=0; c<wifiremotedevices->GetDevices()->GetSize(); c++)
    {
      DIOSTREAMDEVICEWIFI* devicewifi = (DIOSTREAMDEVICEWIFI*)wifiremotedevices->GetDeviceByIndex(c);
      if(devicewifi) devicewifi->DebugPrintInfo();
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(wifiremotedevices);
  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_WakeOnLAN(DEVTESTSCONSOLE* tests)
* @brief      Test_WakeOnLAN
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WakeOnLAN(DEVTESTSCONSOLE* tests)
{
  DIOWAKEONLAN* wakeonlan = NULL;
  DIOMAC        MAC;
  DIOIP         broadcastIP;
//XBYTE         MACdata[DIOMAC_MAXSIZE] = { 0xC8, 0x7F, 0x54, 0xAE, 0x5C, 0x80 };
  XBYTE         MACdata[DIOMAC_MAXSIZE] = { 0x10, 0xBF, 0x48, 0x78, 0x63, 0x53 };
  bool          status                  = false;

  MAC.Set(MACdata);
  broadcastIP.Set(__L("192.168.0.255"));

  wakeonlan = new DIOWAKEONLAN();
  if(!wakeonlan) return status;

  status = wakeonlan->SendActivation(&MAC, &broadcastIP);

  delete wakeonlan;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_Hash(DEVTESTSCONSOLE* tests)
* @brief      Test_Hash
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Hash(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  XBUFFER  input;
  XSTRING  leyend;
  XSTRING  string;

  string = __L("The quick brown fox jumps over the lazy dog");

  tests->console->Printf(__L("Sentence: \"%s\"\n\n"), string.Get());

  XBUFFER charstr;
  input.Add((XBYTE*)charstr.Get(), charstr.GetSize());

  for(int c=0;c<8;c++)
    {
      HASH* hash = NULL;
      switch(c)
        {
          case  0 :  hash = new HASHCRC32();                    leyend = __L("CRC32");      break;
          case  1 :  hash = new HASHMD5();                      leyend = __L("MD5");        break;
          case  2 :  hash = new HASHSHA1();                     leyend = __L("SHA1");       break;
          case  3 :  hash = new HASHSHA2(HASHSHA2TYPE_224);     leyend = __L("SHA2 224");   break;
          case  4 :  hash = new HASHSHA2(HASHSHA2TYPE_256);     leyend = __L("SHA2 256");   break;
          case  5 :  hash = new HASHSHA2(HASHSHA2TYPE_384);     leyend = __L("SHA2 384");   break;
          case  6 :  hash = new HASHSHA2(HASHSHA2TYPE_512);     leyend = __L("SHA2 512");   break;
          case  7 :  hash = new HASHWHIRLPOOL();                leyend = __L("Whirpool");   break;
        }

      if(!hash) return false;

      tests->Test_Hash(hash, input, leyend.Get());
      delete hash;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_OneCipher_Simetric(DEVTESTSCONSOLE* tests, bool operation, CIPHER* cipher, XBUFFER& input, XBUFFER& output)
* @brief      Test_OneCipher_Simetric
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* @param[in]  operation : 
* @param[in]  cipher : 
* @param[in]  input : 
* @param[in]  output : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_OneCipher_Simetric(DEVTESTSCONSOLE* tests, bool operation, CIPHER* cipher, XBUFFER& input, XBUFFER& output)
{
	if(!cipher) return false;

	bool status = operation?cipher->Cipher(input):cipher->Uncipher(input);
	
	if(!status)
		{
			tests->console->Printf(__L("Error!\n"));	
			return false;
		}

  output.CopyFrom((*cipher->GetResult()));

	for(int c=0;c<(int)(output.GetSize());c++)
		{
			tests->console->Printf(__L("%02X"), output.GetByte(c));
		}
		
	tests->console->Printf(__L("\n"));

	return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_Cipher_Simetric(DEVTESTSCONSOLE* tests)
* @brief      Test_Cipher_Simetric
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Cipher_Simetric(DEVTESTSCONSOLE* tests)
{
  XBUFFER								input;
  XBUFFER								output;
	XSTRING								leyend;
	CIPHERKEYSYMMETRICAL  key;	  
  bool                  status      = false;
	
	XBYTE									inivector[]	= { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
	XBYTE									inputdata[]	= { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a, 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
  XBYTE									keydata[]		= { 0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe, 0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81, 0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7, 0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4 }; // { 0x8e, 0x73, 0xb0, 0xf7, 0xda, 0x0e, 0x64, 0x52, 0xc8, 0x10, 0xf3, 0x2b, 0x80, 0x90, 0x79, 0xe5, 0x62, 0xf8, 0xea, 0xd2, 0x52, 0x2c, 0x6b, 0x7b }; // { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };  

	
	key.Set(keydata, sizeof(keydata));	

  tests->console->Printf(__L("Plain text:  "));

	for(int c=0; c<(int)(sizeof(inputdata)); c++)
		{
			tests->console->Printf(__L("%02X"), inputdata[c]);
		}

  tests->console->Printf(__L("\n\n"));

 
	for(int c=0;c<5;c++)
		{
			CIPHER*		cipher = NULL;
			switch(c)
				{
					case  0 :  cipher = new CIPHER();						leyend = __L("XOR (base)");	  break;
					case  1 :  cipher = new CIPHERDES();				leyend = __L("DES");			    break;
					case  2 :  cipher = new CIPHER3DES();				leyend = __L("3DES");			    break;										
					case  3 :  cipher = new CIPHERAES();				leyend = __L("AES");			    break;	
					case  4 :  cipher = new CIPHERBLOWFISH();		leyend = __L("Blowfish");	    break;						
				}
					
			if(cipher) 
				{
					cipher->SetChainingMode(CIPHERCHAININGMODE_CBC);				
					cipher->SetPaddingType(XBUFFER_PADDINGTYPE_ZEROS); 
					cipher->SetInitVector(inivector,sizeof(inivector));			

					cipher->SetKey(&key);

          input.Empty();
          input.Add((XBYTE*)inputdata, sizeof(inputdata));

          tests->console->Printf(__L("[ %s ]\n"), leyend.Get());
          tests->console->Printf(__L("  Cipher   : "));
					status = Test_OneCipher_Simetric(tests, true, cipher, input, output);
          if(!status) break;

          input.Empty();

          tests->console->Printf(__L("  Uncipher : "));
          status = Test_OneCipher_Simetric(tests, false, cipher, output, input);        
          tests->console->Printf(__L("\n"));

          if(!status) break;

					delete cipher;
				}
		}

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_CipherFileKeys(DEVTESTSCONSOLE* tests)
* @brief      Test_CipherFileKeys
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_CipherFileKeys(DEVTESTSCONSOLE* tests)
{
  CIPHERTRUSTEDROOTCERTIFICATESX509 trustedrootcertificates; 
  XPATH		                          xpathgeneric;	
	XPATH	 	                          xpath;
  XPATH	 	                          xpathtarget;
  bool                              status = false;
	
	XPATHSMANAGER::GetInstance().GetPathOfSection(XPATHSMANAGERSECTIONTYPE_CERTIFICATES, xpathgeneric);
//xpath.Create(3 , xpathgeneric.Get(), __L("root")    , CIPHERKEYSFILEPEM_EXT);	
  xpath.Create(3 , xpathgeneric.Get(), __L("cacert")  , CIPHERKEYSFILEPEM_EXT);	 
//xpath.Create(3 , xpathgeneric.Get(), __L("certificate"), CIPHERKEYSFILEKEY_EXT);	
//xpath.Create(2 , xpathgeneric.Get(), __L("certificate.ca.crt"));	
//xpath.Create(2 , xpathgeneric.Get(), __L("id_rsa"));
 

xpathtarget.Create(3 , xpathgeneric.Get(), __L("cacert")  , __L(".h"));	

//status = trustedrootcertificates.GenerateEmbeddedHeadere(&xpath, &xpathtarget);

	CIPHERKEYSFILEPEM* filekeys = new CIPHERKEYSFILEPEM();	
  if(filekeys) 
    {
      status = true;
    }

  if(status)
    {     
      //if(trustedrootcertificates.ReadFromFile(&xpath))
        {
          filekeys->DecodeCertificates(trustedrootcertificates.GetLines());
        }
    }

  delete filekeys;

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_CipherRSA(DEVTESTSCONSOLE* tests)
* @brief      Test_CipherRSA
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_CipherRSA(DEVTESTSCONSOLE* tests)
{
  CIPHERRSA* cipher = new CIPHERRSA();
	if(!cipher) return false; 

  bool status = false;
	
	XPATH	 	 xpath;
	XPATH		 xpathgeneric;	

	XPATHSMANAGER::GetInstance().GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathgeneric);
	xpath.Create(3 , xpathgeneric.Get(), __L("keys"), CIPHERKEYSFILEGKF_EXT);	
	
	CIPHERKEYSFILEGKF*		filekeys   = new CIPHERKEYSFILEGKF(xpath);	
	CIPHERKEYPUBLICRSA*		publickey  = NULL;
	CIPHERKEYPRIVATERSA*	privatekey = NULL;		
		
	publickey  = (CIPHERKEYPUBLICRSA*)filekeys->GetKey(CIPHERKEYTYPE_RSA_PUBLIC);
	privatekey = (CIPHERKEYPRIVATERSA*)filekeys->GetKey(CIPHERKEYTYPE_RSA_PRIVATE);

	if(!publickey || !privatekey)
		{
			status = false;

		} else status = true;

	XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Load RSA keys : %s"), (status?__L("Ok."):__L("Fail.")));	
	
	if(status)
	  {
      XBUFFER input;
      XBYTE   inputdata[]	= "Esta es una prueba de un texto largo para ser encriptado usando la RSA. La prueba consiste en que sea mas largo que la clave, osea mas de 128 bytes de largo, y que ademas tenga una longitud que no sea complemento de 2, para que queden bien los Paddings internos de la funcion. Pues eso. se acabo el rollo de pollo.";

      input.Delete();
	    input.Add((XBYTE*)inputdata, sizeof(inputdata));

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Data to cipher:"));	
      XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, input);

      status = false;
  
	    if(cipher->SetKey(publickey))
		    {
			    if(cipher->SetKey(privatekey)) 
				    {					
					    if(cipher->Cipher(input, CIPHERKEYTYPE_RSA_PRIVATE))
						    {
                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Data cipher:"));	
                  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, (*cipher->GetResult()));

							    cipher->Uncipher((*cipher->GetResult()), CIPHERKEYTYPE_RSA_PUBLIC); 
						    }

					    status = input.Compare(cipher->GetResult());						  
				    }
		    }
    }
		
	XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Test RSA keys : %s"), (status?__L("Ok."):__L("Fail.")));	

	delete filekeys;
	
	delete cipher;

	return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_CipherECDSAX25519(DEVTESTSCONSOLE* tests)
* @brief      Test_CipherECDSAX25519
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_CipherECDSAX25519(DEVTESTSCONSOLE* tests)
{
  CIPHERECDSAX25519  curve25519[2];
  bool              status           = false; 

  for(int c=0; c<2; c++)
    {
      status = curve25519[c].GenerateRandomPrivateKey();
      
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Curve 25519 Private key %d: %s" ), c+1,  status?__L("Ok"):__L("Error!")); 
      XTRACE_PRINTDATABLOCKCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), curve25519[c].GetKey(CIPHERECDSAX25519_TYPEKEY_PRIVATE), 32, 1, 32); 

      if(!status) break;

      status = curve25519[c].CreatePublicKey();

      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Curve 25519 Public  key %d: %s" ), c+1,  status?__L("Ok"):__L("Error!")); 
      XTRACE_PRINTDATABLOCKCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), curve25519[c].GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC), 32, 1, 32);    

      if(!status) break;     
    }

  if(status)
    {   
      curve25519[0].CreateSharedKey(curve25519[1].GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC));
      curve25519[1].CreateSharedKey(curve25519[0].GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC));

      for(int c=0; c<2; c++)
        {    
          status = curve25519[c].GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED)?true:false;

          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Curve 25519 Shared  key %d: %s" ), c+1,  status?__L("Ok"):__L("Error!")); 
          if(status) 
            {
              XTRACE_PRINTDATABLOCKCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), curve25519[c].GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED), 32, 1, 32);         
            }

          if(!status) break;
        }
     
      if(status)
        {      
          for(int c=0; c<CIPHERECDSAX25519_MAXKEY; c++)
            {
              if(curve25519[0].GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED)[c] != curve25519[1].GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED)[c]) status = false;
            }

          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Curve 25519 Shared  Key are equal : %s"), status?__L("Ok"):__L("Error!")); 
        }

    }

  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Curve 25519 All generated : %s"), status?__L("Ok"):__L("Error!")); 

  return status ;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DIOStreamTCPIP(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOStreamTCPIP
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOStreamTCPIP(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  DIOSTREAMTCPIPCONFIG  diostreamcfg;
  DIOSTREAM*            diostream    = NULL;
  XSTRING               line;
  bool                  status       = false;

  diostreamcfg.GetRemoteURL()->Set(__L("endorasoft.com"));
  diostreamcfg.SetMode(DIOSTREAMMODE_CLIENT);
  diostreamcfg.SetRemotePort(25);

  line.Format(__L("Server [%s]: %d"), diostreamcfg.GetRemoteURL()->Get(), diostreamcfg.GetRemotePort());
  tests->console->Printf(__L("   %s\n"), line.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

  diostream = GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(!diostream) return false;
  
  if(diostream->Open())
    {
      status = diostream->WaitToConnected(5);

      line.Format(__L("Connection status: %s"), status?__L("Connected."):__L("No connected."));  
      tests->console->Printf(__L("   %s\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());            

      if(status)
        {       
          XBUFFER buffer;
          XDWORD  size = 0;
        
          buffer.Resize(100);

          status = diostream->WaitToFilledReadingBuffer(30, 5);
          if(status)
            {
              size = diostream->Read(buffer);
            }

          line.Format(__L("Read: %d bytes"), size);  
          tests->console->Printf(__L("   %s\n"), line.Get());
          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());             
        }
  
      status = diostream->Close();

      line.Format(__L("Close connection: %s"), status?__L("Ok."):__L("Error!"));  
      tests->console->Printf(__L("   %s\n\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());                                 
    }

  GEN_DIOFACTORY.DeleteStreamIO(diostream);
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_DIOStreamTLS(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOStreamTLS
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOStreamTLS(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) 
    {
      return false;
    }

  CIPHERTRUSTEDROOTCERTIFICATESX509 trustedrootcertificates;
  CIPHERKEYSFILEPEM                 filekeys;
  DIOSTREAMTLSCONFIG                diostreamcfg;
  DIOSTREAM*                        diostream    = NULL;
  XSTRING                           line;
  bool                              status       = false;
	XPATH		                          xpathgeneric;	
  XPATH	 	                          xpath;

	XPATHSMANAGER::GetInstance().GetPathOfSection(XPATHSMANAGERSECTIONTYPE_CERTIFICATES, xpathgeneric);
  xpath.Create(3 , xpathgeneric.Get(), __L("root"), CIPHERKEYSFILEPEM_EXT);	

  //filekeys.DecodeCertificates(trustedrootcertificates.GetLines());

  diostreamcfg.GetRemoteURL()->Set(__L("www.google.es"));
  diostreamcfg.SetMode(DIOSTREAMMODE_CLIENT);
  diostreamcfg.SetRemotePort(443);
  diostreamcfg.SetIsTLS(true);

  line.Format(__L("Server [%s]: %d"), diostreamcfg.GetRemoteURL()->Get(), diostreamcfg.GetRemotePort());
  tests->console->Printf(__L("   %s\n"), line.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

  diostream = GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(!diostream) 
    {
      return false;
    }

  status = diostream->Open();
  if(status)
    {
      line.Format(__L("Connection status: %s"), status?__L("Connected."):__L("No connected."));  
      tests->console->Printf(__L("   %s\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());            
    }

  while(!diostream->IsDisconnected())  
    {
      if(tests->console->KBHit())
        {
          break;
        } 
       else
        { 
          GEN_XSLEEP.MilliSeconds(10);
        }
    }

              
  status = diostream->Close();

  line.Format(__L("Close connection: %s"), status?__L("Ok."):__L("Error!"));  
  tests->console->Printf(__L("   %s\n\n"), line.Get());
  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());                                 
    

  delete diostream;
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_SystemCPUUsage(DEVTESTSCONSOLE* tests)
* @brief      Test_SystemCPUUsage
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SystemCPUUsage(DEVTESTSCONSOLE* tests)
{
  XSTRING nameapp;

  #ifdef WINDOWS
  nameapp = __L("tests.exe");
  #endif

  #ifdef LINUX
  nameapp = __L("tests");
  #endif


  while(!tests->console->KBHit())
    {      
      tests->console->Clear();

      tests->console->Printf(__L("   CPU usage %-16s : [%3d%%]       \n"), __L("Total"), GEN_XSYSTEM.GetCPUUsageTotal());                                                                                             
      tests->console->Printf(__L("   CPU usage %-16s : [%3d%%]       \n"), APPLICATION_NAMEAPP, GEN_XSYSTEM.GetCPUUsageForProcessName(nameapp.Get()));       

      /*
      for(int d=0; d<10; d++)
        {            
          for(int c=0; c<100000000; c++)
            {
               int a = 0;
               a++;
            }
        }
       */

      GEN_XSLEEP.Seconds(1);

    }

  tests->console->GetChar();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_AppAlerts(DEVTESTSCONSOLE* tests)
* @brief      Test_AppAlerts
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_AppAlerts(DEVTESTSCONSOLE* tests)
{
  int status[APPFLOW_ALERT_TYPE_MAX];
  int result = false;

  if(GEN_APPFLOWALERTS.Ini(&APPFLOW_CFG.GetInstance() , APPLICATION_NAMEAPP 
                                                      , APPLICATION_VERSION
                                                      , APPLICATION_SUBVERSION
                                                      , APPLICATION_SUBVERSIONERR
                                                      , status
                                                      , NULL))
    {
      int result;
      
      result = GEN_APPFLOWALERTS.Send((DIOALERTSSENDER_SMPT | DIOALERTSSENDER_WEB), DIOALERTS_CONDITIONS_ID_GENINTERN_TEST,  DIOALERTLEVEL_SERIOUS, __L("Aterta TEST"), __L("Esto es una prueba de Alerta."));
      if(result) result = GEN_APPFLOWALERTS.Send((DIOALERTSSENDER_SMPT | DIOALERTSSENDER_WEB), DIOALERTS_CONDITIONS_ID_GENINTERN_TEST,  DIOALERTLEVEL_SERIOUS, __L("Aterta TEST"), __L("Esto es una prueba de Alerta 2."));
  
      GEN_APPFLOWALERTS.End();
    }

  GEN_APPFLOWALERTS.DelInstance();

  return result;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_BluetoothEnum(DEVTESTSCONSOLE* tests)
* @brief      Test_BluetoothEnum
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_BluetoothEnum(DEVTESTSCONSOLE* tests)
{
  #ifdef DIO_STREAMBLUETOOTH_ACTIVE

  DIOSTREAMENUMDEVICES* enumdevicesremote = NULL;

  enumdevicesremote = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_BLUETOOTH_REMOTE);
	if(enumdevicesremote)
	  {					
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Start Search sensors ... ")); 

      XTIMER*  xtimer;

      xtimer = GEN_XFACTORY.CreateTimer();

		  enumdevicesremote->Search();

		  xtimer->Reset();

			while(enumdevicesremote->IsSearching())
        {
          if(tests->console->KBHit()) break;          
				  XSLEEP::GetInstance().MilliSeconds(10);          
				}
					
			for(int c=0;c<(int)enumdevicesremote->GetDevices()->GetSize();c++)
			  {					
				  DIOSTREAMDEVICEBLUETOOTH* devicesearch = (DIOSTREAMDEVICEBLUETOOTH*)enumdevicesremote->GetDevices()->Get(c);
					if(devicesearch) 
						{	
              XSTRING MACstring; 

              devicesearch->GetMAC()->GetXString(MACstring);

              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("  Sensor [MAC %s] %s"), MACstring.Get(), devicesearch->GetName()->Get()); 
            }
        }

       XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("End Search sensors ... ")); 

      GEN_XFACTORY.DeleteTimer(xtimer);
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesremote);			

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_BluetoothLEEnum(DEVTESTSCONSOLE* tests)
* @brief      Test_BluetoothLEEnum
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_BluetoothLEEnum(DEVTESTSCONSOLE* tests)
{
  #ifdef DIO_STREAMBLUETOOTHLE_ACTIVE

  DIOSTREAMENUMDEVICES* enumdevicesremote = NULL;

  enumdevicesremote = GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_BLUETOOTHLE_REMOTE);
	if(enumdevicesremote)
	  {					
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Start Search sensors ... ")); 

      XTIMER*  xtimer;

      xtimer = GEN_XFACTORY.CreateTimer();

		  enumdevicesremote->Search();

		  xtimer->Reset();

			while(enumdevicesremote->IsSearching())
        {
          if(tests->console->KBHit()) break;          
				  XSLEEP::GetInstance().MilliSeconds(10);          
				}
					
      enumdevicesremote->StopSearch(false);
   

			for(int c=0;c<(int)enumdevicesremote->GetDevices()->GetSize();c++)
			  {					
				  DIOSTREAMDEVICEBLUETOOTHLE* devicesearch = (DIOSTREAMDEVICEBLUETOOTHLE*)enumdevicesremote->GetDevices()->Get(c);
					if(devicesearch) 
						{	
              XSTRING   MACstring; 
              XTIMER*   lastscantimer = devicesearch->GetLastScanTimer();
              XSTRING   lastscanmeasurestring;

              lastscantimer->GetMeasureString(lastscanmeasurestring, false);  
              devicesearch->GetMAC()->GetXString(MACstring);
              
              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("  Sensor [MAC %s] %d last scan: %s"), MACstring.Get(), devicesearch->GetRSSI(), lastscanmeasurestring.Get()); 
            }
        }

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("End Search sensors ... ")); 

      GEN_XFACTORY.DeleteTimer(xtimer);
    }

  GEN_DIOFACTORY.DeleteStreamEnumDevices(enumdevicesremote);			

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_NTP_Protocol(DEVTESTSCONSOLE* tests)
* @brief      Test_NTP_Protocol
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_NTP_Protocol(DEVTESTSCONSOLE* tests)
{
  XDATETIME*  xdatetime_local = NULL;
  DIONTP*     ntp             = NULL;
  DIOURL      url;     
  bool        status          = false;  
  
  ntp = new DIONTP();
  if(!ntp)
    {
      return status;   
    }

  GEN_XFACTORY_CREATE(xdatetime_local, CreateDateTime())
  if(xdatetime_local) 
    {
      xdatetime_local->Read();
    }
   else
    {
      delete ntp;
      return status;
    }

  //__L("1.es.pool.ntp.org"); 
  //__L("1.europe.pool.ntp.org"); 
  //__L("3.europe.pool.ntp.org"); 

  url = __L("1.es.pool.ntp.org");

  xdatetime_local->Read();

  status = ntp->GetTime(url, DIONTP_DEFAULTTIMEOUT, GEN_XSYSTEM.HardwareUseLittleEndian(), (*xdatetime_local));
         
  delete ntp;

  GEN_XFACTORY.DeleteDateTime(xdatetime_local);
   
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_NTP_InternetServices(DEVTESTSCONSOLE* tests)
* @brief      Test_NTP_InternetServices
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_NTP_InternetServices(DEVTESTSCONSOLE* tests)
{ 
  bool                      status      = false; 

  #ifdef APPFLOW_EXTENDED_INTERNETSTATUS_ACTIVE

  XDATETIME*                datetime1;
  XDATETIME*                datetime2;
  XSTRING                   datetimestr;
  APPFLOWINTERNETSERVICES*  appinternetservices = NULL;
  

  if(APPFLOW_EXTENDED.GetInternetStatus())
    {
      appinternetservices = APPFLOW_EXTENDED.GetInternetStatus()->GetInternetServices();
    }

  if(appinternetservices) 
    {
      return false;
    }

  //while(!tests->console->KBHit())
    {
      int hours = 0;

      datetime1 = appinternetservices->DateTime_GetLocal();
      if(datetime1)
        {    
          datetime1->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[NTP] Date Time Local : %s"), datetimestr.Get()); 

          datetime1->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[NTP] Date Time Local ISO8601: %s"), datetimestr.Get()); 

          status = true;
        }

      datetime2 = appinternetservices->DateTime_GetUTC();
      if(datetime2)
        {    
          datetime2->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[NTP] Date Time UTC : %s"), datetimestr.Get()); 

          datetime2->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[NTP] Date Time UTC ISO8601 : %s"), datetimestr.Get());       

          datetime2->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_ISO8601_ADDHOUROFFSET, datetimestr);
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[NTP] Date Time UTC + offset ISO8601  : %s"), datetimestr.Get());       
          
          status = true;
        }

     GEN_XSLEEP.MilliSeconds(100);
    } 

  
  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_Sound(DEVTESTSCONSOLE* tests)
* @brief      Test_Sound
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Sound(DEVTESTSCONSOLE* tests)
{  
  bool        status = false; 

  #ifdef SND_ACTIVE

  SNDPLAYCFG  playCFG;
  SNDITEM*    item[]   = { NULL, NULL, NULL }; 
  SNDITEM*    itemfile = NULL; 
  XPATH       xpath;
 

  if(!GEN_SNDFACTORY.IsSoundActive())
    {
      tests->console->Printf(__L("   Sound system: no avaible (no active) !!!)\n"));

      return status;
    }
   
  if(!GEN_XSYSTEM.Sound_SetLevel(90)) 
    {
      return false;
    }
      
  GEN_XSLEEP.MilliSeconds(100);
    
  status = true;

  //-------------------------------------------------------------------------

  item[0] = GEN_SNDFACTORY.CreateItem(640 , 3000);
  item[1] = GEN_SNDFACTORY.CreateItem(1000, 3000);
  item[2] = GEN_SNDFACTORY.CreateItem(850 , 3000); 


  GEN_SNDFACTORY.Sound_Play(item[0], &playCFG, SNDFACTORY_INLOOP);   
  GEN_SNDFACTORY.Sound_WaitToEnd(item[0], SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);  

  GEN_SNDFACTORY.Sound_Pause(item[0]);
 
  APPFLOW_EXTENDED.ShowAll();
  tests->Show_PlaySound();  

  GEN_XSLEEP.Seconds(3); 
  
  GEN_SNDFACTORY.Sound_Play(item[0], &playCFG, SNDFACTORY_INLOOP); 
  GEN_SNDFACTORY.Sound_WaitToEnd(item[0], SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);  

  GEN_SNDFACTORY.Sound_Stop(item[0]);
  
  APPFLOW_EXTENDED.ShowAll();
  tests->Show_PlaySound();   
 
    
  for(XDWORD c=0; c<sizeof(item)/sizeof(SNDITEM*); c++)
    {
      GEN_SNDFACTORY.Sound_Play(item[c], &playCFG);      
    }

  GEN_SNDFACTORY.Sound_WaitAllToEnd(SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);
  
  
  GEN_SNDFACTORY.MasterVolume_Set(50);

  playCFG.SetVolume(100);

  GEN_SNDFACTORY.Sound_Play(item[0], &playCFG); 

  int volume = GEN_SNDFACTORY.Sound_GetVolume(item[0]);
  
  GEN_SNDFACTORY.Sound_WaitAllToEnd(SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);
          
  GEN_SNDFACTORY.DeleteAllItems();
  
    
  //-------------------------------------------------------------------------
  
  
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SOUNDS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("alarm.ogg"));

  itemfile = GEN_SNDFACTORY.CreateItem(xpath);
        
  GEN_SNDFACTORY.Sound_Play(itemfile, &playCFG, 3);    
  
  GEN_SNDFACTORY.Sound_WaitAllToEnd(SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);

  GEN_SNDFACTORY.DeleteAllItems();
  
  //-------------------------------------------------------------------------
  
  
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SOUNDS, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("imperialmarch60.wav"));

  itemfile = GEN_SNDFACTORY.CreateItem(xpath);
        
  GEN_SNDFACTORY.Sound_Play(itemfile, &playCFG);    
  
  GEN_SNDFACTORY.Sound_WaitAllToEnd(SNDFACTORY_MAXTIMEOUT_INFINITE, Test_WaitSound);

  GEN_SNDFACTORY.DeleteAllItems();
  

  //-------------------------------------------------------------------------

  #endif

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_ProcessManager(DEVTESTSCONSOLE* tests)
* @brief      Test_ProcessManager
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_ProcessManager(DEVTESTSCONSOLE* tests)
{
  XSTRING             command;
  XSTRING             params; 
  XSTRING             in;
  XSTRING             out;
//int                 returncode;
  XVECTOR<XPROCESS*>  applist;
  
  /*
  command = __L("/usr/bin/festival");
  params  = __L("--language spanish --tts");
  in      = __L("Hola radiola");
 
  bool status = GEN_XPROCESSMANAGER.Application_Execute(command.Get(), params.Get(), &in, NULL, &returncode);

  */

  /*
  command = __L("D:\\depen dencies\\net-tools\\bin\\snmpwalk");
  params  = __L("");
  
  bool status = GEN_XPROCESSMANAGER.Application_Execute(command.Get(), params.Get(), &in, &out, &returncode);


  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Exec: %s "), (status?__L("Ok"):__L("Error!")));
  */

  bool status = GEN_XPROCESSMANAGER.Application_GetRunningList(applist);

  if(status)
    {

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("-- Applications ------------------------------------------------------------------"));        
      for(XDWORD c=0; c<applist.GetSize(); c++)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("%04d    ID    : %d"), c, applist.Get(c)->GetID());        
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("        Path  : %s")   , applist.Get(c)->GetPath()->Get());        
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("        Name  : %s")   , applist.Get(c)->GetName()->Get());  
          if(!applist.Get(c)->GetWindowTitle()->IsEmpty())
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_PURPLE, __L("        Title : [%s]")    , applist.Get(c)->GetWindowTitle()->Get());                     
            }
        }
    }
    
  applist.DeleteContents();
  applist.DeleteAll();

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_GetUserAndDomain(DEVTESTSCONSOLE* tests)
* @brief      Test_GetUserAndDomain
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_GetUserAndDomain(DEVTESTSCONSOLE* tests)
{
  bool status;

  XSTRING   user;
  XSTRING   domain;

  status = GEN_XSYSTEM.GetUserAndDomain(user, domain);
  
  tests->console->Printf(__L("     user [%s]  domain [%s] \n\n"), user.Get(), domain.Get());

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TEST::Test_I2C_GPIO_MCP2317()
* @brief      Test_I2C_GPIO_MCP2317
* @ingroup    APPLICATION
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_I2C_GPIO_MCP2317(DEVTESTSCONSOLE* tests)
{	
	tests->console->PrintMessage(__L(" I2C Test START..."),1,true,true);	
		
	DIOI2CGPIOMCP2317* mcp2317 = new DIOI2CGPIOMCP2317;
	if(!mcp2317) return false;
	
	if(mcp2317->Ini(1, 0x23, 10))
		{
			tests->console->PrintMessage(__L(" Ini ..."),1,true,true);	
			
			mcp2317->Configure();

			XBYTE rvalue = 0;
		  XBYTE wvalue;

			while(!tests->console->KBHit())
				{																
					for(int d=0; d<2; d++)
						{	
							wvalue = (!d)?0x01:0x80;

							for(int c=0; c<8; c++)
								{					
									
									tests->console->Printf(__L("Inputs: "));
									if(mcp2317->ReadInputs(DIOI2CGPIOMCP2317PORT_A, rvalue)) 
													tests->console->Printf(__L("%02X     \r"), rvalue); 
									   else tests->console->Printf(__L("No read. \r"), rvalue); 
									

									mcp2317->WriteOutputs(DIOI2CGPIOMCP2317PORT_B, wvalue);
									
									if(!d) wvalue <<= 1; else wvalue >>= 1;

									XSLEEP::GetInstance().MilliSeconds(150);			

									if(tests->console->KBHit()) break;
								}
						}					
				}
					
			if(mcp2317->End())
				{
					tests->console->PrintMessage(__L(" End ..."),1,true,true);	
				}
		}

	delete mcp2317;
	
  return true;	
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_SPI_GPIO_MCP2317(DEVTESTSCONSOLE* tests)
* @brief      Test_SPI_GPIO_MCP2317
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SPI_GPIO_MCP2317(DEVTESTSCONSOLE* tests)
{	
	tests->console->PrintMessage(__L(" SPI Test START..."),1,true,true);	
		
  /*
	DIOSPIGPIOMCP23S17* mcp23s17 = new DIOSPIGPIOMCP23S17();
	if(!mcp23s17) return false;
	
	if(mcp23s17->Ini(0, 10))
		{
			tests->console->PrintMessage(__L(" Ini ..."),1,true,true);	

      mcp23s17->Configure();
			   
			XBYTE rvalue = 0;
		  
			while(!tests->console->KBHit())
				{																					
          mcp23s17->Write_Register(DIOSPIGPIOMCP23S17_GPIOA, 0, 0xFF);
					XSLEEP::GetInstance().MilliSeconds(150);			

          mcp23s17->Write_Register(DIOSPIGPIOMCP23S17_GPIOA, 0, 0x00);
					XSLEEP::GetInstance().MilliSeconds(150);			

				  if(tests->console->KBHit()) break;
					
				}
					
			if(mcp23s17->End())
				{
					tests->console->PrintMessage(__L(" End ..."),1,true,true);	
				}
		}

	delete mcp23s17;
  */
	
  return true;	
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_WifiManagerMode(DEVTESTSCONSOLE* tests)
* @brief      Test_WifiManagerMode
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WifiManagerMode(DEVTESTSCONSOLE* tests)
{
  DIOWIFIMANAGERMODE* wifimanagermode = NULL;
  bool                status          = false;

  wifimanagermode = GEN_DIOFACTORY.CreateWifiManagerMode();
  status = wifimanagermode?true:false;
  if(status) 
    {
      wifimanagermode->SetSelectNetInterface(__L("wlan0"));     
      wifimanagermode->SetModeType(DIOWIFIMANAGER_MODETYPE_LINUX_CLIENT_NM);
    }  

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Do Connexion ..."));
  status = wifimanagermode->SetMode_Client(__L("AIQ_m09888_09888"), NULL, false);   
  
  XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("Connexion status: %s"), status?__L("Ok"):__L("Error!"));

  //-------------------------------------------------------------------------
 /*
  XSTRING  _aim;
  DIOIP    _IP;
  XSTRING  _IPstring;

  _aim = __L("xtracebizintek.dyndns.org"); 
 
  GEN_DIODNSRESOLVER.ResolveURL(_aim.Get(), _IP);

  _IP.GetXString(_IPstring);

  tests->console->Printf(__L("\n url: %s IP: %s \n"), _aim.Get(), _IPstring.Get());
 

  //-------------------------------------------------------------------------

  APPFLOW_CFG.SetAutomaticDNSResolver();

  */

  for(int c=0; c<5; c++)
    {
      XSTRING string;
      string.ConvertFromBoolean(wifimanagermode->IsDisconnected(), XSTRINGBOOLEANMODE_HUMAN);
      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Is Connected: %s"), string.Get());
      GEN_XSLEEP.Seconds(1);
    }

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Disconnexion."));
  wifimanagermode->Disconnect();

  GEN_DIOFACTORY.DeleteWifiManagerMode(wifimanagermode);

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_NotificationsManager(DEVTESTSCONSOLE* tests)
* @brief      Test_NotificationsManager
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_NotificationsManager(DEVTESTSCONSOLE* tests)
{
  DIONOTIFICATIONSMANAGER* notificationmanager = GEN_DIOFACTORY.CreateNotificationsManager();
  if(!notificationmanager) return false;

  XSTRING genericapp;
  genericapp.Format(__L("Infodesig.%s"), APPLICATION_NAMEFILE);

  notificationmanager->Ini(APPLICATION_NAMEAPP, genericapp.Get());
  
  XSTRING msg;
  XSTRING msgfinal;

  msg = __L("Esto es una prueba de mensaje");

  msgfinal = msg;

  DIONOTIFICATION notification;

  notification.Get_Title()->Set(APPLICATION_NAMEAPP);
  notification.Get_Message()->Set(msgfinal);

  notification.Application_SetHandle(tests->Application_GetHandle());
  notificationmanager->Do(notification);

  notificationmanager->End();
  GEN_DIOFACTORY.DeleteNotificationsManager(notificationmanager);
 
  return true;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_ATCommandGSM(DEVTESTSCONSOLE* tests)
* @brief      Test_ATCommandGSM
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_ATCommandGSM(DEVTESTSCONSOLE* tests)
{				
  #define ATCOMMAND_PIN  __L("7266")

	tests->console->Printf(__L("\n Creando dispositivo... \n"), 1 , true, true);	

	DIOSTREAMUARTCONFIG* diostreamcfg = new DIOSTREAMUARTCONFIG();
	if(diostreamcfg)
    {
	    diostreamcfg->SetFromString(__L("/dev/ttyUSB2,115200,8,N,1,NONE"));

	    DIOSTREAMUART* diostream = (DIOSTREAMUART*)DIOFACTORY::GetInstance().CreateStreamIO(diostreamcfg);
	    if(diostream) 
        {
	        DIOATCMDGSM* dioatcmdgsm =  new DIOATCMDGSM(diostream);
	        if(dioatcmdgsm) 
            {					
	            tests->console->Printf(__L(" Comprobando dispositivo... \n"), 1 , true, true);	

	            if(dioatcmdgsm->Ini(15, true, true))
		            {																	
			            tests->console->Printf(__L(" Dispositivo comandos AT accesible... \n \n"), 1 , true, true);	
			
			            XSTRING   string;
			            XSTRING   value;
                  bool      isPINresulto = false;

			            for(int c=0;c<10;c++)
				            {
					            string.Empty();
							
					            switch(c)
						            {
							            case    0 : if(dioatcmdgsm->GetManufactured(value)==DIOATCMD_ERROR_NONE)					  string.Format(__L(" Fabricante            : %s"), value.Get());                           break;
							            case    1 : if(dioatcmdgsm->GetModel(value)==DIOATCMD_ERROR_NONE)									  string.Format(__L(" Modelo de terminal    : %s"), value.Get());                           break;											
							            case    2 : if(dioatcmdgsm->GetIMEI(value)==DIOATCMD_ERROR_NONE)								  	string.Format(__L(" IMEI                  : %s"), value.Get());                           break;
							            case    3 : if(dioatcmdgsm->GetVersion(value)==DIOATCMD_ERROR_NONE)								  string.Format(__L(" Version               : %s"), value.Get());                           break;	
														
                          case    4 : if(dioatcmdgsm->PIN_Is(isPINresulto)==DIOATCMD_ERROR_NONE)      string.Format(__L(" SIM PIN resuelto      : %s"), isPINresulto?__L("Si"):__L("No"));       break;	 

                          case    5 : if(!isPINresulto)
                                        {
                                          //DIOATCMD_ERROR error;
                                          //error = dioatcmdgsm->PIN_Activate(ATCOMMAND_PIN, false);                                      
                                          //string.Format(__L(" SIM PIN desactivado   : %s [%s]"), ((error == DIOATCMD_ERROR_NONE)?__L("Si"):__L("No")), ATCOMMAND_PIN);     	                                                      

                                          bool isenter = false;
                                          if(dioatcmdgsm->PIN_Enter(ATCOMMAND_PIN, isenter)==DIOATCMD_ERROR_NONE) string.Format(__L(" SIM PIN introducido   : %s [%s]"), (isenter?__L("Si"):__L("No")), ATCOMMAND_PIN);     	                                                      
                                        }
                                      break;


							            case    6 : { int RSSI = 0;
													              int BER  = 0;
																			
  													            if(dioatcmdgsm->GetSignalQuality(RSSI,BER)==DIOATCMD_ERROR_NONE)		  string.Format(__L(" Calidad de senal      : (RSSI %d)  (BER %d)"), RSSI, BER);																																							
	  											            }
		  										            break;		

							            case    7 : { bool avaible;

			  										            if(dioatcmdgsm->IsAvailableServiceGSM(avaible)==DIOATCMD_ERROR_NONE)	string.Format(__L(" Disp. Servicios GSM   : %s") , avaible?__L("Si"):__L("No"));                           
				  								            }
					  							            break;

							            case    8 : if(dioatcmdgsm->GetIMSI(value)==DIOATCMD_ERROR_NONE)									  string.Format(__L(" IMSI                  : %s"), value.Get());   
						  						            break;													
																									

							            case    9 : { XBYTE support;
															
							  						            if(dioatcmdgsm->GetSMSSupport(support)==DIOATCMD_ERROR_NONE)				  string.Format(__L(" Soporte SMS           : servicio %d, destino %s, origen %s, broadcast %s")	, (support>>4)  
								  																																														  																																									            , support&DIOATCMDGSM_SMSSUPPORT_MOVILETERMINATED ? __L("Si"):__L("No")
									  																																														  																																								            , support&DIOATCMDGSM_SMSSUPPORT_MOVILEORIGINATED ? __L("Si"):__L("No")
										    																																														  																																							          , support&DIOATCMDGSM_SMSSUPPORT_BROADCAST			  ? __L("Si"):__L("No"));																				
												              }
												              break;	
													
							            case   10 : { XBYTE format;
													              XBYTE support;
																																						
													              if(dioatcmdgsm->GetSMSFormat(format,false) ==DIOATCMD_ERROR_NONE) 
														              {
															              if(dioatcmdgsm->GetSMSFormat(support,true)==DIOATCMD_ERROR_NONE) 
																              {
																	              XSTRING strformat;
																	              XSTRING strsupport;

																	              strformat = __L("desconocido");
																	              if(format == DIOATCMDGSM_SMSFORMAT_PDU)  strformat = __L("PDU");
																	              if(format == DIOATCMDGSM_SMSFORMAT_TXT)  strformat = __L("Texto");

																	              if(support&DIOATCMDGSM_SMSFORMAT_PDU)		 strsupport = __L("PDU");
																	              if(support&DIOATCMDGSM_SMSFORMAT_TXT)     
																		              {
																			              if(!strsupport.IsEmpty()) strsupport += __L(" + ");
																			              strsupport += __L("Texto");
																		              }


																	              string.Format(__L(" Formato de SMS        : %s  (valido %s)"), strformat.Get(), strsupport.Get());																																							
																              }
														              }
												              }
												              break;	

							            case   11 : if(dioatcmdgsm->GetSMSCenter(value)==DIOATCMD_ERROR_NONE)						string.Format(__L(" Centro de mensajes    : %s"), value.Get());        break;		
						            }
											
					            if(!string.IsEmpty()) 
                        { 
                          tests->console->Printf(string.Get());	
                          tests->console->Printf(__L("\n"));	
                        }
				            }												 
											
			            tests->console->Printf(__L(" Enviando mensaje      : "));	

			            if(dioatcmdgsm->SendSMS(__L("64xxxxxx"),__L("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ$%&/{}[]()\\*#@+-\"=;:.,_|")) == DIOATCMD_ERROR_NONE) 	 //  ¿?¡!																		
						             tests->console->Printf(__L("Ok.\n"));	
				            else tests->console->Printf(__L("Error!\n"));	
											 
																
			            dioatcmdgsm->End();

		            } else tests->console->Printf(__L(" Dispositivo de comandos AT NO accesible!\n"));	
									
	            delete dioatcmdgsm;
           }

          DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
        }
			
      delete diostreamcfg;																					    
		}
								
	tests->console->Printf(__L("\n Terminada conexion AT.\n"), 1, true, true);	

	return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_SNMP(DEVTESTSCONSOLE* tests)
* @brief      Test_SNMP
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SNMP(DEVTESTSCONSOLE* tests)
{  
  bool        status = false;

  #ifdef DIO_SNMP_ACTIVE

  XSTRING			string;		

	DIOSNMP* snmp = new DIOSNMP();
	if(snmp)  
    {	
	    status = snmp->Open(__L("47.61.135.23"), DIOSNMP_DEFAULT_PORT, false);
	    if(status)	
		    {	        		
          DIOSNMP_XBER xberout;

          snmp->SetVersion(DIOSNMP_VERSION_V2c);  
																	
			    status = snmp->Get(DIOSNMP_OPERATION_GETNEXTREQUEST, __L("public"), __L("1.3.6.1.2.1"), xberout); 
	
			    snmp->Close();
        }

      delete snmp;
		}     

  #endif   	
	
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XFileJSON(DEVTESTSCONSOLE* tests)
* @brief      Test_XFileJSON
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XFileJSON(DEVTESTSCONSOLE* tests)
{
  XFILEJSON         fileJSON;
  XFILEJSONOBJECT*  root;
  bool              status = false;

  root = fileJSON.GetRoot();
  if(!root)
    {
      root = new XFILEJSONOBJECT();
      if(!root) return false;

      fileJSON.SetRoot(root);
    }

  XFILEJSONOBJECT* first_obj = new XFILEJSONOBJECT();
  if(first_obj)
    {
       XFILEJSON_ADDVALUE(first_obj, __L("number1"), (int)10);
       XFILEJSON_ADDVALUE(first_obj, __L("string1"), (XCHAR*)__L("prueba"));
    }
  
  root->Add(__L("first_obj"), first_obj);

  XSTRING jsonString;
  fileJSON.EncodeAllLines(true);
  fileJSON.GetAllInOneLine(jsonString);   
  
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, jsonString.Get());

  XSTRING jsonstr;

  jsonstr.Add(__L("{\"webinv\":\"0\",\"sshinv\":\"0\",\"webinvPort\":\"30089\",\"sshinvPort\":\"40089\",\"servertime\":1706297258,\"action\":\"counters\",\"numPrinters\":1,\"printers\":[\"192.168.1.156\"]}"));

  fileJSON.DeleteAllLines();
  fileJSON.DeleteAllObjects();

  fileJSON.AddLine(jsonstr);
  status = fileJSON.DecodeAllLines();

  XFILEJSONVALUE* action_jsv       = fileJSON.GetValue(__L("action"));          
  XFILEJSONVALUE* wevinv_jsv       = fileJSON.GetValue(__L("webinv"));                              
  XFILEJSONVALUE* webinvport_jsv   = fileJSON.GetValue(__L("webinvPort"));
  XFILEJSONVALUE* sshinv_jsv       = fileJSON.GetValue(__L("sshinv"));
  XFILEJSONVALUE* sshinvport_jsv   = fileJSON.GetValue(__L("sshinvPort"));
  XFILEJSONVALUE* servertime_jsv   = fileJSON.GetValue(__L("servertime"));          

  XFILEJSONOBJECT* printerarray_jsv  = fileJSON.GetObj(__L("printers")); 
  XFILEJSONVALUE*  nprinters_jsv     = fileJSON.GetValue(__L("numPrinters"));   

  XDWORD nprinters = 0;

  if(nprinters_jsv) nprinters = nprinters_jsv->GetValueInteger();  

  if(printerarray_jsv)
    {
      if(nprinters < printerarray_jsv->GetValues()->GetSize())  nprinters = printerarray_jsv->GetValues()->GetSize();
    }



  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XFileXML(DEVTESTSCONSOLE* tests)
* @brief      Test_XFileXML
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XFileXML(DEVTESTSCONSOLE* tests)
{
  XPATH       xpath;
  XFILEXML    xml;
  bool        status = false;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("example.xml"));

  if(xml.Open(xpath, true))
    {
      xml.ReadAndDecodeAllLines();

      XFILEXMLELEMENT* root           = xml.GetRoot();
      XFILEXMLELEMENT* nodewebservice = NULL;

      if(root)
        {
          for(int c=0; c<root->GetNElements(); c++)
            {
              nodewebservice = root->GetElement(c);
              if(nodewebservice)
                {
                
                }
            }
        }

      xml.Close();

      status = true;
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XFileRIFF(DEVTESTSCONSOLE* tests)
* @brief      Test_XFileRIFF
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XFileRIFF(DEVTESTSCONSOLE* tests)
{
  XFILERIFF xfileRIFF;  
  XPATH     xpath;
  bool      status = false;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("example.avi"));

  if(xfileRIFF.Open(xpath.Get()))
    {
      status = xfileRIFF.ReadAllLists();

      xfileRIFF.Close();
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DIOStreamUSBConnection(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOStreamUSBConnection
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOStreamUSBConnection(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  DIOSTREAMUSBLOCALENUMDEVICES* enumdevices;
	DIOSTREAMDEVICEUSB*						device       = NULL;
  DIOSTREAMUSBCONFIG            diostreamcfg;
  DIOSTREAM*                    diostream    = NULL;
  XDWORD												PID          = 0xDF11;
	XDWORD												VID          = 0x0483;
  bool                          found        = false;    
  bool                          status       = false;


  tests->console->Printf(__L("\n\nBuscando dispositivo USB...\n"));

  while(!found)
    {
      enumdevices = (DIOSTREAMUSBLOCALENUMDEVICES*)GEN_DIOFACTORY.CreateStreamEnumDevices(DIOSTREAMENUMTYPE_USB_LOCAL);
	    if(!enumdevices) return false;	

	    enumdevices->Search();
      
      while(enumdevices->IsSearching())
       {
         GEN_XSLEEP.MilliSeconds(100);
       }
	
	    for(int c=0;c<(int)enumdevices->GetDevices()->GetSize();c++)
		    {				
			    device = (DIOSTREAMDEVICEUSB*)enumdevices->GetDevices()->Get(c);
			    if(device) 
				    {									    
					    if((device->GetProductID() == PID) && (device->GetVendorID() == VID))						    
                {																				
                  found = true;  
							    break;

						    } else device = NULL;
				    }
		    }

      if(tests->console->KBHit()) break;
    }

  if(!device) return false;
  if(!found)  return false;

  diostreamcfg.SetMode(DIOSTREAMMODE_CLIENT);	
  diostreamcfg.GetResource()->Set(device->GetResource()->Get());
  
  tests->console->Printf(__L("\nConnectando con USB device [%s]"), device->GetLocation()->Get());

  diostream = (DIOSTREAM*)GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(diostream)
    {
      if(diostream->Open())
        {
          status = diostream->WaitToConnected(1);

          tests->console->Printf(__L("\r\nConexion USB estado: %s"), status?__L("Connected!"):__L("Error!"));

          while(diostream->GetStatus()==DIOSTREAMSTATUS_CONNECTED)
            {
              /*                                                  
              tests->console->Printf    (__L("\r\n    Sending packet(%d)"), c++);

              diostream->WriteStr (__L("Hello Jello!\r\n"));
              diostream->WaitToFlushOutXBuffer();
              */
            }
      
          diostream->Close();

          status = true;
        }

      DIOFACTORY::GetInstance().DeleteStreamIO(diostream);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XFileDFU(DEVTESTSCONSOLE* tests)
* @brief      Test_XFileDFU
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XFileDFU(DEVTESTSCONSOLE* tests)
{
  XFILEDFU  xfileDFU;  
  XPATH     xpath;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_FIRMWARE, xpath);
  xpath.Slash_Add();
  xpath.Add(__L("firmware.dfu"));

  if(xfileDFU.Open(xpath.Get()))
    {
      if(xfileDFU.ReadAll())
        {


        }

      xfileDFU.Close();
    }
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_SystemHostFile(DEVTESTSCONSOLE* tests)
* @brief      Test_SystemHostFile
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SystemHostFile(DEVTESTSCONSOLE* tests)
{
  GEN_XSYSTEM.HostFile(true, __L("youtube.es"), __L("127.0.0.1"));

  GEN_XSYSTEM.HostFile(false, __L("youtube.es"), __L(""));

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_SystemBatteryLevel(DEVTESTSCONSOLE* tests)
* @brief      Test_SystemBatteryLevel
* @ingroup    
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_SystemBatteryLevel(DEVTESTSCONSOLE* tests)
{
  bool    isincharge   = false;
  XBYTE   batterylevel = 0;
  bool    status;

  status = GEN_XSYSTEM.GetBatteryLevel(isincharge, batterylevel);  
  if(status)
    {
      XSTRING string;
      string.ConvertFromBoolean(isincharge, XSTRINGBOOLEANMODE_HUMAN);
      
      tests->console->Printf(__L("\n   Is in charge  : %s.\n"), string.Get());	
      tests->console->Printf(__L("   Battery level : %d%%.\n"), batterylevel);	
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_LedNeoPixelWS2812B(DEVTESTSCONSOLE* tests)
* @brief      Test_LedNeoPixelWS2812B
* @ingroup    
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_LedNeoPixelWS2812B(DEVTESTSCONSOLE* tests)
{ 
  DIOLEDNEOPIXELWS2812B* ledneopixelws2812b = GEN_DIOFACTORY.CreateLedNeopixelWS2812B(); 
  if(!ledneopixelws2812b)  return false;

  ledneopixelws2812b->SetDataGPIOEntryID(DEVTESTSCONSOLE_GPIOENTRYID_LED_NEOPIXEL);                                             
     
  if(ledneopixelws2812b->Ini(7))
    {       
      XBYTE data1[] = { 0xFF, 0x00, 0x00,    
                        0xFF, 0x00, 0x00,  
                        0xFF, 0x00, 0x00,   
                        0xFF, 0x00, 0x00,                            
                                                    
                        0xFF, 0x00, 0x00,  
                        0xFF, 0x00, 0x00,
                        0xFF, 0x00, 0x00,
                        0xFF, 0x00, 0x00,                                                                                  
                      };

      XBYTE data2[] = { 0x00, 0xFF, 0x00,    
                        0x00, 0xFF, 0x00,  
                        0x00, 0xFF, 0x00,   
                        0x00, 0xFF, 0x00,                            
                                                    
                        0x00, 0xFF, 0x00,  
                        0x00, 0xFF, 0x00,
                        0x00, 0xFF, 0x00,
                        0x00, 0xFF, 0x00,                                                                                  
                      };     

      XBYTE data3[] = { 0x00, 0x00, 0xFF,     
                        0x00, 0x00, 0xFF,   
                        0x00, 0x00, 0xFF,    
                        0x00, 0x00, 0xFF,                             
                                                     
                        0x00, 0x00, 0xFF,   
                        0x00, 0x00, 0xFF, 
                        0x00, 0x00, 0xFF, 
                        0x00, 0x00, 0xFF,                                                                                   
                      };

      XBYTE data4[] = { 0xFF, 0xFF, 0xFF,     
                        0xFF, 0xFF, 0xFF,   
                        0xFF, 0xFF, 0xFF,    
                        0xFF, 0xFF, 0xFF,                             
                                              
                        0xFF, 0xFF, 0xFF,   
                        0xFF, 0xFF, 0xFF, 
                        0xFF, 0xFF, 0xFF, 
                        0xFF, 0xFF, 0xFF,                                                                                   
                      };

      XBYTE data5[] = { 0x00, 0x00, 0x00,     
                        0xFF, 0x00, 0x00,   
                        0x00, 0xFF, 0x00,    
                        0x00, 0x00, 0xFF,                             
                                                           
                        0xFA, 0xF2, 0x04,   
                        0x3E, 0xF9, 0xF9,                           
                        0xFD, 0xB2, 0x03, 
                        0xFF, 0xFF, 0xFF,                                                                                   
                      };

      
      for(int c=0; c<3; c++)
        {
          ledneopixelws2812b->SendData(data1, sizeof(data1));
          GEN_XSLEEP.Seconds(1);                  

          ledneopixelws2812b->SendData(data2, sizeof(data2));
          GEN_XSLEEP.Seconds(1);  

          ledneopixelws2812b->SendData(data3, sizeof(data3));
          GEN_XSLEEP.Seconds(1);  
        }

      for(int d=0; d<3; d++)
        {            
          for(int c=0; c<255; c++)
            {
              ledneopixelws2812b->SetBrightnessLevel(c);          
              ledneopixelws2812b->SendData(data4, sizeof(data4));

              GEN_XSLEEP.MilliSeconds(1);                  
            }
      
          for(int c=255; c>=0; c--)
            {
              ledneopixelws2812b->SetBrightnessLevel(c);          
              ledneopixelws2812b->SendData(data4, sizeof(data4));

              GEN_XSLEEP.MilliSeconds(1);                  
            }
        } 


      ledneopixelws2812b->SetBrightnessLevel(128);          
      ledneopixelws2812b->SendData(data5, sizeof(data5));

      GEN_XSLEEP.Seconds(4);
      
      ledneopixelws2812b->End();
    }
  
  GEN_DIOFACTORY.DeleteLedNeopixelWS2812B(ledneopixelws2812b);
  
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DIOPCap(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOPCap
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOPCap(DEVTESTSCONSOLE* tests)
{
	#ifdef DIO_PCAP_ACTIVE

	DIOPCAP*						 diopcap					 = NULL; 
	DIOPCAPNETINTERFACE* netinterface			 = NULL;  
	int                  indexnetinterface = 8;

	diopcap = GEN_DIOFACTORY.CreatePCap();
  if(!diopcap)  return false;

	if(diopcap->Ini())
    { 
			tests->console->Printf(__L("Interfaces de red disponibles: \n\n"));
      for(int c=0; c<(int)diopcap->GetNetInterfaces()->GetSize(); c++)
        {
          netinterface = diopcap->GetNetInterface(c);
          if(netinterface) 
            {          
              if(indexnetinterface == -1)
                {
                  if(netinterface->IsLoopBack())
                    {
                      indexnetinterface = c;                        
                    }
                }
                
               tests->console->Printf(__L("[%2d] %c %s, [%s]\n"), c, (indexnetinterface == c)?__C('*'):__C('-'), netinterface->GetName()->Get(), netinterface->GetDescription()->Get());						
            }
				}

			tests->console->Printf(__L("\n"));

			if(indexnetinterface != -1) 
				{
					if(diopcap->Capture_Start(indexnetinterface, true, 100)) 
						{
							while(!tests->console->KBHit())
								{
									int nsize = diopcap->Frames_Get()->GetSize();

									for(int c=0;c<nsize;c++) 
										{
											DIOPCAPFRAME* frame = diopcap->Frames_Get(c);
											if(!frame) break;

											if(tests->console->KBHit()) break;
									          
                      XSTRING string;  

                      if(!frame->GetSourceMAC()->IsZero())
                        {
                          frame->GetSourceMAC()->GetXString(string);

                          tests->console->Printf(__L("MACs [%s"), string.Get());
                        } 

                      if(!frame->GetTargetMAC()->IsZero())
                        {
                          frame->GetTargetMAC()->GetXString(string);

                          tests->console->Printf(__L(" > %s]"), string.Get());
                        }  

                      if(!frame->GetSourceIP()->IsEmpty())
                        {
                          XSTRING protocoltypestr;  

                          frame->GetProtocolTypeString(protocoltypestr);
                          frame->GetSourceIP()->GetXString(string);

                          tests->console->Printf(__L(" %-6s IPs [%15s"), protocoltypestr.Get(), string.Get());
                        }

                      if(!frame->GetTargetIP()->IsEmpty())
                        {
                          frame->GetTargetIP()->GetXString(string);

                          tests->console->Printf(__L(" > %15s]"), string.Get());
                        }

                      if(frame->GetSourcePort())
                        {                          
                          tests->console->Printf(__L(" Ports [%5d"), frame->GetSourcePort());
                        }

                      if(frame->GetTargetPort())
                        {                          
                          tests->console->Printf(__L(" > %5d]"), frame->GetTargetPort());
                        }

                      tests->console->Printf(__L(" header size: %d,  playload size: %d"), frame->GetAllHeadersSize(), frame->GetDataPayLoadSize());
                      
                      tests->console->Printf(__L("\n"));                   
									
											diopcap->Frames_Delete(c);
										}
								
								}
							
							diopcap->Capture_End();
						}
			
				}	 
			
			diopcap->End();														
		}

	GEN_DIOFACTORY.DeletePCap(diopcap);

	#endif
  
	return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XLicense(DEVTESTSCONSOLE* tests)
* @brief      Test_License
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XLicense(DEVTESTSCONSOLE* tests)
{
	XLICENSE* 	xlicense  = NULL;
	XLICENSEID  xlicenseID;	
	XBUFFER			licensefile;
	XBUFFER			license;
	XSTRING			string;
  bool        status = false;


  xlicense = new XLICENSE();
  if(!xlicense)		
    {
      return false;
    }

	if(xlicense->GenerateMachineID(xlicenseID))
		{
			xlicenseID.GetID()->GetToString(string);
			tests->console->Printf(__L("   ID licencia : %s \n"), string.Get()); 
			
			xlicense->Application_GetID()->Set(__L("GEN  Copyright (C).  All right reserved."));		
			xlicense->Generate(xlicenseID);
			xlicense->Get(string);
			tests->console->Printf(__L("   Licencia    : %s \n"), string.Get()); 	

			XPATH		  xpathgeneric;
			XPATH		  xpath;
			DIOURL	  url;
      XSTRING   applicationID;
      XSTRING   expireddate;

      applicationID = __L("TEST Application");

      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
      xpath.Slash_Add();
      xpath.Add("test.lic");
      			
      CREATEMASTERLICENSE(xlicense, xpath, xlicenseID, applicationID, 10)

      CHECKLICENSEFULLLOCAL(xlicense, xpath, applicationID, status)   
			
      CHECKLICENSEFULLLOCALEXPIRE(xlicense, xpath, applicationID, status)   
		}

	return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XSerializable(DEVTESTSCONSOLE* tests)
* @brief      Test_XSerializable
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XSerializable(DEVTESTSCONSOLE* tests)
{
  if(!tests->console) return false;

  XRAND*                xrand;
  XSERIALIZATIONMETHOD* serializationmethod;
  XBUFFER               buffer; 
  XFILEJSON             xfileJSON;      
  XSTRING               alllines;
  TESTSERIALIZABLE      testserializable;
  TESTSERIALIZABLE      testserializable2;

//serializationmethod = XSERIALIZABLE::CreateInstance(buffer);

  xrand = GEN_XFACTORY.CreateRand();
  if(!xrand)
    {
      return false;
    }

  serializationmethod = XSERIALIZABLE::CreateInstance(xfileJSON);


  testserializable.SetValue1(xrand->Max(10000));
  testserializable.GetString1()->Set(__L("hola radiola main"));

  testserializable.GetClassSer()->SetValue2(xrand->Max(10000));
  testserializable.GetClassSer()->GetString2()->Format(__L("Hola radiola class [%04X]"), xrand->Max(16384));

  for(int c=0; c<testserializable.GetVectorSer()->GetSize(); c++)
    {
      TESTSERIALIZABLE2* test = testserializable.GetVectorSer()->Get(c);
      if(test)
        {
          test->SetValue2(xrand->Max(10000)); 
          test->GetString2()->Format(__L("hola radiola vector %d [%04X]"), c+1, xrand->Max(16384));      
        }
    }


  testserializable.DoSerialize(serializationmethod);
  xfileJSON.EncodeAllLines(true);  
  xfileJSON.ShowTraceJSON(XTRACE_COLOR_BLUE);

  testserializable2.DoDeserialize(serializationmethod);
  xfileJSON.EncodeAllLines(true);  
  xfileJSON.ShowTraceJSON(XTRACE_COLOR_GREEN);

  delete serializationmethod;

  GEN_XFACTORY.DeleteRand(xrand);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_InputSimulate(DEVTESTSCONSOLE* tests)
* @brief      Test_InputSimulate
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_InputSimulate(DEVTESTSCONSOLE* tests)
{
  #ifdef INP_ACTIVE

  INPSIMULATE* inpsimulated = GEN_INPFACTORY.CreateSimulator();
  if(!inpsimulated)
    {
      return false;
    }

  inpsimulated->Key_Click(0x41);

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_Scheduler(DEVTESTSCONSOLE* tests)
* @brief      Test_Scheduler
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Scheduler(DEVTESTSCONSOLE* tests)
{
  XSCHEDULER*     xscheduler;
  XSCHEDULERTASK* xtask;
  XDATETIME       xdatetimecadence;
  XTIMER          xtimercadence;
  bool            status   = false;

  xscheduler = new XSCHEDULER();
  if(!xscheduler) 
    {
      return false;
    }

  xtask = new XSCHEDULERTASK(xscheduler);
  if(xtask) 
    {     
      xdatetimecadence.SetToZero();

      xtimercadence.Reset();
      xtimercadence.AddSeconds(5);

      xtimercadence.GetMeasureToDate(&xdatetimecadence);  

      xtask->SetNCycles(XSCHEDULER_CYCLEFOREVER, &xdatetimecadence);
      xtask->SetID(DEVTESTSCONSOLE_TASKID_TEST);
      xtask->SetIsStartImmediatelyCycles(true);
      xtask->SetIsActive(true);

      status = xscheduler->Task_Add(xtask);      

      tests->SubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);

      if(xscheduler->Ini()) 
        {
           status = true;
        }
    }

  if(status)
    {
      GEN_XSLEEP.Seconds(2);

      xtask->StartConditionImmediately();

      GEN_XSLEEP.Seconds(18);
    }

  tests->UnSubscribeEvent(XEVENT_TYPE_SCHEDULER, xscheduler);
  delete xscheduler;
   
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DynDNS(DEVTESTSCONSOLE* tests)
* @brief      Test_DynDNS
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DynDNS(DEVTESTSCONSOLE* tests)
{	
  DIODYNDNS_MANAGER*  dyndnsmanager;
  bool							  status = false;	

  dyndnsmanager = new DIODYNDNS_MANAGER();
  if(!dyndnsmanager)
    {
      return false; 
    }

  #ifdef APPFLOW_CFG_DYNDNSMANAGER_ACTIVE
  for(XDWORD c=0; c<APPFLOW_CFG.DNSManager_GetURLs()->GetSize(); c++)
    {
      dyndnsmanager->AddDNS((*APPFLOW_CFG.DNSManager_GetURL(c)));
    }         
  #endif  

  dyndnsmanager->GetLogin()->Set(__L(""));
  dyndnsmanager->GetPassword()->Set(__L(""));
	
  status = dyndnsmanager->AssingAll();

  delete dyndnsmanager;
  
	return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_ID_IBAN(DEVTESTSCONSOLE* tests)
* @brief      Test_ID_IBAN
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_ID_IBAN(DEVTESTSCONSOLE* tests)
{
  ID_IBAN IBAN;
  bool    status = false;	

  if(!tests->console) 
    {
      return false;
    }

  
  status = IBAN.Set(__L("GB82 WEST 1234 5698 7654 32"));
  if(status)
    {

    }
  
  status = IBAN.Set(__L("ES90 0024 6912 50 1234567891"));
  if(status)
    {

    }

  // 
  
  for(int c=0; c<10000; c++)
    {
      XSTRING IBANstr;
      
      // ES1000492352082414205416
      IBANstr.AddFormat(__L("ES10 0049 2352 08 241420 %04d"), c);

      status = IBAN.Set(IBANstr.Get());

      if(status)
        {
          int a=0;
          a++;
        }

      tests->console->Printf(__L("IBAN : %s  %20s    %c"), IBAN.Get()->Get(), status?__L("Ok!"):__L("Error!"), status?__C('\n'):__C('\r')); 
      if(status)
        {  
          XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("IBAN : %s"), IBAN.Get()->Get()); 
        }
    }

  tests->console->Printf(__L("                                                                              \n")); 

  return status;
} 


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_Compress(DEVTESTSCONSOLE* tests)
* @brief      Test_Compress
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Compress(DEVTESTSCONSOLE* tests)
{
  #define NAMEFILECMPINZIP __L("testcmp.txt")

  COMPRESSMANAGER*	manager     = NULL;
  COMPRESSBASE*			compressor  = NULL;    	
  XPATH             xpathcmpfile;
  XPATH             xpathcmpinzip;
  XPATH             xpathzipfile;  
	bool              status      = false;

 	manager = new COMPRESSMANAGER();
  if(manager)
    {
	    compressor = manager->Create(COMPRESSBASE_TYPE_ZIP);
      if(!compressor)
        {
          delete manager;
          return status;
        }    
    }

	XFILE* xfiletxt = XFACTORY::GetInstance().Create_File();
	if(!xfiletxt)
    { 
      delete(compressor);
	    delete(manager);

	    return status;
    }

  tests->console->Printf(__L("\nAdd file in Zip file: "));	

	XPATHSMANAGER::GetInstance().GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathcmpfile);
	xpathcmpfile.Add(NAMEFILECMPINZIP);
	
	xpathcmpinzip.Add(NAMEFILECMPINZIP);

	XPATHSMANAGER::GetInstance().GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathzipfile);
	xpathzipfile.Slash_Add();
	xpathzipfile.Add(__L("test.zip"));

								
	XFILEZIP* zipfile = new XFILEZIP();		
	if(zipfile) 
    {
	    status = zipfile->Open(xpathzipfile);
	    if(status)
		    {
			    zipfile->AddFile(xpathcmpfile, xpathcmpinzip);
			    zipfile->Close();
		    }
    }
	
	delete(zipfile);    	

  tests->console->Printf(__L("%s\n"), status?__L("Ok."): __L("Error!"));					 							

  tests->console->Printf(__L("Compress and decompress buffer: "));	

  XSTRING sentence;
  XBUFFER buffer;
  XBUFFER cmpbuffer;
  XBUFFER decmpbuffer;

  sentence = __L("I've seen things you people wouldn't believe."
                 "Attack ships on fire off (the) shoulder of Orion."
                 "I watched C-beams glitter in the dark near the Tannhäuser Gate."
                 "All those moments will be lost in time, like tears in rain."
                 "Time to die.");

  sentence.ConvertToUTF8(buffer, false);

  decmpbuffer.Resize(buffer.GetSize());
  
  status = compressor->Compress(buffer.Get(), buffer.GetSize(), &cmpbuffer);
  if(status)
    {
      XSTRING finalsentence;
      status = compressor->Decompress(cmpbuffer.Get(), cmpbuffer.GetSize(), &decmpbuffer);

      finalsentence.ConvertFromUTF8(decmpbuffer);

      status = !finalsentence.Compare(sentence, false)?true:false;
    }

  tests->console->Printf(__L("%s\n"), status?__L("Ok."): __L("Error!"));				

	delete(compressor);
	delete(manager);

	return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DIOStreamTCPIPServer(DEVTESTSCONSOLE* tests)
* @brief      Test_DIOStreamTCPIPServer
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DIOStreamTCPIPServer(DEVTESTSCONSOLE* tests)
{  
  if(!tests->console) 
    {
      return false;
    }

  DIOSTREAMTCPIPCONFIG  diostreamcfg;
  DIOSTREAMTCPIPSERVER* diostream    = NULL;
  XSTRING               line;
  bool                  status       = false;

  diostreamcfg.GetRemoteURL()->Set(__L("127.0.0.1"));
  diostreamcfg.SetMode(DIOSTREAMMODE_SERVERMULTISOCKET);
  diostreamcfg.SetRemotePort(1200);

  line.Format(__L("Server [%s]: %d"), diostreamcfg.GetRemoteURL()->Get(), diostreamcfg.GetRemotePort());
  tests->console->Printf(__L("   %s\n"), line.Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, line.Get());

  diostream =  (DIOSTREAMTCPIPSERVER*)GEN_DIOFACTORY.CreateStreamIO(&diostreamcfg);
  if(!diostream) 
    {
      return false;
    }

  tests->SubscribeEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED    , diostream);
  tests->SubscribeEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED , diostream);
  
  if(diostream->Open())
    {
      while(!tests->console->KBHit())
        {
          line.Format(__L("N Connections: %d  [ %d / %d ] "), diostream->GetNumConnectedMultiSocketStreams()
                                                            , diostream->GetNBytesRead()
                                                            , diostream->GetNBytesWrite());  

          tests->console->Printf(__L("    %s\r"), line.Get());

          GEN_XSLEEP.MilliSeconds(50);
        }

      status = diostream->Close();

      line.Format(__L("Close connection: %s"), status?__L("Ok."):__L("Error!"));  
      tests->console->Printf(__L("   %s\n\n"), line.Get());
      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), line.Get());                                 
    }

  tests->UnSubscribeEvent(DIOSTREAM_XEVENT_TYPE_CONNECTED    , diostream);
  tests->UnSubscribeEvent(DIOSTREAM_XEVENT_TYPE_DISCONNECTED , diostream);

  GEN_DIOFACTORY.DeleteStreamIO(diostream);
  
  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_XPath(DEVTESTSCONSOLE* tests)
* @brief      test  Xpath
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_XPath(DEVTESTSCONSOLE* tests)
{
  XPATH             xpath;
  XSTRING           drive;
  XVECTOR<XSTRING*> subpaths;
  XSTRING           name;
  XSTRING           ext;
  bool              status = false;

  xpath = __L("SOFTWARE\\Policies\\Microsoft\\Edge");

  status = xpath.Split(&drive, subpaths, NULL, NULL);

  return status;
}


#ifdef WINDOWS
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_WindowsACL(DEVTESTSCONSOLE* tests)
* @brief      Test_WindowsACL
* @ingroup    APPLICATION
*
* @param[in]  tests :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WindowsACL(DEVTESTSCONSOLE* tests)
{
  XWINDOWSACCESSCONTROLLISTS  ACList;
  XPATH                       xpathsection;
  XPATH                       namefile;
  bool                        status = false;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  namefile.Create(3 , xpathsection.Get(), __L("scraperweb"), __L(".xml"));

  status = ACList.SetFileOnlyPermissionForSystemUser(namefile.Get());

  GEN_XSLEEP.Seconds(2);

  status = ACList.SetFilePermissionForEveryone(namefile.Get());

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_WindowsRegistry(DEVTESTSCONSOLE* tests)
* @brief      test  registry
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WindowsRegistry(DEVTESTSCONSOLE* tests)
{
  XWINDOWSREGISTRYMANAGER registrymanager;
  XWINDOWSREGISTRYKEY     registrykey;
  bool                    status = false;

  // Property_Add(CTRLAGENT_PROPERTYRESTRICTOR_HKEY_LOCAL_MACHINE, __L("SOFTWARE\\Policies\\Microsoft\\Edge"), __L("HubsSidebarEnabled"), __L("Edge Hubs Sidebar"), 1);  

  status = registrymanager.CreateKey(HKEY_LOCAL_MACHINE, __L("SOFTWARE\\Policies\\Microsoft\\Edge\\prueba\\prueba2"), registrykey);
  if(status)
    {
     
      registrymanager.CloseKey(registrykey);
    }

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_WindowsWinget(DEVTESTSCONSOLE* tests)
* @brief      test  windows winget
* @ingroup    
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WindowsWinget(DEVTESTSCONSOLE* tests)
{  
  XSTRING         jsonresult;
  bool            status = false;

  // status = GEN_WINGET.List(false, jsonresult);

  // status = GEN_WINGET.Find(__L("Xbox"), jsonresult);


  status = GEN_WINGET.ApplicationOperation(XWINDOWSWINGET_APPLICATIONOPERATION_UPDATEVERSION, __L("Microsoft.DotNet.DesktopRuntime.8"), true);


  return status;
}


#endif


#ifdef LINUX
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_DBUS(DEVTESTSCONSOLE* tests)
* @brief      Test_DBUS
* @ingroup    APPLICATION
*
* @param[in]  tests : 
*
* @return     bool : true if is succesful. 
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DBUS(DEVTESTSCONSOLE* tests)
{
  bool                  status = false;

  #ifdef LINUX_DIO_DBUS_ACTIVE

  DIOLINUXDBUS_MESSAGE  message;  
  DIOLINUXDBUS_MESSAGE  reply;  
  

  DIOLINUXDBUS* dbus = new DIOLINUXDBUS();
  if(dbus)
    {
      if(dbus->Ini())
        {        
          //---------------------------------------------------------------------------------

          /*    
          message.GetDestination()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetPath()->Set(__L("/org/freedesktop/NetworkManager"));
          message.GetIFace()->Set(__L("org.freedesktop.NetworkManager.Devices"));
          message.GetMethod()->Set(__L("GetAll"));
          status = message.Create();
          if(status)
            {              
              message.SetArgument(true);

              message.SetArgument(DIOLINUXDBUS_IFACE_PROPERTIES);
              message.SetArgument(DIOLINUXDBUS_IFACE_PROPERTIES);

              status = dbus->CallMethod(message, reply);                       
              if(status)
                {

                  reply.Delete();
                }   

               message.Delete();
            }
           else 
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message ..."));
            }

          */

          //---------------------------------------------------------------------------------
          
          message.GetDestination()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetPath()->Set(__L("/org/freedesktop/NetworkManager"));
          message.GetIFace()->Set(__L("org.freedesktop.NetworkManager"));
          message.GetMethod()->Set(__L("GetDevices"));

          status = message.Create();
          if(status)
            {              
              status = dbus->CallMethod(message, reply);                       
              if(status)
                { 
                  XVECTOR<XSTRING*> result;            

                  status = reply.GetResult(result);
                  if(status)
                    {
                      XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("[DBUS] Result:"));
                      for(int c=0; c<result.GetSize(); c++)
                        {
                          XTRACE_PRINTCOLOR((status?XTRACE_COLOR_BLUE:XTRACE_COLOR_RED), __L("%s"), result.Get(c)->Get());
                        }

                      result.DeleteContents();
                      result.DeleteAll();
                    }
                   else
                    {
                      XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error get result ..."));    
                    } 
                  
                  reply.Delete();
                }   

               message.Delete();
            }  
           else 
            {
              XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[DBUS] Error create message ..."));
            }
          

          //---------------------------------------------------------------------------------


          status = dbus->End();      
        }
 
      delete dbus;
    }

  #endif 

  return status;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_NetWorkManager(DEVTESTSCONSOLE* tests)
* @brief      Test_NetWorkManager
* @ingroup    
* 
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_NetWorkManager(DEVTESTSCONSOLE* tests)
{
  #ifdef LINUX_DIO_NETWORKMANAGER_ACTIVE

  DIOLINUXNETWORKMANAGER networkmanager;
  
  if(networkmanager.Ini()) 
    {

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager ] Activate ..."));    
      networkmanager.Enable(true);

      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("DeviceAdded"));
      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("DeviceRemoved"));
      networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_MAIN  , __L("PropertiesChanged"));

      //networkmanager.Signal_Add(DIOLINUXNETWORKMANAGER_DEFAULT_DBUS_IFACE_DEVICE, __L("PropertiesChanged"));
  

      switch(networkmanager.GetConnectionState())
        {
          case DIOLINUXNETWORKMANAGER_STATE_UNKNOWN            :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: networking state is unknown"));                            break;
          case DIOLINUXNETWORKMANAGER_STATE_ASLEEP             :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: networking is not enabled"));                              break; 
          case DIOLINUXNETWORKMANAGER_STATE_DISCONNECTED       :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is no active network connection"));                  break;
          case DIOLINUXNETWORKMANAGER_STATE_DISCONNECTING      :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: network connections are being cleaned up"));               break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTING         :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: a network connection is being started"));                  break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_LOCAL    :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is only local IPv4 and/or IPv6 connectivity"));      break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_SITE     :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is only site-wide IPv4 and/or IPv6 connectivity"));  break;
          case DIOLINUXNETWORKMANAGER_STATE_CONNECTED_GLOBAL   :   XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Network Manager] Get Connection state: there is global IPv4 and/or IPv6 Internet connectivity")); break;
        }

      XVECTOR<DIOSTREAMDEVICEIP*> devices;

      networkmanager.GetDevices(devices);

      for(XDWORD c=0; c<devices.GetSize(); c++)
        {
          DIOSTREAMDEVICEIP* deviceIP = devices.Get(c);
          if(deviceIP) deviceIP->DebugPrintInfo();
        }

      devices.DeleteContents();
      devices.DeleteAll();
       
      while(!tests->console->KBHit())
				{				
          GEN_XSLEEP.MilliSeconds(100);              
        }

      networkmanager.End();
    }

  #endif

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_DeviceBusInputFile(DEVTESTSCONSOLE* tests)
* @brief      Test_DeviceBusInputFile
* @ingroup    APPLICATION
* 
* 
* @param[in]  tests : 
* 
* @return     static : 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_DeviceBusInputFile(DEVTESTSCONSOLE* tests)
{
  INPDEVICE_TYPE             typedevice = INPDEVICE_TYPE_TOUCHSCREEN; 
  XVECTOR<INPLINUXDEVICEID*> devices;
  bool                       status     = false;
   
  /* 
  XFILETXT* xfiletxtdevices =  new XFILETXT();
  if(xfiletxtdevices)
    {
      XPATH xpathdevices;
      
      #ifdef LINUX
      xpathdevices = INPLINUXDEVICEID_HANDLEFILE;
      #else
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathdevices);
      xpathdevices.Slash_Add();
      xpathdevices.Add(__L("devices"));      
      #endif
      
      if(xfiletxtdevices->Open(xpathdevices))
        {
          xfiletxtdevices->ReadAllFile();

          for(int c=0; c<xfiletxtdevices->GetNLines(); c++)
            {
              XSTRING* line = xfiletxtdevices->GetLine(c);
              if(line)
                {
                  int index = line.Find(__L("I:"), true);
                  if(index == 0)
                    {
                      INPLINUXDEVICEID* deviceID = new INPLINUXDEVICEID();
                      if(deviceID)
                        {
                          do{ line = xfiletxtdevices->GetLine(c);
                              if(!line) break;
                              if(line.GetSize() < 2) break;  

                              char typeline = (char)line.Get()[0];  
                              switch(typeline)
                                {    
                                  case  'I' : break;                                    

                                  case  'N' : { XSTRING name;

                                                name.AdjustSize(_MAXSTR);
                                                line.UnFormat(__L("N: Name=\"%s\""), name.Get());
                                                name.AdjustSize();      

                                                deviceID->GetName()->Set(name);
                                              }
                                              break;                                    

                                  case  'P' : break;                                    
                                  case  'S' : break;                                    
                                  case  'U' : break;                                    

                                  case  'H' : { XSTRING handlers;
                                                int     event_index = INPLINUXDEVICEID_INVALID;

                                                handlers.AdjustSize(_MAXSTR);
                                                line.UnFormat(__L("H: Handlers=%s"), handlers.Get());
                                                handlers.AdjustSize();      

                                                index = handlers.Find(__L("event"), true);
                                                if(index != XSTRING_NOTFOUND)
                                                  {
                                                    XSTRING eventstr;

                                                    handlers.Copy(index, eventstr);
                                                    eventstr.UnFormat(__L("event%d"), &event_index);

                                                    deviceID->SetEventIndex(event_index);
                                                  }                                                
                                              }
                                              break;        
                           
                                  case  'B' : { XCHAR* prefix[] = { __L("PROP=")  , 
                                                                    __L("EV=")    ,
                                                                    __L("KEY=")   ,
                                                                    __L("ABS=")   ,
                                                                    __L("REL=")   ,
                                                                    __L("MSC=")   
                                                                  };

                                                for(int d=0; d< (sizeof(prefix) / sizeof(XCHAR*)); d++)   
                                                  {
                                                    index = line.Find(prefix[d], true);
                                                    if(index != XSTRING_NOTFOUND)
                                                      {
                                                        switch(d)
                                                          {
                                                            case 0  : break;

                                                            case 1  : { XSTRING ev_str;

                                                                        ev_str.AdjustSize(_MAXSTR);
                                                                        line.Copy(index+3, ev_str);
                                                                        ev_str.AdjustSize();

                                                                        if(!ev_str.Compare(__L("120013"), true)) deviceID->SetType(INPDEVICE_TYPE_KEYBOARD);  
                                                                        if(!ev_str.Compare(__L("17"), true))     deviceID->SetType(INPDEVICE_TYPE_MOUSE);                                                                                                                        
                                                                        if(!ev_str.Compare(__L("b"), true))      deviceID->SetType(INPDEVICE_TYPE_TOUCHSCREEN);                                                                                                                        
                                                                      }
                                                                      break;

                                                            case 2  : break;
                                                            case 3  : break;
                                                            case 4  : break;
                                                            case 5  : break;
                                                          }
                                                      }
                                                  }  
                                              }
                                              break;                                                                      
                                }

                              c++;


                            } while(1);
 
                                
                          if((deviceID->GetEventIndex() != INPLINUXDEVICEID_INVALID) && 
                             (typedevice == deviceID->GetType()))
                            {            

                              devices.Add(deviceID);
               
                              #ifdef XTRACE_ACTIVE
                              XSTRING typestr;
   
                              switch(deviceID->GetType())
                                { 
                                                      default       :   
                                  case INPDEVICE_TYPE_NONE          : typestr = __L("Unkwown");       break;
                                  case INPDEVICE_TYPE_KEYBOARD      : typestr = __L("Keyboard");      break;
                                  case INPDEVICE_TYPE_MOUSE         : typestr = __L("Mouse");         break;
                                  case INPDEVICE_TYPE_JOSTICK       : typestr = __L("Jostick");       break;
                                  case INPDEVICE_TYPE_TOUCHSCREEN   : typestr = __L("TouchScreen");   break;
                                  case INPDEVICE_TYPE_WIIMOTE       : typestr = __L("WII Mote");      break;
                                }

                              XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Input Device] Event [%d] Type: %15s Device [%s]"), deviceID->GetEventIndex(), typestr.Get(), deviceID->GetName()->Get());                         
                              #endif                                               
                            } 
                           else delete deviceID;                                 
                        }   
                    }
                }
            }

          xfiletxtdevices->Close();
        }

      delete xfiletxtdevices;
    }

  */

  devices.DeleteContents();
  devices.DeleteAll();

  return status;
}

#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE::Test_Hash(HASH* HASH, XBUFFER& input, XCHAR* leyend)
* @brief      Test_Hash
* @ingroup    APPLICATION
*
* @param[in]  HASH :
* @param[in]  input :
* @param[in]  leyend :
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_Hash(HASH* HASH, XBUFFER& input, XCHAR* leyend)
{
  if(!HASH) return false;

  XSTRING result;

  HASH->Do(input);

  HASH->GetResultString(result);

  console->Printf(__L("%-12s : %s\n"), leyend, result.Get());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCONSOLE::Test_WaitSound(SNDITEM* item)
* @brief      Test_WaitSound
* @ingroup    APPLICATION
* 
* @param[in]  item : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE::Test_WaitSound(SNDITEM* item)
{
  #ifdef SND_ACTIVE
  APPFLOW_EXTENDED.ShowAll();
  devtestsconsole->Show_PlaySound();
    
  for(int c=0; c<10; c++)
    { 
      if(item)
        {             
          if(item->GetNTimesToPlay() == SNDFACTORY_UNDEFINED)
            {
              if(devtestsconsole->console->KBHit()) 
                {
                  devtestsconsole->console->GetChar();

                  return false;
                }
            }
        }

      GEN_XSLEEP.MilliSeconds(5);
    }
   #endif   
   return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCONSOLE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent_Scheduler(XSCHEDULER_XEVENT* event)
{  
  switch(event->GetTask()->GetID())
    {
      case DEVTESTSCONSOLE_TASKID_TEST  : { XSTRING string;

                                            event->GetDateTime()->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
                                            console->Printf(__L("%s: [Task] event ...\n"), string.Get());
                                          }
                                          break;
    } 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCONSOLE::HandleEvent_Sound(SNDFACTORY_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent_Sound(SNDFACTORY_XEVENT* event)
{  
  #ifdef SND_ACTIVE
  switch(event->GetEventType())
    {
      case SNDFACTORY_XEVENT_TYPE_SOUND_INI     : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_PLAY    : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_PAUSE   : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_STOP    : 
      case SNDFACTORY_XEVENT_TYPE_SOUND_END     : { XSTRING  typestr;
                                                    XSTRING  statusstr;
                                                    XSTRING* ID;  
                                                    
                                                    event->GetItem()->GetType(typestr);
                                                    event->GetItem()->GetStatus(statusstr);
                                                    ID = event->GetItem()->GetID();      

                                                    XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Sound] [%08X] %s (%s) -> %s"), event->GetItem(), typestr.Get(), ID->Get(), statusstr.Get());    
                                                  } 
                                                  break;
    }  
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCONSOLE::HandleEvent_WebClient(DIOWEBCLIENT_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
*
* @param[in]  event :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent_WebClient(DIOWEBCLIENT_XEVENT* event)
{
  XSTRING line;
  DIOURL  URLweb;

  if(event->GetURL()) URLweb = event->GetURL()->Get();

  switch(event->GetEventType())
    {
      case DIOWEBCLIENT_XEVENT_TYPE_OPENWEB         :
      case DIOWEBCLIENT_XEVENT_TYPE_WRITEHEADER     :
      case DIOWEBCLIENT_XEVENT_TYPE_SENDPOSTDATA    :
      case DIOWEBCLIENT_XEVENT_TYPE_HEADERERROR     :
      case DIOWEBCLIENT_XEVENT_TYPE_READHEADER      : { line.Format(__L("Inicializando descarga [%s]")  , URLweb.Get());

                                                        console->PrintMessage(line.Get() , 4, true, false);
                                                        console->EraseToEndLine(line.GetSize()+4);
                                                        console->PrintMessage(__L("\r"), 0, false, false);
                                                      }
                                                      break;

      case DIOWEBCLIENT_XEVENT_TYPE_READBODYBLOCK   : { line.Format(__L("Descargando [%s] -> %d Kb ")  , URLweb.Get(), (event->GetDownloadSize() / 1024));

                                                        if(event->GetContentLenght()) line.AddFormat(__L("(%3.2f%%) "), event->GetOperationPercent());

                                                        line.AddFormat(__L("[%d Mbps] "), event->GetMBPSSpeed());

                                                        console->PrintMessage(line.Get() , 4, true, false);
                                                        console->EraseToEndLine(line.GetSize()+4);
                                                        console->PrintMessage(__L("\r"), 0, false, false);
                                                      }
                                                      break;

      case DIOWEBCLIENT_XEVENT_TYPE_CLOSEWEB        : console->PrintMessage(__L(" "), 0, false, true);
                                                      break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCONSOLE::HandleEvent_DNSProtocol_MitM_Server(DIODNSPROTOCOL_MITM_SERVER_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent_DNSProtocol_MitM_Server(DIODNSPROTOCOL_MITM_SERVER_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ASKDNS      : { XSTRING originIP;

                                                                  event->GetOriginIP()->GetXString(originIP);

                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Ask DNS Protocol] (%s)"), event->GetAskedURL()->Get()); 
                                                                  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, (*event->GetAskedBuffer())); 
                                                                }
                                                                break;

      case DIODNSPROTOCOL_MITM_SERVER_XEVENT_TYPE_ANSWERDNS   : { XSTRING originIP;

                                                                  event->GetOriginIP()->GetXString(originIP);

                                                                  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Answer DNS Protocol] (%s)"), event->GetAskedURL()->Get()); 
                                                                  XTRACE_PRINTDATABLOCKCOLOR(XTRACE_COLOR_BLUE, (*event->GetAnsweredBuffer())); 
                                                                }
                                                                break;
    

    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCONSOLE::HandleEvent_DIOStream(DIOSTREAM_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    TESTS
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent_DIOStream(DIOSTREAM_XEVENT* event)
{
  if(!event) 
    {
      return;
    }

  switch(event->GetEventType())
    {
      case DIOSTREAM_XEVENT_TYPE_CONNECTED     : { 
                                                  int a=0;
                                                  a++;               
                                                }
                                                break;

      case DIOSTREAM_XEVENT_TYPE_DISCONNECTED  : { 
                                                  int a=0;
                                                  a++;               
                                                }
                                                break;
    }

}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCONSOLE::HandleEvent
* @brief      Handle Events
* @ingroup
*
* @param[]    xevent : event send to control
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::HandleEvent(XEVENT* xevent)
{
  if(!xevent) 
    {
      return;
    }

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_SCHEDULER        : { XSCHEDULER_XEVENT* event = (XSCHEDULER_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Scheduler(event);
                                          }
                                          break;
      #ifdef SND_ACTIVE
      case XEVENT_TYPE_SOUND            : { SNDFACTORY_XEVENT* event = (SNDFACTORY_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_Sound(event);
                                          }
                                          break;
      #endif

      case XEVENT_TYPE_WEBCLIENT        : { DIOWEBCLIENT_XEVENT* event = (DIOWEBCLIENT_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_WebClient(event);
                                          }
                                          break;

      case XEVENT_TYPE_DIODNS           : { DIODNSPROTOCOL_MITM_SERVER_XEVENT* event = (DIODNSPROTOCOL_MITM_SERVER_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_DNSProtocol_MitM_Server(event);
                                          }
                                          break;

      case XEVENT_TYPE_DIOSTREAM        : { DIOSTREAM_XEVENT* event = (DIOSTREAM_XEVENT*)xevent;
                                            if(!event) return;

                                            HandleEvent_DIOStream(event);
                                          }
                                          break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCONSOLE::ThreadRunFunction(void* param)
* @brief      ThreadRunFunction
* @ingroup    APPLICATION
*
* @param[in]  param :
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::ThreadRunFunction(void* param)
{
  DEVTESTSCONSOLE_XTHREADPARAM* threadparam = (DEVTESTSCONSOLE_XTHREADPARAM*)param;
  if(!threadparam) return;

  //threadparam->devtestconsole->xmutexthread->Lock();
  
  XTRACE_PRINTCOLOR(threadparam->index+1, __L("[%02d] Into Thread ...."), threadparam->index);

  /*
  switch(threadparam->index)
    {
      case 0  : GEN_XSLEEP.MilliSeconds(100);   break;
      case 1  : GEN_XSLEEP.MilliSeconds(600);   break;
      case 2  : GEN_XSLEEP.MilliSeconds(900);   break;
      case 3  : GEN_XSLEEP.MilliSeconds( 50);   break;
      case 4  : GEN_XSLEEP.MilliSeconds(250);   break;
      default : GEN_XSLEEP.MilliSeconds(150);   break;
    }  
  */

  //threadparam->devtestconsole->xmutexthread->UnLock();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCONSOLE::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE::Clean()
{  
  xtimerupdateconsole         = NULL;

  xmutexthread                = NULL;
}

#pragma endregion