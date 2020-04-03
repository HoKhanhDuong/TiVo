#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "liblkdoi.h"
int readfile(node **head, node **tail, int soluong, char filename[])
{
  FILE *f;
  if((f=fopen(filename,"r"))==NULL){
    printf("can't open file %s\n",filename);
    exit(0);
  }
  element a;
  char x[4][20];
  while(!feof(f)){
    fscanf(f,"%s %s %s %s %s",a.nick,x[0],x[1],x[2],x[3]);
    if(feof(f)) break;
    if((a.mau=atoi(x[0]))<=0){
      printf("Du lieu %s trong team %s sai\n",a.nick,filename);
      return -1;
    }
    if((a.tan=atoi(x[1]))<=0){
      printf("Du lieu %s trong team %s sai\n",a.nick,filename);
      return -1;
    }
    if((a.nhanh=atoi(x[2]))<=0){
      printf("Du lieu %s trong team %s sai\n",a.nick,filename);
      return -1;
    }
    if((a.thu=atoi(x[3]))<=0){
      printf("Du lieu %s trong team %s sai\n",a.nick,filename);
      return -1;
    }
    a.diem=0;
    push(head,tail,&a);
    soluong++;
  }
  fclose(f);
 return soluong;
}
void dau(node *h1, node *h2, int turn)
{
  printf("%-10s(HP:%-5d) Tan cong %-10s(HP:%-5d)",h1->vo.nick,h1->vo.mau,h2->vo.nick,h2->vo.mau);
  h2->vo.mau-= h1->vo.tan - h2->vo.thu;
  h1->vo.diem++;
  if(h2->vo.mau<=0){
    if(turn ==0) h1->vo.diem+=2;
    printf("  %s bi ha\n",h2->vo.nick);
    return;
  }
  else printf("  mat %d mau\n",h1->vo.tan - h2->vo.thu);
  dau(h2,h1,turn+1);
}
int tran=1;
void modau(node *h1, node *h2)
{
  printf("Tran %d :\n",tran);
  printf("%-15s %-4s %-15s\n","MP1","VS","MP2");
  printf("%-20s %-15s\n",h1->vo.nick,h2->vo.nick);
  printf("%-20d %-15d\n",h1->vo.mau,h2->vo.mau);
  printf("%-20d %-15d\n",h1->vo.tan,h2->vo.tan);
  printf("%-20d %-15d\n",h1->vo.nhanh,h2->vo.nhanh);
  printf("%-20d %-15d\n",h1->vo.thu,h2->vo.thu);
  tran++;
}
int thidau(node *h1, node *t, node *h2)
{
  if(h1==t->next){
    printf("KQ: Team hai quan thang \n");
    return 2;
  }
  if(h2==NULL){
    printf("KQ: Team Luffy thang \n");
    return 1;
  }
  modau(h1,h2);
  int m;
  if(h1->vo.nhanh >= h2->vo.nhanh){
    dau(h1,h2,0);
    if(h2->vo.mau<=0) thidau(h1,t,h2->next);
    else thidau(h1->next,t,h2);
  }
  else {
    dau(h2,h1,0);
    if(h1->vo.mau<=0) thidau(h1->next,t,h2);
    else thidau(h1,t,h2->next);
  }
}
void swap(node **a, node **b)
{
  element c=(*a)->vo;
  (*a)->vo=(*b)->vo;
  (*b)->vo=c;
}
void xephang(node **head, node **tail)
{
  if(*head==*tail) return;
  node *cur=*tail;
  while(cur->prev!=NULL){
    if(cur->vo.diem > cur->prev->vo.diem) swap(&cur,&cur->prev);
    cur=cur->prev;
  }
  xephang(&(*head)->next,tail);
}
void xem(node *head, int a)
{
  printf("%-5s%-20s %s\n","STT","Biet Danh","Diem");
  node *cur=head;
  while(cur!=NULL){
    printf("%-4d %-20s %d\n",a,cur->vo.nick,cur->vo.diem);
    cur=cur->next;
    a++;
  }
  
}
int main()
{
  node *head1=NULL;
  node *tail1=NULL;
  node *tail2=NULL;
  int sl1=0,sl2=0;
  int dk;
  char *name;
  do {
    printf("\n~~~~~~~~~MENU~~~~~~~~\n");
    printf(" 1.Doc du lieu\n 2.Thi dau\n 3.Xep hang vo sy\n 4.exit\n");
    scanf("%d",&dk);
    switch(dk)
      {
      case 1:
	name=strdup("team1.txt");
	if((sl1=readfile(&head1,&tail1,sl1,name))==-1) break;
	name=strdup("team2.txt");
	tail2=tail1;
	if((sl2=readfile(&tail1,&tail2,sl2,name))==-1) break;
	if(sl1!=sl2) {
	  printf("Luc luong khong can bang !! moi sua lai du lieu \n");
	}
	free(name);
	printf("Team Luffy: \n");
	printf("%-4s %-12s %-10s %-10s %-15s %s\n","STT","Biet Danh","mau","Tan cong","Nhanh nhen","Phong Thu");
	Display(head1,tail1,0);
	printf("\nTeam hai quan: \n");
	Display(tail1->next,tail2,0);
	break;
      
      case 2: thidau(head1,tail1,tail1->next);
	break;
      case 3:
	xephang(&head1,&tail2);
	xem(head1,0);
	break;
      }
  }while(dk!=4);
}
