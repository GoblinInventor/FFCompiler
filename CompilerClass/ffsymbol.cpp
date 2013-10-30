#include "ffsymbol.h"
/*
FFSymbol::FFSymbol(std::string name, int scope) {
    ffSymbolName = name;
    ffSymbolScope = scope;
}
*/
/*
FFSymbol& FFSymbol::operator= (const FFSymbol& symbol) {
	ffSymbolName = symbol.ffSymbolName;
	ffSymbolScope = symbol.ffSymbolScope;
	return *this;
}
*/

std::string FFSymbol::getSymbolName() {
	return ffSymbolName;
}

int FFSymbol::getSymbolScope() {
	return ffSymbolScope;
}
