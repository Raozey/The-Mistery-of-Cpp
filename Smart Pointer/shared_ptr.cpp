#include <iostream>
#include <memory>

// shared_ptr多个指针指向相同的对象。
// shared_ptr使用引用计数，每一个shared_ptr的拷贝都指向相同的内存。
// 每使用一次，内部的引用计数加1;
// 每析构一次，内部的引用计数减1;
// 减为0时，自动删除所指向的堆内存。
// 离开作用域时也会被销毁

/*
int main() {
    // 创建 shared_ptr 对象并传入一个动态分配的整数对象
    std::shared_ptr<int> ptr1(new int(42));
    // 创建另一个 shared_ptr 对象也指向同样的整数对象
    std::shared_ptr<int> ptr2 = ptr1;
    // 访问对象
    std::cout << *ptr1 << std::endl;  // 输出: 42
    // 修改其中一个指针所指向的值
    *ptr1 = 100;
    // 另外一个指针也会同时更新
    std::cout << *ptr2 << std::endl;  // 输出: 100
    // 离开作用域时两个指针都会被销毁，对象也会被自动释放
    return 0;
}
*/



class MyClass {
public:
    MyClass() { std::cout << "MyClass created" << std::endl; }
    ~MyClass() { std::cout << "MyClass destroyed" << std::endl; }
};

// int main() {
//     // 创建 shared_ptr 对象并传入一个动态分配的 MyClass 对象
//     std::shared_ptr<MyClass> ptr1(new MyClass());
//     {
//         // 在新作用域内创建另一个 shared_ptr 对象也指向同样的 MyClass 对象
//         std::shared_ptr<MyClass> ptr2 = ptr1;
//         // 此时两个 shared_ptr 对象的计数都为 2
//     }
//     // 此时只剩下一个 shared_ptr 对象指向 MyClass 对象，计数为 1
//     std::cout << "Leaving scope" << std::endl;
//     return 0;
// }
// 程序输出：
// MyClass created
// Leaving scope
// MyClass destroyed


int main() {
    std::shared_ptr<MyClass> ptr;
    // 创建动态分配的 MyClass 对象，并将其交给 shared_ptr 对象管理
    ptr.reset(new MyClass());
    // 此时 shared_ptr 对象的引用计数为 1
    {
        // 在新作用域内创建另外一个 shared_ptr 对象指向同样的 MyClass 对象
        std::shared_ptr<MyClass> ptr2 = ptr;
        // 此时 shared_ptr 对象的引用计数变为 2
    }
    // 离开新作用域时，ptr2 对象被销毁，计数器变为 1
    // 手动释放 MyClass 对象，此时计数器变为 0，对象被自动销毁
    ptr.reset();
    return 0;
}
//程序输出：
// MyClass created
// Leaving scope
// MyClass destroyed





