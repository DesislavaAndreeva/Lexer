# Lexer

# General info

University evaluation project in formal languages and language processors

# Description

Lexical analysis is the first phase of a compiler. It takes the modified source code from language preprocessors that are written in the form of sentences. The lexical analyzer breaks these syntaxes into a series of tokens, by removing any whitespace or comments in the source code.

If the lexical analyzer finds a token invalid, it generates an error. The lexical analyzer works closely with the syntax analyzer. It reads character streams from the source code, checks for legal tokens, and passes the data to the syntax analyzer when it demands.

Lexemes are said to be a sequence of characters (alphanumeric) in a token. There are some predefined rules for every lexeme to be identified as a valid token. These rules are defined by grammar rules, by means of a pattern. A pattern explains what can be a token, and these patterns are defined by means of regular expressions.

In programming language, keywords, constants, identifiers, strings, numbers, operators and punctuations symbols can be considered as tokens.

For example, in C language, the variable declaration line

```
int value = 100;
```

contains the tokens:

```
int (keyword), value (identifier), = (operator), 100 (constant) and ; (symbol).
```

# Grammar rules

This lexical analyzer should recognize:

• **Identifier** (type/code = 100/0);

• **Real constant** (type/code = 200/0);

• **Keywords** (type 300) - **if** (code 301), **else** (code 302), **for** (code 303);

• **Symbols** (type 400): 

        ( (code 404);
        
        ) (code 405); 
        
        ; (code 408);

• **Operators** (type 400):

      + (code 401); 
      
      * (code 402); 
      
      = (code 403); 
      
      > (code 407); 
      
      < (code 406);
      
      
 # Compile
 
```
gcc lexer.cpp -o lexer -lstdc++
```
 
 # Run
 
 ```
./lexer
 ```
 
 # Example 

```
Enter a text for lexical analysis: 
for ( i=0; i<10; i++)                 

====================================================================
==================Lexical Analyzer==================================
====================================================================
| Type Num | Code |  Type        | Token                         
--------------------------------------------------------------------
| 300      | 303  |  Keyword     | ' for ' 
| 400      | 405  |  Symbol      | ' ( ' 
| 400      | 403  |  Operator    | ' = ' 
| 100      | 0    |  Identifier  | ' i ' 
| 400      | 408  |  Symbol      | ' ; ' 
| 200      | 0    |  Real Const  | ' 0 ' 
| 400      | 406  |  Operator    | ' < ' 
| 100      | 0    |  Identifier  | ' i ' 
| 400      | 408  |  Symbol      | ' ; ' 
| 200      | 0    |  Real Const  | ' 10 ' 
| 400      | 401  |  Operator    | ' + ' 
| 100      | 0    |  Identifier  | ' i ' 
| 400      | 401  |  Operator    | ' + ' 
| 400      | 404  |  Symbol      | ' ) ' 
====================================================================
```
 
