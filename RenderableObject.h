#pragma once
#include <vector>
#include "RenderClass.h"

using namespace std;

// NOTE FROM STUDENT:
// I am basing my implementation of this renderable object class on the 
// IRenderable class in the Train2Game LIT series on creating a game in C++. 
// The structure is similar but the code almost entirely my own. I will 
// flag instances that are from the original course material.

#ifndef __DEG_TO_RAD
#define __DEG_TO_RAD					// Include guard to make sure the const is only ever included once.

const float DEG_TO_RAD = 0.017453292519943295769236907684886f;		// This constant was included in the original LIT material.

#endif

class RenderableObject
{
public:
	bool collidable;			// Can this object collide with other objects?

	DWORD mColour;

	float radius;				// What is the radius of collision?

	bool mRenderThis;			// Should this be rendered?

	RenderableObject();
	~RenderableObject();
	void Release();				// This member function is lightly adapted from the original LIT material.
	virtual void Initialise(RenderClass * pRenderClass);
	virtual void Update(double deltaTime, double totalTime);
	virtual void Render(const D3DXMATRIXA16 &baseMatrix);
	void Resume();
	void GetPosition(double &px, double &py, double &pz);	// Apart from following the LIT material's use of doubles, this implementation is my own
	void GetScale(double &px, double &py, double &pz);
	double GetRotateY();	// Apart from following the LIT material's use of double as a return value, I implemented this function myself.
	void SetTexture(LPCWSTR fileName);	// Taken from the LIT materials
	void Move(float pX, float pY, float pZ);
	virtual void OnCollide(RenderableObject* other);
	void RotateY(float angle);
	int GetOpacity(CUSTOMVERTEX pVertex);

	bool block;
protected:
	bool initialised;			// Is the object initialised?

	wstring mTextureName;		// This variable is taken from the original LIT material.

	RenderClass * mRenderer;	// A pointer to the rendering object
	
	// Vectors for placing the object in the world
	D3DXVECTOR3 mPosition;		// Position
	D3DXVECTOR3 mVelocity;		// Velocity
	D3DXVECTOR3 mScale;			// Scale
	D3DXVECTOR3 mRotation;		// Rotation

	vector<RenderableObject *> mChildren;	// This stack was used in the original LIT material.

	vector<CUSTOMVERTEX> vertices;			// A stack similar to this was used in the original LIT material, but with a different struct.

	IDirect3DIndexBuffer9 * mIndexBuffer;	// This index buffer was used in the original LIT material.

	IDirect3DTexture9 * mTexture;			// This texture was used in the original LIT material.

	IDirect3DVertexBuffer9 * mVertexBuffer;	// This vertex buffer was used in the original LIT material.

	int facecount;							// This integer of faces to be drawn was in the original LIT material.
};

