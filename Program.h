#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#ifndef _DIRECTXDEVICE_H_
#include "DirectXDevice.h"
#endif //#ifndef _DIRECTXDEVICE_H_

class Program : public Singleton<Program>,
				public DirectXDevice
{
public:
	/**
	 * Constructor
	 */
							Program();
	/**
	 * Destructor
	 */
							~Program();
	/**
	 * Generates the program instance for command line apps
	 */
	int						GenerateProgram(
								HINSTANCE hInstance, 
								HINSTANCE hPrevInstance,
								PSTR szCmdLine,
								int iCmdShow
								);
	/**
	 * Generates the program instance for windowed apps
	 */
	int						GenerateProgram(
								HWND hWnd, 
								HWND hWndParent, 
								HINSTANCE hInstance
								);
	/**
	 * Returns if the app is still running
	 */
	bool					GetRunning() const;
	/**
	 * Sets if the program is running
	 */
	void					SetRunning(
								bool running
								);
	/**
	 * returns the programs window
	 */
	HWND					GetWindow() const;
	/**
	 * Handles the rendering of the scene
	 */
	virtual void			RenderScene();
	/**
	 * Process the windows messages
	 */
	virtual LRESULT			WndProc(
								HWND hWindow,
								UINT msg,
								WPARAM wParam,
								LPARAM lParam
								);
	/**
	 * Updates the program
	 */
	void					Update(
								float elapsedTime
								);
	/**
	 * Returns the folder the program is running from
	 */
	const char*				GetDirectory();
	/**
	 * Returns if auto generation of mip maps is enabled
	 */
	bool					GetCanAutoGenerateMips() const;
private:
	bool m_running;

	HWND hWindow;

	int m_ClearR;
	int m_ClearG;
	int m_ClearB;

	char* m_buffer;
};

#endif // #ifndef _PROGRAM_H_
