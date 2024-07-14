template<class T>class Array2D {
private:
    int msize0;
    int msize1;
    T* mArray;

    Array2D() :mArray = 0{};
    ~Array2D() {
        delete[] mArray;
        mArray = 0;
    }

    setSize(int size0, int size1) {
        msize0 = size0;
        msize1 = size1;
        mArray = new T(size0 * size1);
    }

    T& operator()(int index0, int index1) {
        return mArray[index1 * mSize0 + index0];
    }
    const T& operator()(int index0, int index1) const {
        return mArray[index1 * mSize0 + index0];
    }
};