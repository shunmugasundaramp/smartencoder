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
  * @file SmartEncoder.cpp
  * @brief Implementation of SmartEncoder which supports JSON and XML encoding functionalities
  * @author Shunmuga (ssundaramp@outlook.com)
  *
  */

// System headers

// User headers
#include "SmartEncoder.hpp"

using namespace std;

namespace Smart {

// EncoderNumData Class //////////////////////////
EncoderNumData::EncoderNumData(long value)
   : EncoderData(TYPE_NUMBER)
   , m_val(value)
{
}

EncoderNumData::EncoderNumData(const EncoderNumData& o)
   : EncoderData(TYPE_NUMBER)
   , m_val(o.m_val)
{
}

EncoderNumData::~EncoderNumData()
{
}

string EncoderNumData::ToJson() {
   ostringstream s;
   s << m_val;
   return s.str();
}

string EncoderNumData::ToXml() {
   ostringstream s;
   s << m_val;
   return s.str();
}

// EncoderStringData Class //////////////////////////
EncoderStringData::EncoderStringData(const char* value)
   : EncoderData(TYPE_STRING)
   , m_val(value)
{
}

EncoderStringData::EncoderStringData(const EncoderStringData& o)
   : EncoderData(TYPE_STRING)
   , m_val(o.m_val)
{
}

EncoderStringData::~EncoderStringData()
{
}

string EncoderStringData::ToJson() {
   ostringstream s;
   s << "\"" << m_val << "\"";
   return s.str();
}

string EncoderStringData::ToXml() {
   ostringstream s;
   s << m_val;
   return s.str();
}

// EncoderDoubleData Class //////////////////////////
EncoderDoubleData::EncoderDoubleData(double value)
   : EncoderData(TYPE_DOUBLE)
   , m_val(value)
{
}

EncoderDoubleData::EncoderDoubleData(const EncoderDoubleData& o)
   : EncoderData(TYPE_DOUBLE)
   , m_val(o.m_val)
{
}

EncoderDoubleData::~EncoderDoubleData()
{
}

string EncoderDoubleData::ToJson() {
   ostringstream s;
   s << m_val;
   return s.str();
}

string EncoderDoubleData::ToXml() {
   ostringstream s;
   s << m_val;
   return s.str();
}

// EncoderBoolData Class //////////////////////////
EncoderBoolData::EncoderBoolData(bool value)
   : EncoderData(TYPE_BOOL)
   , m_val(value)
{
}

EncoderBoolData::EncoderBoolData(const EncoderBoolData& o)
   : EncoderData(TYPE_BOOL)
   , m_val(o.m_val)
{
}

EncoderBoolData::~EncoderBoolData()
{
}

string EncoderBoolData::ToJson() {
   ostringstream s;
   s << (m_val ? "true" : "false");
   return s.str();
}

string EncoderBoolData::ToXml() {
   ostringstream s;
   s << (m_val ? "true" : "false");
   return s.str();
}

// EncoderBoolData Class //////////////////////////
EncoderNullData::EncoderNullData()
   : EncoderData(TYPE_NULL)
{
}

EncoderNullData::EncoderNullData(const EncoderNullData& o)
   : EncoderData(TYPE_NULL)
{
}

EncoderNullData::~EncoderNullData()
{
}

string EncoderNullData::ToJson() {
   return "null";
}

string EncoderNullData::ToXml() {
   return "";
}

// EncoderObjectData Class //////////////////////////
EncoderObjectData::EncoderObjectData(const EncoderObjectData& o)
   : EncoderData(TYPE_OBJECT)
{
   Init(*o.m_val);
}

EncoderObjectData::EncoderObjectData(Encoder& encoder)
   : EncoderData(TYPE_OBJECT)
{
   Init(encoder);
}

EncoderObjectData::~EncoderObjectData()
{
   if (m_val) {
      delete m_val;
   }
}

void EncoderObjectData::Init(Encoder& encoder)
{
   m_val = new Encoder();
   m_val->m_localKey     = encoder.m_localKey;
   for (uint32_t it = 0; it < encoder.m_db.size(); ++it) {
      vector<EncoderData*> src = encoder.m_db[it].second.second;
      vector<EncoderData*> dst;
      for (uint32_t j = 0; j < src.size(); ++j) {
         EncoderData* d = NULL;
         switch(src[j]->GetType()) {
            case TYPE_NUMBER: d = new EncoderNumData(*(reinterpret_cast<EncoderNumData*>(src[j]))); break;
            case TYPE_STRING: d = new EncoderStringData(*(reinterpret_cast<EncoderStringData*>(src[j]))); break;
            case TYPE_OBJECT: d = new EncoderObjectData(*(reinterpret_cast<EncoderObjectData*>(src[j]))); break;
            case TYPE_DOUBLE: d = new EncoderDoubleData(*(reinterpret_cast<EncoderDoubleData*>(src[j]))); break;
            case TYPE_BOOL: d = new EncoderBoolData(*(reinterpret_cast<EncoderBoolData*>(src[j]))); break;
            case TYPE_NULL: d = new EncoderNullData(*(reinterpret_cast<EncoderNullData*>(src[j]))); break;
         }
         if (d) dst.push_back(d);
      }
      m_val->m_db.push_back(std::make_pair(
                                    encoder.m_db[it].first,
                                    std::make_pair(
                                               std::make_pair(
                                                         encoder.m_db[it].second.first.first,
                                                         encoder.m_db[it].second.first.second),
                                                dst)
                                           )
                            );
   }
}

string EncoderObjectData::ToJson()
{
   return m_val->ToJson();
}

string EncoderObjectData::ToXml()
{
   return m_val->ToXml(true);
}

// Encoder Class //////////////////////////
Encoder::~Encoder()
{
   for (uint32_t it = 0; it < m_db.size(); ++it) {
      vector<EncoderData*> v = m_db[it].second.second;
      for (uint32_t j = 0; j < v.size(); ++j) {
         delete v[j];
      }
   }
   m_db.clear();
}

Encoder& Encoder::operator[](const char* key)
{
   uint32_t it = 0;
   for (; it < m_db.size(); ++it) {
      if (m_db[it].first == key) {
         break;
      }
   }
   if (it == m_db.size()) {
      vector< EncoderData* > v;
      std::map<string,string>     attr;
      string s(key);
      m_db.push_back(std::make_pair(s, std::make_pair(std::make_pair(false,attr),v)));
   }
   m_localKey = key;
   return *this;
}

void Encoder::operator=(const char* value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderStringData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(string value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderStringData(value.c_str());
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(double value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderDoubleData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(long value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderNumData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(unsigned long value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderNumData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(uint32_t value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderNumData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(int32_t value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderNumData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(bool value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderBoolData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::operator=(Encoder& value)
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderObjectData(value);
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::AsNull()
{
   if (m_localKey == "") return;
   EncoderData* j = new EncoderNullData();
   Assign(j);
   m_localKey = "";
   return;
}

void Encoder::AsArray()
{
   if (m_localKey == "") return;
   for (uint32_t it = 0; it < m_db.size(); ++it) {
      if (m_db[it].first == m_localKey) {
         m_db[it].second.first.first = true;
         m_db[it].second.second.clear();
         break;
      }
   }
}

void Encoder::SetAttribute(const char* key, const char* value)
{
   if (m_localKey == "") return;
   for (uint32_t it = 0; it < m_db.size(); ++it) {
      if (m_db[it].first == m_localKey) {
         m_db[it].second.first.second[key] = value;
         break;
      }
   }
}

string Encoder::ToJson()
{
   ostringstream s;
   s << "{";
   for (uint32_t it = 0; it < m_db.size(); ++it) {
      if (it) s << ",";
      string                k = m_db[it].first;
      vector<EncoderData*>  v = m_db[it].second.second;
      s << "\"" << k << "\":";
      if (m_db[it].second.first.first) {
         s << "[";
      }
      for (uint32_t j = 0; j < v.size(); ++j) {
         if (j>0) s << ",";
         s << v[j]->ToJson();
      }
      if (m_db[it].second.first.first) {
         s << "]";
      }
   }
   s << "}";
   return s.str();
}

string Encoder::ToXml(bool shouldbefalse)
{
   ostringstream s;
   if (!shouldbefalse) {
      s << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
      if (m_rootElement.size()) {
         s << "<" << m_rootElement << ">";
      }
   }
   for (uint32_t it = 0; it < m_db.size(); ++it) {
      string                k = m_db[it].first;
      vector<EncoderData*>  v = m_db[it].second.second;
      for (uint32_t j = 0; j < v.size(); ++j) {
         map<string, string>::iterator attr = m_db[it].second.first.second.begin();
         s << "<" << k;
         for (; attr != m_db[it].second.first.second.end(); ++attr) {
            s << " " << attr->first << "=\"" << attr->second << "\"";
         }
         s << ">";
         s << v[j]->ToXml();
         s << "</" << k << ">";
      }
   }
   if (!shouldbefalse) {
      if (m_rootElement.size()) {
         s << "</" << m_rootElement << ">";
      }
   }
   return s.str();
}

void Encoder::Assign(EncoderData* d)
{
   if (d) {
      for (uint32_t it = 0; it < m_db.size(); ++it) {
         if (m_db[it].first == m_localKey) {
            if (!m_db[it].second.first.first) {
               vector< EncoderData* > v = m_db[it].second.second;
               for (uint32_t j = 0; j < v.size(); ++j) {
                  delete v[j];
               }
               m_db[it].second.second.clear();
            }
            m_db[it].second.second.push_back(d);
            break;
         }
      }
   }
}

}; // namespace Smart
