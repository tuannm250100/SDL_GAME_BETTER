#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include<windows.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

const int BACKGROUND_WIDTH = 4800;
const int BACKGROUND_HEIGHT = 600;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;
const int NUM_THREATS = 3;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_background = NULL;
static SDL_Event g_event;

namespace SDLCommon
{
	SDL_Surface* LoadImage(std::string file_path);
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApllySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}
#endif