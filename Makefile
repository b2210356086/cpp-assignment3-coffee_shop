Assignment3:main
	g++ main.o model.o helper_functions.o queue.o -o Assignment3 -std=c++11
main:model
	g++ -c main.cpp -o main.o -std=c++11
model:queue helper_functions
	g++ -c model.cpp -o model.o -std=c++11
queue:
	g++ -c queue.cpp -o queue.o -std=c++11
helper_functions:
	g++ -c helper_functions.cpp -o helper_functions.o -std=c++11