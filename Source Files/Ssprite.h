#ifndef  _SSPRITE_H
#define _SSPRITE_H

class Sprite
{
	public:
        Sprite();

        static SDL_Surface* Load(char* pFile);

        static bool Draw( SDL_Surface* dest, SDL_Surface* src, int x, int y );

        static bool Draw( SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int width, int height );
};

Sprite::Sprite() {}

SDL_Surface* Sprite::Load( char* File )
{
	SDL_Surface* temp = NULL;
	SDL_Surface* optimized = NULL;

	if(( temp = IMG_Load(File)) == NULL ) return NULL;

	optimized = SDL_DisplayFormatAlpha(temp);
	SDL_FreeSurface(temp);

	return optimized;
}

bool Sprite::Draw( SDL_Surface* dest, SDL_Surface* src, int x, int y )
{
    if(dest == NULL || src == NULL) return false;

    SDL_Rect  destR;

    destR.x = x;
    destR.y = y;

    SDL_BlitSurface(src, NULL, dest, &destR);

    return true;
}

bool Sprite::Draw( SDL_Surface* dest, SDL_Surface* src, int x, int y, int x2, int y2, int width, int height)
{
	if(dest == NULL || src == NULL ) return false;

	SDL_Rect destR;

	destR.x = x;
	destR.y = y;

	SDL_Rect srcR;

	srcR.x = x2;
	srcR.y = y2;
	srcR.w = width;
	srcR.h = height;

	SDL_BlitSurface(src, &srcR, dest, &destR);

	return true;
}

#endif
