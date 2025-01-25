#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

#include "StudentManager.h"

//�����˵�����ȫ��д��main�����У��㴴������ 


int main(int arrgc, char* argv[]) {
	//ѭ��֮ǰ����������
	List list = {0};//��ֹfront��Ұָ�룬size������ֵ
	//Ϊ���������˶���ʹ��
	//�ڴ�����memset(�ڴ��ʼ���ĵ�ַ����ʼ�������ݣ��ڴ�Ĵ�С)
	memset(&list, 0, sizeof(List));

	bool isRunning = true;
	//�������һ�ξ��˳�������Ҫ ��������ѭ�����е��� menu �� 
	while (isRunning)//��Ҫʹ��true��Ҫͷ�ļ�#include<stdbool.h> 
	{//��ӡ�˵�����ȡѡ�� 
		switch (menu())
		{
			//Ӣ�ĵ���������֣��������ֶ�Ӧ�Ĺ��ܣ����� ��ö�� �� 
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
				printf("û���ҵ���ѯ��ѧ����\n");
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
			//������ͣ���������һ����ʾ��Ϣ������˲������
			system("pause");
			//����������system������ִ�����---ͷ�ļ���#include<stdlib.h> ������д��system("ָ��"); 
			//�ն����������ָ�������systemִ�� [cls������ָ��]
			system("cls");
		}

		//�Զ���������
		
		saveStudent(&list);
		saveStudentHuman(&list);
	}
}