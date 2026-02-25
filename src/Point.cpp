#include "Point.h"
#include <random>
#define POINT_WIDTH 10
#define POINT_HEIGHT 10
#define POINT_COLLIDER_WIDTH 30
#define POINT_COLLIDER_HEIGHT 30
#define BMP_POINT_IMAGE_FILE_PATH "./assets/bl.bmp"

Point::Point(SDL_Renderer* renderTarget, const char * filename){
	texSrc.w = POINT_WIDTH;
	texSrc.h = POINT_HEIGHT;
	collider.w = POINT_COLLIDER_WIDTH;
	collider.h = POINT_COLLIDER_HEIGHT;

	SDL_Surface* tempSurf = SDL_LoadBMP(filename);
	texture = SDL_CreateTextureFromSurface(renderTarget, tempSurf);
	SDL_FreeSurface(tempSurf);
	hidden = true;
}

void Point::respawn(SDL_Rect& border) {
	collider.x = rand() % (border.w - 50) + border.x + 25;
	collider.y = rand() % (border.h - 50) + border.y + 25;
	texSrc.x = collider.x + 10;
	texSrc.y = collider.y + 10;
	hidden = false;
}

void Point::draw(SDL_Renderer* renderTarget) {
	if (hidden) return;
	SDL_SetRenderDrawColor(renderTarget, 0, 220, 0, 255);
	SDL_RenderCopy(renderTarget, texture, NULL, &texSrc);
}

Point::~Point()
{
	SDL_DestroyTexture(texture);
}

SDL_Rect Point::getCollider() {
	return collider;
}

void Point::hide() {
	collider.x = collider.y = -200;
	hidden = true;
}