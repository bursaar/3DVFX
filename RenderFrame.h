#pragma once

#include "Declarations.h"

// this is the function used to render a single frame
void render_frame(void)
{
	// clear the window
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, NULL, 1.0f, 0);
	// clear the depth buffer
	d3ddev->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	// do 3D rendering on the back buffer here
	init_graphics();    // call the function to initialize the triangle

	// select which vertex format we are using
	d3ddev->SetFVF(CUSTOMFVF);

	D3DXMATRIX matTranslateA;    // a matrix to store the translation for triangle A
	D3DXMATRIX matTranslateB;    // a matrix to store the translation for triangle B

	// PIPELINE
	D3DXMATRIX matRotateY;
	D3DXMATRIX matRocketShip;

	static float index = 0.0f; index += 0.01f;

	// build MULTIPLE matrices to translate the model and one to rotate
	D3DXMatrixTranslation(&matTranslateA, 0.0f, 0.0f, 2.0f);
	D3DXMatrixTranslation(&matTranslateB, 0.0f, 0.0f, -2.0f);
	D3DXMatrixRotationY(&matRotateY, index);    // the front side

	d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateA * matRotateY));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	d3ddev->SetTransform(D3DTS_WORLD, &(matTranslateB * matRotateY));
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	// Build matrix to roate the model based on the increasing float value
	D3DXMatrixRotationY(&matRotateY, index);
	D3DXMatrixTranslation(&matRocketShip, 0.0f, 0.0f, 0.0f);

	// Tell DirectX about the matrix
	d3ddev->SetTransform(D3DTS_WORLD, &matRotateY);

	D3DXMATRIX matView;	// View transformation matrix


	D3DXMatrixLookAtLH(&matView,
		&D3DXVECTOR3(0.0f, 0.0f, 15.0f),							// Camera position
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),		// Look at or target position
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)								// The direction of up
		);

	d3ddev->SetTransform(D3DTS_VIEW, &matView);						// Put the view transform in matView

	D3DXMATRIX matProjection;										// projection transform matrix

	D3DXMatrixPerspectiveFovLH(&matProjection,
		D3DXToRadian(60),											// Field of View
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,					// Aspect ratio
		1.0f,														// Near plane
		100.0f);													// Far plane

	d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);

	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

	// copy the vertex buffer to the back buffer
	d3ddev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	d3ddev->EndScene();    // ends the 3D scene

	d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen
}