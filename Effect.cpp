#include "Types.h"
#include "Effect.h"

Effect::Effect(void)
{
	m_effect = 0;
	m_usesTexture = false;
	m_active = false;
}

Effect::~Effect(void)
{
}

HRESULT
Effect::LoadEffect(const char* effectID,const char* fileName)
{
	m_effectID = effectID;

	ID3DXBuffer* errors =  0;

	HRESULT hr = D3DXCreateEffectFromFile(m_D3DDevice,fileName,0,0,D3DXSHADER_DEBUG,0,&m_effect,&errors);

	if(hr != S_OK || errors)
	{
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);
	}

	return hr;
}

void
Effect::AddEffectHandleTechnique(const char *ID, const char *variableName)
{
	EffectHandle* temp = new EffectHandle;
	m_handles.Insert(temp);
	m_handles.GetLast()->GetData()->m_ID = ID;
	m_handles.GetLast()->GetData()->m_handle = m_effect->GetTechniqueByName(variableName);
}

void
Effect::AddEffectHandleParameter(const char *ID, const char *variableName,bool isTexture)
{
	EffectHandle* temp = new EffectHandle;
	m_handles.Insert(temp);
	m_handles.GetLast()->GetData()->m_ID = ID;
	m_handles.GetLast()->GetData()->m_handle = m_effect->GetParameterByName(0,variableName);

	if(isTexture)
	{
		m_usesTexture = true;
	}
}

ID3DXEffect*
Effect::GetEffect()
{
	return m_effect;
}

const char*
Effect::GetEffectID()
{
	return m_effectID;
}

EffectHandle*
Effect::GetHandle(const char *ID)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,ID) == 0)
		{
			return node->GetData();
		}
		node = node->GetNext();
	}
	return 0;
}

void
Effect::SetTechnique(const char* handleID)
{

	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetTechnique(node->GetData()->m_handle);
			return;
		}
		node = node->GetNext();
	}

	ErrorMessage("error");
}


void
Effect::SetMatrix(const char *handleID, Matrix mat)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetMatrix(node->GetData()->m_handle,&mat);
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetInt(const char *handleID, int number)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetInt(node->GetData()->m_handle,number);
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetFloat(const char* handleID, float flo)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetFloat(node->GetData()->m_handle,flo);
			return;
		}

		node = node->GetNext();
	}
}

void 
Effect::SetBool(const char* handleID, bool flag)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetBool(node->GetData()->m_handle,flag);
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetVector2(const char* handleID, Vector2D v)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetValue(node->GetData()->m_handle,&v,sizeof(Vector2D));
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetVector3(const char* handleID, Vector3D v)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetValue(node->GetData()->m_handle,&v,sizeof(Vector3D));
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetVector4(const char* handleID, Vector4D v)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetValue(node->GetData()->m_handle,&v,sizeof(Vector4D));
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetVector4(const char* handleID, Vector3D v,float a)
{
	Vector4D temp = Vector4D(v.x,v.y,v.z,a);
	SetVector4(handleID,temp);
}

void
Effect::SetColour(const char *handleID, float r, float g, float b, float a)
{
	SetVector4(handleID, Vector4D(r,g,b,a));
}

void
Effect::SetTexture(const char* handleID,LPDIRECT3DBASETEXTURE9 tex)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetTexture(node->GetData()->m_handle,tex);
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetMatrixArray(const char* handleID,Matrix* theMatrix,unsigned int numberBones)
{
	LinkedListNode<EffectHandle*>* node = m_handles.GetFirst();

	while (node)
	{
		if(_stricmp(node->GetData()->m_ID,handleID) == 0)
		{
			m_effect->SetMatrixArray(node->GetData()->m_handle,theMatrix,numberBones);
			return;
		}
		node = node->GetNext();
	}
}

void
Effect::SetActive(bool active)
{
	m_active = active;
}

bool
Effect::GetActive()
{
	return m_active;
}

bool
Effect::GetUsesTexture()
{
	return m_usesTexture;
}






