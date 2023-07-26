# --------------------------------------------------------------------
# DevTestsConsole : GEN Develped Tests Console mode
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.6.0)
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

 option(DEBUG_FEATURE                                       "Debug mode"                                                true )
 option(XTRACE_FEATURE                                      "XTrace"                                                    true )
#option(XTRACE_NOINTERNET_FEATURE                           "No need for trace dependencies with the Internet"          true )                        
 option(XMEMORY_CONTROL_FEATURE                             "XMemory Control"                                           true )

 option(XSHAREDMEMORYMANAGER_FEATURE                        "Shared Memory Manager"                                     true )
 option(XPROCESSMANAGER_FEATURE                             "Process Manager"                                           true )
 option(XLICENSE_FEATURE                                    "License functions"                                         true )

 option(XSERIALIZABLE_BINARY_FEATURE                        "Serializable Binary"                                       true )
 option(XSERIALIZABLE_JSON_FEATURE                          "Serializable JSON"                                         true )

 option(XFILE_HEX_FEATURE                                   "XFile HEX format"                                          true )  
 option(XFILE_DFU_FEATURE                                   "XFile DFU format"                                          true )  
 option(XFILE_RIFF_FEATURE                                  "XFile RIFF format"                                         true ) 

 option(XTESTSMANAGER_FEATURE                               "Tests Manager"                                             true )
  
 option(HASH_FEATURE                                        "Hash"                                                      true )
 option(HASH_CRC16_FEATURE                                  "Hash CRC16"                                                true )  
 option(HASH_CKS16_FEATURE                                  "Hash CKS16"                                                true )  
 option(HASH_CRC32_FEATURE                                  "Hash CRC32"                                                true )
 option(HASH_MD5_FEATURE                                    "Hash MD5"                                                  true )
 option(HASH_SHA1_FEATURE                                   "Hash SHA1"                                                 true )    
 option(HASH_SHA2_FEATURE                                   "Hash SHA2"                                                 true )
 option(HASH_COMP128V1_FEATURE                              "Hash COMP128V1"                                            true )
 option(HASH_WHIRLPOOL_FEATURE                              "Hash Whirlpool"                                            true )    
 option(CIPHER_SYMMETRIC_FEATURE                            "Cipher Symetric"                                           true )
 option(CIPHER_SYMMETRIC_DES_FEATURE                        "Cipher Symetric DES"                                       true )
 option(CIPHER_SYMMETRIC_AES_FEATURE                        "Cipher Symetric AES"                                       true )
 option(CIPHER_SYMMETRIC_BLOWFISH_FEATURE                   "Cipher Symetric BlowFish"                                  true )
 option(CIPHER_ASYMMETRIC_FEATURE                           "Cipher Asymetric"                                          true ) 
 option(CIPHER_ASYMMETRIC_FILEKEY_GFK                       "Cipher Asymetric File Key (.Gen Key File)"                 true ) 
 option(CIPHER_ASYMMETRIC_FILEKEY_PEM                       "Cipher Asymetric File Key (.PEM)"                          true ) 
 option(CIPHER_ASYMMETRIC_RSA_FEATURE                       "Cipher ASymetric RSA"                                      true ) 
 option(CIPHER_ASYMMETRIC_CURVE25519_FEATURE                "Cipher ASymetric Curve25519"                               true ) 

 option(COMPRESS_GZ_FEATURE                                 "Compres GZ"                                                true )  
 option(COMPRESS_LZRW1KH_FEATURE                            "Compres LZRW1KH"                                           true )  
 option(COMPRESS_LZW_FEATURE                                "Compres LZW"                                               true )  
 option(COMPRESS_ZIP_FEATURE                                "Compres ZIP"                                               true )  

 option(DIO_FEATURE                                         "Data Input/Output"                                         true ) 
 option(DIO_STREAMUART_FEATURE                              "Data Input/Output Stream UART"                             true )
 option(DIO_STREAMBLUETOOTH_FEATURE                         "Data Input/Output Stream Bluetooth"                        true )
 option(DIO_STREAMBLUETOOTHLE_FEATURE                       "Data Input/Output Stream Bluetooth LE"                     true )
 option(DIO_STREAMWIFI_FEATURE                              "Data Input/Output Stream Wifi"                             true )
 option(DIO_STREAMTLS_FEATURE                               "Data Input/Output Stream TLS"                              true )
 option(DIO_CHECKCONNECTIONS_FEATURE                        "Check Connections"                                         true )
 option(DIO_NETWORKTINEPROTOCOL_FEATURE                     "Network Time Protocol"                                     true )
 option(DIO_DYNDNS_FEATURE                                  "DynDNS"                                                    true )
 option(DIO_SCRAPERWEB_FEATURE                              "Scraper Web"                                               true )
 option(DIO_GPIO_FEATURE                                    "Data Input/Output GPIO"                                    true )
 option(DIO_STREAMI2C_FEATURE                               "Data Input/Output Stream I2C"                              true )
 option(DIO_I2C_GPIO_MCP2317_FEATURE                        "Data I2C GPIO MCP2317"                                     true )
 option(DIO_STREAMSPI_FEATURE                               "Data Input/Output Stream SPI"                              true )
 option(DIO_SPI_GPIO_MCP23S17_FEATURE                       "Data SPI GPIO MCP23S17"                                    true )   
 option(DIO_ATCMD_FEATURE                                   "AT Commands"                                               true )
 option(DIO_WAKEONLAN_FEATURE                               "Data Input/Output WakeON Lan"                              true )
 option(DIO_MPSSE_FEATURE                                   "Data Input/Output MPSSE"                                   true )     
 option(DIO_ALERTS_FEATURE                                  "Data Input/Output Alerts"                                  true )  
 option(DIO_ONOTIFICATIONS_MANAGER_FEATURE                  "Notifications Nanager"                                     true )
 option(DIO_WIFIMANAGERMODE_FEATURE                         "Data Input/Output Wifi Manager Mode"                       true ) 
