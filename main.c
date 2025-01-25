#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#include "StudentManager.h"

//不将菜单代码全部写在main函数中，便创建函数 


int main(int arrgc, char* argv[]) {
	//循环之前【创建链表】
	List list = {0};//防止front是野指针，size是垃圾值
	//为了让所有人都能使用
	//内存设置memset(内存初始化的地址，初始化的内容，内存的大小)
	memset(&list, 0, sizeof(List));

	bool isRunning = true;
	//不想调用一次就退出程序，则要 “在主【循环】中调用 menu ” 
	while (isRunning)//若要使用true需要头文件#include<stdbool.h> 
	{//打印菜单并获取选择 
		switch (menu())
		{
			//英文单词替代数字，记忆数字对应的功能：利用 “枚举 ” 
		case Quit:
			isRunning = false;
			//printf("Quit\n");
			break;
		case Entry:
			entryStudent(&list);
			break;
		case Search:
		{
			Node* node = searchStudent(&list);
			
			if (!node) {
				printf("没有找到查询的学生。\n");
			}
			else {
				printf("%llu\t%s\t%.1f\n",
					node->stu.number,node->stu.name,node->stu.score
					);
			}
			break;
		}
		case Remove:
			removeStudent(&list);
			break;
		case Print:
			printStudent(&list);
			break;
		case Read:
			readStudent(&list);
			//readStudentHuman(&list);
		case Save:
			saveStudent(&list);
			saveStudentHuman(&list);
		}
		if (isRunning) {
			//程序【暂停】：若输出一个提示信息，不可瞬间清屏
			system("pause");
			//【清屏】：system函数（执行命令）---头文件：#include<stdlib.h> ；函数写法system("指令"); 
			//终端上能输入的指令，都能让system执行 [cls是清屏指令]
			system("cls");
		}

		//自动保存数据
		
		saveStudent(&list);
		saveStudentHuman(&list);
	}
}