#include "Snake.h"
#include <random>


Snake::Snake(){}

Snake::~Snake(){
	//SDL_DestroyTexture(snakeTexture);s
}

void Snake::initBody(int borderX, int borderY) {
	bodyParts.clear();
	direction = DIRECTIONS::RIGHT;
	int x = SNAKE_INIT_X + borderX;
	int y = SNAKE_INIT_Y + borderY;
	x += SNAKE_WIDTH * SNAKE_PARTS;
	for (int i = 0; i < SNAKE_PARTS; i++)
	{
		bodyParts.insertBack(initBodyPart(x, y, SNAKE_WIDTH, SNAKE_HEIGHT));
		x -= SNAKE_WIDTH;
	}
}

SDL_Rect Snake::initBodyPart(int x, int y, int width, int height) {
	SDL_Rect part;
	part.x = x;
	part.y = y;
	part.w = width;
	part.h = height;
	return part;
}

void Snake::draw(SDL_Renderer* renderTarget) {
	Node<SDL_Rect>* temp = bodyParts.getHead();

	//head with one eye cyclop snake
	SDL_SetRenderDrawColor(renderTarget, 0, 220, 0, 255);
	SDL_RenderFillRect(renderTarget, &temp->data);
	SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);
	SDL_Rect eye1;
	eye1.x = temp->data.x + temp->data.w / 2 - 1;
	eye1.y = temp->data.y + temp->data.h / 2 - 1;
	eye1.w = eye1.h = 3;
	SDL_RenderFillRect(renderTarget, &eye1);
	//rest of the body in light and dark greeen
	temp = temp->next;
	int color = -1;
	while (temp){
		if (color > 0) SDL_SetRenderDrawColor(renderTarget, 0, 220, 0, 255);
		else SDL_SetRenderDrawColor(renderTarget, 0, 150, 0, 255);
		color *= -1;
		SDL_RenderFillRect(renderTarget, &temp->data);
		temp = temp->next;
	}
}

void Snake::updatePosition(Board* board, Timer* timer, int& points) {
	Node<SDL_Rect>* temp = bodyParts.getTail();
	int tX = temp->data.x;
	int tY = temp->data.y;
	while (temp->prev)
	{
		changeBodyPartPos(temp->data, temp->prev->data);
		temp = temp->prev;
	}
	int hx = temp->data.x;
	int hy = temp->data.y;
	updateHead(temp->data, board);
	PointColisions(board, timer, points, tX, tY);
}

void Snake::PointColisions(Board* board, Timer* timer, int& points, int tailPrevX, int tailPrevY) {
	Point* bluePoint = board->getBluePoint();
	SDL_Rect bluePointCollider =  bluePoint->getCollider();
	if (collision(bluePointCollider)) {
		SDL_Rect border = board->getBorder();
		bluePoint->respawn(border);
		bodyParts.insertBack(initBodyPart(tailPrevX, tailPrevY, SNAKE_WIDTH, SNAKE_HEIGHT));
		points++;
	}
	Point* redPoint = board->getRedPoint();
	SDL_Rect redPointCollider = redPoint->getCollider();
	if (collision(redPointCollider)) {
		if (rand() % 2) {
			if (bodyParts.amount() <= 3) return;
			for (int i = 0; i < SNAKE_REDDOT_REMOVE_AMOUNT; i++)
			{
				bodyParts.removeBack();
			}
		}
		else {
			timer->mulitplySnakeTimeToMove(SNAKE_REDDOT_SLOWDOWN_AMOUNT);
		}
		timer->startRedDot();
		board->clearRedDot();
		points++;
	}
}

void Snake::changeBodyPartPos(SDL_Rect& dst, SDL_Rect& src) {
	dst.x = src.x;
	dst.y = src.y;
}

void Snake::updateHead(SDL_Rect& head, Board* board) {
	int hx = head.x;
	int hy = head.y;
	int intDirection = (int)direction;
	int prevDirection = (int)direction;
	updateHeadPosition(head);
	if (!board->isInBoard(head)) {
		head.x = hx;
		head.y = hy;
		intDirection++;
		if (intDirection > 3) intDirection %= 4;
		direction = (DIRECTIONS)intDirection;
		updateHeadPosition(head);
	}
	intDirection = prevDirection;
	if (!board->isInBoard(head)) {
		head.x = hx;
		head.y = hy;
		intDirection--;
		if (intDirection < 0) intDirection = 3;
		direction = (DIRECTIONS)intDirection;
		updateHeadPosition(head);
	}
}

void Snake::updateHeadPosition(SDL_Rect& head) {
	switch (direction)
	{
	case Snake::DIRECTIONS::UP:
		head.y -= head.h;
		break;
	case Snake::DIRECTIONS::DOWN:
		head.y += head.h;
		break;
	case Snake::DIRECTIONS::RIGHT:
		head.x += head.w;
		break;
	case Snake::DIRECTIONS::LEFT:
		head.x -= head.w;
		break;
	default:
		break;
	}
}

void Snake::changeDirection(DIRECTIONS direction) {
	this->direction = direction;
}

bool Snake::itSelfCollision() {

	Node<SDL_Rect>* temp = bodyParts.getHead()->next;
	while (temp)
	{
		SDL_Rect tempRect = temp->data;
		if (collision(temp->data)) return true;
		temp = temp->next;
	}
	return false;
}

bool Snake::collision(SDL_Rect& other) {
	SDL_Rect head = bodyParts.getHead()->data;
	if (((head.y >= other.y && head.y < other.y + other.h)
		|| (other.y >= head.y && other.y < head.y + head.h)) &&
		((head.x >= other.x && head.x < other.x + other.w)
			|| (other.x >= head.x && other.x < head.x + other.w))) return true;
	return false;	
}