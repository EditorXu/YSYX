#include <stdio.h>  
#include <stdlib.h>  
  
// 函数用于获取一个数的各位数字，并直接返回最大和最小数字  
void getDigitsAndMinMax(int num, int *maxDigit, int *minDigit) {  
    int digits[3];  
    for (int i = 0; i < 3; ++i) {  
        digits[i] = num % 10;  
        num /= 10;  
          
        // 更新最大和最小数字  
        if (i == 0 || digits[i] > *maxDigit) {  
            *maxDigit = digits[i];  
        }  
        if (i == 0 || digits[i] < *minDigit) {  
            *minDigit = digits[i];  
        }  
    }  
}  
  
// 函数用于构建最大和最小的数  
int buildMax(int maxDigit, int digit1, int minDigit) {  
    return maxDigit * 100 + digit1 * 10 + minDigit; 
}  
  
int buildMin(int minDigit, int digit1, int maxDigit) {  
    return minDigit * 100 + digit1 * 10 + maxDigit; 
}  
  
int main() {  
    int num, maxNum, minNum, diff;  
    int maxDigit, minDigit, digit1, digit2;  
    int step = 1;  
  
    // 读取输入的三位数  
    scanf("%d", &num);  
  
    // 循环直到黑洞数495出现  
    do {  
        // 获取数字的各位，并找到最大和最小数字  
        getDigitsAndMinMax(num, &maxDigit, &minDigit);  
        int a = (num / 10) % 10;
        // 根据最大和最小数字构建其余两个数字  
        if (maxDigit == (num % 10)) {  
            digit1 = num / 100;  
            digit2 = (num / 10) % 10;  
        } else if (maxDigit == a) {  
            digit1 = (num / 100);  
            digit2 = num % 10;  
        } else {  
            digit1 = num % 10;  
            digit2 = (num / 100) % 10;  
        }  
        
        if(digit1 < digit2)
        {
            int tmp = digit1;
            digit1 = digit2;
            digit2 =tmp;
        }
        // 构建最大和最小的数  
        maxNum = buildMax(maxDigit, digit1, minDigit);  
        minNum = buildMin(minDigit, digit1, maxDigit);  
          
        // 计算差值  
        diff = maxNum - minNum;  
          
        // 输出结果  
        printf("%d: %d - %d = %d\n", step++, maxNum, minNum, diff);  
          
        // 更新num为差值，进行下一次循环  
        num = diff;  
    } while (num != 495);  
  
    return 0;  
}
