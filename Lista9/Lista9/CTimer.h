#ifndef CTIMER_H
#define CTIMER_H
#include <Windows.h>


using namespace std;

class CTimer {
private:
	bool b_started;
	LARGE_INTEGER li_start;
public:
	CTimer();
	~CTimer();
	void vStart();
	void vStop();
	double dGetPassedTime();
};

#endif
