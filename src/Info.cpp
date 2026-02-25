#include "Info.h"
#include <string.h>
#include <stdio.h>
#include "AssetsPaths.h"

Info::Info(SDL_Renderer* renderTarget, int x, int y, int width,
	int height)
{
	border.x = x;
	border.y = y;
	border.w = width;
	border.h = height;
	strcpy(this->infoControlText, infoControlText);
	textSurface = SDL_CreateRGBSurface(0, width, height, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	charset = SDL_LoadBMP(Assets::CHARSET_PATH);
	SDL_SetColorKey(charset, true, 0x000000);//white text
	updateTexture(renderTarget, 0, 0, 0);
	switchEndGameInfo(false);
}

Info::~Info()
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(infoField);
}

void Info::updateTexture(SDL_Renderer* renderTarget, double fps, double worldTime, int points) {
	updateTimerInfo(fps, worldTime, points);
	SDL_FillRect(textSurface, NULL, -16777216);//filling with black
	putStringInSurface(textSurface->w / 2 - strlen(infoTimerText) * 8 / 2, 10, infoTimerText);
	putStringInSurface(textSurface->w / 2 - strlen(infoControlText) * 8 / 2, 26, infoControlText);
	if (infoField) SDL_DestroyTexture(infoField);
	infoField = SDL_CreateTextureFromSurface(renderTarget, textSurface);
}
void Info::updateTimerInfo(double fps, double worldTime, int points) {
	sprintf(infoTimerText, "points = %d game duration = % .1lf s % .0lf fps",points, worldTime, fps);
}
void Info::putStringInSurface(int x, int y, const char* text) {
	int px, py, c;	
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, textSurface, &d);
		x += 8;
		text++;
	};
}
void Info::draw(SDL_Renderer* renderTarget, int fps, int worldTime, int points) {
	updateTexture(renderTarget, fps, worldTime, points);//tu
	SDL_RenderCopy(renderTarget, infoField, NULL, &border);
}

void Info::switchEndGameInfo(bool setValue) {
	if (!setValue) strcpy(infoControlText, "Esc exit, \030 move up, \031  move down, \032 move left, \033  move right");
	else strcpy(infoControlText, "Esc - exit, N - new Game");
}

