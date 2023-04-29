#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main(){
//初始化
/*
    vector<int> vec1; // 创建一个空的 vector
    vector<int> vec2(5);// 创建一个带有指定大小的 vector，初始化为默认值 0
    vector<int> vec3(5, 2); // 创建一个带有指定大小的 vector，初始化为指定值
    vector<int> vec4 = {1, 2, 3}; // 使用列表初始化语法创建 vector
    vector<int> vec5(vec4); // 复制一个已有的 vector
    auto it = find(vec4.begin(), vec4.end(), 2);
    vector<int> vec6(vec4.begin(), vec4.end());  //vec.end()指向的是最后一个元素的下一个
    vector<int> vec7(vec4.begin(), it); //复制[it1,it2)区间内另一个数组的元素到vector中
    vector<vector<int>> v(3, vector<int>(4,1));//二维数组初始化
    int a[15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
    vector<int> vec(a, a + 15); //通过数组a的地址初始化，注意地址是从0到5（左闭右开区间）
    vec.push_back(1);
*/

//插入元素
/*
    vector<int> vec{ 1, 2, 3 };
    vec.push_back(4);  //在末尾插入{1，2，3，4}
    vec.insert(vec.begin() + 1, 5); //在指定位置之前插入5 {1，5, 2，3，4}，并返回表示新插入元素位置的迭代器。
    vec.insert(vec.begin(), 2, 5); //在指定位置之前插入两个5 {5，5，1，5, 2，3，4}，并返回表示第一个新插入元素位置的迭代器。
    vec.insert(vec.end(), {1,2}); //在指定位置之前插入{1,2} {5，5，1，5, 2，3，4, 1, 2}，并返回表示第一个新插入元素位置的迭代器。
    //insert(pos,first,last) 在指定位置之前插入其他容器的 [first,last) 区域的所有元素，，并返回表示第一个新插入元素位置的迭代器。


    // insert先调用构造函数，在调用移动构造函数，emplace直接调用构造函数
    // emplace() 在插入元素时，是在容器的指定位置直接构造元素，效率更高
    // 而不是先单独生成，再将其复制（或移动）到容器中。因此，在实际使用中，推荐大家优先使用 emplace()。
    vec.emplace_back(3);  //在末尾插入3
    vec.emplace(vec.begin() + 1, 5); //在第二个元素之前插入5
*/


//删除元素
/*
    vector<int> vec = {1, 2, 3, 4, 5, 6};
    vec.erase(vec.begin() + 1); // 删除第二个元素,返回一个迭代器，指向被删除元素后的一个元素
    vec.pop_back(); //删除最后一个元素 {1 3 4 5}
    vec.shrink_to_fit(); //Reduce the capacity to that needed for elements
    swap(vec[0], vec[3]); //交换首尾元素{5 3 4 1}
    swap(*vec.begin(), *(vec.end()-1));//交换首尾元素,不能直接交换迭代器{1 3 4 5}
    // vec.clear(); // 清空 vector
*/


//遍历方式
/*
    // //遍历方式1：索引遍历
    // cout << "Elements in vector: ";
    // for (int i = 0; i < vec.size(); i++) {
    //     cout << vec[i] << " ";
    // }
    // cout << endl;

    // //遍历方式2：迭代器遍历 
    // cout << "Elements in vector: ";
    // for (auto it = vec.begin(); it != vec.end(); it++) {
    //     cout << *it << " ";
    // }
    // cout << endl;

    //遍历方式3：范围for
    cout << "Elements in vector: ";
    for (int i : vec) cout << i << " ";
    cout << endl;
*/

//获取大小
/*
    // 获取 vector 的大小
    cout << "Size of vector: " << vec.size() << endl;
    // 获取 vector 的capacity
    cout << "Capacity of vector: " << vec.capacity() << endl;
    // 获取 vector 最多可以存多少个元素， 4611686018427387903
    cout << "Max_size of vector: " << vec.max_size()<< endl;
    // 判断 vector 是否为空
    cout << "empty of vector: " << vec.empty()<< endl;
*/

//其他操作

    vector<int> vec{1, 2, 3, 4, 5, 5};
    cout<<vec.front()<<endl; //得到数组头的引用
    auto it = find(vec.begin(), vec.end(), 4); //得到查找元素的迭代器
    cout<<vec.at(2)<<endl;
    vec.resize(5);  //比当前size小则截断
    vec.resize(6);  //比当前size大则填充默认值

    // To be continued...


    return 0;
}