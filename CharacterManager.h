#ifndef _CHARACTERMANAGER_H_
#define _CHARACTERMANAGER_H_

class Character;

class CharacterManager : public Singleton<CharacterManager>
{
public:
	/**
	 * Constructor
	 */
					CharacterManager();
	/**
	 * Destructor
	 */
					~CharacterManager();
	/**
	 * Adds a character to manage
	 */
	void			AddCharacter(
						Character* characterIn
						);
	/**
	 * Returns the number of characters
	 */
	int				GetNumberCharacters() const;
	/**
	 * Get a character by id
	 */
	Character*		GetCharacter(
						const char* CharacterID
						);
	/**
	 * Get a character by index
	 */
	Character*		GetCharacter(
						int CharacterIndex
						);
	/**
	 * Deletes the specified character
	 */
	void			DeleteCharacter(
						Character* haracter
						);
	/**
	 * Renders the characters
	 */
	void			RenderCharacters();
	/**
	 * Updates all the characters
	 */
	void			UpdateCharacters(
						float elapsedTime ///< The amount of time elapsed this frame
						);
	/**
	 * Return an array of characters
	 */
	Character**		GetCharacters(
						int& numCharacters ///< The number of characters
						);
private:
	static const int c_MaxCharacters = 256;
	Character* m_characters[c_MaxCharacters];
	int m_numCharacters;
};

#endif // _CHARACTERMANAGER_H_
