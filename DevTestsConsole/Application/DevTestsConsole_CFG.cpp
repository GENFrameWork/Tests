/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTestsConsole_CFG.cpp
*
* @class      DEVTESTSCONSOLE_CFG
* @brief      Developed Tests console CFG class
* @ingroup    TESTS
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XLog.h"

#include "DevTestsConsole.h"

#include "DevTestsConsole_CFG.h"

#include "XMemory_Control.h"

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

DEVTESTSCONSOLE_CFG* DEVTESTSCONSOLE_CFG::instance = NULL;

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool TESTS_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE_CFG::GetIsInstanced()
{
  return instance!=NULL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCONSOLE_CFG& DEVTESTSCONSOLE_CFG::GetInstance()
* @brief      GetInstance
* @ingroup
*
* @return     DEVTESTSCONSOLE_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCONSOLE_CFG& DEVTESTSCONSOLE_CFG::GetInstance()
{
  if(!instance) instance = new DEVTESTSCONSOLE_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE_CFG::DelInstance()
{
  if(instance)
    {
      delete instance;
      instance = NULL;

      return true;
    }

  return false;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DEVTESTSCONSOLE_CFG::Database_GetURL()
* @brief      Database_GetURL
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DEVTESTSCONSOLE_CFG::Database_GetURL()
{
  return &db_URL;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XDWORD DEVTESTSCONSOLE_CFG::Database_GetPort()
* @brief      Database_GetPort
* @ingroup    APPLICATION
*
* @return     XDWORD :
*
*---------------------------------------------------------------------------------------------------------------------*/
XDWORD DEVTESTSCONSOLE_CFG::Database_GetPort()
{
  return db_port;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DEVTESTSCONSOLE_CFG::Database_DatabaseName()
* @brief      Database_DatabaseName
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DEVTESTSCONSOLE_CFG::Database_DatabaseName()
{
  return &db_databasename;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DEVTESTSCONSOLE_CFG::Database_GetUser()
* @brief      Database_GetUser
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DEVTESTSCONSOLE_CFG::Database_GetUser()
{
  return &db_user;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XSTRING* DEVTESTSCONSOLE_CFG::Database_GetPassword()
* @brief      Database_GetPassword
* @ingroup    APPLICATION
*
* @return     XSTRING* :
*
*---------------------------------------------------------------------------------------------------------------------*/
XSTRING* DEVTESTSCONSOLE_CFG::Database_GetPassword()
{
  return &db_password;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         int DEVTESTSCONSOLE_CFG::Database_GetTimeoutConnection()
* @brief      Database_GetTimeoutConnection
* @ingroup    APPLICATION
*
* @return     int :
*
*---------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCONSOLE_CFG::Database_GetTimeoutConnection()
{
  return db_timeoutconnection;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCONSOLE_CFG::Default()
* @brief      Default config
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCONSOLE_CFG::Default()
{
  //------------------------------------------------------------------------------

  checkresourceshardware_memstatuscheckcadence    = 30;
  checkresourceshardware_memstatuslimitpercent    = 5;
  checkresourceshardware_cpuusagecheckcadence     = 20;
  checkresourceshardware_cpuusagelimitpercent     = 70;  
  checkresourceshardware_cpuusageprocessname     = APPLICATION_NAMEAPP; 


  GEN_XTRACE_NET_CFG_DEFAULT_01
  GEN_XTRACE_NET_CFG_DEFAULT_LOCAL

  //------------------------------------------------------------------------------

  log_isactive                                    = true;
  log_backupisactive                              = true;
  log_backupmaxfiles                              = 10;
  log_backupiscompress                            = true;

  log_activesectionsID.Empty();

  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                           += __L(",");
  log_activesectionsID                           += APP_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                                   = XLOGLEVEL_ALL;
  log_maxsize                                     = 3000;
  log_reductionpercent                            = 10;

  //------------------------------------------------------------------------------

  db_URL                                          = __L("");
  db_port                                         = 0;
  db_databasename                                 = __L("");
  db_user                                         = __L("");
  db_password                                     = __L("");
  db_timeoutconnection                            = 30;

  //------------------------------------------------------------------------------

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCONSOLE_CFG::DEVTESTSCONSOLE_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCONSOLE_CFG::DEVTESTSCONSOLE_CFG(XCHAR* namefile) : APPCFG(namefile)
{
  Clean();

  //-----------------------------------------------------
  // DATABASE

  AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, __L("-------------------------------------------------------"), 0, 1);
  AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, __L("Database config")                                        , 0, 2);
  AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, __L("-------------------------------------------------------"), 0, 3);

  AddValue(XFILECFG_VALUETYPE_STRING  , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_URL                , &db_URL);                       AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, DEVTESTSCONSOLE_CFG_DATABASE_URL          ,  __L("URL for database")  ,60, 0);
  AddValue(XFILECFG_VALUETYPE_INT     , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_PORT               , &db_port);                      AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, DEVTESTSCONSOLE_CFG_DATABASE_PORT         ,  __L("Port for database") ,60, 0);
  AddValue(XFILECFG_VALUETYPE_STRING  , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_DATABASENAME       , &db_databasename);              AddRemark(DEVTESTSCONSOLE_CFG_SECTION_DATABASE, DEVTESTSCONSOLE_CFG_DATABASE_DATABASENAME ,  __L("Database Name")     ,60, 0);
  AddValue(XFILECFG_VALUETYPE_STRING  , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_USER               , &db_user);
  AddValue(XFILECFG_VALUETYPE_STRING  , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_PASSWORD           , &db_password);
  AddValue(XFILECFG_VALUETYPE_INT     , DEVTESTSCONSOLE_CFG_SECTION_DATABASE      , DEVTESTSCONSOLE_CFG_DATABASE_TIMEOUTCONNECTION  , &db_timeoutconnection);


  Default();

  Ini();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCONSOLE_CFG::~DEVTESTSCONSOLE_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCONSOLE_CFG::~DEVTESTSCONSOLE_CFG()
{
  Clean();
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCONSOLE_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCONSOLE_CFG::Clean()
{

}

