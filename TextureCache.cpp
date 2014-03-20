#include "Types.h"
#include "MyFileReader.h"
#include "TextureCache.h"
#include "Program.h"

/*********************************************************************************************************************************/

DefineSingleton(TextureCache);

/*********************************************************************************************************************************/

TextureCache::TextureCache() :
	m_numTextures(0)
{
	AddTexture("ALPHA","ALPHA.tga");
}

/*********************************************************************************************************************************/

TextureCache::~TextureCache()
{
	/// Note Texture cleanup is handled by the entry destructor
}

/*********************************************************************************************************************************/

int 
TextureCache::AddTexture(const char* ID, const char* fileName, bool rootIncluded)
{
	//Check to see if the texture already exists, if so, return the index
	//number to use
	for (int index = 0; index < m_numTextures; index++)
	{
		if(_stricmp(m_textures[index].m_ID, ID) == 0)
		{
			return index;
		}
	}

	//else load the texture
	MyString tempString;
	
	if(!rootIncluded)
	{
		MyString directory;

		GetCurrentDirectoryA(256, &directory[0]);
		
		tempString.Format("%s%s%s", directory.GetPointer(), ASSETPARTICALSTEXTUREPATH, fileName);
	}
	else
	{
		tempString = fileName;
	}

	IDirect3DTexture9* tex = 0;
	HRESULT hr = D3DXCreateTextureFromFile(m_D3DDevice,tempString,&tex);

	if(hr != S_OK)
	{
		return -1;
	}

	assert(m_numTextures < c_MaxTextures);

	m_textures[m_numTextures].m_fileName = fileName;
	m_textures[m_numTextures].m_ID = ID;
	m_textures[m_numTextures].m_texture = tex;
	m_numTextures ++;
	return m_numTextures - 1;
}

/*********************************************************************************************************************************/

IDirect3DTexture9*
TextureCache::GetTexture(const char* ID) const
{
	for (int index = 0; index < m_numTextures; index++)
	{
		if(_stricmp(m_textures[index].m_ID, ID) == 0)
		{
			return m_textures[index].m_texture;
		}
	}

	return 0;
}

/*********************************************************************************************************************************/

IDirect3DTexture9*
TextureCache::GetTexture(int textureCacheId) const
{
	if (textureCacheId == -1)
	{
		return 0;
	}
	
	if(textureCacheId < m_numTextures)
	{
		return m_textures[textureCacheId].m_texture;
	}

	return 0;
}


/*********************************************************************************************************************************/