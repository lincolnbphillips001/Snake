#include "Texture.h"

Texture::Texture(void) {

	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

Texture::~Texture(void) {

	//Deallocate
	free();
}

bool Texture::load_from_file(SDL_Renderer* renderer, std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool Texture::load_from_rendered_text(
	SDL_Renderer* renderer, std::string textureText, SDL_Color textColor, TTF_Font* font)
{
	//Get rid of preexisting texture
	free();

	//Load image at specified path
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor);
	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return mTexture != NULL;
}
#endif

//Deallocates textures
void Texture::free(void) {

	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

//Set color modulation
void Texture::set_color(Uint8 red, Uint8 green, Uint8 blue) {

	//Modulation texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

//Set blending
void Texture::set_blend_mode(SDL_BlendMode blending) {

	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

//Set color modulation
void Texture::set_alpha(Uint8 alpha) {

	//Set blending function
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

//Renders texture at given point
void Texture::render(SDL_Renderer* renderer, int x, int y) {

	SDL_Rect* clip = NULL;

	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

//Renders texture at given point
void Texture::render(
	SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, 
	SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {

	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	//Set clip rendering dimensions
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
}

//Gets image dimensions
int Texture::get_width (void) {

	return mWidth;
}

int Texture::get_height (void) {

	return mHeight;
}

SDL_Texture* Texture::get_m_texture (void) {

		//The actual hardware texture
		return mTexture;
}
