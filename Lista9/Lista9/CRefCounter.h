#ifndef CREF_COUNTER_H
#define CREF_COUNTER_H

class CRefCounter {
public:
	CRefCounter() { i_count = 0; }
	int iAdd() { return(++i_count); }
	int iDec() { return(--i_count); };
	int iGet() { return(i_count); }
private:
	int i_count;
};//class CRefCounter

#endif