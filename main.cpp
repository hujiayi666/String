#include <iostream>
#define MAXLEN 255
typedef struct {
    char ch[MAXLEN];
    int length;
} SString;

// 计算模式串T的next数组
void Get_next(SString T, int next[]) {
    int i = 1, j = 0;  // 注意：j初始值是0，不是1（原代码j初始1会导致逻辑错误）
    next[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

// KMP匹配：在主串S中找模式串T，返回首次匹配的起始位置（从1开始），无匹配返回0
int Index_KMP(SString S, SString T, int next[]) {
    int i = 1, j = 1;
    while (i <= S.length && j <= T.length) {
        if (j == 0 || S.ch[i] == T.ch[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    // 修正：j超过模式串长度时，说明完全匹配
    if (j > T.length) {
        return i - T.length;
    } else {
        return 0;
    }
}
void Get_nextval(SString T, int nextval[]) {
    int i = 1, j = 0;
    nextval[1] = 0;
    while (i < T.length) {
        if (j == 0 || T.ch[i] == T.ch[j]) {
            ++i;
            ++j;
            if (T.ch[i] != T.ch[j]) {
                nextval[i] = j;
            }
            else {
                nextval[i] = nextval[j];
            }
        }
        else {
            j = nextval[j];
        }
    }
}
int main() {
    SString S;
    SString T;
    // 初始化主串S："aaabaaaab"（长度9）
    S.ch[1] = 'a';
    S.ch[2] = 'a';
    S.ch[3] = 'a';
    S.ch[4] = 'b';
    S.ch[5] = 'a';
    S.ch[6] = 'a';
    S.ch[7] = 'a';
    S.ch[8] = 'a';
    S.ch[9] = 'b';
    S.length = 9;
    // 初始化模式串T："aaaab"（长度5）
    T.ch[1] = 'a';
    T.ch[2] = 'a';
    T.ch[3] = 'a';
    T.ch[4] = 'a';
    T.ch[5] = 'b';
    T.length = 5;
    int index;
    // 修正1：next数组长度至少为T.length+1（覆盖1~T.length）
    int next[MAXLEN];
    // 修正2：传入模式串T计算next数组
    Get_next(T, next);
    // KMP匹配
    index = Index_KMP(S, T, next);
    // 输出结果：应该是5（主串第5位开始匹配到模式串）
    printf("%d\n", index);
    int nextval[MAXLEN];
    Get_nextval(T, nextval);
    int index2 = Index_KMP(S, T, nextval);
    printf("%d\n", index2);
    for (int i=1;i<=5;i++) {
        printf("%d\n", next[i]);
    }
    printf("============\n");
    for (int i=1;i<=5;i++) {
        printf("%d\n", nextval[i]);
    }
    return 0;
}