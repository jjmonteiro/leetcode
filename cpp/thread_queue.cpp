#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>

const int MAX_QUEUE_SIZE = 20;  // Maximum size of the queue
const int ENQUEUE_DELAY = 300;  // Simulate packet creation delay
const int DEQUEUE_DELAY = 100;  // Simulate packet processing delay

bool run = true;

// Shared data structure
std::vector<int> dataQueue;
std::mutex queueMutex;
std::condition_variable dataCond;

void enqueuePackets() {
    while (run) {
        // Simulate packet creation delay
        std::this_thread::sleep_for(std::chrono::milliseconds(ENQUEUE_DELAY));

        // Generate a random number of packets to enqueue
        int numPackets = rand() % (MAX_QUEUE_SIZE / 4) + 1;  // Up to 1/4 of MAX_QUEUE_SIZE

        std::lock_guard<std::mutex> lock(queueMutex);
        system("cls");
        int totalSize = dataQueue.size() + numPackets;

        if (totalSize <= MAX_QUEUE_SIZE) {
            
            // Lambda function to print '#' n times
            auto printHash = [](int n) {
                for (int i = 0; i < n; ++i) {
                    std::cout << '#';
                }
                };

            // Print the hashes using the lambda function
            std::cout << "Queue Buffer: ";
            printHash(totalSize);
            std::cout << "\n" << std::endl;

            for (int i = 0; i < numPackets; ++i) {
                int packet = rand() % 100 + 1;
                dataQueue.push_back(packet);
                std::cout << "Enqueued packet: " << packet << std::endl;
            }
            // Notify the dequeueing thread
            dataCond.notify_one();
        }
        else {
            std::cerr << "Error: Queue is full! Dropping " << numPackets << " packets.\n" << std::endl;
            run = false;
        }
        std::cout << std::endl;
    }
}

void dequeuePackets() {
    while (run) {
        std::unique_lock<std::mutex> lock(queueMutex);

        // Wait for data to be available
        dataCond.wait(lock, [] { return !dataQueue.empty(); });

        // Dequeue a packet
        int packet = dataQueue.front();
        dataQueue.erase(dataQueue.begin());
        std::cout << "Dequeued packet: " << packet << std::endl;

        // Unlock the mutex before processing the packet
        lock.unlock();

        // Simulate packet processing delay
        std::this_thread::sleep_for(std::chrono::milliseconds(DEQUEUE_DELAY));
    }
}

int main() {
    // Create threads for enqueueing and dequeueing
    std::thread producer(enqueuePackets);
    std::thread consumer(dequeuePackets);

    // Join threads (run indefinitely in this example)
    producer.join();
    consumer.join();

    return 0;
}
