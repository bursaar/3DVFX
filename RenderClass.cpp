#include "RenderClass.h"

RenderClass::RenderClass()
{

}

RenderClass::~RenderClass()
{
}

/*
void RenderClass::render_frame()		// renders a single frame
{

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the buffer
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);		// Clear the depth buffer

	d3ddev->BeginScene();

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	// Set up the camera
	mCameraController.FOV = 45;
	mCameraController.SetRenderClass(*this);

	for (
		mMeshManager->myIterator = mMeshManager->RegisteredMeshes.begin();
		mMeshManager->myIterator != mMeshManager->RegisteredMeshes.end();
		mMeshManager->myIterator++
		)
		{
		mMeshManager->iter->mesh->DrawSubset(0);
		}

	mCameraController.SetViewTransform();
	mCameraController.SetProjectionTransform();

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}
*/

/*
void RenderClass::cleanD3D(void)						// closes Direct3D and releases memory
{
	if (v_buffer)
	{
		v_buffer->Release();		 // close and release the vertex buffer
	}   
	if (i_buffer)
	{
		i_buffer->Release();	// close and release the index buffer
	}
	
	mMeshManager->RegisteredMeshes.clear();		// Clear the meshes from the mesh manager.
	
	d3ddev->Release();		// close and release the 3D device
	d3d->Release();			// close and release Direct3D
}
*/

void RenderClass::init_graphics(void)					// 3D declarations
{

		// Create a sphere


	//		D3DXATTRIBUTERANGE sphereAttribs;


		// D3DXCreateSphere(d3ddev, fl_radius, slices, stacks, &sphereMesh, &adjacencyBuffer);

// 		DWORD arraySize = sphereMesh->GetNumFaces() * 3;

	//	DWORD * adaj = new DWORD[arraySize];											// Taken from http://ngemu.com/threads/c-setting-the-size-of-array-during-runtime.42522/
	//	DWORD * optAdaj = new DWORD[arraySize];
	//	DWORD * fRemap = new DWORD[arraySize];
		
	// 	sphereMesh->GenerateAdjacency(0.1f, adaj);

	// 	sphereMesh->OptimizeInplace(
	//		D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_IGNOREVERTS,
	//		adaj,
	//		optAdaj,
	//		fRemap,
	//		&vRemap);

// 		VOID* pVoid;    // a void pointer

	// 	D3DXComputeNormals(sphereMesh, optAdaj);

	// 	sphereMesh->LockVertexBuffer(D3DLOCK_DISCARD, (LPVOID*) &v_buffer);
	//	sphereMesh->GetVertexBuffer(&v_buffer);
		// sphereMesh->LockIndexBuffer(D3DLOCK_DISCARD, (LPVOID*) &i_buffer);
		// sphereMesh->GetIndexBuffer(&i_buffer);

		// d3ddev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//	for (DWORD i = 0; i < sphereMesh->GetNumFaces(); i++)
	//	{
	//		sphereMesh->DrawSubset(0);
	//	}
		
		// memcpy(&pVoid, &v_buffer, sizeof(sphereMesh->GetNumBytesPerVertex()));
	//	sphereMesh->UnlockVertexBuffer();
	//	sphereMesh->UnlockIndexBuffer();
	//	v_buffer->Unlock();
	//	i_buffer->Unlock();

	//	sphereMesh->Release();
}


bool RenderClass::Initialise(HWND phWND)
{
	m_D3D = t2GNew D3DClass;
	m_D3D->Initialise(phWND);

	m_camera = t2GNew MyCameraController;
	m_camera->SetPosition(0.0f, 3.0f, 10.0f);
	m_camera->Render();
	m_camera->GetViewMatrix(m_viewMatrix);

	return true;
}

void RenderClass::CreateCharacter()
{
	// Create the sphere
	float fl_radius = 1.0f;
	int slices = 15;
	int stacks = 15;
	m_adjacencyBuffer = new LPD3DXBUFFER;
	m_vRemap = new LPD3DXBUFFER;
	D3DXCreateSphere(m_D3D->d3ddev, fl_radius, slices, stacks, &m_characterMesh, m_adjacencyBuffer);

	DWORD arraySize = m_characterMesh->GetNumFaces() * 3;

	DWORD * m_adaj = new DWORD[arraySize];	
	DWORD * m_optAdaj = new DWORD[arraySize];
	DWORD * m_fRemap = new DWORD[arraySize];

	m_characterMesh->GenerateAdjacency(0.1f, m_adaj);

	m_characterMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_IGNOREVERTS,
			m_adaj,
			m_optAdaj,
			m_fRemap,
			m_vRemap);
	
	m_player = new CharacterClass;

	m_player->mMyMesh = m_characterMesh;


}

void RenderClass::DrawMesh()
{
	D3DXComputeNormals(m_characterMesh, m_optAdaj);

	// Pass into buffers

	m_player->mMyMesh->DrawSubset(0);

	m_player->mMyMesh->GetVertexBuffer(&m_D3D->v_buffer);
	m_player->mMyMesh->GetIndexBuffer(&m_D3D->i_buffer);

	VOID *pVoid;

	memcpy(&pVoid, &m_D3D->v_buffer, sizeof(m_player->mMyMesh->GetNumBytesPerVertex()));
	v_buffer_index_offset += static_cast<int>(m_player->mMyMesh->GetNumVertices());			// Casting as an int to create an offset for buffering multiple meshes at once.
	m_player->mMyMesh->UnlockVertexBuffer();
	m_player->mMyMesh->UnlockIndexBuffer();
	m_player->mMyMesh->Release();
	m_D3D->v_buffer->Unlock();
	m_D3D->i_buffer->Unlock();   
	m_D3D->i_buffer->Release();
	m_D3D->d3ddev->EndScene();
}