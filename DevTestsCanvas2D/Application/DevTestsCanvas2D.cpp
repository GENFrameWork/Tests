/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsCanvas2D.cpp
* 
* @class      DEVTESTSCANVAS2D
* @brief      Developed Tests Canvas 2D class
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

#include "DevTestsCanvas2D.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "VersionFrameWork.h"

#include "XPath.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XFactory.h"
#include "XRand.h"
#include "XDir.h"
#include "XString.h"
#include "XSystem.h"
#include "XLog.h"
#include "XConsole.h"
#include "XFileTXT.h"
#include "XFileCSV.h"
#include "XFileXML.h"
#include "XTranslation.h"
#include "XTranslation_GEN.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XConsole.h"
#include "XThread.h"
#include "XTrace.h"

#include "HashMD5.h"

#include "DIOFactory.h"
#include "DIOStreamDeviceIP.h"
#include "DIOStreamIPLocalEnumDevices.h"
#include "DIOStreamTCPIPConfig.h"
#include "DIOStreamTCPIP.h"

#include "DIOWebClient_XEvent.h"
#include "DIOWebClient.h"

#include "DIOCheckTCPIPConnections.h"
#include "DIOCheckInternetConnection.h"

#include "DIOScraperWeb.h"
#include "DIOScraperWebPublicIP.h"
#include "DIOScraperWebGeolocationIP.h"
#include "DIOScraperWebUserAgentID.h"

#include "GRPVectorFile_XEvent.h"
#include "GRPVectorFile.h"

#include "GRPCanvas.h"
#include "GRPScreen.h"
#include "GRPViewPort.h"
#include "GRPBitmapFile.h"
#include "GRPXEvent.h"

#include "INPManager.h"

#include "APPFlowLog.h"
#include "APPFlowExtended.h"

#ifdef SCRIPT_LIB_WINDOW_ACTIVE  
#include "Script_Lib_Window.h"
#endif
#include "Script_Language_G.h"
#include "Script_Language_Lua.h"
#include "Script_Language_Javascript.h"


#include "DevTestsCanvas2D_CFG.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(DEVTESTSCANVAS2D, devtestscanvas2d)

GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);



