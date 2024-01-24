# --------------------------------------------------------------------
# unittests : Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.14.0)
 project(unittests)


 set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
option(XTRACE_FEATURE                                      "Activate XTrace"                                            true )
option(XTRACE_NOINTERNET_FEATURE                           "No need for trace dependencies with Internet"               true )
option(GOOGLETEST_FEATURE                                  "Activate Google Test functionality"                         true )
option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )

option(XSLEEP_FEATURE                                      "Activate XSleep"                                            true )

#option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                  "Activate Linux CodePage Editor Visual Studio CP1252"         true )   
option(LINUX_VISUALSTUDIOUTF8_FEATURE                      "Activate Linux CodePage Editor UTF8"                        true )   
                            
option(APP_FEATURE                                         "Activate Application modules"                               true )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Main.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Application")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XBase.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XString.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XBuffer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XSleep.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XVariant.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_XDateTime.cpp")


# --------------------------------------------------------------------
# Create proyect 

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_CreateProject.txt") 


# --------------------------------------------------------------------
# Add Libraries

include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

