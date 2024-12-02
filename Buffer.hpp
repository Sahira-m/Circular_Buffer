#ifndef Buffer_hpp
#define Buffer_hpp
#include <mutex>
#include <condition_variable>
#include <stdio.h>
#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#define WSIZE

class Vehicle
{
public:
    static int id;
    static std::string model, type;
};

class Car : Vehicle
{
public:
    static int numberOfPassengers;
    Car(int val1)
    {
        numberOfPassengers = val1;
    }
};

class Truck : Vehicle
{
public:
    static float maximumLoadWeight;
    Truck(float maximum)
    {
        maximumLoadWeight = maximum;
    }
};

class Buffer
{

    // Buffer fields
public:
    std::string buffer[WSIZE];
    int buffer_size = 0;
    int left = 0;  // index where variables are put inside of buffer (produced)
    int right = 0; // index where variables are removed from buffer (consumed)

    // Fields for concurrency
    std::mutex mtx;
    std::condition_variable not_empty;
    std::condition_variable not_full;
    // UNCOPYABLE CIRCULAR BUFFER
    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

public:
    // Place integer inside of buffer

    void produce(std::string element);

    // Remove integer from buffer
    std::string consume(int consume);
};

#endif