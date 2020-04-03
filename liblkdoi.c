#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "liblkdoi.h"
node *MakeNode(element *p)
{
  node *new = (node *)malloc(sizeof(node));
  new->vo = *p;
  return new;
}
void push(node **head, node **tail, element *p)
{
  node *new = MakeNode(p);
  if(*head==NULL) *head= *tail= new;
  else {
  (*tail)->next=new;
  new->prev=*tail;;
  *tail=new;
  }
}
void Delete(node **head, node **tail, int vt)
{
  node *cur = *head;
  if(vt==0) {
    *head =(*head)->next;
    (*head)->prev=NULL;
    free(cur);
    return;
  }
  while(vt>0){
    cur=cur->next;
    vt--;
    if(cur==NULL) break;
  }
  if(cur==NULL){
    printf("danh sach khong du du lieu");
    free(cur);
    return;
  }
  if(cur == *tail){
    *tail=(*tail)->prev;
    (*tail)->next=NULL;
    free(cur);
    return;
  }
  cur->prev->next=cur->next;
  cur->next->prev=cur->prev;
  free(cur);
}
void Inser(node **head, node **tail, element *p, int vt)
{
  node *new;
  if(vt==0) {
    new=MakeNode(p);
    new->next=*head;
    (*head)->prev=new;
    *head=new;
    return;
  }
  new=*head;
  while(vt>0){
    new=new->next;
    vt--;
    if(new==NULL) break;
  }
  if(new==NULL){
    printf("chuong trinh tu dong chen vao cuoi danh sach\n");
    push(head,tail,p);
    return;
  }
  node *cur =new;
  new=MakeNode(p);
  cur->prev->next=new;
  new->prev=cur->prev;
  new->next=cur;
  cur->prev=new;
}
void Display(node *head,node *tail, int dem)
{
  if(head!=tail->next){
  printf("%-4d %-12s %-10d %-10d %-15d %-5d\n",dem,head->vo.nick,head->vo.mau,head->vo.tan,head->vo.nhanh,head->vo.thu);
  Display(head->next,tail,dem+1);
  }
}
