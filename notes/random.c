#include <stdio.h>

int main(int arc, char* argv[]) {
  int *p = (int *) 0x12345678;
  unsigned char *cp = (unsigned char *) &p;

  int i;
  for (i = 0; i < sizeof(p); i++)
    printf("%d: %.2x\n", i, cp[i]);

  return 0;
}




/*

 - running, ready, bloocked, suspended
 - scheduling policy:
   - time silcing sceduling policy
   - fixed priority preemptive scheduling


ListNode* deleteDuplicates(ListNode* head) {
    if(head == NULL || head->next == NULL) return head;

    ListNode* curr = head;
    ListNode* prev = NULL;
    while(curr != NULL && curr->next != NULL) {
        if(curr->val == curr->next->val) {
            while(curr->next != NULL && curr->val == curr->next->val) {
                curr = curr->next;
            }
            if(prev != NULL) {
                prev->next = curr->next;
                curr = curr->next;
            }else {
                head = curr->next;
                curr = curr->next;
            }
        }else {
            prev = curr;
            curr = curr->next;
        }
    }
    return head;
}

binary search
#include <stdio.h>
int iterativeBinarySearch(int array[], int start_index, int end_index, int element){
   while (start_index <= end_index){
      int middle = start_index + (end_index- start_index )/2;
      if (array[middle] == element)
         return middle;
      if (array[middle] < element)
         start_index = middle + 1;
      else
         end_index = middle - 1;
   }
   return -1;
}

struct node *newNode;
newNode = malloc(sizeof(struct node));
newNode->data = 4;

struct node *temp = head;

for(int i=2; i < position; i++) {
  if(temp->next != NULL) {
    temp = temp->next;
  }
}
newNode->next = temp->next;
temp->next = newNode;

for(int i=2; i< position; i++) {
  if(temp->next!=NULL) {
    temp = temp->next;
  }
}

temp->next = temp->next->next;

int addInt(int n, int m)
{
  return n+m;
}

int (*functionPtr)(int, int);
functionPtr = &addInt;
int sum = (*functionPtr)(2, 3);

int add2to3(int (*functionPtr)(int, int)) {
    return (*functionPtr)(2, 3);
}

#include <iostream>
 
struct S
{
    // will usually occupy 2 bytes:
    // 3 bits: value of b1
    // 2 bits: unused
    // 6 bits: value of b2
    // 2 bits: value of b3
    // 3 bits: unused
    unsigned char b1 : 3, : 2, b2 : 6, b3 : 2;
};
 
int main()
{
    std::cout << sizeof(S) << '\n'; // usually prints 2
}
Possible output:

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 8
#define MIN(a,b) ((a>b)?b:a)
#define MY_REGISTER (*(volatile unsigned char*)0x1234)

int stack[8];
int top = -1;

void push(int data)
{
  if(top!=MAXSIZE)
  {
    top= top+1;
    stack[top]=data;
  }else{
    printf("Could not insert data, Stack is full.\n");
  }
}
int pop()
{
  int data;
  if(top != -1)
  {
    data = stack[top];
    top=top-1;
    return data;
  }else{
    printf("Could not retrieve data, Stack is empty.\n");
    return 0;
  }

}

int countones(int num)
{
  int counter=0;
  while(num>0)
  {
   if((num&1)==1)
   {
    counter =counter+1;
   }
    num = num>>1;
  }
  return counter;
}

#define sizeofqueue 8
int queue[sizeofqueue];
int rear = -1;
int front = -1;

void enqueue(int item)
{
  rear = (rear+1)%sizeofqueue;
  queue[rear]=item;
}

int dequeue()
{
  front = (front+1)%sizeofqueue;
  return queue[front];
}

// hash table
typedef struct
{
  int key;
  int count;
}data;

data* array;
int hashcode(int key)
{
  return (key%10);
}
void insert(int value)
{
  int index = hashcode(value);
  if(array[index].count==0)
  {
    array[index].key = value;
    array[index].count= 1;
  }else
  {
    array[index].count+=1;
  }
}

void removehash(int value)
{
  int index = hashcode(value);
  if(array[index].count==0)
  {
    printf("\n This key does not exist \n");
  }else
  {
    array[index].key = 0;
    array[index].count= 0;
  }

}

//linked list
typedef struct node
{
  int data;
  int index;
  struct node* next;
}node;

node* head =NULL;
node* current =NULL;

void insertFirst(int index, int data)
{
  node one;
  node* link =&one;
  link-> index = index;
  link-> data = data;
  link-> next = head;
  head= link;
}

//binary search
struct nodeone
{
  int value;
  struct nodeone *left, *right;
};

struct nodeone* inserttree(struct nodeone* node, int value)
{
  if(node == NULL)
  {

    struct nodeone* temp =  (struct nodeone*)malloc(sizeof(struct nodeone));
    //struct nodeone* temp = &space;

    temp->value = value;
    temp->left = temp-> right = NULL;
    return temp;
  }
  if(value< node->value)
  {
    node->left = inserttree(node->left, value);
  }else if(value>node->value)
  {
    node->right= inserttree(node->right, value);
  }

  return node;
}
// A utility function to do inorder traversal of BST
void inorder(struct nodeone* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d \n", root->value);
        inorder(root->right);
    }
}
// work in progress
struct nodeone* invertTree(struct nodeone* root){
    if(root!=NULL){
        invertTree(root->left);
        struct nodeone* temp = root->left;
        root->right = temp;
        root->left = root->right;
        invertTree(root->right);
    }
}



int main()
{
  struct nodeone* root = NULL;
  root = inserttree(root,50);
  inserttree(root, 30);
  inserttree(root, 20);
  inserttree(root, 40);
  inserttree(root, 70);
  inserttree(root, 60);
  inserttree(root, 80);
  inorder(root);
  invertTree(root);
  insertFirst(1,10);
  insertFirst(2,12);
  // array = (data*)malloc(10*sizeof(data));
  data arraya[10];
  // array =&arraya;
  array = arraya;
  for (int i = 0; i < 10; i++)
  {
		array[i].key = 0;
		array[i].count = 0;
	}
  insert(8);
  insert(1);
  insert(8);
  for (int i = 0; i < 10; i++)
  {
		if (array[i].count == 0)
    {
			printf("\n Array[%d] has no elements \n",i);
		}
		else
    {
			printf("\n array[%d] has elements -:\n key(%d) and value(%d) \t", i, array[i].key, array[i].count);
		}
	}

  push(1);
  push(2);
  push(3);
  enqueue(1);
  enqueue(2);
  enqueue(1);
  enqueue(2);

  printf("ddequeue returns  %d\n",dequeue());
  printf("ddequeue returns  %d\n",dequeue());
  printf("ddequeue returns  %d\n",dequeue());
  printf("pop() returns %d\n",pop());
  printf("pop() returns %d\n",pop());
  printf(" min %d\n", MIN(3,2));
  printf(" counter ones, there are %d\n", countones(10));
 
  int* pointer [10];
  return 0;
}

#include<stdio.h>

enum DAY
{
	Saturday,
	Sunday
};

// typedef can create a neww type naame
// typedef int myint;
// then myint is just a synonym for int
typedef int* intptr;

typedef enum color {blue,white} mycolor;
// mycolor one = blue;
// enum color = white;
// or
// enum color {blue, white} mycolor;
// typedef enum color mycolor;

// typedef enum {blue, white} mycolor;
// mycolor one = white;

// enum color {blue, white};
// enum color one = blue;
// ======================================
// struct, a stucture allows you to wrap one or more variables that may be in different datta types into one
// struct person
// {
// 	char first[32];
// 	char last[32];
// 	int age;
// } instance_1, instance_2, instance_n;

// struct example2
// {
//     int isMemoryAllocated : 1;
//     int isObjectAllocated : 1;
// };
// The above declaration tells the compiler that only 1 bit each from the two variables would be used. 
// After seeing this, the compiler reduces the memory size of the structure.

typedef struct
{
	char first[32];
	char last[32];
	int age;
} student;
// student a;
// student b;
// to access a structure member, use operate '.'
// stduent a;
// a.first = "jessica";

typedef struct
{
	student teacher[0];
	student goodones[40];
}course;
// course CMPEN472;
// CMPEN472.studdeents[0].first="Jack";

// advantages of srtuctures
// - it allows assignment statements between structure variables. 
// 		struct_iinstance1 = struct_instance2
// - passing a structure as a parameter to a functiion
void displaystudent(student info)
{
	printf(" %s %s: %d\n", info.first, info.last, info.age);
}

char* strcpy(char* destination,const char* source)
{
	char* ptr = destination;
	while(*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination='\0';
	return ptr;
}

// union, a union is a type of structure that can be used where the amount of memory used is a key factor
// similarly to the structure the union can contain different tyoes oof data yupes.
// each time a new variable in initiialized from the union it overwrites the previous and usees that memory location

union person
{
	char name;
	int age;
	double height;
} newperson;
// or person new Person;

int main()
{
	intptr p1,p2;
	student chen;
	course soc109;
	course* pointer;
	pointer = &soc109;
	pointer->teacher[0].age=20;
	//*pointer.teacher[0].age =20;

	//person newPerson;
	newperson.age=20;
	newperson.height = 6.2;
	// once the height vaiable is initialized 
	// the variaable age is overwritten and no longer exists

	// assiggning strings to an array of char
	// char s[100] = "abcd"; work
	// char s[100]; declare
	// s = "abcd"; initalize doesnt work
	// use strcpy in string.h, because s is an array not a free point
	strcpy(chen.first,"ping");	
	strcpy(chen.last,"ping");	
	chen.age = 21;
	displaystudent(chen);
	enum DAY freeDay = Sunday;
	return 0;
}

// Insert a node after a node
void insertAfter(struct Node* prev_node, int new_data) {
  if (prev_node == NULL) {
  printf("the given previous node cannot be NULL");
  return;
  }

  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = prev_node->next;
  prev_node->next = new_node;
}

#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}

void reversestr(char* str)
{
  int count = 0;
  int temp;
  while(*str !='\0')
  {
    count++;
    str++;
  }
  str = str- count;
  printf("length of str is %d\n", count);
  for(int i =0; i <count/2;++i)
  {
    printf("char is %c\n", str[i]);
    temp = str[i];
    str[i] = str[count-i-1];
    str[count-1-i] = temp;
  }
}

int roundnum(float num) {
  if(num>0){
    num = num +0.5;
  }else{
    num = num-0.5;
  }
    return num;
}

int cal(int num){
  int digits =0;
  while(num !=0){
    digits ++;
    num = num /10;
  }
  return digits;
}

int cal2(int num){
  int result =0;
  for(int i=0;i<32; ++i){
    result +=((num>>i)&1);
  }
  return result;
}
/*
UInt64 ConvertEndian(UInt64 big_endian_num)
{
  UInt64 small_endian_num = 0
  for(int i=7;i<=0;--i){
    char b = (big_endian_num >> (56 -i*8)) & 0xFF;
    small_endian_num = small_endian_num << 8;
    small_endian_num += b;
  }
  return small_endian_num;
}
*/

