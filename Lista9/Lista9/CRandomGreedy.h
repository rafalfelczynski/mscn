#ifndef CRANDGREEDY_H
#define CRANDGREEDY_H
#include "COptimizer.h"

namespace greedy {
	const double MAX_TIME = 5;
}
const double LAMBDA_MIN = 0;
const double LAMBDA_MAX = 5;
const double RELEVANCE_LIMIT = 0.01;

template<typename T>
class CRandomGreedy : public COptimizer<T> {
private:
	int i_seed;
	virtual void v_generate_xs(T* ptSolution, int iSize, CMySmartPointer<pair<T, T>>& pcRanges);
	void v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize);
	void v_search();
public:
	CRandomGreedy(CProblem<T>* cProblem, int iSeed);
	~CRandomGreedy();
	void vOptimise();
	bool bCheckStop();
	void vPrepare();
	T& dGetBestResult();
	T* pdGetCurrentBestSolution();
};

#endif

template<typename T>
CRandomGreedy<T>::CRandomGreedy(CProblem<T>* cProblem, int iSeed) {
	this->c_problem = cProblem;
	i_seed = iSeed;
	this->pd_current_best_sol = new T[this->c_problem->iGetResultSize()];
	for (int i = 0; i < this->c_problem->iGetResultSize(); i++) {
		this->pd_current_best_sol[i] = T();
	}//for
}//CRandomGreedy<T>::CRandomGreedy(CProblem<T>* cProblem, int iSeed)

template<typename T>
CRandomGreedy<T>::~CRandomGreedy() {
	if (DEBUG) {
		cout << "usuwam randoma" << endl;
	}//if
}//CRandomGreedy<T>::~CRandomGreedy()

template<typename T>
void CRandomGreedy<T>::vPrepare() {
	//do nothing
}//void CRandomSearch<T>::vPrepare()

template<typename T>
bool CRandomGreedy<T>::bCheckStop() {
	return this->c_timer.dGetPassedTime() >= greedy::MAX_TIME;
}//bool CRandomGreedy<T>::bCheckStop()

template<typename T>
T& CRandomGreedy<T>::dGetBestResult() {
	return this->d_current_best_fitness;
}//T& CRandomGreedy<T>::dGetBestResult() 

template<typename T>
T* CRandomGreedy<T>::pdGetCurrentBestSolution() {
	return this->pd_current_best_sol;
}//T* CRandomGreedy<T>::pdGetCurrentBestSolution()

template<>
void CRandomGreedy<double>::vOptimise() {
	int i_size = this->c_problem->iGetResultSize();
	double* pt_solution = new double[i_size];
	CMySmartPointer<pair<double, double>> pc_ranges = this->c_problem->pcCheckRange(i_size);
	v_generate_xs(pt_solution, i_size, pc_ranges);
	CRandom c_rand;
	this->c_timer.vStart();
	while (!bCheckStop()) {
		for (int i = 0; i < i_size; i++) {
			double d_lambda = c_rand.dNextDouble(LAMBDA_MIN, LAMBDA_MAX);
			double d_cur_qual, d_plus_qual, d_minus_qual;
			double d_xi_start;
			do {
				d_xi_start = pt_solution[i];
				d_cur_qual = this->c_problem->tGetQuality(pt_solution, i_size);
				pt_solution[i] += d_lambda;
				if(pt_solution[i] > pc_ranges.rtAt(i).second) {
					pt_solution[i] = pc_ranges.rtAt(i).second;
				}//if
				d_plus_qual = this->c_problem->tGetQuality(pt_solution, i_size);
				pt_solution[i] = d_xi_start - d_lambda;
				if (pt_solution[i] < pc_ranges.rtAt(i).first) {
					pt_solution[i] = pc_ranges.rtAt(i).first;
				}//if
				d_minus_qual = this->c_problem->tGetQuality(pt_solution, i_size);
				if (d_minus_qual < d_plus_qual && d_plus_qual > d_cur_qual) {
					pt_solution[i] = d_xi_start + d_lambda;
					this->d_current_best_fitness = d_plus_qual;
				}//if
				else if (d_minus_qual > d_plus_qual && d_minus_qual > d_cur_qual) {
					pt_solution[i] = d_xi_start - d_lambda;
					this->d_current_best_fitness = d_minus_qual;
				}//else if
				else {
					pt_solution[i] = d_xi_start;
					this->d_current_best_fitness = d_cur_qual;
				}//else
			} while (abs(d_cur_qual - d_plus_qual) > RELEVANCE_LIMIT && abs(d_cur_qual - d_minus_qual) > RELEVANCE_LIMIT);
		}//for
		v_copy_table(&this->pd_current_best_sol, pt_solution, i_size);
	}//while
	this->c_timer.vStop();
	delete[] pt_solution;
}//void CRandomGreedy<double>::vOptimise()

template<>
void CRandomGreedy<double>::v_generate_xs(double* ptSolution, int iSize, CMySmartPointer<pair<double, double>>& pcRanges) {
	CRandom c_rand;
	for (int i = 0; i < iSize; i++) {
		ptSolution[i] = c_rand.dNextDouble(((pair<double, double>)pcRanges.rtAt(i)).first, ((pair<double, double>)pcRanges.rtAt(i)).second);
	}//for
}//void CRandomGreedy<double>::v_generate_xs(double* ptSolution, int iSize, CMySmartPointer<pair<double, double>>& pcRanges) 

template<typename T>
void CRandomGreedy<T>::v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize) {
	T* pt_new = new T[iSize];
	for (int i = 0; i < iSize; i++) {
		pt_new[i] = ptTabToBeCopied[i];
	}//for
	delete[](*ptCopy);
	*ptCopy = pt_new;
}//void CRandomGreedy<T>::v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize)

