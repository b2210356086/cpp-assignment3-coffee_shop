#ifndef PERSON_H
#define PERSON_H

struct Cashier
{
    bool isAvailable = true;
    float busyUntil = 0;
    float totalBusyTime = 0;
    int id = 0;
};

struct Barista
{
    bool isAvailable = true;
    float busyUntil = 0;
    float totalBusyTime = 0;
    int id = 0;
};

struct Customer
{
    float arrivalTime = 0;
    float orderTime = 0;
    float brewTime = 0;
    float orderPrice = 0;
    float baristaTime = 0; //Time that the customer is done with the cashier and ready for barista.
    float turnAroundTime = 0;
    int id = 0;
    int correspondingCashierID = 0; //ID of the cashier that took the customer's order.
    Customer *pNextCustomer = nullptr; //Next Customer in Queue.
};

#endif