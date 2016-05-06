3050 Group Project


The goal of this project was to design and implement a
simple trading algorithm that could be used for trading
 strategies in investment firms. Investment firm X are
 responsible for trading a stock for company Y. Company
 X can predict the stocks for the company Y for the n
days with a reasonable amount of accuracy.
The predicted prices are Pn, where n is the day number.
The goal of this strategy is to buy and sell stocks of
company Y in order to max profits.

The strategy is that Y’s stock would be bought on day b1.
Then Y’s stock will be sold on s1. The next day will
repeat. If r = 1 the optimal trading strategy is buy at
day 1 and sell at day 4. If r = 3 then the optimal
trading strategy is to buy at day 1 and sell at day 4.
Then buy on day 5 and sell at six.



The MIT License (MIT)
Copyright (c) 2016

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


How To Use

A computer with a command line is needed.

Included is an input file. The main program files and a make file. In terminal, navigate to the
3050_Final_Project folder. You would need to compile the program so use the make command. To run the project you would
need to type the following command:

  a.out FILENAME

  FILENAME is the input file that would be included.