- find resource to solve problems
- reach out to people and ask queestions
- constructive feeddback

why pround:
None of us in the capsstone were familiar with UWB technology.
We were able to demenstrate the final product in a relatively short amount of time

situation:
The school parternered us up with a horn company. we had four people in the team
we need to come up with a system using the horn that is provided by the company to help vehicales in industrial and construction spaces to avoid collisions, especilly in blind corners and isles.
we thought about using bluetooth, wifi, and laser sensor. At the end, we decided to use Ultra Width Band technologgy.

action:
We did a lot of research online on UWB and thee microcontroller on the horn itself. And we purchased an existing UWB moddule from a vendor, as well as a transceiver, so we could have the option of building everything from scratch. I tested different firmwares and achieved point to point distance sensoring and point to point messsaging using those UWB modules

result:
in the end, we have a scaleable location tracking system with 20 meter in range and 60 centermeter precision that could interact with the horn that the company provided and visual indications

mistake:
-When purchaing the module, I didn't take a close look at the spec sheet.
the modules were small than expected, so I spend a lot of time soldering those modules
-poor time management, we weree going to make an graphic user interface for this, however, at the end, we ran out of time, so we had to get rid of that idea and put more time into the system itself.

# questions for them
- what is your daily work flow
- do u guys do activities outside of work inn a team
- if i join the team, what will be my responsibility
- is there any tranning process for this position



