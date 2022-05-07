#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100  //声明常量表示数组长度 

int digit;

//将char数组逆序赋值到int数组中
void convert(char str1[],char str2[],int num1[],int num2[]) {
	int i,j;
	//转换第一个char数组
	for(i=0,j=strlen(str1)-1; j>=0; i++,j--) {
		num1[i+1]=str1[j]-'0';
	}
	//赋值长度
	num1[0]=i;
	//转换第二个char数组
	for(i=0,j=strlen(str2)-1; j>=0; i++,j--) {
		num2[i+1]=str2[j]-'0';
	}
	//赋值长度
	num2[0]=i;
}

//大数比较
int compare(int num1[],int num2[]) {
	int i;
	//首先判断长度
	if(num1[0]<num2[0]) {
		//被除数小于除数
		return -1;
	}
	if(num1[0]>num2[0]) {
		//被除数大于除数
		return 1;
	}
	//被除数长度等于除数长度
	for(i=num1[0]; i>=1; i--) {
		if(num1[i]==num2[i]) {
			continue;
		}
		if(num1[i]>num2[i]) {
			//被除数大于除数
			return 1;
		}
		if(num1[i]<num2[i]) {
			//被除数小于除数
			return -1;
		}
	}
	//被除数等于除数
	return 0;
}

//大数乘法
void mul() {
	int i,j,t,f=0;
	//存储输入的大数
	char str1[MAX],str2[MAX];
	//存储转换后的大数与
	int num1[MAX],num2[MAX];
	//存储结果
	int res[MAX];
	//开始输入
	printf("请输入第一个大数:");
	scanf("%s",str1);
	printf("请输入第二个大数:");
	scanf("%s",str2);
	//将char数组逆序赋值到int数组中
	convert(str1,str2,num1,num2);
	//将结果数组清0
	for(i=0; i<MAX; i++) {
		res[i]=0;
	}
	//开始计算大数乘法
	//将第一个大数乘以第二个大数的每个数字,需要进位
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
	//计算结果的位数
	for(i=MAX-1; res[i]==0; i--);
	//赋值结果位数
	res[0]=i;
	//输出结果
	printf("两个数的乘积为:");
	for(i=res[0]; i>=1; i--) {
		printf("%d",res[i]);
	}
	printf("\n\n");
}

//大数减法
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
	//判断减法结束之后,被除数的位数
	for(i=num1[0]; i>=1; i--) {
		if(num1[i]) {
			digit=i;
			break;
		}
	}
}

//大数除法
void divi() {
	int i,j,t,c,f=0,len,k=0;
	//存储输入的大数
	char str1[MAX],str2[MAX];
	//存储转换后的大数与位数
	int num1[MAX],num2[MAX],num1Len,num2Len;
	//存储结果
	int res[MAX],resLen;
	//开始输入
	printf("请输入第一个大数:");
	scanf("%s",str1);
	printf("请输入第二个大数:");
	scanf("%s",str2);
	//将char数组逆序赋值到int数组中
	convert(str1,str2,num1,num2);
	//将结果数组清0
	for(i=0; i<MAX; i++) {
		res[i]=0;
	}
	//开始计算大数除法
	//首先比较大小
	c=compare(num1,num2);
	//判断比较结果
	if(c==-1) {
		//被除数小于除数,直接输出结果
		printf("两个数的商为:0,余数为:");
		for(i=num1[0]; i>=1; i--) {
			printf("%d",num1[i]);
		}
		printf("\n\n");
	} else if(c==0) {
		//被除数等于除数,直接输出结果
		printf("两个数的商为:1,余数为:0!\n\n");
	} else {
		//被除数大于除数
		//两个大数位数的差值
		len=num1[0]-num2[0];
		//将除数后补零使得两个大数位数相同。
		for(i=num1[0]; i>=1; i--) {
			if(i>len) {
				num2[i]=num2[i-len];
			} else {
				num2[i]=0;
			}
		}
		num2[0]=num1[0];
		//将原被除数位数赋值给digit
		digit=num1[0];
		for(j=0; j<=len; j++) {
			res[len-j+1]=0;
			//判断两个数的大小以及被除数位数与除数原位数的关系
			while(((c=compare(num1,num2))>=0) && digit>=k) {
				//大数减法
				sub(num1,num2);
				//储存商的每一位
				res[len-j+1]++;
				//重新修改被除数的长度
				num1[0]=digit;
				if(num1[0]<num2[0]&&num2[num2[0]]==0) {
					//将被除数长度赋给除数;
					num2[0]=num1[0];
				}
			}
			//若被除数小于除数,除数减小一位。
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
		//计算结果的商的位数
		for(i=MAX-1; res[i]==0; i--);
		//赋值结果的商的位数
		res[0]=i;
		//计算结果的商的位数
		for(i=num1[0]; num1[i]==0; i--);
		//赋值结果的商的位数
		num1[0]=i;
		//输出结果
		//输出商
		printf("两个数的商为:");
		for(i=res[0]; i>=1; i--) {
			printf("%d",res[i]);
		}
		printf(",余数为:");
		//输出余数
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
	//进入while循环
	while(1) {
		//显示主菜单
		printf("================================================\n");
		printf("=                   大数运算                   =\n");
		printf("================================================\n");
		printf("=                                              =\n");
		printf("=                  1.大数乘法                  =\n");
		printf("=                  2.大数除法                  =\n");
		printf("=                  0.退出系统                  =\n");
		printf("=                                              =\n");
		printf("================================================\n");
		//输入功能编号
		printf("请输入您需要执行的功能编号:");
		scanf("%d",&n);
		//根据功能编号选择对应功能
		switch(n) {
			case 0:
				//退出系统
				exit(0);
				break;
			case 1:
				//大数乘法
				mul();
				break;
			case 2:
				//大数除法
				divi();
				break;
			default:
				//输入功能编号不存在
				printf("您输入的功能编号不存在,请重新输入!\n\n");
				break;
		}
		//按任意键继续
		system("pause");
		//清屏
		system("cls");
	}
}
