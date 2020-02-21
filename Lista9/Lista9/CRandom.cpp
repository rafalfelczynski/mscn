#include "CRandom.h"

CRandom::CRandom() {
        c_gen.seed(c_seed());
}

CRandom::CRandom(int iSeed) {
        vSetSeed(iSeed);
}
CRandom::~CRandom() {

}
int CRandom::iNextInt(int iMin, int iMax) {
        return ci_distr(c_gen, uniform_int_distribution<int>::param_type(iMin, iMax));
}
double CRandom::dNextDouble(double dMin, double dMax) {
        return cd_distr(c_gen, uniform_real_distribution<double>::param_type(dMin, dMax));
}
void CRandom::vSetSeed(int iSeed) {
        c_gen.seed(iSeed);
}