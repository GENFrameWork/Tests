/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Canvas2D.cpp
*
* @class      DEVTESTS_CANVAS2D
* @brief      Developed tests Canvas 2D class
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

#include "DevTests_Canvas2D.h"

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

#include "GRP2DCanvas.h"
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


#include "DevTests_Canvas2D_CFG.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(DEVTESTS_CANVAS2D, devtests_canvas2d)

GRP2DCOLOR_RGBA8  colorblack(0, 0, 0);
GRP2DCOLOR_RGBA8  colorwhite(255, 255, 255);
GRP2DCOLOR_RGBA8  colorred(255, 0, 0);
GRP2DCOLOR_RGBA8  colorgreen(0, 255, 0);
GRP2DCOLOR_RGBA8  colorblue(0, 0, 255);
GRP2DCOLOR_RGBA8  colorgray(10, 10, 10, 150);


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTS_CANVAS2D::DEVTESTS_CANVAS2D()
* @brief      Constructor of class.
* @ingroup    TESTS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTS_CANVAS2D::DEVTESTS_CANVAS2D() :  XFSMACHINE(0)
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         DEVTESTS_CANVAS2D::~DEVTESTS_CANVAS2D()
* @brief      Destructor of class.
* @ingroup    TESTS
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
DEVTESTS_CANVAS2D::~DEVTESTS_CANVAS2D()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::InitFSMachine()
* @brief      Initializes the finite state machine.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::InitFSMachine()
{
  if(!AddState( DEVTESTS_CANVAS2D_XFSMSTATE_NONE            ,
                DEVTESTS_CANVAS2D_XFSMEVENT_INI             , DEVTESTS_CANVAS2D_XFSMSTATE_INI           ,
                DEVTESTS_CANVAS2D_XFSMEVENT_END             , DEVTESTS_CANVAS2D_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTS_CANVAS2D_XFSMSTATE_INI             ,
                DEVTESTS_CANVAS2D_XFSMEVENT_UPDATE          , DEVTESTS_CANVAS2D_XFSMSTATE_UPDATE        ,                
                DEVTESTS_CANVAS2D_XFSMEVENT_END             , DEVTESTS_CANVAS2D_XFSMSTATE_END           ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTS_CANVAS2D_XFSMSTATE_UPDATE          ,               
                DEVTESTS_CANVAS2D_XFSMEVENT_END             , DEVTESTS_CANVAS2D_XFSMSTATE_END           ,                 
                XFSMACHINESTATE_EVENTDEFEND)) return false;


  if(!AddState( DEVTESTS_CANVAS2D_XFSMSTATE_END             ,
                DEVTESTS_CANVAS2D_XFSMEVENT_NONE            , DEVTESTS_CANVAS2D_XFSMSTATE_NONE          ,
                XFSMACHINESTATE_EVENTDEFEND)) return false;

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::AppProc_Ini()
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

  SetEvent(DEVTESTS_CANVAS2D_XFSMEVENT_INI);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::AppProc_FirstUpdate()
{
  //--------------------------------------------------------------------------------------

  INPDEVICE* inpdevice;

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_KEYBOARD);
  if(inpdevice)
    {
      button[DEVTESTS_CANVAS2D_BUTTON_UP]      = inpdevice->GetButton(INPBUTTON_ID_UP);
      button[DEVTESTS_CANVAS2D_BUTTON_DOWN]    = inpdevice->GetButton(INPBUTTON_ID_DOWN);
      button[DEVTESTS_CANVAS2D_BUTTON_LEFT]    = inpdevice->GetButton(INPBUTTON_ID_LEFT);
      button[DEVTESTS_CANVAS2D_BUTTON_RIGHT]   = inpdevice->GetButton(INPBUTTON_ID_RIGHT);
      button[DEVTESTS_CANVAS2D_BUTTON_SPACE]   = inpdevice->GetButton(INPBUTTON_ID_SPACE);
      button[DEVTESTS_CANVAS2D_BUTTON_ESC]     = inpdevice->GetButton(INPBUTTON_ID_ESCAPE);
      button[DEVTESTS_CANVAS2D_BUTTON_MOUSE]   = inpdevice->GetButton(INPBUTTON_ID_MOUSE_RIGHT);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_MOUSE);
  if(inpdevice)
    {
      button[DEVTESTS_CANVAS2D_BUTTON_MOUSE] = inpdevice->GetButton(INPBUTTON_ID_MOUSE_LEFT);
      cursor = inpdevice->GetCursor(0);
    }

  inpdevice = GEN_INPMANAGER.GetDevice(INPDEVICE_TYPE_TOUCHSCREEN);
  if(inpdevice)
    {     
      button[DEVTESTS_CANVAS2D_BUTTON_TOUCHSCREEN] = inpdevice->GetButton(INPBUTTON_ID_TOUCHSCREEN);     
      cursor = inpdevice->GetCursor(0);
    }  

  //--------------------------------------------------------------------------------

  GRPVIEWPORT* viewport = NULL;
  GRP2DCANVAS*   canvas   = NULL;

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
* @fn         bool DEVTESTS_CANVAS2D::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::AppProc_Update()
{
  if(GetEvent()==DEVTESTS_CANVAS2D_XFSMEVENT_NONE) // Not GEN_NEW event
    {
      switch(GetCurrentState())
        {
          case DEVTESTS_CANVAS2D_XFSMSTATE_NONE        : break;

          case DEVTESTS_CANVAS2D_XFSMSTATE_INI         : break;

          case DEVTESTS_CANVAS2D_XFSMSTATE_UPDATE      : { UpdateInput();

                                                          DrawFrame();

                                                          GetMainScreen()->UpdateViewports();
                                                        }
                                                        break;

          case DEVTESTS_CANVAS2D_XFSMSTATE_END         : break;

        }
    }
   else //  New event
    {
      if(GetEvent()<DEVTESTS_CANVAS2D_LASTEVENT)
        {
          CheckTransition();

          switch(GetCurrentState())
            {
              case DEVTESTS_CANVAS2D_XFSMSTATE_NONE    : break;

              case DEVTESTS_CANVAS2D_XFSMSTATE_INI     : SetEvent(DEVTESTS_CANVAS2D_XFSMEVENT_UPDATE);                                                       
                                                        break;

              case DEVTESTS_CANVAS2D_XFSMSTATE_UPDATE  : break;

              case DEVTESTS_CANVAS2D_XFSMSTATE_END     : break;
            }
        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::AppProc_End()
* @brief      Ends the application process.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::AppProc_End()
{
  XSTRING string;
  XSTRING stringresult;

  //--------------------------------------------------------------------------------------

  SetCurrentState(DEVTESTS_CANVAS2D_XFSMSTATE_END);

  //--------------------------------------------------------------------------------------

  if(backgroundbmp)
    {
      GEN_DELETE backgroundbmp;
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
* @fn         bool DEVTESTS_CANVAS2D::UpdateInput()
* @brief      Updates the input state.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::UpdateInput()
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


  for(int c=0;c<DEVTESTS_CANVAS2D_BUTTON_MAX;c++)
    {
      if(button[c])
        {
          if(button[c]->IsPressedWithRelease())
            {
              switch(c)
                {
                  case DEVTESTS_CANVAS2D_BUTTON_ESC      : { int x = 0;
                                                            int y = 0;

                                                            GetMainScreen()->Get_Position(x, y);

                                                            APPFLOW_CFG.Screen_SetPosX(x);
                                                            APPFLOW_CFG.Screen_SetPosY(y);

                                                            APPFLOW_CFG.Save();

                                                            SetExitType(APPFLOWBASE_EXITTYPE_BY_USER);
                                                          }
                                                          break; 

                    case DEVTESTS_CANVAS2D_BUTTON_SPACE  : Do_Tests();
                                                          break;
                }
            }

          if(button[c]->IsPressed())
            {
              switch(c)
                {
                  case DEVTESTS_CANVAS2D_BUTTON_UP     : makeaction = __L("WALK NORTH");   break;
                  case DEVTESTS_CANVAS2D_BUTTON_DOWN   : makeaction = __L("WALK SOUTH");   break;
                  case DEVTESTS_CANVAS2D_BUTTON_LEFT   : makeaction = __L("WALK WEST" );   break;
                  case DEVTESTS_CANVAS2D_BUTTON_RIGHT  : makeaction = __L("WALK EAST" );   break;               
                }
            }

        }
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
* @brief      Initializes the graphics subsystem.
* @ingroup    TESTS
*
* @param[in]  screen : screen where the graphics resources are initialized.
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::Ini_Graphics(GRPSCREEN* screen)
{
  //--------------------------------------------------------------------------------------

  XPATH           xpath;
  GRPBITMAPFILE*  bitmapfile;

  bitmapfile = GEN_NEW GRPBITMAPFILE();
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

      GRPBITMAPFILE* bitmapfileref = GEN_NEW GRPBITMAPFILE(xpathbitmapref);
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
  
  
  GEN_DELETE bitmapfile;
  

  screen->SetPosition(APPFLOW_CFG.Screen_GetPosX(), APPFLOW_CFG.Screen_GetPosY());
  screen->SetWidth(APPFLOW_CFG.Screen_GetWidth());
  screen->SetHeight(APPFLOW_CFG.Screen_GetHeight());

  GetMainScreen()->CreateViewport(GRPVIEWPORT_ID_MAIN , 0.0f, 0.0f, (float)screen->GetWidth(), (float)screen->GetHeight(),  0,  0, (APPFLOW_CFG.Screen_GetMaxWidth()) , (APPFLOW_CFG.Screen_GetMaxHeight()));

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("[Main Screen] Width %d, height %d"),  screen->GetWidth(), screen->GetHeight());

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::DrawFrame()
* @brief      Draws the current frame.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::DrawFrame()
{
  GRPVIEWPORT*      viewport = NULL;
  GRP2DCANVAS*        canvas   = NULL;
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
* @fn         bool DEVTESTS_CANVAS2D::Do_Tests()
* @brief      Runs the configured tests.
* @ingroup    TESTS
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::Do_Tests()
{
  DEVTESTS_CANVAS2D_LIST_FUNCTION listfunctions[] =  {   { false  , Test_ScriptLibInputSimulated     , __L("Test Script Lib Input Simulated")                    },
                                                        { true   , Test_LoadVectorFileDXF           , __L("Test Load Vector File DXF")                          }                                                     
                                                    };

  for(int c=0; c<(sizeof(listfunctions)/sizeof(DEVTESTS_CANVAS2D_LIST_FUNCTION)); c++)
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
* @fn         bool DEVTESTS_CANVAS2D::Test_ScriptLibInputSimulated(DEVTESTS_CANVAS2D* tests)
* @brief      Runs the script lib input simulated test.
* @ingroup    TESTS
*
* @param[in]  tests : test application instance used by the test.
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::Test_ScriptLibInputSimulated(DEVTESTS_CANVAS2D* tests)
{
  SCRIPT::LoadScriptAndRun(APPFLOW_CFG.Scripts_GetAll(), DEVTESTS_CANVAS2D::AdjustLibraries);

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool DEVTESTS_CANVAS2D::Test_LoadVectorFileDXF(DEVTESTS_CANVAS2D* tests)
* @brief      Runs the load vector file dxf test.
* @ingroup    TESTS
*
* @param[in]  tests : test application instance used by the test.
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool DEVTESTS_CANVAS2D::Test_LoadVectorFileDXF(DEVTESTS_CANVAS2D* tests)
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

      GEN_DELETE vectorfile;
    }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTS_CANVAS2D::AdjustLibraries(SCRIPT* script)
* @brief      Adjusts the script libraries.
* @ingroup    TESTS
*
* @param[in]  script : script instance used to adjust the available libraries.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::AdjustLibraries(SCRIPT* script)
{
  #ifdef SCRIPT_LIB_CFG_ACTIVE  
  SCRIPT_SET_LIB_CFG(script, APPFLOW_CFG);
  #endif

  #ifdef SCRIPT_LIB_WINDOWS_DEBUG  
  SCRIPT_SET_LIB_APPFLOWGRAPHICS(script, devtests_canvas2d)
  #endif
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void DEVTESTS_CANVAS2D::HandleEvent_Script(SCRIPT_XEVENT* event)
* @brief      Handles script events.
* @ingroup    TESTS
*
* @param[in]  event : event information to process.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::HandleEvent_Script(SCRIPT_XEVENT* event)
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
* @fn         void DEVTESTS_CANVAS2D::HandleEvent_VectorFile(GRPVECTORFILE_XEVENT* event)
* @brief      Handles vector file events.
* @ingroup    TESTS
*
* @param[in]  event : event information to process.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::HandleEvent_VectorFile(GRPVECTORFILE_XEVENT* event)
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
* @fn         void DEVTESTS_CANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
* @brief      Handles graphics events.
* @ingroup    TESTS
*
* @param[in]  event : event information to process.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::HandleEvent_Graphics(GRPXEVENT* event)
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
* @fn         void DEVTESTS_CANVAS2D::HandleEvent(XEVENT* xevent)
* @brief      Handles an event.
* @ingroup    TESTS
*
* @param[in]  xevent : event information to process.
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::HandleEvent(XEVENT* xevent)
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
* @fn         void DEVTESTS_CANVAS2D::Clean()
* @brief      Cleans the object internal state.
* @ingroup    TESTS
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void DEVTESTS_CANVAS2D::Clean()
{
  xtimer                      = NULL;

  for(int c=0; c<DEVTESTS_CANVAS2D_BUTTON_MAX; c++)
    {
      button[c] = NULL;
    }

  cursor                      = NULL;

  backgroundbmp               = NULL;
}


