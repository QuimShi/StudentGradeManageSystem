#pragma once
//防止头文件重复包含

/*
学生结构
*/
//存储一个
typedef struct Student
{
	unsigned long long number;
	char name[32];
	float score;
}Student;


//存储多个（数据结构组织）（链表）
/*
节点Node
*/
typedef struct Node 
{
	Student stu;	  //学生
	struct Node* next;//指向下一个结点的指针（注意：此时不能直接用别名Node，而是要写完整struct Node：因为此时定义别名在}后写完别名后才定义完）
}Node;


/*
链表
*/
typedef struct List
{
	Node* front;//头指针：指向第一个结点
	int size;	//当前结点数量
}List;



/*
菜单功能
*/
typedef enum MenuOptions
{
	Quit,//退出系统
	Entry,
	Search,
	Remove,
	Print,
	Read,
	Save
}MenuOptions;


/*打印菜单，并提示用户选择功能*/
int menu();


/*
学生录入
*/
void entryStudent(List* list);//传入main文件中定义的参数

/*
打印学生
*/
void printStudent(List* list);

/*
保存学生(以二进制的方式保存：打开文件看不懂保存的数据)
*/
void saveStudent(List* list);

/*
保存学生（以我们能看懂的方式保存）
*/
void saveStudentHuman(List* list);

/*
查找学生（返回结点）
*/
Node* searchStudent(List* list);

/*
删除学生
*/
void removeStudent(List* list);

/*
读取学生(二进制文件)
*/
void readStudent(List* list);

/*
读取学生(能读懂的)
*/
void readStudentHuman(List* list);

