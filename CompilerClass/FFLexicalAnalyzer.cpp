/*
Lexical Analysis:

Input: FILE.ff
Output: (void, but output to file) TOKENFILE.ff

1A) Remove all comments
@@ is single line
/@ is begin multiline
@/ is end multiline


1): Enter characters until delimiter is reached. Delimiters either
a) Nonalphanumeric characters (with the exception of "_")
or
b) alphabetic characters after numeric characters (this should result in an error)

2) Take the length of the extracted characters to match against keywords.
a) Match, assign token
b) Non-Match, assign identifier

3)

Keywords by size:

2:
IS
IF
OR

3:
RAT
INT
EIF
BEG
END
NOT
DEF
MOD
GET

4:
REAL
PROC
FUNC
DECL
ELSE
THEN
WHEN
LOOP
BOOL
TRUE

5:
CONST
WHILE
FALSE

6:
ASSERT

7:
ENDFUNC
ENDPROC
*/
#include "FFLexicalAnalyzer.h"

void getToken(const char* token) {




using namespace ffLexAnalysis;
/*
typedef int TOKEN
*/





