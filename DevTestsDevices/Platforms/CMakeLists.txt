# --------------------------------------------------------------------
# DevTestsDevices : GEN Developed Test Devices (all micros)
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(devtestsdevices)


 set(GEN_DIRECTORY "../../../../GENFrameWork") 

# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Compile.txt") 


# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


# --------------------------------------------------------------------
# Activate features/Defines

 option(DEBUG_FEATURE                                  "Activate Debug mode"                                        true )
 option(XTRACE_FEATURE                                 "Activate XTrace"                                            true )
 option(XMEMORY_CONTROL_FEATURE                        "Activate XMemory Control"                                   true )

 option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE             "Activate Linux CodePage Editor Visual Studio CP1252"        true )   
                                    
 option(DIO_FEATURE                                    "Activate Data Input/Output"                                 true ) 
 option(DIO_STREAM_FEATURE                             "Activate Data Input/Output Stream"                          true )
 option(DIO_STREAMUART_FEATURE                         "Activate Data Input/Output Stream UART"                     true )
 option(DIO_STREAMUSB_FEATURE                          "Activate Data Input/Output Stream USB"                      true )
 option(DIO_GPIO_FEATURE                               "Activate GPIO"                                              true )
#option(DIO_GPIO_PCPARALLEL_FEATURE                    "Activate Data Input/Output GPIO PC Parallel"                true )

 option(DIO_STREAMI2C_FEATURE                          "Activate Data Input/Output Stream I2C"                      true )
 option(DIO_I2C_6AXISTRACKING_BMI270_FEATURE           "Activate Data I2C 6 axis tracking BMI270"                   true )
 option(DIO_I2C_6AXISTRACKING_LSM303DLHC_FEATURE       "Activate Data I2C 6 axis tracking LSM303DLHC"               true )
 option(DIO_I2C_9AXISTRACKING_MPU9150_FEATURE          "Activate Data I2C 9 axis tracking MPU9150"                  true )
 option(DIO_I2C_ADDACONVERTER_PCF8591_FEATURE          "Activate Data I2C ADDA converter PCF8591"                   true )
 option(DIO_I2C_AIRQUALITY_CCS811_FEATURE              "Activate Data I2C Air quality CCS811"                       true )
 option(DIO_I2C_EEPROM_24XXX_FEATURE                   "Activate Data I2C EEPROM 24XXX"                             true )
 option(DIO_I2C_GPIO_MCP2317_FEATURE                   "Activate Data I2C GPIO MCP2317"                             true )
 option(DIO_I2C_GPIO_PCF8574_FEATURE                   "Activate Data I2C GPIO PCF8574"                             true )
 option(DIO_I2C_LIGHTSENSOR_TSL2561_FEATURE            "Activate Data I2C Light sensor TSL2561"                     true )
 option(DIO_I2C_OLEDDISPLAY_SSD1306_FEATURE            "Activate Data I2C OLED Display SSD1306"                     true )
 option(DIO_I2C_PWMCONTROLER_PCA9685_FEATURE           "Activate Data I2C PWM Controler PCA9685"                    true )
 option(DIO_I2C_TEMHUMSENSOR_AM2315_FEATURE            "Activate Data I2C Temperature Humidity Sensor AM2315"       true )
 option(DIO_I2C_TEMHUMSENSOR_SHT20_FEATURE             "Activate Data I2C Temperature Humidity Sensor SHT20"        true )
 option(DIO_I2C_MONITORGAUGE_LTC2942_FEATURE           "Activate Data I2C Monitor Gauge LTC2942"                    true )
 option(DIO_I2C_BATTERYCHARGER_BQ24295_FEATURE         "Activate Data I2C Battery Charger BQ24295"                  true )  
 option(DIO_I2C_TOUCHSENSOR_AT42QT1060_FEATURE         "Activate Data I2C Touch Sensor AT42QT1060"                  true )   

 option(DIO_STREAMSPI_FEATURE                          "Activate Data Input/Output Stream SPI"                      true )
 option(DIO_SPI_GPIO_MCP23S17_FEATURE                  "Activate Data SPI GPIO MCP23S17"                            true )
 option(DIO_SPI_LCDDISPLAY_PCF8833_FEATURE             "Activate Data SPI LCD Display PCF8833"                      true )  
 option(DIO_SPI_OLEDDISPLAY_SSD1306_FEATURE            "Activate Data SPI OLED Display SSD1306"                     true )
 option(DIO_SPI_OLEDDISPLAY_SSD1331_FEATURE            "Activate Data SPI OLED Display SSD1331"                     true )
 option(DIO_SPI_TFTDISPLAY_ILI9341_FEATURE             "Activate Data SPI TFT Display ILI9341"                      true )
 option(DIO_SPI_TFTDISPLAY_ST7789_FEATURE              "Activate Data SPI TFT Display ST7789"                       true )
 option(DIO_SPI_TOUCHSCREEN_STMPE610_FEATURE           "Activate Data SPI Touch Screen STMPE610"                    true )

 option(DIO_LEDNEOPIXELWS2812B_FEATURE                 "Activate Data Input/Output Led Neopixel WS2812B"            true )

 option(XEEPROMMEMORYMANAGER_FEATURE                   "Activate EEPROM Memory Manager"                             true )

 option(APP_FEATURE                                    "Activate Application modules"                               true )


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsDevices.cpp")

 if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_WindowsPlatform.cpp")
 endif()

 if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")  
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_LinuxPlatform.cpp")
 endif()

 if(${CMAKE_SYSTEM_NAME} MATCHES "STM32")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/DevTestsDevices_STM32Platform.cpp")
 endif()



# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Librarys.txt") 

