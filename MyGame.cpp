#include "MyGame.h"


MyGame::MyGame(HWND &pHWND)
{
	
	SetupGame(pHWND);
}


MyGame::~MyGame()
{
}

void MyGame::SetupGame(HWND &pHWND)
{

	// Set up parameters of game however necessary.
	RenderClass Renderer(pHWND);
	mRenderer = Renderer;
	
	// Create the mesh manager
	MeshManager GameMeshManager;
	mMeshManager = GameMeshManager;

	// Create the sphere
	float fl_radius = 1.0f;
	int slices = 15;
	int stacks = 15;
	LPD3DXBUFFER adjacencyBuffer;
	ID3DXMesh *sphereMesh;
	D3DXCreateSphere(mRenderer.d3ddev, fl_radius, slices, stacks, &sphereMesh, &adjacencyBuffer);
	
	// Create the mesh to be used for all of the characters
	MyMeshClass CharacterMesh(&mMeshManager, sphereMesh, &mRenderer);
	
	// Create the player and non-player characters
	CharacterClass PlayerCharacter(&CharacterMesh);
// 	CharacterClass EnemyCharacter1(&CharacterMesh);
// 	CharacterClass EnemyCharacter2(&CharacterMesh);

	// Assign newly created characters to game class
	 mPlayerCharacter = new CharacterClass(PlayerCharacter);

//	mPlayerCharacter = &PlayerCharacter;
// 	mNPC1 = &EnemyCharacter1;
// 	mNPC2 = &EnemyCharacter2;

}

void MyGame::Update()
{
	// Update character input
	mPlayerCharacter->UpdateCharacter();

	// Player attributes first - NPC attributes will be derived from this model
	if (mPlayerCharacter->speed > 0)
	{
		mPlayerCharacter->speed -= mPlayerCharacter->friction;		// Trend towards zero with friction variable.
	}
	if (mPlayerCharacter->speed < 0)
	{
		mPlayerCharacter->speed += mPlayerCharacter->friction;		// Trend towards zero with friction variable.
	}

	switch (mPlayerCharacter->movement)
	{
	case CharacterClass::FORWARD:
	{
									mPlayerCharacter->speed += accelerationPlayer;
	}
	case CharacterClass::BACK:
	{
								 mPlayerCharacter->speed -= accelerationPlayer;
	}
	case CharacterClass::LEFT:
	{
								 mPlayerCharacter->rotationInRadians -= rotationPlayer;
	}
	case CharacterClass::RIGHT:
	{
								  mPlayerCharacter->rotationInRadians += rotationPlayer;
	}
	}

	mPlayerCharacter->mMyMesh->UpdateMeshParameters(mPlayerCharacter->speed, mPlayerCharacter->rotationInRadians);

	mPlayerCharacter->mMyMesh->mesh->DrawSubset(0);
}