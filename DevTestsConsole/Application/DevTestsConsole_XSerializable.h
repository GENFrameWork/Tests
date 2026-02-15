/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       DevTestsConsole_XSerializable.h
* 
* @class      DEVTESTSCONSOLE_XSERIALIZABLE
* @brief      Developed Tests console Serializable class
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

#include "XString.h"
#include "XSerializable.h"



/*---- DEFINES & ENUMS  ----------------------------------------------------------------------------------------------*/




/*---- CLASS ---------------------------------------------------------------------------------------------------------*/

class TESTSERIALIZABLE2 : public XSERIALIZABLE
{ 
  public:
                                    TESTSERIALIZABLE2                  ()
                                    {
                                      Clean();                                                       
                                    }

    virtual                        ~TESTSERIALIZABLE2                  ()
                                    {
                                      Clean();                     
                                    }

    int                             GetValue2                          ()
                                    {
                                      return value2;
                                    }    

    void                            SetValue2                          (int value2)
                                    {
                                      this->value2 = value2;
                                    }    

    XSTRING*                        GetString2                         ()  
                                    {
                                      return &string2;    
                                    }

    bool                            Serialize                          ()
                                    {
                                      Primitive_Add<int>(value2           , __L("value2"));
                                      Primitive_Add<bool>(value3          , __L("value3"));
                                      Primitive_Add<XSTRING*>(&string2    , __L("string2"));

                                      return true;
                                    }


    bool                            Deserialize                        ()
                                    {   
                                      Primitive_Extract<int>(value2      , __L("value2"));
                                      Primitive_Extract<bool>(value3     , __L("value3"));
                                      Primitive_Extract<XSTRING>(string2 , __L("string2"));

                                      return true;
                                    }
  private:

    void                            Clean                              ()
                                    {
                                      value2  = 0;                               
                                      value3  = true;   
                                      string2 = __L("");
                                    } 

    int                             value2;
    bool                            value3;      
    XSTRING                         string2;   

};


class TESTSERIALIZABLE : public XSERIALIZABLE
{ 
  public:
  
                                    TESTSERIALIZABLE                   ()
                                    {
                                      Clean();                                  

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


    int                             GetValue1                          ()
                                    {
                                      return value1;
                                    }    

    void                            SetValue1                          (int value1)
                                    {
                                      this->value1 = value1;
                                    }    

    XSTRING*                        GetString1                         ()  
                                    {
                                      return &string1;    
                                    }

    TESTSERIALIZABLE2*              GetClassSer                        ()
                                    {
                                      return &class_ser;
                                    }

    XVECTOR<TESTSERIALIZABLE2*>*    GetVectorSer                       ()
                                    {
                                      return &vector_ser;
                                    }
    
    bool                            Serialize                          ()
                                    {
                                      Primitive_Add<int>(value1, __L("value1"));
                                      Primitive_Add<bool>(value2, __L("value2"));
                                      Primitive_Add<XSTRING*>(&string1, __L("string1"));
                                      
                                      Class_Add<TESTSERIALIZABLE2>(&class_ser, __L("class_ser"));
                                      
                                      XVectorClass_Add<TESTSERIALIZABLE2>(&vector_ser, __L("vector_ser"), __L(""));

                                      return true;
                                    }


    bool                            Deserialize                        ()
                                    {    
                                      Primitive_Extract<int>(value1, __L("value1"));
                                      Primitive_Extract<bool>(value2, __L("value2"));
                                      Primitive_Extract<XSTRING&>(string1, __L("string1"));
                                      
                                      Class_Extract<TESTSERIALIZABLE2>(&class_ser, __L("class_ser"));
                                      
                                      XVectorClass_Extract<TESTSERIALIZABLE2>(&vector_ser, __L("vector_ser"), __L(""));

                                      return true;
                                    }


  private:

    void                            Clean                              ()
                                    {
                                      value1  = 0;
                                      value2  = false;  
                                      string1 = __L("");
                                    } 

    int                             value1;
    bool                            value2;    
    XSTRING                         string1;
    TESTSERIALIZABLE2               class_ser;
    XVECTOR<TESTSERIALIZABLE2*>     vector_ser;
};




/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/




