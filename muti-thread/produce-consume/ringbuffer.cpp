#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>

using namespace std;

template<typename T> 
class ringBuffer {
private:
    vector<T> buffer;
    int read_pos;
    int write_pos;
    int count;
    mutex mtx;
    condition_variable not_full;
    condition_variable not_empty;
public:
    ringBuffer(int size) : buffer(size), read_pos(0), write_pos(0), count(0) {}

    // 添加到缓冲区
    void AddToBuffer(T item) {
        unique_lock<mutex> lock(mtx);
        not_full.wait(lock, [this]() { return count < buffer.size(); });
        buffer[write_pos] = item;
        cout << "Produced: " << item << endl;
        write_pos = (write_pos + 1) % buffer.size();
        ++count;
        not_empty.notify_one();
    }

    // 从缓冲区获取
    T GetFromBuffer() {
        unique_lock<mutex> lock(mtx);
        not_empty.wait(lock, [this]() { return count > 0; });
        T item = buffer[read_pos];
        cout << "Consumed: " << item << endl;
        read_pos = (read_pos + 1) % buffer.size();
        --count;
        not_full.notify_one();
        return item;
    }
};

void Producer(ringBuffer<int>* buffer) {
    for (int i = 1; i <= 20; ++i) {
        buffer->AddToBuffer(i);
		this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void Consumer(ringBuffer<int>* buffer) {
    for (int i = 1; i <= 20; ++i) {
        int item = buffer->GetFromBuffer();
		this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    ringBuffer<int> buffer(10);

    thread producerThread(Producer, &buffer);
    thread consumerThread(Consumer, &buffer);

    producerThread.join();
    consumerThread.join();
    return 0;
}

