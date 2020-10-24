# Lexer
Implementation of a lexical analyzer that recognizes:

• Identifier (type/code = 100/0);
• Real constant (type/code = 200/0);
• Keywords (type 300) - if (code 301), other (code 302), for (code 303);

• Symbols (type 400): 
        ( - (code 404);
        ) - (code  405); 
        ; - (code 408);

• Operators (type 400):
      + (code 401); 
      * (code 402); 
      = (code 403); 
      > (code 407); 
      < (code 406);
