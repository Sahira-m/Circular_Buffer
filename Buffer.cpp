#include <iostream>
#include "Buffer.hpp"
#include <bits/stdc++.h>
using namespace std;
// #define WSIZE

void Buffer::produce(std::string num)
{
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);

    while (num.good())
    {
        string substr;
        getline(num, substr, ',');
        v.push_back(substr);
    }

    std::cout << " ID: " << v[0] << "\n"
              << " MODEL: " << v[1] << "\n"
              << " TYPE: " << v[2] << "\n"
              << " PASSENGERS OR lOADWIEGHT " << v[3] << "\n";

    // Wait if the buffer is full
    not_full.wait(unique_lock, [this]()
                  { return buffer_size != WSIZE; });

    // Add input to buffer
    buffer[right] = num;

    // Update appropriate fields
    right = (right + 1) % WSIZE;
    buffer_size++;

    // Unlock unique lock
    unique_lock.unlock();

    // Notify a single thread that buffer isn't empty
    not_empty.notify_one();
}

std::string Buffer::consume(int consume)
{
    // Acquire a unique lock on the mutex
    std::unique_lock<std::mutex> unique_lock(mtx);

    // Wait if buffer is empty
    not_empty.wait(unique_lock, [this]()
                   { return buffer_size != 0; });

    // Getvalue from position to remove in buffer
    std::string result = buffer[left];
    /// NEW CODE TO GET CHARACTER
    vector<std::string> v;

    stringstream ss(result);
    // std::cout << "thread " << consume << "\n";

    // Update appropriate fields
    left = (left + 1) % WSIZE;
    buffer_size--;

    // Unlock unique lock
    unique_lock.unlock();

    // Notify a single thread that the buffer isn't full
    not_full.notify_one();

    // Return result
    return result;
}
