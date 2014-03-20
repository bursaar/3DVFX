#ifndef _FILEREADER_H_
#define _FILEREADER_H_
#include "MyString.h"
#include <String.h>
#include <stdio.h>
class MyFileReader
{
public:
	/**
	 * Constructor
	 */
				MyFileReader();
	/**
	 * Destructor
	 */
				~MyFileReader();
	/**
	 * Opens the specified file with the corresponding acess type ready for processing
	 */
	void		OpenFile(
					const char* name, ///< The filename to open
					const char* accessType ///< The file access type
					);
	/**
	 * Closes the open file
	 */
	void		CloseFile();

	/**
	 *	Writes a string out to the open file
	 */
	void		Write(
					const char* buffer ///< The string to write to the file
					);
	/**
	 * Writes an integer out to the open file
	 */
	void		Write(
					const int value ///< The integer value to write to the file
					);
	/**
	 * Reads a string from the open file
	 */
	void		Read(
					const char* buffer ///< pointer to the buffer which will recieve the string data
					);
	/**
	 * Reads a integer from the open file
	 */
	void		Read(
					const int &value ///< reference to the integer which will receive the data
					);
	/**
	 * Writes a string buffer to the open file
	 */
	void		WriteBuffer(
					const char* buffer ///< The buffer to write out
					);
	/**
	 * Writes a string buffer to the open file for the specified number of characters
	 */
	void		WriteBuffer(
					const char* buffer, ///< The string buffer to write out
					int count ///< The number of characters to write out
					);
	/**
	 * Returns if a file with the specified filename exists or not
	 */
	bool		Exists(
					const char* name ///< the filename to check for
					);

	/**
	 * Returns the next token in parsing the file
	 */
	const char*	GetNextToken();
	/**
	 * Returns if the last character was a space used for detecting ends of lines so that optional paramaeters can
	 * be used
	 */
	bool		WasLastCharSpace() const;

private:
	/**
	 * Reads the entire file into a new buffer which will then be stored within the class so that the file can be 
	 * tokenised. This memory will be free once the file is closed.
	 */
	void		Preload();

	FILE* m_file;
	
	char* m_cachedFile;
	int	  m_cachedFileOffset;
	int	  m_cachedFileLength;

	MyString m_fileName;
	MyString m_accessType;
};
#endif // _FILEREADER_H_
