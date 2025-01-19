#include "Game.h"

Game::Game(SDL_Renderer* renderer, int sw, int sh){
	info = new Info(renderer, 10, 10, sw - 20, 42);
	board = new Board(renderer, 10, 80, sw - 20, sh - 90);
	timer = new Timer(SNAKE_TIME_TO_MOVE, TIME_TO_SPEEDUP, RED_DOT_ACTIVE_TIME);
	snake = new Snake();
}

void Game::startGame() {
	state = STATES::PLAYING;
	SDL_Rect border = board->getBorder();
	points = 0;
	snake->initBody(border.x, border.y);
	timer->startTimer();
	info->switchEndGameInfo(false);
	board->clearRedDot();
}

Game::~Game(){
	delete info;
	delete board;
	delete timer;
	delete snake;
}

void Game::renderFrame(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	info->draw(renderer, timer->getFps(), timer->getWorldTime(), points);

	if (state == STATES::PLAYING) {
		board->draw(renderer);
		snake->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}
void Game::generateFrame() {
	if (state != STATES::PLAYING) return;
	timer->update();
	if (timer->snakeMove()) {
		snake->updatePosition(board,timer, points);
		if (snake->itSelfCollision()) {
			state = STATES::LOOSE;
			info->switchEndGameInfo(true);
		}
	}
	board->handleRedDot(timer->redDot());
}

enum Game::STATES Game::getState() {
	return state;
}

bool Game::playing() {
	if (state == STATES::PLAYING) return true;
	else return false;
}

void Game::handleControl(SDL_Event& event) {
	// obs³uga zdarzeñ (o ile jakieœ zasz³y) / handling of events (if there were any)
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				state = STATES::QUIT;
			case SDLK_UP:
				snake->changeDirection(Snake::DIRECTIONS::UP);
				break;
			case SDLK_DOWN:
				snake->changeDirection(Snake::DIRECTIONS::DOWN);
				break;
			case SDLK_LEFT:
				snake->changeDirection(Snake::DIRECTIONS::LEFT);
				break;
			case SDLK_RIGHT:
				snake->changeDirection(Snake::DIRECTIONS::RIGHT);
				break;
			case SDLK_n:
				if(state == STATES::LOOSE) startGame();
			default:
				break;
			}
			break;
		case SDL_KEYUP:
			break;
		case SDL_QUIT:
			state = STATES::QUIT;
			break;
		};
	};
}

bool Game::quit() {
	if (state == STATES::QUIT) return true;
	else return false;
}