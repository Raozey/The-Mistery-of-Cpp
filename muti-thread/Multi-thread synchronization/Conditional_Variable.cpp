#include <iostream>
#include <mutex>
#include <thread>
#include <future>  
#include<condition_variable>

using namespace std;


mutex mtx;
condition_variable cv;
bool hello_done=false;
void Hello(int n) {
    for (int i = 0; i < n; i++){
        unique_lock<std::mutex> lock(mtx);
        // using while to let thread wait
        // while (hello_done) {
        //     cv.wait(lock);
        // }
        // using lambada function,, thread will blocked until return ture
        cv.wait(lock,[&](){return !hello_done;});
        cout<<"Hello"<<endl;
        hello_done = true;
        cv.notify_all();
    }
}
void World(int n) {
    for (int i = 0; i < n; i++){
        unique_lock<std::mutex> lock(mtx);
        // while (!hello_done) {
        //     cv.wait(lock);
        // }
        // using lambada function, thread will blocked until return ture
        cv.wait(lock,[&](){return hello_done;});
        cout<<"World"<<endl;
        hello_done = false;
        cv.notify_all();
    }
}
int main(){
    thread hello(Hello,3);
    thread world(World,3);
    hello.join();
    world.join();
    cout << endl << "Finish and Exit!" << endl;
    return 0;
}
