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

#ifndef STACK_H
#define STACK_H

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
        if (myCapacity == 0)
        {
            myCapacity = 1;
            allocate(myCapacity);
        }
        else if (myTop == myCapacity)
        {
            myCapacity *= 2;
            // allocate double the memory below
            T * temp;

            // try and catch to check for push error
            try
            {
                temp = new T [myCapacity];
            }
            catch(std::bad_alloc)
            {
                throw "ERROR: Unable to properly push the stack!";
            }

            for (int i = 0; i < myTop; i++)
            {
                temp[i] = myArray[i];
            }
            delete [] myArray;
            myArray = temp;
        }
        myArray[myTop] = value;
        myTop++;
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

    //top
    T & top() throw (const char *)
    {
        if (!empty())
        {
            return myArray[myTop-1];
        }
        else
        {
            throw "ERROR: Unable to reference the element from an empty Stack";
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

#endif // Stack_H
