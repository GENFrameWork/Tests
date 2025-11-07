# --------------------------------------------------------------------
# DevTestsConsole : Develped Tests (Console mode)
# GEN FrameWork.
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(devtestsconsole)


set(GEN_DIRECTORY "../../../../GEN_FrameWork") 


# Compile Selection
include("${GEN_DIRECTORY}/Common/CMake/Main/GEN_CMakeLists_Main_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with the Internet"        ON )                        
option(XFEEDBACK_CONTROL_FEATURE                                "XFeedback Control"                                       ON )  

option(LINUX_X11_FEATURE                                        "Linux X11"                                               ON )

option(XTHREADCOLLECTED_FEATURE                                 "Thread Collected"                                        ON )

option(ANONYMOUS_MODE_FEATURE                                   "Activate Anonymous mode"                                 false )
    
option(XSHAREDMEMORYMANAGER_FEATURE                             "Shared Memory Manager"                                   ON )
option(XPROCESSMANAGER_FEATURE                                  "Process Manager"                                         ON )
option(XLICENSE_FEATURE                                         "License functions"                                       ON )
    
option(XSERIALIZABLE_BINARY_FEATURE                             "Serializable Binary"                                     ON )
option(XSERIALIZABLE_JSON_FEATURE                               "Serializable JSON"                                       ON )
    
option(XFILE_HEX_FEATURE                                        "XFile HEX format"                                        ON )  
option(XFILE_DFU_FEATURE                                        "XFile DFU format"                                        ON )  
option(XFILE_RIFF_FEATURE                                       "XFile RIFF format"                                       ON ) 
option(XFILE_ZIP_FEATURE                                        "XFile Zip format"                                        ON )
    
option(HASH_FEATURE                                             "Hash"                                                    ON )
option(HASH_CRC16_FEATURE                                       "Hash CRC16"                                              ON )  
option(HASH_CKS16_FEATURE                                       "Hash CKS16"                                              ON )  
option(HASH_CRC32_FEATURE                                       "Hash CRC32"                                              ON )
option(HASH_MD5_FEATURE                                         "Hash MD5"                                                ON )
option(HASH_SHA1_FEATURE                                        "Hash SHA1"                                               ON )    
option(HASH_SHA2_FEATURE                                        "Hash SHA2"                                               ON )
option(HASH_COMP128V1_FEATURE                                   "Hash COMP128V1"                                          ON )
option(HASH_WHIRLPOOL_FEATURE                                   "Hash Whirlpool"                                          ON )    
option(CIPHER_SYMMETRIC_FEATURE                                 "Cipher Symetric"                                         ON )
option(CIPHER_SYMMETRIC_DES_FEATURE                             "Cipher Symetric DES"                                     ON )
option(CIPHER_SYMMETRIC_AES_FEATURE                             "Cipher Symetric AES"                                     ON )
option(CIPHER_SYMMETRIC_BLOWFISH_FEATURE                        "Cipher Symetric BlowFish"                                ON )
option(CIPHER_ASYMMETRIC_FEATURE                                "Cipher Asymetric"                                        ON ) 
option(CIPHER_ASYMMETRIC_FILEKEY_GFK                            "Cipher Asymetric File Key (.Gen Key File)"               ON ) 
option(CIPHER_ASYMMETRIC_FILEKEY_PEM                            "Cipher Asymetric File Key (.PEM)"                        ON ) 
option(CIPHER_ASYMMETRIC_RSA_FEATURE                            "Cipher Asymetric RSA"                                    ON ) 
option(CIPHER_ASYMMETRIC_X25519_FEATURE                         "Cipher Asimetric ECDSA X25519"                           ON ) 
        
