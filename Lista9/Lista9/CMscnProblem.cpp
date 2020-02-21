#include "CMscnProblem.h"
#include <vector>
#include <iomanip>
#include "CFileErrCode.h"
#include "CRandom.h"

////////////////////////////////////
//CAbstractUnit

void CAbstractUnit::vSetName(string& sName) {
        s_name = sName;
}//void CAbstractUnit::vSetName(string sName)

string& CAbstractUnit::sGetName() {
        return s_name;
}//string CAbstractUnit::sGetName()

void CAbstractUnit2::vSetCosts(CMySmartPointer<double>& cdCosts) {
        pd_costs = cdCosts;
}//void CAbstractUnit2::vSetCosts(CMySmartPointer<double>& cdCosts)

CMySmartPointer<double>& CAbstractUnit2::cdGetCosts() {
        return pd_costs;
}//CMySmartPointer<double>& CAbstractUnit2::cdGetCosts()

void CAbstractUnit2::vSetCost(double dCost, int iOffset) {
        pd_costs.vSet(dCost, iOffset);
}//void CAbstractUnit2::vSetCost(double dCost, int iOffset)

double CAbstractUnit2::dGetCost(int iOffset) {
        return pd_costs.rtAt(iOffset);
}//double CAbstractUnit2::dGetCost(int iOffset)

void CAbstractUnit2::vSetXMax(int iOffset, double dXMax) {
        pd_x_max.vSet(dXMax, iOffset);
}//void CAbstractUnit2::vSetXMax(double iXMax)

void CAbstractUnit2::vSetXMin(int iOffset,double dXMin) {
        pd_x_min.vSet(dXMin, iOffset);
}//void CAbstractUnit2::vSetXMin(double iXMin)

double CAbstractUnit2::dGetXMax(int iOffset) {
        return pd_x_max.rtAt(iOffset);
}//double CAbstractUnit2::dGetXMax()

double CAbstractUnit2::dGetXMin(int iOffset) {
        return pd_x_min.rtAt(iOffset);
}//double CAbstractUnit2::dGetXMin()

double CAbstractUnit2::dGetU() {
        return d_u;
}//double CAbstractUnit2::dGetU()

void CAbstractUnit2::vSetU(double dU) {
        d_u = dU;
}//void CAbstractUnit2::vSetU(double dU)


double CAbstractUnit2::dPrintCosts() {
        double d_res=0;
        for (int i = 0; i < pd_costs.iGetTabSize(); i++) {
                d_res += pd_costs.rtAt(i);
        }//for
        return d_res;
}//double CAbstractUnit2::dPrintCosts()





////////////////////////////////////
//CMscnProblem

CMscnProblem::CMscnProblem(int iNumOfSup, int iNumOfFac, int iNumOfWare, int iNumOfSh) {
        if (DEBUG) {
                cout << "CMSCN constructor v1.0" << endl;
        }//if
        i_num_of_sup = iNumOfSup;
        i_num_of_fac = iNumOfFac;
        i_num_of_ware = iNumOfWare;
        i_num_of_sh = iNumOfSh;
}//CMscnProblem::CMscnProblem(int iNumOfSup, int iNumOfFac, int iNumOfWare, int iNumOfSh)

CMscnProblem::CMscnProblem(CMySmartPointer<CSupplier>* pcSups, int iNumOfSup, CMySmartPointer<CFactory>* pcFacs, int iNumOfFac, CMySmartPointer<CWarehouse>* pcWares, int iNumOfWare, CMySmartPointer<CShop>* pcShops, int iNumOfSh) {
        if (DEBUG) {
                cout << "CMSCN constructor v2.0" << endl;
        }//if
        c_suppliers.assign(pcSups, iNumOfSup);
        c_factories.assign(pcFacs, iNumOfFac);
        c_warehouses.assign(pcWares, iNumOfWare);
        c_shops.assign(pcShops, iNumOfSh);
        i_num_of_sup = iNumOfSup;
        i_num_of_fac = iNumOfFac;
        i_num_of_ware = iNumOfWare;
        i_num_of_sh = iNumOfSh;
}//CMscnProblem::CMscnProblem(CMySmartPointer<CSupplier>* pcSups, int iNumOfSup, CMySmartPointer<CFactory>* pcFacs, int iNumOfFac, CMySmartPointer<CWarehouse>* pcWares, int iNumOfWare, CMySmartPointer<CShop>* pcShops, int iNumOfSh)


CMscnProblem::CMscnProblem(const CMscnProblem& rcOther) {
        c_suppliers = rcOther.c_suppliers;
        c_factories = rcOther.c_factories;
        c_warehouses = rcOther.c_warehouses;
        c_shops = rcOther.c_shops;
        i_num_of_fac = rcOther.i_num_of_fac;
        i_num_of_sh = rcOther.i_num_of_sh;
        i_num_of_sup = rcOther.i_num_of_sup;
        i_num_of_ware = rcOther.i_num_of_ware;
}//CMscnProblem::CMscnProblem(const CMscnProblem& rcOther)

CMscnProblem::~CMscnProblem() {
        if (DEBUG) {
                cout << "usuwam cmscn problem" << endl;
        }//if
}//CMscnProblem::~CMscnProblem()

bool CMscnProblem::bCreateSups(string* sNames, int iNumOfSup) {
        if (iNumOfSup == i_num_of_sup) {
                CMySmartPointer<CSupplier>* c_sups = new CMySmartPointer<CSupplier>[iNumOfSup];
                for (int i = 0; i < iNumOfSup; i++) {
                        c_sups[i].assign(new CSupplier(sNames[i], i_num_of_fac), 0);
                }//for
                c_suppliers.assign(c_sups, iNumOfSup);
                return true;
        }//if
        else {
                return false;
        }//else
}// bool CMscnProblem::bCreateSups(string* sNames, double* dProdCaps, int iNumOfSup)

