#ifndef CFILE_ERR_CODE_H
#define CFILE_ERR_CODE_H
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CFileErrCode {

public:
	CFileErrCode();
	~CFileErrCode();
	bool bOpenFile(const string& sFileName, const string& sType);
	bool bCloseFile();
	bool bPrintLine(const string& sText);
	bool bPrint(const string& sText);
	bool bRead(const string& sFormat, double& tDest);
	bool bRead(const string& sFormat, int& tDest);
	bool bPrintManyLines(const vector<string>& sText);
	bool bRead(const string& sFormat, const char* tDest, int iBuffSize);
private:
	FILE *pf_file;

};//class CFileErrCode

#endif