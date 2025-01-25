#include "StudentManager.h"

#include<stdio.h>
#include<malloc.h>
#include<string.h>

//������㺯�����ڲ��������ⲻ���ã�������static
static Node* CreateNode() {
	//������㣨��̬�ڴ���䣩:��ΪҪ��������������ֲ����������Զ��ͷţ�����ʹ�ö�̬�ڴ���䡣->ͷ�ļ���#include<malloc.h>
	Node* node = malloc(sizeof(Node));
	//�ж��Ƿ����ʧ�ܣ��ڴ治����
	if (!node) {
		printf("malloc failed\n");
		return NULL;//���ڴ漴û�б�Ҫ������
	}
	node->next = NULL;
	return node;
}

int menu() {//��������Ϊ���� 
	printf("**************************\n\n");
	printf("  ��ӭʹ��ѧ������ϵͳ\n\n");
	printf("**************************\n\n");
	printf("       ��ѡ����\n\n");
	printf("**************************\n\n");
	printf("    1������ѧ���ɼ�\n\n");
	printf("    2����ѯѧ���ɼ�\n\n");
	printf("    3��ɾ��ѧ���ɼ�\n\n");
	printf("    4����ӡѧ���ɼ�\n\n");
	printf("    5���Ǽ�ѧ���ɼ�\n\n");
	printf("    6������ѧ���ɼ�\n\n");
	printf("    0���˳�ϵͳ\n\n");
	printf("**************************\n\n");
	printf("select>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entryStudent(List* list)
{
	Node* node = CreateNode();

	//���ѧ����Ϣ
	printf("����ѧ��ѧ��>\n");
	scanf("%llu", &node->stu.number);

	printf("����ѧ������>\n");
	scanf("%s", &node->stu.name);

	printf("����ѧ���ɼ�>\n");
	scanf("%f", &node->stu.score);

	//���뵽������
	node->next = list->front;//���½ڵ���뵽����ͷ��
	list->front = node;//ͷָ����Ϊ��һ������ͷָ�븳ֵ
	list->size++;
}

void printStudent(List* list)
{
	//�ȴ�ӡͷ����Ϣ
	printf("*******************************************\n\n");
	printf("         ��ӭʹ��ѧ������ϵͳ\n\n");
	printf("*******************************************\n\n");
	printf("*    ѧ��     *    ����     *    �ɼ�     *\n\n");
	printf("*******************************************\n\n");
	//��������
	Node* curNode = list->front;
	while (curNode != NULL) {//δ���������ʱִ��
		printf("*%llu*    %s    *    %.1f    *\n",curNode->stu.number,curNode->stu.name,curNode->stu.score);
		curNode = curNode->next;
	}
}

void saveStudent(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.data","wb");//�������ļ����ƣ���ʽ��wb(�����ļ�)
	if (!fp) {
		perror("file open failed");
		return;
	}//��ʧ��-��ʾ
	//perror:���ļ���ʧ��ʱ����д����ϸ�Ĵ���ԭ��

	//�򿪳ɹ���д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL) {
		fwrite(&curNode->stu,sizeof(Student),1,fp);
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

void saveStudentHuman(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.txt", "w");//�������ļ����ƣ���ʽ��wb(�����ļ�)
	if (!fp) {
		perror("file open failed");
		return;
	}//��ʧ��-��ʾ
	//perror:���ļ���ʧ��ʱ����д����ϸ�Ĵ���ԭ��

	//�򿪳ɹ���д��ѧ����Ϣ
	Node* curNode = list->front;
	while (curNode != NULL) {
		fprintf(fp,"%llu\t%s\t%.1f\n",curNode->stu.number,curNode->stu.name,curNode->stu.score);//ͨ����ʽ����ӡ�ķ�ʽд���ļ�
		curNode = curNode->next;
	}

	//�ر��ļ�
	fclose(fp);
}

Node* searchStudent(List* list)
{
	//������Ϊ��ʱ
	if (list->size == 0) {
		return NULL;
	}

	char buffer[32];
	printf("������Ҫ���ҵ�ѧ��ѧ�Ż�����>");
	scanf("%s", buffer);

	//���԰�bufferת������
	unsigned long long number=-1;
	sscanf(buffer, "%llu", &number);

	//�����ȶ�
	Node* curNode = list->front;
	while (curNode != NULL) {
		if (strcmp(curNode->stu.name, buffer) == 0||//����������
			curNode->stu.number==number) {
			return curNode;
		}
		curNode = curNode->next;
	}
	return NULL;
}

void removeStudent(List* list)
{	
	//������Ϊ��ʱ
	if (list->size == 0) {
		printf("����ѧ��\n");
		return;
	}

	
	//�����߼���ͬ����ǰ���֣�
	char buffer[32];
	printf("������Ҫ�޸ĵ�ѧ��ѧ�Ż�����>");
	scanf("%s", buffer);

	//���԰�bufferת������
	unsigned long long number = -1;
	sscanf(buffer, "%llu", &number);

	//����//���ҵ�����ɾ����һ�������������ʱ��ǰһ������ָ����ָ���һ������������ɾ���ҵ��Ľ�㣩
	Node* curNode = list->front;
	Node* prevNode = NULL;
	while (curNode != NULL) {
		//�ж��Ƿ�Ҫ�ҵ�
		if (strcmp(curNode->stu.name, buffer) == 0 || curNode->stu.number == number) {
			break;
		}
		prevNode = curNode;
		curNode = curNode->next;
	}
	//�ж��Ƿ��ҵ�������Ϊ�����ʾ����ѭ������ǰbreak�ļ�Ϊ�ҵ���
	if (curNode) {
		//��Ҫɾ���Ľ���ǵ�һ�����ʱ
		if (prevNode == NULL) {
			list->front = curNode->next;
		}
		else {//�����������ǵ�һ�����
			prevNode->next = curNode->next;
		}
		free(curNode);
		list->size--;
	}

}

void readStudent(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.data","rb");
	if (!fp) {
		perror("file open failed");
		return;
	}

	//��ȡѧ����Ϣ
	while (!feof(fp)) {//feof�������ж����޶���//!feof(fp)��Ϊû�ж����ʱ��
		Node* node = CreateNode();
		if (!node)
			break;

		size_t len=fread(&node->stu, sizeof(Student), 1, fp);//fread�᷵��һ���ɹ���ȡ������
		if (len == 0) {
			free(node);
			break;
		}
		//���뵽������
		node->next = list->front;
		list->front = node;
		list->size++;
	}


	//�ر��ļ�
	fclose(fp);
}

void readStudentHuman(List* list)
{
	//���ļ�
	FILE* fp = fopen("students.txt", "r");
	if (!fp) {
		perror("file open failed");
		return;
	}
	//��ȡѧ����Ϣ
	while (!feof(fp))
	{
		Node* node = CreateNode();
		if (!node)break;
		if (3 != fscanf(fp,"%llu\t%s\t%.1f\n", &node->stu.number, node->stu.name, &node->stu.score))
		{
			free(node);
			break;
		}
		//��������
		node->next = list->front;
		list->front = node;
		list->size++;
	}

	//�ر��ļ�
	fclose(fp);
}

