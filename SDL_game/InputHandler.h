#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SDL.h>
#include <vector>
class Vector2D;

const int m_joystickDeadZone = 10000;

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == 0)
		{
			s_pInstance = new InputHandler();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//Joystick related
	void initialiseJoysticks();
	bool joysticksInitialised() { return m_bJoysticksInitialised; }

	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);

	bool getButtonState(int joy, int buttonNumber) { return m_buttonStates[joy][buttonNumber]; }

	//Mouse Related
	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	Vector2D* getMousePosition() {return m_mousePosition; }

	//Keyboard Related
	bool isKeyDown(SDL_Scancode key);

	void update();
	void clean();
	void reset();

private:
	InputHandler();
	~InputHandler(){};
	static InputHandler* s_pInstance;

	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);

	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
	void onMouseMove(SDL_Event& event);

	void onKeyDown();
	void onKeyUp();

	//Joystick related
	bool m_bJoysticksInitialised;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	//Mouse related
	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	//Keyboard related
	const Uint8* m_keystates; //Pointer to keystates array
};
typedef InputHandler TheInputHandler;

#endif