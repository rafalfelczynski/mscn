#ifndef CRANDOM_H
#define CRANDOM_H
#include <random>

using namespace std;

class CRandom {
private:
	random_device c_seed;
	mt19937_64 c_gen;
	uniform_int_distribution<> ci_distr;
	uniform_real_distribution<> cd_distr;
public:
	CRandom();
	CRandom(int iSeed);
	~CRandom();
	int iNextInt(int iMin, int iMax);
	double dNextDouble(double dMin, double dMax);
	void vSetSeed(int iSeed);
};


#endif
