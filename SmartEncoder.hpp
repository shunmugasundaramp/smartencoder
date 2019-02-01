/*
Copyright [2016] [ssundaramp@outlook.com]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/**
  *
  * @file SmartEncoder.hpp
  * @brief Implementation of SmartEncoder which supports JSON and XML encoding functionalities
  * @author Shunmuga (ssundaramp@outlook.com)
  *
  */

#ifndef _SmartEncoder_hpp_
#define _SmartEncoder_hpp_

// System headers
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <typeinfo>

// User headers

#pragma once

using namespace std;

namespace AKKU {

namespace Smart {

/**
 *  A EncoderData class. It is a template class to maintain the data
 */
class EncoderData {
   protected:
      /// @brief Type of encoder object
      typedef enum {
         TYPE_NUMBER,         ///< Number object
         TYPE_STRING,         ///< String object
         TYPE_OBJECT,         ///< Another encoder object
         TYPE_DOUBLE,         ///< Double object
         TYPE_BOOL,           ///< Boolean object
         TYPE_NULL,           ///< Null object
      }TYPE;

   public:
      /// @brief Construct a new Encoder Data object
      /// @param[in] t - type of the object
      EncoderData(TYPE t) : m_type(t) {}

      /// @brief Destroy the Encoder Data object
      virtual ~EncoderData(){}

      /// @brief To get the type of data
      /// @return type
      TYPE GetType() { return m_type; }

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      virtual string ToJson() = 0;

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      virtual string ToXml() = 0;

   private:
      TYPE       m_type;
};

/**
 *  A EncoderNumData class. It is a class to maintain the integet/number data
 */
class EncoderNumData : public EncoderData {
   public:
      /// @brief Destroy the Encoder Num Data object
      virtual ~EncoderNumData();

      /// @brief Construct a new Encoder Num Data object
      /// @param[in] v - integer/number value
      EncoderNumData(long v);

      /// @brief Construct a new Encoder Num Data object
      /// @param[in] o - object to copy
      EncoderNumData(const EncoderNumData& o);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();

   private:
      long m_val;
};

/**
 *  A EncoderStringData class. It is a class to maintain the string data
 */
class EncoderStringData : public EncoderData {
   public:
      /// @brief Destroy the Encoder String Data object
      virtual ~EncoderStringData();

      /// @brief Construct a new Encoder String Data object
      /// @param[in] v - string value
      EncoderStringData(const char* v);

      /// @brief Construct a new Encoder String Data object
      /// @param[in] o - object to copy
      EncoderStringData(const EncoderStringData& o);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();

   private:
      string m_val;
};

/**
 *  A EncoderDoubleData class. It is a class to maintain the double/float data
 */
class EncoderDoubleData : public EncoderData {
   public:
      /// @brief Destroy the Encoder Double Data object
      virtual ~EncoderDoubleData();

      /// @brief Construct a new Encoder Double Data object
      /// @param[in] v - double value
      EncoderDoubleData(double v);

      /// @brief Construct a new Encoder Double Data object
      /// @param[in] o - object to copy
      EncoderDoubleData(const EncoderDoubleData& o);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();

   private:
      double m_val;
};

/**
 *  A EncoderBoolData class. It is a class to maintain the boolean data
 */
class EncoderBoolData : public EncoderData {
   public:
      /// @brief Destroy the Encoder Bool Data object
      virtual ~EncoderBoolData();

      /// @brief Construct a new Encoder Bool Data object
      /// @param[in] v - boolean value
      EncoderBoolData(bool v);

      /// @brief Construct a new Encoder Bool Data object
      /// @param[in] o - object to copy
      EncoderBoolData(const EncoderBoolData& o);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();

   private:
      bool m_val;
};

/**
 *  A EncoderNullData class. It is a class to maintain the boolean data
 */
class EncoderNullData : public EncoderData {
   public:
      /// @brief Destroy the Encoder Null Data object
      virtual ~EncoderNullData();

      /// @brief Construct a new Encoder Null Data object
      EncoderNullData();

      /// @brief Construct a new Encoder Null Data object
      /// @param[in] o - object to copy
      EncoderNullData(const EncoderNullData& o);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();
};

class Encoder;
/**
 *  A EncoderObjectData class. It is a class to maintain another object of Encoder
 */
class EncoderObjectData : public EncoderData {
   public:
      /// @brief Destroy the Encoder Object Data object
      virtual ~EncoderObjectData();

      /// @brief Construct a new Encoder Object Data object
      /// @param[in] o - object to copy
      EncoderObjectData(const EncoderObjectData& o);

      /// @brief Construct a new Encoder Object Data object
      /// @param[in] encoder - object of Encoder
      EncoderObjectData(Encoder& encoder);

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml();

   private:
      void Init(Encoder& encoder);

   private:
      Encoder *m_val;
};

/**
 *  A Encoder class. It is a class to do all Json encoding specific functionality
 */
class Encoder
{
   friend EncoderObjectData;
   public:
      /// @brief Construct a new Encoder object
      Encoder() {}

      /// @brief Destroy the Encoder object
      ~Encoder();

      /// @brief To get the encoder data for the given key.  It should create a new object, if it was not present
      /// @return  encoder data
      Encoder& operator[](const char* key);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(const char* value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(string value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(double value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(long value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(unsigned long value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(uint32_t value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(int32_t value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(bool value);

      /// @brief To assign the given value into the specific encoder data
      /// @return  none
      void operator=(Encoder& value);

      /// @brief To set the encoder data as null
      /// @return  none
      void AsNull();

      /// @brief To set the encoder data as array.  Otherwise it will maintain a single data
      /// @return  none
      void AsArray();

      /// @brief To set the attribute to encoder data
      /// @return  none
      void SetAttribute(const char* key, const char* value);

      /// @brief To set the attribute to encoder data
      /// @return  none
      void SetRootElement(const char* name) {m_rootElement = name;}

      /// @brief To convert the data into json encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToJson();

      /// @brief To convert the data into xml encoding.  Which should be override in the derived class
      /// @return  data in string notation
      string ToXml(bool shouldbefalse = false);

      /// @brief To get whether the object is empty or not
      /// @return  true or false
      bool IsEmpty() {return !m_db.size();}

   private:
      /// @brief To assign the EncoderData with the given key
      /// @return  none
      void Assign(EncoderData* d);

   private:
      //          first                ----> key
      //          second
      //                first
      //                   first       ----> array
      //                   second  ----> attributes
      //                second     ----> data
      vector< std::pair <                                                                                \
                          string,                                                                        \
                          std::pair <                                                                    \
                                      std::pair <                                                        \
                                                  bool,                                                  \
                                                  std::map < string, string >     \
                                                >,                                                       \
                                      vector< EncoderData* >                                             \
                                    >                                                                    \
                        >                                                                                \
            >  m_db;
      string   m_rootElement;
      string   m_localKey;
};

}; // namespace Smart

}; // namespace AKKU

#endif //_SmartEncoder_hpp_

