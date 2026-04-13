/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUtils_UnitTests.cpp
* 
* @class      XUTILS_UNITTESTS
* @brief      Unit Tests for GEN FrameWork
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

#include "XUtils_UnitTests.h"

#ifdef GOOGLETEST_ACTIVE

  #ifdef XMEMORY_CONTROL_ACTIVE        
    #undef new
  #endif

  #include "gtest/gtest.h"

  #ifdef XMEMORY_CONTROL_ACTIVE        
    #define new new(GEN_MODULE_EXEC, GEN_LINE_EXEC)
  #endif

#endif

#include "VersionFrameWork.h"

#include "XTranslation_GEN.h"
#include "XTranslation.h"




/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(XUTILS_UNITTESTS, unittests)



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUTILS_UNITTESTS::XUTILS_UNITTESTS()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XUTILS_UNITTESTS::XUTILS_UNITTESTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XUTILS_UNITTESTS::~XUTILS_UNITTESTS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
XUTILS_UNITTESTS::~XUTILS_UNITTESTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUTILS_UNITTESTS::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUTILS_UNITTESTS::AppProc_Ini()
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  
  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPLICATION_DIRECTORYMAIN);

  //GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS    , APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  //GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS       , APPFLOW_DEFAULT_DIRECTORY_FONTS);
  //GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS  , APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);
  //GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_WEB         , APPLICATION_DIRECTORYWEB);
  
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
* @fn         bool XUTILS_UNITTESTS::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUTILS_UNITTESTS::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUTILS_UNITTESTS::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUTILS_UNITTESTS::AppProc_Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool XUTILS_UNITTESTS::AppProc_LastUpdate()
* @brief      AppProc_LastUpdate
* @ingroup    DATAIO
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool XUTILS_UNITTESTS::AppProc_LastUpdate()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool XUTILS_UNITTESTS::AppProc_End()
* @brief      AppProc_End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool XUTILS_UNITTESTS::AppProc_End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void XUTILS_UNITTESTS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void XUTILS_UNITTESTS::Clean()
{

}




