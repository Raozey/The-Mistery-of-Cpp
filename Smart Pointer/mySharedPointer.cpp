#include<bits/stdc++.h>
using namespace std;

template<typename T>
class MysharedPtr{
private:
    T* _ptr;
    int* _count;
public:
    MysharedPtr(T* ptr = nullptr): _ptr(ptr) {
        if(_ptr == nullptr) _count = new int(0);
        else _count = new int(1);
    }
    ~MysharedPtr(){
        if(this->_ptr){
            if(--(*this->_count) == 0){
                delete this->_count;
                delete this->_ptr;
                this->_count = nullptr;
                this->_ptr = nullptr;
            }
        }
    }

    MysharedPtr(const MysharedPtr& shared){
        this->_ptr = shared._ptr;
        this->_count = shared._count;
        (*this->_count)++;
    }

    MysharedPtr& operator=(const MysharedPtr& shared){
        if(this == &shared) return *this;
        if(this->_ptr){
                if(--(*this->_count) == 0){
                delete this->_count;
                delete this->_ptr;
                this->_count = nullptr;
                this->_ptr = nullptr;
            }
        }
        this->_ptr = shared._ptr;
        this->_count = shared._count;
        (*this->_count)++;
        return *this;
    }

    T& operator*() { return *this->_ptr;}
    T* operator->() { return this->_ptr;}
    int getCount() {return *this->_count;}
};




int main() {
    // 创建一个指向整数的智能指针
    MysharedPtr<int> sp1(new int(5));
    
    // 使用解引用运算符获取指针指向的值
    cout << "sp1: " << *sp1 << endl;
    cout << "sp1 count: " << sp1.getCount() << endl;
    
    // 创建另一个指向整数的智能指针，并复制给另一个智能指针
    MysharedPtr<int> sp2 = sp1; 
    // sp2 = sp1;

    // 输出两个智能指针的值
    cout << "sp1: " << *sp1 << endl;
    cout << "sp2: " << *sp2 << endl;
    cout << "sp1 count: " << sp1.getCount() << endl;
    cout << "sp2 count: " << sp2.getCount() << endl;

    // 修改智能指针指向的值
    *sp1 = 10;
    // 输出修改后的值
    cout << "sp1: " << *sp1 << endl;
    cout << "sp2: " << *sp2 << endl;

    // 创建一个空的智能指针
    MysharedPtr<int> sp3;
    // 尝试使用空指针会导致运行时错误
    // cout << "sp3: " << *sp3 << endl;
    return 0;
}
