#include <iostream>
#include <thread>
#include <future>  
using namespace std;


int long_running_task(int x) {
    // 模拟耗时任务
    x = x + 1;
    this_thread::sleep_for(chrono::milliseconds(500));
    return x;
}
int main() {

    future<int> fut = async(launch::async, long_running_task, 42);
    // 在主线程中执行其他操作，不需要等待线程完成
    for (int i = 0; i < 4; i++) {
        cout << "doing something else..." << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
  
    // 等待线程执行完毕，并读取 Promise 中的值
    int result = fut.get();
    // 输出计算结果
    cout << "long_running_task = " << result << endl;
    return 0;
}
