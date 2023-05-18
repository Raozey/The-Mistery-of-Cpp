#include <memory>
#include <iostream>

class B;

class A {
public:
    std::shared_ptr<B> pb;
    ~A() { std::cout << "A destroyed" << std::endl; }
};

class B {
public:
    std::shared_ptr<A> pa;
    ~B() { std::cout << "B destroyed" << std::endl; }
};

// class B {
// public:
//     std::weak_ptr<A> pa;
//     ~B() { std::cout << "B destroyed" << std::endl; }
// };

int main() {
    // 创建两个对象
    std::shared_ptr<A> pa(new A());
    std::shared_ptr<B> pb(new B());
    // 互相引用对方对象
    pa->pb = pb;
    pb->pa = pa;
    // 离开作用域时，两个对象都不会被销毁，导致内存泄漏
    return 0;
}



