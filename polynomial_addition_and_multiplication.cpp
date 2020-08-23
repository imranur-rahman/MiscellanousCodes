//Design data structures(linked list) for sorting polynomial
/*this program will ask you first node numbers,
then polynomial, for input.
print that two polynomial and merge them into one.
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<assert.h>
 
struct node
{
    int coefficint,exponent; //input coef and expo will be integer number
    struct node* next;
};
 
struct node* insertpoly(struct node* thead,int c,int e);
struct node* append(struct node* thead,int c,int e);
struct node* polyaddition(struct node* p1thead,struct node* p2thead);
void display(struct node* thead);
 
void display(struct node* thead)
{
    struct node* temp=thead;
    if(temp==NULL)
    {
        printf("\nEmpty..");
    }
    else
    {
        while(temp->next!=NULL)
        {
            printf(" %dx^%d +",temp->coefficint,temp->exponent);
            temp=temp->next;
        }
        printf(" %dx^%d ",temp->coefficint,temp->exponent);
    }
}
 
 
 
struct node* append(struct node* thead,int c,int e)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->coefficint=c;
    newnode->exponent=e;
    if(thead==NULL) // Corner Case to handle if the list is empty.
    {
        newnode->next=NULL;
        return newnode;
    }
    struct node* trav=thead;
    while(trav->next!=NULL) // Traversing to point to the last node
        trav=trav->next;
    trav->next=newnode;
    newnode->next=NULL;
    return thead;
}
 
struct node* insertpoly(struct node* thead,int c,int e)
{
    struct node* newnode=(struct node*)malloc(sizeof(struct node));
    newnode->coefficint=c;
    newnode->exponent=e;
    if(thead==NULL)             // for inserting the first node
    {
        newnode->next=NULL;
        return newnode;
    }
    struct node* prev,* curr;
    prev=curr=thead;
    while(curr!=NULL && curr->exponent>e)
    {
        prev=curr;
        curr=curr->next;
    }
    if(curr==thead)             // for inserting before the first node.
    {
        newnode->next=curr;
        return newnode;
    }
    else if(curr==NULL)         //for inserting after the last node.
    {
        prev->next=newnode;
        newnode->next=NULL;
    }
    else
    {
        newnode->next=curr;
        prev->next=newnode;
    }
    return thead;
}
 
struct node* polyaddition(struct node* p1thead,struct node* p2thead)
{
    struct node* ans=NULL;
    struct node* t1,* t2;
    t1=p1thead;
    t2=p2thead;
    while(t1!=NULL && t2!=NULL)
    {
        if(t1->exponent > t2->exponent)
        {
            ans=append(ans,t1->coefficint,t1->exponent);
            t1=t1->next;
        }
        else if(t1->exponent < t2->exponent)
        {
            ans=append(ans,t2->coefficint,t2->exponent);
            t2=t2->next;
        }
        else
        {
            ans=append(ans,(t1->coefficint)+(t2->coefficint),t1->exponent);
            t1=t1->next;
            t2=t2->next;
        }
    }
    while(t1!=NULL)             //coping the remaining terms of polynomial 1
    {
        ans=append(ans,t1->coefficint,t1->exponent);
        t1=t1->next;
    }
    while(t2!=NULL)             //coping the remaining terms of polynomial 2
    {
        ans=append(ans,t2->coefficint,t2->exponent);
        t2=t2->next;
    }
    return ans;
}
 
struct node* multiplyonce(struct node* p1thead, int coeff, int expo)
{
    struct node* ret = NULL;
    struct node* t1 = p1thead;
 
    while (t1 != NULL)
    {
        ret = append(ret, t1->coefficint * coeff, t1->exponent + expo);
        t1 = t1->next;
    }
 
    return ret;
}
 
struct node* polymultiply(struct node* p1thead, struct node* p2thead)
{
    struct node* ans=NULL;
    struct node* t1,* t2;
    t1=p1thead;
    t2=p2thead;
 
    while (t2 != NULL)
    {
        ans = polyaddition(ans, multiplyonce(t1, t2->coefficint, t2->exponent));
        t2 = t2->next;
    }
 
    return ans;
}
 
//the main function
void main()
{
    int a,b,n,i;  //integer a is coefficient, b is exponent, n is node number
    struct node* p1head,* p2head,* p3head, * p4head;  //here node is how many time expo and coef you want
    //p1head is 1sh poly after sorting
    //p1head is 2nd poly after sorting
    //after adding 1st and 2nd poly it will stored in p3head
    p1head=p2head=NULL;
    // Inputing the first polynomial
    printf("Enter the number of nodes for the first polynomial: ");  //this string ask you how many nodes you want for the fist polynomial
    scanf("%d",&n);  // take input from user how many nodes he want
    printf("\nGood job! Now you can enter the polynomial.");
    for(i=0; i<n; i++)
    {
        printf("\nInput coefficient and exponent: "); //ask user for coef and expo
        scanf("%d%d",&a,&b);  // input coef and expo from the user
        p1head=insertpoly(p1head,a,b);
    }
 
    // Inputing the second polynomial.
    printf("\n\nEnter the number of nodes for the second polynomial: "); //this string ask you how many nodes you want for the fist polynomial
    scanf("%d",&n); // take input from user how many nodes he want
    printf("\nGreat! Now you can enter the polynomial for the second one.");
    for(i=0; i<n; i++)
    {
        printf("\nInput coefficient and exponent: "); //ask user for coef and expo
        scanf("%d%d",&a,&b);  // input coef and expo from the user
        p2head=insertpoly(p2head,a,b);
    }
 
    //Performing Addition
    p3head=polyaddition(p1head,p2head);
    //Displaying the polynomial
    printf("\nThe first polynomial is: ");
    display(p1head);  //display the first polynomial
    printf("\nThe second polynomial is: ");
    display(p2head); //display the second polynomial
    printf("\n\nThe sum of the two polynomials is: ");
    display(p3head); //after adding two polynomial will be display here
 
    //Performing Multiplication
    p4head = polymultiply(p1head, p2head);
    printf("\n\nThe multiplication of the two polynomials is: ");
    display(p4head);
	  return 0;
}  //end of the program
