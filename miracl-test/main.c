#include <stdio.h>
#include "miracl.h"
#include <time.h>

int main(){
    // 初始化 MIRACL 系统
    miracl *mip = mirsys(100, 0);
    mip->IOBASE = 16;  // 设置输入输出为16进制

    // 定义大整数和椭圆曲线点
    big p, a, b, xP, yP, xQ, yQ,k;
    epoint *P, *Q,*R;

    p = mirvar(0);
    a = mirvar(0);
    b = mirvar(0);
    xP = mirvar(0);
    yP = mirvar(0);
    xQ = mirvar(0);
    yQ = mirvar(0);
    k=mirvar(0);

    // 初始化椭圆曲线上的点
    P = epoint_init();
    Q = epoint_init();
    R = epoint_init();  // 用于存储乘法结果

    // 设置椭圆曲线参数
    cinstr(p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");  // p
    cinstr(a, "0");  // a
    cinstr(b, "7");  // b


    // 初始化椭圆曲线
    ecurve_init(a, b, p, MR_PROJECTIVE);

    // 设置点 P 和 Q 的坐标
    cinstr(xP, "79BE667EF9DCBBAC55A62D92A4F6B2F578C93A1BC582D831DFD8C97D7E67B00B");
    cinstr(yP, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B4486340D98C8E8A4D65F7B5B8EE");

    epoint_set(xP, yP, 0, P);  // 设置点 P
    epoint_set(xP, yP, 0, Q);  // 设置点 Q （与 P 相同）

    // 开始测量椭圆加法的时间
    // clock_t start_time = clock();
    // for (int i = 0; i < 10000; ++i) {  // 重复加法以获得平均时间
    //     ecurve_add(P, Q);  // 椭圆曲线加法
    // }
    // clock_t end_time = clock();
    big xP1, yP1;
    xP1 = mirvar(0);
    yP1 = mirvar(0);
    epoint_get(P, xP1, yP1);
    char xP_str[200], yP_str[200];
    cotstr(xP1, xP_str);
    cotstr(yP1, yP_str);
    printf("P 的坐标: (%s, %s)\n", xP_str, yP_str);
  
    cinstr(k, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    clock_t start_time = clock();
    for (int i = 0; i < 1000; ++i) {  // 重复乘法以获得平均时间
        ecurve_mult(k, P, R);  // k * P = R
    }
    clock_t end_time = clock();

    // 计算并输出时间
    //  double total_time_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // 转换为毫秒
    // printf("椭圆曲线加法总时间: %.6f 毫秒\n", total_time_ms);
    // printf("单次椭圆曲线加法时间: %.6f 毫秒\n", total_time_ms / 10000);  // 单次加法时间

    // return 0;
    double total_time_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // 转换为毫秒
    printf("椭圆曲线乘法总时间: %.6f 毫秒\n", total_time_ms);
    printf("单次椭圆曲线乘法时间: %.6f 毫秒\n", total_time_ms / 1000);  // 单次乘法时间

    big xR, yR;
    xR = mirvar(0);
    yR = mirvar(0);
    epoint_get(R, xR, yR);  // 从 R 中提取 x 和 y 坐标

    // 打印 R 的 x 和 y 坐标
    char x_str[200];
    char y_str[200];
    cotstr(xR, x_str);  // 将 big 类型转换为字符串
    cotstr(yR, y_str);
    printf("R 的坐标: (%s, %s)\n", x_str, y_str);

    // 释放内存
    mirkill(xR);
    mirkill(yR);
    epoint_free(P);
    epoint_free(R);
    return 0;
}
