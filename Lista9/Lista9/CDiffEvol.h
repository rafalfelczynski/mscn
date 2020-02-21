#ifndef CDIFFEVOL_H
#define CDIFFEVOL_H
#include "CProblem.h"
#include "CRandom.h"
#include "COptimizer.h"

const int ZERO_POPULATION_ERROR = -1;
const int TOURNAMENT_SIZE = 3;

namespace CDiff {
	const double MAX_TIME = 3;
}

template<typename T>
class CIndividual {
private:
	CMySmartPointer<T> pd_solution;
	T d_fitness;
public:
	CIndividual();
	~CIndividual();
	void operator=(const CIndividual<T>& rcOther);
	bool operator==(const CIndividual<T>& rcOther);
	bool operator!=(const CIndividual<T>& rcOther);
	T* pdGetSolution();
	T dGetGene(int iOffset);
	void vSetGene(int iOffset, T dVal);
	void vSetFitness(T dFitness);
	T dGetFitnessVal();
	int iGetSize();
	void vSetSolution(T* pdSolution, int iSize);
};

template<typename T>
class CDiffEvol : public COptimizer<T> {
private:
	double d_diff_weight;
	CRandom c_rand;
	double d_cross_prob;
	int i_pop_size;
	CMySmartPointer<CIndividual<T>> pc_population;
	bool b_ind_are_diff(CIndividual<T>& cInd, CIndividual<T>& cBaseInd, CIndividual<T>& cInd0, CIndividual<T>& CInd1);
	double d_get_random_real(double dLow, double dHigh);
	T d_calc_fitness(CIndividual<T>& cInd);
	T* pd_generate_random_genes(CMySmartPointer<pair<T, T>>& pc_ranges, int iSize);
public:
	CDiffEvol(CProblem<T>* cProblem, double dCrossProb, double dDiffWeight, int iPopSize);
	CDiffEvol(CProblem<T>* cProblem, int iPopSize);
	~CDiffEvol();
	void vPrepare();
	void vInitPopulation(int iSize);
	void vOptimise();
	bool bCheckStop();
	void vSetCrossProb(double dCrossProb);
	void vSetDiffWeight(double dDiffWeight);
	CIndividual<T>& cGetRandomInd();
	CIndividual<T>& cGetRandomIndTournament(int iSize);
	T& dGetBestResult();
	T* pdGetCurrentBestSolution();
};

#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////IMPLEMENTACJA://////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T> CDiffEvol<T>::CDiffEvol(CProblem<T>* cProblem, double dCrossProb, double dDiffWeight, int iPopSize) {
	this->c_problem = cProblem;
	d_cross_prob = dCrossProb;
	d_diff_weight = dDiffWeight;
	i_pop_size = iPopSize;
	this->d_current_best_fitness = NULL;
	this->pd_current_best_sol = NULL;
}//CDiffEvol::CDiffEvol(CProblem<double>* cProblem, double dCrossProb, double dDiffWeight)

template<typename T> CDiffEvol<T>::CDiffEvol(CProblem<T>* cProblem, int iPopSize){
	this->c_problem = cProblem;
	d_cross_prob = 0;
	d_diff_weight = 0;
	i_pop_size = iPopSize;
	this->d_current_best_fitness = NULL;
	this->pd_current_best_sol = NULL;
}//CDiffEvol::CDiffEvol(CProblem<double>* cProblem)

template<typename T> CDiffEvol<T>::~CDiffEvol() {}

template<typename T>
void CDiffEvol<T>::vPrepare(){
	vInitPopulation(i_pop_size);
}//void CDiffEvol<T>::vPrepare()

template<typename T> bool CDiffEvol<T>::b_ind_are_diff(CIndividual<T>& cInd, CIndividual<T>& cBaseInd, CIndividual<T>& cInd0, CIndividual<T>& cInd1) {
	return cInd != cBaseInd && cInd != cInd0 && cInd != cInd1 
		&& cBaseInd != cInd0 && cBaseInd != cInd1 
		&& cInd0 != cInd1;
}//bool CDiffEvol::b_ind_are_diff(CIndividual& cInd, CIndividual& cBaseInd, CIndividual& cInd0, CIndividual& cInd1)

