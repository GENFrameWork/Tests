/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole_Property.h
* 
* @class      DEVTESTSCONSOLE_XPROPERTY
* @brief      
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

#ifndef _DEVTESTSCONSOLE_XPROPERTY_H_
#define _DEVTESTSCONSOLE_XPROPERTY_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XProperty.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/


/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class DEVTESTSCONSOLE_PROPERTY
{ 
  public:                                     
                      DEVTESTSCONSOLE_PROPERTY        () : x(this), y(this), z(this)
                      {
                        x_ = 0.0f;
                        y_ = 0.0f;
                        z_ = 10.0f;
                      }
                      /*
                      DEVTESTSCONSOLE_PROPERTY        (double x0, double y0) : x_(x0), y_(y0), x(this), y(this), z(this)
                      {
                        z_ = 10.0f;
                      } 
                      */

    void              SetX                            (double x) 
                      { 
                        x_ = x; 
                      }

    double            GetX                            () 
                      { 
                        return x_; 
                      } 

    XPROPERTY<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetX, &DEVTESTSCONSOLE_PROPERTY::SetX> x;

    void              SetY                            (double y) 
                      { 
                        y_ = y;                       
                      }

    double            GetY                            () 
                      { 
                        return y_; 
                      }

   
    XPROPERTY<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetY, &DEVTESTSCONSOLE_PROPERTY::SetY> y;


    double            GetZ                            ()
                      {
                        return z_;
                      }


    XPROPERTYG<DEVTESTSCONSOLE_PROPERTY, double, &DEVTESTSCONSOLE_PROPERTY::GetZ> z;

    double            x_;
    double            y_;
    double            z_;   
};



class DEVTESTSCONSOLE_PROPERTY2
{
  public:
                      DEVTESTSCONSOLE_PROPERTY2         () :  data(this)
                      {

                      }

                      /*
                      DEVTESTSCONSOLE_PROPERTY2         (DEVTESTSCONSOLE_PROPERTY data0) : data_(data0), data(this)
                      {
                      }
                      */

    void              SetX                              (DEVTESTSCONSOLE_PROPERTY data)
                      {
                        data_.x = data.x;
                      }

    DEVTESTSCONSOLE_PROPERTY GetX                       ()
                      {
                        return data_;
                      }

    
    XPROPERTY<DEVTESTSCONSOLE_PROPERTY2, DEVTESTSCONSOLE_PROPERTY, &DEVTESTSCONSOLE_PROPERTY2::GetX, &DEVTESTSCONSOLE_PROPERTY2::SetX>  data;

    DEVTESTSCONSOLE_PROPERTY data2;


  private:

    DEVTESTSCONSOLE_PROPERTY data_;

};



/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif