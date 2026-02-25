#pragma once
#include <SDL.h>
#include "List.h"
#include "Board.h"
#include "Timer.h"
#include "Point.h"

#define SNAKE_INIT_X 20
#define SNAKE_INIT_Y 20
#define SNAKE_PARTS 6
#define SNAKE_WIDTH 20
#define SNAKE_HEIGHT 20
#define SNAKE_TIME_TO_MOVE 0.2
#define SNAKE_REDDOT_REMOVE_AMOUNT 2
#define SNAKE_REDDOT_SLOWDOWN_AMOUNT 1.3

class Snake
{
public:
	Snake();
	~Snake();
	void draw(SDL_Renderer* renderTarget);
	void updatePosition(Board* board, Timer* timer, int &score);
	void initBody(int borderX, int borderY);
	SDL_Rect initBodyPart(int x, int y, int width, int height);
	enum class DIRECTIONS { UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3};
	void changeDirection(DIRECTIONS direction);
	bool itSelfCollision();
	void PointColisions(Board* board, Timer* timer, int& score, int tailPrevX, int tailPrevY);
private:
	enum DIRECTIONS direction;
	SDL_Texture* snakeTexture;
	List<SDL_Rect> bodyParts;
	void changeBodyPartPos(SDL_Rect& dst, SDL_Rect& src);
	void updateHead(SDL_Rect& head, Board* board);
	void updateHeadPosition(SDL_Rect& head);
	bool collision(SDL_Rect& other);
};

