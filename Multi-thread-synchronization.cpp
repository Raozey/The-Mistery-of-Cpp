#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <future>  
#include <atomic>
// #include <vector>
// #include <queue>
// #include <chrono>
// #include <iomanip>
#include<condition_variable>
#include<semaphore.h>
using namespace std;


// 多线程实现同步
// 两个线程交替执行，生产者-消费者模型
mutex mtx1;
mutex mtx2;
void Hello(int n) {
    for (int i = 0; i < n; i++){
        mtx1.lock();
        cout<<"Hello"<<endl;
        mtx2.unlock();
    }
}
void World(int n) {
    for (int i = 0; i < n; i++){
        mtx2.lock();
        cout<<"World"<<endl;
        mtx1.unlock();
    }
}
int main(){
    mtx2.lock();
    thread hello(Hello,3);
    thread world(World,3);
    hello.join();
    world.join();
    cout << endl << "Finish and Exit!" << endl;
    return 0;
}

