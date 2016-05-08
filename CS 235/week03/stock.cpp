/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <vector>
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   char input[10];
   int numShares = 0;
   Dollars price;
   Dollars proceeds;
   Queue <Dollars> Stocks;
   vector<int> NumSharesSold;
   vector<Dollars> SharePriceSold;
   vector<Dollars> profit;
   int numSoldTrans = 0;
   bool stocksBought = false;
   bool stocksSold = false;
   
   while (input[0] != 'q')
   {
   		cout << "> ";
		cin >> input;
		
		if (input[0] == 'b' || input[0] == 's')
		{
			cin >> numShares;
			cin >> price;
		}
   
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(30, '\n');
			cin >> input;
			if (input[0] == 'b' || input[0] == 's')
				{
					cin >> numShares;
					cin >> price;
				}
		}
		
		switch (input[0])
		{
			case 'b':
				buyStock(Stocks, numShares, price);
				stocksBought = true;
				break;
			case 's':
				sellStock(Stocks, numShares, price, proceeds, 
							NumSharesSold, SharePriceSold,
							profit, numSoldTrans);
				stocksSold = true;
				break;
			case 'd':
			case 'q':
				display(stocksBought, stocksSold, Stocks,
							NumSharesSold, SharePriceSold,
							profit, numSoldTrans, proceeds);
				break;
			default:
				cout << "Unrecognized command, please reenter...\n";
				break;
		}
   }
}

void buyStock(Queue <Dollars> & MyStocks, int myShares, Dollars sharePrice)
{
	for(int i = 0; i < myShares; i++)
		MyStocks.push(sharePrice);
}

void sellStock(Queue <Dollars> & MyStocks, int myShares, Dollars sharePrice, Dollars & myProceeds,
				vector<int> & pNumSharesSold, vector<Dollars> & pSharePriceSold,
				vector<Dollars> & pProfit, int & pNumSoldTrans)
{
	Dollars profitOrLoss;
	Dollars totalProfit;
	for(int i = 0; i < myShares; i++)
	{
		profitOrLoss = sharePrice - MyStocks.front();
		myProceeds += profitOrLoss;
		totalProfit += profitOrLoss;
		MyStocks.pop();
	}
	pNumSharesSold.push_back(myShares);
	pSharePriceSold.push_back(sharePrice);
	pProfit.push_back(totalProfit);
	pNumSoldTrans++;
}

void display(bool bought, bool sold, Queue <Dollars> & MyStocks,
				vector<int> & pNumSharesSold, vector<Dollars> & pSharePriceSold,
				vector<Dollars> & pProfit, int & pNumSoldTrans, Dollars & myProceeds)
{
	Queue<Dollars> Temp(MyStocks);
	Dollars tempVal;
	int tempShares = 1;
	
	if(bought)
	{
		cout << "Currently held:\n";
		while(!Temp.empty())
		{
			tempVal = Temp.front();
			Temp.pop();
			if(Temp.empty())
				cout << "\tBought " << tempShares << " shares at " << tempVal << endl;
			else
			{
				if(tempVal == Temp.front())
					tempShares++;
				else
				{
					cout << "\tBought " << tempShares << " shares at " << tempVal << endl;
					tempShares = 1;
				}
			}
		}
	}
	
	if(sold)
	{
		cout << "Sell History:\n";
		for(int i = 0; i < pNumSoldTrans; i++)
			cout 	<< "\tSold " << pNumSharesSold[i] << " shares at "
					<< pSharePriceSold[i] << " for a profit of " << pProfit[i]
					<< endl;
	}
	
	cout << "Proceeds: " << myProceeds << endl;
}