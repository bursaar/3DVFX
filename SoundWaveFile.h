#ifndef _SOUNDWAVEFILE_H_
#define _SOUNDWAVEFILE_H_
#include <windows.h>

//////////////////////////////////////////////
//SoundWaveFile is used to load data from a sound wave (.wav)
//then store the data waves read from it into memory.
//
//Don't worry to much about understanding all the code, as its fairly advanced,
//One thing to remember however is that code like this doesn't really change from
//project to project.
//////////////////////////////////////////////

class SoundWaveFile
{
public:
	/**
	 * Constrcutor
	 */
						SoundWaveFile(
							const char* fileName
							);
	/**
	 * Destructor
	 */
						~SoundWaveFile();
	/**
	 * Returns if the file is valid
	 */
	bool				isVaild() const;
	/**
	 * Reads in data from the file
	 */
	bool				Read(
							int size,
							BYTE* data,
							UINT* sizeRead
							);
	/**
	 * Closes the file
	 */
	void				Close();
	/**
	 * Resets the file back to the start
	 */
	bool				Reset();
	/**
	 * Returns the wave format information
	 */
	void*				GetWaveFormat();
	/**
	 * Returns the Wave Riff chunk
	 */
	void*				GetWaveRiffChunk();
	/**
	 * Returns the Wave Info
	 */
	void*				GetWaveInfo();
private:
	bool m_valid;
	void* m_waveFormat;
	void* m_mmIOHandle;
	int	 m_ckIn[5];
	int m_ckInRiff[5];
};
#endif //_SOUNDWAVEFILE_H_
