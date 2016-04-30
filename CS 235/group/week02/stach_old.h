//
// Created by thesh on 4/26/2016.
//

#ifndef WEEK02_STACH_OLD_H
#define WEEK02_STACH_OLD_H

/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of a Stack: a slot to hold
 *    myArray for the user.
 *
 *    This will contain the class definition of:
 *        Stack         : A class that pushes items to top of list
 * Author
 *    Josh Higgins
 ************************************************************************/

#include <cassert>
#include <iostream>

using namespace std;

/************************************************
* Stack
* A class that holds stuff
***********************************************/
template <class T>
class Stack
{
public:
   // default constructor : empty and kinda useless
   Stack() : myTop(0), myCapacity(0)
   {
      allocate(myCapacity);
   }

   // copy constructor : copy it
   Stack(const Stack & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Stack(int myCapacity) throw (const char *);

   // destructor : free everything
   ~Stack()        { if (myCapacity) delete [] myArray; }
   // is the Stack currently empty
   bool empty() const  { return myTop == 0;         }

   // remove all the items from the Stack
   void clear()        { myTop = 0;                 }

   // how many items are currently in the Stack?
   int size() const    { return myTop;              }

   // Return the number of elements that can be held in the currently allocated storage
   int capacity()      { return myCapacity;                   }

   //Assignment Operator returns reference to a Stack
   Stack<T> & operator=(const Stack<T> & rhs)
   {
      clear();
      if (myCapacity < rhs.myCapacity)
      {
         allocate(rhs.myCapacity);
      }
      copy(rhs);
      return *this;
   }

   //push
   void push(const T & value) throw (const char *)
   {

      cerr << "starting stack push\n";
      if(myCapacity == 0)
      {
         cerr << "capacity is equal to 0\n";
         myCapacity = 5;

         cerr << "capacity = " << myCapacity << endl;

         cerr << "value = " << value << endl;
         this->myArray[myTop] = value;

         cerr << "array contents = " << this->myArray[myTop] << endl;
         myTop++;
         cerr << "myTop = " << myTop << endl;
      }
      else if (myTop == myCapacity)
      {
         cerr << "myTop = capacity\n";
         myCapacity *= 2;
         //myTop++;

         cerr << "capacity = " << myCapacity << endl;
         T * temp = new T [myCapacity];
         for (int i = 0; i < myTop - 1; i++)
         {
            cerr << "copy to new array\n";
            temp[i] = this->myArray[i];
         }
         delete [] myArray;
         myArray = temp;

         this->myArray[myTop] = value;
         myTop++;
         cerr << "myTop = " << myTop << endl;
      }
      else if (myTop < myCapacity)
      {
         cerr << "myTop is less than capacity\n";
         cerr << "capacity = " << myCapacity << endl;
         this->myArray[myTop] = value;
         myTop++;
         cerr << "myTop = " << myTop << endl;
      }
      else
      {
         throw "ERROR: Unable to allocate a new buffer for Stack";
      }
   }

   //pop
   void pop() throw (const char *)
   {
      if (!empty())
      {
         myTop--;
      }
      else
      {
         throw "ERROR: Unable to pop from an empty Stack";
      }
   }

private:
   T * myArray;              // dynamically allocated array of T
   int myTop;                // top of the stack
   int myCapacity;           // capacity of stack

   void allocate(int Space) throw (const char *)
   {
      // attempt to allocate
      try
      {
         myArray = new T[Space];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Stack";
      }
   }

   void copy(const Stack<T> & rhs)
   {
      // copy over the myCapacity and size
      assert(rhs.myTop >= 0 && rhs.myTop <= rhs.myCapacity);
      myTop = rhs.myTop;
      // set myCapacityacity to passed in myCapacityacity
      myCapacity = rhs.myCapacity;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < myTop; i++)
         myArray[i] = rhs.myArray[i];

      // the rest needs to be filled with the default value for T
      for (int i = myTop; i < myCapacity; i++)
         myArray[i] = T();
   }
};

/*******************************************
 * Stack :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
{
   assert(rhs.myCapacity >= 0);

   // do nothing if there is nothing to do
   if (rhs.myCapacity == 0)
   {
      myCapacity = myTop = 0;
      myArray = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      myArray = new T[rhs.myCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }

   // copy over the myCapacity and size
   assert(rhs.myTop >= 0 && rhs.myTop <= rhs.myCapacity);
   this->myCapacity = rhs.myCapacity;
   myTop = rhs.myTop;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < myTop; i++)
      myArray[i] = rhs.myArray[i];

   // the rest needs to be filled with the default value for T
   for (int i = myTop; i < myCapacity; i++)
      myArray[i] = T();
}

/**********************************************
 * Stack : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Stack to "myCapacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int myCapacity) throw (const char *)
{
   assert(myCapacity >= 0);

   // do nothing if there is nothing to do
   if (myCapacity == 0)
   {
      this->myCapacity = this->myTop = 0;
      this->myArray = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      myArray = new T[myCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Stack";
   }


   // copy over the stuff
   this->myCapacity = myCapacity;
   this->myTop = 0;

   // initialize the Stack by calling the default constructor
   for (int i = 0; i < myCapacity; i++)
      myArray[i] = T();
}

#endif //WEEK02_STACH_OLD_H
