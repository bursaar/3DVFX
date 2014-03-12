#include "MyGame.h"


MyGame::MyGame(HWND pHWnd, RenderClass pRenderClass)
{
	mHWND = pHWnd;
	mRenderClass = &pRenderClass;
}


MyGame::~MyGame()
{
}

void MyGame::SetupGame()
{

	// Set up parameters of game however necessary.
	RenderClass Renderer(mHWND);
	
	// Create the mesh manager
	MeshManager GameMeshManager;

	// Create the sphere
	float fl_radius = 1.0f;
	int slices = 15;
	int stacks = 15;
	LPD3DXBUFFER adjacencyBuffer;
	ID3DXMesh *sphereMesh;
	D3DXCreateSphere(mRenderClass->d3ddev, fl_radius, slices, stacks, &sphereMesh, &adjacencyBuffer);
	
	// Create the mesh to be used for all of the characters
	MyMeshClass CharacterMesh(&GameMeshManager, sphereMesh, &Renderer);
	
	// Create the player and non-player characters
	CharacterClass PlayerCharacter(CharacterMesh);
	CharacterClass EnemyCharacter1(CharacterMesh);
	CharacterClass EnemyCharacter2(CharacterMesh);



}