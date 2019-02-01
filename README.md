
                   AKKU::Smart::Encoder, Release 2.0.0

This is AKKU::Smart::Encoder, a C++ library for do the encoding(either 
XML or JSON) written by Shunmuga Sundaram.  It is
a independent source which should not having any other thirdparty
software references

Currently it is having a support to compile with GCC Compiler.
Hopefully it will come for other compilers too.

AKKU Parser is free software.  You may copy, distribute, and modify
it under the terms of the License contained in the file COPYING
distributed with this package.  This license is the same as the
Apache Consortium license.


# AKKU::Smart::Encoder
Light weight module to do the encoding in either Xml or Json from single object

1. Easy to include anywhere
2. No dependencies
3. Simpler & Modular
4. Enhanced to any new datatype

# Usage
## In Linux

### To Compile

./linbuild.sh

### To Run

./objs/usage.exe

## In Windows
### To Compile

winbuild.bat

### To Run

objs\usage.exe

# Output
```
*** SimpleEncode() ***
In JSON    : {"name":"Shunmuga","job":"Software Engineer","where":"Bangalore, India","age":31,"experience":9.2}
In XML     : <?xml version="1.0" encoding="UTF-8"?><record><name>Shunmuga</name><job>Software Engineer</job><where>Bangalore, India</where><age>31</age><experience>9.2</experience></record>


*** NestedObject() ***
In JSON    : {"name":"Shunmuga","job":"Software Engineer","where":"Bangalore, India","age":31,"experience":9.2,"skills":{"C++":true,"C":true,"C++11":true,"Java":false,"HTML5":true,"JavaScript":true,"jQuery":true}}
In XML     : <?xml version="1.0" encoding="UTF-8"?><record><name>Shunmuga</name><job>Software Engineer</job><where>Bangalore, India</where><age>31</age><experience>9.2</experience><skills><C++>true</C++><C>true</C><C++11>true</C++11><Java>false</Java><HTML5>true</HTML5><JavaScript>true</JavaScript><jQuery>true</jQuery></skills></record>


*** ArrayObject() ***
In JSON    : {"name":"Shunmuga","job":"Software Engineer","where":"Bangalore, India","age":31,"experience":9.2,"skills":["C++","C","C++11","HTML5","JavaScript","jQuery"]}
In XML     : <?xml version="1.0" encoding="UTF-8"?><record><name>Shunmuga</name><job>Software Engineer</job><where>Bangalore, India</where><age>31</age><experience>9.2</experience><skills>C++</skills><skills>C</skills><skills>C++11</skills><skills>HTML5</skills><skills>JavaScript</skills><skills>jQuery</skills></record>


*** NullObject() ***
In JSON    : {"data":null}
In XML     : <?xml version="1.0" encoding="UTF-8"?><record><data></data></record>


*** EmptyObject() ***
In JSON    : {}
In XML     : <?xml version="1.0" encoding="UTF-8"?><record></record>
```