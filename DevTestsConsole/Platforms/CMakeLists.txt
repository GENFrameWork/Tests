# --------------------------------------------------------------------
# DevTestsConsole : GEN Develped Tests Console mode
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(devtestsconsole)


 set(GEN_DIRECTORY "../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Platform-Compiler.txt") 


# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
 option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
#option(XTRACE_NOINTERNET_FEATURE                           "Activate No need for trace dependencies with the Internet"  true )                        
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )

 option(XSHAREDMEMORYMANAGER_FEATURE                        "Activate Shared Memory Manager"                             true )
 option(XPROCESSMANAGER_FEATURE                             "Activate Process Manager"                                   true )
 option(XLICENSE_FEATURE                                    "Activate License functions"                                 true )

 option(XSERIALIZABLE_BINARY_FEATURE                        "Activate Serializable Binary"                               true )
 option(XSERIALIZABLE_JSON_FEATURE                          "Activate Serializable JSON"                                 true )

 option(XFILE_HEX_FEATURE                                   "Activate XFile HEX format"                                  true )  
 option(XFILE_DFU_FEATURE                                   "Activate XFile DFU format"                                  true )  
 option(XFILE_RIFF_FEATURE                                  "Activate XFile RIFF format"                                 true ) 

 option(XTESTSMANAGER_FEATURE                               "Activate Tests Manager"                                     true )
  
 option(HASH_FEATURE                                        "Activate Hash"                                              true )
 option(HASH_CRC16_FEATURE                                  "Activate Hash CRC16"                                        true )  
 option(HASH_CKS16_FEATURE                                  "Activate Hash CKS16"                                        true )  
 option(HASH_CRC32_FEATURE                                  "Activate Hash CRC32"                                        true )
 option(HASH_MD5_FEATURE                                    "Activate Hash MD5"                                          true )
 option(HASH_SHA1_FEATURE                                   "Activate Hash SHA1"                                         true )    
 option(HASH_SHA2_FEATURE                                   "Activate Hash SHA2"                                         true )
 option(HASH_COMP128V1_FEATURE                              "Activate Hash COMP128V1"                                    true )
 option(HASH_WHIRLPOOL_FEATURE                              "Activate Hash Whirlpool"                                    true )    
 option(CIPHER_SYMMETRIC_FEATURE                            "Activate Cipher Symetric"                                   true )
 option(CIPHER_SYMMETRIC_DES_FEATURE                        "Activate Cipher Symetric DES"                               true )
 option(CIPHER_SYMMETRIC_AES_FEATURE                        "Activate Cipher Symetric AES"                               true )
 option(CIPHER_SYMMETRIC_BLOWFISH_FEATURE                   "Activate Cipher Symetric BlowFish"                          true )
 option(CIPHER_ASYMMETRIC_FEATURE                           "Activate Cipher Asymetric"                                  true ) 
 option(CIPHER_ASYMMETRIC_FILEKEY_GFK                       "Activate Cipher Asymetric File Key (.Gen Key File)"         true ) 
 option(CIPHER_ASYMMETRIC_FILEKEY_PEM                       "Activate Cipher Asymetric File Key (.PEM)"                  true ) 
 option(CIPHER_ASYMMETRIC_RSA_FEATURE                       "Activate Cipher ASymetric RSA"                              true ) 
 option(CIPHER_ASYMMETRIC_CURVE25519_FEATURE                "Activate Cipher ASymetric Curve25519"                       true ) 

 option(COMPRESS_GZ_FEATURE                                 "Activate Compres GZ"                                        true )  
 option(COMPRESS_LZRW1KH_FEATURE                            "Activate Compres LZRW1KH"                                   true )  
 option(COMPRESS_LZW_FEATURE                                "Activate Compres LZW"                                       true )  
 option(COMPRESS_ZIP_FEATURE                                "Activate Compres ZIP"                                       true )  

 option(DIO_FEATURE                                         "Activate Data Input/Output"                                 true ) 
 option(DIO_STREAMUART_FEATURE                              "Activate Data Input/Output Stream UART"                     true )
 option(DIO_STREAMBLUETOOTH_FEATURE                         "Activate Data Input/Output Stream Bluetooth"                true )
 option(DIO_STREAMBLUETOOTHLE_FEATURE                       "Activate Data Input/Output Stream Bluetooth LE"             true )
 option(DIO_STREAMWIFI_FEATURE                              "Activate Data Input/Output Stream Wifi"                     true )
 option(DIO_STREAMTLS_FEATURE                               "Activate Data Input/Output Stream TLS"                      true )
 option(DIO_CHECKCONNECTIONS_FEATURE                        "Activate Check Connections"                                 true )
 option(DIO_NETWORKTINEPROTOCOL_FEATURE                     "Activate Network Time Protocol"                             true )
 option(DIO_DYNDNS_FEATURE                                  "Activate DynDNS"                                            true )
 option(DIO_SCRAPERWEB_FEATURE                              "Activate Scraper Web"                                       true )
 option(DIO_GPIO_FEATURE                                    "Activate Data Input/Output GPIO"                            true )
 option(DIO_STREAMI2C_FEATURE                               "Activate Data Input/Output Stream I2C"                      true )
 option(DIO_I2C_GPIO_MCP2317_FEATURE                        "Activate Data I2C GPIO MCP2317"                             true )
 option(DIO_STREAMSPI_FEATURE                               "Activate Data Input/Output Stream SPI"                      true )
 option(DIO_SPI_GPIO_MCP23S17_FEATURE                       "Activate Data SPI GPIO MCP23S17"                            true )   
 option(DIO_ATCMD_FEATURE                                   "Activate AT Commands"                                       true )
 option(DIO_WAKEONLAN_FEATURE                               "Activate Data Input/Output WakeON Lan"                      true )
 option(DIO_MPSSE_FEATURE                                   "Activate Data Input/Output MPSSE"                           true )     
 option(DIO_ALERTS_FEATURE                                  "Activate Data Input/Output Alerts"                          true )  
 option(DIO_ONOTIFICATIONS_MANAGER_FEATURE                  "Activate Notifications Nanager"                             true )
 option(DIO_WIFIMANAGERMODE_FEATURE                         "Activate Data Input/Output Wifi Manager Mode"               true ) 