#option(DIO_SNMP_FEATURE                                    "SNMP (Simple Network Management Protocol)"                 true )
 option(DIO_BUSPIRATE_FEATURE                               "Data Input/Output Bus Pirate 4.0"                          true )
 option(DIO_MODBUSCLIENT_FEATURE                            "Data Input/Output ModBus Client (UART/TCPIP)"              true )
 option(DIO_LEDNEOPIXELWS2812B_FEATURE                      "Data Input/Output Led Neopixel WS2812B"                    true ) 
 option(DIO_PROTOCOL_CLI_BUS_FEATURE                        "Data Input/Output Protocol in CLI Bus"                     true )
#option(DIO_PCAP_FEATURE                                    "Data Input/Output Cap"                                     true )
 option(DIO_IEC60870_5_FEATURE                              "IEC60870_5 Protocol"                                       true )  


 option(DIO_STREAMSPI_FEATURE                               "Data Input/Output Stream SPI"                              true )  
 option(DIO_SPI_GPIO_MCP23S17_FEATURE                       "Data SPI GPIO MCP23S17"                                    true )
 option(DIO_SPI_LCDDISPLAY_PCF8833_FEATURE                  "Data SPI LCD Display PCF8833"                              true )  
 option(DIO_SPI_OLEDDISPLAY_SSD1306_FEATURE                 "Data SPI OLED Display SSD1306"                             true )
 option(DIO_SPI_OLEDDISPLAY_SSD1331_FEATURE                 "Data SPI OLED Display SSD1331"                             true )
 option(DIO_SPI_TFTDISPLAY_ILI9341_FEATURE                  "Data SPI TFT Display ILI9341"                              true )
 option(DIO_SPI_TFTDISPLAY_ST7789_FEATURE                   "Data SPI TFT Display ST7789"                               true )
 option(DIO_SPI_TOUCHSCREEN_STMPE610_FEATURE                "Data SPI Touch Screen STMPE610"                            true )

 if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

  option(DIO_LINUX_DBUS_FEATURE                             "Linux DBus"                                                true ) 
  option(DIO_LINUX_NETWORKMANAGER_FEATURE                   "Linux Network Manager"                                     true )

 endif()

#option(SND_FEATURE                                         "Sound"                                                     true )

 option(INP_FEATURE                                         "Inputs"                                                    true )
 option(INP_SIMULATE_FEATURE                               "Inputs Simulate"                                          true )
 option(INP_CAPTURE_FEATURE                                 "Inputs Capture"                                            true )

 option(APP_FEATURE                                         "Application modules"                                       true )
 option(APP_CHECKRESOURCESHARDWARE_FEATURE                  "Application Check Resources Hardwar"                       true )
 option(APP_CONSOLE_FEATURE                                 "Application Console"                                       true )
 option(APP_INTERNETSERVICES_FEATURE                        "Application Internet Services"                             true )
 option(APP_LOG_FEATURE                                     "Application Log"                                           true )
 option(APP_ALERTS_FEATURE                                  "Application Alerts"                                        true )
 option(APP_CFG_REMOTEFILE_FEATURE                          "Application CFG Remote File"                               true )

 option(APP_CFG_GENERAL_FEATURE                             "Application CFG General"                                   true )  
 option(APP_CFG_LOG_FEATURE                                 "Application CFG LOG"                                       true )
 option(APP_CFG_INTERNETSERVICES_FEATURE                    "Application CFG Internet services"                         true )      
 option(APP_CFG_DYNDNSMANAGER_FEATURE                       "Application CFG DynDNS Manager"                            true )
 option(APP_CFG_CHECKRESOURCESHARDWARE_FEATURE              "Application CFG Check Resorces HW"                         true )  
 option(APP_CFG_DNSRESOLVED_FEATURE                         "Application CFG DNS Resolved"                              true )  
 option(APP_CFG_ALERTS_FEATURE                              "Application CFG Alerts"                                    true )  


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

 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOPiFace.cpp")   
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_DRIVERS}/DIOTemHumSensorAM2301.cpp")  
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO_STREAMS}/DIOStreamUDPAcknowledge.cpp") 
 list(APPEND SOURCES "${GEN_DIRECTORY_SOURCES_DATAIO}/DIOModBusElectricMeter.cpp")      
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

