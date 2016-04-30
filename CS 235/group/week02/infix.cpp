/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
   string postfix;

   /**********************************
   Implement code for infix to postfix
   **********************************/
   char token,
         topToken;
   Stack<char> myStack;
   const string BLANK = " ";
   for (int i = 0; i < infix.length(); i++)
   {
      token = infix[i];
      switch(token)
      {
         case ' ' : break;    //do nothing skip blanks
         case '(' : myStack.push(token);
                    break;
         case ')' : for (;;)
            {
               assert (!myStack.empty());
               topToken = myStack.top();
               myStack.pop();
               if (topToken == '(') break;
               postfix.append(BLANK + topToken);
            }
            break;
         case '+' : case '-' :
         case '^' : case '*' : case '/' : case '%':
                    for (;;)
                    {
                        if (myStack.empty() ||
                           myStack.top() == '(' ||
                           ((token == '^' || token == '*' || token == '/' || token == '%') &&
                           (myStack.top() == '*' || myStack.top() == '+' || myStack.top() == '-')))
                        {
                           myStack.push(token);
                           break;
                        }
                        else
                        {
                           topToken = myStack.top();
                           myStack.pop();
                           postfix.append(BLANK + topToken);
                        }
                    }
                    break;
         default : //operand
                  // postfix.append(BLANK + token);
                  if ( isdigit(infix[i-1]) )
                  {
                     postfix.append(1, token);
                  }
                  else
                  {
                     postfix.append(BLANK + token);
                  }

                  for(;;)
                  {
                     if ( !isalnum(infix[i+1]) ) break; //end of identifier
                     i++;
                     token = infix[i];
                     postfix.append(1, token);
                  }
      }
   }
   // pop remaining operators on the stack
   for (;;)
   {
      if (myStack.empty()) break;
      topToken = myStack.top();
      myStack.pop();
      if (topToken != '(')
      {
         postfix.append(BLANK + topToken);
      }
      else
      {
         std::cout << " *** Error in infix expression ***\n";
         break;
      }
   }

   return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);

      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   string assembly;

   return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";

   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
      
}
