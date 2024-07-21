#pragma once

class File {
public:
	File(const char* filename);
	~File();

	int size() const;
	const char* data() const; //第一个const修饰char,用指针无法修改char数据,第二个代表该函数只读,不会修改类中任何成员变量
	unsigned getUnsigned(int position) const;

private:
	int mSize;
	char* mData;
};