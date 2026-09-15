/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Script.h
* @class      UNITTESTS_SCRIPT
* @brief      Script unit tests application
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "APPFlowBase.h"


/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#define APPLICATION_VERSION                       0
#define APPLICATION_SUBVERSION                    0
#define APPLICATION_SUBVERSIONERR                 1

#define APPLICATION_NAMEAPP                       __L("Script Unit Tests")
#define APPLICATION_NAMEFILE                      __L("unittests_script")
#define APPLICATION_OWNER                         __L("GEN Framework")
#define APPLICATION_YEAROFCREATION                2026

#define APPLICATION_CFG_NAMEFILE                  APPLICATION_NAMEFILE
#define APPLICATION_LNG_NAMEFILE                  APPLICATION_NAMEFILE
#define APPLICATION_LOG_NAMEFILE                  APPLICATION_NAMEFILE
#define APPLICATION_DIRECTORYMAIN                 __L("assets")


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class UNITTESTS_SCRIPT : public APPFLOWBASE
{
  public:
                        UNITTESTS_SCRIPT                    ();
    virtual            ~UNITTESTS_SCRIPT                    ();

    bool                AppProc_Ini                         ();
    bool                AppProc_FirstUpdate                 ();
    bool                AppProc_Update                      ();
    bool                AppProc_LastUpdate                  ();
    bool                AppProc_End                         ();

  private:

    void                Clean                               ();
};


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/
