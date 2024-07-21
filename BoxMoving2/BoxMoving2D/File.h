#pragma once

class File {
public:
	File(const char* filename);
	~File();

	int size() const;
	const char* data() const; //��һ��const����char,��ָ���޷��޸�char����,�ڶ�������ú���ֻ��,�����޸������κγ�Ա����
	unsigned getUnsigned(int position) const;

private:
	int mSize;
	char* mData;
};