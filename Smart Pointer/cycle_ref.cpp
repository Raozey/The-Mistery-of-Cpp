#include <memory>
#include <iostream>

class B; // 前置声明
class A {
public:
    shared_ptr<B> ptr;
};

class B {
public:
    shared_ptr<A> ptr;
};


// class A和class B的对象各自被两个智能指针管理，
// 也就是A object和B object引用计数都为2
// 分析class A对象的引用情况，该对象被main函数中的pa和class B对象中的ptr管理，
// 因此A object引用计数是2，B object同理。

// 在这种情况下，在main函数中一个while循环结束的时候，pa和pb的析构函数被调用，
// 但是class A对象和class B对象仍然被一个智能指针管理，
// A object和B object引用计数变成1，于是这两个对象的内存无法被释放，造成内存泄漏

int main()
{
    while(true) {
        shared_ptr<A> pa(new A());
        shared_ptr<B> pb(new B());
        pa -> ptr = pb;
        pb -> ptr = pa;
    }
    return 0;
}

//解决办法：把class A或者class B中的shared_ptr改成weak_ptr即可，
// 由于weak_ptr不会增加shared_ptr的引用计数，
// 所以A object和B object中有一个的引用计数为1，在pa和pb析构时，会正确地释放掉内存


