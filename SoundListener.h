#ifndef _SOUNDLISTENER_H
#define _SOUNDLISTENER_H

#include "DSound.h"

class SoundListener
{
public:
	/**
	 * Constrcutor
	 */
					SoundListener(
						const char* ID
						);
	/**
	 * Destructor
	 */
					~SoundListener();
	/**
	 * Returns the ID of the listener
	 */
	const char*		GetID() const {return m_ID;}
	/**
	 * Initialises the parameters from the DS listener
	 */
	void			InitParams();
	/**
	 * Returns the position of the listener
	 */
	Vector3D		GetPosition() const;
	/**
	 * Returns the velocity of the listener
	 */
	Vector3D		GetVelocity() const;
	/**
	 * Returns the forward vector of the listener
	 */
	Vector3D		GetForward() const;
	/**
	 * Sets the position of the listener
	 */
	void			SetPosition(
						const Vector3D& pos, 
						bool defer = false
						);
	/**
	 * Sets the velocity of the listener
	 */
	void			SetVelocity(
						const Vector3D& vel, 
						bool defer = false
						);
	/**
	 * Sets the forward vector of the listener
	 */
	void			SetForward(
						const Vector3D& fwd, 
						bool defer = false
						);
	/**
	 * Updates the listener
	 */
	void			Update();

	/**
	 * Sets up the listener params
	 */
	void			SetParams(
						float distance, 
						float doppler, 
						float rollOff, 
						bool defer = false
						);
private:
	friend class SoundManager;

	MyString m_ID;

	LPDIRECTSOUND3DLISTENER  m_listener;
	DS3DLISTENER             m_listenerParameters; 
};

#endif
