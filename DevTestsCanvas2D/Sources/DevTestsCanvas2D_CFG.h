/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsCanvas2D_CFG.h
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

#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPFlowCFG.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define DEVTESTSCANVAS2DCFG_SECTIONGENERAL              __L("general")
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_POSX         __L("screen_posx")  
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_POSY         __L("screen_posy")  
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_WIDTH        __L("screen_width")  
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_HEIGHT       __L("screen_height")  
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_MAXWIDTH     __L("screen_maxwidth")  
#define DEVTESTSCANVAS2DCFG_GENERAL_SCREEN_MAXHEIGHT    __L("screen_maxheight")  



/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DEVTESTSCANVAS2D_CFG : public APPFLOWCFG
{
  public:

    static bool                     GetIsInstanced                          ();
    static DEVTESTSCANVAS2D_CFG&    GetInstance                             (bool ini = true);
    static bool                     DelInstance                             ();

    bool                            DoVariableMapping                       (); 
    bool                            DoDefault                               ();

    int                             Screen_GetPosX                          ();
    int                             Screen_GetPosY                          ();
    void                            Screen_SetPosX                          (int posx);
    void                            Screen_SetPosY                          (int posy);

    int                             Screen_GetWidth                         ();
    int                             Screen_GetHeight                        ();

    int                             Screen_GetMaxWidth                      ();
    int                             Screen_GetMaxHeight                     ();


  private:

                                    DEVTESTSCANVAS2D_CFG                    (XCHAR* namefile);
                                    DEVTESTSCANVAS2D_CFG                    (DEVTESTSCANVAS2D_CFG const&);       // Don't implement
    virtual                        ~DEVTESTSCANVAS2D_CFG                    ();

    void                            operator =                              (DEVTESTSCANVAS2D_CFG const&);       // Don't implement

    void                            Clean                                   ();

    static DEVTESTSCANVAS2D_CFG*    instance;

    int                             screen_posx;    
    int                             screen_posy;    
    int                             screen_width;    
    int                             screen_height;    
    int                             screen_maxwidth;    
    int                             screen_maxheight;    
};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/