template<typename T> bool CDiffEvol<T>::bCheckStop() {
	return this->c_timer.dGetPassedTime() >= CDiff::MAX_TIME;
}//bool CDiffEvol::bCheckStop()

template<typename T> void CDiffEvol<T>::vSetCrossProb(double dCrossProb){
	d_cross_prob = dCrossProb;
}//void CDiffEvol::vSetCrossProb(double dCrossProb)

template<typename T> void CDiffEvol<T>::vSetDiffWeight(double dDiffWeight){
	d_diff_weight = dDiffWeight;
}//void CDiffEvol::vSetDiffWeight(double dDiffWeight)

template<typename T> CIndividual<T>& CDiffEvol<T>::cGetRandomInd() {
	int i_index = c_rand.iNextInt(0, pc_population.iGetTabSize() - 1);
	return pc_population.rtAt(i_index);
}//CIndividual& CDiffEvol::cGetRandomInd()

template<typename T> T& CDiffEvol<T>::dGetBestResult() {
	return this->d_current_best_fitness;
}//double CDiffEvol::dGetBestResult()

template<typename T> CIndividual<T>& CDiffEvol<T>::cGetRandomIndTournament(int iSize) {
	CIndividual<T>* c_best = &cGetRandomInd();
	if (iSize > 0) {
		double d_best_fitness = d_calc_fitness(*c_best);
		double d_current_fitness = d_best_fitness;
		for (int i = 0; i < iSize; i++) {
			int i_index = c_rand.iNextInt(0, pc_population.iGetTabSize() - 1);
			if ((d_current_fitness = d_calc_fitness(pc_population.rtAt(i_index))) > d_best_fitness) {
				d_best_fitness = d_current_fitness;
				c_best = &pc_population.rtAt(i_index);
			}//if
		}//for
	}//if
	return *c_best;
}//CIndividual& CDiffEvol::cGetRandomIndTournament(int iSize)

template<typename T> void CDiffEvol<T>::vOptimise() {
	if (DEBUG) {
		cout << "cDiffevol optimise" << endl;
	}
	this->c_timer.vStart();
	int i_genesize = this->c_problem->iGetResultSize();
	CMySmartPointer<pair<double, double>> pc_ranges = this->c_problem->pcCheckRange(i_genesize);
	while (!bCheckStop()) {
		for (int i = 0; i < pc_population.iGetTabSize(); i++) {
			CIndividual<T>& c_ind = pc_population.rtAt(i);
			CIndividual<T>& c_base_ind = cGetRandomIndTournament(TOURNAMENT_SIZE);
			CIndividual<T>& c_ind0 = cGetRandomIndTournament(TOURNAMENT_SIZE);
			CIndividual<T>& c_ind1 = cGetRandomIndTournament(TOURNAMENT_SIZE);
			if (b_ind_are_diff(c_ind, c_base_ind, c_ind0, c_ind1)) {
				CIndividual<T> c_ind_new;
				c_ind_new.vSetSolution(pd_generate_random_genes(pc_ranges, i_genesize), i_genesize);
				for (int j = 0; j < c_ind.iGetSize(); j++) {
					if (d_get_random_real(0, 1) < d_cross_prob) {
						double d_new_val = (c_base_ind.dGetGene(j) + d_diff_weight * (c_ind0.dGetGene(j) - c_ind1.dGetGene(j)));
						c_ind_new.vSetGene(j, d_new_val <= pc_ranges.rtAt(j).first ? pc_ranges.rtAt(j).first : (d_new_val >= pc_ranges.rtAt(j).second ? pc_ranges.rtAt(j).second : d_new_val));
					}//if
					else {
						c_ind_new.vSetGene(j, c_ind.dGetGene(j));
					}//else
				}//for
				double d_fitness = d_calc_fitness(c_ind_new);
				c_ind_new.vSetFitness(d_fitness);
				if (d_fitness > c_ind.dGetFitnessVal()) {
					c_ind = c_ind_new;
					if (d_fitness > this->d_current_best_fitness) {
						this->pd_current_best_sol = c_ind_new.pdGetSolution();
						this->d_current_best_fitness = d_fitness;
						if (DEBUG) {
							printf("current best: %.30f\n", this->d_current_best_fitness);
						}//if
					}//if
				}//if
				
			}//if
		}//for
	}//while
	this->c_timer.vStop();
}//void CDiffEvol::vOptimise()

