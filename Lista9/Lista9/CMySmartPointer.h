#ifndef CMY_SMART_POINTER_H
#define CMY_SMART_POINTER_H
#include "CRefCounter.h"
#include <iostream>

static const bool DEBUG = false;

using namespace std;

//////////////////////////////////////
//definition:

template <typename T>
class CMySmartPointer {
public:
	CMySmartPointer();
	CMySmartPointer(T* ptPointer, int iTabSize = 0);
	CMySmartPointer(const CMySmartPointer& rcOther);
	~CMySmartPointer();
	T& operator*();
	T* operator->();
	void operator=(const CMySmartPointer& rcOther);
	void assign(T* ptTable, int iTabSize);
	T& rtAt(int iOffset);
	void vSet(const T& tVal, int iOffset);
	int iGetTabSize();
private:
	CRefCounter* pc_counter;
	T* pt_pointer;
	int i_tab_size;
};//class CMySmartPointer
/////////////////////////////////////////////////////////////////////////

//////////////////////////////////////
//implementation::

template<typename T>
CMySmartPointer<T>::CMySmartPointer() {
	if (DEBUG) {
		cout << "constr smart pointer default" << endl;
	}//if
	pt_pointer = NULL;
	pc_counter = new CRefCounter();
	i_tab_size = 0;

}//CMySmartPointer<T>::CMySmartPointer()

template<typename T>
CMySmartPointer<T>::CMySmartPointer(T* ptPointer, int iTabSize) {
	if (DEBUG) {
		cout << "constr smart pointer param" << endl;
	}//if
	i_tab_size = iTabSize;

	pt_pointer = ptPointer;
	pc_counter = new CRefCounter();
	pc_counter->iAdd();
}//CMySmartPointer<T>::CMySmartPointer(T* ptPointer, bool bIsTable, int iTabSize)

template<typename T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer<T>& rcOther) {
	if (DEBUG) {
		cout << "copy constr smart pointer" << endl;
	}//if
	i_tab_size = rcOther.i_tab_size;

	pt_pointer = rcOther.pt_pointer;
	pc_counter = rcOther.pc_counter;
	pc_counter->iAdd();
}//CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer<T>& rcOther)

template<typename T>
CMySmartPointer<T>::~CMySmartPointer() {
	if (DEBUG) {
		cout << "destr smart pointer" << endl;
	}//if
	if (pc_counter->iDec() == 0) {
		if (DEBUG) {
			cout << "reference counter == 0, deleting" << endl;
		}//if
		if (i_tab_size > 0) {
			delete[] pt_pointer;
		}//if
		else {
			delete pt_pointer;
		}//else
		delete pc_counter;
	}//if
	else {
		if (pc_counter->iGet() < 0) {
			delete pc_counter;
		}//if
		if (DEBUG) {
			cout << "reference counter != 0, not deleting anything" << endl;
		}//if
	}//else
}//CMySmartPointer<T>::~CMySmartPointer()

template<typename T>
T& CMySmartPointer<T>::operator*() {
	return(*pt_pointer);
}//T& CMySmartPointer<T>::operator*()

template<typename T>
T* CMySmartPointer<T>::operator->() {
	return pt_pointer;
}//T* CMySmartPointer<T>::operator->()

template<typename T>
int CMySmartPointer<T>::iGetTabSize() {
	return i_tab_size;
}//int CMySmartPointer<T>::iGetTabSize()

template<typename T>
void CMySmartPointer<T>::operator=(const CMySmartPointer<T>& rcOther) {
	if (this != &rcOther) {
		if (this->pt_pointer != NULL) {
			if (pc_counter->iDec() == 0) {
				if (i_tab_size > 0) {
					delete[] pt_pointer;	
				}//if
				else {
					delete pt_pointer;
				}//else
				delete pc_counter;
			}//if
			else {
				if (pc_counter->iGet() < 0) {
					delete pc_counter;
				}//if
			}//else
		}//if
		else {
			if (pc_counter->iGet() <= 0) {
				delete pc_counter;
			}//if
		}//else
		i_tab_size = rcOther.i_tab_size;
		pc_counter = rcOther.pc_counter;
		pt_pointer = rcOther.pt_pointer;
		pc_counter->iAdd();
	}//if
}//void CMySmartPointer<T>::operator=(const CMySmartPointer<T>& rcOther)

template<typename T>
void CMySmartPointer<T>::assign(T* ptPointer, int iTabSize) {
	if (this->pt_pointer != NULL) {
		if (pc_counter->iDec() == 0) {
			if (i_tab_size > 0) {
				delete[] pt_pointer;
			}//if
			else {
				delete pt_pointer;
			}//else
			delete pc_counter;
		}//if
	}//if
	else {
		if (pc_counter->iGet() <= 0) {
			delete pc_counter;
		}//if
	}//else
	i_tab_size = iTabSize;
	pt_pointer = ptPointer;
	pc_counter = new CRefCounter();
	pc_counter->iAdd();
}

/////////////////////////////////////////////////////////////////////////

//modyfikacja:

template<typename T>
T& CMySmartPointer<T>::rtAt(int iOffset) {
	if (i_tab_size > 0) {
		if (iOffset < i_tab_size && iOffset >= 0) {
			return pt_pointer[iOffset];
		}//if
		else {
			throw exception("Index out of bounds");
		}//else
	}//if
	else {
		throw exception("Type is not an array type");
	}//else
}//T CMySmartPointer<T>::ptAt(int iOffset)

template<typename T>
void CMySmartPointer<T>::vSet(const T& tVal, int iOffset) {
	if (i_tab_size > 0) {
		if (iOffset < i_tab_size && iOffset >= 0) {
			T t_val;
			t_val = tVal;
			pt_pointer[iOffset] = t_val;
		}//if
		else {
			throw exception("Index out of bounds");
		}//else
	}//if
	else {
		throw exception("Type is not an array type");
	}//else
}//T CMySmartPointer<T>::ptAt(int iOffset)


#endif

