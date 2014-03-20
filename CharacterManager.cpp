#include "Types.h"
#include "Character.h"
#include "CharacterManager.h"
#include "ModelManager.h"

/************************************************************************/

DefineSingleton(CharacterManager);

/************************************************************************/

CharacterManager::CharacterManager() :
	m_numCharacters(0)
{
}

/************************************************************************/

CharacterManager::~CharacterManager()
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		delete m_characters[index];
	}
}

/************************************************************************/

void
CharacterManager::AddCharacter(Character* characterIn)
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		if(strcmp(characterIn->GetID(),m_characters[index]->GetID())==0)
		{
			ErrorMessage("Character already Exists");
		}
	}

	assert(m_numCharacters < c_MaxCharacters);
	m_characters[m_numCharacters] = characterIn;
	m_numCharacters ++;
}

/************************************************************************/

void
CharacterManager::DeleteCharacter(Character* character)
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		if (m_characters[index] == character)
		{
			m_characters[index] = m_characters[m_numCharacters - 1];
			m_numCharacters --;
			break;
		}
	}

	delete character;
}

/************************************************************************/

Character*
CharacterManager::GetCharacter(const char* CharacterID)
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		if(strcmp(CharacterID, m_characters[index]->GetID())==0)
		{	
			return m_characters[index];
		}
	}

	return 0;
}

/************************************************************************/

Character*
CharacterManager::GetCharacter(int CharacterIndex)
{
	if(CharacterIndex < m_numCharacters)
	{
		return m_characters[CharacterIndex];
	}
	ErrorMessage("Doesn't exist");
	return 0;
}

/************************************************************************/

void
CharacterManager::RenderCharacters()
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		m_characters[index]->Render();
	}
}

/************************************************************************/

void 
CharacterManager::UpdateCharacters(float elapsedTime)
{
	for (int index = 0; index < m_numCharacters; index ++)
	{
		m_characters[index]->Update(elapsedTime);
	}
}

/************************************************************************/

int
CharacterManager::GetNumberCharacters() const
{
	return m_numCharacters;
}

/************************************************************************/

Character**		
CharacterManager::GetCharacters(int& numCharacters)
{
	numCharacters = m_numCharacters;
	return m_characters;
}

/************************************************************************/