#ifndef CMSCNPROBLEM_H
#define CMSCNPROBLEM_H
#include <string>
#include <vector>
#include "CMySmartPointer.h"
#include "CProblem.h"

//errors
const int ILLEGAL_VALUE_ERR = -1;
const int NULL_TABLE_ERR = -2;
const int INDEX_OUT_OF_BOUNDS = -3;
const int SUCCESS_CODE = 1;
const int CONS_NOT_SATTISFIED = -4;

//what's wrong codes
const int ALL_OK_CODE = 0;
const int SUP_FAC_CODE = -10;
const int FAC_WARE_CODE = -11;
const int WARE_SHOP_CODE = -12;
const int SHOP_DEM_CODE = -13;
const int FAC_OUT_IN_CODE = -14;
const int WARE_OUT_IN_CODE = -15;
const int OUT_OF_RANGE_CODE = -16;

const int STUCK_CNT = 10;

//costs constants
const double SUP_FAC_COST_MIN = 2;
const double SUP_FAC_COST_MAX = 3;
const double FAC_WARE_COST_MIN = 3;
const double FAC_WARE_COST_MAX = 5;
const double WARE_SHOP_COST_MIN = 10;
const double WARE_SHOP_COST_MAX = 15;

const double SHOP_PRICE_MIN = 30;
const double SHOP_PRICE_MAX = 35;

const double SUP_CONST_COST_MIN = 20;
const double SUP_CONST_COST_MAX = 35;
const double FAC_CONST_COST_MIN = 15;
const double FAC_CONST_COST_MAX = 30;
const double WARE_CONST_COST_MIN = 50;
const double WARE_CONST_COST_MAX = 100;

const double SUP_PROD_CAP_MIN = 30000;
const double SUP_PROD_CAP_MAX = 60000;
const double FAC_PROD_CAP_MIN = 40000;
const double FAC_PROD_CAP_MAX = 50000;
const double WARE_CAP_MIN = 100000;
const double WARE_CAP_MAX = 280000;
const double SHOP_DEMAND_MIN = 2000;
const double SHOP_DEMAND_MAX = 7000;

const double SUP_FAC_X_MIN = 1000;
const double SUP_FAC_X_MAX = 1500;
const double FAC_WARE_X_MIN = 500;
const double FAC_WARE_X_MAX = 850;
const double WARE_SHOP_X_MIN = 200;
const double WARE_SHOP_X_MAX = 400;

const string RESULT_INSTANCE_FILE = "wynik_instancja.txt";
const string RESULT_FILE = "wynik.txt";


using namespace std;

class CAbstractUnit {
protected:
	string s_name;
public:
	virtual void vSetName(string& sName);
	virtual string& sGetName();
};
class CAbstractUnit2: public CAbstractUnit {
protected:
	CMySmartPointer<double> pd_costs;
	CMySmartPointer<double> pd_x_max;
	CMySmartPointer<double> pd_x_min;
	double d_u = 1;////////////////////////default 1
public:
	virtual void vSetCosts(CMySmartPointer<double>& cdCosts);
	virtual CMySmartPointer<double>& cdGetCosts();
	virtual void vSetCost(double dCost, int iOffset);
	virtual double dGetCost(int iOffset);
	virtual double dPrintCosts();
	virtual void vSetXMax(int iOffset, double iXMax);
	virtual void vSetXMin(int iOffset, double iXMin);
	virtual double dGetXMax(int iOffset);
	virtual double dGetXMin(int iOffset);
	virtual double dGetU();
	virtual void vSetU(double dU);
};

class CShop : public CAbstractUnit {
private:
	
	double d_price=1;
	double d_demand=1;
public:
	CShop();
	CShop(string& sName);
	CShop(const CShop& rcOther);
	~CShop();

	void vSetPrice(double dPrice);
	double dGetPrice();
	void vSetDemand(double dDemand);
	double dGetDemand();
};

class CWarehouse : public CAbstractUnit2 {
private:

	double d_ware_cap=1;
	int i_num_of_sh;
	CMySmartPointer<double> pd_x_ware_sh;
	CMySmartPointer<CMySmartPointer<CShop>> c_shops;
public:
	CWarehouse(int iNumOfSh);
	CWarehouse(string& sName, int iNumOfShops);
	CWarehouse(const CWarehouse& rcOther);
	~CWarehouse();
	void vAddShops(CMySmartPointer< CMySmartPointer<CShop>>& rcShops);
	void vSetWareCap(double dWareCap);
	double dGetX(int iOffset);
	void vSetX(int iOffset, double dX);
	double dGetWareCap();
	void vPrint();

};

class CFactory : public CAbstractUnit2 {
private:

	double d_fac_prod_cap=1;
	int i_num_of_ware;
	CMySmartPointer<CMySmartPointer<CWarehouse>> c_warehouses;
	CMySmartPointer<double> pd_x_fac_ware;
public:
	CFactory(int iNumOfWare);
	CFactory(string& sName, int iNumOfWare);
	CFactory(const CFactory& rcOther);
	~CFactory();
	void vAddWarehouses(CMySmartPointer< CMySmartPointer<CWarehouse>>& rpWarehouses);
	void vSetFacProdCap(double dFacProdCap);
	double dGetX(int iOffset);
	void vSetX(int iOffset, double dX);
	double dGetFacProdCap();
	void vPrint();
};

class CSupplier : public CAbstractUnit2 {
private:

