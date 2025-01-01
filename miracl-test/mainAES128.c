#include "miracl.h"
#include "stdio.h"
#include "time.h"

 void AesTest()
{
 aes _aes;
 char szAesKey[] = "1234567890abcdef";
 char szStr[32] = {"优雅人生"};
 
 printf("密钥：%s\n明文：%s\n", szAesKey, szStr);
 // 128 -- 16
 // 192 -- 24
 // 256 -- 32
clock_t start_time1 = clock();
 aes_init(&_aes, MR_ECB, 16, szAesKey, NULL);
 int len = aes_encrypt(&_aes, szStr);
 aes_end(&_aes);
clock_t end_time1 = clock();

double total_time_ms1 = (double)(end_time1 - start_time1) / CLOCKS_PER_SEC * 1000; 
printf("AES加密时间: %.6f 毫秒\n", total_time_ms1);
 
clock_t start_time2 = clock();
 for (int i = 0; i < 16; i++)
 {
  printf("%X", (unsigned char)szStr[i]);
 }
 printf("\n");
clock_t end_time2 = clock();

double total_time_ms2 = (double)(end_time2 - start_time2) / CLOCKS_PER_SEC * 1000; 
printf("AES解密时间: %.6f 毫秒\n", total_time_ms2);
 
}


int main(){
    
    AesTest();
}