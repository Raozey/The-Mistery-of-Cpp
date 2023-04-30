
#include <iostream>
#include <vector>
using namespace std;

// 模板函数使用
template<Typename T>
T compareMax(T a, T b){
  return a > b ? a : b;
}

// 模板类使用
template<Typename T>
class Stack
{
public:
  bool empty()  return items_.empty();
  int size() return items_.size();
  T& top() return items_.back();
  void pop() items_.pop_back();
  void push(const T& item) items_.push_back();
private:
   vector<T> items_;
};


int main()
{
    // 模板函数的使用示例
    int a = 3, b = 4;
    cout << "Max of " << a << " and " << b << " is " << Max(a, b) << endl;
    
    double c = 3.14, d = 2.718;
    cout << "Max of " << c << " and " << d << " is " << Max(c, d) << :endl;
    
    // 模板类的使用示例
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);
    cout << "Top of int stack is " << int_stack.top() << endl; //3
    int_stack.pop();
    cout << "Top of int stack is " << int_stack.top() << endl; //2
    
    Stack<string> string_stack;
    string_stack.push("hello");
    string_stack.push("world");
    cout << "Top of string stack is " << string_stack.top() << endl; //world
    string_stack.pop();
    cout << "Top of string stack is " << string_stack.top() << endl; //hello
    
    return 0;
}


