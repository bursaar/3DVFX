#include "SphereClass.h"


SphereClass::SphereClass()
{
	mColour = 0xFF00FFFF;
}


SphereClass::~SphereClass()
{
	delete mMesh;
}

// This method is taken from the Train2Game LIT with minor modifications.
void SphereClass::Initialise(RenderClass * pRenderClass)
{
		CreateSphereManually();
		int verticeCount = ui_VCount;

		for (int x = 0; x < verticeCount; x++)
		{
			CUSTOMVERTEX vert = arr_Vertices[x];
			vertices.push_back(CUSTOMVERTEX(vert.x, vert.y, vert.z, mColour, 0.0f, 0.0f));
		}

		facecount = ui_ShapeCount;
		mRenderThis = true;
		RenderableObject::Initialise(pRenderClass);

		initialised = true;
		collidable = true;
		radius = 0.54f;

		// Resize manually-created sphere to match scale of meshed scene
		float scale = 1.0f;
		mScale.x = scale;
		mScale.y = scale;
		mScale.z = scale;
}


void SphereClass::Update(double deltaTime, double totalTime)
{
	RenderableObject::Update(deltaTime, totalTime);
}

// The below method was adapted from http://stackoverflow.com/questions/4405787/generating-vertices-for-a-sphere
// The refactoring consists of changing the way the function uses my CUSTOMVERTEX type.
void SphereClass::CreateSphereManually()
{
		const int iFactor = 30;
		int iPos = 0;
		ui_VCount = 5760;

		arr_Vertices = new CUSTOMVERTEX[ui_VCount];
		ui_ShapeCount = iFactor *iFactor * 2; // use when rendering

		float arrV[iFactor* iFactor][3];

		for (DWORD j = 0; j < iFactor; j++)
		{
			FLOAT theta = (D3DX_PI*j) / (iFactor);

			for (DWORD i = 0; i<iFactor; i++)
			{
				iPos = j*iFactor + i;
				FLOAT phi = (2 * D3DX_PI*i) / (iFactor);
				arrV[iPos][0] = (float)(sin(theta)*cos(phi));
				arrV[iPos][1] = (float)(sin(theta)*sin(phi));
				arrV[iPos][2] = (float)(cos(theta));
			}
		}

		int iNext = 0;

		for (DWORD j = 0; j < iFactor; j++)
		{

			for (DWORD i = 0; i<iFactor; i++)
			{
				if (i == iFactor - 1)
					iNext = 0;
				else iNext = i + 1;

				iPos = (j*iFactor * 6) + (i * 6);
				arr_Vertices[iPos].x = arrV[j*iFactor + i][0];
				arr_Vertices[iPos].y = arrV[j*iFactor + i][1];
				arr_Vertices[iPos].z = arrV[j*iFactor + i][2];
				arr_Vertices[iPos + 1].x = arrV[j*iFactor + iNext][0];
				arr_Vertices[iPos + 1].y = arrV[j*iFactor + iNext][1];
				arr_Vertices[iPos + 1].z = arrV[j*iFactor + iNext][2];

				if (j != iFactor - 1)
				{
					arr_Vertices[iPos + 2].x = arrV[((j + 1)*iFactor) + i][0];
					arr_Vertices[iPos + 2].y = arrV[((j + 1)*iFactor) + i][1];
					arr_Vertices[iPos + 2].z = arrV[((j + 1)*iFactor) + i][2];
				}
				else
				{
					arr_Vertices[iPos + 2].x = 0; //Create a pseudo triangle fan for the last set of triangles
					arr_Vertices[iPos + 2].y = 0;
					arr_Vertices[iPos + 2].z = -1;
				}
					

				arr_Vertices[iPos].normal = D3DXVECTOR3(arr_Vertices[iPos].x, arr_Vertices[iPos].y, arr_Vertices[iPos].z);
				arr_Vertices[iPos + 1].normal = D3DXVECTOR3(arr_Vertices[iPos + 1].x, arr_Vertices[iPos + 1].y, arr_Vertices[iPos + 1].z);
				arr_Vertices[iPos + 2].normal = D3DXVECTOR3(arr_Vertices[iPos + 2].x, arr_Vertices[iPos + 2].y, arr_Vertices[iPos + 2].z);

				arr_Vertices[iPos + 3].x = arr_Vertices[iPos + 2].x;
				arr_Vertices[iPos + 3].y = arr_Vertices[iPos + 2].y;
				arr_Vertices[iPos + 3].z = arr_Vertices[iPos + 2].z;
				arr_Vertices[iPos + 4].x = arr_Vertices[iPos + 1].x;
				arr_Vertices[iPos + 4].y = arr_Vertices[iPos + 1].y;
				arr_Vertices[iPos + 4].z = arr_Vertices[iPos + 1].z;


				if (j != iFactor - 1)
				{
					arr_Vertices[iPos + 5].x = arrV[((j + 1)*iFactor) + iNext][0];
					arr_Vertices[iPos + 5].y = arrV[((j + 1)*iFactor) + iNext][1];
					arr_Vertices[iPos + 5].z = arrV[((j + 1)*iFactor) + iNext][2];
				}
				else
				{
					arr_Vertices[iPos + 5].x = 0;
					arr_Vertices[iPos + 5].y = 0;
					arr_Vertices[iPos + 5].z = -1;
				}
				arr_Vertices[iPos + 3].normal = D3DXVECTOR3(arr_Vertices[iPos + 3].x, arr_Vertices[iPos + 3].y, arr_Vertices[iPos + 3].z);
				arr_Vertices[iPos + 4].normal = D3DXVECTOR3(arr_Vertices[iPos + 4].x, arr_Vertices[iPos + 4].y, arr_Vertices[iPos + 4].z);
				arr_Vertices[iPos + 5].normal = D3DXVECTOR3(arr_Vertices[iPos + 5].x, arr_Vertices[iPos + 5].y, arr_Vertices[iPos + 5].z);

			}
		}


}