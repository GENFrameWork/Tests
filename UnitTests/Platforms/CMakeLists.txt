# --------------------------------------------------------------------
# unittests : GEN Unit Tests
# --------------------------------------------------------------------

 cmake_minimum_required(VERSION 3.3.0)
 project(unittests)


 set(GEN_DIRECTORY "../../../../GENFrameWork") 


# --------------------------------------------------------------------
# Compile Selection
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Compile.txt") 


# --------------------------------------------------------------------
# Warnings control
 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Warnings.txt") 


 option(DEBUG_FEATURE                                       "Activate Debug mode"                                        true )
 option(GOOGLETEST_FEATURE                                  "Activate Google Test functionality"                         true )
 option(XMEMORY_CONTROL_FEATURE                             "Activate XMemory Control"                                   true )

 option(XSLEEP_FEATURE                                      "Activate XSleep"                                            true )

#option(LINUX_VISUALSTUDIOCODEPAGE_FEATURE                  "Activate Linux CodePage Editor Visual Studio CP1252"        true )   
 option(LINUX_VISUALSTUDIOUTF8_FEATURE                      "Activate Linux CodePage Editor UTF8"                        true )   
                            
 option(APP_FEATURE                                         "Activate Application modules"                               true )


# --------------------------------------------------------------------
# Source code of the GEN in this Application

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists.txt") 

                     
# --------------------------------------------------------------------
# Directorys of the Application

 set(APP_DIRECTORY_APPLICATION   "../Application")
 list(APPEND INCLUDES_DIR ${APP_DIRECTORY_APPLICATION})


# --------------------------------------------------------------------
# Source code of the Application

 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UnitTests.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UnitTests_XString.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UnitTests_XBuffer.cpp")
 list(APPEND SOURCES "${APP_DIRECTORY_APPLICATION}/UnitTests_XSleep.cpp")


# --------------------------------------------------------------------
# Create proyect 

 include_directories(${INCLUDES_DIR})

 add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})


# --------------------------------------------------------------------
# Add Libraries

 include("${GEN_DIRECTORY}/GEN/CMake/GEN_CMakeLists_Libraries.txt") 

