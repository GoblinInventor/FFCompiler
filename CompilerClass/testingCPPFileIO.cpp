#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <iostream>

enum ffToken {
	ffIdentifierToken, //identifier
	ffLiteralToken, // [integer], FALSE, TRUE
	ffTypeToken, //RAT INT REAL
	ffAdditionOp, //+, -, or
	ffMultiplicationOp, //*, /, MOD, AND
	ffRelationOp, // ==, >, <. >=, <=
	ffPeriod, //'.'
	ffComma, //','
	ffBracket, // {, }, (, ), [, ]
	ffQuote, // ", '
	ffFunctionOp, //FUNC, PROC, ENDFUNC, ENDPROC
	ffLoop, //LOOP, ENDLOOP
	ffWhile, //WHILE, ENDWHILE
	ffDeclare, //DECL
	ffGet, //GET
	ffPut, //PUT
	ffColon, //:
	ffAssign, //:=
	ffIs, //IS
	ffErrorToken, //any non-assigned character
	ffEOF // no lexeme
}






/*
POSSIBLE FUNCTION FOR CREATING DFA FOR DEBUG

void printDFA
*/

enum ffChar {
	ffErrorChar, ffUpperAlphaChar, ffLowerAlphaChar, ffDigitChar,
	ffWhiteSpaceChar, ffUnderscoreChar, ffSingleQuoteDelimChar, ffDoubleQuoteDelimChar, ffRelationOperatorDelimChar,
	ffLeftBoundDelimChar, ffRightBoundDelimChar, ffColonAssignDelimChar, ffEqualOperatorDelimChar; ffMultiplicativeOperatorDelimChar,
	ffArithOperatorDelimChar,
};

/*
Initialization char code map modelled on Ronald Mak: Writing Compilers And Interpreters
*/
void initializeCharacterCode() {
	int i;
	for (i = 0; i <= 127; ++i) {
		lc_charToType[i] = ffErrorChar;
	}
	for (i = 'a'; i <= 'z'; ++i) {
		lc_charToType[i] = ffUpperAlphaChar;
	}
	for (i = 'A'; i <= 'Z'; ++i) {
		lc_charToType[i] = ffLowerAlphaChar;
	}
	for (i = '0'; i <= '9'; ++i) {
		lc_charToType[i] = ffDigitChar;
	}
	//numeric op chars
	charToType['_'] ffUnderscoreChar;
	charToType['+'] = ffArithOperatorDelimChar;
	charToType['-'] = ffArithOperatorDelimChar;
	charToType['/'] = ffMultiplicativeOperatorDelimChar;
	charToType['*'] = ffMultiplicativeOperatorDelimChar;
	charToType['^'] = ffExponentialDelimChar;
	//relat chars
	charToType['<'] = ffRelationOperatorDelimChar;
	charToType['>'] = ffRelationOperatorDelimChar;
	charToType[':'] = ffColonAssignDelimChar;
	charToType['='] = ffEqualOperatorDelimChar;
	//bracket chars
	charToType['('] = ffLeftBoundDelimChar;
	charToType[')'] = ffRightBoundDelimChar;
	charToType[']'] = ffRightBoundDelimChar;
	charToType['['] = ffLeftBoundDelimChar;
	charToType['{'] = ffLeftBoundDelimChar;
	charToType['}'] = ffRightBoundDelimChar;
	//Punctuation Chars
	charToType['.'] = ffPunctuationDelimChar;
	charToType[','] = ffPunctuationDelimChar;
	charToType[';'] = ffPunctuationDelimChar;
	//Quote Chars
	charToType['\''] = ffSingleQuoteChar;
	charToType['"'] = ffDoubleQuoteChar;
	//whitespace chars
	charToType['\n'] = ffWhiteSpaceChar;
	charToType['\t'] = ffWhiteSpaceChar;
	charToType[' '] = ffWhiteSpaceChar;
	charToType['\0'] = ffWhiteSpaceChar;
	//comment char
	charToType['@'] = ffCommChar;
}








enum transitionState {
	qInitial,
	qReserved,
	qIdentAlpha,
	qIdentUnderScore,
	qIdentAlphaNum,
	qNumberDigit,
	qDelimOrBlank,
	qComment,
	qError
};

enum delimiterState {
	qRelationOperatorDelim,
	qEqualOperatorDelim;
	qColonAssignDelim;
	qPunctuationDelim,
	qRightBoundDelim;
	qLeftBoundDelim;
	qSingleQuoteDelim;
	qDoubleQuoteDelim;
	qBlankDelim;
}

