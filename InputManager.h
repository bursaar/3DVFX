#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#include "Singleton.h"
#include <windows.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#define CTRL 0x1d
//////////////////////////////////////////////
//InputManger Class
//
//This Controls the Inputs of the game by creating a DirectInput Object
//The user can then test the class to see if keyboard inputs have been made
//////////////////////////////////////////////
class InputManager : public Singleton<InputManager>
{
public:
	//ButtonState stores the current status of a keypress.
	//weather is it not presses, just presses or being held down
	enum ButtonState
	{
		ButtonState_Off     = 0,
		ButtonState_Clicked = 1,
		ButtonState_On      = 2,
	};
	
	enum MouseButtons
	{
		LeftMouse = 0,
		RightMouse = 1,
	};

	/**
	 * Constructor
	 */
							InputManager();
	/**
	 * Destructor
	 */
							~InputManager();
	/**
	 * Sets up the direct input instance
	 */
	bool					Setup(
								HINSTANCE hInst, ///< Application instance
								HWND hWindow ///< Application window
								);
	/**
	 * Converts a VK into its ascii equivilant
	 */
	unsigned int			KeycodeToASCII(
								int code
								) const;
	/**
	 * Updates the input state
	 */
	void					Update();
	/**
	 *Returns the current key state
	 */
	ButtonState				GetKeyState(
								int key
								) const;

	/**
	 * Returns if the button state for the specified VK ident, or ascii code, is down
	 */
	bool					IsKeyDown(
								bool ascii,
								int key
								)const;

	/**
	 * Returns if the button state for the specified VK ident, or ascii code, has just been pressed this frame
	 */
	bool					IsKeyClicked(
								bool ascii,
								int key
								)const;
	/**
	 * Checks to see if any key has been pressed
	 */
	bool					IsAnyKeyClicked()const;


	/**
	 * Returns if the mouse button state is down for the specified button
	 */
	bool					IsMouseButtonDown(
								int button
								) const;
	/**
	 * Returns the mouses current x axis (movement axis left to right)
	 */
	float					GetMouseX() const;
	/**
	 * Returns the mouses current y axis (movment axis up & down)
	 */
	float					GetMouseY() const;
	/**
	 * Returns the mouses current z axis (scroll axis up & down)
	 */
	float					GetMouseZ() const;
private:
	/**
	 * Handles the creation of the keyboard
	 */
	bool					CreateKeyboard(
								HWND hWindow ///< Game window
								);
	/**
	 * Handles the creation of the mouse
	 */
	bool					CreateMouse(
								HWND hWindow ///< Game window
								);
	/**
	 * updates the state of the keyboard
	 */
	void					UpdateKeyboard();
	/**
	 * Updates the state of the mouse
	 */
	void					UpdateMouse();


	//Arrays for key information
	__int8 m_keyStates[256];
	__int8 m_vkkeyStates[256];
	//DirectInput Device
	LPDIRECTINPUT8 m_directInput;
	//Keyboad Device
	LPDIRECTINPUTDEVICE8 m_keyboard;
	//Mouse Device
	LPDIRECTINPUTDEVICE8 m_mouse;
	DIMOUSESTATE2        m_mouseState;
	bool m_change;
	unsigned int m_ASCII[256];

};

#endif // _INPUTMANAGER_H_
