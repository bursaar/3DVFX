#include "Types.h"
#include "dsound.h"
#include "SoundWaveFile.h"
#include "SoundManager.h"
#include "SoundEmitter.h"

/*****************************************************************************************/

SoundEmitter::SoundEmitter(const char* name, const char* fileName, GUID algorithm, DWORD processMode) : 
	m_isPlaying(false),
	m_volume(100),
	m_sharedBuffer(0),
	m_3DBuffer(NULL),
	m_soundBuffer(0),
	m_name(name),
	m_fileName(fileName)
{
	SoundWaveFile soundWave(fileName);

	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd,sizeof(DSBUFFERDESC));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_CTRL3D;
	dsbd.dwBufferBytes = ((MMCKINFO*)soundWave.GetWaveRiffChunk())->cksize;
	dsbd.guid3DAlgorithm = algorithm;
	dsbd.lpwfxFormat   = (WAVEFORMATEX*)soundWave.GetWaveFormat();

	HRESULT hr = SoundManager::GetInstance()->GetSoundObject()->CreateSoundBuffer(&dsbd,&m_sharedBuffer,NULL);

	if(FAILED(hr))
	{
		return;
	}

	m_bufferParams.dwSize = sizeof(DS3DBUFFER);
	m_bufferSize = dsbd.dwBufferBytes;
	FillSharedBuffer (soundWave);

	hr = m_sharedBuffer->QueryInterface( IID_IDirectSound3DBuffer, (VOID**)&m_3DBuffer );
	
	m_3DBuffer->GetAllParameters( &m_bufferParams );

	// Set new 3D buffer parameters
	m_bufferParams.dwMode = processMode;
	
	m_3DBuffer->SetAllParameters( &m_bufferParams, DS3D_IMMEDIATE );
}

/*****************************************************************************************/

SoundEmitter::~SoundEmitter()
{
	Stop();

	if(m_3DBuffer)
	{
		m_3DBuffer->Release();
		m_3DBuffer = NULL;
	}

	if(m_soundBuffer)
	{
		m_soundBuffer->Release();
		m_soundBuffer = 0;
	}

	if(m_sharedBuffer)
	{
		m_sharedBuffer->Release();
		m_sharedBuffer = NULL;
	}
}


/*****************************************************************************************/

bool
SoundEmitter::CreateSoundBuffer()
{
	LPDIRECTSOUND dsound = SoundManager::GetInstance()->GetSoundObject();

	HRESULT hr = dsound->DuplicateSoundBuffer(m_sharedBuffer,&m_soundBuffer);

	if(hr == DS_OK)
	{
		hr = m_soundBuffer->QueryInterface( IID_IDirectSound3DBuffer, (VOID**)&m_3DBuffer );
		m_3DBuffer->SetAllParameters( &m_bufferParams, DS3D_IMMEDIATE );
		
		return true;
	}

	return false;
}

/*****************************************************************************************/

void
SoundEmitter::Play(bool loop)
{
	if(!m_soundBuffer)
	{
		if(!CreateSoundBuffer())
		{
			return;
		}
	}

	HRESULT hr;			
	
	if(loop)
	{
		hr = m_soundBuffer->Play( 0, 0, DSBPLAY_LOOPING );
	}
	else
	{
		hr = m_soundBuffer->Play( 0, 0, 0 );
	}

	if(hr != S_OK)
	{
		return;
	}

	m_isPlaying = true;
}

/*****************************************************************************************/

void
SoundEmitter::SetVolume(int volume)
{
	m_volume = volume;

	if(m_soundBuffer)
	{
		m_soundBuffer->SetVolume((volume*100)-10000);
		m_soundBuffer->SetPan(100*100);
	}		
}
/*****************************************************************************************/

void
SoundEmitter::Stop()
{
	if(m_soundBuffer)
	{
		m_soundBuffer->Stop();
		m_soundBuffer->Release();
		m_soundBuffer = 0;
	}

	m_isPlaying = false;
}
/*****************************************************************************************/

void
SoundEmitter::Update()
{
	
	if(m_soundBuffer)
	{

		DWORD status = 0;
		m_soundBuffer->GetStatus(&status);

		bool playing  =(( status & DSBSTATUS_PLAYING) != 0);
		
		if(m_isPlaying && !playing)
		{
			Stop();
		}
	}
}
/*****************************************************************************************/

bool
SoundEmitter::IsPlaying() const
{
	return m_isPlaying;
}

/*****************************************************************************************/
////////////////////////////////////////
//This method fills the sound buffer with the sound stream,
//the buffer it creates is played though direct sounds
/////////////////////////////////////////
void
SoundEmitter::FillSharedBuffer(SoundWaveFile& loader)
{
	HRESULT hr;
	BYTE*   pbWavData; 
	UINT    cbWavSize; 
	VOID*   pbData  = NULL;
	VOID*   pbData2 = NULL;
	DWORD   dwLength;
	DWORD   dwLength2;

	//creates the buffer the the right size.
	INT nWaveFileSize = ((MMCKINFO*)loader.GetWaveRiffChunk())->cksize;

	pbWavData = new BYTE[nWaveFileSize];

	if(FAILED(loader.Read(nWaveFileSize,pbWavData,&cbWavSize)))
	{
		return;
	}

	loader.Reset();

	//locks the buffer for writing
	if(FAILED(hr = m_sharedBuffer->Lock( 0, m_bufferSize, &pbData, &dwLength, &pbData2, &dwLength2, 0L )))
	{
		return;
	}

	//Ensure that the end of the sound is not empty
	memcpy( pbData, pbWavData, m_bufferSize - 50 );

	m_sharedBuffer->Unlock( pbData, m_bufferSize, NULL, 0 );

	pbData = NULL;

	delete pbWavData;
}

/*****************************************************************************************/

const char*
SoundEmitter::GetFileName() const
{
	return m_fileName;
}

/*****************************************************************************************/

const char*
SoundEmitter::GetName() const
{
	return m_name;
}

/*****************************************************************************************/

Vector3D 
SoundEmitter::GetPosition() const
{
	Vector3D pos;
	m_3DBuffer->GetPosition(&pos);
	return pos;
}

/*****************************************************************************************/

Vector3D 
SoundEmitter::GetVelocity() const
{
	Vector3D vel;
	m_3DBuffer->GetPosition(&vel);
	return vel;
}

/*****************************************************************************************/

void 
SoundEmitter::SetPosition(const Vector3D &pos, bool defer /* = false */)
{
	
	if( m_3DBuffer )
	{
		m_bufferParams.vPosition = pos;

		if(!defer)
		{
			m_3DBuffer->SetPosition(pos.x,pos.y,pos.z,DS3D_IMMEDIATE);
			//m_sharedBuffer->SetPosition(pos.x,pos.y,pos.z,DS3D_IMMEDIATE);
		}
		else
		{
			m_3DBuffer->SetPosition(pos.x,pos.y,pos.z,DS3D_DEFERRED);
		}
	}
}

/*****************************************************************************************/

void 
SoundEmitter::SetVelocity(const Vector3D &vel, bool defer /* = false */)
{
	if( m_3DBuffer )
	{
		m_bufferParams.vVelocity = vel;
		
		if(!defer)
		{
			m_3DBuffer->SetVelocity(vel.x,vel.y,vel.z,DS3D_IMMEDIATE);
		}
		else
		{
			m_3DBuffer->SetVelocity(vel.x,vel.y,vel.z,DS3D_DEFERRED);
		}
	}
}

/*****************************************************************************************/