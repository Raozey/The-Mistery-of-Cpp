
#include <iostream>
#include <string>

using namespace std;

//父类
class Base {
public:
    virtual void print() {
        cout << "Base class" << endl;
    }
};

//子类
class Derived : public Base {
public:
    void print() {
        cout << "Derived class" << endl;
    }
};


int main() {

    // 隐式转换：将整数类型赋值给浮点数类型，编译器自动完成类型转换
    int x = 10;
    double y = x;
    cout << "Implicit conversion: " << y << endl;

    // 静态转换：使用static_cast显式转换类型，转换整数类型为浮点数类型
    double a = static_cast<double>(x);
    cout << "Static conversion: " << a << endl;

    // 常量转换：使用const_cast删除const限定符，转换指向常量的指针为指向非常量的指针
    const int b = 20;
    int* ptr1 = const_cast<int*>(&b);
    *ptr1 = 30;
    cout << "Constant conversion: " << *ptr1 << endl;

    // 动态转换：使用dynamic_cast将基类指针或引用转换为派生类指针或引用
    // 会在运行时检查类型转换是否有效,如果无法进行转换，则返回空指针（对于指针）或抛出异常（对于引用）。
    Base* basePtr = new Derived();
    Base* base = new Base();
    Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);
    derivedPtr->print();
   
    //double c = dynamic_cast<double>(x); //报错：dynamic_cast 中的类型必须是指向完整类类型或 void * 的指针或引用


    Derived* derivedPtr2 = dynamic_cast<Derived*>(base);
    if(derivedPtr2 != nullptr) derivedPtr2->print();
    if(derivedPtr2 == nullptr) cout<<"wrong cast"<<endl;
    
    // reinterpret_cast：重新解释一个指针或引用类型的值，不执行任何转换
    // 转换过程中并不进行任何类型检查或者安全性检查
    // 将源类型的对象的底层二进制表示强制转换为目标类型的指针类型所表示的地址，然后返回这个地址对应的指针（或引用）
    int c = 100;
    int* ptr2 = &c;
    cout << "adress of ptr2: " << ptr2 << endl;
    cout << "value of ptr2: " << *ptr2 << endl;
    string* strPtr = reinterpret_cast<string*>(ptr2);
    cout << "adress of strPtr: " << strPtr << endl;
    cout << "value of strPtr: " ;
    // for(char i : *strPtr) cout<< i ; /可以通过编译，但是无法执行

    return 0;
}
