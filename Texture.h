#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Texture wrapper class
class Texture {

	public:
		//Initializes variables
		Texture(void);

		//Deallocates memory
		~Texture(void);

		//Loads images at specified path
		bool load_from_file(SDL_Renderer*, std::string);

#ifdef _SDL_TTF_H
		//Creates image from font string
		bool load_from_rendered_text(SDL_Renderer*, std::string, SDL_Color, TTF_Font*);
#endif

		//Deallocates textures
		void free(void);

		//Set color modulation
		void set_color(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void set_blend_mode(SDL_BlendMode);

		//Set alpha modulation
		void set_alpha(Uint8 alpha);

		//Renders texture at given point
		void render(SDL_Renderer*, int x, int y);
		void render(SDL_Renderer*, int, int, SDL_Rect*, double, SDL_Point*, SDL_RendererFlip);

		//Gets image dimensions
		int get_width (void);
		int get_height (void);
		SDL_Texture* get_m_texture (void);

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

#endif //TEXTURE_H
