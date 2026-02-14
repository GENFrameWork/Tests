# --------------------------------------------------------------------
# DevTestsDevices : Developed Test Devices (include micros)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(devtestsdevices)


set(GEN_DIRECTORY "../../..") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                          "Debug mode"                                              ON )
option(XTRACE_FEATURE                                         "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                "XMemory Control"                                         ON )
                                                                                                                        
option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                     "Linux CodePage Editor Visual Studio CP1252"              ON )   
                                        
option(DIO_FEATURE                                            "Data Input/Output"                                       ON ) 
option(DIO_STREAM_FEATURE                                     "Data Input/Output Stream"                                ON )
option(DIO_STREAMUART_FEATURE                                 "Data Input/Output Stream UART"                           ON )
option(DIO_STREAMUSB_FEATURE                                  "Data Input/Output Stream USB"                            ON )
option(DIO_GPIO_FEATURE                                       "GPIO"                                                    ON )
#option(DIO_GPIO_PCPARALLEL_FEATURE                            "Data Input/Output GPIO PC Parallel"                      ON )
    
option(DIO_STREAMI2C_FEATURE                                  "Stream I2C"                                              ON )
option(DIO_STREAMI2C_6AXISTRACKING_LSM303DLHC_FEATURE         "Stream I2C 6 axis tracking LSM303DLHC"                   ON )
option(DIO_STREAMI2C_6AXISTRACKING_BMI270_FEATURE             "Stream I2C 6 axis tracking BMI270"                       ON )
option(DIO_STREAMI2C_9AXISTRACKING_MPU9150_FEATURE            "Stream I2C 9 axis tracking MPU9150"                      ON )
option(DIO_STREAMI2C_ADDACONVERTER_PCF8591_FEATURE            "Stream I2C ADDA converter PCF8591"                       ON )
option(DIO_STREAMI2C_AIRQUALITY_CCS811_FEATURE                "Stream I2C Air quality CCS811"                           ON )
option(DIO_STREAMI2C_EEPROM_24XXX_FEATURE                     "Stream I2C EEPROM 24XXX"                                 ON )
option(DIO_STREAMI2C_GPIO_MCP2317_FEATURE                     "Stream I2C GPIO MCP2317"                                 ON )
option(DIO_STREAMI2C_GPIO_PCF8574_FEATURE                     "Stream I2C GPIO PCF8574"                                 ON )
option(DIO_STREAMI2C_LIGHTSENSOR_TSL2561_FEATURE              "Stream I2C Light sensor TSL2561"                         ON )
option(DIO_STREAMI2C_OLEDDISPLAY_SSD1306_FEATURE              "Stream I2C OLED Display SSD1306"                         ON )
option(DIO_STREAMI2C_PWMCONTROLER_PCA9685_FEATURE             "Stream I2C PWM Controler PCA9685"                        ON )
option(DIO_STREAMI2C_TEMHUMSENSOR_AM2315_FEATURE              "Stream I2C Temperature Humidity Sensor AM2315"           ON )
option(DIO_STREAMI2C_TEMHUMSENSOR_SHT20_FEATURE               "Stream I2C Temperature Humidity Sensor SHT20"            ON )
option(DIO_STREAMI2C_MONITORGAUGE_LTC2942_FEATURE             "Stream I2C Monitor Gauge LTC2942"                        ON )
option(DIO_STREAMI2C_BATTERYCHARGER_BQ24295_FEATURE           "Stream I2C Battery Charger BQ24295"                      ON )  
option(DIO_STREAMI2C_TOUCHSENSOR_AT42QT1060_FEATURE           "Stream I2C Touch Sensor AT42QT1060"                      ON )   
    
option(DIO_STREAMSPI_FEATURE                                  "Stream SPI"                                              ON )
option(DIO_STREAMSPI_GPIO_MCP23S17_FEATURE                    "Stream SPI GPIO MCP23S17"                                ON )
option(DIO_STREAMSPI_LCDDISPLAY_PCF8833_FEATURE               "Stream SPI LCD Display PCF8833"                          ON )  
option(DIO_STREAMSPI_OLEDDISPLAY_SSD1306_FEATURE              "Stream SPI OLED Display SSD1306"                         ON )
option(DIO_STREAMSPI_OLEDDISPLAY_SSD1331_FEATURE              "Stream SPI OLED Display SSD1331"                         ON )
option(DIO_STREAMSPI_TFTDISPLAY_ILI9341_FEATURE               "Stream SPI TFT Display ILI9341"                          ON )
option(DIO_STREAMSPI_TFTDISPLAY_ST7789_FEATURE                "Stream SPI TFT Display ST7789"                           ON )
option(DIO_STREAMSPI_TOUCHSCREEN_STMPE610_FEATURE             "Stream SPI Touch Screen STMPE610"                        ON )
                                                                                                                        
option(DIO_LEDNEOPIXELWS2812B_FEATURE                         "Data Input/Output Led Neopixel WS2812B"                  ON )
                                                                                                                        
option(XEEPROMMEMORYMANAGER_FEATURE                           "EEPROM Memory Manager"                                   ON )
                                                                                                                        
option(APPFLOW_FEATURE                                        "Application Flow modules"                                ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Main.txt") 

                     
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

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Libraries.txt") 

