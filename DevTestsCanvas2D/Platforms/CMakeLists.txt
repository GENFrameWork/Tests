# --------------------------------------------------------------------
# DevTestCanvas2D : Develped Tests (Canvas 2D mode)
# GEN FrameWork 
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(devtestscanvas2D)


set(GEN_DIRECTORY "../../..") 


# --------------------------------------------------------------------
# features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(LINUX_X11_FEATURE                                        "Linux X11"                                               ON )
       
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
option(APPFLOW_GRAPHICS_FEATURE                                 "Application Flow Graphics"                               ON )
                                                                             
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )
option(APPFLOW_CFG_SCRIPTS_FEATURE                              "Application Flow Scripts List"                           ON )  

option(GRP_FEATURE                                              "Graphics"                                                ON )
option(GRP_BITMAP_FILE_BMP_FEATURE                              "Graphics Bitmap File BMP"                                ON )
option(GRP_BITMAP_FILE_JPG_FEATURE                              "Graphics Bitmap File JPG"                                ON )
option(GRP_BITMAP_FILE_PNG_FEATURE                              "Graphics Bitmap File PNG"                                ON )
option(GRP_BITMAP_FILE_TGA_FEATURE                              "Graphics Bitmap File TGA"                                ON )
option(GRP_VECTOR_FILE_DXF_FEATURE                              "Graphics Vector File DXF"                                ON )   
option(GRP_VECTOR_FILE_SVG_FEATURE                              "Graphics Vector File SVG"                                ON ) 
option(GRP_2D_FEATURE                                           "Graphics 2D"                                             ON )

option(INP_FEATURE                                              "Inputs"                                                  ON )

option(DIO_CAMERA_FEATURE                                       "Camera API"                                              ON )
option(DIO_LOCATION_FEATURE                                     "Location API"                                            ON ) 

option(SCRIPT_FEATURE                                           "Scripts"                                                 ON )
option(SCRIPT_G_FEATURE                                         "Script G Language"                                       ON )
option(SCRIPT_LUA_FEATURE                                       "Script LUA Language"                                     ON )
option(SCRIPT_JAVASCRIPT_FEATURE                                "Script Javascript Language"                              ON )
option(SCRIPT_LIB_SYSTEM_FEATURE                                "Script Lib System"                                       ON )    
option(SCRIPT_LIB_PROCESS_FEATURE                               "Script Lib Process"                                      ON )    
option(SCRIPT_LIB_LOG_FEATURE                                   "Script Lib Log"                                          ON )    
option(SCRIPT_LIB_CONSOLE_FEATURE                               "Script Lib Console"                                      ON ) 
option(SCRIPT_LIB_WINDOW_FEATURE                                "Script Lib Window"                                       ON ) 
option(SCRIPT_LIB_INPUTSIMULATE_FEATURE                         "Script Lib Input Simulated"                              ON )    



# --------------------------------------------------------------------
# Config Application Macro

set(APP_CFG_DEVTESTSCANVAS2D "-DAPPFLOW_CFG=DEVTESTSCANVAS2D_CFG::GetInstance()")
add_definitions(${APP_CFG_DEVTESTSCANVAS2D})


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Main.txt") 
                   
                   
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

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_CreateProject.txt")


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/cmake/GEN_CMakeLists_Libraries.txt") 

