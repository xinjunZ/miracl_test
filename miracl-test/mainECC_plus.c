#include <stdio.h>
#include "miracl.h"
#include <time.h>

char x_str[200];
int main() {
    // 初始化 MIRACL 系统
    miracl *mip = mirsys(100, 0);
    mip->IOBASE = 16;  // 设置输入输出为16进制

    // 定义大整数和椭圆曲线点
    big p, a, b, xP, yP, k;
    epoint *P, *R;

    p = mirvar(0);
    a = mirvar(0);
    b = mirvar(0);
    xP = mirvar(0);
    yP = mirvar(0);
    k = mirvar(0);

    // 初始化椭圆曲线上的点
    P = epoint_init();
    R = epoint_init();  // 用于存储乘法结果

    // 设置椭圆曲线参数
    cinstr(p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");  // p
    cinstr(a, "0");  // a
    cinstr(b, "7");  // b

    // 初始化椭圆曲线
    ecurve_init(a, b, p, MR_PROJECTIVE);

    // 设置点 P 的坐标
    cinstr(xP, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    cinstr(yP, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");

    epoint_set(xP, yP, 1, P);  // 设置点 P

    // 设置标量 k
    cinstr(k, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");  // 大标量 k

    // 开始测量椭圆曲线乘法的时间
    clock_t start_time = clock();
    for (int i = 0; i < 1000; ++i) {  // 重复乘法以获得平均时间
        ecurve_mult(k, P, R);  // 椭圆曲线乘法
    }
    clock_t end_time = clock();
    // 计算并输出时间
    
    big x=mirvar(0), y=mirvar(0);
    epoint_get(P, x, y);  // 获取点 P 的坐标
    printf("点 P 的坐标：\n");
    cotstr(x, x_str); 
    printf("[%s,",x_str);
    cotstr(y, x_str); 
    printf("%s]\n",x_str);
    epoint_get(R, x, y);  // 获取点 R 的坐标
    printf("点 R 的坐标：\n");
    cotstr(x, x_str); 
    printf("[%s,",x_str);
    cotstr(y, x_str); 
    printf("%s]\n",x_str);
   
    
    double total_time_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // 转换为毫秒
    printf("单次椭圆曲线乘法时间: %.6f 毫秒\n", total_time_ms / 1000);  // 单次乘法时间

    // 释放内存
    epoint_free(P);
    epoint_free(R);

    return 0;
}
