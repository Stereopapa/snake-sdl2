#include "Board.h"
#include <stdio.h>
#include <string.h>
#include "AssetsPaths.h"

#define PROGGRES_BAR_SCALE 20


Board::Board(SDL_Renderer* renderTarget, int x, int y, int width, int height){
	border.x = x;
	border.y = y;
	border.w = width;
	border.h = height;
	bluePoint = new Point(renderTarget, Assets::BLUE_DOT_PATH);
	redPoint = new Point(renderTarget, Assets::RED_DOT_PATH);
	bluePoint->respawn(border);
	redDotBar = new ProgressBar(PROGGRES_BAR_SCALE, RED_DOT_ACTIVE_TIME, x + 2, y - 50);
}

Board::~Board(){
	delete redDotBar;
	delete bluePoint;
	delete redPoint;
}

void Board::draw(SDL_Renderer* renderTarget) {
	SDL_SetRenderDrawColor(renderTarget, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderTarget, &border);
	
	bluePoint->draw(renderTarget);
	redPoint->draw(renderTarget);
	redDotBar->draw(renderTarget);
}

Point* Board::getRedPoint(){
	return redPoint;
}
Point* Board::getBluePoint() {
	return bluePoint;
}

SDL_Rect Board::getBorder() {
	return border;
}

bool Board::isInBoard(SDL_Rect& obj) {
	if (obj.x + obj.w >= border.x + border.w || obj.x <= border.x ||
		obj.y + obj.w >= border.y + border.h || obj.y <= border.y) return false;
	return true;
}

void Board::clearRedDot(){
	redDotBar->updateProgresBar(0);
	redPoint->hide();
}

void Board::handleRedDot(double switchValue) {
	if (switchValue == -1.0) {
		redPoint->respawn(border);
	}
	else if (switchValue == -2.0) {
		clearRedDot();
	}
	else if (switchValue == -3.0) return;
	else {	
		redDotBar->updateProgresBar(switchValue);
	}
}
