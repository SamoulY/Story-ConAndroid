/*
Copyright 2013-2016 Yuer

This file is part of Story.

    Story is free software: you can redistribute it and/or 
	modify it under the terms of the GNU General Public 
	License as published by the Free Software Foundation, 
	either version 3 of the License, or (at your option) 
	any later version.

    Story is distributed in the hope that it will be useful, 
	but WITHOUT ANY WARRANTY; without even the implied 
	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
	PURPOSE.  See the GNU General Public License for more 
	details.

    You should have received a copy of the GNU General 
	Public License along with Story.  If not, see 
	<http://www.gnu.org/licenses/>.
*/

#include"����.cpp"

#define ver "0.7.4"

struct USERINFO
{
 char username[20];
 char userpwd[20];
};

struct USERINFO USER[100];
int CurCounts;
char jiami[20] = "hbxfbmphbxfbmphbxfb";
FILE* f1;
FILE* f2;
FILE* f3;

struct USERINFO Pwd(void)
{
 struct USERINFO pwd;
 char c;
 int i=0,k=0;
 while(i<=19)
 {
  pwd.userpwd[i] = '\0';
  i++;
 }
 i=0;
 while(i<=19)
   {
    c = getch();
    if(c==127) //�˸�ɾ��
	{
	 if(i!=0)
	 {
	  printf("\b \b");
	  if(i>0)
	  {
	   pwd.userpwd[i-1] = '\0';
	   i--;
	  }
	 }
	}
	if(c==10)  //�س�ʱ����
	{
	 break;
	}
	if(i!=19)
	{
	 if(c!=127&&c!=10)
	 {
	  pwd.userpwd[i] = c;
	  printf("*");
	  i++;
	 }
	}
   }
 printf("\n");
 return pwd;
}

bool Register(struct USERINFO newu)                  //ע��
{
 struct USERINFO pwd;
 struct USERINFO chg;
 int i=0,l;
 if(CurCounts==100)
 {
  printf("ע��������\n\n");
  return false;
 }
 printf("����дҪע����ʺź�����\n");
 printf("�ʺ�:");
 gets(newu.username);
 if(newu.username[0]<'a'||newu.username[0]>'z')
 {
  printf("�ʺ���λ��ΪСд��ĸ\n\n");
  return false;
 }
 l = strlen(newu.username);
 if(l<6)
 {
  printf("�ʺŲ�������6λ\n\n");
  return false;
 }
 while(i<=CurCounts-1)
 {
  if(strcmp(newu.username,USER[i].username)==0)
  {
   printf("�û��Ѵ���\n\n");
   return false;
  }
  i++;
 }
 for(i=0;i<=l-1;i++)
 {
  if((newu.username[i]<'a'||newu.username[i]>'z')&&(newu.username[i]<'0'||newu.username[i]>'9'))
  {
   printf("�ʺ��в����������ַ�\n\n");
   return false;
  }
 }
 if(strlen(newu.username)>=20)
 {
  printf("�ʺŹ���\n\n");
  return false;
 }
 printf(" ��\n");

 printf("����:");
 pwd = Pwd();
 strcpy(newu.userpwd,pwd.userpwd);
 l = strlen(newu.userpwd);
 if(l<6)
 {
  printf("���벻������6λ\n\n");
  return false;
 }
 if(l>=20)
 {
  printf("�������\n\n");
  return false;
 }
 for(i=0;i<=l-1;i++)
 {
  if((newu.userpwd[i]<'a'||newu.userpwd[i]>'z')&&(newu.userpwd[i]<'0'||newu.userpwd[i]>'9')&&
	  (newu.userpwd[i]<'A'||newu.userpwd[i]>'Z'))
  {
   printf("�����в����������ַ�\n\n");
   return false;
  }
 }
 printf(" ��\n");
 printf("��������һ��\n");
 printf("����:");
 chg = Pwd();
 if(strcmp(chg.userpwd,pwd.userpwd)!=0)
 {
  printf("���벻һ��\n\n");
  return false;
 }
 for(i=0;i<=strlen(newu.userpwd)-1;i++)
 {
  newu.userpwd[i] += jiami[i];
 }
 printf(" ��\n");

 printf("ע��ɹ�\n\n");
 USER[CurCounts] = newu;
 CurCounts++;
 f1 = fopen(accountfile,"wb");
 //f1 = fopen("account.ys","wb");
 fwrite(&CurCounts,4,1,f1);
 fwrite(USER,sizeof(struct USERINFO),CurCounts,f1);
 fclose(f1);
 return true;
}

