
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <assert.h>
#include "MyFileReader.h"

#define BLANK 10
#define ENDOFLINE 59
#define SPACE 32
#define SEMICOLON 59

/*********************************************************************************/

MyFileReader::MyFileReader() :
	m_file(0),
	m_cachedFile(0),
	m_cachedFileLength(0),
	m_cachedFileOffset(0)
{
}

/*********************************************************************************/

MyFileReader::~MyFileReader()
{
	if (m_file)
	{
		CloseFile();
	}
}

/*********************************************************************************/
//Exists checks to see if a m_file exists within memory,
//it runs an fopen command and checks the result of m_file
//if m_file contains anything, then the command returns true,
//if not then it returns false
bool
MyFileReader::Exists(const char* name)
{
	m_file = fopen(name, "r");

	if (m_file)
	{
		fclose(m_file);
		m_file = NULL;
		return true;
	}
	else
	{
		//create file
		m_file = fopen(name, "w");
		fclose(m_file);
		m_file = NULL;
		return true;

	}
	return false;
}

/*********************************************************************************/

//OpenFile opens a m_file into memory, the accessType passed into the method

void
MyFileReader::OpenFile(const char* name, const char* accessType)
{
	m_fileName = name;
	m_accessType = accessType;
	m_file = fopen(name,accessType);
}

/*********************************************************************************/

//the CloseFile method closes the currently open m_file, 

void
MyFileReader::CloseFile()
{
	if(m_file)
	{
		fclose(m_file);
		m_file = NULL;

		if (m_cachedFile)
		{
			free(m_cachedFile);
			m_cachedFile = 0;
			m_cachedFileLength = 0;
		}

	}
}

/*********************************************************************************/

//this Write command will write a string of character to the text m_file,

void
MyFileReader::Write(const char* buffer)
{
	if(m_file && m_accessType == "w")
	{
		fprintf(m_file,"%s",buffer);
	}
	else
	{
		//m_file does not exist or wrong accessType or HighScores.txt is set to Read-Only
		assert(false);
	}
}

/*********************************************************************************/

//this Write command will write an integer number to the text m_file,

void
MyFileReader::Write(const int buffer)
{
	if(m_file && m_accessType == "w")
	{
		fprintf(m_file,"%i",buffer);
	}
	else
	{
		//m_file does not exist or wrong accessType or HighScores.txt is set to Read-Only
		assert(false);
	}
}

/*********************************************************************************/

//this Read command will read the next string within the within the m_file,
//the result is stored in the memory address of the buffer

void
MyFileReader::Read(const char* buffer)
{
	if(m_file && m_accessType == "r")
	{
		fscanf (m_file, "%s", buffer);
	}
	else
	{
		//m_file does not exist or wrong accessType
		assert(false);
	}
}

/*********************************************************************************/

//this Read command will read the next intager value stored within the text m_file,
//the resuly is stored in the memory address of value

void
MyFileReader::Read(const int &value)
{
	if(m_file && m_accessType == "r")
	{
		fscanf (m_file, "%i", &value);
	}
	else
	{
		//m_file does not exist or wrong accessType
		assert(false);
	}
}

/*********************************************************************************/

void
MyFileReader::WriteBuffer(const char* buffer)
{
	if(m_file && m_accessType == "w")
	{
		fwrite (buffer , 1 , strlen(buffer) , m_file );
	}
}	

/*********************************************************************************/

void
MyFileReader::WriteBuffer(const char* buffer,int count)
{
	if(m_file && m_accessType == "w")
	{
		fwrite (buffer , 1 , count , m_file );
	}
}

/*********************************************************************************/

void
MyFileReader::Preload()
{
	if(m_file && m_accessType == "r")
	{
		fseek(m_file , 0 , SEEK_END);
		m_cachedFileLength = ftell(m_file);
		m_cachedFileOffset = 0;
		rewind (m_file);
		m_cachedFile = (char*)malloc(m_cachedFileLength);
		memset(m_cachedFile, 0, m_cachedFileLength);
		fread (m_cachedFile,1,m_cachedFileLength,m_file);
	}
	else
	{
		m_cachedFileLength = 0;
	}
}

/*********************************************************************************/

const char*
MyFileReader::GetNextToken()
{
	if (!m_cachedFile && m_file)
	{
		Preload();
		m_cachedFileOffset = 0;
	}

	static MyString result;
	result = "";
	
	bool terminate = false;

	while (!terminate && m_cachedFileOffset < m_cachedFileLength)
	{
		char srcChar = m_cachedFile[m_cachedFileOffset];
		
		if(srcChar != BLANK && srcChar != SPACE && srcChar != -51 && srcChar != SEMICOLON)
		{
			result.Concatenate(srcChar);
			m_cachedFileOffset++;
		}
		else
		{
			if(srcChar == BLANK || srcChar == SPACE || srcChar == SEMICOLON)
			{
				if(result.Length() != 0)
				{
					terminate = true;
					m_cachedFileOffset++;
				}
				else
				{
					m_cachedFileOffset++;
				}
			}
			else
			{
				terminate = true;
				m_cachedFileOffset++;
			}
		}
	}

	return result;
}

/*********************************************************************************/

bool		
MyFileReader::WasLastCharSpace() const
{
	if (m_cachedFileOffset)
	{
		return (m_cachedFile[m_cachedFileOffset - 1] == SPACE);
	}

	return false;
}

/*********************************************************************************/
