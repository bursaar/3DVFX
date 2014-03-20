#ifndef _ENTITYLOADER_H_
#define _ENTITYLOADER_H_


class EntityLoader
{
public:
	EntityLoader(void);
	~EntityLoader(void);

	void LoadAssetList(const char* fileName);
	void LoadCharacterList(const char* fileName);
    void LoadPropList(const char* fileName);
	void LoadSounds(const char* fileName);
};

#endif