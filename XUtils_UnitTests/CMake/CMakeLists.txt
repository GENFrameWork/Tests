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

option(USE_CLANG_COMPILER_FEATURE                               "Use Clang Compiler"                                      ON )
                        
option(XSLEEP_FEATURE                                           "XSleep"                                                  ON )
option(XUUID_FEATURE                                            "UUID functions"                                          ON )    

option(DIO_FEATURE                                              "Input/Output"                                            ON )
                                                                            
option(APPFLOW_FEATURE                                          "Application Flow modules"                                ON )
                        
option(GOOGLETEST_FEATURE                                       "Google Test functionality"                               ON )
option(XSERIALIZABLE_BINARY_FEATURE                             "Serializable Binary"                                     ON )
option(XSERIALIZABLE_JSON_FEATURE                               "Serializable JSON"                                       ON )

option(HASH_SHA1_FEATURE                                        "Hash SHA1"                                               ON )
option(HASH_SHA2_FEATURE                                        "Hash SHA2"                                               ON )
option(CIPHER_SYMMETRIC_AES_FEATURE                             "Cipher Symetric AES"                                     ON )
option(XFILE_INI_FEATURE                                        "XFile INI format"                                        ON )

option(XFILE_RIFF_FEATURE                                       "XFile RIFF format"                                       ON )
option(XFILE_DFU_FEATURE                                        "XFile DFU format"                                        ON )

option(DIO_STREAMTLS12_FEATURE                                  "TLS 1.2 (RFC 5246)"                                      OFF)



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
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XRect.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XPair.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XInheritEnum.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XStack.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XRand.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XMemory_Control.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XVector.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XList.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XMap.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XVectorSTL.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTree.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XOrderedList.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XAVLTree.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSystem.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XPath.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XPathsManager.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XDir.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSubject.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XObserver.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XPublisher.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFSMachine.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XFString.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFString.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBufferBits.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBufferBits.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLanguage_ISO_639_3.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XLicense_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLicense_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XDriveImageManager_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XDriveImageManager_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBER_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBER_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XScheduler_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XScheduler_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XThread.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XThreadListNonPreemptive.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XThreadListNonPreemptive.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XScheduler.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XScheduler.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XProcessManager.cpp")
if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/Platforms/Linux/XLINUXProcessManager.cpp")
endif()
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XProcessManager.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializable.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethod.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethodBinary.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethodJSON.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTrace.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTranslation.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTranslation_GEN.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFactory.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XMPInteger.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XMPInteger.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XInterpolator.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XInterpolator.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XASN1.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XASN1.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBER.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBER.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XLicense.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLicense.cpp")

# XLicense.cpp's LoadFromURL() (never exercised by the test above -- it needs a real network stack)
# is the only caller anywhere in this build of DIOWEBCLIENT's constructor and XCHAR*-URL Get()
# overload; DIOWebClient.cpp itself cannot be compiled in without DIO_WEBCLIENT_FEATURE cascading
# into the same missing zlib third-party dependency as XFileZIP/XLog (see the stub file's own
# top comment for the full chain). These two never-invoked symbols are supplied as inert link-time
# stubs so the linker is satisfied -- LoadFromURL is dead code in this test binary.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLicense_LinkStubs.cpp")


# Batch 12: XFILE, XFILEHASH, XFILETXT, XFILEINI, XFILECSV (GEN/XUtils/FormatFiles/).
# XFile.cpp (gated by XFILE_FEATURE) and XFileTXT.cpp (gated by XFILE_TXT_FEATURE) are already
# compiled into this build unconditionally by GEN_Main_Sources.cmake (both flags are turned ON
# transitively by other already-enabled features in this project, confirmed present in
# build.ninja's object list before this change) -- likewise XFileINI.cpp (XFILE_INI_FEATURE,
# already turned ON above for Batch 11's XLicense test). Only the test files themselves are
# needed for those three.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFile.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileTXT.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileINI.cpp")

