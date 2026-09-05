/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Canvas2D.h
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
#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "Script_XEvent.h"

#include "APPFlowGraphics.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


enum DEVTESTS_CANVAS2DXFSMEVENTS
{
  DEVTESTS_CANVAS2D_XFSMEVENT_NONE                 = 0 ,
  DEVTESTS_CANVAS2D_XFSMEVENT_INI                      ,
  DEVTESTS_CANVAS2D_XFSMEVENT_UPDATE                   ,
  DEVTESTS_CANVAS2D_XFSMEVENT_END                      ,

  DEVTESTS_CANVAS2D_LASTEVENT
};


enum DEVTESTS_CANVAS2DXFSMSTATES
{
  DEVTESTS_CANVAS2D_XFSMSTATE_NONE                 = 0 ,
  DEVTESTS_CANVAS2D_XFSMSTATE_INI                      ,
  DEVTESTS_CANVAS2D_XFSMSTATE_UPDATE                   ,
  DEVTESTS_CANVAS2D_XFSMSTATE_END                      ,

  DEVTESTS_CANVAS2D_LASTSTATE
};


enum DEVTESTS_CANVAS2DTASKID
{
  DEVTESTS_CANVAS2DTASKID_UNKNOWN                  = 0 ,
  DEVTESTS_CANVAS2DTASKID_CHECKMEMORYSTATUS            ,
};


enum DEVTESTS_CANVAS2D_BUTTONS
{
  DEVTESTS_CANVAS2D_BUTTON_UP                      = 0 ,
  DEVTESTS_CANVAS2D_BUTTON_DOWN                        ,
  DEVTESTS_CANVAS2D_BUTTON_LEFT                        ,
  DEVTESTS_CANVAS2D_BUTTON_RIGHT                       ,
  DEVTESTS_CANVAS2D_BUTTON_SPACE                       ,
  DEVTESTS_CANVAS2D_BUTTON_ESC                         ,
  DEVTESTS_CANVAS2D_BUTTON_MOUSE                       ,
  DEVTESTS_CANVAS2D_BUTTON_TOUCHSCREEN                 ,

  DEVTESTS_CANVAS2D_BUTTON_MAX
};


class DEVTESTS_CANVAS2D;
typedef bool (*DEVTESTS_CANVAS2D_FUNCTION)(DEVTESTS_CANVAS2D* tests);

typedef struct
{
  bool                        active;
  DEVTESTS_CANVAS2D_FUNCTION   function;
  XCHAR*                      namefunction;

} DEVTESTS_CANVAS2D_LIST_FUNCTION;


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("DevTests_Canvas2D")
#define APPLICATION_NAMEFILE                      __L("devtests_canvas2d")

#define APPLICATION_OWNER                         __L("EndoraSoft")

#define APPLICATION_YEAROFCREATION                2023


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class XTIME;
class XTIMER;
class XRAND;
class XTHREAD;
class XDIR;
class XSCHEDULER;
class XSCHEDULER_XEVENT;
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
class GRPVECTORFILE_XEVENT;
class GRPXEVENT;
class GRPBITMAP;
class GRPBITMAPSEQUENCE;
class SCRIPT;
class DEVTESTS_CANVAS2D_CFG;


class DEVTESTS_CANVAS2D : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    DEVTESTS_CANVAS2D                        ();
    virtual                        ~DEVTESTS_CANVAS2D                        ();

    bool                            InitFSMachine                           ();

    bool                            AppProc_Ini                             ();
    bool                            AppProc_FirstUpdate                     ();
    bool                            AppProc_Update                          ();
    bool                            AppProc_End                             ();
   
  private:

    bool                            UpdateInput                             ();

    bool                            Ini_Graphics                            (GRPSCREEN* screen);
    bool                            DrawFrame                               ();   

    bool                            Do_Tests                                (); 

    static bool                     Test_ScriptLibInputSimulated            (DEVTESTS_CANVAS2D* tests);
    static bool                     Test_LoadVectorFileDXF                  (DEVTESTS_CANVAS2D* tests);
   
    static void                     AdjustLibraries                         (SCRIPT* script);

    void                            HandleEvent_Script                      (SCRIPT_XEVENT* event);
    void                            HandleEvent_VectorFile                  (GRPVECTORFILE_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimer;

    INPBUTTON*                      button[DEVTESTS_CANVAS2D_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;

    GRPBITMAP*                      backgroundbmp;  
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/