bool CMscnProblem::bCreateFacs(string* sNames, int iNumOfFac) {
        if (iNumOfFac == i_num_of_fac) {
                CMySmartPointer<CFactory>* c_sups = new CMySmartPointer<CFactory>[iNumOfFac];
                for (int i = 0; i < iNumOfFac; i++) {
                        c_sups[i].assign(new CFactory(sNames[i], i_num_of_ware), 0);
                }//for
                c_factories.assign(c_sups, iNumOfFac);
                return true;
        }//if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateFacs(string* sNames, double* dProdCaps, int iNumOfFac)


bool CMscnProblem::bCreateWares(string* sNames, int iNumOfWare) {
        if (iNumOfWare == i_num_of_ware) {
                CMySmartPointer<CWarehouse>* c_sups = new CMySmartPointer<CWarehouse>[iNumOfWare];
                for (int i = 0; i < iNumOfWare; i++) {
                        c_sups[i].assign(new CWarehouse(sNames[i], i_num_of_sh), 0);
                }//for

                c_warehouses.assign(c_sups, iNumOfWare);
                return true;

        }//if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateWares(string* sNames, double* dWareCaps, int iNumOfWare)

bool CMscnProblem::bCreateShops(string* sNames, int iNumOfSh) {

        if (iNumOfSh == i_num_of_sh) {
                CMySmartPointer<CShop>* c_sups = new CMySmartPointer<CShop>[iNumOfSh];
                for (int i = 0; i < iNumOfSh; i++) {
                        c_sups[i].assign(new CShop(sNames[i]), 0);
                }//for

                c_shops.assign(c_sups, iNumOfSh);
                return true;
        }// if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateShops(string* sNames, double* dPrices, double* dDemands, int iNumOfSh)

bool CMscnProblem::bCreateSups(int iNumOfSup) {
        if (iNumOfSup == i_num_of_sup) {
                CMySmartPointer<CSupplier>* c_sups = new CMySmartPointer<CSupplier>[iNumOfSup];
                for (int i = 0; i < iNumOfSup; i++) {
                        c_sups[i].assign(new CSupplier(i_num_of_fac), 0);
                }//for
                c_suppliers.assign(c_sups, iNumOfSup);
                return true;
        }//if
        else {
                return false;
        }//else
}// bool CMscnProblem::bCreateSups(string* sNames, double* dProdCaps, int iNumOfSup)

bool CMscnProblem::bCreateFacs(int iNumOfFac) {
        if (iNumOfFac == i_num_of_fac) {
                CMySmartPointer<CFactory>* c_sups = new CMySmartPointer<CFactory>[iNumOfFac];
                for (int i = 0; i < iNumOfFac; i++) {
                        c_sups[i].assign(new CFactory(i_num_of_ware), 0);
                }//for
                c_factories.assign(c_sups, iNumOfFac);
                return true;
        }//if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateFacs(string* sNames, double* dProdCaps, int iNumOfFac)


bool CMscnProblem::bCreateWares(int iNumOfWare) {
        if (iNumOfWare == i_num_of_ware) {
                CMySmartPointer<CWarehouse>* c_sups = new CMySmartPointer<CWarehouse>[iNumOfWare];
                for (int i = 0; i < iNumOfWare; i++) {
                        c_sups[i].assign(new CWarehouse(i_num_of_sh), 0);
                }//for

                c_warehouses.assign(c_sups, iNumOfWare);
                return true;

        }//if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateWares(string* sNames, double* dWareCaps, int iNumOfWare)

bool CMscnProblem::bCreateShops(int iNumOfSh) {

        if (iNumOfSh == i_num_of_sh) {
                CMySmartPointer<CShop>* c_sups = new CMySmartPointer<CShop>[iNumOfSh];
                for (int i = 0; i < iNumOfSh; i++) {
                        c_sups[i].assign(new CShop(), 0);
                }//for

                c_shops.assign(c_sups, iNumOfSh);
                return true;
        }// if
        else {
                return false;
        }//else

}//bool CMscnProblem::bCreateShops(string* sNames, double* dPrices, double* dDemands, int iNumOfSh)

bool CMscnProblem::bConnect() {

        for (int i = 0; i < i_num_of_sup; i++) {
                (c_suppliers.rtAt(i))->vAddFactories(c_factories);
        }//for

        for (int i = 0; i < i_num_of_fac; i++) {
                (c_factories.rtAt(i))->vAddWarehouses(c_warehouses);
        }//for

        for (int i = 0; i < i_num_of_ware; i++) {
                (c_warehouses.rtAt(i))->vAddShops(c_shops);
        }//for

        return true;
}//bool CMscnProblem::bConnect()

int CMscnProblem::iChangeCD(int iSupIndex, int iFacIndex, double dNewCost) {

        if (iSupIndex >= 0 && iSupIndex < i_num_of_sup && iFacIndex >= 0 && iFacIndex < i_num_of_fac && dNewCost >0) {
                (c_suppliers.rtAt(iSupIndex))->vSetCost(dNewCost, iFacIndex);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else

}//int CMscnProblem::iChangeCD(int iSupIndex, int iFacIndex, double dNewCost)

int CMscnProblem::iChangeCF(int iFacIndex, int iWareIndex, double dNewCost) {

        if (iFacIndex >= 0 && iFacIndex < i_num_of_fac && iWareIndex >= 0 && iWareIndex < i_num_of_ware&& dNewCost > 0) {
                (c_factories.rtAt(iFacIndex))->vSetCost(dNewCost, iWareIndex);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else

}//int CMscnProblem::iChangeCF(int iFacIndex, int iWareIndex, double dNewCost)

int CMscnProblem::iChangeCM(int iWareIndex, int iShIndex, double dNewCost) {

        if (iWareIndex >= 0 && iWareIndex < i_num_of_ware && iShIndex >= 0 && iShIndex < i_num_of_sh&& dNewCost > 0) {
                (c_warehouses.rtAt(iWareIndex))->vSetCost(dNewCost, iShIndex);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else

}//int CMscnProblem::iChangeCM(int iWareIndex, int iShIndex, double dNewCost)

int CMscnProblem::iChangeSD(int iSupIndex, double dNewCap) {

        if (iSupIndex >= 0 && iSupIndex < i_num_of_sup && dNewCap >0) {
                (c_suppliers.rtAt(iSupIndex))->vSetSupProdCap(dNewCap);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else

}//int CMscnProblem::iChangeSD(int iSupIndex, double dNewCap)

int CMscnProblem::iChangeSF(int iFacIndex, double dNewCap) {

        if (iFacIndex >= 0 && iFacIndex < i_num_of_fac && dNewCap >0) {
                (c_factories.rtAt(iFacIndex))->vSetFacProdCap(dNewCap);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//int CMscnProblem::iChangeSF(int iFacIndex, double dNewCap)

int CMscnProblem::iChangeSM(int iWareIndex, double dNewCap) {

        if (iWareIndex >= 0 && iWareIndex < i_num_of_ware && dNewCap >0) {
                (c_warehouses.rtAt(iWareIndex))->vSetWareCap(dNewCap);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//int CMscnProblem::iChangeSM(int iWareIndex, double dNewCap)

int CMscnProblem::iChangeSS(int iShIndex, double dNewCap) {
        if (iShIndex >= 0 && iShIndex < i_num_of_sh) {
                (c_shops.rtAt(iShIndex))->vSetDemand(dNewCap);
                return SUCCESS_CODE;
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//int CMscnProblem::iChangeSS(int iShIndex, double dNewCap)


int CMscnProblem::iChangeNumOfSup(int iNumOfSup) {

        if (iNumOfSup > 0 && iNumOfSup != i_num_of_sup) {
                CMySmartPointer<CSupplier>* pc_new_tab = new CMySmartPointer<CSupplier>[iNumOfSup];
                if (iNumOfSup > i_num_of_sup) {

                        for (int i = 0; i < i_num_of_sup; i++) {
                                pc_new_tab[i] = c_suppliers.rtAt(i);
                        }// for

                        for (int i = i_num_of_sup; i < iNumOfSup; i++) {
                                pc_new_tab[i].assign(new CSupplier(i_num_of_fac), 0);
                        }//for

                }//if
                else if (iNumOfSup < i_num_of_sh) {
                        for (int i = 0; i < iNumOfSup; i++) {
                                pc_new_tab[i] = c_suppliers.rtAt(i);
                        }// for
                }//else if

                c_suppliers.assign(pc_new_tab, iNumOfSup);
                i_num_of_sup = iNumOfSup;

                for (int i = 0; i < i_num_of_sup; i++) {
                        (*(c_suppliers.rtAt(i))).vAddFactories(c_factories);
                }//for

                return SUCCESS_CODE;
        }//if
        else {
                return ILLEGAL_VALUE_ERR;
        }//else
}//int CMscnProblem::iChangeNumOfSup(int iNumOfSup)

int CMscnProblem::iChangeNumOfFac(int iNumOfFac) {

        if (iNumOfFac > 0 && iNumOfFac != i_num_of_fac) {
                CMySmartPointer<CFactory>* pc_new_tab = new CMySmartPointer<CFactory>[iNumOfFac];
                if (iNumOfFac > i_num_of_fac) {
                        for (int i = 0; i < i_num_of_fac; i++) {
                                pc_new_tab[i] = c_factories.rtAt(i);
                        }//for
                        for (int i = i_num_of_fac; i < iNumOfFac; i++) {
                                pc_new_tab[i].assign(new CFactory(i_num_of_ware), 0);
                        }//for
                }//if
                else if (iNumOfFac < i_num_of_fac) {
                        for (int i = 0; i < iNumOfFac; i++) {
                                pc_new_tab[i] = c_factories.rtAt(i);
                        }//for
                }//else if
                c_factories.assign(pc_new_tab, iNumOfFac);
                i_num_of_fac = iNumOfFac;
                for (int i = 0; i < i_num_of_sup; i++) {
                        (*(c_suppliers.rtAt(i))).vAddFactories(c_factories);
                }//for
                for (int i = 0; i < i_num_of_fac; i++) {
                        (*(c_factories.rtAt(i))).vAddWarehouses(c_warehouses);
                }//for
                return SUCCESS_CODE;
        }//if
        else {
                return ILLEGAL_VALUE_ERR;
        }//else
}//int CMscnProblem::iChangeNumOfFac(int iNumOfFac)

int CMscnProblem::iChangeNumOfWare(int iNumOfWare) {

        if (iNumOfWare > 0 && iNumOfWare != i_num_of_ware) {
                CMySmartPointer<CWarehouse>* pc_new_tab = new CMySmartPointer<CWarehouse>[iNumOfWare];
                if (iNumOfWare > i_num_of_ware) {
                        for (int i = 0; i < i_num_of_ware; i++) {
                                pc_new_tab[i] = c_warehouses.rtAt(i);
                        }//for
                        for (int i = i_num_of_ware; i < iNumOfWare; i++) {
                                pc_new_tab[i].assign(new CWarehouse(i_num_of_sh), 0);
                        }//for
                }//if
                else if (iNumOfWare < i_num_of_ware) {
                        for (int i = 0; i < iNumOfWare; i++) {
                                pc_new_tab[i] = c_warehouses.rtAt(i);
                        }//for
                }//else if
                c_warehouses.assign(pc_new_tab, iNumOfWare);
                i_num_of_ware = iNumOfWare;
                for (int i = 0; i < i_num_of_fac; i++) {
                        (*(c_factories.rtAt(i))).vAddWarehouses(c_warehouses);
                }//for
                for (int i = 0; i < i_num_of_ware; i++) {
                        (*(c_warehouses.rtAt(i))).vAddShops(c_shops);
                }//for
                return SUCCESS_CODE;
        }//if
        else {
                return ILLEGAL_VALUE_ERR;
        }//else
}//int CMscnProblem::iChangeNumOfWare(int iNumOfWare)

int CMscnProblem::iChangeNumOfSh(int iNumOfSh) {

        if (iNumOfSh > 0 && iNumOfSh != i_num_of_sh) {
                CMySmartPointer<CShop>* pc_new_tab = new CMySmartPointer<CShop>[iNumOfSh];
                if (iNumOfSh > i_num_of_sh) {
                        for (int i = 0; i < i_num_of_sh; i++) {
                                pc_new_tab[i] = c_shops.rtAt(i);
                        }//for
                        for (int i = i_num_of_sh; i < iNumOfSh; i++) {
                                pc_new_tab[i].assign(new CShop(), 0);
                        }//for
                }//if
                else if (iNumOfSh < i_num_of_sh) {
                        for (int i = 0; i < iNumOfSh; i++) {
                                pc_new_tab[i] = c_shops.rtAt(i);
                        }//for
                }//else if
                c_shops.assign(pc_new_tab,iNumOfSh);
                i_num_of_sh = iNumOfSh;
                for (int i = 0; i < i_num_of_ware; i++) {
                        (*(c_warehouses.rtAt(i))).vAddShops(c_shops);
                }//for
                return SUCCESS_CODE;
        }//if
        else {
                return ILLEGAL_VALUE_ERR;
        }//else
}//int CMscnProblem::iChangeNumOfSh(int iNumOfSh)

int CMscnProblem::iGetNumOfSup() {
        return i_num_of_sup;
}//int CMscnProblem::iGetNumOfSup()

int CMscnProblem::iGetNumOfFac() {
        return i_num_of_fac;
}//int CMscnProblem::iGetNumOfFac()

int CMscnProblem::iGetNumOfWare() {
        return i_num_of_ware;
}//int CMscnProblem::iGetNumOfWare()

int CMscnProblem::iGetNumOfSh() {
        return i_num_of_sh;
}//int CMscnProblem::iGetNumOfSh()

void CMscnProblem::vSetSupplierCost(int iSupIndex, int iFacIndex, double dCost) {
        if (iSupIndex < c_suppliers.iGetTabSize() && iSupIndex >= 0 && iFacIndex >= 0 && iFacIndex < c_factories.iGetTabSize()) {
                (c_suppliers.rtAt(iSupIndex))->vSetCost(dCost, iFacIndex);
        }//if
}//void CMscnProblem::setSupplierCost(int iSupIndex, int iFacIndex, double dCost)

void CMscnProblem::vSetFactoryCost(int iFacIndex, int iWareIndex, double dCost) {
        if (iFacIndex < c_factories.iGetTabSize() && iFacIndex >= 0 && iWareIndex >= 0 && iWareIndex < c_warehouses.iGetTabSize()) {
                (c_factories.rtAt(iFacIndex))->vSetCost(dCost, iWareIndex);
        }//if
}//void CMscnProblem::setFactoryCost(int iFacIndex, int iWareIndex, double dCost)

void CMscnProblem::vSetWarehouseCost(int iWareIndex, int iShIndex, double dCost) {
        if (iWareIndex < c_warehouses.iGetTabSize() && iWareIndex >= 0 && iShIndex >= 0 && iShIndex < c_shops.iGetTabSize()) {
                (c_warehouses.rtAt(iWareIndex))->vSetCost(dCost, iShIndex);
        }//if
}//void CMscnProblem::setWarehouseCost(int iWareIndex, int iShIndex, double dCost)

void CMscnProblem::vSetSupplierNames(string* psNames, int iSize) {
        CMySmartPointer< CMySmartPointer<CSupplier>>& cUnits = c_suppliers;
        if (cUnits.iGetTabSize() == iSize) {
                for (int i = 0; i < cUnits.iGetTabSize(); i++) {
                        vSetName(&(*cUnits.rtAt(i)), psNames[i]);
                }//for
        }//if
}//void CMscnProblem::vSetSupplierNames(string* psNames, int iSize)

void CMscnProblem::vSetFactoryNames(string* psNames, int iSize) {
        CMySmartPointer< CMySmartPointer<CFactory>>& cUnits = c_factories;
        if (cUnits.iGetTabSize() == iSize) {
                for (int i = 0; i < cUnits.iGetTabSize(); i++) {
                        vSetName(&(*cUnits.rtAt(i)), psNames[i]);
                }//for
        }//if
}//void CMscnProblem::vSetFactoryNames(string* psNames, int iSize)

void CMscnProblem::vSetWarehouseNames(string* psNames, int iSize) {
        CMySmartPointer< CMySmartPointer<CWarehouse>>& cUnits = c_warehouses;
        if (cUnits.iGetTabSize() == iSize) {
                for (int i = 0; i < cUnits.iGetTabSize(); i++) {
                        vSetName(&(*cUnits.rtAt(i)), psNames[i]);
                }//for
        }//if
}//void CMscnProblem::vSetWarehouseNames(string* psNames, int iSize)

void CMscnProblem::vSetShopNames(string* psNames, int iSize) {
        CMySmartPointer<CMySmartPointer<CShop>>& cUnits = c_shops;
        if (cUnits.iGetTabSize() == iSize) {
                for (int i = 0; i < cUnits.iGetTabSize(); i++) {
                        vSetName(&(*cUnits.rtAt(i)), psNames[i]);
                }//for
        }//if
}//void CMscnProblem::vSetShopNames(string* psNames, int iSize)

void CMscnProblem::vSetName(CAbstractUnit* cUnit, string sName) {
        cUnit->vSetName(sName);
}//void CMscnProblem::vSetName(CAbstractUnit* cUnit, string sName)

void CMscnProblem::vPrintAll() {

        CAbstractUnit2* pc_unit = NULL;
        for (int i = 0; i < i_num_of_sup; i++) {
                pc_unit = &(*c_suppliers.rtAt(i));
                cout << "Dostawca: "<<pc_unit->sGetName() <<", koszt: "<< pc_unit->dPrintCosts() << endl;
        }//for
        for (int i = 0; i < i_num_of_fac; i++) {
                pc_unit = &(*c_factories.rtAt(i));
                cout << "Fabryka: " << pc_unit->sGetName() << ", koszt: " << pc_unit->dPrintCosts() << endl;
        }//for
        for (int i = 0; i < i_num_of_ware; i++) {
                pc_unit = &(*c_warehouses.rtAt(i));
                cout << "Magazyn: " << pc_unit->sGetName() << ", koszt: " << pc_unit->dPrintCosts() << endl;
        }//for
        pc_unit = NULL;
        CAbstractUnit* pc_unit_2 = NULL;
        for (int i = 0; i < i_num_of_sh; i++) {
                pc_unit_2 = &(*c_shops.rtAt(i));
                cout << "Sklep: " << pc_unit_2->sGetName() << ", cena: " << ((CShop*)pc_unit_2)->dGetPrice() << endl;
        }//for
        pc_unit_2 = NULL;
}//void CMscnProblem::vPrintAll()

void CMscnProblem::vPrintDown(string& sName) {
        int i_index = 0;
        while (i_index < i_num_of_sup && (*(c_suppliers.rtAt(i_index))).sGetName() != sName) {
                i_index++;
        }//while
        (c_suppliers.rtAt(i_index))->vPrint();
}//void CMscnProblem::vPrintDown(string sName)

void CMscnProblem::vSetSupProdCap(double* pdCapacities) {
        for (int i = 0; i < c_suppliers.iGetTabSize(); i++) {
                c_suppliers.rtAt(i)->vSetSupProdCap(pdCapacities[i] < 0 ? 0 : pdCapacities[i]);
        }//for
}//void CMscnProblem::vSetSupProdCap(double* pdCapacities)

void CMscnProblem::vSetFacProdCap(double* pdCapacities) {
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                c_factories.rtAt(i)->vSetFacProdCap(pdCapacities[i] < 0 ? 0 : pdCapacities[i]);
        }//for
}//void CMscnProblem::vSetFacProdCap(double* pdCapacities)

void CMscnProblem::vSetWareCap(double* pdCapacities) {
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                c_warehouses.rtAt(i)->vSetWareCap(pdCapacities[i] < 0 ? 0 : pdCapacities[i]);
        }//for
}//void CMscnProblem::vSetWareCap(double* pdCapacities)

void CMscnProblem::vSetShDemands(double* pdDemands) {
        for (int i = 0; i < c_shops.iGetTabSize(); i++) {
                c_shops.rtAt(i)->vSetDemand(pdDemands[i] < 0 ? 0 : pdDemands[i]);
        }//for
}//void CMscnProblem::vSetShDemands(double* pdDemands)

void CMscnProblem::vSetSupCosts(double* pdCosts) {
        int i_index = 0;
        for (int i = 0; i < c_suppliers.iGetTabSize(); i++) {
                for (int j = 0; j < c_factories.iGetTabSize(); j++) {
                        c_suppliers.rtAt(i)->vSetCost(pdCosts[i_index], j);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetSupCosts(double* pdCosts)

void CMscnProblem::vSetFacCosts(double* pdCosts) {
        int i_index = 0;
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                for (int j = 0; j < c_warehouses.iGetTabSize(); j++) {
                        c_factories.rtAt(i)->vSetCost(pdCosts[i_index], j);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetFacCosts(double* pdCosts)

void CMscnProblem::vSetWareCosts(double* pdCosts) {
        int i_index = 0;
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                for (int j = 0; j < c_shops.iGetTabSize(); j++) {
                        c_warehouses.rtAt(i)->vSetCost(pdCosts[i_index], j);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetWareCosts(double* pdCosts)

void CMscnProblem::vSetSupX(double* pdX) {
        int i_index = 0;
        for (int i = 0; i < c_suppliers.iGetTabSize(); i++) {
                for (int j = 0; j < c_factories.iGetTabSize(); j++) {
                        c_suppliers.rtAt(i)->vSetX(j, pdX[i_index]);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetSupX(double* pdX)

void CMscnProblem::vSetFacX(double* pdX) {
        int i_index = 0;
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                for (int j = 0; j < c_warehouses.iGetTabSize(); j++) {
                        c_factories.rtAt(i)->vSetX(j, pdX[i_index]);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetFacX(double* pdX)

void CMscnProblem::vSetWareX(double* pdX) {
        int i_index = 0;
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                for (int j = 0; j < c_shops.iGetTabSize(); j++) {
                        c_warehouses.rtAt(i)->vSetX(j, pdX[i_index]);
                        i_index++;
                }//for
        }//for
}//void CMscnProblem::vSetWareX(double* pdX)

void CMscnProblem::vSetConstantSupCost(double* pdCosts) {
        for (int i = 0; i < c_suppliers.iGetTabSize(); i++) {
                c_suppliers.rtAt(i)->vSetU(pdCosts[i]);
        }//for
}//

void CMscnProblem::vSetConstantFacCost(double* pdCosts) {
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                c_factories.rtAt(i)->vSetU(pdCosts[i]);
        }//for
}//void CMscnProblem::vSetConstantFacCost(double* pdCosts)

void CMscnProblem::vSetConstantWareCost(double* pdCosts) {
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                c_warehouses.rtAt(i)->vSetU(pdCosts[i]);
        }//for
}//void CMscnProblem::vSetConstantWareCost(double* pdCosts)

void CMscnProblem::vSetShopsPrices(double* pdPrices) {
        for (int i = 0; i < c_shops.iGetTabSize(); i++) {
                c_shops.rtAt(i)->vSetPrice(pdPrices[i]);
        }//for
}//void CMscnProblem::vSetShopsPrices(double* pdPrices)

void CMscnProblem::vSetSupMinMaxes(double* pdMinMaxes) {
        int i_index = 0;
        for (int i = 0; i < c_suppliers.iGetTabSize(); i++) {
                for (int j = 0; j < c_factories.iGetTabSize(); j++) {
                        c_suppliers.rtAt(i)->vSetXMin(j, pdMinMaxes[i_index++]);
                        c_suppliers.rtAt(i)->vSetXMax(j, pdMinMaxes[i_index++]);
                }//for
        }//for
}//void CMscnProblem::vSetSupMinMaxes(double* pdMinMaxes)

void CMscnProblem::vSetFacMinMaxes(double* pdMinMaxes) {
        int i_index = 0;
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                for (int j = 0; j < c_warehouses.iGetTabSize(); j++) {
                        c_factories.rtAt(i)->vSetXMin(j, pdMinMaxes[i_index++]);
                        c_factories.rtAt(i)->vSetXMax(j, pdMinMaxes[i_index++]);
                }//for
        }//for
}//void CMscnProblem::vSetFacMinMaxes(double* pdMinMaxes)

void CMscnProblem::vSetWareMinMaxes(double* pdMinMaxes) {
        int i_index = 0;
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                for (int j = 0; j < c_shops.iGetTabSize(); j++) {
                        c_warehouses.rtAt(i)->vSetXMin(j, pdMinMaxes[i_index++]);
                        c_warehouses.rtAt(i)->vSetXMax(j, pdMinMaxes[i_index++]);
                }//for
        }//for
}//void CMscnProblem::vSetWareMinMaxes(double* pdMinMaxes)

double CMscnProblem::dCalculateKT() {
        double d_kt = 0;
        for (int s = 0; s < i_num_of_sup; s++) {
                for (int f = 0; f < i_num_of_fac; f++) {
                        double i_x = c_suppliers.rtAt(s)->dGetX(f);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_kt += c_suppliers.rtAt(s)->dGetCost(f) * i_x;
                        }//if
                }//for
        }//for
        for (int f = 0; f < i_num_of_fac; f++) {
                for (int w = 0; w < i_num_of_ware; w++) {
                        double i_x = c_factories.rtAt(f)->dGetX(w);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_kt += c_factories.rtAt(f)->dGetCost(w) * i_x;
                        }//if
                }//for
        }//for
        for (int w = 0; w < i_num_of_sup; w++) {
                for (int s = 0; s < i_num_of_fac; s++) {
                        double i_x = c_warehouses.rtAt(w)->dGetX(s);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_kt += c_warehouses.rtAt(w)->dGetCost(s) * i_x;
                        }//if
                }//for
        }//for
        return d_kt;
}//double CMscnProblem::dCalculateKT()

double CMscnProblem::dCalculateKU() {
        double d_xsum;
        double d_ku = 0;
        for (int s = 0; s < i_num_of_sup; s++) {
                d_xsum = 0;
                for (int f = 0; f < i_num_of_fac; f++) {
                        double i_x = c_suppliers.rtAt(s)->dGetX(f);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_xsum += i_x;
                        }//if
                }//for
                if (d_xsum > 0) {
                        d_ku += c_suppliers.rtAt(s)->dGetU();
                }//if
        }//for
        for (int f = 0; f < i_num_of_fac; f++) {
                d_xsum = 0;
                for (int w = 0; w < i_num_of_ware; w++) {
                        double i_x = c_factories.rtAt(f)->dGetX(w);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_xsum += i_x;
                        }//if
                }//for
                if (d_xsum > 0) {
                        d_ku += c_factories.rtAt(f)->dGetU();
                }//if
        }//for
        for (int w = 0; w < i_num_of_ware; w++) {
                d_xsum = 0;
                for (int s = 0; s < i_num_of_sh; s++) {
                        double i_x = c_warehouses.rtAt(w)->dGetX(s);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_xsum += i_x;
                        }//if
                }//for
                if (d_xsum > 0) {
                        d_ku += c_warehouses.rtAt(w)->dGetU();
                }//if
        }//for
        return d_ku;
}//double CMscnProblem::dCalculateKU()

double CMscnProblem::dCalculateP() {
        double d_p = 0;
        for (int w = 0; w < i_num_of_ware; w++) {
                for (int s = 0; s < i_num_of_sh; s++) {
                        double i_x = c_warehouses.rtAt(w)->dGetX(s);
                        if (i_x != INDEX_OUT_OF_BOUNDS) {
                                d_p += c_shops.rtAt(s)->dGetPrice() * i_x;
                        }//if
                }//for
        }//for
        return d_p;
}//double CMscnProblem::dCalculateP()

double CMscnProblem::dCalculateProfit() {
        return dCalculateP() - dCalculateKT() - dCalculateKU();
}//double CMscnProblem::dCalculateProfit()

double CMscnProblem::tGetQuality(double* pdSolution, int iSize) {
        if (pdSolution != NULL && iSize == i_num_of_sup*i_num_of_fac + i_num_of_fac*i_num_of_ware+i_num_of_ware*i_num_of_sh) {
                vector<double> v_cons;
                int i_counter = 0;
                CMySmartPointer<pair<double, double>> pc_range = pcCheckRange(iSize);
                do {
                        v_cons = vConstraintSatisfied(pdSolution, iSize);
                        v_repair_solution(pdSolution, v_cons, pc_range);
                        i_counter++;
                } while (v_cons[0] != ALL_OK_CODE && v_cons[0] != NULL_TABLE_ERR && i_counter<STUCK_CNT);
                if (v_cons[0] == NULL_TABLE_ERR) {
                        return NULL_TABLE_ERR;
                }//if
                else if(v_cons[0] == ALL_OK_CODE){
                        for (int i = 0; i < iSize; i++) {
                                if (pdSolution[i] < 0) {
                                        pdSolution[i] = 0;
                                }//if
                        }//for
                        double* d_temp = new double[i_num_of_sup*i_num_of_fac];
                        for (int i = 0; i < i_num_of_sup*i_num_of_fac; i++) {
                                d_temp[i] = pdSolution[i];
                        }//for
                        vSetSupX(d_temp);
                        delete[] d_temp;
                        d_temp = new double[i_num_of_fac * i_num_of_ware];
                        for (int i = 0; i < i_num_of_fac * i_num_of_ware; i++) {
                                d_temp[i] = pdSolution[i + i_num_of_sup * i_num_of_fac];
                        }//for
                        vSetFacX(d_temp);
                        delete[] d_temp;
                        d_temp = new double[i_num_of_ware*i_num_of_sh];
                        for (int i = 0; i < i_num_of_ware*i_num_of_sh; i++) {
                                d_temp[i] = pdSolution[i + i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware];
                        }//for
                        vSetWareX(d_temp);
                        delete[] d_temp;
                        return dCalculateProfit();
                }//else if
                else {
                        return v_cons[0];
                }//else
        }//if
        else {
                return NULL_TABLE_ERR;
        }//else
}//double CMscnProblem::dGetQuality(double* pdSolution)

void CMscnProblem::v_repair_solution(double* pdSolution, vector<double>& vData, CMySmartPointer<pair<double, double>>& pcRange) {
        switch ((int)(vData[0])){
                case SUP_FAC_CODE: {
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = d_sum - c_suppliers.rtAt(i_index)->dGetSupProdCap();
                        v_loop(pdSolution, i_index*i_num_of_fac, i_num_of_fac, d_diff, pcRange);
                }break;
                case FAC_WARE_CODE: {
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = d_sum - c_factories.rtAt(i_index)->dGetFacProdCap();
                        int i_start = i_num_of_sup * i_num_of_fac + i_index * i_num_of_ware;
                        v_loop(pdSolution, i_start, i_num_of_ware, d_diff, pcRange);
                }break;
                case WARE_SHOP_CODE:{
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = d_sum - c_warehouses.rtAt(i_index)->dGetWareCap();
                        int i_start = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_index * i_num_of_sh;
                        v_loop(pdSolution, i_start, i_num_of_sh, d_diff, pcRange);
                }break;
                case SHOP_DEM_CODE:{
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = d_sum - c_shops.rtAt(i_index)->dGetDemand();
                        int i_start = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_index * i_num_of_sh;
                        v_loop(pdSolution, i_start, i_num_of_sh, d_diff, pcRange);
                }break;
                case FAC_OUT_IN_CODE: {
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = vData[3];
                        int i_start = i_num_of_sup * i_num_of_fac + i_index * i_num_of_ware;
                        v_loop(pdSolution, i_start, i_num_of_ware, d_diff, pcRange);
                }break;
                case WARE_OUT_IN_CODE: {
                        double d_sum = vData[2];
                        int i_index = vData[1];
                        double d_diff = vData[3];
                        int i_start = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_index * i_num_of_sh;
                        v_loop(pdSolution, i_start, i_num_of_sh, d_diff, pcRange);
                }break;
                case OUT_OF_RANGE_CODE: {
                        int i_index = vData[1];
                        double d_min = vData[2];
                        double d_max = vData[3];
                        if (pdSolution[i_index] < d_min) {
                                pdSolution[i_index] = d_min;
                        }//if
                        else {
                                pdSolution[i_index] = d_max;
                        }//else
                        //cout << "poprawione: " << pdSolution[i_index] << ", min: " << d_min << ", max: " << d_max << endl;
                }break;
                default: {
                }break;
        }//switch
}//void CMscnProblem::v_repair_solution(double* pdSolution, vector<double>& vData, CMySmartPointer<pair<double, double>>& pcRange)

void CMscnProblem::v_loop(double* pdSolution, int iStart, int iNumIter, double dDiff, CMySmartPointer<pair<double, double>>& pcRange) {
        for (int i = iStart; i < iStart + iNumIter; i++) {
                double d_min = pcRange.rtAt(i).first;
                double d_diff2 = 0;
                if ((d_diff2 = pdSolution[i] - d_min) > dDiff) {
                        pdSolution[i] = pdSolution[i] - dDiff;
                        dDiff = 0;
                }//if
                else {
                        pdSolution[i] = pdSolution[i] - d_diff2;
                        dDiff = dDiff - d_diff2;
                }//else
        }//for
}//void CMscnProblem::v_loop(double* pdSolution, int iStart, int iNumIter, double dDiff, CMySmartPointer<pair<double, double>>& pcRange)

vector<double> CMscnProblem::vConstraintSatisfied(double* pdSolution, int iSize) {
        if (pdSolution != NULL && iSize == i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_num_of_ware * i_num_of_sh) {
                CMySmartPointer<pair<double, double>> pc_range = pcCheckRange(iSize);
                for (int i = 0; i < iSize; i++) {
                        if (pdSolution[i] < pc_range.rtAt(i).first || pdSolution[i] > pc_range.rtAt(i).second) {
                                return vector<double>{(double)OUT_OF_RANGE_CODE, (double)i, pc_range.rtAt(i).first, pc_range.rtAt(i).second};
                        }//if
                }//for
                double d_sum = 0;
                int i_index = 0;
                for (int i = 0; i < i_num_of_sup; i++) {
                        d_sum = 0;
                        for (int j = 0; j < i_num_of_fac; j++) {
                                d_sum += pdSolution[i_index++];
                        }//for
                        if (d_sum > c_suppliers.rtAt(i)->dGetSupProdCap()) {
                                return vector<double>{(double)SUP_FAC_CODE, (double)i, d_sum};//wiecej wychodzi od dostawcy niz jest w stanie przerobiæ
                        }//if
                }//for
                for (int i = 0; i < i_num_of_fac; i++) {
                        d_sum = 0;
                        for (int j = 0; j < i_num_of_ware; j++) {
                                d_sum += pdSolution[i_index++];
                        }//for
                        if (d_sum > c_factories.rtAt(i)->dGetFacProdCap()) {
                                return vector<double>{(double)FAC_WARE_CODE, (double)i, d_sum};//wiecej wychodzi z fabryki niz jest w stanie przerobiæ
                        }//if
                }//for
                for (int i = 0; i < i_num_of_ware; i++) {
                        d_sum = 0;
                        for (int j = 0; j < i_num_of_sh; j++) {
                                d_sum += pdSolution[i_index++];
                        }//for
                        if (d_sum > c_warehouses.rtAt(i)->dGetWareCap()) {
                                return vector<double>{(double)WARE_SHOP_CODE, (double)i, d_sum}; //wiecej wychodzi z magazynu niz jest w stanie przetrzymac
                        }//if
                }//for
                i_index = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware;
                for (int i = 0; i < i_num_of_ware; i++) {
                        d_sum = 0;
                        for (int j = 0; j < i_num_of_sh; j++) {
                                d_sum += pdSolution[i_index++];
                        }//for
                        if (d_sum > c_shops.rtAt(i)->dGetDemand()) {
                                return vector<double>{(double)SHOP_DEM_CODE, (double)i, d_sum};//wiecej wchodzi do sklepu niz jego popyt
                        }//if
                }//for
                i_index = 0;
                double* d_temp = new double[i_num_of_fac];// suma produktu ktory wchodzi do fabryki od wszystkich dostawcow
                for (int i = 0; i < i_num_of_fac; i++) {
                        d_temp[i] = 0;
                }//for
                for (int i = 0; i < i_num_of_sup; i++) {
                        for (int j = 0; j < i_num_of_fac; j++) {
                                d_temp[i_index % i_num_of_fac] += pdSolution[i_index++];
                        }//for
                }//for
                double* d_temp2 = new double[i_num_of_fac]; // suma tego produktu co wychodzi z fabryk
                for (int i = 0; i < i_num_of_fac; i++) {
                        d_temp2[i] = 0;
                }//for
                double d_sum2 = 0;
                i_index = i_num_of_sup * i_num_of_fac;
                for (int i = 0; i < i_num_of_fac; i++) {
                        d_sum2 = 0;
                        for (int j = 0; j < i_num_of_ware; j++) {
                                d_sum2 += pdSolution[i_index++];
                        }
                        d_temp2[i] = d_sum2;
                }//for
                for (int i = 0; i < i_num_of_fac; i++) {
                        if (d_temp[i] < d_temp2[i]) {
                                double d_sum = d_temp2[i];
                                double d_diff = d_sum - d_temp[i];
                                delete[] d_temp;
                                delete[] d_temp2;
                                return vector<double>{(double)FAC_OUT_IN_CODE, (double)i, d_sum, d_diff};
                        }//if
                }//for
                delete[] d_temp;
                delete[] d_temp2;

                d_temp = new double[i_num_of_ware];// suma produktu ktory wchodzi do danego magazynu z wszystkich fabryk
                for (int i = 0; i < i_num_of_ware; i++) {
                        d_temp[i] = 0;
                }//for
                i_index = i_num_of_sup * i_num_of_fac;
                for (int i = 0; i < i_num_of_fac; i++) {
                        for (int j = 0; j < i_num_of_ware; j++) {
                                d_temp[i_index % i_num_of_ware] += pdSolution[i_index++];
                        }//for
                }//for
                d_temp2 = new double[i_num_of_fac]; // suma tego produktu co wychodzi z magazynu do sklepow
                for (int i = 0; i < i_num_of_fac; i++) {
                        d_temp2[i] = 0;
                }//for
                d_sum2 = 0;
                i_index = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware;
                for (int i = 0; i < i_num_of_ware; i++) {
                        d_sum2 = 0;
                        for (int j = 0; j < i_num_of_sh; j++) {
                                d_sum2 += pdSolution[i_index++];
                        }//for
                        d_temp2[i] = d_sum2;
                }//for
                for (int i = 0; i < i_num_of_ware; i++) {
                        if (d_temp[i] < d_temp2[i]) {

                                double d_sum = d_temp2[i];
                                double d_diff = d_sum - d_temp[i];
                                delete[] d_temp;
                                delete[] d_temp2;
                                return vector<double>{(double)WARE_OUT_IN_CODE, (double)i, d_sum, d_diff};
                        }//if
                }//for
                delete[] d_temp;
                delete[] d_temp2;

                return vector<double>{(double)ALL_OK_CODE};
        }//if
        else {
                return vector<double>{(double)NULL_TABLE_ERR};
        }//else
}//bool CMscnProblem::bConstaintSatisfied(double* pdSolution)

CMySmartPointer<pair<double, double>> CMscnProblem::pcCheckRange(int iSize) {
        if (iSize == i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_num_of_ware * i_num_of_sh) {
                CMySmartPointer<pair<double, double>> c_temp;
                pair<double, double>* c_pairs = new pair<double, double>[iSize];
                int i_index = 0;
                for (int i = 0; i < i_num_of_sup; i++) {
                        for (int j = 0; j < i_num_of_fac; j++) {
                                c_pairs[i_index].first = c_suppliers.rtAt(i)->dGetXMin(j);
                                c_pairs[i_index++].second = c_suppliers.rtAt(i)->dGetXMax(j);
                        }//for
                }//for
                for (int i = 0; i < i_num_of_fac; i++) {
                        for (int j = 0; j < i_num_of_ware; j++) {
                                c_pairs[i_index].first = c_factories.rtAt(i)->dGetXMin(j);
                                c_pairs[i_index++].second = c_factories.rtAt(i)->dGetXMax(j);
                        }//for
                }//for
                for (int i = 0; i < i_num_of_ware; i++) {
                        for (int j = 0; j < i_num_of_sh; j++) {
                                c_pairs[i_index].first = c_warehouses.rtAt(i)->dGetXMin(j);
                                c_pairs[i_index++].second = c_warehouses.rtAt(i)->dGetXMax(j);
                        }//for
                }//for
                c_temp.assign(c_pairs, iSize);
                return c_temp;
        }//if
        else {
                return NULL;
        }//else

}//pair<double, double> CMscnProblem::pCheckRange(double* pdSolution, int iOffset)


bool CMscnProblem::bSaveToFile(const string& rsFileName) {
        if (this != NULL) {
                CMscnProblem& rcInstance = *this;
                if (rsFileName != "") {
                        CFileErrCode c_file;
                        c_file.bOpenFile(rsFileName, "w+");
                        c_file.bPrint("D ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_sup));
                        c_file.bPrint("\nF ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_fac));
                        c_file.bPrint("\nM ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_ware));
                        c_file.bPrint("\nS ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_sh));
                        c_file.bPrint("\nsd\n");
                        for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                                c_file.bPrint(to_string(rcInstance.c_suppliers.rtAt(i)->dGetSupProdCap()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\nsf\n");
                        for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                                c_file.bPrint(to_string(rcInstance.c_factories.rtAt(i)->dGetFacProdCap()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\nsm\n");
                        for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                                c_file.bPrint(to_string(rcInstance.c_warehouses.rtAt(i)->dGetWareCap()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\nss\n");
                        for (int i = 0; i < rcInstance.i_num_of_sh; i++) {
                                c_file.bPrint(to_string(rcInstance.c_shops.rtAt(i)->dGetDemand()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\ncd\n");
                        for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_fac; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_suppliers.rtAt(i)->dGetCost(j)));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("cf\n");
                        for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_ware; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_factories.rtAt(i)->dGetCost(j)));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("cm\n");
                        for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_sh; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_warehouses.rtAt(i)->dGetCost(j)));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("ud\n");
                        for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                                c_file.bPrint(to_string(rcInstance.c_suppliers.rtAt(i)->dGetU()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\nuf\n");
                        for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                                c_file.bPrint(to_string(rcInstance.c_factories.rtAt(i)->dGetU()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\num\n");
                        for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                                c_file.bPrint(to_string(rcInstance.c_warehouses.rtAt(i)->dGetU()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\np\n");
                        for (int i = 0; i < rcInstance.i_num_of_sh; i++) {
                                c_file.bPrint(to_string(rcInstance.c_shops.rtAt(i)->dGetPrice()));
                                c_file.bPrint(" ");
                        }//for
                        c_file.bPrint("\nxdminmax\n");
                        for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_fac; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_suppliers.rtAt(i)->dGetXMin(j)));
                                        c_file.bPrint(" ");
                                        c_file.bPrint(to_string(rcInstance.c_suppliers.rtAt(i)->dGetXMax(j)));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("xfminmax\n");
                        for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_ware; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_factories.rtAt(i)->dGetXMin(j)));
                                        c_file.bPrint(" ");
                                        c_file.bPrint(to_string(rcInstance.c_factories.rtAt(i)->dGetXMax(j)));
                                        c_file.bPrint(" ");
                                }
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("xmminmax\n");
                        for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_sh; j++) {
                                        c_file.bPrint(to_string(rcInstance.c_warehouses.rtAt(i)->dGetXMin(j)));
                                        c_file.bPrint(" ");
                                        c_file.bPrint(to_string(rcInstance.c_warehouses.rtAt(i)->dGetXMax(j)));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bCloseFile();
                        return true;
                }
                else {
                        return false;
                }
        }
        else {
                return false;
        }
}//bool CMscnProblem::bSaveToFile(string sFileName, CMscnProblem* pcMscnInstance)

bool CMscnProblem::bSaveResult(const string& rsFileName, double* pdSolution) {
        if (this != NULL) {
                CMscnProblem& rcInstance = *this;
                if (rsFileName != "") {
                        CFileErrCode c_file;
                        c_file.bOpenFile(rsFileName, "w+");
                        c_file.bPrint("D ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_sup));
                        c_file.bPrint("\nF ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_fac));
                        c_file.bPrint("\nM ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_ware));
                        c_file.bPrint("\nS ");
                        c_file.bPrint(to_string(rcInstance.i_num_of_sh));
                        c_file.bPrint("\nxd\n");
                        int i_index = 0;
                        for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_fac; j++) {
                                        c_file.bPrint(to_string(pdSolution[i_index++]));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("xf\n");
                        for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_ware; j++) {
                                        c_file.bPrint(to_string(pdSolution[i_index++]));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bPrint("xm\n");
                        for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                                for (int j = 0; j < rcInstance.i_num_of_sh; j++) {
                                        c_file.bPrint(to_string(pdSolution[i_index++]));
                                        c_file.bPrint(" ");
                                }//for
                                c_file.bPrint("\n");
                        }//for
                        c_file.bCloseFile();
                        return true;
                }//if
                else {
                        return false;
                }
        }//if
        else {
                return false;
        }//else
}//bool CMscnProblem::bSaveResult(const string& rsFileName)

bool CMscnProblem::bReadFromFile(const string& rsFileName) {
        if (this != NULL) {
                CMscnProblem& rcInstance = *this;
                CFileErrCode c_file;
                c_file.bOpenFile(rsFileName, "r+");
                c_file.bRead("%*s%d", rcInstance.i_num_of_sup);
                c_file.bRead("%*[\n]%*s%d",rcInstance.i_num_of_fac);
                c_file.bRead("%*[\n]%*s%d", rcInstance.i_num_of_ware);
                c_file.bRead("%*[\n]%*s%d", rcInstance.i_num_of_sh);
                rcInstance.bCreateSups(rcInstance.i_num_of_sup);
                rcInstance.bCreateFacs(rcInstance.i_num_of_fac);
                rcInstance.bCreateWares(rcInstance.i_num_of_ware);
                rcInstance.bCreateShops(rcInstance.i_num_of_sh);
                rcInstance.bConnect();
                double d_temp = 0;
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_suppliers.rtAt(i)->vSetSupProdCap(d_temp);
                }//for
                c_file.bRead("%*s","", 0);
                for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_factories.rtAt(i)->vSetFacProdCap(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_warehouses.rtAt(i)->vSetWareCap(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sh; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_shops.rtAt(i)->vSetDemand(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_fac; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_suppliers.rtAt(i)->vSetCost(d_temp, j);
                        }//for
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_ware; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_factories.rtAt(i)->vSetCost(d_temp, j);
                        }//for
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_sh; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_warehouses.rtAt(i)->vSetCost(d_temp, j);
                        }//for
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_suppliers.rtAt(i)->vSetU(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_factories.rtAt(i)->vSetU(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_warehouses.rtAt(i)->vSetU(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sh; i++) {
                        c_file.bRead("%lf%*[;: ]", d_temp);
                        rcInstance.c_shops.rtAt(i)->vSetPrice(d_temp);
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_sup; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_fac; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_suppliers.rtAt(i)->vSetXMin(j, d_temp);
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_suppliers.rtAt(i)->vSetXMax(j, d_temp);
                        }//for
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_fac; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_ware; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_factories.rtAt(i)->vSetXMin(j, d_temp);
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_factories.rtAt(i)->vSetXMax(j,d_temp);
                        }//for
                }//for
                c_file.bRead("%*s", "", 0);
                for (int i = 0; i < rcInstance.i_num_of_ware; i++) {
                        for (int j = 0; j < rcInstance.i_num_of_sh; j++) {
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_warehouses.rtAt(i)->vSetXMin(j, d_temp);
                                c_file.bRead("%lf%*[;: ]", d_temp);
                                rcInstance.c_warehouses.rtAt(i)->vSetXMax(j, d_temp);
                        }//for
                }//for
                c_file.bCloseFile();
                return true;
        }//if
        else {
                return false;
        }//else
}//CMscnProblem* CMscnProblem::bReadFromFile(string sFileName)

void CMscnProblem::vGenerateInstance(int iInstanceSeed) {
        CRandom c_rand(iInstanceSeed);
        for (int i = 0; i < i_num_of_sh; i++) {
                c_shops.rtAt(i)->vSetPrice(c_rand.dNextDouble(SHOP_PRICE_MIN, SHOP_PRICE_MAX));
                c_shops.rtAt(i)->vSetDemand(c_rand.dNextDouble(SHOP_DEMAND_MIN, SHOP_DEMAND_MAX));
        }//for
        for (int i = 0; i < i_num_of_sup; i++) {
                c_suppliers.rtAt(i)->vSetU(c_rand.dNextDouble(SUP_CONST_COST_MIN, SUP_CONST_COST_MAX));
                c_suppliers.rtAt(i)->vSetSupProdCap(c_rand.dNextDouble(SUP_PROD_CAP_MIN, SUP_PROD_CAP_MAX));
                for (int j = 0; j < i_num_of_fac; j++) {
                        c_suppliers.rtAt(i)->vSetCost(c_rand.dNextDouble(SUP_FAC_COST_MIN, SUP_FAC_COST_MAX), j);
                        c_suppliers.rtAt(i)->vSetXMin(j, SUP_FAC_X_MIN);
                        c_suppliers.rtAt(i)->vSetXMax(j, SUP_FAC_X_MAX);
                }//for
        }//for
        for (int i = 0; i < i_num_of_fac; i++) {
                c_factories.rtAt(i)->vSetU(c_rand.dNextDouble(FAC_CONST_COST_MIN, FAC_CONST_COST_MAX));
                c_factories.rtAt(i)->vSetFacProdCap(c_rand.dNextDouble(FAC_PROD_CAP_MIN, FAC_PROD_CAP_MAX));
                for (int j = 0; j < i_num_of_ware; j++) {
                        c_factories.rtAt(i)->vSetCost(c_rand.dNextDouble(FAC_WARE_COST_MIN, FAC_WARE_COST_MAX), j);
                        c_factories.rtAt(i)->vSetXMin(j, FAC_WARE_X_MIN);
                        c_factories.rtAt(i)->vSetXMax(j, FAC_WARE_X_MAX);
                }//for
        }//for
        for (int i = 0; i < i_num_of_ware; i++) {
                c_warehouses.rtAt(i)->vSetU(c_rand.dNextDouble(WARE_CONST_COST_MIN, WARE_CONST_COST_MAX));
                c_warehouses.rtAt(i)->vSetWareCap(c_rand.dNextDouble(WARE_CAP_MIN, WARE_CAP_MAX));
                for (int j = 0; j < i_num_of_sh; j++) {
                        c_warehouses.rtAt(i)->vSetCost(c_rand.dNextDouble(WARE_SHOP_COST_MIN, WARE_SHOP_COST_MAX), j);
                        c_warehouses.rtAt(i)->vSetXMin(j, WARE_SHOP_X_MIN);
                        c_warehouses.rtAt(i)->vSetXMax(j, WARE_SHOP_X_MAX);
                }//for
        }//for
}//void CMscnProblem::vGenerateInstance(int iInstanceSeed)

/*
//lista 10 modyfikacja
void CMscnProblem::v_generate_xs_copy(double** pdSolution, int iSize) {
        CRandom c_rand;
        double* pd_sol_copy = new double[iSize];
        for (int i = 0; i < iSize; i++) {
                pd_sol_copy[i] = (*pdSolution)[i];
        }//for
        delete[] (*pdSolution);
        *pdSolution = pd_sol_copy;
        int* pi_ind = new int[iSize/2];
        for (int i = 0; i < iSize / 2; i++) {
                pi_ind[i] = -1;
        }//for
        for (int i = 0; i < iSize / 2; i++) {
                bool b_perm = true;
                do{
                        b_perm = true;
                        int i_random = c_rand.iNextInt(0, iSize-1);
                        for (int j = 0; j < iSize / 2 && b_perm; j++) {
                                if (i_random == pi_ind[j]) {
                                        b_perm = false;
                                }//if
                        }//for
                        if (b_perm) {
                                pi_ind[i] = i_random;
                        }//if
                } while (!b_perm);
        }//for
        for (int i = 0; i < iSize/2; i++) {
                int i_index = pi_ind[i];
                if (i_index < i_num_of_sup * i_num_of_fac) {
                        (*pdSolution)[i_index] = c_rand.dNextDouble(c_suppliers.rtAt(i_index / i_num_of_fac)->dGetXMin(i_index % i_num_of_fac), c_suppliers.rtAt(i_index / i_num_of_fac)->dGetXMax(i_index % i_num_of_fac));
                }//if
                else if (i_index >= i_num_of_sup * i_num_of_fac && i_index < i_num_of_sup * i_num_of_fac + i_num_of_fac*i_num_of_ware) {
                        int i_supfac = i_num_of_sup * i_num_of_fac;
                        (*pdSolution)[i_index] = c_rand.dNextDouble(c_factories.rtAt((i_index - i_supfac)/i_num_of_ware)->dGetXMin((i_index-i_supfac)%i_num_of_ware), c_factories.rtAt((i_index - i_supfac)/i_num_of_ware)->dGetXMax((i_index-i_supfac)%i_num_of_ware));
                }//elseif
                else {
                        int i_facware = i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware;
                        (*pdSolution)[i_index] = c_rand.dNextDouble(c_warehouses.rtAt((i_index-i_facware)/i_num_of_sh)->dGetXMin((i_index-i_facware)%i_num_of_sh), c_warehouses.rtAt((i_index - i_facware) / i_num_of_sh)->dGetXMax((i_index-i_facware)%i_num_of_sh));
                }//else
        }//for
        delete[] pi_ind;
}//void CMscnProblem::v_generate_xs_copy(double* pdSolution, int iSize)

*/

int CMscnProblem::iGetResultSize(){
        return i_num_of_sup * i_num_of_fac + i_num_of_fac * i_num_of_ware + i_num_of_ware * i_num_of_sh;
}

////////////////////////////////////
//CSupplier

CSupplier::CSupplier(int iNumOfFac) {
        if (DEBUG) {
                cout << "CSupplier default constructor: " << s_name << endl;
        }//if
        s_name = "default supplier";
        d_sup_prod_cap = 10;
        i_num_of_fac = iNumOfFac;
        pd_costs.assign(new double[iNumOfFac],iNumOfFac);
        pd_x_sup_fac.assign(new double[iNumOfFac], iNumOfFac);
        pd_x_max.assign(new double[iNumOfFac], iNumOfFac);
        pd_x_min.assign(new double[iNumOfFac], iNumOfFac);
        for (int i = 0; i < iNumOfFac; i++) {
                pd_costs.vSet(0, i);
                pd_x_sup_fac.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CSupplier::CSupplier(int iNumOfFac)

CSupplier::CSupplier(string& sName, int iNumOfFac) {
        if (DEBUG) {
                cout << "CSupplier constructor: " << s_name << endl;
        }//if
        s_name = sName;
        i_num_of_fac = iNumOfFac;
        pd_costs.assign(new double[iNumOfFac], iNumOfFac);
        pd_x_sup_fac.assign(new double[iNumOfFac], iNumOfFac);
        pd_x_max.assign(new double[iNumOfFac], iNumOfFac);
        pd_x_min.assign(new double[iNumOfFac], iNumOfFac);
        for (int i = 0; i < iNumOfFac; i++) {
                pd_costs.vSet(0, i);
                pd_x_sup_fac.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CSupplier::CSupplier(string sName, double dSupProdCap, int iNumOfFac)

CSupplier::CSupplier(const CSupplier& rcOther) {
        if (DEBUG) {
                cout << "CSupplier copy constructor: " << s_name << endl;
        }//if
        d_sup_prod_cap = rcOther.d_sup_prod_cap;
        c_factories = rcOther.c_factories;
        s_name = rcOther.s_name + "_copy";
}//CSupplier::CSupplier(const CSupplier& rcOther)

CSupplier::~CSupplier() {
        if (DEBUG) {
                cout << "CSupplier destructor: " << s_name << endl;
        }//if
}//CSupplier::~CSupplier()

void CSupplier::vSetSupProdCap(double dSupProdCap) {
        d_sup_prod_cap = dSupProdCap;
}//void CSupplier::vSetSupProdCap(double dSupProdCap)

double CSupplier::dGetSupProdCap() {
        return d_sup_prod_cap;
}//double CSupplier::dGetSupProdCap()

double CSupplier::dGetX(int iOffset) {
        if (iOffset >= 0 && iOffset < i_num_of_fac) {
                return pd_x_sup_fac.rtAt(iOffset);
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//double CSupplier::iGetX(int iOffset)

void CSupplier::vSetX(int iOffset, double dX) {
        if (iOffset >= 0 && iOffset < i_num_of_fac) {
                pd_x_sup_fac.vSet(dX, iOffset);
        }//if
}//void CSupplier::vSetX(int iOffset, double dX)

void CSupplier::vAddFactories(CMySmartPointer< CMySmartPointer<CFactory>>& rpFactory) {
        c_factories = rpFactory;
}//void CSupplier::vAddFactories(CMySmartPointer< CMySmartPointer<CFactory>>& rpFactory)

void CSupplier::vPrint() {
        for (int i = 0; i < c_factories.iGetTabSize(); i++) {
                cout << (*c_factories.rtAt(i)).sGetName() << endl;
                (*c_factories.rtAt(i)).vPrint();
        }//for
}//void CSupplier::vPrint()


////////////////////////////////////
//CFactory

CFactory::CFactory(int iNumOfWare) {
        if (DEBUG) {
                cout << "CFactory default constructor: " << s_name << endl;
        }//if
        s_name = "default Factory";
        d_fac_prod_cap = 10;
        i_num_of_ware = iNumOfWare;
        pd_costs.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_fac_ware.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_max.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_min.assign(new double[iNumOfWare], iNumOfWare);
        for (int i = 0; i < iNumOfWare; i++) {
                pd_costs.vSet(0, i);
                pd_x_fac_ware.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CFactory::CFactory(int iNumOfWare)

CFactory::CFactory(string& sName, int iNumOfWare) {
        if (DEBUG) {
                cout << "CFactory constructor: " << sName << endl;
        }//if
        s_name = sName;
        i_num_of_ware = iNumOfWare;
        pd_costs.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_fac_ware.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_max.assign(new double[iNumOfWare], iNumOfWare);
        pd_x_min.assign(new double[iNumOfWare], iNumOfWare);
        for (int i = 0; i < iNumOfWare; i++) {
                pd_costs.vSet(0, i);
                pd_x_fac_ware.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CFactory::CFactory(string sName, double dFacProdCap, int iNumOfWare)

CFactory::CFactory(const CFactory& rcOther) {
        if (DEBUG) {
                cout << "CFactory copy constructor: " << s_name << endl;
        }//if
        d_fac_prod_cap = rcOther.d_fac_prod_cap;
        c_warehouses = rcOther.c_warehouses;
        s_name = rcOther.s_name + "_copy";
}//CFactory::CFactory(const CFactory& rcOther)

CFactory::~CFactory() {
        if (DEBUG) {
                cout << "CFactory destructor: " << s_name << endl;
        }//if
}//CFactory::~CFactory()

void CFactory::vSetFacProdCap(double dFacProdCap) {
        d_fac_prod_cap = dFacProdCap;
}//void CFactory::vSetFacProdCap(double dFacProdCap)

double CFactory::dGetFacProdCap() {
        return d_fac_prod_cap;
}//double CFactory::dGetFacProdCap()

double CFactory::dGetX(int iOffset) {
        if (iOffset >= 0 && iOffset < i_num_of_ware) {
                return pd_x_fac_ware.rtAt(iOffset);
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//double CFactory::iGetX(int iOffset)

void CFactory::vSetX(int iOffset, double dX) {
        if (iOffset >= 0 && iOffset < i_num_of_ware) {
                pd_x_fac_ware.vSet(dX, iOffset);
        }//if
}//void CFactory::vSetX(int iOffset, double dX)

void CFactory::vAddWarehouses(CMySmartPointer< CMySmartPointer<CWarehouse>>& rpWarehouses) {
        c_warehouses = rpWarehouses;
}//void CFactory::vAddWarehouses(CMySmartPointer< CMySmartPointer<CWarehouse>>& rpWarehouses)

void CFactory::vPrint() {
        for (int i = 0; i < c_warehouses.iGetTabSize(); i++) {
                cout << (*c_warehouses.rtAt(i)).sGetName() << endl;
                (*c_warehouses.rtAt(i)).vPrint();
        }//for
}//void CFactory::vPrint()


////////////////////////////////////
//CWarehouse

CWarehouse::CWarehouse(int iNumOfSh) {
        if (DEBUG) {
                cout << "CWarehouse default constructor: " << s_name << endl;
        }//if
        s_name = "default warehouse";
        d_ware_cap = 10;
        i_num_of_sh = iNumOfSh;
        pd_costs.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_ware_sh.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_max.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_min.assign(new double[iNumOfSh], iNumOfSh);
        for (int i = 0; i < iNumOfSh; i++) {
                pd_costs.vSet(0, i);
                pd_x_ware_sh.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CWarehouse::CWarehouse(int iNumOfSh)

CWarehouse::CWarehouse(string& sName, int iNumOfSh) {
        if (DEBUG) {
                cout << "CWarehouse constructor: " << sName << endl;
        }//if
        s_name = sName;
        i_num_of_sh = iNumOfSh;
        pd_costs.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_ware_sh.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_max.assign(new double[iNumOfSh], iNumOfSh);
        pd_x_min.assign(new double[iNumOfSh], iNumOfSh);
        for (int i = 0; i < iNumOfSh; i++) {
                pd_costs.vSet(0, i);
                pd_x_ware_sh.vSet(0, i);
                pd_x_min.vSet(0, i);
                pd_x_max.vSet(0, i);
        }//for
}//CWarehouse::CWarehouse(string sName, double dWareCap, int iNumOfSh)

CWarehouse::CWarehouse(const CWarehouse& rcOther) {
        if (DEBUG) {
                cout << "CWarehouse constructor: " << s_name << endl;
        }//if
        d_ware_cap = rcOther.d_ware_cap;
        c_shops = rcOther.c_shops;
        s_name = rcOther.s_name + "_copy";
}//CWarehouse::CWarehouse(const CWarehouse& rcOther)

CWarehouse::~CWarehouse() {
        if (DEBUG) {
                cout << "CWarehouse destructor: " << s_name << endl;
        }//if
}//CWarehouse::~CWarehouse()

void CWarehouse::vSetWareCap(double dWareCap) {
        d_ware_cap = dWareCap;
}//void CWarehouse::vSetWareCap(double dWareCap)

double CWarehouse::dGetWareCap() {
        return d_ware_cap;
}//double CWarehouse::dGetWareCap()

double CWarehouse::dGetX(int iOffset) {
        if (iOffset >= 0 && iOffset < i_num_of_sh) {
                return pd_x_ware_sh.rtAt(iOffset);
        }//if
        else {
                return INDEX_OUT_OF_BOUNDS;
        }//else
}//double CWarehouse::iGetX(int iOffset)

void CWarehouse::vSetX(int iOffset, double dX) {
        if (iOffset >= 0 && iOffset < i_num_of_sh) {
                pd_x_ware_sh.vSet(dX, iOffset);
        }//if
}//void CWarehouse::vSetX(int iOffset, double dX)

void CWarehouse::vAddShops(CMySmartPointer< CMySmartPointer<CShop>>& rpShops) {
        c_shops = rpShops;
}//void CWarehouse::vAddShops(CMySmartPointer< CMySmartPointer<CShop>>& rpShops)

void CWarehouse::vPrint() {
        for (int i = 0; i < c_shops.iGetTabSize(); i++) {
                cout << (*c_shops.rtAt(i)).sGetName() << endl;
        }//for
}//void CWarehouse::vPrint()



///////////////////////////////////
//CShop:


CShop::CShop() {
        if (DEBUG) {
                cout << "CShop default costructor: " << endl;
        }//if
        s_name = "default shop";
        d_price = 10;
        d_demand = 10;
}//CShop::CShop()


CShop::CShop(string& sName) {
        if (DEBUG) {
                cout << "CShop costructor: " << sName << endl;
        }//if
        s_name = sName;

}//CShop::CShop(string sName, double dPrice, double dDemand)

CShop::CShop(const CShop& rcOther) {
        if (DEBUG) {
                cout << "CShop copy constructor: " << s_name << endl;
        }//if
        s_name = rcOther.s_name + "_copy";
        d_price = rcOther.d_price;
        d_demand = rcOther.d_demand;
}//CShop::CShop(const CShop& rcOther)

CShop::~CShop() {
        if (DEBUG) {
                cout << "CShop destructor: " << s_name << endl;
        }//if
}//CShop::~CShop()

void CShop::vSetPrice(double dPrice) {
        this->d_price = dPrice;
}//void CShop::vSetPrice(double dPrice)

double CShop::dGetPrice() {
        return d_price;
}//double CShop::dGetPrice()

void CShop::vSetDemand(double dDemand) {
        this->d_demand = dDemand;
}//void CShop::vSetDemand(double dDemand)

double CShop::dGetDemand() {
        return d_demand;
}//double CShop::dGetDemand()