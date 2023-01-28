#include "model.h"
#include "helper_functions.h"
#include "queue.h"

void model1(int numOfOrders, int numOfCashiers, Cashier cashierList[], Customer customerList[], int numOfBaristas, Barista baristaList[], std::ofstream &outputFile)
{
    float startTime = customerList[0].arrivalTime; //Start time of the coffee shop.
    
    Queue CashierQueue; //Create a Cashier Queue.
    for (int i = 0; i < numOfOrders; i++) //Traverse the customers one by one.
    {
        setAvailableCashiers(numOfCashiers, cashierList, customerList[i]); //Set which cashiers are available at customer i's arrival time.
            
        if(getAvailableCashier(numOfCashiers, cashierList) == -1) //If there are no available cashiers, put customer i to CashierQueue.
        {
            Customer customerToQueue = customerList[i];
            CashierQueue.enqueueCashier(customerToQueue);
        }
        else //If there are available cashiers,
        {   
            while((getAvailableCashier(numOfCashiers, cashierList) != -1) && CashierQueue.getLength() >= 1) //Firstly put customers from CashierQueue to the Available Cashiers.
            {
                Cashier *currentCashier = &(cashierList[getAvailableCashier(numOfCashiers, cashierList)]);
                Customer customerFromQueue = *(CashierQueue.dequeue());
                currentCashier -> isAvailable = false;
                currentCashier -> busyUntil += customerFromQueue.orderTime;
                currentCashier -> totalBusyTime += customerFromQueue.orderTime;
                customerList[customerFromQueue.id].baristaTime = currentCashier -> busyUntil;
            }
            
            if(getAvailableCashier(numOfCashiers, cashierList) != -1) //If the CashierQueue is empty and there are still available cashiers, put customer i to an available cashier.
            {
                Cashier *currentCashier = &(cashierList[getAvailableCashier(numOfCashiers, cashierList)]);
                currentCashier -> isAvailable = false;
                currentCashier -> busyUntil = customerList[i].arrivalTime + customerList[i].orderTime;
                if(currentCashier -> totalBusyTime == 0)
                {
                    currentCashier -> totalBusyTime = customerList[i].orderTime;
                }
                else
                {
                    currentCashier -> totalBusyTime += customerList[i].orderTime;
                }
                customerList[i].baristaTime = currentCashier -> busyUntil;
            }
            else //If the CashierQueue is empty and there are no available cashiers left, put customer i to CashierQueue.
            {
                Customer customerToQueue = customerList[i];
                CashierQueue.enqueueCashier(customerToQueue);
            }
        }
    }

    while(CashierQueue.getLength() > 0) //After all the customers are traversed once, put the customers that are left in the CashierQueue to the Cashiers one by one.
    {
        Cashier *currentCashier = &cashierList[getFirstAvailableCashier(numOfCashiers, cashierList)];
        Customer customerFromQueue = *(CashierQueue.dequeue());
        currentCashier -> isAvailable = false;
        currentCashier -> busyUntil += customerFromQueue.orderTime;
        currentCashier -> totalBusyTime += customerFromQueue.orderTime;
        customerList[customerFromQueue.id].baristaTime = currentCashier -> busyUntil;
    }   
    
    Customer oldCustomerList[numOfOrders]; //Create a duplicate array of oldCustomerList before sorting customerList.
    for (int i = 0; i < numOfOrders; i++)
    {
        oldCustomerList[i] = customerList[i];
    }
        
    //Sort customerList increasingly according to the customers' barista times(The time that they are done with the cashiers).
    for(int i = 0; i < numOfOrders; i++)
    {
        for(int j = 0; j < numOfOrders; j++)
        {
            if(customerList[j].baristaTime > customerList[i].baristaTime)
            {
                Customer tempCustomer = customerList[i];
                customerList[i] = customerList[j];
                customerList[j] = tempCustomer;
            }
        }
    }

    Queue BaristaQueue; //Create a Barista Queue.
    for(int i = 0; i < numOfOrders; i++) //Traverse the sorted customers one by one.
    {
        setAvailableBaristas(numOfBaristas, baristaList, customerList[i]); //Set which baristas are available at customer i's arrival time.
            
        if(getAvailableBarista(numOfBaristas, baristaList) == -1) //If there are no available baristas, put customer i to BaristaQueue.
        {
            Customer &customerToQueue = customerList[i];
            BaristaQueue.enqueueBarista(customerToQueue);
        }
        else //If there are available baristas,
        {   
            while((getAvailableBarista(numOfBaristas, baristaList) != -1) && BaristaQueue.getLength() >= 1) //Firstly put customers from BaristaQueue to the Available Baristas.
            {
                Barista *currentBarista = &(baristaList[getAvailableBarista(numOfBaristas, baristaList)]);
                Customer customerFromQueue = *(BaristaQueue.dequeue());
                currentBarista -> isAvailable = false;
                currentBarista -> busyUntil += customerFromQueue.brewTime;
                currentBarista -> totalBusyTime += customerFromQueue.brewTime;
                oldCustomerList[customerFromQueue.id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerFromQueue.id].arrivalTime;
            }
            
            if(getAvailableBarista(numOfBaristas, baristaList) != -1) //If the BaristaQueue is empty and there are still available baristas, put customer i to an available barista.
            {
                Barista *currentBarista = &(baristaList[getAvailableBarista(numOfBaristas, baristaList)]);
                currentBarista -> isAvailable = false;
                if(currentBarista -> busyUntil != 0)
                {
                    currentBarista -> busyUntil += customerList[i].brewTime;
                }
                else
                {
                    currentBarista -> busyUntil = customerList[i].baristaTime + customerList[i].brewTime;
                }
                    
                if(currentBarista -> totalBusyTime == 0)
                {
                    currentBarista -> totalBusyTime = customerList[i].brewTime;
                }
                else
                {
                    currentBarista -> totalBusyTime += customerList[i].brewTime;
                }
                oldCustomerList[customerList[i].id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerList[i].id].arrivalTime;
            }
            else //If the BaristaQueue is empty and there are no available baristas left, put customer i to BaristaQueue.
            {
                Customer &customerToQueue = customerList[i];
                BaristaQueue.enqueueBarista(customerToQueue);
            }
        }
    }

    while(BaristaQueue.getLength() > 0) //After all the customers are traversed once, put the customers that are left in the BaristaQueue to the Baristas one by one.
    {
        Barista *currentBarista = &baristaList[getFirstAvailableBarista(numOfBaristas, baristaList)];
        Customer customerFromQueue = *(BaristaQueue.dequeue());
        currentBarista -> isAvailable = false;
        currentBarista -> busyUntil += customerFromQueue.brewTime;
        currentBarista -> totalBusyTime += customerFromQueue.brewTime;
        oldCustomerList[customerFromQueue.id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerFromQueue.id].arrivalTime;
    }

    float endTime; //End Time of the coffee shop equals the biggest busyUntil time of a Barista.
    for(int i = 0; i < numOfBaristas; i++)
    {
        if(baristaList[i].busyUntil > endTime)
        {
            endTime = baristaList[i].busyUntil;
        }
    }
    float totalRunningTime = endTime - startTime;
    
    //Write to the outputFile.
    outputFile << round(totalRunningTime) << '\n' << CashierQueue.getMaxLength() << '\n' << BaristaQueue.getMaxLength() << '\n'; 

    for (int i = 0; i < numOfCashiers; i++)
    {
        outputFile << round(cashierList[i].totalBusyTime/totalRunningTime) << '\n';
    }

    for (int i = 0; i < numOfBaristas; i++)
    {
        outputFile << round(baristaList[i].totalBusyTime/totalRunningTime) << '\n';
    }

    for(int i = 0; i < numOfOrders; i++)
    {
        outputFile << round(oldCustomerList[i].turnAroundTime) << '\n';
    }
    outputFile << '\n';
}

