#include "queue.h"

Queue::Queue()
{
    this -> pFrontCustomer = nullptr;
    this -> pRearCustomer = nullptr;
    this -> maxLength = 0;
    this -> length = 0;
}

Queue::~Queue(){};

void Queue::enqueueCashier(Customer &newCustomer)
{
    this -> length++;
    if(this -> length > this -> maxLength)
    {
        this -> maxLength = this -> length;
    }

    if(this -> length == 1)
    {
        this -> pFrontCustomer = &newCustomer;
        this -> pRearCustomer = &newCustomer;
        return;
    }
            
    this -> pRearCustomer -> pNextCustomer = &newCustomer;
    this -> pRearCustomer = &newCustomer;
}    

void Queue::enqueueBarista(Customer &newCustomer)
{
    this -> length++;
    if(this -> length > this -> maxLength)
    {
        this -> maxLength = this -> length;
    }

    if(this -> length == 1)
    {
        this -> pFrontCustomer = &newCustomer;
        return;
    }
            
    if(newCustomer.orderPrice > this -> pFrontCustomer -> orderPrice)
    {
        newCustomer.pNextCustomer = this -> pFrontCustomer;
        this -> pFrontCustomer = &newCustomer;
        return;
    }
    
    Customer *pTempCustomer = this -> pFrontCustomer;
    while(pTempCustomer -> pNextCustomer != nullptr && newCustomer.orderPrice < pTempCustomer -> pNextCustomer -> orderPrice) //Add new customer to the BaristaQueue according to her order price.
    {
        pTempCustomer = pTempCustomer -> pNextCustomer;
    }
    newCustomer.pNextCustomer = pTempCustomer -> pNextCustomer;
    pTempCustomer -> pNextCustomer = &newCustomer;
}

Customer* Queue::dequeue()
{
    this -> length--;

    if(this -> length == -1)
    {
        return nullptr;
    }

    Customer *pCustomerToDequeue = this -> pFrontCustomer;
    if(this -> length == 0)
    {
        this -> pFrontCustomer = nullptr;
        this -> pRearCustomer = nullptr;
        return pCustomerToDequeue;
    }
            
    this -> pFrontCustomer = this -> pFrontCustomer -> pNextCustomer;
    return pCustomerToDequeue;
}

int Queue::getMaxLength()
{
    return this -> maxLength;
}

int Queue::getLength()
{
    return this -> length;
}