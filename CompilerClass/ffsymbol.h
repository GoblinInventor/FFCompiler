#ifndef FFSYMBOL_H_INCLUDED
#define FFSYMBOL_H_INCLUDED
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class FFSymbol {

public:
	FFSymbol(std::string symname,int scope) : ffSymbolScope(scope), ffSymbolName(symname) {}
    ~FFSymbol () {}
	std::string getSymbolName();
	int getSymbolScope();
	//FFSymbol& operator= (const FFSymbol& symbol);
protected:
	/*
	TEMPORARY SCOPE INDICATOR
	ffScope will probably be managed differently
	*/
private:
	int ffSymbolScope;

	std::string ffSymbolName;

};




#endif // FFSYMBOL_H_INCLUDED