void model2(int numOfOrders, int numOfCashiers, Cashier cashierList[], Customer customerList[], int numOfBaristas, Barista baristaList[], std::ofstream &outputFile)
{
    //MODEL 2 IS THE SAME AS MODEL 1 UNTIL BARISTA OPERATIONS.
    
    float startTime = customerList[0].arrivalTime;
    
    Queue CashierQueue;
    for (int i = 0; i < numOfOrders; i++)
    {
        setAvailableCashiers(numOfCashiers, cashierList, customerList[i]);
            
        if(getAvailableCashier(numOfCashiers, cashierList) == -1)
        {
            Customer customerToQueue = customerList[i];
            CashierQueue.enqueueCashier(customerToQueue);
        }
        else
        {   
            while((getAvailableCashier(numOfCashiers, cashierList) != -1) && CashierQueue.getLength() >= 1)
            {
                Cashier *currentCashier = &(cashierList[getAvailableCashier(numOfCashiers, cashierList)]);
                Customer customerFromQueue = *(CashierQueue.dequeue());
                currentCashier -> isAvailable = false;
                currentCashier -> busyUntil += customerFromQueue.orderTime;
                currentCashier -> totalBusyTime += customerFromQueue.orderTime;
                customerList[customerFromQueue.id].baristaTime = currentCashier -> busyUntil;
                customerList[customerFromQueue.id].correspondingCashierID = currentCashier -> id;
            }
            
            if(getAvailableCashier(numOfCashiers, cashierList) != -1)
            {
                Cashier *currentCashier = &(cashierList[getAvailableCashier(numOfCashiers, cashierList)]);
                currentCashier -> isAvailable = false;
                currentCashier -> busyUntil = customerList[i].arrivalTime + customerList[i].orderTime;
                if(currentCashier -> totalBusyTime == 0)
                {
                    currentCashier -> totalBusyTime = customerList[i].orderTime;
                }
                else
                {
                    currentCashier -> totalBusyTime += customerList[i].orderTime;
                }
                customerList[i].baristaTime = currentCashier -> busyUntil;
                customerList[i].correspondingCashierID = currentCashier -> id;
            }
            else
            {
                Customer customerToQueue = customerList[i];
                CashierQueue.enqueueCashier(customerToQueue);
            }
        }
    }  

    while(CashierQueue.getLength() > 0)
    {
        Cashier *currentCashier = &cashierList[getFirstAvailableCashier(numOfCashiers, cashierList)];
        Customer customerFromQueue = *(CashierQueue.dequeue());
        currentCashier -> isAvailable = false;
        currentCashier -> busyUntil += customerFromQueue.orderTime;
        currentCashier -> totalBusyTime += customerFromQueue.orderTime;
        customerList[customerFromQueue.id].baristaTime = currentCashier -> busyUntil;
        customerList[customerFromQueue.id].correspondingCashierID = currentCashier -> id;
    } 
    
    Customer oldCustomerList[numOfOrders];
    for (int i = 0; i < numOfOrders; i++)
    {
        oldCustomerList[i] = customerList[i];
    }
    
    for(int i = 0; i < numOfOrders; i++)
    {
        for(int j = 0; j < numOfOrders; j++)
        {
            if(customerList[j].baristaTime > customerList[i].baristaTime)
            {
                Customer tempCustomer = customerList[i];
                customerList[i] = customerList[j];
                customerList[j] = tempCustomer;
            }
        }
    }

    Queue BaristaQueues[numOfBaristas]; //Array of BaristaQueues because each Barista has it's own BaristaQueue.
    for(int i = 0; i < numOfBaristas; i++)
    {
        Queue BaristaQueue;
        BaristaQueues[i] = BaristaQueue;
    }    
    
    for(int i = 0; i < numOfOrders; i++) //Traverse the sorted customers one by one.
    {
        int correspondingBaristaID = customerList[i].correspondingCashierID / 3; //ID of the barista that will prepare the coffee of the customer.
        Barista correspondingBaristaList[1] = {baristaList[correspondingBaristaID]}; //Corresponding Barista is put into a 1-length Array to be able to use helper functions without changing parameters.

        setAvailableBaristas(1, correspondingBaristaList, customerList[i]); //Sets if the corresponding barista is available or not.
            
        if(getAvailableBarista(1, correspondingBaristaList) == -1) //If the corresponding barista is not available, put the customer to the corresponding barista's queue.
        {
            Customer &customerToQueue = customerList[i];
            BaristaQueues[correspondingBaristaID].enqueueBarista(customerToQueue);
        }
        else //If the corresponding barista is available,
        {   
            if(BaristaQueues[correspondingBaristaID].getLength() >= 1) //If the corresponding barista's queue is not empty, put customer from queue to the barista. Then put customer i to the corresponding barista's queue.
            {
                Barista *currentBarista = &baristaList[correspondingBaristaID];
                Customer customerFromQueue = *(BaristaQueues[correspondingBaristaID].dequeue());
                currentBarista -> isAvailable = false;
                currentBarista -> busyUntil += customerFromQueue.brewTime;
                currentBarista -> totalBusyTime += customerFromQueue.brewTime;
                oldCustomerList[customerFromQueue.id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerFromQueue.id].arrivalTime;
                correspondingBaristaList[0] = baristaList[correspondingBaristaID];
                Customer &customerToQueue = customerList[i];
                BaristaQueues[correspondingBaristaID].enqueueBarista(customerToQueue);
            }      
            else //If the corresponding barista's queue is empty, put customer i to the corresponding barista.
            {
                Barista *currentBarista = &baristaList[correspondingBaristaID];
                currentBarista -> isAvailable = false;
                if(currentBarista -> busyUntil != 0)
                {
                    currentBarista -> busyUntil += customerList[i].brewTime;
                }
                else
                {
                    currentBarista -> busyUntil = customerList[i].baristaTime + customerList[i].brewTime;
                }
                    
                if(currentBarista -> totalBusyTime == 0)
                {
                    currentBarista -> totalBusyTime = customerList[i].brewTime;
                }
                else
                {
                    currentBarista -> totalBusyTime += customerList[i].brewTime;
                }
                oldCustomerList[customerList[i].id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerList[i].id].arrivalTime;
            }
        }
    }

    for(int i = 0; i < numOfBaristas; i++) //After all the customers are traversed once, put the customers that are left in the BaristaQueues to the correspondingBaristas one by one.
    {
        while(BaristaQueues[i].getLength() > 0)
        {
            Barista *currentBarista = &baristaList[i];
            Customer customerFromQueue = *(BaristaQueues[i].dequeue());
            currentBarista -> isAvailable = false;
            currentBarista -> busyUntil += customerFromQueue.brewTime;
            currentBarista -> totalBusyTime += customerFromQueue.brewTime;
            oldCustomerList[customerFromQueue.id].turnAroundTime = currentBarista -> busyUntil - oldCustomerList[customerFromQueue.id].arrivalTime;
        }
    }

    float endTime; //End Time of the coffee shop equals the biggest busyUntil time of a Barista.
    for(int i = 0; i < numOfBaristas; i++)
    {
        if(baristaList[i].busyUntil > endTime)
        {
            endTime = baristaList[i].busyUntil;
        }
    }
    float totalRunningTime = endTime - startTime;
    
    //Write to the outputFile.
    outputFile << round(totalRunningTime) << '\n' << CashierQueue.getMaxLength() << '\n';

    for(int i = 0; i < numOfBaristas; i++)
    {
        outputFile << BaristaQueues[i].getMaxLength() << '\n';
    }

    for (int i = 0; i < numOfCashiers; i++)
    {
        outputFile << round(cashierList[i].totalBusyTime/totalRunningTime) << '\n';
    }

    for (int i = 0; i < numOfBaristas; i++)
    {
        outputFile << round(baristaList[i].totalBusyTime/totalRunningTime) << '\n';
    }

    for(int i = 0; i < numOfOrders; i++)
    {
        outputFile << round(oldCustomerList[i].turnAroundTime) << '\n';
    }
}