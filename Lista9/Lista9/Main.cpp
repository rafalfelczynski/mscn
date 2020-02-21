#include <iostream>
#include "CMscnProblem.h"
#include "CRandom.h"
#include "CRandomSearch.h"
#include <time.h>
#include "CDiffEvol.h"
#include "CRandomGreedy.h"
using namespace std;

void v_test() {      
        string s_filename = "inst.txt";
        CMscnProblem c_prob2(2,3,3,5);
        c_prob2.bReadFromFile(s_filename);
        string s_filename3 = "inst3.txt";
        c_prob2.bSaveToFile(s_filename3);
        CMscnProblem* c_prob3 = new CMscnProblem(c_prob2);
        CRandomSearch<double> c_search(c_prob3, 1);
        c_prob3->vGenerateInstance(1);
        c_search.vOptimise();
        cout << "end of random search" << endl;
        double* pd_solu = c_search.pdGetCurrentBestSolution();
        cout << "res: " << c_prob3->tGetQuality(pd_solu,c_prob3->iGetResultSize())<< endl;
        COptimizer<double>& c_diff_evol = *new CDiffEvol<double>(c_prob3, 0.8, 0.1, 100);
        c_diff_evol.vPrepare();
        c_diff_evol.vOptimise();
        double* d_rozw = c_diff_evol.pdGetCurrentBestSolution();
        cout << "res2: "<< c_prob3->tGetQuality(d_rozw, c_prob3->iGetResultSize()) << endl;
        cout << "everything ok? 0 - yes: " << c_prob3->vConstraintSatisfied(d_rozw, c_prob3->iGetResultSize())[0] << endl;
        COptimizer<double>& c_greedy = *new CRandomGreedy<double>(c_prob3, 1);
        c_greedy.vOptimise();
        cout << "res3: " << c_greedy.dGetBestResult() << endl;
        c_prob3->bSaveToFile("result_inst.txt");
        c_prob3->bSaveResult("result.txt", d_rozw);
        delete c_prob3;
        delete[] pd_solu;
        delete &c_diff_evol;
}

int main(void) {
        v_test();
        return 0;
}