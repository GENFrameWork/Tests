/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsCanvas2D_CFG.cpp
* 
* @class      DEVTESTSCANVAS2D_CFG
* @brief      Developed Tests Canvas 2D Config class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "DevTestsCanvas2D_CFG.h"

#include "XLog.h"

#include "DevTestsCanvas2D.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

DEVTESTSCANVAS2D_CFG* DEVTESTSCANVAS2D_CFG::instance = NULL;

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCANVAS2D_CFG::GetIsInstanced()
* @brief      GetIsInstanced
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D_CFG::GetIsInstanced()
{
  return instance!=NULL;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCANVAS2D_CFG& DEVTESTSCANVAS2D_CFG::GetInstance(bool ini)
* @brief      GetInstance
* @ingroup
*
* @return     DEVTESTSCANVAS2D_CFG& :
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCANVAS2D_CFG& DEVTESTSCANVAS2D_CFG::GetInstance(bool ini)
{
  if(!instance) instance = new DEVTESTSCANVAS2D_CFG(APPLICATION_NAMEFILE);

  return (*instance);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTSCANVAS2D_CFG::DelInstance()
* @brief      DelInstance
* @ingroup
*
* @return     bool : true if is succesful.
*
*---------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D_CFG::DelInstance()
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
* @fn         bool DEVTESTSCANVAS2D_CFG::DoVariableMapping()
* @brief      DoVariableMapping
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D_CFG::DoVariableMapping()
{
  if(!APPFLOWCFG::DoVariableMapping())
    {
      return false;
    }

  //-----------------------------------------------------
  // GENERAL
 
  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_POSX                , &screen_posx);
  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_POSY                , &screen_posy);

  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_WIDTH               , &screen_width); 
  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_HEIGHT              , &screen_height);

  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_MAXWIDTH            , &screen_maxwidth); 
  AddValue(XFILECFG_VALUETYPE_INT	  , DEVTESTSCANVAS2DCFG_SECTIONGENERAL        , DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_MAXHEIGHT           , &screen_maxheight);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D_CFG::DoDefault()
* @brief      DoDefault
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D_CFG::DoDefault()
{
  if(!APPFLOWCFG::DoDefault()) 
    {
      return false;
    }

  //------------------------------------------------------------------------------

  GEN_XTRACE_NET_CFG_DEFAULT_01

  screen_posx       = 400;    
  screen_posy       = 100;    

  screen_width      = 800;    
  screen_height     = 600;      

  screen_maxwidth   = 1024;    
  screen_maxheight  = 800;    

  //------------------------------------------------------------------------------

  log_isactive                          = true;
  log_backupisactive                    = true;
  log_backupmaxfiles                    = 10;
  log_backupiscompress                  = true;

  log_activesectionsID.Empty();

  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_INITIATION;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_GENERIC;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_STATUSAPP;
  log_activesectionsID                  += __L(",");
  log_activesectionsID                  += APPFLOW_CFG_LOG_SECTIONID_ENDING;

  log_levelmask                         = XLOGLEVEL_ALL;
  log_maxsize                           = 3000;
  log_reductionpercent                  = 10;

  //------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetPosX()
* @brief      Screen_GetPosX
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetPosX()
{
  return screen_posx;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetPosY()
* @brief      Screen_GetPosY
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetPosY()
{
  return screen_posy;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D_CFG::Screen_SetPosX(int posx)
* @brief      Screen_SetPosX
* @ingroup    APPLICATION
* 
* @param[in]  posx : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D_CFG::Screen_SetPosX(int posx)
{
  this->screen_posx = posx;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D_CFG::Screen_SetPosY(int posy)
* @brief      Screen_SetPosY
* @ingroup    APPLICATION
* 
* @param[in]  posy : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D_CFG::Screen_SetPosY(int posy)
{
  this->screen_posy = posy;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetSizeWidth()
* @brief      Screen_GetSizeWidth
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetWidth()
{
  return screen_width;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetSizeHeight()
* @brief      Screen_GetSizeHeight
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetHeight()
{
  return screen_height;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetMaxWidth()
* @brief      Screen_GetMaxWidth
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetMaxWidth()
{
  return screen_maxwidth;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         int DEVTESTSCANVAS2D_CFG::Screen_GetMaxHeight()
* @brief      Screen_GetMaxHeight
* @ingroup    APPLICATION
* 
* @return     int : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
int DEVTESTSCANVAS2D_CFG::Screen_GetMaxHeight()
{
  return screen_maxheight;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCANVAS2D_CFG::DEVTESTSCANVAS2D_CFG(XCHAR* namefile) : APPLICATIONCFG(namefile)
* @brief      Constructor
* @ingroup
*
* @param[in]  XCHAR* : name of file of config
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCANVAS2D_CFG::DEVTESTSCANVAS2D_CFG(XCHAR* namefile) : APPFLOWCFG(namefile)
{
  Clean();

  if(namefile)
    {
      Ini<DEVTESTSCANVAS2D_CFG>();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTSCANVAS2D_CFG::~DEVTESTSCANVAS2D_CFG()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup
*
* @return     Does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCANVAS2D_CFG::~DEVTESTSCANVAS2D_CFG()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTSCANVAS2D_CFG::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup
*
* @return     void : does not return anything.
*
*---------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D_CFG::Clean()
{
  screen_posx         = 0;    
  screen_posy         = 0;    

  screen_width        = 0;    
  screen_height       = 0;    

  screen_maxwidth     = 0;    
  screen_maxheight    = 0;    
}


#pragma endregion

