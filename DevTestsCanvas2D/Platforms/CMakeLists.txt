# --------------------------------------------------------------------
# DevTestCanvas2D : Develped Tests (Canvas 2D mode)
# GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(devtestscanvas2D)


set(GEN_DIRECTORY "../../../") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                          "Debug mode"                                              true )
option(XTRACE_FEATURE                                         "XTrace"                                                  true )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            true )
option(XMEMORY_CONTROL_FEATURE                                "XMemory Control"                                         true )

option(LINUX_X11_FEATURE                                      "Linux X11"                                               true )
       
option(APP_FEATURE                                            "Application modules"                                     true )
option(APP_LOG_FEATURE                                        "Application Log"                                         true )
option(APP_GRAPHICS_FEATURE                                   "Application Graphics"                                    true )

option(APP_CFG_GENERAL_FEATURE                                "Application CFG General"                                 true )  
option(APP_CFG_LOG_FEATURE                                    "Application CFG LOG"                                     true )
option(APP_CFG_SCRIPTS_FEATURE                                "Application Scripts List"                                true )  

option(GRP_FEATURE                                            "Graphics"                                                true )
option(GRP_BITMAP_FILE_BMP_FEATURE                            "Graphics Bitmap File BMP"                                true )
option(GRP_BITMAP_FILE_JPG_FEATURE                            "Graphics Bitmap File JPG"                                true )
option(GRP_BITMAP_FILE_PNG_FEATURE                            "Graphics Bitmap File PNG"                                true )
option(GRP_BITMAP_FILE_TGA_FEATURE                            "Graphics Bitmap File TGA"                                true )
option(GRP_2D_FEATURE                                         "Graphics 2D"                                             true )

option(INP_FEATURE                                            "Inputs"                                                  true )

option(DIO_CAMERA_FEATURE                                     "Camera API"                                              true )
option(DIO_LOCATION_FEATURE                                   "Location API"                                            true ) 

option(SCRIPT_FEATURE                                         "Scripts"                                                 true )
option(SCRIPT_G_FEATURE                                       "Script G Language"                                       true )
option(SCRIPT_LUA_FEATURE                                     "Script LUA Language"                                     true )
option(SCRIPT_JAVASCRIPT_FEATURE                              "Script Javascript Language"                              true )
option(SCRIPT_LIB_SYSTEM_FEATURE                              "Script Lib System"                                       true )    
option(SCRIPT_LIB_PROCESS_FEATURE                             "Script Lib Process"                                      true )    
option(SCRIPT_LIB_LOG_FEATURE                                 "Script Lib Log"                                          true )    
option(SCRIPT_LIB_CONSOLE_FEATURE                             "Script Lib Console"                                      true ) 
option(SCRIPT_LIB_WINDOW_FEATURE                              "Script Lib Window"                                       true ) 
option(SCRIPT_LIB_INPUTSIMULATE_FEATURE                       "Script Lib Input Simulated"                              true )    



# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_DEVTESTSCANVAS2D "-DAPP_CFG=DEVTESTSCANVAS2D_CFG::GetInstance()")
add_definitions(${APP_CFG_DEVTESTSCANVAS2D})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 
                   
                   
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsCanvas2D.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/DevTestsCanvas2D_CFG.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

