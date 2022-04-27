#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define Red 0
#define Black 1

typedef struct node
{
    char*data;
    int color;
    struct node*leftchild;
    struct node*rightchild;
    struct node*parent;

} node;


typedef struct RedBlackTree
{
    node*Root;
    node*NIL;
} RedBlackTree;

RedBlackTree*newRedBlacktree()
{

    RedBlackTree*t=malloc(sizeof(RedBlackTree));
    node*nil=malloc(sizeof(node));
    nil->color=Black;
    nil->leftchild=NULL;
    nil->rightchild=NULL;
    nil->parent=NULL;
    nil->data=0;
    t->NIL=nil;
    t->Root=t->NIL;
    return t;

}
node*newnode(char *data)
{
    node*p;
    p=malloc(sizeof(node));
    p->data=malloc(sizeof(char)*20);
    strcpy(p->data,data);
    p->leftchild=NULL;
    p->rightchild=NULL;
    p->parent=NULL;
    p->color=Red;
    return p;
}

void left_rotate(RedBlackTree*t, node *x)
{

    node *y = x->rightchild;
    x->rightchild= y->leftchild;
    if(y->leftchild!= t->NIL)
    {
        y->leftchild->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL)
    {
        t->Root = y;
    }
    else if(x == x->parent->leftchild)
    {
        x->parent->leftchild = y;
    }
    else
    {
        x->parent->rightchild = y;
    }
    y->leftchild = x;
    x->parent = y;
}

void right_rotate(RedBlackTree *t, node*x)
{
    node *y = x->leftchild;
    x->leftchild = y->rightchild;
    if(y->rightchild != t->NIL)
    {
        y->rightchild->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->NIL)
    {
        t->Root = y;
    }
    else if(x == x->parent->rightchild)
    {
        x->parent->rightchild = y;
    }
    else
    {
        x->parent->leftchild = y;
    }
    y->rightchild = x;
    x->parent = y;
}

void fix_insert(RedBlackTree*t,node*z)
{


    while( (z->parent->color==Red) && (z!=t->Root) && (z->color != Black) )
    {
        node*parent_pt=z->parent;
        node*grand_parent_pt= z->parent->parent;
        node*uncle_pt;

        if(parent_pt==grand_parent_pt->leftchild)
        {

            uncle_pt=grand_parent_pt->rightchild;


            if(uncle_pt->color==Red && uncle_pt !=t->NIL)
            {
                parent_pt->color=Black;
                uncle_pt->color=Black;
                grand_parent_pt->color=Red;
                z=grand_parent_pt;
            }
            else
            {
                //left Right
                if(z==parent_pt->rightchild)
                {
                    left_rotate(t,z->parent);
                    z=parent_pt;
                    parent_pt=z->parent;


                }
                //left left

                z->parent->color=Black;
                grand_parent_pt->color=Red;
                right_rotate(t,grand_parent_pt);
                z=parent_pt;



            }

        }
        else
        {
            uncle_pt=grand_parent_pt->leftchild;


            if(uncle_pt->color==Red)
            {
                parent_pt->color=Black;
                uncle_pt->color=Black;
                grand_parent_pt->color=Red;
                z=grand_parent_pt;
            }
            else
            {
                //right left
                if(z==parent_pt->leftchild)
                {

                    right_rotate(t,z->parent);
                    z=parent_pt;
                    parent_pt=z->parent;

                }
                //right right
                z->parent->color=Black;
                grand_parent_pt->color=Red;
                left_rotate(t,grand_parent_pt);
                z=parent_pt;

            }


        }


    }
    t->Root->color=Black;
}
int search(RedBlackTree*t,char *data)
{

    while(t->Root != t->NIL)
    {
        if(strcmp(t->Root->data,data)==0)
        {
            return 1;
        }

        else if(strcmp(data,t->Root->data)<0)
        {
            t->Root=t->Root->leftchild;
        }
        else

            t->Root=t->Root->rightchild;
    }

    return 0;
}

void insert(RedBlackTree *t,node *z)
{

    node* iterator = t->NIL;
    node* temp = t->Root;


    //find place to insert
    while(temp != t->NIL)
    {
        iterator = temp;

        if((strcmp(z->data,temp->data))<0)
        {
            temp = temp->leftchild;
        }
        else
        {
            temp = temp->rightchild;
        }
    }
    z->parent = iterator;

    //insert node
    if(iterator == t->NIL)
    {
        t->Root = z;
    }
    else if((strcmp(z->data,iterator->data))<0)
    {
        iterator->leftchild = z;
    }
    else
    {
        iterator->rightchild = z;

    }
    z->rightchild = t->NIL;
    z->leftchild = t->NIL;


    fix_insert(t, z);

}
int max(int x,int y)
{
    if(x>y)
        return x;
    else
        return y;

}
int height(RedBlackTree*t,node*root)
{
    if(root==NULL || root==t->NIL)
        return -1;
    else
        return 1+ max(height(t,root->leftchild),height(t,root->rightchild));

}
int size(RedBlackTree*t,node*root)
{
    if(root==NULL || root==t->NIL)
        return 0;
    else
        return (1+size(t,root->leftchild)+size(t,root->rightchild));
}
void inorder(RedBlackTree *t,node *n)
{
    if(n != t->NIL )
    {
        inorder(t, n->leftchild);
        if(n->color==0)
        printf("Color = Red\n");
        else
        printf("Color = Black\n");
        printf("inorder =%s\n",n->data);
        inorder(t, n->rightchild);

    }
}
RedBlackTree* fillfromfile(char*filename)
{
    RedBlackTree*t=newRedBlacktree();

    char*p=(char*)malloc(sizeof(char)*20);
    FILE*f;
    f=fopen(filename,"r");
    int count=0;
    while(!feof(f))
    {
        count++;
        fscanf(f,"%s",p);
        node*x;
        x=newnode(p);
        insert(t,x);
    }
    fclose(f);
    printf("File Size = %d\n",count);
    return t;
}
void readline(RedBlackTree*t)
{

    char *p=(char*)malloc(sizeof(char)*20);
    char*z;
    printf("Please Enter Word ");
    gets(p);
    z=strtok(p," ");

    node*temp;
    while(z!=NULL)
    {
        temp=t->Root;
        int y=search(t,z);
        t->Root=temp;
        if(y==1)
        {
            printf("ERROR: Word already in the dictionary!\n");
        }
        else
        {
            printf("Word Inseretd\n\n");
            node*temp2=newnode(z);
            insert(t,temp2);
            inorder(t,t->Root);

        }
        z=strtok(NULL," ");
    }


}

int main()
{
    RedBlackTree *t=newRedBlacktree() ;
    t=fillfromfile("dictionary.txt");
    int h=height(t,t->Root);
    printf("Height=%d\n",h);
    int s=size(t,t->Root);
    printf("Tree Size = %d\n",s);
    readline(t);
    int h2=height(t,t->Root);
    printf("New Height = %d\n",h2);
    int s2=size(t,t->Root);
    printf("New Tree Size = %d\n",s2);



    return 0;
}
