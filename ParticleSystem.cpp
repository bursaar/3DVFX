#include "Types.h"
#include "ParticleEmitter.h"
#include "ParticleSystem.h"

/*************************************************************************************************************************************************/

DefineSingleton(ParticleSystem);

/*************************************************************************************************************************************************/

IDirect3DVertexDeclaration9* Particle::Decl  = 0;

/*************************************************************************************************************************************************/

ParticleSystem::ParticleSystem()
{
	D3DVERTEXELEMENT9 ParticleElements[] = 
	{
		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0, 24, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
		{0, 28, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
		{0, 32, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},
		{0, 36, D3DDECLTYPE_FLOAT1, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4},
		{0, 40, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		D3DDECL_END()
	};	
	m_D3DDevice->CreateVertexDeclaration(ParticleElements, &Particle::Decl);
}

/*************************************************************************************************************************************************/

ParticleSystem::~ParticleSystem()
{
	Particle::Decl->Release();
	
	LinkedListNode<ParticleEmitter*>* node = m_emitters.GetFirst();

	while (node)
	{
		delete node->GetData();
		node = node->GetNext();
	}
	
	m_emitters.Clear();
}

/*************************************************************************************************************************************************/

void
ParticleSystem::AddEmitter(ParticleEmitter *e)
{
	m_emitters.Insert(e);
}

/*************************************************************************************************************************************************/

ParticleEmitter*
ParticleSystem::GetEmitter(const char *ID)
{
	LinkedListNode<ParticleEmitter*>* node = m_emitters.GetFirst();

	while (node)
	{
		if(strcmp(node->GetData()->GetID(),ID) ==0)
		{
			return node->GetData();
		}
		node = node->GetNext();
	}
	return 0;
}

/*************************************************************************************************************************************************/

void
ParticleSystem::Update(float elapsedTime)
{
	LinkedListNode<ParticleEmitter*>* node = m_emitters.GetFirst();

	while(node)
	{
		node->GetData()->Update(elapsedTime);
		
		if(node->GetData()->IsAllDead())
		{
			LinkedListNode<ParticleEmitter*>* toRemove = node;
			delete node->GetData();
			node = node->GetNext();
			m_emitters.Remove(toRemove);
		}
		else
		{
			node = node->GetNext();
		}
	}
	
}

/*************************************************************************************************************************************************/

void
ParticleSystem::Render()
{
	LinkedListNode<ParticleEmitter*>* node = m_emitters.GetFirst();

	while (node)
	{
		node->GetData()->Render();
		node = node->GetNext();
	}
}

/*************************************************************************************************************************************************/
