#pragma once
class EndScreen
{
public:
	EndScreen(const Window* window);
	~EndScreen();
	EndScreen(const EndScreen& other) = delete;
	EndScreen& operator=(const EndScreen& other) = delete;
	EndScreen(EndScreen&& other) = delete;
	EndScreen& operator=(EndScreen&& other) = delete;

	void Run(SDL_Window* window);

private:
	TTF_Font* m_font;
	Mix_Chunk* m_sound;
	const Window* m_pWindow;
};

