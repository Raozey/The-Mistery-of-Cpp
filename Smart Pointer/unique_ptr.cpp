#include<iostream>
#include <memory>
using namespace std;


// 定义一个结构体
struct MyStruct {
    int data;
};

int main() {
    // 创建 unique_ptr 对象，并传入一个动态分配的 MyStruct 对象的指针
    unique_ptr<MyStruct> ptr(new MyStruct { 42 });
    // 访问结构体成员
    cout << ptr->data << endl;  // 输出: 42
    // 不需要手动释放内存，unique_ptr 在离开作用域时会自动删除对象
 

    // unique_ptr<T> 是 move-only 的
    // unique_ptr<MyStruct> ptr2 = ptr; //报错
    unique_ptr<MyStruct> ptr2 = move(ptr);//正常
    return 0;
}
