# --------------------------------------------------------------------
# unittests : Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.14.0)
project(unittests)


set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                          "Activate Debug mode"                                     ON )
option(XTRACE_FEATURE                                         "Activate XTrace"                                         ON )
option(XTRACE_NOINTERNET_FEATURE                              "No need for trace dependencies with Internet"            ON )
    
option(XMEMORY_CONTROL_FEATURE                                "Activate XMemory Control"                                ON )
    
option(XSLEEP_FEATURE                                         "Activate XSleep"                                         ON )
    
#option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                     "Activate Linux CodePage Editor Visual Studio CP1252"     ON )   
option(LINUX_VISUALSTUDIOUTF8_FEATURE                         "Activate Linux CodePage Editor UTF8"                     ON )   
                                
option(APP_FEATURE                                            "Activate Application modules"                            ON )
    
option(GOOGLETEST_FEATURE                                     "Activate Google Test functionality"                      ON )
#option(GOOGLETEST_EXECFORDISCOVER_FEATURE                     "Activate Google Test Execution for discovery"            ON )



# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XBase.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XBuffer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XDateTime.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XSleep.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XString.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XTimer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XVariant.cpp")



# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/Common/CMake/GEN_CMakeLists_Libraries.txt") 

