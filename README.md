Algebraic Expression Graphing Calculator

A graphing calculator and computational numeric system with GUI interface.

Calculator by Zachary Meeks
GUI interface and plotting functionality by Gregory Miles

Note: GUI Interface and graphing code not included here.

This project was done for CS20 Independent Study at Pasadena City College with
Dr Wilkinson.

Note:
hard drive crashed since final project. Fixed most bugs to be same as final project level of functionality, but a few bugs still need refixing including:
—need to fix compilation warnings
—need to fix eval(#) for # a decimal number
——can get around this issue temporarily by manually converting decimals to fractions
Additionally, could add the beta plot function with extra parsing so as to skip the corner cases (or just fix plot to handle corner cases)

#Commands:

Function names can be anything from a-z except x and &.

For assignment use:

(function name)= function

eval (function name)(number)

print (function name)

plot (function name)

For taking integrals use:(function name)= $(function name)

For taking derivative use:(function name)= (function name)'

Other common operators are also used: +-*/ and for exponents ^

Numbers can be fraction or decimals.

To do the natural log first 

(function name A)=(variable)^-1

then 

(function name)=$(function name A)

#Examples:

Save a function:

p=x^4+x^3

Then take integral:

p=$p 

Then plot:

plot p

Then evaluate at a point:

eval p(7)

Then print out p:

print p

Then take derivative of function:

p=p'

Functions can also be added add, subtract, divide and multiply function:
(If the natural log is in the denominator of a function divide the
program is not yet designed to handle this situation)

q=x^3+x^7

Add the function q and p together:

z=q+p

print z

plot z

eval z(7)

After clicking or tabbing to the graph, it can be
manipulated using arrow keys and + will zoom and - will zoom out.

#BUGS:

Graphing natural Log does not work but the bug for why it occurs is known 
to be that natural log can not handle negative numbers and zero.  Further
programming time would be required to patch this bug.

* * * * * * * * * * * * * *
Future Additions and Fixes:

The color scheme needs to be tweaked so that the graph is more visible.

A good idea also would be the ability to save past graphs and simultaneously
display them on the screen.

Another future feature would be the addition of 3D graphs and capabilities.

Add definite integral capability to evaluate function

Add +C notation to default indefinite integral evaluation

Add numeric methods to integration evaluation so that calculator can evaluate non-elementary integrals - - - will need to modify parsing to catch when this occurs.
Also, could add more advanced parsing for elementary integrals.

Add asymptotic lines to plots involving asymptotes

Add apt comments to header files

