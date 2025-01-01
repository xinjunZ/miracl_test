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
    cinstr(xP, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798");
    cinstr(yP, "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");

    epoint_set(xP,yP, 1, P);  // 设置点 P
    epoint_set(xP,yP, 1, Q);  // 设置点 Q （与 P 相同）

    // 开始测量椭圆加法的时间
    clock_t start_time = clock();
    for (int i = 0; i < 10000; ++i) {  // 重复加法以获得平均时间
        ecurve_add(P, Q);  // 椭圆曲线加法
    }
    clock_t end_time = clock();
    
    // 计算并输出时间
     double total_time_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // 转换为毫秒
    printf("椭圆曲线加法总时间: %.6f 毫秒\n", total_time_ms);
    printf("单次椭圆曲线加法时间: %.6f 毫秒\n", total_time_ms / 10000);  // 单次加法时间

    return 0;
    
    epoint_free(P);
    epoint_free(Q);
}
