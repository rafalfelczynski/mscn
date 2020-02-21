#ifndef CRANDOMSEARCH_H
#define CRANDOM_SEARCH_H
#include "CMySmartPointer.h"
#include "CProblem.h"
#include "COptimizer.h"

const double MAX_TIME = 5;
const int FINISH_COND_COUNTER = 10000;

template<typename T>
class CRandomSearch : public COptimizer<T> {
private:
	int i_seed;
	virtual void v_generate_xs(T* ptSolution, int iSize, CMySmartPointer<pair<T, T>>& pcRanges);
	void v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize);
	void v_search();
public:
	CRandomSearch(CProblem<T>* cProblem, int iSeed);
	~CRandomSearch();
	void vOptimise();
	bool bCheckStop();
	void vPrepare();
	T& dGetBestResult();
	T* pdGetCurrentBestSolution();
};

template<typename T>
CRandomSearch<T>::CRandomSearch(CProblem<T>* cProblem, int iSeed) {
	this->c_problem = cProblem;
	i_seed = iSeed;
	this->pd_current_best_sol = new T[this->c_problem->iGetResultSize()];
	for (int i = 0; i < this->c_problem->iGetResultSize(); i++) {
		this->pd_current_best_sol[i] = T();
	}//for
}//CRandomSearch<T>::CRandomSearch(CProblem<T>* cProblem, int iSeed)

template<typename T>
CRandomSearch<T>::~CRandomSearch() {
	if (DEBUG) {
		cout << "usuwam randoma" << endl;
	}//if
	CRandom c_rand;
}//CRandomSearch<T>::~CRandomSearch()

template<typename T>
void CRandomSearch<T>::vPrepare() {
	//do nothing
}//void CRandomSearch<T>::vPrepare()

template<typename T>
void CRandomSearch<T>::v_search() {
	this->c_timer.vStart();
	int i_size = this->c_problem->iGetResultSize();
	int i_counter = 0;
	T d_result;
	T* pt_solution = new T[i_size];
	CMySmartPointer<pair<T, T>> pc_ranges = this->c_problem->pcCheckRange(i_size);
	v_generate_xs(pt_solution, i_size, pc_ranges);
	T d_current_best = this->c_problem->tGetQuality(pt_solution, i_size);;
	while (!bCheckStop()) {
		v_generate_xs(pt_solution, i_size, pc_ranges);
		d_result = this->c_problem->tGetQuality(pt_solution, i_size);
		
		if (d_result > this->d_current_best_fitness) {
			v_copy_table(&this->pd_current_best_sol, pt_solution, i_size);
			if (DEBUG) {
				cout << "eureka" << endl;
			}//if
			this->d_current_best_fitness = d_result;
		}//if
		i_counter++;
	}//while
	this->c_timer.vStop();
	delete[] pt_solution;
}//void CRandomSearch<T>::v_search()

template<typename T>
void CRandomSearch<T>::vOptimise(){
	v_search();
}//void CRandomSearch<T>::vOptimise()

template<typename T>
bool CRandomSearch<T>::bCheckStop(){
	return this->c_timer.dGetPassedTime() >= MAX_TIME;
}//bool CRandomSearch<T>::bCheckStop()

template<typename T>
T& CRandomSearch<T>::dGetBestResult(){
	return this->d_current_best_fitness;
}//T& CRandomSearch<T>::dGetBestResult()

template<typename T>
T * CRandomSearch<T>::pdGetCurrentBestSolution(){
	return this->pd_current_best_sol;
}//T * CRandomSearch<T>::pdGetCurrentBestSolution()

template<typename T>
void CRandomSearch<T>::v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize) {
	T* pt_new = new T[iSize];
	for (int i = 0; i < iSize; i++) {
		pt_new[i] = ptTabToBeCopied[i];
	}//for
	delete[] (*ptCopy);
	*ptCopy = pt_new;
}//void CRandomSearch<T>::v_copy_table(T** ptCopy, T* ptTabToBeCopied, int iSize)

template<>
void CRandomSearch<int>::v_generate_xs(int* ptSolution, int iSize, CMySmartPointer<pair<int, int>>& pcRanges) {
	CRandom c_rand;
	for (int i = 0; i < iSize; i++) {
		ptSolution[i] = c_rand.iNextInt(((pair<int, int>)pcRanges.rtAt(i)).first, ((pair<int, int>)pcRanges.rtAt(i)).second);
	}//for
}//void CRandomSearch<int>::v_generate_xs(int* ptSolution, int iSize, CMySmartPointer<pair<int, int>>& pcRanges)


template<>
void CRandomSearch<double>::v_generate_xs(double* ptSolution, int iSize, CMySmartPointer<pair<double, double>>& pcRanges) {
	CRandom c_rand;
	for (int i = 0; i < iSize; i++) {
		ptSolution[i] = c_rand.dNextDouble(((pair<double, double>)pcRanges.rtAt(i)).first, ((pair<double, double>)pcRanges.rtAt(i)).second);
	}//for
}//void CRandomSearch<double>::v_generate_xs(double* ptSolution, int iSize, CMySmartPointer<pair<double, double>>& pcRanges)



#endif