#include "miracl.h"
#include "stdio.h"
#include "time.h"

//测试miracl库各类函数

int main() {
    miracl *mip = mirsys(500, 0);  // 初始化 MIRACL 系统
    mip->IOBASE = 16;  // 设置输出为16进制

    // 定义 x, n, p 和 result
    big x, n, p, result,randnumber;
    x = mirvar(0);    // x
    n = mirvar(0);    // n
    p = mirvar(0);    // p (取模)
    result = mirvar(0); // 用于存储结果
    randnumber=mirvar(0);

    char x_str[200];
    bigdig(128,2,x);
    cotstr(x, x_str); 
    printf("128位随机数x %s\n",x_str);

    // int bits=bit(x);
    // printf("x的位数为：%d",bits);


    // 设置 x, n 和 p 的值

    cinstr(x, "3");  // 设置 x 为 3
    cinstr(n, "500000f");  // 设置 n 为 500000f
    cinstr(p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");  // 设置 p 为指定的大数

    big y;
    y= mirvar(0);
    char n_str[200];

    divide(y, p, y);
    cotstr(y, n_str); 
    printf("y mod p的结果： %s\n",n_str);
    divide(n, p, y);
    
   
    cotstr(n, n_str); 
    printf("n mod p的结果： %s\n",n_str);


    big x1=mirvar(6);
    big x2=mirvar(2);
  
    cotstr(x1, n_str); 
    printf("x1: %s\n",n_str);
    cotstr(x2, n_str); 
    printf("x2: %s\n",n_str);

    multiply(x1,x2,x2);
    cotstr(x2, n_str); 
    printf("x2: %s\n",n_str);

    x1=mirvar(1);
    x2=mirvar(2);

    n=mirvar(3);
    clock_t start_time = clock();
    printf("x1和x2相比的结果：%d \n",subdiv(n,2,n));
    clock_t end_time = clock();
    double total_time_ms = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;  // 转换为毫秒
    printf("切比雪夫混沌映射时间: %.6f 毫秒\n", total_time_ms);

    printf("x1能否整除x2：%d \n", divisible(x1,x2));
    subdiv(x1,2,x1);
    cotstr(x1, n_str); 
    printf("x1除以2: %s\n",n_str);
    printf("x1和x1相比的结果：%d \n",mr_compare(x1,x1));

    // big b1=mirvar(3);
    // big b2=mirvar(0);
    // while (mr_compare(b1,b2)) {
    //     printf("循环内容%d",4);
    //     subdiv(b1,2,b1);
    // }
    // 输入 n 和 x
    big a1=mirvar(0);
    big a2=mirvar(3);

   
    // 初始化矩阵 A = [[0, 1], [-1, 2x]]
    big A[2][2];
    big a3=mirvar(0);
    premult(a2,2,a3);
    A[0][0] = mirvar(0);  
    A[0][1] = mirvar(1);  
    A[1][0] = mirvar(-1); 
    A[1][1] = mirvar(0);
    copy(a3,A[1][1]);

    cotstr(A[0][0], n_str); 
    printf("A[0][0]: %s\n",n_str);
    cotstr(A[0][1], n_str); 
    printf("A[0][1]: %s\n",n_str);
    cotstr(A[1][0], n_str); 
    printf("A[1][0]: %s\n",n_str);
    cotstr(A[1][1], n_str); 
    printf("A[1][1]: %s\n",n_str);

    big  temp[2][2] = {{A[0][0], A[0][1]}, {A[1][0], A[1][1]}};
    cotstr(temp[0][0], n_str); 
    printf("temp[0][0]: %s\n",n_str);
    cotstr(temp[0][1], n_str); 
    printf("temp[0][1]: %s\n",n_str);
    cotstr(temp[1][0], n_str); 
    printf("temp[1][0]: %s\n",n_str);
    cotstr(temp[1][1], n_str); 
    printf("temp[1][1]: %s\n",n_str);


    return 0;
}