#include "StudentManager.h"

#include<stdio.h>
#include<malloc.h>
#include<string.h>

//创建结点函数：内部函数，外不可用，所以用static
static Node* CreateNode() {
	//创建结点（动态内存分配）:因为要插入链表，若定义局部变量，则自动释放，所以使用动态内存分配。->头文件：#include<malloc.h>
	Node* node = malloc(sizeof(Node));
	//判断是否分配失败（内存不够）
	if (!node) {
		printf("malloc failed\n");
		return NULL;//无内存即没有必要输入了
	}
	node->next = NULL;
	return node;
}

int menu() {//返回类型为整形 
	printf("**************************\n\n");
	printf("  欢迎使用学生管理系统\n\n");
	printf("**************************\n\n");
	printf("       请选择功能\n\n");
	printf("**************************\n\n");
	printf("    1、插入学生成绩\n\n");
	printf("    2、查询学生成绩\n\n");
	printf("    3、删除学生成绩\n\n");
	printf("    4、打印学生成绩\n\n");
	printf("    5、登记学生成绩\n\n");
	printf("    6、保存学生成绩\n\n");
	printf("    0、退出系统\n\n");
	printf("**************************\n\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	Node* node = CreateNode();

	//输出学生信息
	printf("输入学生学号>\n");
	scanf("%llu", &node->stu.number);

	printf("输入学生姓名>\n");
	scanf("%s", &node->stu.name);

	printf("输入学生成绩>\n");
	scanf("%f", &node->stu.score);

	//插入到链表中
	node->next = list->front;//将新节点插入到链表头部
	list->front = node;//头指针作为下一个；给头指针赋值
	list->size++;
}

void printStudent(List* list)
{
	//先打印头部信息
	printf("*******************************************\n\n");
	printf("         欢迎使用学生管理系统\n\n");
	printf("*******************************************\n\n");
	printf("*    学号     *    姓名     *    成绩     *\n\n");
	printf("*******************************************\n\n");
	//遍历链表
	Node* curNode = list->front;
	while (curNode != NULL) {//未遍历到最后时执行
		printf("*%llu*    %s    *    %.1f    *\n",curNode->stu.number,curNode->stu.name,curNode->stu.score);
		curNode = curNode->next;
	}
}

void saveStudent(List* list)
{
	//打开文件
	FILE* fp = fopen("students.data","wb");//参数是文件名称；方式：wb(创建文件)
	if (!fp) {
		perror("file open failed");
		return;
	}//打开失败-提示
	//perror:当文件打开失败时，会写出详细的错误原因

	//打开成功后：写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {
		fwrite(&curNode->stu,sizeof(Student),1,fp);
		curNode = curNode->next;
	}

	//关闭文件
	fclose(fp);
}

void saveStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "w");//参数是文件名称；方式：wb(创建文件)
	if (!fp) {
		perror("file open failed");
		return;
	}//打开失败-提示
	//perror:当文件打开失败时，会写出详细的错误原因

	//打开成功后：写入学生信息
	Node* curNode = list->front;
	while (curNode != NULL) {
		fprintf(fp,"%llu\t%s\t%.1f\n",curNode->stu.number,curNode->stu.name,curNode->stu.score);//通过格式化打印的方式写入文件
		curNode = curNode->next;
	}

	//关闭文件
	fclose(fp);
}

Node* searchStudent(List* list)
{
	//当数据为空时
	if (list->size == 0) {
		return NULL;
	}

	char buffer[32];
	printf("请输入要查找的学生学号或姓名>");
	scanf("%s", buffer);

	//尝试把buffer转成整形
	unsigned long long number=-1;
	sscanf(buffer, "%llu", &number);

	//遍历比对
	Node* curNode = list->front;
	while (curNode != NULL) {
		if (strcmp(curNode->stu.name, buffer) == 0||//按姓名查找
			curNode->stu.number==number) {
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;
}

void removeStudent(List* list)
{	
	//当数据为空时
	if (list->size == 0) {
		printf("暂无学生\n");
		return;
	}

	
	//输入逻辑（同查找前部分）
	char buffer[32];
	printf("请输入要修改的学生学号或姓名>");
	scanf("%s", buffer);

	//尝试把buffer转成整形
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	//遍历//先找到（非删除第一个结点的特殊情况时：前一个结点的指针域指向后一个结点的数据域，删除找到的结点）
	Node* curNode = list->front;
	Node* prevNode = NULL;
	while (curNode != NULL) {
		//判断是否要找的
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number) {
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	//判断是否找到（若不为空则表示是在循环结束前break的即为找到）
	if (curNode) {
		//当要删除的结点是第一个结点时
		if (prevNode == NULL) {
			list->front = curNode->next;
		}
		else {//否则，倘若不是第一个结点
			prevNode->next = curNode->next;
		}
		free(curNode);
		list->size--;
	}

}

void readStudent(List* list)
{
	//打开文件
	FILE* fp = fopen("students.data","rb");
	if (!fp) {
		perror("file open failed");
		return;
	}

	//读取学生信息
	while (!feof(fp)) {//feof函数：判断有无读完//!feof(fp)即为没有读完的时候
		Node* node = CreateNode();
		if (!node)
			break;

		size_t len=fread(&node->stu, sizeof(Student), 1, fp);//fread会返回一个成功读取的数量
		if (len == 0) {
			free(node);
			break;
		}
		//插入到链表中
		node->next = list->front;
		list->front = node;
		list->size++;
	}


	//关闭文件
	fclose(fp);
}

void readStudentHuman(List* list)
{
	//打开文件
	FILE* fp = fopen("students.txt", "r");
	if (!fp) {
		perror("file open failed");
		return;
	}
	//读取学生信息
	while (!feof(fp))
	{
		Node* node = CreateNode();
		if (!node)break;
		if (3 != fscanf(fp,"%llu\t%s\t%.1f\n", &node->stu.number, node->stu.name, &node->stu.score))
		{
			free(node);
			break;
		}
		//插入链表
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	//关闭文件
	fclose(fp);
}