# XFileHash.cpp is SKIPPED/BLOCKED: confirmed via -fsyntax-only (and then via the full build,
# which fails identically) that XFILEHASH::Create() (XFileHash.cpp lines 222-223 and the mirrored
# line 234) is genuinely uncompilable as shipped, independent of any feature flag --
# `IDini->ConvertToBufferExchange(xbufferexchange);` uses the `->` operator on `IDini`, a plain
# stack XSTRING (not a pointer) declared two lines above, AND calls a method
# (`ConvertToBufferExchange`) that does not exist anywhere on XSTRING at all (confirmed absent
# from XString.h/.cpp via grep; the same nonexistent-method call is mirrored for `IDstring` at
# line 234). This is a genuine, unconditional compile error in XFILEHASH's own source (not gated
# by any XFILE_HASH_FEATURE, since no such flag exists anywhere in Common/CMake/) -- the same
# class of gap as XDICTIONARY/XBINARYMAP (Batch 3/4's Skipped/blocked entries), not a fixable
# build-list oversight like XFString/XBufferBits. Per the hard rule against modifying XUtils, no
# test file was compiled in or written for XFILEHASH -- report only.

# XFileCSV.cpp, by contrast, is never referenced by GEN_Main_Sources.cmake under ANY _FEATURE
# flag at all (confirmed via a full grep of Common/CMake/ -- no XFILE_CSV_FEATURE option or if()
# block exists anywhere) -- the same class of build-list oversight as XFString/XBufferBits/
# XInterpolator in earlier batches, not a real feature gate, and (unlike XFileHash.cpp above) it
# compiles cleanly standalone: XFileCSV.cpp derives from XFILETXT (already compiled) and needs
# nothing else. The file itself is untouched.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/FormatFiles/XFileCSV.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileCSV.cpp")


# Batch 13: XFILECFG, XFILEHEX, XFILEXDB, XFILESENTENCES, XFILEXML (GEN/XUtils/FormatFiles/).
#
# XFileHEX.cpp derives from XFILETXT (already compiled unconditionally) and is never referenced by
# GEN_Main_Sources.cmake under any `_FEATURE` flag at all (confirmed via a full grep of Common/CMake/
# -- no XFILE_HEX_FEATURE option or if() block exists anywhere) -- the same class of build-list
# oversight as XFString/XBufferBits/XFileCSV in earlier batches, not a real feature gate. Compiles
# cleanly standalone, confirmed via the full build below.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/FormatFiles/XFileHEX.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileHEX.cpp")

# XFileCFG.cpp is likewise never referenced by GEN_Main_Sources.cmake under any `_FEATURE` flag
# (same oversight class) and needs only XFILEINI (already compiled in via Batch 11's
# XFILE_INI_FEATURE) plus XSUBJECT/XVARIANT/XVECTOR (all already compiled). Compiles standalone.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/FormatFiles/XFileCFG.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileCFG.cpp")

# XFileXML.cpp is likewise never referenced by GEN_Main_Sources.cmake under any `_FEATURE` flag
# (same oversight class) and needs only XFILETXT (already compiled). Compiles standalone.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/FormatFiles/XFileXML.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileXML.cpp")

# XFILEXDB/XFILESENTENCES SKIPPED/BLOCKED: both derive from XFILEHASH (XFileHash.h/.cpp), which
# Batch 12 already confirmed is genuinely uncompilable as shipped -- XFileHash.cpp:222-223 (and the
# mirrored line 234) call `IDini->ConvertToBufferExchange(xbufferexchange);` where `IDini` is a
# plain stack XSTRING (not a pointer) AND `ConvertToBufferExchange` does not exist anywhere on
# XSTRING at all -- reconfirmed for this batch via a fresh, direct clang++ -fsyntax-only invocation
# against this exact build's real DEFINES/INCLUDES (4 hard compile errors, both call sites). Since
# this breaks XFileHash.cpp as a WHOLE TRANSLATION UNIT (not just the buggy Create() method), none
# of XFILEHASH's other methods (constructor, Open(), Close(), Set(), Get*()) can ever be linked into
# this project either -- concretely reconfirmed (not merely assumed from Batch 12's report) by
# compiling XFileXDB.cpp standalone (which succeeds, since XFileXDB.cpp's own code has no syntax
# errors) and then inspecting its object file with `nm`: it references 6 undefined XFILEHASH
# symbols (constructor, destructor, Set, Open, Close, typeinfo) that can never be satisfied without
# either fixing XFileHash.cpp (forbidden -- GEN is read-only) or reimplementing XFILEHASH's real
# logic ourselves outside GEN (which would test our own stand-in code, not XUtils's actual
# behavior, defeating the purpose). XFILESENTENCES derives from XFILEXDB and is blocked the same
# way, transitively, plus its own ConvertFileFromDBF() additionally calls the broken
# XFILEHASH::Create() directly. No test files were written for either class -- report only, same
# class of gap as XFILEHASH itself (Batch 12) / XDICTIONARY / XBINARYMAP.


