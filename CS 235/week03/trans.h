/*********************************************************
 * Transaction structure includes:
 *      number of stocks
 *      price per stock
 *      profit made (if a sell)
 *********************************************************/
#ifndef TRANS_H
#define TRANS_H

#include "dollars.h"
struct Trans
{
   Dollars price;
   int     volume;
   Dollars profit;
};

#endif
