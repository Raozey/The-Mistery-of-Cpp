#include <iostream>
#include <thread>
#include<semaphore.h>
using namespace std;


sem_t foo_done, bar_done;

//sem_wait(&semvalue)
// 阻塞的函数，测试所指定信号量的值，它的操作是原子的。
// 若 semvalue > 0，则该信号量值减去 1 并立即返回。
// 若 semvalue = 0，则阻塞直到 sem value > 0，此时立即减去 1，然后返回。
//sem_post(&semvalue)
// 把指定的信号量 semvalue 的值加 1，唤醒正在等待该信号量的任意线程。

void Hello(int n) {
    for (int i = 0; i < n; i++){
        sem_wait(&bar_done);
        cout<<"Hello"<<endl;
        sem_post(&foo_done);
    }
}
void World(int n) {
    for (int i = 0; i < n; i++){
        sem_wait(&foo_done);
        cout<<"World"<<endl;
        sem_post(&bar_done);
    }
}
int main(){
    //第一个参数为要操作的信号量，第二个参数设置为0代表多线程同步（大于0用于进程）
    //第三个参数为初始值value   
    sem_init(&foo_done, 0 , 0);
    sem_init(&bar_done, 0 , 1);
    thread hello(Hello,3);
    thread world(World,3);
    hello.join();
    world.join();
    cout << endl << "Finish and Exit!" << endl;
    return 0;
}
