#pragma once
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>
#include <map>

class Text {
public:
	Text(const std::string &file_path, int font_size, const std::string &message_text, const SDL_Color &color);
	Text() {}

	void display(int x, int y, SDL_Renderer *renderer) const;
	void setText(const std::string &text);

	inline int getTextWidth() const { return _text_rect.w; }
	inline int getTextHeight() const { return _text_rect.h; }
	inline const std::string &getText() const { return _message_text; }

private:
	SDL_Texture *loadFont(const std::string &file_path, int font_size, const std::string &message_text, const SDL_Color &color);

private:
	SDL_Texture *_text_texture = nullptr;
	mutable SDL_Rect _text_rect;

	std::string _file_path;
	int _font_size;
	std::string _message_text;
	SDL_Color _color;
};