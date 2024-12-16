#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>  // 用于高精度时间测量
#include "miracl.h"

// 定义切比雪夫多项式递归函数
void chebyshev_T(big Tn_1, big Tn_2, int n, big modulus, miracl *mip) {
    big Tn = mirvar(0);   // 当前的 Tn
    big two = mirvar(2);  // 常量 2
    
    for (int i = 2; i <= n; i++) {
        mad(Tn_1, two, Tn_2, modulus, modulus, Tn); // Tn = (2 * Tn_1 - Tn_2) mod modulus
        copy(Tn_1, Tn_2); // Tn-2 = Tn-1
        copy(Tn, Tn_1);   // Tn-1 = Tn
    }
    // 清理内存
    mirkill(Tn);
    mirkill(two);
}

int main() {
    // 初始化 MIRACL
    miracl *mip = mirsys(100, 0);
    mip->IOBASE = 16;

    // 定义大整数
    big T0 = mirvar(1);  // T0(x) = 1
    big T1 = mirvar(1);  // T1(x) = x
    big modulus = mirvar(0); // 模数
    
    // 设置模数为 128 位大整数
    cinstr(modulus, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");

    // 测试 n=128 的切比雪夫多项式
    int n = 128;
    struct timeval start, end;
    gettimeofday(&start, NULL); // 开始计时

    chebyshev_T(T1, T0, n, modulus, mip);

    gettimeofday(&end, NULL); // 结束计时

    // 计算时间差
    double elapsed_time = (end.tv_sec - start.tv_sec) * 1000.0; // 秒 -> 毫秒
    elapsed_time += (end.tv_usec - start.tv_usec) / 1000.0;     // 微秒 -> 毫秒

    printf("计算 n=%d 的切比雪夫多项式耗时: %.3f 毫秒\n", n, elapsed_time);

    // 清理内存
    mirkill(T0);
    mirkill(T1);
    mirkill(modulus);
    mirexit(); // 退出 MIRACL 系统

    return 0;
}
