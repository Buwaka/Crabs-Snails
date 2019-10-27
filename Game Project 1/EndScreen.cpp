#include "stdafx.h"
#include "EndScreen.h"
#include "Texture.h"

#include <algorithm>



EndScreen::EndScreen(const Window * window)
{
	m_pWindow = window;
}

EndScreen::~EndScreen()
{
}

void ClearBackground()
{
	glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void EndScreen::Run(SDL_Window* window)
{

	m_sound = Mix_LoadWAV("resources/dead.wav");
	m_font = TTF_OpenFont("resources/AGaramondPro-Regular.otf", 64);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);



	Mix_PlayChannel(1, m_sound, 0);
	Texture scr("You Died", m_font, Color4f{ 0.f,0.f,0.f,1.f });

	int i = 0;
	while (Mix_Playing(1))
	{
		ClearBackground();
		scr.Draw({ m_pWindow->width / 2 - (scr.GetWidth() / 2) - i, (m_pWindow->height / 2) - (scr.GetHeight() / 2) - i, scr.GetWidth() + i, scr.GetHeight() + i}, {});
		SDL_GL_SwapWindow(window);
		i = std::min(i + 1, 100);
	}




	Mix_FreeChunk(m_sound);
	TTF_CloseFont(m_font);
}
