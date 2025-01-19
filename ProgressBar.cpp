#include "ProgressBar.h"
ProgressBar::ProgressBar(int magnifier, int base, int x, int y)
	: magnifier(magnifier), base(base){
	progresBarSlider.h = progressBar.h = 25;
	progresBarSlider.x = progressBar.x = x;
	progresBarSlider.y = progressBar.y = y;
	progressBar.w = base * magnifier;
	progresBarSlider.w = 0;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::updateProgresBar(double switchValue) {
	progresBarSlider.w = (int)(switchValue * magnifier);
}

void ProgressBar::draw(SDL_Renderer* renderTarget) {
	SDL_SetRenderDrawColor(renderTarget, 200, 0, 0, 255);
	SDL_RenderFillRect(renderTarget, &progresBarSlider);
	SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderTarget, &progressBar);
}