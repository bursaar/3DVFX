#ifndef _EFFECT_H_
#define _EFFECT_H_

struct EffectHandle
{
	D3DXHANDLE m_handle;
	MyString m_ID;
};

class Effect
{
public:
	Effect(void);
	~Effect(void);
	HRESULT LoadEffect(const char* effectID,const char* fileName);
	void AddEffectHandleTechnique(const char* ID, const char* variableName);
	void AddEffectHandleParameter(const char* ID, const char* variableName,bool isTexture = false);
	
	ID3DXEffect* GetEffect();
	const char* GetEffectID();

	EffectHandle* GetHandle(const char* ID);

	void SetTechnique(const char* handleID);
	void SetMatrix(const char* handleID, Matrix mat);
	void SetInt(const char* handleID, int number);
	void SetFloat(const char* handleID, float flo);
	void SetBool(const char* handleID, bool flag);
	void SetVector2(const char* handleID, Vector2D v);
	void SetVector3(const char* handleID, Vector3D v);
	void SetVector4(const char* handleID, Vector4D v);
	void SetVector4(const char* handleID, Vector3D v, float a);
	void SetColour(const char* handleID, float r, float g, float b, float a);
	void SetTexture(const char* handleID,LPDIRECT3DBASETEXTURE9 tex);
	void SetMatrixArray(const char* handleID,Matrix* theMatrix,unsigned int numberBones);

	void SetActive(bool active);
	bool GetActive();

	bool GetUsesTexture();

private:

	MyString m_effectID;
	MyLinkedList<EffectHandle*> m_handles;
	ID3DXEffect* m_effect;

	bool m_active;
	bool m_usesTexture;

};

#endif // _EFFECT_H_
