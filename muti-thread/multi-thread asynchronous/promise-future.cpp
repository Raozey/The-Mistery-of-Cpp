#include <iostream>
#include <thread>
#include <future>  
using namespace std;

void printMessage(const string& message, int delay) {
    // 模拟时间延迟
    this_thread::sleep_for(chrono::milliseconds(delay));
    cout << message << endl;
}

int main() {
    promise<string> promiseObj;// 创建Promise对象
    future<string> futureObj = promiseObj.get_future(); // 获取Future对象并绑定到Promise

    // 异步执行任务
    thread t([&promiseObj]() {
        printMessage("Hello from the worker thread!", 3000);
        promiseObj.set_value("Message from the worker thread");
    });

    // 主线程中执行其他操作
    for(int i =0;i <5;i++){
        cout << "Message from the main thread:" << i<<endl;
        this_thread::sleep_for(chrono::milliseconds(600));
    }

    // 等待Future获取异步任务结果,若未执行完会阻塞
    string result = futureObj.get();
    cout << "Result: " << result << endl;

    // 等待子线程结束
    t.join();

    return 0;
