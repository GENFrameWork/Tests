/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsCanvas2D.h
* 
* @class      DEVTESTSCANVAS2D
* @brief      Developed Tests Canvas 2D class
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

#ifndef _DEVTESTSCANVAS2D_H_
#define _DEVTESTSCANVAS2D_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XDateTime.h"
#include "XFSMachine.h"
#include "XString.h"
#include "XScheduler.h"

#include "DIOStream.h"
#include "DIOURL.h"

#include "Script_XEvent.h"

#include "APPFlowGraphics.h"

#pragma endregion


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/
#pragma region DEFINES_ENUMS


enum DEVTESTSCANVAS2DXFSMEVENTS
{
  DEVTESTSCANVAS2D_XFSMEVENT_NONE                 = 0 ,
  DEVTESTSCANVAS2D_XFSMEVENT_INI                      ,
  DEVTESTSCANVAS2D_XFSMEVENT_UPDATE                   ,
  DEVTESTSCANVAS2D_XFSMEVENT_END                      ,

  DEVTESTSCANVAS2D_LASTEVENT
};


enum DEVTESTSCANVAS2DXFSMSTATES
{
  DEVTESTSCANVAS2D_XFSMSTATE_NONE                 = 0 ,
  DEVTESTSCANVAS2D_XFSMSTATE_INI                      ,
  DEVTESTSCANVAS2D_XFSMSTATE_UPDATE                   ,
  DEVTESTSCANVAS2D_XFSMSTATE_END                      ,

  DEVTESTSCANVAS2D_LASTSTATE
};


enum DEVTESTSCANVAS2DTASKID
{
  DEVTESTSCANVAS2DTASKID_UNKNOWN                  = 0 ,
  DEVTESTSCANVAS2DTASKID_CHECKMEMORYSTATUS            ,
};


enum DEVTESTSCANVAS2D_BUTTONS
{
  DEVTESTSCANVAS2D_BUTTON_UP                      = 0 ,
  DEVTESTSCANVAS2D_BUTTON_DOWN                        ,
  DEVTESTSCANVAS2D_BUTTON_LEFT                        ,
  DEVTESTSCANVAS2D_BUTTON_RIGHT                       ,
  DEVTESTSCANVAS2D_BUTTON_SPACE                       ,
  DEVTESTSCANVAS2D_BUTTON_ESC                         ,
  DEVTESTSCANVAS2D_BUTTON_MOUSE                       ,
  DEVTESTSCANVAS2D_BUTTON_TOUCHSCREEN                 ,

  DEVTESTSCANVAS2D_BUTTON_MAX
};


class DEVTESTSCANVAS2D;
typedef bool (*DEVTESTSCANVAS2D_FUNCTION)(DEVTESTSCANVAS2D* tests);

typedef struct
{
  bool                        active;
  DEVTESTSCANVAS2D_FUNCTION   function;
  XCHAR*                      namefunction;

} DEVTESTSCANVAS2D_LIST_FUNCTION;


#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    1
#define APPLICATION_SUBVERSIONERR                 0

#define APPLICATION_NAMEAPP                       __L("DevTestsCanvas2D")
#define APPLICATION_NAMEFILE                      __L("devtestscanvas2d")

#define APPLICATION_OWNER                         __L("GEN Group")

#define APPLICATION_YEAROFCREATION                2023

#pragma endregion


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/
#pragma region CLASS

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
class DEVTESTSCANVAS2D_CFG;


class DEVTESTSCANVAS2D : public APPFLOWGRAPHICS, public XFSMACHINE
{
  public:
                                    DEVTESTSCANVAS2D                        ();
    virtual                        ~DEVTESTSCANVAS2D                        ();

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

    static bool                     Test_ScriptLibInputSimulated            (DEVTESTSCANVAS2D* tests);
    static bool                     Test_LoadVectorFileDXF                  (DEVTESTSCANVAS2D* tests);
   
    static void                     AdjustLibraries                         (SCRIPT* script);

    void                            HandleEvent_Script                      (SCRIPT_XEVENT* event);
    void                            HandleEvent_VectorFile                  (GRPVECTORFILE_XEVENT* event);
    void                            HandleEvent_Graphics                    (GRPXEVENT* event);
    void                            HandleEvent                             (XEVENT* xevent);

    void                            Clean                                   ();

    XTIMER*                         xtimer;

    INPBUTTON*                      button[DEVTESTSCANVAS2D_BUTTON_MAX];
    INPCURSOR*                      cursor;

    XSTRING                         makeaction;

    GRPBITMAP*                      backgroundbmp;  
};

#pragma endregion


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
#pragma region FUNCTIONS_PROTOTYPES


#pragma endregion


#endif