int reverseBit(int num){
  int result;
  int size = sizeof(num)*8;
  for(int i =0;i>size; i++){
    if(num&(1<<i)){
      result |= 1<<(size-i-1);
    }
  }
  return result;
}
void memcpy(void* destination, void* source, size_t n)
{
  char* tempsrc = (char*) source;
  char* tempdest = (char*) destination;

  for(int i =0; i<n;++i){
     tempdest[i] = tempsrc[i];
  }
}
int strlen(char* str){
  int count = 0;
  int temp;
  while(*str !='\0')
  {
   count++;
   str++;
  }
  str = str- count;
  return count;
}
void findrepeat(char*s)
{
  int hash[256]={0};
  for(int i =0; i < strlen(s); ++i)
  {
    if(hash[s[i]%256]==0)
    {
      hash[s[i]%256]++;
    }else
    {
      printf("%i\n",hash[s[i]%256]);
      printf("%c\n",s[i]);
    }
  }
}

void checkendian(){
   unsigned int i = 1;
   char *c = (char*)&i;
   printf("%p\n",c);
   printf("%p\n", (char*)&i);
   if (*c)
       printf("Little endian");
   else
       printf("Big endian");

}

int findpattern(char* s1, char* s2){
  int size1=0;
  int size2=0;
  int result =0;
  while(*s1!='\0'){
    s1++;
    size1++;
  }
  s1 =s1-size1;
  while(*s2!='\0'){
    s2++;
    size2++;
  }
  s2 =s2-size2;
  for(int i =0;i<size1-size2+1;++i){
    char* temp =s1;
    int count =0;
    while((*temp == *(s2+count))&& (count<size2)){
      temp++;
      count++;
    }
    if(count == size2){
      result++;
    }
    s1++;
  }
  return result;
}

