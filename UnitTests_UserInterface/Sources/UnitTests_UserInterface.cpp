/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface.cpp
*
* @class      UNITTESTS_USERINTERFACE
* @brief      UserInterface unit tests application
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

#include "UnitTests_UserInterface.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "VersionFrameWork.h"

#include "XTranslation_GEN.h"
#include "XTranslation.h"

#include "XThreadListNonPreemptive.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(UNITTESTS_USERINTERFACE, unittests)


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS_USERINTERFACE::UNITTESTS_USERINTERFACE()
* @brief      Constructor of class.
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UNITTESTS_USERINTERFACE::UNITTESTS_USERINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS_USERINTERFACE::~UNITTESTS_USERINTERFACE()
* @brief      Destructor of class.
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UNITTESTS_USERINTERFACE::~UNITTESTS_USERINTERFACE()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_USERINTERFACE::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_USERINTERFACE::AppProc_Ini()
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPLICATION_DIRECTORYMAIN);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);
  XTRACE_ADDTARGET(XTRACE_TYPE_NET, __L("*:10001"));

  XTRACE_CLEARSCREEN;
  XTRACE_CLEARMSGSSTATUS;

  XSTRING SO_ID;
  GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("S.O. version: %s"), SO_ID.Get());

  { XPATH xpathsection;
    XPATH xpath;
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
    xpath.Create(3 , xpathsection.Get(),  APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

    if(!GEN_XTRANSLATION.Ini(xpath))
      {
        return false;
      }

    GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);
  }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_USERINTERFACE::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_USERINTERFACE::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_USERINTERFACE::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_USERINTERFACE::AppProc_Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_USERINTERFACE::AppProc_LastUpdate()
* @brief      App Proc Last Update.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_USERINTERFACE::AppProc_LastUpdate()
{
  // Same documented fix as UnitTests_Compress / UnitTests_XUtils: APPFLOWBASE::End() only calls
  // AppProc_End() when AppProc_LastUpdate() returns true.
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_USERINTERFACE::AppProc_End()
* @brief      Ends the application process.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_USERINTERFACE::AppProc_End()
{
  XTHREADLISTNONPREEMPTIVE::DelInstance();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UNITTESTS_USERINTERFACE::Clean()
* @brief      Cleans the object internal state.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void UNITTESTS_USERINTERFACE::Clean()
{

}
