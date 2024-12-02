
#include <thread>
#include <iostream>
#include "Buffer.hpp"
#include <stdlib.h>

#define WSIZE 8

using namespace std;

void produceInt(Buffer &buffer)
{
    static int genereateUniqueNumber = 1;
    for (int i = 0; i < 8; i++)
    {

        std::string value;
        if (i % 2 == 0)
        {
            Vehicle::id = 1000 + genereateUniqueNumber;

            Vehicle::model = "V40";
            Vehicle::type = "CAR";

            value = Vehicle::id + "," + Vehicle::model + "," + Vehicle::type + "," + std::to_string(Car::numberOfPassengers);
        }
        else
        {
            Vehicle::id = 1000 + i;

            Vehicle::model = "Volvo40";
            Vehicle::type = "TRUCK";

            value = Vehicle::id + "," + Vehicle::model + "," + Vehicle::type + "," + std::to_string(Truck::maximumLoadWeight);
        }

        cout << "VALUE IS" << value;
        buffer.produce(value);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumeInt(Buffer &buffer, int argc)
{
    for (int i = 0; i < argc; i++)
    {
        buffer.consume(i);
        std::cout << "consumed 2 items";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, const char *argv[])
{

    Car car(5);
    Truck truck(110.6);
    std::cout << "Executing code in main...\n";

    // Initialize random seed
    srand(time(NULL));

    // Create Buffer
    Buffer buffer;
    ;

    // Create a thread to produce
    std::thread produceThread(produceInt, std::ref(buffer));

    std::thread consumeThread(consumeInt, std::ref(buffer), argc);
    produceThread.join();

    consumeThread.join();

    std::cout << "Done!\n";
    return 0;
}
