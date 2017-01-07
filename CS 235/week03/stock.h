/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM
#include <vector>

// the interactive stock buy/sell function
void stocksBuySell();
void buyStock(Queue <Dollars> & MyStocks, int myShares, Dollars sharePrice);
void sellStock(Queue <Dollars> & MyStocks, int myShares, Dollars sharePrice, Dollars & myProceeds,
				std::vector<int> & pNumSharesSold, std::vector<Dollars> & pSharePriceSold,
				std::vector<Dollars> & pProfit, int & pNumSoldTrans);
void display(bool bought, bool sold, Queue <Dollars> & MyStocks,
				std::vector<int> & pNumSharesSold, std::vector<Dollars> & pSharePriceSold,
				std::vector<Dollars> & pProfit, int & pNumSoldTrans, Dollars & myProceeds);

#endif // STOCK_H

