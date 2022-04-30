/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTestGraphics.h
*
* @class      UNITTESTGRAPHICS
* @brief      GEN Unit Test Graphics class
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

#ifndef _UNITTESTGRAPHICS_H_
#define _UNITTESTGRAPHICS_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "APPGraphics.h"

#ifdef WINDOWS
  #include "INPWINDOWSKeyboardHook.h"
#endif

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

enum UNITTESTGRAPHICSXFSMEVENTS
{
  UNITTESTGRAPHICS_XFSMEVENT_NONE                 = 0 ,
  UNITTESTGRAPHICS_XFSMEVENT_INI                      ,
  UNITTESTGRAPHICS_XFSMEVENT_UPDATE                   ,
  UNITTESTGRAPHICS_XFSMEVENT_END                      ,

  UNITTESTGRAPHICS_LASTEVENT
};


enum UNITTESTGRAPHICSXFSMSTATES
{
  UNITTESTGRAPHICS_XFSMSTATE_NONE                 = 0 ,
  UNITTESTGRAPHICS_XFSMSTATE_INI                      ,
  UNITTESTGRAPHICS_XFSMSTATE_UPDATE                   ,
  UNITTESTGRAPHICS_XFSMSTATE_END                      ,

  UNITTESTGRAPHICS_LASTSTATE
};


enum UNITTESTGRAPHICSTASKID
{
  UNITTESTGRAPHICSTASKID_UNKNOWN                  = 0 ,
  UNITTESTGRAPHICSTASKID_CHECKMEMORYSTATUS            ,
};


enum UNITTESTGRAPHICS_BUTTONS
{
  UNITTESTGRAPHICS_BUTTON_UP                      = 0 ,
  UNITTESTGRAPHICS_BUTTON_DOWN                        ,
  UNITTESTGRAPHICS_BUTTON_LEFT                        ,
  UNITTESTGRAPHICS_BUTTON_RIGHT                       ,
  UNITTESTGRAPHICS_BUTTON_SPACE                       ,
  UNITTESTGRAPHICS_BUTTON_ESC                         ,
  UNITTESTGRAPHICS_BUTTON_F1                          ,
  UNITTESTGRAPHICS_BUTTON_F2                          ,
  UNITTESTGRAPHICS_BUTTON_F5                          ,
  UNITTESTGRAPHICS_BUTTON_F9                          ,
  UNITTESTGRAPHICS_BUTTON_PLUS                        ,
  UNITTESTGRAPHICS_BUTTON_MINUS                       ,

  UNITTESTGRAPHICS_BUTTON_MOUSE                       ,

  UNITTESTGRAPHICS_BUTTON_TOUCHSCREEN                 ,

  UNITTESTGRAPHICS_BUTTON_MAX
};


#define XTHREADGROUPID_UNITTESTGRAPHICS_DRAWFRAME     XTHREADGROUPID_APPOWNER + 100


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("UnitTestGraphics")
#define APPLICATION_ENTERPRISE                    __L("GEN Group")

#define APPLICATION_NAMEFILE                      __L("unittestgraphics")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
class XRAND;
class DIOINTERNET;
class DIOCHECKTCPIPCONNECTIONS;
class DIOCHECKINTERNETCONNECTION;
class DIOSCRAPERWEBPUBLICIP;
class DIOSCRAPERWEBGEOLOCATIONIP;
class DIOSCRAPERWEBUSERAGENTID;
class GRPBITMAPSECUENCE;
class INPBUTTON;
class INPCURSOR;
class UI_XEVENT;
class UI_ELEMENT;
class UI_ELEMENT_TEXT;
class INPWINDOWSKEYBOARDHOOK_XEVENT;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class UNITTESTGRAPHICS_CFG;


class UNITTESTGRAPHICS : public APPGRAPHICS, public XFSMACHINE
{
  public:
                                    UNITTESTGRAPHICS                        ();
    virtual                        ~UNITTESTGRAPHICS                        ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:
    
    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            Ini_UserInterface                       (bool on);

    bool                            DrawFrame                               ();

    bool                            UserInterface_ElementSelected           (UI_ELEMENT* element);
    bool                            UserInterface_ChangeLiteralText         (UI_ELEMENT_TEXT* element_text, XSTRING* maskvalue, XSTRING* maskresult);


    bool                            UnitTest_AVIVideoWrite                  ();

    void                            HandleEvent_WINDOWSKeyboardHook         (INPWINDOWSKEYBOARDHOOK_XEVENT* event);
    void                            HandleEvent_UserInterface               (UI_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimer;

    XRAND*                          xrand;

    INPBUTTON*                      button[UNITTESTGRAPHICS_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;
    
    GRPBITMAP*                      testbmp;
    
    #ifdef WINDOWS
    INPWINDOWSKEYBOARDHOOK*         kbhook;
    #endif
};


/*---- INLINE FUNCTIONS ----------------------------------------------------------------------------------------------*/

#endif

