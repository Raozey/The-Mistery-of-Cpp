#include <iostream>
#include <thread>
#include <atomic>
using namespace std;


atomic<bool> hello_done(false);
void Hello(int n) {
    for (int i = 0; i < n; i++){
        while (hello_done) {
           this_thread::yield();
        }
        cout<<"Hello"<<endl;
        hello_done = true;
       
    }
}
void World(int n) {
    for (int i = 0; i < n; i++){
        while (!hello_done) {
           this_thread::yield();
        }
        cout<<"World"<<endl;
        hello_done = false;
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
