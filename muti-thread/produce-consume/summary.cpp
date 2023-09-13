#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <atomic>
using namespace std;

template<typename T>
class Queue{
public:
    Queue(int maxn = 50) : maxnsize(maxn) {}
    bool Push(const T& elm){
        unique_lock<mutex> lock(_mtx);
        _full.wait(lock, [&](){
            cout<<"push wait"<<endl;
            return _queue.size() < maxnsize;
        });
        _queue.push(elm);
        _empty.notify_one();
        return true;
    }
    T Pop(){
        unique_lock<mutex> lock(_mtx);
        _empty.wait(lock, [&](){
            cout<<"pop wait"<<endl;
            return _queue.size() > 0;
        });
        T elm = _queue.front();
        _queue.pop();
        _full.notify_one();
        return elm;
    }
private:
    queue<T> _queue;
    mutex _mtx;
    condition_variable _full;
    condition_variable _empty;
    int maxnsize;
};


template<typename T>
class ringBuff {
public:
    ringBuff(int size) : max_size(size), pos_write(0), pos_read(0), _data(size) {}
    inline bool isFull() {
        return pos_read == (pos_write + 1) % max_size;
    }
    inline bool isEmpty() {
        return pos_read == pos_write;
    }
    bool push(const T& value){
        if(isFull()) return false;
        _data[pos_write] = value;
        pos_write = (pos_write + 1) % max_size;
        return true;
    }
    bool pop(T& value){
        if(isEmpty()) return false;
        value = _data[pos_read];
        pos_read = (pos_read + 1) % max_size;
        return true;
    }
private:
    int max_size;
    atomic<int> pos_write;
    atomic<int> pos_read;
    vector<T> _data;
};


template<typename T>
class ringBuffCount {
public:
    ringBuffCount(int size) : max_size(size), pos_write(0), pos_read(0), count(0), _data(size){}
    inline bool isFull() {
        return count == max_size;
    }
    inline bool isEmpty() {
        return count == 0;
    }
    bool push(const T& value){
        if(isFull()) return false;
        _data[pos_write] = value;
        pos_write = (pos_write + 1) % max_size;
        count++;
        return true;
    }
    bool pop(T& value){
        if(isEmpty()) return false;
        value = _data[pos_read];
        pos_read = (pos_read + 1) % max_size;
        count--;
        return true;
    }
private:
    int max_size;
    atomic<int> pos_write;
    atomic<int> pos_read;
    atomic<int> count;
    vector<T> _data;
};

void producer(Queue<int> *q)
{
    for(int i = 0; i < 100; i++)
    {
        q->Push(i);
        cout<<"push:"<<i<<endl;
    }
}

void comsumer(Queue<int> *q)
{
    for(int i = 0;i < 100; i ++)
    {
        int ilem = q->Pop();
        cout<<"Pop:"<<ilem<<endl;
    }
}

void producer(int n, ringBuff<int>* buf){
    for(int i = 0; i < n; i++){
        bool flag = buf->push(i);
        while(!flag){
            cout<<"fail push:"<<i<<endl;
            flag = buf->push(i);
        }
        cout<<"success push:"<<i<<endl;
    }
}
void consumer(int n, ringBuff<int>* buf){
    for(int i = 0; i < n; i++){
        int result = 0;
        bool flag = buf->pop(result);
        while(!flag){
            cout<<"fail pop:"<<endl;
            flag = buf->pop(result);
        }
        cout<<"success pop:"<<result<<endl;
    }
}

void producer1(int n, ringBuffCount<int>* buf){
    for(int i = 0; i < n; i++){
        bool flag = buf->push(i);
        while(!flag){
            cout<<"fail push:"<<i<<endl;
            flag = buf->push(i);
        }
        cout<<"success push:"<<i<<endl;
    }
}
void consumer1(int n, ringBuffCount<int>* buf){
    for(int i = 0; i < n; i++){
        int result = 0;
        bool flag = buf->pop(result);
        while(!flag){
            cout<<"fail pop:"<<endl;
            flag = buf->pop(result);
        }
        cout<<"success pop:"<<result<<endl;
    }
}

int main(){
    ringBuffCount<int>* buf = new ringBuffCount<int>(10);
    ringBuff<int>* buf2 = new ringBuff<int>(10);
    Queue<int> q(100);

    thread t1(producer1, 10, buf);
    thread t2(consumer1, 10, buf);
    t1.join();
    t2.join();
    return 0;
}

