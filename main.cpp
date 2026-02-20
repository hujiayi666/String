#include <iostream>
#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
}SString;

// BF算法（下标从0开始实现）
// 返回值：匹配成功返回从1开始的位置，失败返回0（符合常规算法输出习惯）
int Index(SString S,SString T) {
    int i=0, j=0; // 下标从0开始
    // 循环条件：i不越界（0~S.length-1），j不越界（0~T.length-1）
    while (i < S.length && j < T.length) {
        if (S.ch[i] == T.ch[j]) { // 字符匹配，指针同时后移
            ++i;
            ++j;
        } else { // 字符不匹配，主串指针回退，模式串指针重置
            i = i - j + 1; // 下标0开始的回退公式
            j = 0; // j重置为0（而非1）
        }
    }
    // 匹配成功：j遍历完模式串所有字符
    if (j >= T.length) {
        // 返回从1开始的位置（算法常用），如果想返回0开始的位置，去掉+1即可
        return (i - T.length) + 1;
    } else {
        return 0; // 匹配失败
    }
}

int main() {
    SString S,T;
    // 主串S：下标0~7，字符a~h，长度8（正确）
    S.ch[0]='a';
    S.ch[1]='b';
    S.ch[2]='c';
    S.ch[3]='d';
    S.ch[4]='e';
    S.ch[5]='f';
    S.ch[6]='g';
    S.ch[7]='h';
    S.length=8;

    // 模式串T：下标0~2，字符d~f，长度3（正确）
    T.ch[0]='d';
    T.ch[1]='e';
    T.ch[2]='f';
    T.length=3;

    int index=Index(S,T);
    // 统一用C++输出，避免混用printf
    printf("%d\n",index);
    return 0;
}