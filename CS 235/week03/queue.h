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
    }

    // copy constructor : copy it
    Queue(const Queue & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Queue(int myCapacity) throw (const char *);
    
    // destructor : free everything
    ~Queue()        { if (myCapacity) delete [] myArray; }
    // is the Queue currently empty
    bool empty() const  { return (mySize == 0);}

    // remove all the items from the Queue
    void clear()        { while(!empty()) {pop();}                }

    // how many items are currently in the Queue?
    int size() const    { return mySize;              }

    // Return the number of elements that can be held in the currently allocated storage
    int capacity()      { return myCapacity;                   }

    //Assignment Operator returns reference to a Queue
    Queue<T> & operator=(const Queue<T> & rhs)
    {
        //cerr << "entered operator=\n";
        //clear();
        if (myCapacity != rhs.myCapacity)
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
    ////cerr << "Using default copy constructor\n";

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
    this->mySize = rhs.mySize;
    this->myFront = rhs.myFront;
    this->myBack = rhs.myBack;

    ////cerr << "myCapacity vs rhs.myCapacity and mySize and myFront " << myCapacity << " : " << rhs.myCapacity << " : " << mySize << " : " << myFront << endl;
    int queueIndex = myFront;
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < mySize; i++)
    {
        ////cerr << "i: " << i << endl;
        myArray[queueIndex] = rhs.myArray[queueIndex];
        queueIndex = (queueIndex + 1) % myCapacity;
    }

/*
    if (mySize < myCapacity)
    {
        //cerr << "filling in empty spaces in the queue\n";
        // the rest needs to be filled with the default value for T
        for (int i = mySize; i < myCapacity; i++)
            myArray[i] = T();
    }
*/
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
        myCapacity = 2;
        allocate(myCapacity);
        newBack = (myBack + 1) % myCapacity;
    }
    else if (mySize >= myCapacity)
    {
        //cerr << "We need to double our queue size\n";
        int oldCapacity = myCapacity;
        myCapacity *= 2;
         //allocate double the memory below
        T * temp;

        // try and catch to check for push error
        try
        {
            //cerr << "push...new temp array\n";
            temp = new T [myCapacity];
        }
        catch(std::bad_alloc)
        {
            throw "ERROR: Unable to allocate a new buffer for queue";
        }

        int queueIndex = myFront;
        // copy the items over one at a time using the assignment operator
        for (int i = 0; i < mySize; i++)
        {
            //cerr << "copying array items " << i << " queueIndex: " << queueIndex << " myCapacity " << myCapacity << endl;
            temp[i] = myArray[queueIndex];
            queueIndex = (queueIndex + 1) % oldCapacity;
            //cerr << "queueIndex: " << queueIndex << endl;
        }

        /*
        for (int i = 0; i < mySize; i++)
        {
            //cerr << "copying array items " << i << " myCapacity " << myCapacity << endl;
            temp[i] = myArray[i];
        }
         */
        //cerr << "**POST initial copy: myFront | myBack | mySize | myCapacity: " << myFront << " | " << myBack
            //<< " | " << mySize << " | " << myCapacity << endl;
        if(mySize < myCapacity)
        {
            //cerr << "mySize is smaller than myCapacity, so we're filling the rest of the queue with null\n";
            // the rest needs to be filled with the default value for T
            for (int i = mySize; i < myCapacity; i++)
            {
                //cerr << "copying nulls into extra capacity " << i << endl;
                //myArray[i] = T();
            }

        }

        //cerr << "ready to delete array\n";
        delete [] myArray;
        //cerr << "about to invoke operator=\n";
        myArray = temp;
        // reset myBack to correct place in the queue
        myFront = 0;
        myBack = mySize; // using  mySize since we know this place in the queue
        //cerr << "new myBack size is: " << myBack << endl;
     }

    //cerr << "myFront | myBack | mySize | myCapacity: " << myFront << " | " << myBack
        //<< " | " << mySize << " | " << myCapacity << endl;
    myArray[myBack] = value;
	 myBack = (myBack + 1) % myCapacity;
    mySize++;

    //cerr << "myFront | myBack | mySize | myCapacity: " << myFront << " | " << myBack
    //<< " | " << mySize << " | " << myCapacity << endl;

}

template <class T>
void Queue <T> :: allocate(int space) throw (const char *)
{
    // attempt to allocate
    try
    {
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
    //cerr << "mySize vs rhs.mySize: " << mySize << " : " << rhs.mySize << endl;
    mySize = rhs.mySize;

    //cerr << "myCapacity vs rhs.myCapacity: " << myCapacity << " : " << rhs.myCapacity << endl;
    // set myCapacity to passed in rhs capacity value
    myCapacity = rhs.myCapacity;

    // set front and back of queue to equal the original
    myFront = rhs.myFront;
    myBack = rhs.myBack;

    //cerr << "copy() method...about to copy the array\n";
    // copy the items over one at a time using the assignment operator
    //for (int i = 0; i < mySize; i++)
     //   myArray[i] = rhs.myArray[i];

    int queueIndex = myFront;
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < mySize; i++)
    {
        ////cerr << "i: " << i << endl;
        myArray[queueIndex] = rhs.myArray[queueIndex];
        queueIndex = (queueIndex + 1) % myCapacity;
    }
        
    // the rest needs to be filled with the default value for T
    //for (int i = mySize; i < myCapacity; i++)
     //  myArray[i] = T();

    //cerr << "Leaving copy() method\n";
}

#endif // QUEUE_H
