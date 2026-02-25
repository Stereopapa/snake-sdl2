#pragma once
#include <SDL.h>

#define RED_DOT_ACTIVE_TIME 5.0

class Point
{
public:
	Point(SDL_Renderer* renderTarget, const char* filename);
	~Point();
	void draw(SDL_Renderer* renderTarget);
	void respawn(SDL_Rect& border);
	SDL_Rect getCollider();
	void hide();
private:
	SDL_Rect collider;
	SDL_Rect texSrc;
	SDL_Texture* texture;
	bool hidden;
};