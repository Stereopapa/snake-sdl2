#include "Timer.h"
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}
#include <random>

#define SPEEDUP_AMMOUNT 0.8
#define RED_DOT_MIN_TIME 2;
#define RED_DOT_MAX_TIME 2;

Timer::Timer(double snakeMoveTime, double timeToSpeedup, 
	double redDotActiveTime): 
	snakeBaseTimeToMove(snakeMoveTime), timeToSpeedup(timeToSpeedup)
	, redDotActiveTime(redDotActiveTime){}

void Timer::startTimer() {
	currentTime = previousTime = SDL_GetTicks();
	frames = fps = dTime = fpsTimer = worldTime = 
	snakeTimePassed = speedupTimePassed = redDotTimePassed = 0;
	snakeTimeToMove = snakeBaseTimeToMove;
	startRedDot();
}

void Timer::startRedDot() {
	timeToRedDot = rand() % RED_DOT_MAX_TIME;
	timeToRedDot += RED_DOT_MIN_TIME;
	redDotTimePassed = 0;
}

void Timer::mulitplySnakeTimeToMove(double value) {
	snakeTimeToMove *= value;
}

Timer::~Timer(){}

void Timer::update() {
	currentTime = SDL_GetTicks(); //[ms]

	dTime = (currentTime - previousTime) * 0.001;
	previousTime = currentTime;

	worldTime += dTime;
	snakeTimePassed += dTime;
	speedupTimePassed += dTime;
	redDotTimePassed += dTime;



	fpsTimer += dTime;
	if (fpsTimer > 0.5) {
		fps = frames * 2;
		frames = 0;
		fpsTimer -= 0.5;
	};
	frames++;

	if (speedupTimePassed > timeToSpeedup) {
		speedupTimePassed = 0;
		mulitplySnakeTimeToMove(SPEEDUP_AMMOUNT);
	}
}

int Timer::getFps() {
	return fps;
}
double Timer::getDTime(){
	return dTime;
}
double Timer::getWorldTime(){
	return worldTime;
}

bool Timer::snakeMove() {
	if (snakeTimePassed > snakeTimeToMove) {
		snakeTimePassed = 0;
		return true;
	}
	return false;
}

double Timer::redDot() {
	if (timeToRedDot >= 0) {
		if (redDotTimePassed > timeToRedDot) {
			timeToRedDot = -1;
			redDotTimePassed = 0;
			return -1.0;//activate
		}
		else return -3.0;//wainting for respawn
	}
	else {//active
		if (redDotTimePassed > redDotActiveTime) {
			startRedDot();
			return -2.0;//disappering
		}
		else return redDotTimePassed; //loading bar
	}

}