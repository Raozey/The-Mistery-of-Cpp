#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

// 设定要循环的次数n
int n = 10;

// 定义全局原子变量count
atomic<int> count(0);

// 定义一个用于同步的布尔型原子变量
atomic<bool> start(false);

// 定义一个线程函数，参数为要输出的字符串以及该线程的编号
void print_string(const string& str, int thread_num) {
    // 等待start变量被设置为true
    while (!start);

    // 循环n次，每次输出一个字符串
    while (count < n) {
        // 使用compare_exchange_strong方法来保证原子性
        // 如果count等于thread_num，则将count加1并输出字符串，否则不做任何操作
        if (count % 2 == thread_num) {
            cout << str << endl;
            count++;
        }
    }
}

int main() {
    // 创建两个线程分别输出hello和world
    thread t1(print_string, "hello", 0);
    thread t2(print_string, "world", 1);
    // 设置start变量为true，让两个线程开始执行循环
    start = true;
    // 等待两个线程执行完毕
    t1.join();
    t2.join();
    return 0;
}
