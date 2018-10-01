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

#include <stdio.h>

#include "SmartEncoder.hpp"

static void SimpleEncode()
{
    Smart::Encoder encode;
    encode["name"] = "Shunmuga";
    encode["job"] = "Software Engineer";
    encode["where"] = "Bangalore, India";
    encode["age"] = 31;
    encode["experience"] = 9.2;
    
    printf("\n\n*** %s() ***\n", __FUNCTION__);
    printf("%-10s : %s\n", "In JSON", encode.ToJson().c_str());
    encode.SetRootElement("record");
    printf("%-10s : %s\n", "In XML", encode.ToXml().c_str());
}

static void NestedObject()
{
    Smart::Encoder encode, skills;
    encode["name"] = "Shunmuga";
    encode["job"] = "Software Engineer";
    encode["where"] = "Bangalore, India";
    encode["age"] = 31;
    encode["experience"] = 9.2;
    skills["C++"] = true;
    skills["C"] = true;
    skills["C++11"] = true;
    skills["Java"] = false;
    skills["HTML5"] = true;
    skills["JavaScript"] = true;
    skills["jQuery"] = true;
    encode["skills"] = skills;
    
    printf("\n\n*** %s() ***\n", __FUNCTION__);
    printf("%-10s : %s\n", "In JSON", encode.ToJson().c_str());
    encode.SetRootElement("record");
    printf("%-10s : %s\n", "In XML", encode.ToXml().c_str());
}

static void ArrayObject()
{
    Smart::Encoder encode, skills;
    encode["name"] = "Shunmuga";
    encode["job"] = "Software Engineer";
    encode["where"] = "Bangalore, India";
    encode["age"] = 31;
    encode["experience"] = 9.2;
    encode["skills"].AsArray();
    encode["skills"] = "C++";
    encode["skills"] = "C";
    encode["skills"] = "C++11";
    encode["skills"] = "HTML5";
    encode["skills"] = "JavaScript";
    encode["skills"] = "jQuery";
    
    printf("\n\n*** %s() ***\n", __FUNCTION__);
    printf("%-10s : %s\n", "In JSON", encode.ToJson().c_str());
    encode.SetRootElement("record");
    printf("%-10s : %s\n", "In XML", encode.ToXml().c_str());
}

static void NullObject()
{
    Smart::Encoder encode;
    encode["data"].AsNull();
    
    printf("\n\n*** %s() ***\n", __FUNCTION__);
    printf("%-10s : %s\n", "In JSON", encode.ToJson().c_str());
    encode.SetRootElement("record");
    printf("%-10s : %s\n", "In XML", encode.ToXml().c_str());
}

static void EmptyObject()
{
    Smart::Encoder encode;
    
    printf("\n\n*** %s() ***\n", __FUNCTION__);
    printf("%-10s : %s\n", "In JSON", encode.ToJson().c_str());
    encode.SetRootElement("record");
    printf("%-10s : %s\n", "In XML", encode.ToXml().c_str());
}

int main(int argc, char** argv)
{
    SimpleEncode();

    NestedObject();

    ArrayObject();

    NullObject();

    EmptyObject();

    return 0;
}