	double d_sup_prod_cap=1;
	int i_num_of_fac;
	CMySmartPointer<CMySmartPointer<CFactory>> c_factories;
	CMySmartPointer<double> pd_x_sup_fac;
public:
	CSupplier(int iNumOfFac);
	CSupplier(string& sName, int iNumOfWare);
	CSupplier(const CSupplier& rcOther);
	~CSupplier();
	void vAddFactories(CMySmartPointer< CMySmartPointer<CFactory>>& rpFactory);
	void vSetSupProdCap(double dSupProdCap);
	double dGetSupProdCap();
	double dGetX(int iOffset);
	void vSetX(int iOffset, double dX);
	void vPrint();
};

class CMscnProblem : public CProblem<double> {
private:
	CMySmartPointer<CMySmartPointer<CSupplier>> c_suppliers;
	CMySmartPointer<CMySmartPointer<CFactory>> c_factories;
	CMySmartPointer<CMySmartPointer<CWarehouse>> c_warehouses;
	CMySmartPointer<CMySmartPointer<CShop>> c_shops;
	int i_num_of_sup;
	int i_num_of_fac;
	int i_num_of_ware;
	int i_num_of_sh;
	//lista 11
	void v_loop(double* pdSolution, int iStart, int iNumIter, double dDiff, CMySmartPointer<pair<double, double>>& pcRange);
	void v_repair_solution(double* pdSolution, vector<double>& vData, CMySmartPointer<pair<double, double>>& pcRange);
public:
	CMscnProblem(int iNumOfSup, int iNumOfFac, int iNumOfWare, int iNumOfSh);
	CMscnProblem(CMySmartPointer<CSupplier>* pcSups, int iNumOfSup, CMySmartPointer<CFactory>* pcFacs, int iNumOfFac, CMySmartPointer<CWarehouse>* pcWares, int iNumOfWare, CMySmartPointer<CShop>* pcShops, int iNumOfSh);
	CMscnProblem(const CMscnProblem& rcOther);
	~CMscnProblem();
	bool bCreateSups(string* sNames, int iNumOfSup);
	bool bCreateFacs(string* sNames, int iNumOfFac);
	bool bCreateWares(string* sNames, int iNumOfWare);
	bool bCreateShops(string* sNames, int iNumOfSh);
	bool bCreateSups(int iNumOfSup);
	bool bCreateFacs(int iNumOfFac);
	bool bCreateWares(int iNumOfWare);
	bool bCreateShops(int iNumOfSh);
	bool bConnect();
	int iChangeNumOfSup(int iNumOfSup);
	int iChangeNumOfFac(int iNumOfFac);
	int iChangeNumOfWare(int iNumOfWare);
	int iChangeNumOfSh(int iNumOfSh);
	int iGetNumOfSup();
	int iGetNumOfFac();
	int iGetNumOfWare();
	int iGetNumOfSh();

	int iChangeCD(int iSupIndex, int iFacIndex, double dNewCost);
	int iChangeCF(int iFacIndex, int iWareIndex, double dNewCost);
	int iChangeCM(int iWareIndex, int iShIndex, double dNewCost);

	int iChangeSD(int iSupIndex, double dNewCap);
	int iChangeSF(int iFacIndex, double dNewCap);
	int iChangeSM(int iWareIndex, double dNewCap);
	int iChangeSS(int iShIndex, double dNewCap);

	void vSetSupplierNames(string* psNames, int iSize);
	void vSetFactoryNames(string* psNames, int iSize);
	void vSetWarehouseNames(string* psNames, int iSize);
	void vSetShopNames(string* psNames, int iSize);
	void vSetName(CAbstractUnit* cUnit, string sName);

	void vSetSupplierCost(int iSupIndex, int iFacIndex, double dCost);
	void vSetFactoryCost(int iFacIndex, int iWareIndex, double dCost);
	void vSetWarehouseCost(int iWareIndex, int iShIndex, double dCost);

	void vSetSupProdCap(double* pdCapacities);
	void vSetFacProdCap(double* pdCapacities);
	void vSetWareCap(double* pdCapacities);
	void vSetShDemands(double* pdDemands);

	void vSetSupCosts(double* pdCosts);
	void vSetFacCosts(double* pdCosts);
	void vSetWareCosts(double* pdCosts);

	void vSetSupX(double* pdX);
	void vSetFacX(double* pdX);
	void vSetWareX(double* pdX);

	void vSetConstantSupCost(double* pdCosts);
	void vSetConstantFacCost(double* pdCosts);
	void vSetConstantWareCost(double* pdCosts);
	void vSetShopsPrices(double* pdPrices);

	void vSetSupMinMaxes(double* pdMinMaxes);
	void vSetFacMinMaxes(double* pdMinMaxes);
	void vSetWareMinMaxes(double* pdMinMaxes);

	double dCalculateKT();
	double dCalculateKU();
	double dCalculateP();
	double dCalculateProfit();
	void vPrintAll();
	void vPrintDown(string& sName);

	double tGetQuality(double* ptSolution, int iSize);
	vector<double> vConstraintSatisfied(double* pdSolution, int iSize);
	CMySmartPointer<pair<double, double>> pcCheckRange(int iSize);
	bool bSaveToFile(const string& rsFileName);
	bool bSaveResult(const string& rsFileName, double* pdSolution);
	bool bReadFromFile(const string& rsFileName);

	//lista 10
	void vGenerateInstance(int iInstanceSeed);
	int iGetResultSize();


};

#endif