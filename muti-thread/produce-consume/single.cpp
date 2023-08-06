#include<iostream>
#include<queue>
#include<thread>
#include<mutex>
#include<semaphore.h>
#include<condition_variable>
using namespace std;


struct dataSet {
	int x;
	int y;
	dataSet(int a, int b) : x(a), y(b){}
};

template<typename T>
class blockQueue {
private:
	queue<T> _q;
	int _maxItem;
	mutex _mtx;
	condition_variable _full;
	condition_variable _empty;
private:
	void lockQueue() { _mtx.lock();}
	void unlockQueue() { _mtx.unlock();}
	bool isEmpty() { return _q.empty();}
	bool isFull() { return _q.size() == _maxItem;}

	void producerWait(unique_lock<mutex> &lock) { _full.wait(lock);}
	void consumerWait(unique_lock<mutex> &lock) { _empty.wait(lock);}

	void notifyProducer() { _full.notify_one();}
	void notifyConsumer() { _empty.notify_one();}
public:
	blockQueue(int x) : _maxItem(x) {}
	~blockQueue() {}
	void pushData(const T& data) {
		unique_lock<mutex> lock(_mtx);
		while(isFull()) {
			producerWait(lock);
		}
		_q.push(data);
		notifyConsumer();
	}
	T popData() {
		unique_lock<mutex> lock(_mtx);
		while(isEmpty()) {
			consumerWait(lock);
		}
		T data = _q.front();
		_q.pop();
		notifyProducer();
		return data;
	}
};

void produce (void * q){
	blockQueue<dataSet> *queue = static_cast<blockQueue<dataSet> *>(q);
	for (int i = 0; i < 10; i++) {
		queue->pushData(dataSet(i,i));
		std::cout << "Produced: " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

void consume (void * q){
	blockQueue<dataSet> *queue = static_cast<blockQueue<dataSet> *>(q);
	for (int i = 0; i < 10; i++) {
		dataSet data = queue->popData();
		std::cout << "Consumed: " << data.x << data.y << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main() {
    blockQueue<dataSet> queue(5);
    std::thread producer(produce, &queue);
    std::thread consumer(consume, &queue);
    producer.join();
    consumer.join();
    return 0;
}


