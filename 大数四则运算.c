#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100  //����������ʾ���鳤�� 

int digit;

//��char��������ֵ��int������
void convert(char str1[],char str2[],int num1[],int num2[]) {
	int i,j;
	//ת����һ��char����
	for(i=0,j=strlen(str1)-1; j>=0; i++,j--) {
		num1[i+1]=str1[j]-'0';
	}
	//��ֵ����
	num1[0]=i;
	//ת���ڶ���char����
	for(i=0,j=strlen(str2)-1; j>=0; i++,j--) {
		num2[i+1]=str2[j]-'0';
	}
	//��ֵ����
	num2[0]=i;
}

//�����Ƚ�
int compare(int num1[],int num2[]) {
	int i;
	//�����жϳ���
	if(num1[0]<num2[0]) {
		//������С�ڳ���
		return -1;
	}
	if(num1[0]>num2[0]) {
		//���������ڳ���
		return 1;
	}
	//���������ȵ��ڳ�������
	for(i=num1[0]; i>=1; i--) {
		if(num1[i]==num2[i]) {
			continue;
		}
		if(num1[i]>num2[i]) {
			//���������ڳ���
			return 1;
		}
		if(num1[i]<num2[i]) {
			//������С�ڳ���
			return -1;
		}
	}
	//���������ڳ���
	return 0;
}

//�����˷�
void mul() {
	int i,j,t,f=0;
	//�洢����Ĵ���
	char str1[MAX],str2[MAX];
	//�洢ת����Ĵ�����
	int num1[MAX],num2[MAX];
	//�洢���
	int res[MAX];
	//��ʼ����
	printf("�������һ������:");
	scanf("%s",str1);
	printf("������ڶ�������:");
	scanf("%s",str2);
	//��char��������ֵ��int������
	convert(str1,str2,num1,num2);
	//�����������0
	for(i=0; i<MAX; i++) {
		res[i]=0;
	}
	//��ʼ��������˷�
	//����һ���������Եڶ���������ÿ������,��Ҫ��λ
	for(i=1; i<=num2[0]; i++) {
		for(j=1; j<=num1[0]; j++) {
			t=num1[j]*num2[i];
			res[j+i-1]=res[j+i-1]+t%10+f;
			f=t/10+res[j+i-1]/10;
			res[j+i-1]=res[j+i-1]%10;
		}
		if(f!=0) {
			res[j+i-1]=res[j+i-1]+f;
			f=0;
		}
	}
	//��������λ��
	for(i=MAX-1; res[i]==0; i--);
	//��ֵ���λ��
	res[0]=i;
	//������
	printf("�������ĳ˻�Ϊ:");
	for(i=res[0]; i>=1; i--) {
		printf("%d",res[i]);
	}
	printf("\n\n");
}

//��������
void sub(int num1[],int num2[]) {
	int i;
	for(i=1; i<=num1[0]; i++) {
		if(num1[i]<num2[i]) {
			num1[i]=num1[i]+10-num2[i];
			num1[i+1]--;
		} else{
			num1[i]=num1[i]-num2[i];
		}
	}
	//�жϼ�������֮��,��������λ��
	for(i=num1[0]; i>=1; i--) {
		if(num1[i]) {
			digit=i;
			break;
		}
	}
}

//��������
void divi() {
	int i,j,t,c,f=0,len,k=0;
	//�洢����Ĵ���
	char str1[MAX],str2[MAX];
	//�洢ת����Ĵ�����λ��
	int num1[MAX],num2[MAX],num1Len,num2Len;
	//�洢���
	int res[MAX],resLen;
	//��ʼ����
	printf("�������һ������:");
	scanf("%s",str1);
	printf("������ڶ�������:");
	scanf("%s",str2);
	//��char��������ֵ��int������
	convert(str1,str2,num1,num2);
	//�����������0
	for(i=0; i<MAX; i++) {
		res[i]=0;
	}
	//��ʼ�����������
	//���ȱȽϴ�С
	c=compare(num1,num2);
	//�жϱȽϽ��
	if(c==-1) {
		//������С�ڳ���,ֱ��������
		printf("����������Ϊ:0,����Ϊ:");
		for(i=num1[0]; i>=1; i--) {
			printf("%d",num1[i]);
		}
		printf("\n\n");
	} else if(c==0) {
		//���������ڳ���,ֱ��������
		printf("����������Ϊ:1,����Ϊ:0!\n\n");
	} else {
		//���������ڳ���
		//��������λ���Ĳ�ֵ
		len=num1[0]-num2[0];
		//����������ʹ����������λ����ͬ��
		for(i=num1[0]; i>=1; i--) {
			if(i>len) {
				num2[i]=num2[i-len];
			} else {
				num2[i]=0;
			}
		}
		num2[0]=num1[0];
		//��ԭ������λ����ֵ��digit
		digit=num1[0];
		for(j=0; j<=len; j++) {
			res[len-j+1]=0;
			//�ж��������Ĵ�С�Լ�������λ�������ԭλ���Ĺ�ϵ
			while(((c=compare(num1,num2))>=0) && digit>=k) {
				//��������
				sub(num1,num2);
				//�����̵�ÿһλ
				res[len-j+1]++;
				//�����޸ı������ĳ���
				num1[0]=digit;
				if(num1[0]<num2[0]&&num2[num2[0]]==0) {
					//�����������ȸ�������;
					num2[0]=num1[0];
				}
			}
			//��������С�ڳ���,������Сһλ��
			if(c<0) {
				for(i=2; i<=num2[0]; i++) {
					num2[i-1]=num2[i];
				}
				num2[i-1]=0;
				if(num1[0]<num2[0]) {
					num2[0]--;
				}
			}
		}
		//���������̵�λ��
		for(i=MAX-1; res[i]==0; i--);
		//��ֵ������̵�λ��
		res[0]=i;
		//���������̵�λ��
		for(i=num1[0]; num1[i]==0; i--);
		//��ֵ������̵�λ��
		num1[0]=i;
		//������
		//�����
		printf("����������Ϊ:");
		for(i=res[0]; i>=1; i--) {
			printf("%d",res[i]);
		}
		printf(",����Ϊ:");
		//�������
		if(num1[0]!=0){
			for(i=num1[0]; i>=1; i--) {
				printf("%d",num1[i]);
			}
		}else{
			printf("0");
		}
		printf("!\n\n");
	}
}

void main() {
	int n;
	//����whileѭ��
	while(1) {
		//��ʾ���˵�
		printf("================================================\n");
		printf("=                   ��������                   =\n");
		printf("================================================\n");
		printf("=                                              =\n");
		printf("=                  1.�����˷�                  =\n");
		printf("=                  2.��������                  =\n");
		printf("=                  0.�˳�ϵͳ                  =\n");
		printf("=                                              =\n");
		printf("================================================\n");
		//���빦�ܱ��
		printf("����������Ҫִ�еĹ��ܱ��:");
		scanf("%d",&n);
		//���ݹ��ܱ��ѡ���Ӧ����
		switch(n) {
			case 0:
				//�˳�ϵͳ
				exit(0);
				break;
			case 1:
				//�����˷�
				mul();
				break;
			case 2:
				//��������
				divi();
				break;
			default:
				//���빦�ܱ�Ų�����
				printf("������Ĺ��ܱ�Ų�����,����������!\n\n");
				break;
		}
		//�����������
		system("pause");
		//����
		system("cls");
	}
}
