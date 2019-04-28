#include "GLFWEW.h"
#include "Sound.h"

#define FILE_MUSIC "Res/MainScene2m.wav"

int main()
{
	GLFWEW::Window& window = GLFWEW::Window::Instance();

	if (!window.Init(800,600,"SoundEditor"))
	{
		return 1;
	}
	if (!Sound::EngineInitialize()) {
		return 1;
	}

	Sound::Player sPlayer;
	sPlayer.Init(FILE_MUSIC);

	bool exitFlag = false;
	while (!window.ShouldClose() && !exitFlag)
	{
		window.Update();
		float deltatime = static_cast<float>(window.DeltaTime());
		
		if (window.IsKeyDown(GLFW_KEY_E)) {
			exitFlag = true;
		}
		if (window.IsKeyDown(GLFW_KEY_P)) {
			sPlayer.Play();
		}

		window.SwapBuffers();
		Sound::EngineUpdate(deltatime);
	}


	return 0;
}