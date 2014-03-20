#include "Types.h"
#include "Effect.h"
#include "EffectManager.h"
#include "MyFileReader.h"

/*****************************************************************************************/

DefineSingleton(EffectManager);

/*****************************************************************************************/

const char* TEXTURENAME = "m_Texture";

/*****************************************************************************************/

EffectManager::EffectManager()
{
	m_effectCounter = 0;
	LoadExternalFile("effects.txt");
}

/*****************************************************************************************/

EffectManager::~EffectManager()
{
	for (int i = 0; i < m_effectCounter; i++)
	{
		delete m_effects[i];
	}
}

/*****************************************************************************************/

Effect*
EffectManager::AddEffect(const char* effectID,const char* fileName)
{
	assert(m_effectCounter < 20);
	m_effects[m_effectCounter] = new Effect();
	m_effects[m_effectCounter]->LoadEffect(effectID,fileName);
	m_effectCounter ++;
	return m_effects[m_effectCounter - 1];
}

/*****************************************************************************************/

void
EffectManager::AddEffect(Effect* effect)
{
	assert(m_effectCounter < 20);
	m_effects[m_effectCounter] = effect;
	m_effectCounter ++;
}

/*****************************************************************************************/

Effect*
EffectManager::GetEffect(const char* effectID)
{
	for(int i = 0; i < m_effectCounter; i++)
	{
		if(_stricmp(m_effects[i]->GetEffectID(), effectID) == 0)
		{
			return m_effects[i];
		}
	}

	return 0;
}

/*****************************************************************************************/

void
EffectManager::SetTexture(LPDIRECT3DBASETEXTURE9 texture)
{
	for(int i = 0; i < m_effectCounter; i++)
	{
		if(m_effects[i]->GetActive() && m_effects[i]->GetUsesTexture())
		{
			m_effects[i]->SetTexture("m_Texture",texture);
			m_effects[i]->GetEffect()->CommitChanges();
		}
	}

}

/*****************************************************************************************/

void
EffectManager::SetNormalMap(LPDIRECT3DBASETEXTURE9 texture)
{
	for(int i = 0; i < m_effectCounter; i++)
	{
		if(m_effects[i]->GetActive() && m_effects[i]->GetUsesTexture())
		{
			m_effects[i]->SetTexture("m_NormalTexture",texture);
			m_effects[i]->GetEffect()->CommitChanges();
		}
	}
}
/*****************************************************************************************/

void
EffectManager::LoadExternalFile(const char* fileName)
{
	MyFileReader reader;
	
	MyString fullPath;

	if(reader.Exists(fileName))
	{
		reader.OpenFile(fileName,"r");
		
		const char* file = reader.GetNextToken();

		while (file[0] != '\0')
		{
			fullPath.Format("%s",file);
			AddEffectFromFile(fullPath);
			
			file = reader.GetNextToken();
		}

		reader.CloseFile();
	}
	else
	{
		ErrorMessage("Effect File Could not be found");
	}
}

/*****************************************************************************************/

//////////////////////////////////////////////////////////////////////////
//AddEffectFromFile opens and reads effects text files into memory, the output of
//reading the file will be the effect itself and all the handles it uses.
//////////////////////////////////////////////////////////////////////////
void
EffectManager::AddEffectFromFile(const char* EffectName)
{
	MyFileReader reader;

	if(reader.Exists(EffectName))
	{
		reader.OpenFile(EffectName,"r");

		MyString effectID = reader.GetNextToken();
		MyString fileName = reader.GetNextToken();
		MyString fullPath;
		fullPath.Format("%s",fileName.GetPointer());
		
		Effect* newEffect = AddEffect(effectID,fullPath);
		
		MyString techniqueName = reader.GetNextToken();
		MyString techniqueVariable = reader.GetNextToken();

		newEffect->AddEffectHandleTechnique(techniqueName,techniqueVariable);

		MyString name = reader.GetNextToken();
		MyString variable = reader.GetNextToken();

		while (name[0] != '\0')
		{
			if(strncmp(name,"mTech",5) == 0)
			{
				newEffect->AddEffectHandleTechnique(name,variable);
			}
			else if(strcmp(name,TEXTURENAME) == 0)
			{
				newEffect->AddEffectHandleParameter(name,variable,true);
			}
			else
			{
				newEffect->AddEffectHandleParameter(name,variable);
			}

			name = reader.GetNextToken();
			variable = reader.GetNextToken();
		}

		reader.CloseFile();
	}
	else
	{
		ErrorMessage("Effect Information Does not exist");
	}
}

/*****************************************************************************************/