bool Login(struct USERINFO login)                //��¼
{
 struct USERINFO pwd;
 char act[20];
 char name[20];
 int i=0,t,k;
 printf("������\n");
 printf("�ʺ�:");
 gets(login.username);
 while(i<=CurCounts-1)
 {
  if(strcmp(login.username,USER[i].username)==0)
  {
   break;
  }
  i++;
 }
 if(i==CurCounts)
 {
  printf("�ʻ�������\n\n");
  return false;
 }

 printf("����:");
 pwd = Pwd();
 strcpy(login.userpwd,pwd.userpwd);
 for(k=0;k<=strlen(login.userpwd)-1;k++)
 {
  login.userpwd[k] += jiami[k];
 }
 if(strcmp(login.userpwd,USER[i].userpwd)!=0)
 {
  printf("�������\n\n");
  return false;
 }
 i = 1;
 f3 = fopen(onlinefile,"rb+");
 if(f3!=NULL)
 {
  fread(&t,4,1,f3);
  while(i<=t)
  {
   fread(act,20,1,f3);
   if(strcmp(act,login.username)==0)
   {
    printf("���˺����ڵ�¼��\n\n");
	fclose(f3);
	return false;
   }
   fseek(f3,20L,1);
   i++;
  }
  t++;
  rewind(f3);
  fwrite(&t,4,1,f3);
  fclose(f3);
  f3 = fopen(onlinefile,"ab");
  fwrite(login.username,20,1,f3);
  strcpy(name,"\0");
  fwrite(name,20,1,f3);
  fclose(f3);
 }
 if(f3==NULL)
 {
  f3 = fopen(onlinefile,"wb");
  t = 1;
  fwrite(&t,4,1,f3);
  fwrite(login.username,20,1,f3);
  strcpy(name,"\0");
  fwrite(name,20,1,f3);
  fclose(f3);
 }
 printf("��¼�ɹ�\n\n");
 /*
 f2 = fopen("temp.ys","wb");
 fwrite(login.username,strlen(login.username),1,f2);
 char a[5] = ".ys";
 for(i=0;i<=3;i++)
 {
  fputc(a[i],f2);
 }
 fclose(f2);
 */
 //system("����.exe");
 cqmain(login.username);
 return true;
}

void main()
{
 printf("����");
 char version[10]=ver;
 printf("  v%s\nCopyright 2013-2016 Yuer\n",version);

 //ʼ����2015��10��23��
 mkdir(storyfolder);        //�����ļ���
 mkdir(savefolder);        //�����ļ���

 struct USERINFO use;
 f1 = fopen(accountfile,"rb");
 if(f1==NULL)
 {
  CurCounts=0;
  f1 = fopen(accountfile,"wb");
  fwrite(&CurCounts,4,1,f1);
  fclose(f1);
 }
 else
 {
  fread(&CurCounts,4,1,f1);
  fread(USER,sizeof(struct USERINFO),CurCounts,f1);
  fclose(f1);
 }
 int i,n,t=0;
 bool del;
 while(t==0)
 {
  printf("1.��¼��Ϸ\n");
  printf("2.ע���˺�\n");
  printf("3.�˳���Ϸ\n");
  printf("��ѡ��");
  scanf("%d",&n);
  getchar();
  if(n==1)
  {
	t=1;
	while(t==1)
	{
		del = Login(use);
		t=1;
		if(!del)
		{
		 printf("�Ƿ������\n");
		 printf("1.����  2.�˳�");
		 scanf("%d",&i);
		 getchar();
		 printf("\n");
		 if(i!=1)
		 {
		  printf("\n");
		  t=0;
		 }
		}
		else
		{
		 t=2;
		}
	}
  }
  if(n==2)
  {
	t=1;
	while(t==1)
	{
		del = Register(use);
		t=1;
		if(!del)
		{
		 printf("�Ƿ������\n");
		 printf("1.����  2.�˳�");
		 scanf("%d",&i);
		 getchar();
		 printf("\n");
		 if(i!=1)
		 {
		  printf("\n");
		  t=0;
		 }
		}
		else
		{
		 printf("\n");
		 t=0;
		}
	}
  }
  if(n==3)
  {
	   printf("ȷ���˳�?\n");
       printf("1.��  2.��");
	   scanf("%d",&i);
	   getchar();
	   if(i==1)
	   {
		   printf("��Ϸ���˳�\n");
		   exit(0);
	   }
	   if(i!=1)
	   {
	    printf("\n");
	   }
  }
  if(n!=1&&n!=2&&n!=3)
  {
   printf("\n");
  }
 }
}