/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DEVTESTSCANVAS2D::DEVTESTSCANVAS2D() : XFSMACHINE(0)
* @brief      Constructor
* @ingroup    GRAPHIC
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCANVAS2D::DEVTESTSCANVAS2D() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         DEVTESTSCANVAS2D::~DEVTESTSCANVAS2D()
* @brief      Destructor
* @note       VIRTUAL
* @ingroup    GRAPHIC
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTSCANVAS2D::~DEVTESTSCANVAS2D()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::InitFSMachine()
* @brief      InitFSMachine
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::InitFSMachine()
{
  if(!AddState( DEVTESTSCANVAS2D_XFSMSTATE_NONE            ,
                DEVTESTSCANVAS2D_XFSMEVENT_INI             , DEVTESTSCANVAS2D_XFSMSTATE_INI           ,
                DEVTESTSCANVAS2D_XFSMEVENT_END             , DEVTESTSCANVAS2D_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCANVAS2D_XFSMSTATE_INI             ,
                DEVTESTSCANVAS2D_XFSMEVENT_UPDATE          , DEVTESTSCANVAS2D_XFSMSTATE_UPDATE        ,                
                DEVTESTSCANVAS2D_XFSMEVENT_END             , DEVTESTSCANVAS2D_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCANVAS2D_XFSMSTATE_UPDATE          ,               
                DEVTESTSCANVAS2D_XFSMEVENT_END             , DEVTESTSCANVAS2D_XFSMSTATE_END           ,                 
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTSCANVAS2D_XFSMSTATE_END             ,
                DEVTESTSCANVAS2D_XFSMEVENT_NONE            , DEVTESTSCANVAS2D_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::AppProc_Ini()
* @brief      AppProc_Ini
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::AppProc_Ini()
{
  XSTRING   string;
  XSTRING   stringresult;

  //-------------------------------------------------------------------------------------------------

  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  Application_GetName()->Set(APPLICATION_NAMEAPP);

  SetInitOptions( APPFLOWGRAPHICS_INIOPTION_CREATEMAINSCREEN    |
                  APPFLOWGRAPHICS_INIOPTION_SHOWMAINSCREEN      |
                  APPFLOWGRAPHICS_INIOPTION_INPUT);

  //--------------------------------------------------------------------------------------------------

  XTRACE_SETAPPLICATIONNAME((*Application_GetName()));
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);
  XTRACE_SETAPPLICATIONID(string);

  //--------------------------------------------------------------------------------------------------

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPFLOW_DEFAULT_DIRECTORY_ROOT);

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS      , APPFLOW_DEFAULT_DIRECTORY_GRAPHICS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_FONTS         , APPFLOW_DEFAULT_DIRECTORY_FONTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_UI_LAYOUTS    , APPFLOW_DEFAULT_DIRECTORY_UI_LAYOUTS);
  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS       , APPFLOW_DEFAULT_DIRECTORY_SCRIPTS);


  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  //--------------------------------------------------------------------------------------------------

  InitFSMachine();

  //--------------------------------------------------------------------------------------

  xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  //--------------------------------------------------------------------------------------

  /*
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
  xpath.Create(3 , xpathsection.Get(), SCRIPTS_LNG_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

  if(!GEN_XTRANSLATION.Ini(xpath))
    {
      return false;
    }
  */

  GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_SPA);

  //--------------------------------------------------------------------------------------

  APPFLOW_CFG_SETAUTOMATICTRACETARGETS

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPStart(&APPFLOW_CFG);

  //--------------------------------------------------------------------------------------

  SetEvent(DEVTESTSCANVAS2D_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::AppProc_FirstUpdate()
* @brief      AppProc_FirstUpdate
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[DEVTESTSCANVAS2D_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[DEVTESTSCANVAS2D_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[DEVTESTSCANVAS2D_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[DEVTESTSCANVAS2D_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[DEVTESTSCANVAS2D_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[DEVTESTSCANVAS2D_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[DEVTESTSCANVAS2D_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[DEVTESTSCANVAS2D_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[DEVTESTSCANVAS2D_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }  

  //--------------------------------------------------------------------------------

  GRPVIEWPORT* viewport = NULL;
  GRPCANVAS*   canvas   = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();

  if(canvas)
    {
      canvas->Clear(&colorblack);  

      // if(backgroundbmp) canvas->PutBitmapNoAlpha(0, 0, backgroundbmp);

      canvas->RasterFont_Select(__L("verdana18"));
    }

  //--------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::AppProc_Update()
* @brief      AppProc_Update
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::AppProc_Update()
{
  if(GetEvent()==DEVTESTSCANVAS2D_XFSMEVENT_NONE) // Not new event
    {
      switch(GetCurrentState())
        {
          case DEVTESTSCANVAS2D_XFSMSTATE_NONE        : break;

          case DEVTESTSCANVAS2D_XFSMSTATE_INI         : break;

          case DEVTESTSCANVAS2D_XFSMSTATE_UPDATE      : { UpdateInput();

                                                          DrawFrame();

                                                          GetMainScreen()->UpdateViewports();
                                                        }
                                                        break;

          case DEVTESTSCANVAS2D_XFSMSTATE_END         : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<DEVTESTSCANVAS2D_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DEVTESTSCANVAS2D_XFSMSTATE_NONE    : break;

              case DEVTESTSCANVAS2D_XFSMSTATE_INI     : SetEvent(DEVTESTSCANVAS2D_XFSMEVENT_UPDATE);                                                       
                                                        break;

              case DEVTESTSCANVAS2D_XFSMSTATE_UPDATE  : break;

              case DEVTESTSCANVAS2D_XFSMSTATE_END     : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::AppProc_End()
* @brief      AppProc_End
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(DEVTESTSCANVAS2D_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------

  if(backgroundbmp)
    {
      delete backgroundbmp;
      backgroundbmp = NULL;
    }

  //--------------------------------------------------------------------------------------

  if(xtimer)
    {
      GEN_XFACTORY.DeleteTimer(xtimer);
      xtimer = NULL;
    }

  //--------------------------------------------------------------------------------------

  APPFLOW_EXTENDED.APPEnd();
  APPFLOW_EXTENDED.DelInstance();  
  APPFLOW_CFG.DelInstance();


  //--------------------------------------------------------------------------------------

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::UpdateInput()
* @brief      UpdateInput
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::UpdateInput()
{
  if(cursor)
    {     
      if(cursor->GetMotion()->IsReadyToTest())
        {
          INPCURSORMOTION_DIR motiondir = cursor->GetMotion()->GetDirectionByAngle(true);
          if(motiondir != INPCURSORMOTION_DIR_UNKNOWN)
            {
              switch(motiondir)
                {
                  case INPCURSORMOTION_DIR_DOWN       :
                  case INPCURSORMOTION_DIR_RIGHTUP    : makeaction = __L("WALK NORTH");
                                                        break;

                  case INPCURSORMOTION_DIR_RIGHT      :
                  case INPCURSORMOTION_DIR_LEFTUP     : makeaction = __L("WALK WEST" );
                                                        break;

                  case INPCURSORMOTION_DIR_LEFT       :
                  case INPCURSORMOTION_DIR_RIGHTDOWN  : makeaction = __L("WALK EAST" );
                                                        break;

                  case INPCURSORMOTION_DIR_UP         :
                  case INPCURSORMOTION_DIR_LEFTDOWN   : makeaction = __L("WALK SOUTH");
                                                        break;

                                          default     : break;
                }

              cursor->GetMotion()->Reset();
            }
        }
    }


  for(int c=0;c<DEVTESTSCANVAS2D_BUTTON_MAX;c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case DEVTESTSCANVAS2D_BUTTON_ESC      : { int x = 0;
                                                            int y = 0;

                                                            GetMainScreen()->Get_Position(x, y);

                                                            APPFLOW_CFG.Screen_SetPosX(x);
                                                            APPFLOW_CFG.Screen_SetPosY(y);

                                                            APPFLOW_CFG.Save();

                                                            SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                          }
                                                          break; 

                    case DEVTESTSCANVAS2D_BUTTON_SPACE  : Do_Tests();
                                                          break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case DEVTESTSCANVAS2D_BUTTON_UP     : makeaction = __L("WALK NORTH");   break;
                  case DEVTESTSCANVAS2D_BUTTON_DOWN   : makeaction = __L("WALK SOUTH");   break;
                  case DEVTESTSCANVAS2D_BUTTON_LEFT   : makeaction = __L("WALK WEST" );   break;
                  case DEVTESTSCANVAS2D_BUTTON_RIGHT  : makeaction = __L("WALK EAST" );   break;               
                }
            }

        }
    }

  return true;
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::Ini_Graphics(GRPSCREEN* screen)
* @brief      Ini_Graphics
* @ingroup    GRAPHIC
* 
* @param[in]  screen : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::Ini_Graphics(GRPSCREEN* screen)
{
  //--------------------------------------------------------------------------------------

  XPATH           xpath;
  GRPBITMAPFILE*  bitmapfile;

  bitmapfile = new GRPBITMAPFILE();
  if(!bitmapfile) return false;

  if(!backgroundbmp)
    {
      /*
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpath);
      xpath.Slash_Add();
      xpath.Add(__L("background.png"));

      backgroundbmp = bitmapfile->Load(xpath, GetMainScreen()->GetMode());
      if(!backgroundbmp) return false;
      */
   

      /*
      int x = 0;
      int y = 0;

      XPATH xpathbitmapref;  
        
      GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, xpathbitmapref);
      xpathbitmapref.Slash_Add();
      xpathbitmapref.Add(__L("ref.png"));

      GRPBITMAPFILE* bitmapfileref = new GRPBITMAPFILE(xpathbitmapref);
      if(bitmapfileref)
        {                                         
          GRPBITMAP* bitmapref = bitmapfileref->Load();         
          if(bitmapref)
            {                                      
              if(backgroundbmp->FindSubBitmap(bitmapref, x, y))
                {

                }
            }
        } 
      */

      /*
      GRPRECTINT  rect;
                  
      rect.x1 = 75;
      rect.x2 = rect.x1 + 100;

      rect.y1 = 310;
      rect.y2 = rect.y1 + 100;    

      GRPBITMAP* bitmapref = backgroundbmp->GetSubBitmap(rect);        
      if(bitmapref)
        { 
          if(backgroundbmp->FindSubBitmap(bitmapref, x, y))
            {

            }
        }         
      */
    }
  
  
  delete bitmapfile;
  

  screen->SetPosition(APPFLOW_CFG.Screen_GetPosX(), APPFLOW_CFG.Screen_GetPosY());
  screen->SetWidth(APPFLOW_CFG.Screen_GetWidth());
  screen->SetHeight(APPFLOW_CFG.Screen_GetHeight());

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(),  0,  0, (APPFLOW_CFG.Screen_GetMaxWidth()) , (APPFLOW_CFG.Screen_GetMaxHeight()));

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Main Screen] Width %d, height %d"),  screen->GetWidth(), screen->GetHeight());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::DrawFrame()
* @brief      DrawFrame
* @ingroup    GRAPHIC
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::DrawFrame()
{
  GRPVIEWPORT*      viewport = NULL;
  GRPCANVAS*        canvas   = NULL;
  GRPRECTINT*       rect     = NULL;

  viewport = GetMainScreen()->GetViewport(0);
  if(viewport) canvas =   viewport->GetCanvas();
  if(!canvas) return false;

  int width  = GetMainScreen()->GetWidth();
  int height = GetMainScreen()->GetHeight();

  //canvas->ReleaseDrawFramerate();  

  int poscanvas_x = (int)viewport->GetCanvasPositionX();
  int poscanvas_y = (int)viewport->GetCanvasPositionX();

  if(makeaction.Compare(__L("WALK NORTH"), true))   { poscanvas_y++;  }
  if(makeaction.Compare(__L("WALK WEST" ), true))   { poscanvas_x++;  }
  if(makeaction.Compare(__L("WALK EAST" ), true))   { poscanvas_x--;  }
  if(makeaction.Compare(__L("WALK SOUTH"), true))   { poscanvas_y--;  }
  
  viewport->SetCanvasPosition((float)poscanvas_x, (float)poscanvas_y);

  //canvas->Clear(&colorwhite);  

  canvas->RebuildAllAreas();
  canvas->DeleteAllRebuildAreas();

  //canvas->DrawFramerate(GetMainScreen(), 2, 20);


  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::Do_Tests()
* @brief      Do_Tests
* @ingroup    APPLICATION
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::Do_Tests()
{
  DEVTESTSCANVAS2D_LIST_FUNCTION listfunctions[] =  {   { false  , Test_ScriptLibInputSimulated     , __L("Test Script Lib Input Simulated")                    },
                                                        { true   , Test_LoadVectorFileDXF           , __L("Test Load Vector File DXF")                          }                                                     
                                                    };

  for(int c=0; c<(sizeof(listfunctions)/sizeof(DEVTESTSCANVAS2D_LIST_FUNCTION)); c++)
    {
       if(listfunctions[c].active)
         {
           bool status = listfunctions[c].function(this);           
         }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::Test_ScriptLibInputSimulated(DEVTESTSCANVAS2D* tests)
* @brief      Test_ScriptLibInputSimulated
* @ingroup    APPLICATION
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::Test_ScriptLibInputSimulated(DEVTESTSCANVAS2D* tests)
{
  SCRIPT::LoadScriptAndRun(APPFLOW_CFG.Scripts_GetAll(), DEVTESTSCANVAS2D::AdjustLibraries);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         bool DEVTESTSCANVAS2D::Test_LoadVectorFileDXF(DEVTESTSCANVAS2D* tests)
* @brief      Test_LoadVectorFileDXF
* @ingroup    TESTS
* 
* @param[in]  tests : 
* 
* @return     bool : true if is succesful. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTSCANVAS2D::Test_LoadVectorFileDXF(DEVTESTSCANVAS2D* tests)
{
  XPATH                 pathfile;
  GRPVECTORFILERESULT   result  = GRPVECTORFILERESULT_ERRORUNKNOWN;

  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GRAPHICS, pathfile);  
  pathfile.Slash_Add();
  pathfile.Add(__L("diamond.dxf"));    

  GRPVECTORFILE* vectorfile = GRPVECTORFILE::CreateInstance(pathfile);
  if(vectorfile)
    {  
      tests->SubscribeEvent(GRPVECTORFILE_XEVENTTYPE_PARTUNKNOWN, vectorfile);   

      XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Vector File Load] File [%s] "), pathfile.Get()); 
                
      result = vectorfile->Load(); 
      if(result != GRPVECTORFILERESULT_OK)
        {
          XTRACE_PRINTCOLOR(XTRACE_COLOR_RED, __L("[Vector File Load] Error %d "), result);
        }

      delete vectorfile;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void CBUILDER::AdjustLibraries(SCRIPT* script)
* @brief      AdjustLibraries
* @ingroup    APPLICATION
* 
* @param[in]  script : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::AdjustLibraries(SCRIPT* script)
{
  #ifdef SCRIPT_LIB_CFG_ACTIVE  
  SCRIPT_SET_LIB_CFG(script, APPFLOW_CFG);
  #endif

  #ifdef SCRIPT_LIB_WINDOWS_DEBUG  
  SCRIPT_SET_LIB_APPFLOWGRAPHICS(script, devtestscanvas2d)
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D::HandleEvent_Script(SCRIPT_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    APPLICATION
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::HandleEvent_Script(SCRIPT_XEVENT* event)
{
  switch(event->GetEventType())
    {
      case SCRIPT_XEVENT_TYPE_ERROR    : XTRACE_PRINTCOLOR(4,__L("Script ERROR [%d]: %s line %d -> \"%s\""), event->GetError(), event->GetErrorText()->Get(), event->GetNLine(), event->GetCurrentToken()->Get());
                                         break;

      case SCRIPT_XEVENT_TYPE_BREAK    : XTRACE_PRINTCOLOR(4,__L("Script BREAK: line %d -> \"%s\""), event->GetNLine(), event->GetCurrentToken()->Get());
                                         break;

    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D::HandleEvent_VectorFile(GRPVECTORFILE_XEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    TESTS
* 
* @param[in]  event : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::HandleEvent_VectorFile(GRPVECTORFILE_XEVENT* event)
{
   switch(event->GetEventType())
   {
      case GRPVECTORFILE_XEVENTTYPE_UNKNOWN         :  break;

      case GRPVECTORFILE_XEVENTTYPE_PARTUNKNOWN     :  XTRACE_PRINTCOLOR(XTRACE_COLOR_WARNING, __L("[Vector File] Type %s \"%s\" -> [%s]")  , GRPVECTORFILE::GetTypeText(event->GetType())
                                                                                                                                            , event->GetMsg()->Get()
                                                                                                                                            , event->GetPath()->Get());    
                                                       break;                                                                                
   }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* @param[in]  event : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
{
  switch(event->GetEventType())
    {
      case GRPXEVENT_TYPE_SCREEN_CREATING   : { GRPSCREEN* screen  = event->GetScreen();
                                                if(!screen) break;

                                                Ini_Graphics(screen);                                            
                                              }
                                              break;
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D::HandleEvent(XEVENT* xevent)
* @brief      Handle Event for the observer manager of this class
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* @param[in]  xevent : 
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::HandleEvent(XEVENT* xevent)
{
  if(!xevent) return;

  switch(xevent->GetEventFamily())
    {
      case XEVENT_TYPE_GRAPHICS       : { GRPXEVENT* event = (GRPXEVENT*)xevent;
                                          if(!event) return;

                                          HandleEvent_Graphics(event);
                                        }
                                        break;

      case XEVENT_TYPE_VECTORFILE   :  {  GRPVECTORFILE_XEVENT* event = (GRPVECTORFILE_XEVENT*)xevent;
                                          if(!event) 
                                            {
                                              return;
                                            }

                                          HandleEvent_VectorFile(event);                                                    
                                       }
                                       break;


    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         void DEVTESTSCANVAS2D::Clean()
* @brief      Clean the attributes of the class: Default initialice
* @note       INTERNAL
* @ingroup    GRAPHIC
* 
* @return     void : does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTSCANVAS2D::Clean()
{
  xtimer                      = NULL;

  for(int c=0; c<DEVTESTSCANVAS2D_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                      = NULL;

  backgroundbmp               = NULL;
}


