#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H
#pragma comment(lib, "dsound.lib")

#include "Mmreg.h"
#include "DSound.h"

class SoundListener;
class SoundEmitter;

class SoundManager : public Singleton<SoundManager> 
{
public:
	/**
	 * Constructor
	 */
					SoundManager();
	/**
	 * Destructor
	 */
					~SoundManager();
	/**
	 * Creates the Direct Sound object for the window
	 */
	HRESULT			LoadSoundDevice(
						HWND hWindow, 
						DWORD coopLevel = DSSCL_PRIORITY
						);
	/**
	 * Returns the Direct Sound object
	 */
	LPDIRECTSOUND&	GetSoundObject(){return m_directSound;}
	/**
	 * Adds an new sound listener
	 */
	void			AddListener(
						const char* ID
						);
	/**
	 * Gets the sound listener with the speicifed id
	 */
	SoundListener*	GetListener(const char* listenerID);
	/**
	 * Creates an new sound emitter
	 */
	void			AddEmitter(
						SoundEmitter* newEmitter
						);
	/**
	 * Gets the sound emitter with the specified id
	 */
	SoundEmitter*	GetEmitter(
						const char* emitterID
						);
	/**
	 * Updates all the emitters and listeners
	 */
	void			Update();
private:
	/**
	 * Creates an new listener object
	 */
	HRESULT			CreateListener(
						LPDIRECTSOUND3DLISTENER* pplistener
						);

	//DirectSound Object
	LPDIRECTSOUND m_directSound;
	static const int c_MaxNumListeners = 8;
	SoundListener* m_listeners[c_MaxNumListeners];
	int m_numListeners;

	static const int c_MaxNumEmitters = 256;
	SoundEmitter* m_emitters[c_MaxNumEmitters];
	int m_numEmitters;
	

};
#endif