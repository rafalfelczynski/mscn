#include "CTimer.h"


CTimer::CTimer() {
        b_started = false;
}//CTimer::CTimer()

CTimer::~CTimer() {}

void CTimer::vStart() {
        if (!b_started) {
                b_started = true;
                QueryPerformanceCounter(&li_start);
        }//if
}//void CTimer::vStart()

void CTimer::vStop() {
        b_started = false;
}//void CTimer::vStop()

double CTimer::dGetPassedTime() {
        if (b_started) {
                LARGE_INTEGER li_sec;
                QueryPerformanceFrequency(&li_sec);
                LARGE_INTEGER li_now;
                QueryPerformanceCounter(&li_now);
                return (li_now.QuadPart - li_start.QuadPart) / li_sec.QuadPart;
        }//if
        else {
                return 0;
        }//else
}//double CTimer::dGetPassedTime()