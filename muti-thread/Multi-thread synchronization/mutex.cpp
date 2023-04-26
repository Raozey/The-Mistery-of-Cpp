#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
using namespace std;


// 多线程实现同步
// 两个线程交替执行，生产者-消费者模型
// 初始化锁住mtx2，world线程无法获取锁阻塞
// hello线程获取到mtx1打印完成后解锁mtx2，然后阻塞
// World线程获取到mtx2打印完成后解锁mtx1，然后阻塞
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
    //交替打印n次Hello World
    thread hello(Hello,3);
    thread world(World,3);
    hello.join();
    world.join();
    cout << endl << "Finish and Exit!" << endl;
    return 0;
}
