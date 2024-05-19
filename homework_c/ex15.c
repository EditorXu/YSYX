#include<stdio.h>
int main(int argc,char *argv[])
{
	int ages[] = {23,43,12,89,2};
	char *names[] = {"Alan","Frank","Mary","John","Lisa"};

	int count = sizeof(ages) / sizeof(int);
	int i;


	for(i = 0;i < count ; i++)
	{
		printf("%s has %d years alive.\n",names[i],ages[i]);
	}
	
	printf("---\n");
	
	int *cur_age = ages;
	char **cur_name = names;

	for(i = 0;i < count; i++)
	{
		printf("%s is %d years old.\n",*(cur_name+i),*(cur_age+i));
	}

	printf("---\n");

	for(i = 0;i< count;i++)
	{
		printf("%s is %d years old again.\n",cur_name[i],cur_age[i]);
	}

	printf("---\n");

	for(int i = 0;i < count;i++)
	{
		printf("%d point = %p\n",*(cur_age+i),(cur_age+i));
	}
	
	printf("---\n");

	for(int i =0;i < count;i++)
	{
		printf("%s point = %p\n",*(cur_name+i),(*cur_name+i)); 
		//*(cur_name+i) 表示取得指针数组中第 i 个指针所指向的值，而 (*cur_name+i) 表示取得指针数组中第一个指针所指向的地址再加上 i，然后取得该地址处的值。
	}

	printf("---\n");
	
	i =0;

	while(i < count)
	{
		printf("%s point = %p\n",*(cur_name+i),(*cur_name+i)); 
		i++;
	}
	
	printf("---\n");

	for(int i =0;i < count;i++)
	{
		printf("%d point = %p\n",**(cur_name+i),(cur_name+i)); 
		//*cur_name 取得姓名指针指向的第一个字符，然后 **(cur_name+i) 取得该字符的ASCII码值，最后 (cur_name+i) 取得指针的地址
	}


	printf("---\n");

	for(cur_name = names,cur_age = ages;(cur_age - ages) < count;cur_name++,cur_age++)
	{
		printf("%s lived %d years so far.\n",*cur_name,*cur_age);
	}

	

	return 0;
}
[?1049h[?1h=[23m[24m[0m[37m[40m[1m[?25l[1;1H[1m[4m[33m  1 [24m[0m[37m[40m[1m[1m[4m[34m#include[24m[0m[37m[40m[1m[1m[4m[35m<stdio.h>[24m[0m[37m[40m[1m[4m                                                                                 [24m[37m[40m[1m[2;1H[1m[33m  2 [0m[37m[40m[1m[1m[32mint[0m[37m[40m[1m main([1m[32mint[0m[37m[40m[1m argc,[1m[32mchar[0m[37m[40m[1m *argv[])                                                                   [3;1H[1m[33m  3 [0m[37m[40m[1m{                                                                                                 [4;1H[1m[33m  4 [0m[37m[40m[1m  [1m[32mint[0m[37m[40m[1m ages[] = {[1m[35m23[0m[37m[40m[1m,[1m[35m43[0m[37m[40m[1m,[1m[35m12[0m[37m[40m[1m,[1m[35m89[0m[37m[40m[1m,[1m[35m2[0m[37m[40m[1m};                                                                   [5;1H[1m[33m  5 [0m[37m[40m[1m  [1m[32mchar[0m[37m[40m[1m *names[] = {[1m[35m"Alan"[0m[37m[40m[1m,[1m[35m"Frank"[0m[37m[40m[1m,[1m[35m"Mary"[0m[37m[40m[1m,[1m[35m"John"[0m[37m[40m[1m,[1m[35m"Lisa"[0m[37m[40m[1m};                                          [6;1H[1m[33m  6 [0m[37m[40m[1m                                                                                                  [7;1H[1m[33m  7 [0m[37m[40m[1m  [1m[32mint[0m[37m[40m[1m count = [1m[33msizeof[0m[37m[40m[1m(ages) / [1m[33msizeof[0m[37m[40m[1m([1m[32mint[0m[37m[40m[1m);                                                         [8;1H[1m[33m  8 [0m[37m[40m[1m                                                                                                  [9;1H[1m[33m  9 [0m[37m[40m[1m                                                                                                  [10;1H[1m[33m 10 [0m[37m[40m[1m  [1m[33mfor[0m[37m[40m[1m(i = [1m[35m0[0m[37m[40m[1m;i < count ; i++)                                                                      [11;1H[0m[34m[47m 11 +---  3 lines: {----------------------------------------------------------------------------------[0m[37m[40m[1m[12;1H[1m[33m 14 [0m[37m[40m[1m                                                                                                  [13;1H[1m[33m 15 [0m[37m[40m[1m  printf([1m[35m"---[0m[37m[40m[1m[1m[31m\n[0m[37m[40m[1m[1m[35m"[0m[37m[40m[1m);                                                                                [14;1H[1m[33m 16 [0m[37m[40m[1m                                                                                                  [15;1H[1m[33m 17 [0m[37m[40m[1m  [1m[32mint[0m[37m[40m[1m *cur_age = ages;                                                                            [16;1H[1m[33m 18 [0m[37m[40m[1m  [1m[32mchar[0m[37m[40m[1m **cur_name = names;                                                                        [17;1H[1m[33m 19 [0m[37m[40m[1m                                                                                                  [18;1H[1m[33m 20 [0m[37m[40m[1m  [1m[33mfor[0m[37m[40m[1m(i = [1m[35m0[0m[37m[40m[1m;i < count; i++)                                                                       [19;1H[0m[34m[47m 21 +---  3 lines: {----------------------------------------------------------------------------------[0m[37m[40m[1m[20;1H[1m[33m 24 [0m[37m[40m[1m                                                                                                  [21;1H[1m[33m 25 [0m[37m[40m[1m  printf([1m[35m"---[0m[37m[40m[1m[1m[31m\n[0m[37m[40m[1m[1m[35m"[0m[37m[40m[1m);                                                                                [22;1H[1m[33m 26 [0m[37m[40m[1m                                                                                                  [23;1H[1m[33m 27 [0m[37m[40m[1m  [1m[33mfor[0m[37m[40m[1m(i = [1m[35m0[0m[37m[40m[1m;i< count;i++)                                                                         [24;1H[0m[34m[47m 28 +---  3 lines: {----------------------------------------------------------------------------------[0m[37m[40m[1m[25;1H[1m[33m 31 [0m[37m[40m[1m                                                                                                  [26;1H[1m[33m 32 [0m[37m[40m[1m  printf([1m[35m"---[0m[37m[40m[1m[1m[31m\n[0m[37m[40m[1m[1m[35m"[0m[37m[40m[1m);                                                                                [27;1H[1m[33m 33 [0m[37m[40m[1m                                                                                                  [28;1H[1m[33m 34 [0m[37m[40m[1m  [1m[33mfor[0m[37m[40m[1m(cur_name = names,cur_age = ages;(cur_age - ages) < count;cur_name++,cur_age++)              [29;1H[0m[34m[47m 35 +---  3 lines: {----------------------------------------------------------------------------------[0m[37m[40m[1m[30;1H[1m[33m 38 [0m[37m[40m[1m                                                                                                  [31;1H[1m[33m 39 [0m[37m[40m[1m  [1m[33mreturn[0m[37m[40m[1m [1m[35m0[0m[37m[40m[1m;                                                                                       [32;1H[1m[33m 40 [0m[37m[40m[1m}                                                                                                 [33;1H[1m[33m 41 [0m[37m[40m[1m                                                                                                  [34;1H[1m[33m 42 [0m[37m[40m[1m                                                                                                  [35;1H[1m[34m~                                                                                                     [36;1H~                                                                                                     [37;1H~                                                                                                     [38;1H~                                                                                                     [39;1H~                                                                                                     [40;1H~                                                                                                     [41;1H~                                                                                                     [42;1H~                                                                                                     [43;1H~                                                                                                     [44;1H~                                                                                                     [45;1H~                                                                                                     [46;1H~                                                                                                     [47;1H~                                                                                                     [48;1H~                                                                                                     [49;1H~                                                                                                     [50;1H~                                                                                                     [51;1H~                                                                                                     [52;1H~                                                                                                     [53;1H~                                                                                                     [54;1H~                                                                                                     [55;1H~                                                                                                     [56;1H~                                                                                                     [57;1H~                                                                                                     [58;1H~                                                                                                     [59;1H~                                                                                                     [60;1H~                                                                                                     [61;1H~                                                                                                     [62;1H~                                                                                                     [63;1H~                                                                                                     [64;1H~                                                                                                     [65;1H~                                                                                                     [66;1H~                                                                                                     [67;1H~                                                                                                     [68;1H~                                                                                                     [0m[37m[40m[1m[69;1H[1m[7m ~/ysyx-workbench/homework_c/ex16.c[1]                                   [c] unix utf-8 Ln 1, Col 1/42[0m[37m[40m[1m[70;1H[1mrecording @q[0m[37m[40m[1m                                                                                          [1;5H[34h[?25h[70;1H
                                                                                                      [70;1H[1m[32mW11: Warning: File "ex16.c" has changed since editing started[0m[37m[40m[1m
                                                                                                      [70;1H[1m[32mSee ":help W11" for more info.[0m[37m[40m[1m
                                                                                                      [70;1H[1m[32m[O]K, (L)oad File: [0m[37m[40m[1m[39;49m[0m[?1l>[?1049lVim: Caught deadly signal HUP
Vim: Finished.
[70;1H[23m[24m[0m[37m[40m[1m[39;49m[0m