/*
	ffErrorChar, ffUpperAlphaChar, ffLowerAlphaChar, ffDigitChar, ffDelimChar, ffSingleQuoteChar, ffDoubleQuoteChar, ffWhiteSpaceChar, ffUnderscoreChar
*/

enum transitionState stateMove(char newchar, enum transitionState currState) {
	enum transitionState retState;
	if (currState == qError) {
			retState = qError;
	}
	else if (currState == qReserved) {
		if (charToType[newchar] == ffUpperAlphaChar) {
				retState = qReserved;
		}
		else if (charToType[newchar] == ffUnderscoreChar) {
			retState = qIdentUnderscore;
		}
		else if (charToType[newchar] == ffLowerAlphaChar) {
				retState = qIdentAlpha;
		}
		else if (charToType[newchar] == ffDigitChar) {
				retState = qIdentAlphaNum;
		}
	}
	else if (currState == qIdentAlpha) {
		if (charToType[newchar] == ffLowerAlphaChar || charToType[newchar] == ffUpperAlphaChar) {
				retState = qIdentAlpha;
		}
		else if (charToType[newchar] == ffUnderscoreChar) {
				retState = qIdentUnderscore;
		}
		else if (charToType[newchar] == ffDigitChar) {
				retState = qIdentAlphaNum;
		}
		else if (charToType[newchar] == ffSingleDelimChar) {
				retState = qSingleDelim;
		}
		else if (charToType[newchar] == ffDoubleDelimChar) {
				retState = qDoubleDelim;
		}
		else {
				retState = qError;
		}
	}
	else if (currState == qIdentUnderscore) {
		if (charToType[newchar] == ffLowerAlphaChar || charToType[newchar] == ffUpperAlphaChar) {
				retState = qIdentAlpha;
		}
		else if (charToType[newchar] == ffDigitChar) {
				retState = qIdentAlphaNum;
		}
		else if (charToType[newchar] == ffUnderscoreChar) {
				retState = qError;
		}
		else if (charToType[newchar] == ffDelimOrBlankChar) {
				retState = qDelimOrBlank;
		}
		else {
			retState = qError;
		}
	}
	else if (currState == qIdentAlphaNum) {
		if (charToType[newchar] == ffDigitChar) {
				retState = qIdentAlphaNum;
		}
		else if (charToType[newchar] == ffUpperAlphaChar || charToType[newchar] == ffLowerAlphaChar) {
				retState = qError;
		}
		else if (charToType[newchar] == ffDelimOrBlankChar) {
			retState = qDelimOrBlank;
		}
		else {
				retState = qError;
		}
	}






void lc_getToken(std::string fmt_lineString,std::vector<std::string> &ret_tokens) {
    std::string::iterator itr_lineStringIteratorBegin = fmt_lineString.begin();
    //std::string::iterator itr_lineStringIteratorEnd = fmt_lineString.begin();
    int moved = 0;
    bool cond_Delimiter=false;
    while (itr_lineStringIteratorBegin != fmt_lineString.end()) {
            cond_Delimiter = lc_isDelimiter(*(itr_lineStringIteratorBegin+moved));
            if (cond_Delimiter) {
				char lc_delimiter = *(itr_lineStringIteratorBegin+moved);
				std::string lc_str_delimiter;
				lc_str_delimiter += lc_delimiter;
				std::cout << "found token" << std::endl;
                std::string lc_currToken(itr_lineStringIteratorBegin, itr_lineStringIteratorBegin+moved);
                std::cout << "lc_currToken: " << lc_currToken << std::endl;
                ret_tokens.push_back(lc_currToken);
                std::cout << "delimiter: " << lc_str_delimiter << std::endl;

			    ret_tokens.push_back(lc_str_delimiter);
                itr_lineStringIteratorBegin += moved;
                moved=1;
            }
            else {
                moved++;
            }
    }
}

void lc_tokenDump(std::vector<std::string> val_tokens, std::ofstream& out_token_file) {
    for (int i = 0; i < val_tokens.size(); i++) {
        out_token_file << val_tokens[i];
    }
    return;
}






int main() {
    std::ifstream raw_file;
    std::ofstream raw_output_file;
    raw_file.open("lexerTest1.ff", std::ios::in);
    raw_output_file.open("testFileIODump.txt", std::ios::app);
    //std::string fmt_lineString;
    //streamsize lineBufferLen = getline(raw_file,fmt_lineString);
    bool cond_keepReading = true;
	std::string fmt_lineString;
    while (getline(raw_file,fmt_lineString)) {
		std::vector<std::string> ref_tokens;
		lc_getToken(fmt_lineString,ref_tokens);
		lc_tokenDump(ref_tokens, raw_output_file);
	}
}