option(DIO_FEATURE                                              "Data Input/Output"                                       ON ) 
option(DIO_STREAMUART_FEATURE                                   "Data Input/Output Stream UART"                           ON )
#option(DIO_STREAMBLUETOOTH_FEATURE                              "Data Input/Output Stream Bluetooth"                      ON )
#option(DIO_STREAMBLUETOOTHLE_FEATURE                            "Data Input/Output Stream Bluetooth LE"                   ON )
option(DIO_STREAMTCPIP_FEATURE                                  "Stream TCPIP"                                            ON )
#option(DIO_STREAMWIFI_FEATURE                                   "Data Input/Output Stream Wifi"                           ON )
option(DIO_STREAMTLS_FEATURE                                    "Data Input/Output Stream TLS"                            ON )
option(DIO_CHECKCONNECTIONS_FEATURE                             "Check Connections"                                       ON )
option(DIO_NETWORKTIMEPROTOCOL_FEATURE                          "Network Time Protocol"                                   ON )
option(DIO_DYNDNS_FEATURE                                       "DynDNS"                                                  ON )
option(DIO_SCRAPERWEB_FEATURE                                   "Scraper Web"                                             ON )
option(DIO_GPIO_FEATURE                                         "Data Input/Output GPIO"                                  ON )
option(DIO_STREAMI2C_FEATURE                                    "Data Input/Output Stream I2C"                            ON )
option(DIO_STREAMI2C_GPIO_MCP2317_FEATURE                       "Data I2C GPIO MCP2317"                                   ON )
option(DIO_STREAMSPI_FEATURE                                    "Data Input/Output Stream SPI"                            ON )
option(DIO_STREAMSPI_GPIO_MCP23S17_FEATURE                      "Data SPI GPIO MCP23S17"                                  ON )
option(DIO_SPI_GPIO_MCP23S17_FEATURE                            "Data SPI GPIO MCP23S17"                                  ON )   
option(DIO_ATCMD_FEATURE                                        "AT Commands"                                             ON )
option(DIO_WAKEONLAN_FEATURE                                    "Data Input/Output WakeON Lan"                            ON )
option(DIO_MPSSE_FEATURE                                        "Data Input/Output MPSSE"                                 ON )     
option(DIO_ALERTS_FEATURE                                       "Data Input/Output Alerts"                                ON )  
option(DIO_ONOTIFICATIONS_MANAGER_FEATURE                       "Notifications Nanager"                                   ON )
option(DIO_WIFIMANAGERMODE_FEATURE                              "Data Input/Output Wifi Manager Mode"                     ON ) 
option(DIO_SNMP_FEATURE                                         "SNMP (Simple Network Management Protocol)"               ON )
option(DIO_MODBUSCLIENT_FEATURE                                 "Data Input/Output ModBus Client (UART/TCPIP)"            ON )
option(DIO_BUSPIRATE_FEATURE                                    "Data Input/Output Bus Pirate 4.0"                        ON )
option(DIO_LEDNEOPIXELWS2812B_FEATURE                           "Data Input/Output Led Neopixel WS2812B"                  ON ) 
option(DIO_PROTOCOL_CLI_BUS_FEATURE                             "Data Input/Output Protocol in CLI Bus"                   ON )
#option(DIO_PCAP_FEATURE                                         "Data Input/Output Cap"                                   ON )
option(DIO_IEC60870_5_FEATURE                                   "IEC60870_5 Protocol"                                     ON ) 
option(DIO_DNSPROTOCOL_MITM_SERVER                              "DNS Protocol Man in the Middle Server"                   ON )
option(DIO_DYNDNS_FEATURE                                       "DynDNS"                                                  ON )
option(DIO_WEBSERVER_RESOLVEENDPOINT_FEATURE                    "Web Server Resolved End Point"                           ON )
option(DIO_COREPROTOCOL_FEATURE                                 "Core Protocol"                                           ON )
    

#option(DIO_STREAMSPI_LCDDISPLAY_PCF8833_FEATURE                 "Data SPI LCD Display PCF8833"                            ON )  
#option(DIO_STREAMSPI_OLEDDISPLAY_SSD1306_FEATURE                "Data SPI OLED Display SSD1306"                           ON )
#option(DIO_STREAMSPI_OLEDDISPLAY_SSD1331_FEATURE                "Data SPI OLED Display SSD1331"                           ON )
#option(DIO_STREAMSPI_TFTDISPLAY_ILI9341_FEATURE                 "Data SPI TFT Display ILI9341"                            ON )
#option(DIO_STREAMSPI_TFTDISPLAY_ST7789_FEATURE                  "Data SPI TFT Display ST7789"                             ON )
#option(DIO_STREAMSPI_TOUCHSCREEN_STMPE610_FEATURE               "Data SPI Touch Screen STMPE610"                          ON )
    
