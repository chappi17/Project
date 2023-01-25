#include "framework.h"
#include "Timer.h"

Timer* Timer::_instance = nullptr;
Timer::Timer()
{
	// 1초동안 CPU의 진동수를 반환하는 함수
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);

	// 현재 진동수 총합
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); // 0

	_timeScale = 1.0f / (double)_periodFrequency; // 10000
}

Timer::~Timer()
{
}

void Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime); // 10000
	// (지금까지 진동한 횟수 - 처음에 진동한 횟수) * ( 1 / 초당 진동한 횟수)
	// (10000 - 0) * ( 1 / 10000) -> Update 한번에 걸린 시간 : 1초 -> Delta Time

	if (_lockFPS != 0)
	{
		while (_timeElased < (1.0f / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			// 딱 한 프레임만큼 경과한 시간
			_timeElased = (double)(_curTime - _lastTime) * _timeScale;
		}
	}
	else
	{
		_timeElased = (double)(_curTime - _lastTime) * _timeScale;
	}

	_lastTime = _curTime;

	_frameCount++; // -> FPS
	_oneSecCount += _timeElased; // timeElased : Update한번에 경과된 시간 = Delta Time

	// 1초마다 갱신해야되는 정보
	if (_oneSecCount >= 1)
	{
		_frameRate = _frameCount;
		// frameRate : FPS (Frame Per Second)
		_frameCount = 0;
		_oneSecCount = 0;
	}

	// 총 경과된 시간
	_runTime += _timeElased;
}
