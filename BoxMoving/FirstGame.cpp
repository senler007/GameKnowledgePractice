#include<iostream>

using namespace std;

const char gStageData[] = "\
########\n\
# .. p #\n\
# oo   #\n\
#      #\n\
########";

const int gStageWidth = 8;
const int gStageHeight = 5;

enum Object {
    OBJ_SPACE,
    OBJ_WALL,
    OBJ_GOAL,
    OBJ_BOX,
    OBJ_BOX_ON_GOAL,
    OBJ_MAN,
    OBJ_MAN_ON_GOAL,

    OBJ_UNKNOWN,
};

void initialize(Object* state, int w, int h, const char* stageData);
void draw(const Object* state, int w, int h);
void update(Object* state, char input, int w, int h);
bool checkClear(const Object* state, int w, int h);

int main() {

    Object* state = new Object[gStageWidth * gStageHeight];

    initialize(state, gStageWidth, gStageHeight, gStageData);

    //MainLoop
    while (true) {
        draw(state, gStageWidth, gStageHeight);

        if (checkClear(state, gStageWidth, gStageHeight)) {
            break;
        }

        cout << "wasd上下左右,推箱子游戏" << endl;
        char input;
        cin >> input;

        update(state, input, gStageWidth, gStageHeight);

    }

    cout << "通关！";

    //析构
    delete[] state;//-------------P1
    state = 0;

    //为了避免运行完一闪而过，添加无限循环。命令行中按下Ctrl C即可终止
    while (true) {
        ;
    }
    return 0;
}

//----------------函数定义----------------

//////////以后可能会需要传入高度值，但是目前没用到，所以把参数变量名height先注释掉
void initialize(Object* state, int width, int /*height*/, const char* stageData) {//------------P2
    const char* d = stageData;
    int x = 0, y = 0;
    while (*d != '\0') {
        Object t;
        switch (*d) {
        case '#': t = OBJ_WALL; break;
        case ' ': t = OBJ_SPACE; break;
        case 'o': t = OBJ_BOX; break;
        case 'O': t = OBJ_BOX_ON_GOAL; break;
        case '.': t = OBJ_GOAL; break;
        case 'p': t = OBJ_MAN; break;
        case 'P': t = OBJ_MAN_ON_GOAL; break;
        case '\n': x = 0; ++y; t = OBJ_UNKNOWN; break; //换行处理
        default: t = OBJ_UNKNOWN; break;
        }
        ++d;
        if (t != OBJ_UNKNOWN) { //这个if处理的意义在如果遇到未定义的元素值就跳过它
            state[y * width + x] = t; //写入
            ++x;
        }
    }
}

void draw(const Object* state, int width, int height) {
    const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' }; //Object的可能值
    for (int y = 0;y < height;y++) {
        for (int x = 0;x < width;x++) {
            Object o = state[y * width + x];
            cout << font[o];
        }
        cout << endl;
    }
}

//第一个参数就是其他函数中的state，不过这里因为会频繁使用，就缩写为s。另外两个参数w，h分别表示width,height
void update(Object* s, char input, int w, int h) {
    //移动量变换(变量名中的d可以理解为difference或者delta)
    int dx = 0;
    int dy = 0;
    switch (input) {
    case 'a': dx = -1; break; //向左
    case 'd': dx = 1; break; //右
    case 'w': dy = -1; break; //上。Y朝下为正
    case 's': dy = 1; break; //下。
    }
    //查询小人的坐标
    int i = -1;
    for (i = 0; i < w * h; ++i) {
        if (s[i] == OBJ_MAN || s[i] == OBJ_MAN_ON_GOAL) {
            break;
        }
    }
    int x = i % w; //x是对宽度的余数
    int y = i / w; //y是对宽度的商

    //移动
    //移动后的坐标（t并没有特定的代表含义）
    int tx = x + dx;
    int ty = y + dy;
    //判断坐标的极端值。不允许超出合理值范围
    if (tx < 0 || ty < 0 || tx >= w || ty >= h) {
        return;
    }
    //A.该方向上是空白或者终点。小人则移动
    int p = y * w + x; //人员位置
    int tp = ty * w + tx; //目标位置（TargetPosition）
    if (s[tp] == OBJ_SPACE || s[tp] == OBJ_GOAL) {
        s[tp] = (s[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN; //如果该位置是终点，则将该位置值变为“终点上站着人”
        s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE; //如果该位置已经是“终点上站着人”，则变为“终点”
        //B.如果该方向上是箱子。并且该方向的下下个格子是空白或者终点，则允许移动
    } else if (s[tp] == OBJ_BOX || s[tp] == OBJ_BOX_ON_GOAL) {
        //检测同方向上的下下个格子是否位于合理值范围
        int tx2 = tx + dx;
        int ty2 = ty + dy;
        if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h) { //按键无效
            return;
        }

        int tp2 = (ty + dy) * w + (tx + dx); //下下个格子
        if (s[tp2] == OBJ_SPACE || s[tp2] == OBJ_GOAL) {
            //按顺序替换
            s[tp2] = (s[tp2] == OBJ_GOAL) ? OBJ_BOX_ON_GOAL : OBJ_BOX;
            s[tp] = (s[tp] == OBJ_BOX_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
            s[p] = (s[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
        }
    }
}

//如果没有方块了则判定为通关
bool checkClear(const Object* s, int width, int height) {
    for (int i = 0; i < width * height; ++i) {
        if (s[i] == OBJ_BOX) {
            return false;
        }
    }
    return true;
}
