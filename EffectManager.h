#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_

class Effect;

class EffectManager : public Singleton<EffectManager>
{
	
public:
	/**
	 * Constructor
	 */
							EffectManager();
	/**
	 * Destructor
	 */
							~EffectManager();
	/**
	 * Returns the effect for the specified effect type
	 */
	Effect*					GetEffect(
								const char* effectID
								);
	/**
	 * Sets the base (aka diffuse or colour) texture (aka map) to use on the currently active 
	 * effects
	 */
	void					SetTexture(
								LPDIRECT3DBASETEXTURE9 texture
								);
	/**
	 * Sets the Normal map (aka texture) to use on the currently active effects
	 */
	void					SetNormalMap(
								LPDIRECT3DBASETEXTURE9 texture
								);
private:
	/**
	 * Loads the file which contains the lists the effect files to use, note that this list
	 * must match up with the order of the EffectList enum type
	 */
	void					LoadExternalFile(
								const char* fileName
								);
	/**
	 * Loads the paramter / effect mapping data
	 */
	void					AddEffectFromFile(
								const char* EffectName
								);
	/**
	 * Adds the effect to the list of available effects
	 */
	Effect*					AddEffect(
								const char* effectID,
								const char* fileName
								);
	/**
	 * Adds the effect to the list of available effects
	 */
	void					AddEffect(
								Effect* effect
								);

	Effect* m_effects[20];
	int m_effectCounter;
};

#endif // _EFFECTMANAGER_H_
