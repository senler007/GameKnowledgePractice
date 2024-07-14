#include<iostream>


//namespace -------------p3
//三年级二班/一年级二班
class Student;
namespace Grade3 {
    namespace Class2 {
        extern Student Wang;//声明wang在外部文件里
    }
}
namespace Grade1 {
    namespace Class2 {
        extern Student Wang;
    }
}

//Template
template<class SomeClass> class A {
public:
    SomeClass mNumber;
};

/*
int main() {
    A<int> aInt;
    int bInt = 5;
    aInt.mNumber = bInt;

    std::cout << "aInt.mNumber = " << aInt.mNumber << std::endl;

    return 0;
}
*/

//模板类用法（二维数组实现）
template< class T > class Array2D {
public:
    Array2D() : mArray(0) {}
    ~Array2D() {
        delete[] mArray;
        mArray = 0;  //为安全起见，把指针值设为0
    }
    void setSize(int size0, int size1) {
        mSize0 = size0;
        mSize1 = size1;
        mArray = new T[size0 * size1];
    }
    T& operator()(int index0, int index1) {
        return mArray[index1 * mSize0 + index0];
    }
    const T& operator()(int index0, int index1) const {
        return mArray[index1 * mSize0 + index0];
    }
    //第一个const修饰返回的T类型数据，防止如此修改：array(1,3) = 5;
    //第二个const修饰该函数，用该函数无法修改private里的变量
private:
    T* mArray;
    int mSize0;
    int mSize1;
};

// constructor and destructor
//~析构


