#include "Types.h"
#include "EntityLoader.h"
#include "MyFileReader.h"
#include "ModelManager.h"
#include "EnvironmentManager.h"
#include "CharacterManager.h"
#include "CollisionMesh.h"
#include "WaypointManager.h"
#include "Character.h"
#include "PropItem.h"
#include "PropManager.h"
#include "SoundManager.h"
#include "SoundEmitter.h"

/************************************************************************/

EntityLoader::EntityLoader()
{
}

/************************************************************************/

EntityLoader::~EntityLoader()
{
}

/************************************************************************/

void
EntityLoader::LoadAssetList(const char* fileName)
{
	MyFileReader reader;

	if(reader.Exists(fileName))
	{
		reader.OpenFile(fileName,"r");
		
		MyString type = reader.GetNextToken();
		MyString Id = reader.GetNextToken();
		MyString filePath = reader.GetNextToken();
		int Scale = atoi(reader.GetNextToken());

		while (type[0] != '\0')
		{
			if(strcmp(type,"CHARACTER")== 0)
			{
				ModelManager::GetInstance()->CreateModel(Id,filePath,(float)Scale);
			}
			else if(strcmp(type,"PROP")== 0)
			{
				ModelManager::GetInstance()->CreateMesh(Id,filePath,(float)Scale);
			}
			else if(strcmp(type,"ENVIRONMENT")== 0)
			{
				EnvironmentManager::GetInstance()->AddModel(Id,filePath);
			}
			else if(strcmp(type,"ENVIRONMENTCOLLISION")== 0)
			{
				EnvironmentManager::GetInstance()->AddCollisionMesh(Id,filePath);
			}

			type = reader.GetNextToken();
			Id = reader.GetNextToken();
			filePath = reader.GetNextToken();
			Scale = atoi(reader.GetNextToken());
		}

		reader.CloseFile();

		if (EnvironmentManager::GetInstance()->GetCollisionMesh())
		{
			EnvironmentManager::GetInstance()->GetCollisionMesh()->CreateSearchTree();
		}
	}
	else
	{
		ErrorMessage("Effect File Could not be found");
	}
}

/************************************************************************/

void
EntityLoader::LoadCharacterList(const char *fileName)
{
	MyFileReader reader;

	if(reader.Exists(fileName))
	{
		reader.OpenFile(fileName,"r");

		MyString modelType = reader.GetNextToken();
		MyString characterID  = reader.GetNextToken();
		int waypointCounter = atoi(reader.GetNextToken());
		MyString waypoint;

		while (modelType[0] != '\0')
		{
			Character* newCharacter = new Character();
			newCharacter->SetID(characterID);
			newCharacter->SetType(modelType);
			SkinnedMesh* model = ModelManager::GetInstance()->GetSkinnedMeshPointer(modelType.GetPointer());
			
			newCharacter->SetMesh(model);
			newCharacter->SetAnimation(0);
			
			for(int i = 0; i < waypointCounter; i++)
			{
				waypoint = reader.GetNextToken();
				
				if (_stricmp(waypoint.GetPointer(),"NONE"))
				{
					newCharacter->AddWayPoint(WaypointManager::GetInstance()->GetWayPoint(waypoint));
				}
			}

			CharacterManager::GetInstance()->AddCharacter(newCharacter);

			modelType = reader.GetNextToken();
			characterID  = reader.GetNextToken();
			waypointCounter = atoi(reader.GetNextToken());
		}
		
		reader.CloseFile();
	}
	else
	{
		ErrorMessage("Effect File Could not be found");
	}
}

/************************************************************************/

void 
EntityLoader::LoadPropList(const char* fileName)
{
	MyFileReader reader;

	if(reader.Exists(fileName))
	{
		reader.OpenFile(fileName,"r");
		
		MyString type = reader.GetNextToken();
		MyString uniqueID = reader.GetNextToken();
		float secs = (float)atof(reader.GetNextToken());
		float x = (float)atof(reader.GetNextToken());
		float y = (float)atof(reader.GetNextToken());
		float z = (float)atof(reader.GetNextToken());

		while (type[0] != '\0')
		{
			PropItem* p = new PropItem();
			p->SetType(type);
			p->SetID(uniqueID);
			p->SetPosition(Vector3D(x, y, z));

			if(secs > 0)
			{
				p->SetRespawn(true);
				p->SetRespawnTime((float)secs);
			}
			else
			{
				p->SetRespawn(false);
			}
			
			p->SetMesh(ModelManager::GetInstance()->GetStaticMeshPointer(type));

			p->GenerateRadius();
			
			if(strlen(p->GetID()) > 0)
			{
				p->SetBakedIntoWorld(false);
				PropManager::GetInstance()->AddProp(p);
			}
			else
			{
				delete p;
			}

			type = reader.GetNextToken();
			uniqueID = reader.GetNextToken();
			secs = (float)atof(reader.GetNextToken());
			x = (float)atof(reader.GetNextToken());
			y = (float)atof(reader.GetNextToken());
			z = (float)atof(reader.GetNextToken());
		}

		reader.CloseFile();

		EnvironmentManager::GetInstance()->GetCollisionMesh()->CreateSearchTree();
	}
	else
	{
		ErrorMessage("PropItem File Could not be found");
	}
}

/************************************************************************/

void 
EntityLoader::LoadSounds(const char* fileName)
{
	MyFileReader reader;

	if(reader.Exists(fileName))
	{
		reader.OpenFile(fileName,"r");

		MyString uniqueID = reader.GetNextToken();
		MyString filename = reader.GetNextToken();

		while (uniqueID[0] != '\0')
		{
			SoundEmitter* se = new SoundEmitter(uniqueID,filename,DS3DALG_NO_VIRTUALIZATION);
			SoundManager::GetInstance()->AddEmitter(se);
			SoundManager::GetInstance()->GetEmitter(uniqueID)->SetPosition(Vector3D(1,0,0));

			uniqueID = reader.GetNextToken();
			filename = reader.GetNextToken();
		}

		reader.CloseFile();
	}
	else
	{
		ErrorMessage("Sounds File Couldn't Be found");
	}

}

/************************************************************************/
