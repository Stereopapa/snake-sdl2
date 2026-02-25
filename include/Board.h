#pragma once
#include <SDL.h>
#include "Point.h"
#include "Info.h"
#include "ProgressBar.h"

class Board
{
public:
	Board(SDL_Renderer* renderTarget, int x, int y, int width, int height);
	~Board();
	SDL_Rect getBorder();
	bool isInBoard(SDL_Rect& obj);
	Point* getRedPoint();
	Point* getBluePoint();
	void draw(SDL_Renderer* renderTarget);
	void handleRedDot(double switchValue);
	void clearRedDot();

private:
	SDL_Rect border;
	Point* bluePoint;
	Point* redPoint;
	ProgressBar* redDotBar;
};

