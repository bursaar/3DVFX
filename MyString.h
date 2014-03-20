#ifndef _MYSTRING_H_
#define _MYSTRING_H_

#define _CRT_SECURE_NO_WARNINGS

#define MAXSTRINGLENGTH 255

class MyString
{
public:
	/**
	 * Default constructor
	 */
								MyString();
	/**
	 * Constructor from a single letter
	 */
								MyString(
									char letter ///< The letter to store within the string
									);
	/**
	 * Constructor from a const char*
	 */
								MyString(
									const char* str ///< The string to copy 
									);
	/**
	 * Copy constructor
	 */
								MyString(
									const MyString& text ///< The string to copy 
									);
	/**
	 * Destructor
	 */
								~MyString();

	/**
	 * Returns a const char* handle to the string data stored within
	 */
	const char*					GetPointer() const;
	/**
	 * Concatiantes a string onto the end of this string
	 */
	void						Concatenate(
									const char* value ///< The string to append to end the end of our existing data
									);
	/**
	 * Concatiantes a string onto the end of this string
	 */
	void						Concatenate(
									const MyString& value ///< The string to append to end the end of our existing data
									);
	/**
	 * Concatiantes a character onto the end of this string
	 */
	void						Concatenate(
									char value ///< The character to append to end the end of our existing data
									);
	/**
	 * Formats a varg string and stores the result in this string
	 */
	void						Format(
									const char* format,... ///< The varg data to format and store
									);
	/**
	 * Returns the length of the string
	 */
	int							Length() const;
	/**
	 * const char* asignment operator
	 */
	MyString&					operator = (
									const char* value ///< The string to store
									);
	/**
	 * Copy operator
	 */
	MyString&					operator = (
									const MyString& value ///< The string to store
									);
	/**
	 * Conpares this string to the string and passes back if they match
	 */
	bool						operator == (
									const char* value ///< The string to check
									) const;
	/**
	 * Conpares this string to the string and passes back if they match
	 */
	bool						operator == (
									const MyString& value ///< The string to check
									) const;
	/**
	 * Conpares this string to the string and passes back if they dont match
	 */
	bool						operator != (
									const MyString& value ///< The string to check
									) const;
	/**
	 * Conpares this string to the string and passes back if they dont match
	 */
	bool						operator != (
									const char* value ///< The string to check
									) const;

	/**
	 * Array index operator
	 */
	char&						operator [] (
									int index
									);

	/**
	 * const char* operator
	 */
	operator const char*() const;

private:
	char	m_string[MAXSTRINGLENGTH];

};

#endif //_MYSTRING_H_