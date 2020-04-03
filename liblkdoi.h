#ifndef LINK
#define LINK

#include<stdio.h>
#include<stdlib.h>

typedef struct
{
  char nick[80];
  int mau;
  int tan;
  int nhanh;
  int thu;
  int diem;
}element;
typedef struct node
{
  element vo;
  struct node *next;
  struct node *prev;
}node;
node *MakeNode(element *p);
void push(node **head, node ** tail, element *p);
void Delete(node **head, node **tail, int vt);
void Inser(node **head, node **tail, element *p, int vt);
void Display(node *head,node *tail,int dem);

#endif	