#option(INP_FEATURE                                              "Inputs"                                                  ON )
#option(INP_SIMULATE_FEATURE                                     "Inputs Simulate"                                         ON )
#option(INP_CAPTURE_FEATURE                                      "Inputs Capture"                                          ON )
    
#option(SND_FEATURE                                              "Sound"                                                   ON )
#option(SND_FILE_WAV_FEATURE                                     "Sound WAV file"                                          ON )
#option(SND_FILE_OGG_FEATURE                                     "Sound OGG file"                                          ON )
    
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )  
option(APPFLOW_EXTENDED_APPLICATIONHEADER_FEATURE               "Application Flow Extended Aplication Header"             ON )
option(APPFLOW_EXTENDED_APPLICATIONSTATUS_FEATURE               "Application Flow Extended Aplication Status"             ON )  
option(APPFLOW_EXTENDED_INTERNETSTATUS_FEATURE                  "Application Flow Extended Internet Status"               ON )  
option(APPFLOW_CHECKRESOURCESHARDWARE_FEATURE                   "Application Flow Check Resources Hardwar"                ON )
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_INTERNETSERVICES_FEATURE                         "Application Flow Internet Services"                      ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
option(APPFLOW_ALERTS_FEATURE                                   "Application Flow Alerts"                                 ON )
                                                                             
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
option(APPFLOW_CFG_INTERNETSERVICES_FEATURE                     "Application Flow CFG Internet services"                  ON )      
option(APPFLOW_CFG_DYNDNSMANAGER_FEATURE                        "Application Flow CFG DynDNS Manager"                     ON )
option(APPFLOW_CFG_CHECKRESOURCESHARDWARE_FEATURE               "Application Flow CFG Check Resorces HW"                  ON )  
option(APPFLOW_CFG_DNSRESOLVER_FEATURE                          "Application Flow CFG DNS "                               ON )  
option(APPFLOW_CFG_ALERTS_FEATURE                               "Application Flow CFG Alerts"                             ON )  
option(APPFLOW_CFG_DIOLOCATION_FEATURE                          "Application Flow CFG Location"                           ON )  

option(IDENTIFICATION_FEATURE                                   "Identification"                                          ON )
     
if(COMPILE_FOR_WINDOWS)   
    
  option(WINDOWS_XDESKTOPMANAGER_FEATURE                        "Windows Desktop Manager"                                 ON )
  option(WINDOWS_XVIRTUALDESKTOPMANAGER_FEATURE                 "Windows Virtual Desktop Manager"                         ON )
      
endif()   
    
    
if(COMPILE_FOR_LINUX)   
    
  #option(DIO_LINUX_DBUS_FEATURE                                 "Linux DBus"                                              ON ) 
  #option(DIO_LINUX_NETWORKMANAGER_FEATURE                       "Linux Network Manager"                                   ON )
    
endif()


# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_DEVTESTSCONSOLE "-DAPPFLOW_CFG=DEVTESTSCONSOLE_CFG::GetInstance()")
add_definitions(${APP_CFG_DEVTESTSCONSOLE})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 

                        
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application 

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOPiFace.cpp")   
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOTemHumSensorAM2301.cpp")  
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY_SOURCES_DATAIO_STREAMS}/DIOStreamUDPAcknowledge.cpp") 
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY_SOURCES_DATAIO_PROTOCOLS}/DIOModBusElectricMeter.cpp")      
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY_SOURCES_DATAIO}/DIOXTraceInterStreams.cpp")
 
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsConsole.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_CFG.cpp")

if(COMPILE_FOR_WINDOWS)

  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_WindowsPlatform.cpp")

endif()

if(COMPILE_FOR_LINUX)  

  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_LinuxPlatform.cpp")

endif()


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

