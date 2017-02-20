#include "text.h"
#include <iostream>
#include "window.h"
Text::Text(	const std::string &file_path, 
			int font_size, 
			const std::string &message_text, 
			const SDL_Color &color) 

			: _file_path(file_path), _font_size(font_size),
			_message_text(message_text), _color(color)
{
	setText(message_text);
}

void Text::setText(const std::string &text) {
	_message_text = text;
	_text_texture = loadFont(_file_path, _font_size, text, _color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);
}

void Text::display(int x, int y, SDL_Renderer *renderer) const {	
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(renderer, _text_texture, nullptr, &_text_rect);
}

SDL_Texture * Text::loadFont(const std::string &file_path, int font_size, const std::string &message_text, const SDL_Color &color) {
	TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
	if (!font)
		std::cout << "failed to load font\n";

	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	if (!text_surface)
		std::cout << "failed to create text surface\n";

	auto text_texture = SDL_CreateTextureFromSurface(Window::renderer, text_surface);
	if (!text_texture)
		std::cout << "failed to create text texture\n";

	SDL_FreeSurface(text_surface);
	return text_texture;
}