#include "Types.h"

#include "SoundListener.h"
#include "SoundEmitter.h"
#include "SoundManager.h"

/*****************************************************************************************/

DefineSingleton(SoundManager);

/*****************************************************************************************/

SoundManager::SoundManager() : 
	m_directSound(NULL),
	m_numEmitters(0),
	m_numListeners(0)
{
}

/*****************************************************************************************/

SoundManager::~SoundManager()
{	
	for (int index = 0; index < m_numListeners; index ++)
	{
		delete m_listeners[index];
	}
	
	for (int index = 0; index < m_numEmitters; index ++)
	{
		delete m_emitters[index];
	}
	
	if (m_directSound)
	{
		m_directSound->Release();
		m_directSound = 0;
	}
}

/*****************************************************************************************/

HRESULT 
SoundManager::LoadSoundDevice(HWND hWindow, DWORD coopLevel)
{
	//Create Device
	HRESULT hr = DirectSoundCreate(NULL,&m_directSound,NULL);
	if (hr != S_OK)
	{
		assert(false);
	}

	//set sound to DSSCL_PRIORITY
	hr = m_directSound->SetCooperativeLevel(hWindow, coopLevel);
	if (hr != S_OK)
	{
		assert(false);
	}
	

	if(!m_directSound)
	{
		return CO_E_NOTINITIALIZED;
	}

	DSBUFFERDESC dsbdesc;
	//Create and allocate memory to the primary buffer
	ZeroMemory(&dsbdesc, sizeof(DSBUFFERDESC));
	dsbdesc.dwSize        = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags       = DSBCAPS_PRIMARYBUFFER;	
	dsbdesc.dwBufferBytes = 0;
	dsbdesc.lpwfxFormat   = NULL;
	
	
	//create the buffer
	LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;
	hr = m_directSound->CreateSoundBuffer(&dsbdesc,&pDSBPrimary,NULL);
	if (hr != S_OK)
	{
		assert(false);
	}

	WAVEFORMATEX wfx;
	//Set sound quality
	ZeroMemory(&wfx,sizeof(WAVEFORMATEX));
	wfx.wFormatTag = WAVE_FORMAT_PCM;
	wfx.nChannels = 1;
	wfx.nSamplesPerSec = 22050;
	wfx.wBitsPerSample = 16;
	wfx.nBlockAlign     = wfx.wBitsPerSample / 8 * wfx.nChannels;
	wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;

	hr = pDSBPrimary->SetFormat(&wfx);
	if (hr != S_OK)
	{
		assert(false);
	}

	
	if(pDSBPrimary)
	{
		pDSBPrimary->Release();
		pDSBPrimary = NULL;
	}
	
	return S_OK;
}

/*****************************************************************************************/

void 
SoundManager::Update()
{
	for (int i = 0; i < m_numEmitters; i++)
	{
		m_emitters[i]->Update();
	}

	for (int i = 0; i < m_numListeners; i++)
	{
		m_listeners[i]->Update();
	}
}

/*****************************************************************************************/

HRESULT 
SoundManager::CreateListener(LPDIRECTSOUND3DLISTENER* pplistener)
{
	HRESULT hr;

	assert(pplistener);

	if( m_directSound == NULL )
	{
		return CO_E_NOTINITIALIZED;
	}

	DSBUFFERDESC        dsbdesc;
	LPDIRECTSOUNDBUFFER pDSBPrimary = NULL;
	*pplistener = NULL;

	// Obtain primary buffer, asking it for 3D control
	ZeroMemory( &dsbdesc, sizeof(DSBUFFERDESC) );
	dsbdesc.dwSize = sizeof(DSBUFFERDESC);
	dsbdesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	hr = m_directSound->CreateSoundBuffer( &dsbdesc, &pDSBPrimary, NULL );
	if(hr < 0)
	{
		assert(false);
	}

	hr = pDSBPrimary->QueryInterface( IID_IDirectSound3DListener,(VOID**)pplistener );
	if (hr != S_OK)
	{
		assert(false);
	}

	if(pDSBPrimary)
	{
		pDSBPrimary->Release();
		pDSBPrimary = 0;
	}

	return S_OK;
}

/*****************************************************************************************/

void
SoundManager::AddListener(const char* ID)
{
	for (int i = 0; i < m_numListeners; i++)
	{
		if(strcmp(ID,m_listeners[i]->GetID())==0)
		{
			return;
		}
	}

	assert(m_numListeners < c_MaxNumListeners);
	SoundListener* listener = new SoundListener(ID);

	CreateListener(&listener->m_listener);
	listener->InitParams();
	m_listeners[m_numListeners] = listener;
	m_numListeners ++;
}

/*****************************************************************************************/

SoundListener* 
SoundManager::GetListener(const char* listenerID)
{
	for (int i = 0; i < m_numListeners; i++)
	{
		if(strcmp(listenerID ,m_listeners[i]->GetID())==0)
		{	
			return m_listeners[i];
		}
	}

	ErrorMessage("Doesn't exist");
	return 0;
}

/*****************************************************************************************/

void 
SoundManager::AddEmitter(SoundEmitter* newEmitter)
{
	for (int i = 0; i < m_numEmitters; i++)
	{
		if(strcmp(newEmitter->GetName(),m_emitters[i]->GetName())==0)
		{
			//ErrorMessage("Emitter already Exists");
			//No need for error message if emitter exists use it
			return;
		}
	}

	assert(m_numEmitters < c_MaxNumEmitters);

	m_emitters[m_numEmitters] = newEmitter;
	m_numEmitters ++;

}

/*****************************************************************************************/

SoundEmitter* 
SoundManager::GetEmitter(const char* emitterID)
{
	for (int i = 0; i < m_numEmitters; i++)
	{
		if(strcmp(emitterID ,m_emitters[i]->GetName())==0)
		{	
			return m_emitters[i];
		}
	}

	ErrorMessage("Doesn't exist");
	return 0;
}

/*****************************************************************************************/
