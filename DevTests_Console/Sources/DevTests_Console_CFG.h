/**-------------------------------------------------------------------------------------------------------------------
*
* @file       DevTests_Console_CFG.h
*
* @class      DEVTESTS_CONSOLE_CFG
* @brief      Developed tests console configuration class
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

#define DEVTESTS_CONSOLE_CFG_SECTION_DATABASE                         __L("database")
#define DEVTESTS_CONSOLE_CFG_DATABASE_URL                             __L("url")
#define DEVTESTS_CONSOLE_CFG_DATABASE_PORT                            __L("port")
#define DEVTESTS_CONSOLE_CFG_DATABASE_DATABASENAME                    __L("databasename")
#define DEVTESTS_CONSOLE_CFG_DATABASE_USER                            __L("user")
#define DEVTESTS_CONSOLE_CFG_DATABASE_PASSWORD                        __L("password")
#define DEVTESTS_CONSOLE_CFG_DATABASE_TIMEOUTCONNECTION               __L("timeoutconnection")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class DEVTESTS_CONSOLE_CFG : public APPFLOWCFG
{
  public:


    static bool                     GetIsInstanced                            ();
    static DEVTESTS_CONSOLE_CFG&     GetInstance                               (bool ini = true);
    static bool                     DelInstance                               ();

    bool                            DoVariableMapping                         (); 
    bool                            DoDefault                                 ();

    XSTRING*                        Database_GetURL                           ();
    XDWORD                          Database_GetPort                          ();
    XSTRING*                        Database_DatabaseName                     ();
    XSTRING*                        Database_GetUser                          ();
    XSTRING*                        Database_GetPassword                      ();
    int                             Database_GetTimeoutConnection             ();
    
  private:
                                    DEVTESTS_CONSOLE_CFG                       (XCHAR* namefile);
                                    DEVTESTS_CONSOLE_CFG                       (DEVTESTS_CONSOLE_CFG const&);        
    virtual                        ~DEVTESTS_CONSOLE_CFG                       ();

    void                            operator =                                (DEVTESTS_CONSOLE_CFG const&);        


    void                            Clean                                     ();

    static DEVTESTS_CONSOLE_CFG*     instance;

    XSTRING                         db_URL;
    XDWORD                          db_port;
    XSTRING                         db_databasename;
    XSTRING                         db_user;
    XSTRING                         db_password;
    int                             db_timeoutconnection;
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/


