# ReadMe
## Ben Black, Brandon Finley


### Issues Encountered:
After outlining the initial grammar and running `bison -d`, we had roughly 30 reduce/reduce errors and roughly 100 shift/reduce errors.  
We solved the reduce/reduce errors in one swoop by amppending a missing terminal in our grammar.  
We eliminated a number of the shift/reduce errors by first dictating precedence for the mathematical operators.  
We eliminated more by dictating precedence for the IF ELSE keywords.  
As of Monday March 19 2018 we have 60 remaining S/R errors.  
These remaining S/R errors all concern this rule:

```
expr: expr op expr
```

Upon examining the `tiger.output` file that `bison -d` produces, we found that at almost every possible instance, the compiler
is confused about whether to shift at the first `expr` or to reduce at the last `expr` present in some other rule.  
Solution pending.

Later, when adding array indexing, there was another reduce/reduce conflict between array indexing (lvalue) and array creation (expr). This was not resolved, and remains a problem. Right now, programs of the style

    x[5] := 6

Gives a syntax error.

There is also something funny happening with strings, so many string expressions also give errors.

### Test design

To make testing easier, we copied various code examples from the tiger reference manual, and put them in files in the `language_examples` folder. The catch framework then parses those files, and prints out the parsed output to inspect by hand. Since printed output is also a valid tiger program, it compiles the result again, and prints it again, and checks if they are the same. So there are elements of both automatic and hand testing.

### AST design

The AST was designed to capture as much type structure as possible. So there is an expression, lvalue, etc class which all expressions, lvalues, etc, inherit from. This allows basic type checking in the AST, and also gives any recursive analysis run more information.
