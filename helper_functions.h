#include "person.h"

int getAvailableCashier(int numOfCashiers, Cashier cashierList[]); //Returns the ID of the first available Cashier at any given time.
void setAvailableCashiers(int numOfCashiers, Cashier cashierList[], Customer customer); //Sets which cashiers will be available when a customer arrives at any cashier.
int getAvailableBarista(int numOfBaristas, Barista baristaList[]); //Returns the ID of the first available Barista at any given time.
void setAvailableBaristas(int numOfBaristas, Barista baristaList[], Customer customer); //Sets which baristas will be available when a customer arrives at any barista.
int getFirstAvailableBarista(int numOfBaristas, Barista baristaList[]); //Returns the ID of the barista that will be available first in the future.
int getFirstAvailableCashier(int numOfCashiers, Cashier cashierList[]); //Returns the ID of the cashier that will be available first in the future.
float round(float num); //Rounds any float number to 2 decimal points and returns the result.