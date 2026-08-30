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

# XSERIALIZABLE_BINARY_FEATURE/XSERIALIZABLE_JSON_FEATURE are real, correctly-wired GEN feature
# switches (GEN_Main_Sources.cmake / GEN_Main_Dependencies.cmake both already gate
# XSerializable.cpp/XSerializationMethod.cpp/XSerializationMethodBinary.cpp/
# XSerializationMethodJSON.cpp behind them, and turning them on also defines the
# XSERIALIZABLE_BINARY_ACTIVE/XSERIALIZABLE_JSON_ACTIVE macros those sources need) -- they are
# just never reachable ON by default from this project (XSERIALIZABLE_BINARY_FEATURE has no
# option() anywhere; XSERIALIZABLE_JSON_FEATURE only turns ON transitively through
# DIO_WEBSERVER_RESOLVEENDPOINT_FEATURE, unreachable here). Turning them on here (before
# GEN_Main.cmake runs) lets GEN's own existing, correctly-wired build logic pull all four
# sources in normally -- no GEN file is modified, and XFILE_JSON_FEATURE (needed by
# XSerializationMethodJSON.cpp's XFileJSON.h dependency) is already ON in this project.
option(XSERIALIZABLE_BINARY_FEATURE                             "Serializable Binary"                                     ON )
option(XSERIALIZABLE_JSON_FEATURE                                "Serializable JSON"                                       ON )

# Batch 11: XLicense.cpp (compiled directly below, bypassing XLICENSE_FEATURE itself -- see the
# comment at its list(APPEND...) site for why) calls real HASHSHA1/HASHSHA2/CIPHERAES/XFILEINI
# methods. These four are real, correctly-wired GEN feature switches (GEN_Main_Sources.cmake gates
# HashSHA1.cpp/HashSHA2.cpp/CipherAES.cpp/XFileINI.cpp behind them) that are simply not reachable ON
# by default from this project -- turning them on here (same legitimate pattern as
# XSERIALIZABLE_BINARY_FEATURE/XSERIALIZABLE_JSON_FEATURE above) lets GEN's own build logic compile
# them in normally, with no duplicate-source risk (none of the four is already added anywhere else
# in this file).
option(HASH_SHA1_FEATURE                                        "Hash SHA1"                                               ON )
option(HASH_SHA2_FEATURE                                        "Hash SHA2"                                               ON )
option(CIPHER_SYMMETRIC_AES_FEATURE                             "Cipher Symetric AES"                                     ON )
option(XFILE_INI_FEATURE                                        "XFile INI format"                                        ON )

# Batch 14: XFILE_RIFF_FEATURE/XFILE_DFU_FEATURE are both real, correctly-wired GEN feature
# switches (GEN_Main_Sources.cmake gates XFileRIFF.cpp/XFileDFU.cpp behind them, and
# GEN_Main_Dependencies.cmake's own if(XFILE_RIFF_FEATURE)/if(XFILE_DFU_FEATURE) blocks both just
# add_definitions() the matching _ACTIVE macro and turn on the already-compiled XFILE_FEATURE, no
# other dependency needed). XFILE_RIFF_FEATURE only has an option() declared transitively behind
# GRP_VIDEO_FILE_AVI_FEATURE/SND_FILE_WAV_FEATURE (neither reachable here); XFILE_DFU_FEATURE has
# NO option() anywhere in Common/CMake/ at all (same class of gap as Batch 9's
# XSERIALIZABLE_BINARY_FEATURE). Turning both on here (same legitimate pattern as those Batch 9/11
# examples above) lets GEN's own existing build logic pull XFileRIFF.cpp/XFileDFU.cpp in normally.
option(XFILE_RIFF_FEATURE                                       "XFile RIFF format"                                       ON )
option(XFILE_DFU_FEATURE                                        "XFile DFU format"                                        ON )



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
# XFString.cpp is never referenced by GEN_Main_Sources.cmake for any platform/feature combination
# (XFSTRING has no _FEATURE flag at all, unlike its siblings XFSMachine/XPublisher) -- this looks
# like an oversight in the framework's own build list rather than an intentional exclusion, since
# the class compiles cleanly and has no unmet dependency. Compiling it directly into this test
# binary (the file itself is untouched) is the only way to exercise it.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XFString.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFString.cpp")

# XBufferBits.cpp is never referenced by GEN_Main_Sources.cmake for any platform/feature combination
# (same class of oversight as XFString above: it compiles cleanly with no unmet dependency, it is just
# missing from the framework's own build list). Compiling it directly into this test binary (file
# itself untouched) is the only way to exercise it.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBufferBits.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBufferBits.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLanguage_ISO_639_3.cpp")