template<typename T> T* CDiffEvol<T>::pdGetCurrentBestSolution() {
	return this->pd_current_best_sol;
}//double* CDiffEvol::pdGetCurrentBestSolution()

template<typename T> T CDiffEvol<T>::d_calc_fitness(CIndividual<T>& cInd) {
	return this->c_problem->tGetQuality(cInd.pdGetSolution(), cInd.iGetSize());
}//double CDiffEvol::d_calc_fitness(CIndividual& cInd)

template<typename T> double CDiffEvol<T>::d_get_random_real(double dLow, double dHigh) {
	return c_rand.dNextDouble(dLow, dHigh);
}//double CDiffEvol::d_get_random_real(double dLow, double dHigh)

template<typename T> void CDiffEvol<T>::vInitPopulation(int iSize) {
	int i_genesize = this->c_problem->iGetResultSize();
	CIndividual<T>* c_inds = new CIndividual<T>[iSize];
	CMySmartPointer<pair<double, double>> pc_ranges = this->c_problem->pcCheckRange(i_genesize);
	for (int i = 0; i < iSize; i++) {
		c_inds[i].vSetSolution(pd_generate_random_genes(pc_ranges, i_genesize), i_genesize);
		c_inds[i].vSetFitness(this->c_problem->tGetQuality(c_inds[i].pdGetSolution(), c_inds[i].iGetSize()));
	}//for
	pc_population.assign(c_inds, iSize);
}//void CDiffEvol::vInitPopulation(int iSize)

template<typename T> T* CDiffEvol<T>::pd_generate_random_genes(CMySmartPointer<pair<T, T>>& pc_ranges, int iSize) {
	T* pd_sol = new T[iSize];
	for (int i = 0; i < iSize; i++) {
		pd_sol[i] = c_rand.dNextDouble(pc_ranges.rtAt(i).first, pc_ranges.rtAt(i).second);
	}//for
	return pd_sol;
}//double* CDiffEvol::pd_generate_random_genes(CMySmartPointer<pair<double, double>>& pc_ranges, int iSize)

template<typename T> CIndividual<T>::CIndividual() {}

template<typename T> CIndividual<T>::~CIndividual() {}

template<typename T> void CIndividual<T>::vSetFitness(T dFitness) {
	d_fitness = dFitness;
}//void CIndividual::vSetFitness(double dFitness)

template<typename T> T CIndividual<T>::dGetFitnessVal() {
	return d_fitness;
}//double CIndividual::dGetFitnessVal()

template<typename T> void CIndividual<T>::operator=(const CIndividual<T>& rcOther) {
	pd_solution = rcOther.pd_solution;
	d_fitness = rcOther.d_fitness;
}//void CIndividual::operator=(const CIndividual& rcOther)

template<typename T> bool CIndividual<T>::operator==(const CIndividual<T>& rcOther) {
	return this == &rcOther;
}//bool CIndividual::operator==(const CIndividual& rcOther)

template<typename T> bool CIndividual<T>::operator!=(const CIndividual<T>& rcOther) {
	return !operator==(rcOther);
}//bool CIndividual::operator!=(const CIndividual& rcOther)

template<typename T> T* CIndividual<T>::pdGetSolution() {
	return pd_solution.operator->();
}//double* CIndividual::pdGetSolution()

template<typename T> void CIndividual<T>::vSetGene(int iOffset, T dVal) {
	if (iOffset >= 0 && iOffset < pd_solution.iGetTabSize()) {
		pd_solution.vSet(dVal, iOffset);
	}//if
}//void CIndividual::vSetGene(int iOffset, double dVal)

template<typename T> T CIndividual<T>::dGetGene(int iOffset) {
	return pd_solution.rtAt(iOffset);
}//double CIndividual::dGetGene(int iOffset)

template<typename T> int CIndividual<T>::iGetSize(){
	return pd_solution.iGetTabSize();
}//int CIndividual::iGetSize()

template<typename T> void CIndividual<T>::vSetSolution(T* pdSolution, int iSize) {
	pd_solution.assign(pdSolution, iSize);
}//void CIndividual::vSetSolution(double* pdSolution, int iSize)