# Batch 14: XFILEJSON (+VALUE,+OBJECT,+ARRAY), XFILERIFF (+_LIST), XFILEDFU (+PREFIX,+IMAGE,
# +ELEMENT,+SUFFIX). XFILEDBF and XFILECOBOL were both attempted but are genuinely uncompilable
# as shipped -- see notes below. XFILEZIP remains blocked (missing minizip) -- see note below.
#
# XFileJSON.cpp was already compiled into this build (XFILE_JSON_FEATURE turned ON in Batch 9, for
# XSerializationMethodJSON.cpp's sake) -- only the test .cpp is new here.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileJSON.cpp")

# XFileRIFF.cpp/XFileDFU.cpp are newly pulled in via the XFILE_RIFF_FEATURE/XFILE_DFU_FEATURE
# option() calls added above (both real GEN feature gates, simply unreachable ON by default from
# this project -- see the comment there).
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileRIFF.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFileDFU.cpp")

# XFileDBF.cpp: like XFileCSV/XFileHEX/XFileCFG/XFileXML in earlier batches, never referenced by
# GEN_Main_Sources.cmake under any `_FEATURE` flag (confirmed via a full grep of Common/CMake/) --
# so adding it as a plain source-list entry was attempted the same way. However, unlike those
# earlier classes, XFileDBF.cpp is genuinely UNCOMPILABLE as shipped: its own
# CreateHeaderData()-equivalent code at GEN/XUtils/FormatFiles/XFileDBF.cpp:685 calls
# `strlen(charstr)` where `charstr` is a stack XBUFFER object (not a `const char*`/`char*`), which
# has no implicit conversion to `const char*` -- clang++ rejects it with "no matching function for
# call to 'strlen'". This is a genuine bug in XUtils's own source, reachable from any translation
# unit that compiles this file at all (not merely from a particular test), and GEN/ is read-only
# for this project, so it cannot be fixed here. Per instructions, no source line for XFileDBF.cpp
# is added and no test file was kept for it -- report only, same class of gap as XFILEHASH/XFILEZIP.

# XFileCobol.cpp: attempted the same way, also genuinely UNCOMPILABLE as shipped. XFileCobol.h
# only includes "XBase.h"/"XVector.h"/"XMap.h"/"XTree.h" and never includes XString.h/XPath.h/
# XBuffer.h/XVariant.h, yet its class bodies use XSTRING/XCHAR/XBUFFER/XPATH/XVARIANT_TYPE as
# complete types (e.g. XFileCobol.h:116-134 `XSTRING* GetMask()`/`XSTRING mask;`, :207-221
# `XBUFFER& data`/`XBUFFER data;`, :329-333 `XPATH xpathcpyfiles;` etc.) -- confirmed by compiling
# GEN/XUtils/FormatFiles/XFileCobol.cpp exactly as GEN itself includes it (only "GEN_Defines.h"
# then "XFileCobol.h", no other headers first, matching the real .cpp's own include block), which
# fails with 20 "unknown type name"/"field has incomplete type" errors from clang++. This is a
# genuine defect in XUtils's own header (a missing-include bug, not a build-list oversight our
# test file's include order could work around, since the real XFileCobol.cpp itself has the same
# gap) and GEN/ is read-only, so it cannot be fixed here. No source line for XFileCobol.cpp is
# added and no test file was kept for it -- report only, same class of gap as XFILEDBF above.

# XFILEZIP (+UNZIP,+CMPZIP) SKIPPED/BLOCKED, reconfirmed for this batch: XFileZIP.h does
# "#include <zip.h>"/"#include <unzip.h>" (minizip) which is still not present anywhere on this
# system's include path (no ThirdPartyLibraries/zlib directory at all, same as Batch 7's
# XFILEZIP_XEVENT / Batch 10's XLOG / Batch 11's DIOWEBCLIENT chain) -- a genuinely missing
# third-party dependency, not a fixable build-list oversight. No test file written -- report only.

# --------------------------------------------------------------------
# End Proyect

include("${GEN_DIRECTORY}/Common/CMake/GEN_End.cmake")

