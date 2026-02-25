#pragma once
#include <SDL.h>
class ProgressBar
{
public:
	ProgressBar(int magnifier, int base, int x, int);
	~ProgressBar();
	void updateProgresBar(double switchValue);
	void draw(SDL_Renderer* renderTarget);
private:
	SDL_Rect progressBar;
	SDL_Rect progresBarSlider;
	int magnifier;
	int base;
};
