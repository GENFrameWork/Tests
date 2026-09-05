/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XLicense_LinkStubs.cpp
*
* @class      UNITTESTS_XUTILS_XLICENSE_LINKSTUBS
* @brief      Link-time stubs for the DIOWEBCLIENT members XLicense.cpp needs but never calls in tests
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

// XLICENSE::LoadFromURL() (XLicense.cpp, never exercised by this batch's tests -- LoadFromURL
// needs a real network stack and DIOURL, out of scope for a unit test) is the ONLY caller in this
// whole build of DIOWEBCLIENT's constructor and XCHAR*-URL Get() overload. DIOWebClient.cpp itself
// is not compiled into this project: DIO_WEBCLIENT_FEATURE is a real, correctly-wired GEN feature
// switch, but turning it on cascades into COMPRESS_GZ_FEATURE/COMPRESS_DEFLATE_FEATURE ->
// THIRDPARTYLIBRARIES_ZLIB_FEATURE, and no ThirdPartyLibraries/zlib directory exists anywhere on
// this system (the same genuinely-missing-third-party-dependency class of gap as XFileZIP/XLog --
// confirmed via `find`, no build-list oversight to fix). Since XLICENSE's own real methods
// (Generate/GenerateMachineID/GetBufferKeyFromMachineID/CipherExpirationDate/LoadFromFile/
// LoadFromBuffer/CheckMasterCreation/SetEvent -- everything this batch's tests actually exercise)
// need no network code at all, XLicense.cpp is compiled in directly (see CMakeLists.txt) and only
// these two never-invoked DIOWEBCLIENT symbols are supplied here, as inert link-time stubs, purely
// so the linker is satisfied -- LoadFromURL is dead code in this test binary, never called.
//
// GEN update: DIOWEBCLIENT now holds two by-value DIOWEBCLIENT_OPERATIONERROR members
// (lastoperationerror / lastHTTPSattempterror), so constructing a DIOWEBCLIENT also requires
// DIOWEBCLIENT_OPERATIONERROR's default constructor to link. Its other methods are never invoked
// here (our DIOWEBCLIENT constructor stub below does nothing), so only that one constructor is
// stubbed, same as everything else in this file: inert, never exercised by any test.
#include "DIOWebClient.h"
#include "DIOWebHeader.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

DIOWEBHEADER::DIOWEBHEADER()
{

}


DIOWEBHEADER::~DIOWEBHEADER()
{

}


DIOWEBCLIENT_HEADER::DIOWEBCLIENT_HEADER()
{

}


DIOWEBCLIENT_HEADER::~DIOWEBCLIENT_HEADER()
{

}


DIOWEBCLIENT_OPERATIONERROR::DIOWEBCLIENT_OPERATIONERROR()
{

}


DIOWEBCLIENT::DIOWEBCLIENT(XDWORD maxsizebuffer)
{

}


DIOWEBCLIENT::~DIOWEBCLIENT()
{

}


bool DIOWEBCLIENT::Get(XCHAR* url, XBUFFER& tobuffer, XCHAR* addheader, int timeout, XSTRING* localIP)
{
  return false;
}
