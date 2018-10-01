# smart-encoder
It is a stylish interface to making different encoded data from a single object

1. Easy to include anywhere
2. No dependencies
3. Simpler & Modular
4. Enhanced to any new datatype

# Usage
**In Linux**
***To Compile,***

g++ SmartEncoder.cpp -c -o SmartEncoder.o

g++ test.cpp SmartEncoder.o

***To Run,***

./a.out

**In Windows**
***To Compile,***

cl /c /EHsc SmartEncoder.cpp /FoSmartEncoder.o

cl /EHsc test.cpp SmartEncoder.o

***To Run,***

./test.exe

Output:
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