#include "person.h"

class Queue //Queue Class that is used for both Cashier and Barista Queues.
{
    private:
        int maxLength; //Maximum Length of a queue.
        int length; //Length of a queue at any given time.
        Customer *pFrontCustomer; //First Customer in the queue.
        Customer *pRearCustomer; //Last Customer in the queue.
    
    public:
        Queue();
        ~Queue();
        void enqueueCashier(Customer &newCustomer); //This method is called to enqueue a Customer to a Cashier Queue. It is a standard queue, when a new customer arrives she is put to the rear of the cashier queue.
        void enqueueBarista(Customer &newCustomer); //This method is called to enqueue a Customer to a Barista Queue. It is a priority queue, when a new customer arrives she is put to the barista queue according to her order price.
        Customer* dequeue(); //Dequeues the first Customer in the CashierQueue or BaristaQueue. Returns the dequeued Customer.
        int getMaxLength(); //Return Max Length of a queue.
        int getLength(); //Return Length of a queue at any given time.
};