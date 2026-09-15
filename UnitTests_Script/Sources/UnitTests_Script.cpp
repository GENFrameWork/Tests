/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Script.cpp
* @class      UNITTESTS_SCRIPT
* @brief      Script unit tests application
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/

/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_Script.h"

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

APPLICATIONCREATEINSTANCE(UNITTESTS_SCRIPT, unittests)


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

UNITTESTS_SCRIPT::UNITTESTS_SCRIPT()
{
  Clean();
}


UNITTESTS_SCRIPT::~UNITTESTS_SCRIPT()
{
  Clean();
}


bool UNITTESTS_SCRIPT::AppProc_Ini()
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPLICATION_DIRECTORYMAIN);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, APPFLOW_DEFAULT_DIRECTORY_SCRIPTS);
  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  return true;
}


bool UNITTESTS_SCRIPT::AppProc_FirstUpdate()
{
  return true;
}


bool UNITTESTS_SCRIPT::AppProc_Update()
{
  return false;
}


bool UNITTESTS_SCRIPT::AppProc_LastUpdate()
{
  return true;
}


bool UNITTESTS_SCRIPT::AppProc_End()
{
  XTHREADLISTNONPREEMPTIVE::DelInstance();

  return true;
}


void UNITTESTS_SCRIPT::Clean()
{

}
