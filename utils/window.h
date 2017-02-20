#pragma once

#include <SDL/SDL.h>
#include <string>

class Window {
public:
	Window(const std::string &title, int width, int height);
	~Window();

	inline bool closed() const { return _closed; }

	void pollEvents(SDL_Event &event);
	void clear() const;

private:
	bool init();

private:
	std::string _title;
	int _width = 320;
	int _height = 480;
	bool _closed = false;

	SDL_Window *_window = nullptr;

public:
	static SDL_Renderer *renderer;
};