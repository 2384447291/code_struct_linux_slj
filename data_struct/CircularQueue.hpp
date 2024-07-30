#ifndef CIRCULARQUEUE_HPP
#define CIRCULARQUEUE_HPP
#include <iostream>
#include <vector>
template <typename T>
class CircularQueue {
private:
    std::vector<T> arr;
    //uin32_t
    size_t front, rear;
    size_t capacity;
    std::string name;

public:
    CircularQueue(size_t cap, std::string _name) : arr(cap), front(0), rear(0), capacity(cap), name(_name) {}

    void enqueue(const T& value) {
        if ((rear + 1) % capacity == front) {
            // Queue is full
            std::cout << name << "Queue is full. Cannot enqueue." << std::endl;
            return;
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;
    }

    void enqueue(const T* _pData, uint32_t _len) {
        for (uint32_t i = 0; i < _len; ++i) {
            enqueue(_pData[i]);  // 调用 enqueue(const T& value) 方法
        }
    }

    void enqueueFront(const T& value) {
        if ((rear + 1) % capacity == front) {
            // Queue is full
            std::cout << "Queue is full. Cannot enqueue front." << std::endl;
            return;
        }
        front = (front == 0) ? capacity - 1 : front - 1;
        arr[front] = value;
    }

    T dequeue() {
        if (front == rear) {
            // Queue is empty
            std::cout << "Queue is empty. Cannot dequeue." << std::endl;
            return T(); // Return default value for type T
        }
        T value = arr[front];
        front = (front + 1) % capacity;
        return value;
    }

    void printcontent() const
    {
        std::cout << "Not define circularQueue printcontent function";
    }

    bool isEmpty() const{
        return front == rear;
    }

    int size() const {
        size_t queueSize = (rear - front + capacity) % capacity;
        // Check if queueSize can fit into an int
        if (queueSize > static_cast<size_t>(std::numeric_limits<int>::max())) {
            std::cerr << "Queue size exceeds maximum int value" << std::endl;
            return -1; // Return an error code or handle appropriately
        }
        return static_cast<int>(queueSize);
    }
};

#endif
