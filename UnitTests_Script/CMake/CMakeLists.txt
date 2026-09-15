# --------------------------------------------------------------------
# unittests_script : Script Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(unittests_script)


set(GEN_DIRECTORY "../../..")


# --------------------------------------------------------------------
# Activate features/Defines

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )
option(COVERAGE_CREATEINFO_FEATURE                              "Coverage - Create Info"                                  ON )
option(LINUX_VISUALSTUDIO_UTF8_FEATURE                          "Linux CodePage Editor UTF8"                              ON )
option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )  
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )

option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_STREAMTLS_FEATURE                                    "Stream TLS"                                              ON )    

option(XSLEEP_FEATURE                                           "XSleep"                                                  ON )
option(XFILE_INI_FEATURE                                        "XFile INI format"                                        ON )
option(XFILE_CFG_FEATURE                                        "XFile Config format"                                     ON )

option(SCRIPT_FEATURE                                           "Script modules"                                          ON )
option(SCRIPT_CACHE_FEATURE                                     "Script cache"                                            ON )
option(SCRIPT_G_FEATURE                                         "G script interpreter"                                    ON )
option(SCRIPT_LUA_FEATURE                                       "Lua script interpreter"                                  ON )
option(SCRIPT_JAVASCRIPT_FEATURE                                "JavaScript interpreter"                                  ON )

option(SCRIPT_LIB_SYSTEM_FEATURE                                "Script System library"                                   ON )
option(SCRIPT_LIB_PROCESS_FEATURE                               "Script Process library"                                  ON )
option(SCRIPT_LIB_LOG_FEATURE                                   "Script Log library"                                      ON )
option(SCRIPT_LIB_CONSOLE_FEATURE                               "Script Console library"                                  ON )
option(SCRIPT_LIB_WINDOW_FEATURE                                "Script Window library"                                   ON )
option(SCRIPT_LIB_CFG_FEATURE                                   "Script CFG library"                                      ON )
option(SCRIPT_LIB_INPUTSIMULATE_FEATURE                         "Script Input Simulate library"                           ON )
option(SCRIPT_LIB_DEVTEST_FEATURE                               "Script development test library"                         ON )

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

set(UNITTESTS_SCRIPT_MODULES
  Script
  ScriptCache
  ScriptErrorCode
  ScriptLanguageG
  ScriptLanguageLua
  ScriptLanguageJavascript
  ScriptLib
  ScriptLibFunction
  ScriptXEvent
  ScriptLibCFG
  ScriptLibConsole
  ScriptLibDevTest
  ScriptLibDir
  ScriptLibInputSimulate
  ScriptLibLog
  ScriptLibMath
  ScriptLibPath
  ScriptLibProcess
  ScriptLibRand
  ScriptLibString
  ScriptLibSystem
  ScriptLibTimer
  ScriptLibTrace
  ScriptLibWindow
)

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Script.cpp")

foreach(UNITTESTS_SCRIPT_MODULE ${UNITTESTS_SCRIPT_MODULES})
  list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_Script_${UNITTESTS_SCRIPT_MODULE}.cpp")
endforeach()


# --------------------------------------------------------------------
# End Proyect

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")
