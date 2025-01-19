#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
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