#option(DIO_SNMP_FEATURE                                    "Activate SNMP (Simple Network Management Protocol)"         true )
 option(DIO_BUSPIRATE_FEATURE                               "Activate Data Input/Output Bus Pirate 4.0"                  true )
 option(DIO_MODBUSCLIENT_FEATURE                            "Activate Data Input/Output ModBus Client (UART/TCPIP)"      true )
 option(DIO_LEDNEOPIXELWS2812B_FEATURE                      "Activate Data Input/Output Led Neopixel WS2812B"            true ) 
 option(DIO_PROTOCOL_CLI_BUS_FEATURE                        "Activate Data Input/Output Protocol in CLI Bus"             true )
#option(DIO_PCAP_FEATURE                                    "Activate Data Input/Output Cap"                             true )


 option(DIO_STREAMSPI_FEATURE                               "Activate Data Input/Output Stream SPI"                      true )  
 option(DIO_SPI_GPIO_MCP23S17_FEATURE                       "Activate Data SPI GPIO MCP23S17"                            true )
 option(DIO_SPI_LCDDISPLAY_PCF8833_FEATURE                  "Activate Data SPI LCD Display PCF8833"                      true )  
 option(DIO_SPI_OLEDDISPLAY_SSD1306_FEATURE                 "Activate Data SPI OLED Display SSD1306"                     true )
 option(DIO_SPI_OLEDDISPLAY_SSD1331_FEATURE                 "Activate Data SPI OLED Display SSD1331"                     true )
 option(DIO_SPI_TFTDISPLAY_ILI9341_FEATURE                  "Activate Data SPI TFT Display ILI9341"                      true )
 option(DIO_SPI_TFTDISPLAY_ST7789_FEATURE                   "Activate Data SPI TFT Display ST7789"                       true )
 option(DIO_SPI_TOUCHSCREEN_STMPE610_FEATURE                "Activate Data SPI Touch Screen STMPE610"                    true )

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
 option(DIO_LINUX_DBUS_FEATURE                              "Activate Linux DBus"                                        true ) 
 option(DIO_LINUX_NETWORKMANAGER_FEATURE                    "Activate Linux Network Manager"                             true )
endif()

#option(SND_FEATURE                                         "Activate Sound"                                             true )

 option(APP_FEATURE                                         "Activate Application modules"                               true )
 option(APP_CHECKRESOURCESHARDWARE_FEATURE                  "Activate Application Check Resources Hardwar"               true )
 option(APP_CONSOLE_FEATURE                                 "Activate Application Console"                               true )
 option(APP_INTERNETSERVICES_FEATURE                        "Activate Application Internet Services"                     true )
 option(APP_LOG_FEATURE                                     "Activate Application Log"                                   true )
 option(APP_ALERTS_FEATURE                                  "Activate Application Alerts"                                true )
 option(APP_CFG_REMOTEFILE_FEATURE                          "Activate Application CFG Remote File"                       true )

 option(APP_CFG_GENERAL_FEATURE                             "Activate Application CFG General"                           true )  
 option(APP_CFG_LOG_FEATURE                                 "Activate Application CFG LOG"                               true )
 option(APP_CFG_INTERNETSERVICES_FEATURE                    "Activate Application CFG Internet services"                 true )      
 option(APP_CFG_DYNDNSMANAGER_FEATURE                       "Activate Application CFG DynDNS Manager"                    true )
 option(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE              "Activate Application CFG Check Resorces HW"                 true )  
 option(APP_CFG_DNSRESOLVED_FEATURE                         "Activate Application CFG DNS Resolved"                      true )  
 option(APP_CFG_ALERTS_FEATURE                              "Activate Application CFG Alerts"                            true )  


# --------------------------------------------------------------------
# Config Application Macro

 set(APP_CFG_DEVTESTSCONSOLE "-DAPP_CFG=DEVTESTSCONSOLE_CFG::GetInstance()")
 add_definitions(${APP_CFG_DEVTESTSCONSOLE})


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 

                        
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application 

 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOIEC60870_5.cpp")
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO}/DIOModBusElectricMeter.cpp")      
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOPiFace.cpp")   
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO}/DIOStreamUDPAcknowledge.cpp")
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOTemHumSensorAM2301.cpp")
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO}/DIOXTraceInterStreams.cpp")

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsConsole.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_CFG.cpp")

 if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_WindowsPlatform.cpp")
 endif()

 if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsConsole_LinuxPlatform.cpp")
 endif()


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

