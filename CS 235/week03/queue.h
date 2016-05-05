/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of a Queue: a slot to hold
 *    myArray for the user.
 *
 *    This will contain the class definition of:
 *        Queue         : A class that pushes items to top of list
 * Author
 *    Josh Higgins
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include <iostream>

using namespace std;

 /************************************************
 * Queue
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
    // default constructor : empty and kinda useless
    Queue() : mySize(0), myCapacity(0), myFront(0), myBack(0)
    {
       allocate(myCapacity);
       cerr << "myFront value is: " << myFront << endl;
       cerr << "myBack value is: " << myBack << endl;
       cerr << "mySize value is: " << mySize << endl;
       cerr << "we're empty? " << empty() << endl;
    }

    // copy constructor : copy it
    Queue(const Queue & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Queue(int myCapacity) throw (const char *);
    
    // destructor : free everything
    ~Queue()        { if (myCapacity) delete [] myArray; }
    // is the Queue currently empty
    bool empty() const  { return (myFront == myBack);};

    // remove all the items from the Queue
    void clear()        { mySize = 0;                 }

    // how many items are currently in the Queue?
    int size() const    { return mySize;              }

    // Return the number of elements that can be held in the currently allocated storage
    int capacity()      { return myCapacity;                   }

    //Assignment Operator returns reference to a Queue
    Queue<T> & operator=(const Queue<T> & rhs)
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
    void push(const T & value) throw (const char *);
	
    //pop
    void pop() throw (const char *)
    {
       cerr << "we're in POP\n";
       cerr << "myFront value is: " << myFront << endl;
       cerr << "myBack value is: " << myBack << endl;
       cerr << "mySize value is: " << mySize << endl;
        if (!empty())
        {
            myFront = (myFront + 1) % myCapacity;
			mySize--;
        }
        else
        {
            throw "ERROR: Unable to pop from an empty Queue";
        }
    }

    //top
    T & front() throw (const char *)	{return accessArray(myFront);};
    T & back() throw (const char *)		{return accessArray((myBack - 1) % myCapacity);};
	
private:
    T * myArray;              // dynamically allocated array of T
    int myFront;                // Front of the Queue
	int myBack;					// Back of the Queue
    int myCapacity;           // capacity of Queue
	int mySize;					// Number of Items in queue

    void allocate(int Space) throw (const char *);
    
    void copy(const Queue<T> & rhs);
	
	T & accessArray(int index) throw (const char *);
};

/*******************************************
 * Queue :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
    assert(rhs.myCapacity >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.myCapacity == 0)
    {
        myCapacity = mySize = 0;
        myArray = NULL;
        myFront = myBack = 0;
        return;
    }
    
    // attempt to allocate
    allocate(rhs.myCapacity);
    
    // copy over the myCapacity and size
    assert(rhs.mySize >= 0 && rhs.mySize <= rhs.myCapacity);
    this->myCapacity = rhs.myCapacity;
    mySize = rhs.mySize;
    myFront = rhs.myFront;
    myBack = rhs.myBack;
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < mySize; i++)
        myArray[i] = rhs.myArray[i];
        
    // the rest needs to be filled with the default value for T
    for (int i = mySize; i < myCapacity; i++)
        myArray[i] = T();
    }

/**********************************************
 * Queue : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Queue to "myCapacity"
 **********************************************/
template <class T>
Queue <T> :: Queue(int pCapacity) throw (const char *)
{
    assert(pCapacity >= 0);
    
    // do nothing if there is nothing to do
    if (pCapacity == 0)
    {
        this->myCapacity = this->mySize = 0;
        this->myArray = NULL;
        this->myFront = this->myBack = 0;
        return;
    }
    
    // attempt to allocate
    allocate(pCapacity);
    
    // copy over the stuff
    this->myCapacity = pCapacity;
    this->mySize = 0;

    // set front and back of the queue
    this->myFront = this->myBack = 0;
    
    // initialize the Queue by calling the default constructor
    for (int i = 0; i < pCapacity; i++)
        myArray[i] = T();
}

template <class T>
void Queue <T> :: push(const T & value) throw (const char *)
{
   int newBack;

    if (myCapacity == 0)
    {
        cerr << "Capacity is ZERO\n";
        myCapacity = 2;
        allocate(myCapacity);
        newBack = (myBack + 1) % myCapacity;
    }
    else if (newBack == myFront)
    {
        cerr << "Capacity is greater than ZERO, but queue is FULL\n";
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
            throw "ERROR: Unable to allocate a new buffer for queue";
        }

        for (int i = 0; i < mySize; i++)
        {
            temp[i] = myArray[i];
        }
        delete [] myArray;
        myArray = temp;
    }
   cerr << "**BEFORE** my value is: " << value << endl;
   cerr << "myFront value is: " << myFront << " myBack value is: " << myBack
   << " newBack value is: " << newBack << " mySize value is: " << mySize << endl;
    myArray[myBack] = value;
	 myBack = newBack;
    mySize++;
   cerr << "**AFTER** my value is: " << value << endl;
   cerr << "myFront value is: " << myFront << " myBack value is: " << myBack
   << " newBack value is: " << newBack << " mySize value is: " << mySize << endl;
}

template <class T>
void Queue <T> :: allocate(int space) throw (const char *)
{
    // attempt to allocate
    try
    {
       cerr << "we're in allocate\n";
        myArray = new T[space];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Queue";
    }
}

template <class T>
T & Queue <T> :: accessArray(int index) throw (const char *)
{
    if (!empty())
    {
       cerr << "we're in accessArray and index value is: " << index << endl;
       cerr << "Are we empty now? " << empty() << endl;
       cerr << "myFront value is: " << myFront << " myBack value is: " << myBack
         << " mySize value is: " << mySize << endl;
        return myArray[index];
    }
    else
    {
        throw "ERROR: attempting to access an item in an empty queue";
    }
}

template <class T>
void Queue <T> :: copy(const Queue<T> & rhs)
{
    // copy over the myCapacity and size
    assert(rhs.mySize >= 0 && rhs.mySize <= rhs.myCapacity);
    mySize = rhs.mySize;
	
    // set myCapacity to passed in rhs capacity value
    myCapacity = rhs.myCapacity;
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < mySize; i++)
        myArray[i] = rhs.myArray[(rhs.myFront + i) % rhs.myCapacity];
        
    // the rest needs to be filled with the default value for T
    for (int i = mySize; i < myCapacity; i++)
        myArray[i] = T();
}

#endif // QUEUE_H
