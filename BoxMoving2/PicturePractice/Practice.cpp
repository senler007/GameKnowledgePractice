//读取图片写出
#include <fstream>
#include "GameLib\Framework.h"
using namespace std;

void readFile(char** buffer, int* size, const char* filename);
unsigned getUnsigned(const char* p);

bool gFirst = true;
int gImageWidth = 0;
int gImageHeight = 0;
unsigned* gImageData = 0;

namespace GameLib {
	void Framework::update() {
		char* buffer = 0;
		int size = 0;
		readFile(&buffer, &size, "bar.dds");
		gImageWidth = getUnsigned(&(buffer[12]));
		gImageHeight = getUnsigned(&(buffer[16]));
		gImageData = new unsigned[gImageWidth * gImageHeight];
		for (int i = 0; i < gImageWidth * gImageHeight; i++) {
			gImageData[i] = getUnsigned(&(buffer[128 + i * 4]));
		}

		unsigned* vram = GameLib::Framework::instance().videoMemory();//必须获取Framework的实例才能调用函数
		unsigned windowWidth = GameLib::Framework::instance().width();
		for (int y = 0; y < gImageHeight; y++) {
			for (int x = 0; x < gImageWidth; x++) {
				vram[y * windowWidth + x+100] = gImageData[y * gImageWidth + x];
			}
		}
	}
}

void readFile(char** buffer, int* size, const char* filename) {
	ifstream in(filename, ifstream::binary);
	if (!in) {
		*buffer = 0;
		*size = 0;
		return;
	}
	else {
		in.seekg(0, ifstream::end);
		*size = static_cast<int>(in.tellg());
		in.seekg(0, ifstream::beg);
		*buffer = new char[*size];
		in.read(*buffer, *size);
	}
}

unsigned getUnsigned(const char* p) {
	const unsigned char* a;
	a = reinterpret_cast<const unsigned char*> (p);
	unsigned rep =a[0];
	rep |= a[1] << 8;
	rep |= a[2] << 16;
	rep |= a[3] << 24;
	return rep;
}