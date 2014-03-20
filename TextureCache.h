#ifndef _TEXTURECACHE_H_
#define _TEXTURECACHE_H_

class TextureCache : public Singleton<TextureCache>
{
public:
	
	/**
	 * Constructor
	 */
						TextureCache();
	/**
	 * Destructor
	 */
						~TextureCache();
	/**
	 * Loads a texture into the texture cache, or returns the existing entry if it exists
	 */
	int					AddTexture(
							const char* ID, 
							const char* fileName, 
							bool rootIncluded = false
							);
	/**
	 * Returns the texure for the specified id
	 */
	IDirect3DTexture9*	GetTexture(
							const char* ID
							) const;
	/**
	 * Returns the texture for the textureCacheId specified
	 */
	IDirect3DTexture9*	GetTexture(
							int textureCacheId
							) const;
private:
	struct TextureEntry 
	{
		TextureEntry() :
			m_texture(0)
		{
		}

		~TextureEntry()
		{
			if (m_texture)
			{
				m_texture->Release();
				m_texture = 0;
			}
		}
		
		MyString			m_ID;
		MyString			m_fileName;
		IDirect3DTexture9*  m_texture;
	};
	
	static const int c_MaxTextures = 256; ///< The maxmimum number of textures that can be loaded in the texture cache

	TextureEntry m_textures[c_MaxTextures]; ///< The list of textures
	int			 m_numTextures; ///< The number of textures currently loaded
};

#endif //_TEXTURECACHE_H_
