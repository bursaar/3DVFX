#ifndef _DIRECTXDEVICE_H_
#define _DIRECTXDEVICE_H_
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")

#define ANTI_ALIAS_ENABLED true

//////////////////////////////////////////////////////////////////////////
//DirectXDevice
//
//This Class contains the functions the create a DirectX 9 device, 
//and the command to render items when required,
//
//There are 2 render functions, Render is a setup for direct x to control the
//draw scene, by clearing the screen, starting the scene for drawing and ending the scene
//when completed. RenderScene, a virtual function, will be called in between the begin and end scene.
//and will contains all objects that need to be drawn, such as meshes and lights.
//////////////////////////////////////////////////////////////////////////

class DirectXDevice
{
public:
	/**
	 * Creates the D3D device using the window handle passed in
	 */
	HRESULT				CreateD3DDevice(
							HWND Window
							);
	/**
	 * Cleans up the D3D Device
	 */
	void				CleanUp();
	/**
	 * Handles the renderering of a frame.
	 */
	void				Render();
	/**
	 * Interface for rendering the scene
	 */
	virtual void		RenderScene() {};
	/**
	 * Returns the device width
	 */
	int					GetScreenWidth() const;
	/**
	 * Returns the device height
	 */
	int					GetScreenHeight() const;
	/**
	 * Returns if the device supports 2 sided stencil operations
	 */
	bool				Allow2SidedShadows();
	/**
	 * Clears the render buffer
	 */
	void				ClearBuffer();
	/**
	 * Sets the clear colour
	 */
	void				SetClearBufferColour(
							int r, 
							int g, 
							int b
							);
	/**
	 * Gets the clear colour
	 */
	void				GetClearBufferColour(
							int& r, 
							int& g, 
							int& b
							);
protected:
	//Direct 9 Structure
	LPDIRECT3D9 m_D3D;
	int m_screenWidth;
	int m_screenHeight;
	bool m_autoGenMips;
	bool m_allow2Sided;
	int m_ClearR;
	int m_ClearG;
	int m_ClearB;
};

#endif //_DIRECTXDEVICE_H_
