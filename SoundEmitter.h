#ifndef _SOUNDEMITTER_H
#define _SOUNDEMITTER_H

class SoundWaveFile;

class SoundEmitter
{
public:
	/**
	 * Constructor
	 */
							SoundEmitter(
								const char* name, ///< Emitter name
								const char* fileName, ///< sound filename
								GUID algorithm, ///< DS process algorithm
								DWORD processMode = DS3DMODE_NORMAL ///< DS 3D Processing Mode
								);
	/**
	 * Destructor
	 */
							~SoundEmitter();
	/**
	 * Creates the sound buffer to play
	 */
	bool					CreateSoundBuffer();
	/**
	 * Playes the sound, looped if the flag is set
	 */
	void					Play(
								bool loop = false
								);
	/**
	 * Stops the sound
	 */
	void					Stop();
	/**
	 * Updates the playback of the sound
	 */
	void					Update();
	/**
	 * Fills the sound buffer from the source wav reader.
	 */
	void					FillSharedBuffer(
								SoundWaveFile& loader
								);
	/**
	 * Returns if the sound is still playing
	 */
	bool					IsPlaying() const;
	/**
	 * Returns the sound emitter name
	 */
	const char*				GetName() const;
	/**
	 * Returns the sound filename
	 */
	const char*				GetFileName() const;
	/**
	 * Returns the sound buffer
	 */
	LPDIRECTSOUNDBUFFER&	GetBuffer(){return m_sharedBuffer;}
	/**
	 * Returns the sounds position
	 */
	Vector3D				GetPosition()const;
	/**
	 * Returns the sounds verlocity
	 */
	Vector3D				GetVelocity()const;
	/**
	 * Sets the sounds volume
	 */
	void					SetVolume(
								int volume
								);
	/**
	 * Sets the sounds position
	 */
	void					SetPosition(
								const Vector3D& pos, 
								bool defer = false
								);
	/**
	 * Sets the sounds velocity
	 */
	void					SetVelocity(
								const Vector3D& vel, 
								bool defer = false
								);
protected:
	MyString				m_name;
	MyString				m_fileName;
	
	
	LPDIRECTSOUNDBUFFER     m_sharedBuffer;
	LPDIRECTSOUNDBUFFER	    m_soundBuffer;
	LPDIRECTSOUND3DBUFFER   m_3DBuffer;
	DS3DBUFFER              m_bufferParams;


	int						m_bufferSize;
	int						m_volume;
	bool					m_isPlaying;
	
};


#endif