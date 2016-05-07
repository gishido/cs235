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
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
#include "portfolio.h" // for PORTFOLIO
#include <stdlib.h>    // for EXIT
// #include <boost/algorithm/string.hpp>  
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

   // your code here..
   Portfolio myPortfolio;
   string volume;
   string decision;
   string price;
   Trans trans;
   char token;
   string volString;
   string dollarsString;
   string centsString;
   int i;
   int vol;
   int dollars;
   int cents;
   int centsTotal;
   do
   {
      cout << "> ";
      cin>>decision;
      cin>>volume;
      cin>>price;
      dollarsString = '0';
      if (decision == "buy")
      {
         //skip first 4 "buy " and get buy volume
         for(i=0; i < volume.length(); i++)
         {
            token=volume[i];
            volString.push_back(token);
         }
         vol=atoi(volString.c_str());
         trans.volume=vol;
         //skip the next space and $
         i=+2;

         int beforePeriod;
         int afterPeriod;
         bool flag = false;
         int total;
         //get the dollars
         for(i=0; i < price.length(); i++)
         {  
            if (price[i] == '.')
            {
               beforePeriod = ((atoi(dollarsString.c_str())) *  100);
               flag = true;
               token = '\0';
               dollarsString = '0';
            }
            else
            {
               token = price[i];
               dollarsString.push_back(token);
            }
            
         }
         afterPeriod = atoi(dollarsString.c_str());
         if (!flag)
         {
            afterPeriod = ((atoi(dollarsString.c_str())) *  100);
            total = afterPeriod;
         }
         else
         {
            total = beforePeriod + afterPeriod;
         }
         cerr << total << endl;
         Dollars price(total);
         myPortfolio.buy(vol, total);
      }
      else if(volume[0]=='s')
      {
         //skip first 5 "sell " and get buy volume
         for(i=4; token!=' '; i++)
         {
            token=volume[i];
            volString.push_back(token);
         }
         vol=atoi(volString.c_str());
         trans.volume=vol;
         //skip the next space and $
         i=+2;
         //get the dollars
         for(i; token!='.';i++)
         {
            token=volume[i];
            dollarsString.push_back(token);
         }
         dollars=atoi(dollarsString.c_str());
         //get the cents
         centsString.push_back(volume[i]);
         i++;
         centsString.push_back(volume[i]);
         cents=atoi(centsString.c_str());
         //convert price into cents only
         centsTotal=(dollars*100)+cents;
         //use that to create a dollars variable
         Dollars price(centsTotal);
         //use the sell function of portfollio
         myPortfolio.sell(vol, price);
      }
      else
      {
         cout<<"ERROR";
      }
   }while (decision != "quit");
   
};
      
      
   
/*   Portfolio trader;
   string decision;
   int ammount = 0;
   Dollars cash = 0;
   
   do
   {
      cout << "> ";
      cin >> decision;
      boost::algorithm::to_lower(decision);
      if (decision == "buy")
      {
         cout << ' ';
         cin >> ammount;
         cout << ' ';
         cin >> cash;
         trader.buy(ammount, cash);
         cin.ignore();
      }
      else if (decision == "sell")
      {
         cout << ' ';
         cin >> ammount;
         cout << ' ';
         cin >> cash;
         trader.sell(ammount, cash);
      }
      else if (decision == "display")
      {
         trader.display();
      }
      else if (decision == "quit")
      {
         cout << "Exiting program...\n";
         exit(0);
      }
      else
      {
         cout << "volume not recognized, exiting program...\n";
         exit(0);
      }
   }
   while (decision != "quit");
*/ 


