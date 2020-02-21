#ifndef CPROBLEM_H
#define CPROBLEM_H
#include "CMySmartPointer.h"

template<typename T>
class CProblem {
public:
	virtual ~CProblem() {};
	virtual void vGenerateInstance(int iInstanceSeed) =0;
	virtual CMySmartPointer<pair<T, T>> pcCheckRange(int iSize) =0;
	virtual int iGetResultSize() =0;
	virtual T tGetQuality(T* ptSolution, int iSize) =0;
};


#endif