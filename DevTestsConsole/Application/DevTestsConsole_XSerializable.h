/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole_XSerializable.h
* 
* @class      DEVTESTSCONSOLE_XSERIALIZABLE
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

#ifndef _DEVTESTSCONSOLE_XSERIALIZABLE_H_
#define _DEVTESTSCONSOLE_XSERIALIZABLE_H_

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XSerializable.h"
#include "XSerializableBinary.h"

/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/

#include "XSerializable.h"

/*---- CLASS ---------------------------------------------------------------------------------------------------------*/


class TESTSERIALIZABLE2 : public XSERIALIZABLE
{ 
  public:
                                    TESTSERIALIZABLE2                  ()
                                    {
                                      Clean();

                                      value2 = 0x55AA55AA;
                                    }

    virtual                        ~TESTSERIALIZABLE2                  ()
                                    {
                                      Clean();                     
                                    }

    bool                            Serialize                          ()
                                    {
                                      Primitive_Add<int>(value2, __L("value2"));
                                      Primitive_Add<XSTRING>(string2, __L("string2"));

                                      return true;
                                    }


    bool                            Deserialize                        ()
                                    {   
                                      Primitive_Extract<int>(value2, __L("value2"));
                                      Primitive_Extract<XSTRING>(string2, __L("string2"));

                                      return true;
                                    }

  private:

    void                            Clean                              ()
                                    {
                                      value2 = 0;
                                    } 

    int                             value2;
    XSTRING                         string2;   

};


class TESTSERIALIZABLE : public XSERIALIZABLE
{ 
  public:
  
                                    TESTSERIALIZABLE                   ()
                                    {
                                      Clean();

                                      value1 = 0xAA55AA55;

                                      for(int c=0; c<10; c++)
                                        {
                                          TESTSERIALIZABLE2* ser = new TESTSERIALIZABLE2();
                                          if(ser)
                                            {
                                              vector_ser.Add(ser);
                                            }
                                        }

                                    }

    virtual                        ~TESTSERIALIZABLE                   ()
                                    {
                                      vector_ser.DeleteContents();
                                      vector_ser.DeleteAll();

                                      Clean();                     
                                    }

    bool                            Serialize                          ()
                                    {
                                      Primitive_Add<int>(value1, __L("value1"));
                                      Primitive_Add<XSTRING>(string1, __L("string1"));
                                      
                                      Class_Add<TESTSERIALIZABLE2>(&class_ser, __L("class_ser"));
                                      
                                      XVector_Add<TESTSERIALIZABLE2>(&vector_ser, __L("vector_ser"));

                                      return true;
                                    }


    bool                            Deserialize                        ()
                                    {    
                                      Primitive_Extract<int>(value1, __L("value1"));
                                      Primitive_Extract<XSTRING>(string1, __L("string1"));
                                      
                                      Class_Extract<TESTSERIALIZABLE2>(&class_ser, __L("class_ser"));
                                      
                                      XVector_Extract<TESTSERIALIZABLE2>(&vector_ser, __L("vector_ser"));

                                      return true;
                                    }

  private:

    void                            Clean                              ()
                                    {
                                       value1 = 0;
                                    } 

    int                             value1;
    XSTRING                         string1;
    TESTSERIALIZABLE2               class_ser;
    XVECTOR<TESTSERIALIZABLE2*>     vector_ser;
};

/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

#endif