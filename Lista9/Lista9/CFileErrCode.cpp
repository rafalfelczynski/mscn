#include "CFileErrCode.h"

CFileErrCode::CFileErrCode() {
        pf_file = NULL;
}//CFileErrCode::CFileErrCode()

CFileErrCode::~CFileErrCode() {
        bCloseFile();
}//CFileErrCode::~CFileErrCode()

bool CFileErrCode::bOpenFile(const string& sFileName, const string& sType) {
        if (pf_file == NULL) {
                fopen_s(&pf_file, sFileName.c_str(), sType.c_str());
                return pf_file == NULL ? false : true;
        }//if
        else {
                return false;
        }//else
}//bool CFileErrCode::bOpenFile(CString sFileName)

bool CFileErrCode::bCloseFile() {
        if (pf_file == NULL) {
                return false;
        }//if (pf_file == NULL)
        else {
                if (fclose(pf_file) == 0) {
                        pf_file = NULL;
                        return true;
                }//if
                else {
                        return false;
                }//else
        }//else
}//bool CFileErrCode::bCloseFile()

bool CFileErrCode::bPrintLine(const string& csText) {
        if (pf_file != NULL) {
                if (fprintf(pf_file, "%s\n", csText.c_str()) < 0) {
                        return false;
                }//if
                else {
                        return true;
                }//else
        }//if
        else {
                return false;
        }//else
}//bool CFileErrCode::bPrintLine(CString csText)

bool CFileErrCode::bPrint(const string& csText) {
        if (pf_file != NULL) {
                if (fprintf(pf_file, "%s", csText.c_str()) < 0) {
                        return false;
                }//if
                else {
                        return true;
                }//else
        }//if
        else {
                return false;
        }//else
}//bool CFileErrCode::bPrint(CString csText)


bool CFileErrCode::bPrintManyLines(const vector<string>& vsText) {
        for (string cs_text : vsText) {
                if (!bPrintLine(cs_text)) {
                        return false;
                }//if
        }//for
        return true;
}//bool CFileErrCode::bPrintManyLines(vector<CString> vsText)

bool CFileErrCode::bRead(const string& sFormat, double& tDest) {
        if (pf_file != NULL) {
                try {
                        fscanf_s(pf_file, sFormat.c_str(), &tDest);
                }
                catch (exception& e) {
                        cout << e.what() << endl;
                }
                return true;
        }
        else {
                return false;
        }
}

bool CFileErrCode::bRead(const string& sFormat, int& tDest) {
        if (pf_file != NULL) {
                try {
                        fscanf_s(pf_file, sFormat.c_str(), &tDest);//sFormat.c_str(), tDest);
                        //cout << tDest << endl;
                }
                catch (exception& e) {
                        cout << e.what() << endl;
                }
                return true;
        }
        else {
                return false;
        }
}

bool CFileErrCode::bRead(const string& sFormat, const char* tDest, int iBuffSize) {
        if (pf_file != NULL) {
                try {
                        fscanf_s(pf_file, sFormat.c_str(), tDest, iBuffSize);
                }
                catch (exception& e) {
                        cout << e.what() << endl;
                }
                return true;
        }
        else {
                return false;
        }
}