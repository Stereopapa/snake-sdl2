#pragma once
class Timer
{
public:
	Timer(double snakeMoveTime, double timeToSpeedup,
		double redDotActiveTime);
	~Timer();
	void update();
	int getFps();
	double getDTime();
	double getWorldTime();
	bool snakeMove();
	double redDot();
	void startRedDot();
	void mulitplySnakeTimeToMove(double value);
	void startTimer();
private:
	//time
	int currentTime;
	int previousTime;
	double dTime;
	double worldTime;
	//frames
	int frames;
	int fps;
	double fpsTimer;
	//snake movement
	double snakeTimePassed;
	double snakeTimeToMove;
	double snakeBaseTimeToMove;
	//speed up
	double speedupTimePassed;
	double timeToSpeedup;
	//red dot
	double timeToRedDot;
	double redDotActiveTime;
	double redDotTimePassed;
};	
