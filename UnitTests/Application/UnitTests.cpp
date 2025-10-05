/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests.cpp
* 
* @class      UNITTESTS
* @brief      Unit Tests for GEN FrameWork
* @ingroup    TESTS
* 
* @copyright  GEN Group. All rights reserved.
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "UnitTests.h"

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


#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

APPLICATIONCREATEINSTANCE(UNITTESTS, unittests)

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS::UNITTESTS()
* @brief      Constructor
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
UNITTESTS::UNITTESTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS::~UNITTESTS()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    DATAIO
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
UNITTESTS::~UNITTESTS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS::AppProc_Ini()
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);  
  XTRACE_ADDTARGET(XTRACE_TYPE_NET, __L("*:10001"));  

  XTRACE_CLEARSCREEN;
  XTRACE_CLEARMSGSSTATUS;

  XSTRING SO_ID;
  GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("S.O. version: %s"), SO_ID.Get()); 

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UNITTESTS::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS::AppProc_Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool UNITTESTS::AppProc_LastUpdate()
* @brief      AppProc_LastUpdate
* @ingroup    DATAIO
* 
* 
* @return     bool : true if is succesful. 
* 
* ---------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS::AppProc_LastUpdate()
{
  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS::AppProc_End()
* @brief      AppProc_End
* @ingroup    DATAIO
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS::AppProc_End()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UNITTESTS::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    TEST
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void UNITTESTS::Clean()
{

}


#pragma endregion


