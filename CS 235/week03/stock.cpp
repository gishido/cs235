#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "portfolio.h" // for PORTFOLIO
#include <stdlib.h>    // for EXIT
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

   Portfolio myPortfolio;
   int volume;
   string decision;
   Dollars price;
   Trans trans;
   char token;
   int i;
   for(;;) {
      cout << "> ";
      cin>>decision;
      if(decision=="buy")
      {
         cin>>volume;
         cin>>price; 
         myPortfolio.buy(volume, price);
      }
      else if( decision=="sell")
      {
         cin>>volume;
         cin>>price; 
         myPortfolio.sell(volume, price);
      }
      else if(decision=="display")
      {
         myPortfolio.display();
      }
      else if(decision== "quit")
         return;
   }   
};