# XLICENSE_XEVENT/XDRIVEIMAGEMANAGER_XEVENT/XBER_XEVENT/XSCHEDULER_XEVENT are gated behind
# XLICENSE_FEATURE/XDRIVEIMAGEMANAGER_FEATURE/XASN1_FEATURE/XSCHEDULER_FEATURE, none of which are
# reachable ON from this project's CMakeLists.txt (confirmed absent from CMakeCache.txt and from
# build.ninja's compiled-object list before this change -- same class of gap as XFSTRING/XFString
# above). Unlike XFSTRING though, each of these _XEVENT subclasses only ever stores/returns a raw
# pointer (or, for XBER_XEVENT, owns XSTRING/XBUFFER/XVARIANT members that are already compiled into
# this binary) to its "real" sibling class (XLICENSE/XDRIVEIMAGEMANAGER_DRIVE/XSCHEDULER/etc.) and
# never dereferences it, so the _XEvent.cpp files link cleanly on their own -- confirmed by a
# -fsyntax-only compile of each and then by the full build below -- without needing their much
# heavier sibling implementation files (which would pull in XFactory/XThread singleton usage, and,
# for XFileZip specifically, an unmet <zip.h> system dependency -- see XFileZIP_XEvent note in
# STATUS.md, not attempted here as it is a real missing header, not a fixable oversight).
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XLicense_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XLicense_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XDriveImageManager_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XDriveImageManager_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBER_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBER_XEvent.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XScheduler_XEvent.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XScheduler_XEvent.cpp")

# XThread.cpp/XLINUXThread.cpp are already part of GEN_Main_Sources.cmake unconditionally (no
# feature gate), so XTHREAD/XMUTEX need no extra source -- only the test file itself.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XThread.cpp")

# XThreadListNonPreemptive.cpp is never referenced by GEN_Main_Sources.cmake for any
# platform/feature combination (same class of oversight as XFString/XBufferBits above: it compiles
# cleanly standalone, with no unmet dependency -- confirmed via -fsyntax-only). Compiling it
# directly into this test binary (file itself untouched) is the only way to exercise it.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XThreadListNonPreemptive.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XThreadListNonPreemptive.cpp")

# XScheduler.cpp is gated behind XSCHEDULER_FEATURE, not reachable ON from this project's
# CMakeLists.txt (confirmed absent from CMakeCache.txt and from build.ninja's compiled-object list
# before this change). XScheduler.h includes XThreadCollected.h, but since XTHREADCOLLECTED_ACTIVE
# is not defined anywhere in this build, that header's own else-branch aliases XTHREADCOLLECTED to
# the already-compiled XTHREAD via CREATEXTHREAD/DELETEXTHREAD macros pointing at
# GEN_XFACTORY.CreateThread/DeleteThread -- so XScheduler.cpp needs no extra sibling source beyond
# what XTHREAD/XPublisher(XSUBJECT)/XDateTime/XTimer already provide in this build, confirmed by a
# standalone -fsyntax-only compile and then by the full build below.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XScheduler.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XScheduler.cpp")

# XProcessManager.cpp/XLINUXProcessManager.cpp are gated behind XPROCESSMANAGER_FEATURE, not
# reachable ON from this project's CMakeLists.txt (confirmed absent from CMakeCache.txt and from
# build.ninja's compiled-object list before this change). Both compile cleanly standalone (confirmed
# via -fsyntax-only) against this build's existing XPath/XFile/XConsole.h(header-only, XCONSOLE_FEATURE
# off)/GRPRect.h dependencies, so no XCONSOLE.cpp or other extra sibling source is required.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XProcessManager.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/Platforms/Linux/XLINUXProcessManager.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XProcessManager.cpp")

# XSerializable.cpp/XSerializationMethod.cpp/XSerializationMethodBinary.cpp/
# XSerializationMethodJSON.cpp are pulled into GEN_SOURCES_MODULES_LIST automatically by
# GEN_Main_Sources.cmake now that XSERIALIZABLE_BINARY_FEATURE/XSERIALIZABLE_JSON_FEATURE are
# turned ON above (see the option() calls near the top of this file for why) -- only the test
# files themselves need to be added here.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializable.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethod.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethodBinary.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XSerializationMethodJSON.cpp")

