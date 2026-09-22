# --------------------------------------------------------------------
# unittests_userinterface : UserInterface Unit Tests (Google Test console mode)
# GEN FrameWork
# --------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.0)
project(unittests_userinterface)


set(GEN_DIRECTORY "../../..")


# --------------------------------------------------------------------
# Activate features/Defines
# Feature set mirrors UI_System (graphics + UI) plus GoogleTest / console,
# so the full UserInterface module links; tests themselves are pure-logic.

option(DEBUG_FEATURE                                            "Debug mode"                                              ON )
option(XTRACE_FEATURE                                           "XTrace"                                                  ON )
option(XTRACE_NOINTERNET_FEATURE                                "No need for trace dependencies with Internet"            ON )
option(XMEMORY_CONTROL_FEATURE                                  "XMemory Control"                                         ON )

option(COVERAGE_CREATEINFO_FEATURE                              "Coverage - Create Info"                                  ON )

option(LINUX_VISUALSTUDIO_UTF8_FEATURE                          "Linux CodePage Editor UTF8"                              ON )

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )

option(LINUX_X11_FEATURE                                        "Linux X11"                                               ON )

option(XSLEEP_FEATURE                                           "XSleep"                                                  ON )
option(XUUID_FEATURE                                            "UUID functions"                                          ON )

option(DIO_FEATURE                                              "Input/Output"                                            ON )
option(DIO_STREAMTLS12_FEATURE                                  "TLS 1.2 (RFC 5246)"                                      OFF)

option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
option(APPFLOW_EXTENDED_FEATURE                                 "Application Flow Extended"                               ON )
option(APPFLOW_LOG_FEATURE                                      "Application Flow Log"                                    ON )
option(APPFLOW_GRAPHICS_FEATURE                                 "Application Flow Graphics"                               ON )
option(APPFLOW_CONSOLE_FEATURE                                  "Application Flow Console"                                ON )
option(APPFLOW_CFG_GENERAL_FEATURE                              "Application Flow CFG General"                            ON )
option(APPFLOW_CFG_LOG_FEATURE                                  "Application Flow CFG LOG"                                ON )

option(GOOGLETEST_FEATURE                                       "Google Test functionality"                               ON )
option(XSERIALIZABLE_BINARY_FEATURE                             "Serializable Binary"                                     ON )
option(XSERIALIZABLE_JSON_FEATURE                               "Serializable JSON"                                       ON )

option(XFILE_INI_FEATURE                                        "XFile INI format"                                        ON )
option(XFILE_CFG_FEATURE                                        "XFile Config format"                                     ON )
option(XFILE_TXT_FEATURE                                        "XFile Text format"                                       ON )

option(GRP_OPENGL_FEATURE                                       "Graphics Open GL"                                        ON )
option(GRP_FEATURE                                              "Graphics"                                                ON )
option(GRP_BITMAP_FILE_BMP_FEATURE                              "Graphics Bitmap File BMP"                                ON )
option(GRP_BITMAP_FILE_JPG_FEATURE                              "Graphics Bitmap File JPG"                                ON )
option(GRP_BITMAP_FILE_PNG_FEATURE                              "Graphics Bitmap File PNG"                                ON )
option(GRP_BITMAP_FILE_TGA_FEATURE                              "Graphics Bitmap File TGA"                                ON )
option(GRP_VECTOR_FILE_SVG_FEATURE                              "Graphics Vector File SVG"                                ON )
option(GRP_STATISTICSCHARS_FEATURE                              "Graphics Statistics Chars"                               ON )
option(GRP_2D_FEATURE                                           "Graphics 2D"                                             ON )

option(INP_FEATURE                                              "Inputs"                                                  ON )

option(USERINTERFACE_FEATURE                                    "User Interace"                                           ON )


# --------------------------------------------------------------------
# Main CMakeList of GEN

include("${GEN_DIRECTORY}/Common/CMake/GEN_Main.cmake")

# clang-cl on Windows needs the MSVC exception model explicitly when CMAKE_CXX_FLAGS
# was not seeded by an MSVC-first configure (matches UI_System /EHsc defaults).
if(WIN32 AND COMPILE_WITH_CLANG_CL)
  if(NOT CMAKE_CXX_FLAGS MATCHES "EHsc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /GR" CACHE STRING "CXX flags" FORCE)
  endif()
endif()


# --------------------------------------------------------------------
# Directorys of the Application

set(APP_DIRECTORY_APPLICATION   "../Sources")
list(APPEND GEN_INCLUDES_DIR_LIST ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_CSS.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Color.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Colors.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_BoundaryLine.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_CSSAdapter.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Element.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Text.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Layout.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_UIScale.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Property_Selectable.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Property_Editable.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/UnitTests_UserInterface_Property_Scrolleable.cpp")


# --------------------------------------------------------------------
# End Proyect

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")
