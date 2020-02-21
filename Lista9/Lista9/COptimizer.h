#ifndef COPTIMIZER_H
#define COPTIMIZER_H
#include "CTimer.h"
#include "CProblem.h"

template<typename T>
class COptimizer {
protected:
	CTimer c_timer;
	CProblem<T>* c_problem;
	T d_current_best_fitness;
	T* pd_current_best_sol;
public:
	COptimizer() {};
	virtual ~COptimizer() {};
	virtual void vPrepare() =0;
	virtual void vOptimise() =0;
	virtual bool bCheckStop() =0;
	virtual T& dGetBestResult() =0;
	virtual T* pdGetCurrentBestSolution() =0;
};

#endif
