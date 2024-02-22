# --------------------------------------------------------------------
# DevTestsDevices : Developed Test Devices (include micros)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(devtestsdevices)


set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                          "Debug mode"                                              true )
option(XTRACE_FEATURE                                         "XTrace"                                                  true )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            true )
option(XMEMORY_CONTROL_FEATURE                                "XMemory Control"                                         true )
                                                                                                                        
option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                     "Linux CodePage Editor Visual Studio CP1252"              true )   
                                        
option(DIO_FEATURE                                            "Data Input/Output"                                       true ) 
option(DIO_STREAM_FEATURE                                     "Data Input/Output Stream"                                true )
option(DIO_STREAMUART_FEATURE                                 "Data Input/Output Stream UART"                           true )
option(DIO_STREAMUSB_FEATURE                                  "Data Input/Output Stream USB"                            true )
option(DIO_GPIO_FEATURE                                       "GPIO"                                                    true )
#option(DIO_GPIO_PCPARALLEL_FEATURE                            "Data Input/Output GPIO PC Parallel"                      true )
    
option(DIO_STREAMI2C_FEATURE                                  "Stream I2C"                                              true )
option(DIO_STREAMI2C_6AXISTRACKING_LSM303DLHC_FEATURE         "Stream I2C 6 axis tracking LSM303DLHC"                   true )
option(DIO_STREAMI2C_6AXISTRACKING_BMI270_FEATURE             "Stream I2C 6 axis tracking BMI270"                       true )
option(DIO_STREAMI2C_9AXISTRACKING_MPU9150_FEATURE            "Stream I2C 9 axis tracking MPU9150"                      true )
option(DIO_STREAMI2C_ADDACONVERTER_PCF8591_FEATURE            "Stream I2C ADDA converter PCF8591"                       true )
option(DIO_STREAMI2C_AIRQUALITY_CCS811_FEATURE                "Stream I2C Air quality CCS811"                           true )
option(DIO_STREAMI2C_EEPROM_24XXX_FEATURE                     "Stream I2C EEPROM 24XXX"                                 true )
option(DIO_STREAMI2C_GPIO_MCP2317_FEATURE                     "Stream I2C GPIO MCP2317"                                 true )
option(DIO_STREAMI2C_GPIO_PCF8574_FEATURE                     "Stream I2C GPIO PCF8574"                                 true )
option(DIO_STREAMI2C_LIGHTSENSOR_TSL2561_FEATURE              "Stream I2C Light sensor TSL2561"                         true )
option(DIO_STREAMI2C_OLEDDISPLAY_SSD1306_FEATURE              "Stream I2C OLED Display SSD1306"                         true )
option(DIO_STREAMI2C_PWMCONTROLER_PCA9685_FEATURE             "Stream I2C PWM Controler PCA9685"                        true )
option(DIO_STREAMI2C_TEMHUMSENSOR_AM2315_FEATURE              "Stream I2C Temperature Humidity Sensor AM2315"           true )
option(DIO_STREAMI2C_TEMHUMSENSOR_SHT20_FEATURE               "Stream I2C Temperature Humidity Sensor SHT20"            true )
option(DIO_STREAMI2C_MONITORGAUGE_LTC2942_FEATURE             "Stream I2C Monitor Gauge LTC2942"                        true )
option(DIO_STREAMI2C_BATTERYCHARGER_BQ24295_FEATURE           "Stream I2C Battery Charger BQ24295"                      true )  
option(DIO_STREAMI2C_TOUCHSENSOR_AT42QT1060_FEATURE           "Stream I2C Touch Sensor AT42QT1060"                      true )   
    
option(DIO_STREAMSPI_FEATURE                                  "Stream SPI"                                              true )
option(DIO_STREAMSPI_GPIO_MCP23S17_FEATURE                    "Stream SPI GPIO MCP23S17"                                true )
option(DIO_STREAMSPI_LCDDISPLAY_PCF8833_FEATURE               "Stream SPI LCD Display PCF8833"                          true )  
option(DIO_STREAMSPI_OLEDDISPLAY_SSD1306_FEATURE              "Stream SPI OLED Display SSD1306"                         true )
option(DIO_STREAMSPI_OLEDDISPLAY_SSD1331_FEATURE              "Stream SPI OLED Display SSD1331"                         true )
option(DIO_STREAMSPI_TFTDISPLAY_ILI9341_FEATURE               "Stream SPI TFT Display ILI9341"                          true )
option(DIO_STREAMSPI_TFTDISPLAY_ST7789_FEATURE                "Stream SPI TFT Display ST7789"                           true )
option(DIO_STREAMSPI_TOUCHSCREEN_STMPE610_FEATURE             "Stream SPI Touch Screen STMPE610"                        true )
                                                                                                                        
option(DIO_LEDNEOPIXELWS2812B_FEATURE                         "Data Input/Output Led Neopixel WS2812B"                  true )
                                                                                                                        
option(XEEPROMMEMORYMANAGER_FEATURE                           "EEPROM Memory Manager"                                   true )
                                                                                                                        
option(APP_FEATURE                                            "Application modules"                                     true )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsDevices.cpp")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_WindowsPlatform.cpp")

endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  

  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_LinuxPlatform.cpp")

endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "STM32")

  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_STM32Platform.cpp")

endif()


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

