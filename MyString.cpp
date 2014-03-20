
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <String.h>
#include <assert.h>
#include "MyString.h"

/*****************************************************************************************/

MyString::MyString()
{
	m_string[0] = '\0';
}

/*****************************************************************************************/

MyString::~MyString()
{
	
}

/*****************************************************************************************/

MyString::MyString(const char* str)
{
	strcpy(m_string, str);
}

/*****************************************************************************************/

//this constructor is used for char to string conversion,
MyString::MyString(char letter)
{
	m_string[0] = letter;
	m_string[1] = '\0';
}

/*****************************************************************************************/

//this constructor is used when another MyString is passed into this string, in result it copies the passed in string
MyString::MyString(const MyString& text)
{
	strcpy(m_string, text.GetPointer()); 
}

/*****************************************************************************************/

//this returns a pointer to the memory address of the string
const char* 
MyString::GetPointer() const
{
	return m_string;
}
 
/*****************************************************************************************/

//this method is used to format a number of times into a string, for example, char's, strings, ints and floats
void 
MyString::Format(const char* format,...)
{
	char temp[256];

	va_list vlist;

	va_start( vlist, format);
	 vsprintf_s( &temp[0], 256, format, vlist );
	va_end( vlist );
	
	strcpy(m_string,temp);
}

/*****************************************************************************************/

//this returns the length of the string
int 
MyString::Length() const
{
	return  strlen(m_string);
}

/*****************************************************************************************/

//this Concatenates a char on the end of the string
void 
MyString::Concatenate(char value)
{
	char* string = m_string;

	while (*string)
	{
		string++;
	}
	
	assert(m_string - string + 1 < MAXSTRINGLENGTH);
	string[0] = value;
	string[1] = '\0';
}

/*****************************************************************************************/

//this method Concatenates a Char* or char array to the end of the string
void 
MyString::Concatenate(const char* value)
{
	assert(strlen(m_string) + strlen(value) < MAXSTRINGLENGTH);
	strcat(m_string,value);
}

/*****************************************************************************************/

//this Concatenates another string to the end of this string
void 
MyString::Concatenate(const MyString& value)
{
	assert(strlen(m_string) + strlen(value) < MAXSTRINGLENGTH);
	strcat(m_string,value.GetPointer());
}

/*****************************************************************************************/

//this operator, equals, sets this string to the value of a char* or char array
MyString&
MyString::operator =(const char *value)
{
	assert(strlen(value) < MAXSTRINGLENGTH);
	strcpy(m_string, value);
	return *this;
}

/*****************************************************************************************/

//this operator, equals, sets this string to the value of another string
MyString&
MyString::operator = (const MyString& value)
{
	assert(strlen(value) < MAXSTRINGLENGTH);
	strcpy(m_string, value.GetPointer());
	return *this;
}

/*****************************************************************************************/

//this operator, equal too, compaires the value of this string to a char* or char array
//it returns true if the two values are the same
bool 
MyString::operator == (const char* value) const
{ 
	if(strcmp(m_string,value) == 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************/

//this operator, equal too, compaires the value of this string to another string
//it returns true if the two values are the same

bool 
MyString::operator == (const MyString& value) const
{ 
	if(strcmp(m_string,value.GetPointer()) == 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************/

//this operator, not equal too, compaires the value of this string to another string
//it returns true if the two values are not the same

bool 
MyString::operator != (const MyString& value) const
{
	if(strcmp(m_string,value.GetPointer()) != 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************/

//this operator,not equal too, compaires the value of this string to a char* or char array
//it returns true if the two values are not the same

bool 
MyString::operator != (const char* value) const
{
	if(strcmp(m_string,value) != 0)
	{
		return true;
	}
	return false;
}

/*****************************************************************************************/

char&
MyString::operator [](int index)
{
	assert(index >= 0 && index < MAXSTRINGLENGTH);
	return m_string[index];
}

/*****************************************************************************************/

MyString::operator const char*() const
{
	return m_string;
}

/*****************************************************************************************/