# --------------------------------------------------------------------
# xutils_unittests : XUtils Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(xutils_unittests)


set(GEN_DIRECTORY "../../..") 


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )                        
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(COVERAGE_CREATEINFO_FEATURE                              "Coverage - Create Info"                                  ON ) 

option(LINUX_VISUALSTUDIO_UTF8_FEATURE                          "Linux CodePage Editor UTF8"                              ON )   

#option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )
                        
option(XSLEEP_FEATURE                                           "XSleep"                                                  ON )
option(XUUID_FEATURE                                            "UUID functions"                                          ON )    

option(DIO_FEATURE                                              "Input/Output"                                            ON )
                                                                            
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
                        
option(GOOGLETEST_FEATURE                                       "Google Test functionality"                               ON )



# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBase.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBuffer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XDateTime.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSleep.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XString.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTimer.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XVariant.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XUUID.cpp")


# --------------------------------------------------------------------
# End Proyect 

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

