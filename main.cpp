#include <fstream>
#include "model.h"

int main(int argc, char* argv[])
{
    std::string line;
    std::ifstream inputFile (argv[1]);
    if (inputFile.is_open())
    {    
        int row = 0;
        int numOfCashiers;
        int numOfOrders;
        while (getline(inputFile, line))
        {
            if(row == 0) //First row of the input file equals number of Cashiers.
            {
                numOfCashiers = std::stoi(line);
            }
            if(row == 1) //Second row of the input file equals number of Orders.
            {
                numOfOrders = std::stoi(line);
                break;
            }
            row++;
        }
        
        float orderList[numOfOrders][4]; //2D array that holds the information of the orders(arrival time, order time, brew time, order price).
        std::string line;
        row = 2;
        while(getline(inputFile, line))
        {
            if (row >= 2)
            {
                for (int column = 0; column <= 2; column++)
                {
                    int index = line.find(' ');
                    orderList[row - 2][column] = std::stof(line.substr(0, index));
                    line = line.substr(index + 1, line.length());
                }
                orderList[row - 2][3] = std::stof(line.substr(0, line.length())); //OrderList array is filled with input file rows greater than 2.
            }
            row++;
        }
        inputFile.close();

        
        Cashier cashierList[numOfCashiers]; //Array of Cashiers.
        for (int i = 0; i < numOfCashiers; i++)
        {
            Cashier cashier;
            cashier.id = i;
            cashierList[i] = cashier;
        }

        int numOfBaristas = numOfCashiers/3; //Number of Baristas equals Number of Cashiers divided by 3.
        Barista baristaList[numOfBaristas]; //Array of Baristas.
        for(int i = 0; i < numOfBaristas; i++)
        {
            Barista barista;
            barista.id = i;
            baristaList[i] = barista;
        }

        Customer customerList[numOfOrders]; //Array of Customers.
        for (int i = 0; i < numOfOrders; i++)
        {
            Customer customer;
            
            //Customer informations are filled with their order's informations.
            customer.arrivalTime = orderList[i][0];
            customer.orderTime = orderList[i][1];
            customer.brewTime = orderList[i][2];
            customer.orderPrice = orderList[i][3];
            
            customer.id = i;
            customerList[i] = customer;
        }  
         
        //Cashier Array, Customer Array and Barista Arrays are duplicated for model2. i.e cashierList is used in model1 and cashierList2 is used in model2.
        Cashier cashierList2[numOfCashiers];
        Customer customerList2[numOfOrders];
        Barista baristaList2[numOfBaristas];
        for(int i = 0; i < numOfCashiers; i++)
        {
            cashierList2[i] = cashierList[i];
        }
        for(int i = 0; i < numOfOrders; i++)
        {
            customerList2[i] = customerList[i];
        }
        for(int i = 0; i < numOfBaristas; i++)
        {
            baristaList2[i] = baristaList[i];
        }

        std::ofstream outputFile(argv[2]); //Output File is created.
        
        model1(numOfOrders, numOfCashiers, cashierList, customerList, numOfBaristas, baristaList, outputFile); //Model 1 is run.
        model2(numOfOrders, numOfCashiers, cashierList2, customerList2, numOfBaristas, baristaList2, outputFile); //Model 2 is run.
        
        if(outputFile.is_open())
        {
            outputFile.close();
        }
    }
    return 0;
}