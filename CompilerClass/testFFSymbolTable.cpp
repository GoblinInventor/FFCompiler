#include "testFFSymbolTable.h"

//using namespace FFSymbolTable;


int main() {
std::vector<std::string> tests;
tests.push_back("ffSymbolTest0.txt");
tests.push_back("ffSymbolTableTest2.txt");
tests.push_back("ffSymbolTableTest1.txt");

for (unsigned int q = 0; q < tests.size(); q++) {

SymbolTable* FFSymTab = new SymbolTable(-1,0);

FFSymTab->scopeBlockStack.push_back(0);

	std::cout << "qnum: " << q << std::endl;
	std::ifstream testFileQ (tests[q].c_str(), std::ifstream::in);
	std::string line;
    int n = 0;
	std::string curriden;
	int o = 0;
	//while (testFileQ.is_open()) {
		//std::cout << o << "th open" << std::endl;
	//	o
		while (getline (testFileQ,line)) {
			n++;
			bool holdOpen = false;
			bool holdClose = false;
			std::cout << n << "th getline" << std::endl;
			for (std::string::iterator i = line.begin(); i != line.end(); i++) {
				bool newiden = false;
				switch (*i) {
					case '{':
						newiden = (curriden != "");
						holdOpen = true;
						break;
					case '}':
						newiden = (curriden != "");
						holdClose = true;
						break;
					case ' ':
						newiden = (curriden != "");
						break;
					case '\n':
						newiden = (curriden != "");
						break;
					case '\t':
						newiden = (curriden != "");
						break;
					default:
						curriden+=*i;
						break;
				}
				if (newiden) {
					//if (FFSymTab->findFFSymbol(curriden) == NULL) {
						std::cout << "newiden: " << curriden << " :: currScope: " << FFSymTab->currScope << " :: scopeBlockStack size: " << FFSymTab->scopeBlockStack.size() << std::endl;
						FFSymTab->insertFFSymbol(curriden);
						curriden="";
					//}
				}
				if (holdOpen) {
					FFSymTab->openFFScope();
					holdOpen = false;
				}
				if (holdClose) {
					FFSymTab->closeFFScope();
					holdClose=false;
				}
			}
		}
	//}
	FFSymTab->dumpFFSymbolTable(tests[q]+".output");
	delete FFSymTab;
}

return 0;

}
