#ifndef _MESHHIERARCHY_H_
#define _MESHHIERARCHY_H_

/**
 * This is a collection of classes and structs which handle the loading of x files
 * MeshContainer - stores the mesh & material information
 * Frame - Stores a frame/bone within the model structure
 * MeshHierarchy - Handles the creation & destruction of the models meshes / bones
 */

struct MeshContainer : public D3DXMESHCONTAINER
{
	IDirect3DTexture9** m_textures; 
	D3DMATERIAL9*		m_material; 
	IDirect3DTexture9** m_NormalMaps; 

	Mesh*	 m_mesh;
	Matrix*	 m_boneOffset;
	Matrix** m_frameMatrix;
};

struct Frame : public D3DXFRAME
{
	Matrix  exCombinedTransformationMatrix;
};

class MeshHierarchy : public ID3DXAllocateHierarchy
{
public:
	/**
	 * Handles the creation of a d3dx frame
	 */
	STDMETHOD	(CreateFrame)(
					LPCSTR name, 
					LPD3DXFRAME* newFrame
					);
	/**
	 * Handles the creation of a d3dx mesh container
	 */
	STDMETHOD	(CreateMeshContainer)(
					LPCSTR name, 
					CONST D3DXMESHDATA* meshData, 
					CONST D3DXMATERIAL* materials, 
					CONST D3DXEFFECTINSTANCE* effects, 
					DWORD numMaterials, 
					CONST DWORD* adjacency, 
					LPD3DXSKININFO skinInfo, 
					LPD3DXMESHCONTAINER* newMeshContainer
					);

	/**
	 * Handles the destruction of a d3dx frame
	 */
	STDMETHOD	(DestroyFrame)(
					LPD3DXFRAME frame
					);
	/**
	 * Handles the destruction of a d3dx mesh container
	 */
	STDMETHOD	(DestroyMeshContainer)(
					LPD3DXMESHCONTAINER meshContainerToFree
					);
};

#endif //_MESHHIERARCHY_H_