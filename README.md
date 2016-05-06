# 3050 Group Project


### Project Goal
The goal of this project was to design and implement a simple trading algorithm that could be used for trading strategies in investment firms. Investment firm X are responsible for trading a stock for company Y. Company X can predict the stocks for the company Y for the n days with a reasonable amount of accuracy. The predicted prices are Pn, where n is the day number. The goal of this strategy is to buy and sell stocks of company Y in order to max profits.

The strategy is that Y’s stock would be bought on day b1. Then Y’s stock will be sold on s1. The next day will repeat. If r = 1 the optimal trading strategy is buy at day 1 and sell at day 4. If r = 3 then the optimal trading strategy is to buy at day 1 and sell at day 4. Then buy on day 5 and sell at six.


### How To Use

A computer with a command line is needed.

Included is an input file. The main program files and a make file. In terminal, navigate to the 3050_Final_Project folder. You would need to compile the program so use the make command. To run the project you would need to type the following command:

  program name, number of days, r value and FILENAME

  FILENAME is the input file that would be included.
