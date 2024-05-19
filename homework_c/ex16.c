#include<stdio.h>
#include<string.h>

struct Person
{
	char name[20];
	int age;
	int height;
	int weight;
};

void Person_create(struct Person *who,char *name,int age,int height,int weight)
{
	strcpy(who->name,name);
	who->age = age;
	who->height = height;
	who->weight = weight;
}

void Person_print(struct Person *who)
{
	// 打印个人信息
	printf("Name: %s\n",who->name);
	printf("\tAge: %d\n",who->age);
	printf("\tHeight: %d\n",who->height);
	printf("\tWeight: %d\n",who->weight);
}

int main(int argc,char *argv[])
{
	// 创建两个 Person 结构
	struct Person joe;
	Person_create(&joe,"Joe Alex",32,64,140);
	struct Person frank; 
	Person_create(&frank,"Frank Blank",20,72,180);
	
	// 打印它们的信息以及内存位置
	printf("Joe\n");
	Person_print(&joe);

	printf("Frank\n");
	Person_print(&frank);

	//Person_print(NULL);  //Segmentation fault (core dumped)
	// 让他们每个人年龄增加 20 岁并重新打印信息
	joe.age += 20;
	joe.height -=2;
	joe.weight +=40;
	Person_print(&joe);

	frank.age += 20;
	frank.weight += 20;
	Person_print(&frank);

	//Person_destory(NULL); //Person_destory: Assertion `who != NULL' failed.
	return 0;
}

