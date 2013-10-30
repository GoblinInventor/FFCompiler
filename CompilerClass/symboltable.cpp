#include "symboltable.h"


FFSymbol* SymbolTable::findFFSymbol(std::string symname) {
	FFSymbol* returnSym;
	if (ffProtectedSymbolTable[currScope].find(symname) != ffProtectedSymbolTable[currScope].end()) {
		returnSym = ffProtectedSymbolTable[currScope][symname];
	}
	else {
		returnSym = NULL;
	}
}

FFSymbol* SymbolTable::insertFFSymbol(std::string symname) {
    if (ffProtectedSymbolTable[currScope].find(symname) == ffProtectedSymbolTable[currScope].end()) {
		FFSymbol* newSymbol = new FFSymbol(symname, currScope);
		ffProtectedSymbolTable[currScope][symname] = newSymbol;
    }
    FFSymbol* returnSym = ffProtectedSymbolTable[currScope][symname];
	return returnSym;
}

void SymbolTable::openFFScope() {
	std::cout << "open" << std::endl;
	std::cout << "scopeBlockStack.size(): " << scopeBlockStack.size() << std::endl;
	scopeBlockStack.push_back(newScope);
	std::cout << "scopeBlockStack.size() after push: " << scopeBlockStack.size() << std::endl;
	std::map<std::string, FFSymbol*> newScopeMap;
	ffProtectedSymbolTable.push_back(newScopeMap);
	std::cout << "ffProtectedSymbolTable.size(): " << ffProtectedSymbolTable.size() << std::endl;
	std::cout << "currScope: " << currScope << ", newScope: " << newScope << std::endl;
	currScope = newScope;
	newScope = newScope+1;
	return;
}

void SymbolTable::closeFFScope() {
	std::cout << "close" << std::endl;
	scopeBlockStack.pop_back();
	currScope = scopeBlockStack.back();
	return;
}

void SymbolTable::dumpFFSymbolTable(std::string filename) {
	std::ofstream tableDumpFileHandle;
	tableDumpFileHandle.open(filename.c_str());
	std::cout << "dumpFFSymbolTable" << std::endl;
	for (int q = 0; q < ffProtectedSymbolTable.size(); q++) {
		if (ffProtectedSymbolTable[q].size() > 0) {
			for (std::map<std::string, FFSymbol*>::iterator i = ffProtectedSymbolTable[q].begin(); i != ffProtectedSymbolTable[q].end(); i++) {

				tableDumpFileHandle << "SCOPE: " << q << ", NAME: " << i->second->getSymbolName() << std::endl;
			}
		}
		else {
			tableDumpFileHandle << "SCOPE EMPTY: " << q << std::endl;
		}
	}
	tableDumpFileHandle.close();
	std::cout << "symbol table dump complete" << std::endl;
}

