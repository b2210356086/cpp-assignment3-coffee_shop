#include "helper_functions.h"

int getAvailableCashier(int numOfCashiers, Cashier cashierList[])
{
    for (int i = 0; i < numOfCashiers; i++)
    {
        if(cashierList[i].isAvailable)
        {
            return i;
        }
    }
    return -1;
}

void setAvailableCashiers(int numOfCashiers, Cashier cashierList[], Customer customer)
{
    for (int i = 0; i < numOfCashiers; i++)
    {
        if(customer.arrivalTime > cashierList[i].busyUntil)
        {
            cashierList[i].isAvailable = true;
        }
    }
}

int getAvailableBarista(int numOfBaristas, Barista baristaList[])
{
    for (int i = 0; i < numOfBaristas; i++)
    {
        if(baristaList[i].isAvailable)
        {
            return i;
        }
    }
    return -1;
}

void setAvailableBaristas(int numOfBaristas, Barista baristaList[], Customer customer)
{
    for (int i = 0; i < numOfBaristas; i++)
    {
        if(customer.baristaTime > baristaList[i].busyUntil)
        {
            baristaList[i].isAvailable = true;
        }
    }
}

int getFirstAvailableBarista(int numOfBaristas, Barista baristaList[])
{
    Barista firstAvailableBarista = baristaList[0];
    for(int i = 1; i < numOfBaristas; i++)
    {
        if(baristaList[i].busyUntil < firstAvailableBarista.busyUntil)
        {
            firstAvailableBarista = baristaList[i];
        }
    }
    return firstAvailableBarista.id;
}

int getFirstAvailableCashier(int numOfCashiers, Cashier cashierList[])
{
    Cashier firstAvailableCashier = cashierList[0];
    for(int i = 1; i < numOfCashiers; i++)
    {
        if(cashierList[i].busyUntil < firstAvailableCashier.busyUntil)
        {
            firstAvailableCashier = cashierList[i];
        }
    }
    return firstAvailableCashier.id;
}

float round(float num)
{
    float result = (int)(num*100 + 0.5);
    return (float)result / 100;
}