int main(int argc, char **argv){

  for (int i = 0; i != argc; i++) {
    printf("Argument %d: %s\n", i, argv[i]);
  }
  char str1[] = "this is Chen Shen";
  char str2[] = "hen";
  printf("%d\n",findpattern(str1, str2));
}

/*
two formats to store multibyte data types
the right most byte data type called least significiant byte
the left most byte data type called most significiant byte

big endian
the most significant byte is stored first
small endian
the least significant byte stored first
int x = 0x76543210;
char *c = (char*) &x;

Big endian format:
------------------
Byte address  | 0x01 | 0x02 | 0x03 | 0x04 | 
              +++++++++++++++++++++++++++++
Byte content  | 0x76 | 0x54 | 0x32 | 0x10 |
			 
Little endian format:
---------------------
Byte address  | 0x01 | 0x02 | 0x03 | 0x04 | 
              +++++++++++++++++++++++++++++
Byte content  | 0x10 | 0x32 | 0x54 | 0x76 |

i =1;
a = ++i;
this is pre increment
becasue it increments i's value by 1 before the operation
a =2, i =2

a = i++;
this is post increment
because it inrements i's value by 1 after the operation is over
a =1, i =2

static variables ahve a property of perserving theirvalue after they are out of scope

memory in C
- text segment, instructions
- initialized data segment, 
  global and static variabales that are initialized
- uninitialized data segment bss, 
  contains all globaal and static vaariables that are initialized to zero or do not have explicit initialization
- stack
  automatic variables 
  return address, machine registers
- heap
  dynamic allocation

int* ptr;
ptr = (int*) 0x67a9;
*ptr = 0xaa55;
*(int* const)(0x67a9) = 0xaa55;
int n = sizeof(array)/sizeof(array[0])
char greetings[6] = {'H','e','l','l','o','\0'};
char greeting[] = "Hello";
Strings are one-dimensional array of characters terminated by a null character '\0'
const char *str1 = "Chen";
A[i][j] = *(A[i] + j) = *(*(A+i)+j)
1 D arraay A[i], *(A+i)
int a;
scanf("%d", &a);
*/

*/

extern keyword, tells the compiler to look for it in other translation units
======
* how to program in C
- handle, pointer to opaqe data structure
- func, function pointer or function used as functiom pointer
- i, j, k, count, length, found, next, previous... 

======
find ./ -iname "temp.txt"
grep -r -i "abc" . | grep -i "def" 

struct node {
   int data;
   struct node *next;
};
struct node *head = NULL;
struct node *current = NULL;

// display the list
void printList(){
   struct node *p = head;
   printf("\n[");

   //start from the beginning
   while(p != NULL) {
      printf(" %d ",p->data);
      p = p->next;
   }
   printf("]");
}

//insertion at the beginning
void insertatbegin(int data){

   //create a link
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;

   // point it to old first node
   lk->next = head;

   //point first to new first node
   head = lk;
}
void insertatend(int data){

   //create a link
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;
   struct node *linkedlist = head;

   // point it to old first node
   while(linkedlist->next != NULL)
      linkedlist = linkedlist->next;

   //point first to new first node
   linkedlist->next = lk;
}
void insertafternode(struct node *list, int data){
   struct node *lk = (struct node*) malloc(sizeof(struct node));
   lk->data = data;
   lk->next = list->next;
   list->next = lk;
}
void deleteatbegin(){
   head = head->next;
}
void deleteatend(){
   struct node *linkedlist = head;
   while (linkedlist->next->next != NULL)
      linkedlist = linkedlist->next;
   linkedlist->next = NULL;
}
void deletenode(int key){
   struct node *temp = head, *prev;
   if (temp != NULL && temp->data == key) {
      head = temp->next;
      return;
   }

   // Find the key to be deleted
   while (temp != NULL && temp->data != key) {
      prev = temp;
      temp = temp->next;
   }

   // If the key is not present
   if (temp == NULL) return;

   // Remove the node
   prev->next = temp->next;
}
int searchlist(int key){
   struct node *temp = head;
   while(temp != NULL) {
      if (temp->data == key) {
         return 1;
      }
      temp=temp->next;
   }
   return 0;
}