/*******************************************************************
 * Portfolio class includes
 *      A queue of holdings
 *      Proceeds, sum of all profits
 *      A queue of past sells
 *      Sell function that alters the queue and returns a profit
 *      Buy function that alters the transaction queue
 *      Display function
 *******************************************************************/
#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "trans.h"
#include "queue.h"
#include <iostream>

class Portfolio
{
  private:
   Queue<Trans> holdings;
   Dollars proceeds;
   Queue<Trans> history;

  public:
   //default constructor
  Portfolio()
  {
     proceeds=0;
  };

   //destructor
  ~Portfolio(){};

   //purchase a stock, overloaded
   void buy(Trans trans)
   {
      holdings.push(trans);
      return;
   };

   void buy(int vol, Dollars pr)
   {
      Trans newTrans;
      newTrans.volume=vol;
      newTrans.price=pr;
      holdings.push(newTrans);
   };

   //sell a stock
   Dollars sell(int vol, Dollars pr)
   {
      Dollars profit=0;
      if(holdings.front().volume>vol)
      {
         int currVol=holdings.front().volume;
         int newVol=currVol-vol;
         holdings.front().volume=newVol;
         profit=(pr-holdings.front().price)*vol;
         Trans trans;
         trans.volume=vol;
         trans.price=pr;
         trans.profit=(pr-holdings.front().price)*vol;
         history.push(trans);
         return profit;
      }
      else if(holdings.front().volume==vol)
      {
         profit=(pr-holdings.front().price)*vol;
         holdings.pop();
         Trans trans;
         trans.volume=vol;
         trans.price=pr;
         trans.profit=(pr-holdings.front().price)*vol;
         history.push(trans);
         return profit;
      }
      else
      {
         while(vol>0)
         {
            if(holdings.front().volume>vol)
            {
               int currVol=holdings.front().volume;
               int newVol=currVol-vol;
               holdings.front().volume=newVol;
               vol=0;
               Trans trans;
               trans.volume=vol;
               trans.price=pr;
               trans.profit=(pr-holdings.front().price)*vol;
               history.push(trans);
               profit=((pr-holdings.front().price)*currVol)+profit;
            }
            else
            {
               profit=((pr-holdings.front().price)*holdings.front().volume)+profit;
               vol=-holdings.front().volume;
               holdings.pop();
               Trans trans;
               trans.volume=vol;
               trans.price=pr;
               trans.profit=(pr-holdings.front().price)*vol;
               history.push(trans);
            }
         }
      }
      return profit;
   };
               
   //getters
   Queue<Trans> getPortfolio()
   {
      return holdings;
   };
   
   Dollars getProceeds()
   {
      return proceeds;
   };

   Queue<Trans> getHistory()
   {
      return history;
   };

   //display
   void display()
   {
      Queue<Trans> tmpHold=holdings;
      cout<<"Currently held:"<<endl;
      while(!tmpHold.empty())
      {
         cout<<"\tBought "<<tmpHold.front().volume
             <<" shares at "<<tmpHold.front().price<<endl;
         tmpHold.pop();
      }
      Queue<Trans> tmpHist=history;
      cout<<"Sell History:"<<endl;
      while(!tmpHist.empty())
      {
         cout<<"\tSold"<<tmpHist.front().volume
             <<" shares at "<<tmpHist.front().price
             <<" for a profit of "<<tmpHist.front().profit<<endl;
         tmpHist.pop();
      }
      cout<<"Proceeds: "<<proceeds<<endl;
   };
};
   
#endif
