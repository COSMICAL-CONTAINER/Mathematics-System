#ifndef _My_String_H
#define _My_String_H

typedef char* String;

String String_Init(const char* str);
String String_AddChar(String str, char c);
String String_Addxchar_temp(String str, size_t times, char c);

#endif //_My_String_H
