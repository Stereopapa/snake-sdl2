#pragma once
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
class Info
{
public:
	Info(SDL_Renderer* renderTarget,int x, int y, int width, int height);
	~Info();
	void draw(SDL_Renderer* renderTarget, int fps, int worldTime, int points);
	void switchEndGameInfo(bool value);
	void updateProgresBar(double switchValue, double maxValue);
private:
	SDL_Rect border;
	SDL_Surface* charset;
	SDL_Surface* textSurface;
	SDL_Texture* infoField;
	char infoTimerText[100],  infoControlText[100];
	bool endGameOn;
	
	void updateTexture(SDL_Renderer* renderTarget, double fps, double worldTime, int points);
	void updateTimerInfo(double fps, double worldTime, int points);
	void putStringInSurface(int x, int y, const char* text);
};