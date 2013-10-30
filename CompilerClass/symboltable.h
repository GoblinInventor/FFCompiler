#ifndef SYMBOLTABLE_H_INCLUDED
#define SYMBOLTABLE_H_INCLUDED

#include<stack>
#include<vector>
#include<map>
#include<string>
#include "ffsymbol.h"
/**
Important routines:  FIND, INSERT, DISPLAY

Driver program:  to test FIND, INSERT, DISPLAY,
you need a driver (main) program that can:
(1) open and close scopes,
(2) check if a name is already in the symbbl table, and
(3) add it into the ST if not already there.
*/

class SymbolTable {
public:
SymbolTable(int cs, int ns) : currScope(cs), newScope(ns) {}
int newScope;
int currScope;
std::vector<int> scopeBlockStack;
std::vector<std::map<std::string, FFSymbol*> > ffProtectedSymbolTable;


//namespace FFSymbolTable {

//The reason



/*
FIND must return more than a simple boolean;  if found, it must return some means of retrieving the information in the symbol table (pointer to or copy of the record).
*/


/**
    findFFSymbol takes a string related directly to a symbol and retrieves the pointer to the symbol
    @param[in] _symbolName the name of the symbol taken directly from the code, thus if we have
    "CCC" as a identifier the input is "CCC"
    @param[out] _hashValuePointer gives you the reference to the symbol of the name "symbolName"
    in the symbol table
*/
FFSymbol* findFFSymbol(std::string symname);

/**
    insertFFSymbol takes the char* name of a symbol (again if "CCC" we accept "CCC") and returns
    @param[in] _symbolName string associated with the symbol directly
    a pointer to the value in the symbol table
    @param[out] _hashSymbolPointer pointer to access the symbol in the table
*/
FFSymbol* insertFFSymbol(std::string symname);

/**
    ONLY USE IN INITIAL ASSIGNMENT
    dumpFFSymbolTable prints a representation of the symbol table to a file with default
    name "symbolTableDump".
    @param[in] char* filename for the symbol table representation
    @param[out] void output, simply sends to a separate file
*/
void dumpFFSymbolTable(std::string fileName="symbolTableDump");

/**
	ONLY USE IN INITIAL ASSIGNMENT
	closeFFScope returns to the previous scope
	@param[in] void
	@param[out] void
*/
void closeFFScope();
/**
	ONLY USE IN INITIAL ASSIGNMENT
	openFFScope starts a new scope.
	@param[in] void
	@param[out] void
*/
void openFFScope();
};
//}
#endif // SYMBOLTABLE_H_INCLUDED