# Batch 10: XTRACE, XTRANSLATION, XTRANSLATION_GEN, XFACTORY.
# XTrace.cpp/XTranslation.cpp/XTranslation_GEN.cpp/XFactory.cpp are all already compiled into this
# build unconditionally (no feature gate -- confirmed present in build.ninja's object list before
# this change), so only the test files themselves need to be added here.
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTrace.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTranslation.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XTranslation_GEN.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XFactory.cpp")

# XLOG (XLog.h/.cpp) is SKIPPED: XLog.cpp unconditionally does "#include "XFileZIP.h"" (XLog.cpp
# line 48, needed for its ZIP-backup feature), which itself does "#include <zip.h>" (minizip) --
# and no zip.h exists anywhere on this system (no ThirdPartyLibraries/zlib directory at all,
# confirmed by `find`), the same genuinely-missing-third-party-dependency class of gap as
# XFILEZIP_XEVENT in Batch 7, not a build-list oversight fixable by adding an option()/source line
# here. No test file was written for XLOG/XLOGBASE/XLOGENTRY -- report only.

# Batch 11: XMPINTEGER, XINTERPOLATOR, XASN1, XBER, XLICENSE.
# XMPInteger.cpp/XInterpolator.cpp are never referenced by GEN_Main_Sources.cmake for any
# platform/feature combination reachable from this project by default (XMPInteger.cpp is only
# pulled in via CIPHER_ASYMMETRIC_RSA_FEATURE/CIPHER_ASYMMETRIC_ED25519_FEATURE, neither of which
# this project turns on; XInterpolator.cpp has no _FEATURE gate at all, the same class of build-list
# oversight as XFString/XBufferBits/XThreadListNonPreemptive in earlier batches). Both compile
# cleanly standalone (confirmed via -fsyntax-only against this build's real DEFINES/INCLUDES): each
# depends only on already-compiled XUtils leaves (XBase/XString/XBuffer for XMPInteger; XBase and
# XSERIALIZABLE, already on via Batch 9, for XInterpolator). Compiled directly into this test binary
# (files themselves untouched).
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XMPInteger.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XMPInteger.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XInterpolator.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XInterpolator.cpp")

# XASN1.cpp/XBER.cpp are gated behind XASN1_FEATURE, not reachable ON from this project by default.
# Rather than turning that flag on (which would make GEN_Main_Sources.cmake add XBER_XEvent.cpp a
# SECOND time -- it is already compiled in via Batch 7's own manual, standalone addition above,
# before XASN1_FEATURE existed as an option here -- causing a duplicate-symbol link error), XASN1.cpp
# and XBER.cpp are instead compiled directly the same standalone way, confirmed via -fsyntax-only:
# neither file's own code is conditioned on XASN1_ACTIVE (that macro is never even referenced by
# either .cpp/.h), so no behavior is lost by bypassing the feature flag -- they need only XSubject/
# XTrace/XObserver/XVector/XBuffer/XString/XVariant/XBER_XEvent.h, all already present in this build.
list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XASN1.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XASN1.cpp")

list(APPEND GEN_SOURCES_MODULES_LIST "${GEN_DIRECTORY}/GEN/XUtils/XBER.cpp")
list(APPEND GEN_SOURCES_MODULES_LIST "${APP_DIRECTORY_APPLICATION}/XUtils_UnitTests_XBER.cpp")

# XLicense.cpp is gated behind XLICENSE_FEATURE, not reachable ON from this project by default.
# Same duplicate-risk reasoning as XASN1_FEATURE above applies here too: turning XLICENSE_FEATURE on
# would make GEN_Main_Sources.cmake add XLicense_XEvent.cpp a SECOND time (already compiled in via
# Batch 7's own manual, standalone addition). XLicense.cpp's own code is also never conditioned on
# XLICENSE_ACTIVE (only the two convenience macros in XLicense.h are -- see the analysis report's
# confirmed macro-arity bug between their #ifdef/#else branches, independently reconfirmed while
# writing this batch's tests -- neither macro is invoked by XLicense.cpp itself nor by its tests), so
# XLicense.cpp is compiled directly the same standalone way, confirmed via -fsyntax-only. Unlike
# XASN1/XBER though, XLicense.cpp needs four real sibling sources this project does not otherwise
# compile in (HASHSHA1::Do/HASHSHA2::Do/CIPHERAES/XFILEINI, all confirmed absent from build.ninja's
# object list beforehand) -- provided by turning on their own legitimate, non-duplicating feature
# flags near the top of this file (HASH_SHA1_FEATURE/HASH_SHA2_FEATURE/CIPHER_SYMMETRIC_AES_FEATURE/
# XFILE_INI_FEATURE) rather than adding those four sources by hand.
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

