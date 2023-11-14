#define OK 1
#define ERROR 0

#ifndef _stack_H

typedef struct StackNode{
    char data;
    struct StackNode *next;
} StackNode, *LinkStack;

void InitStack(LinkStack &s);      //初始化链栈 
bool IsEmptyStack(LinkStack s);    //判断链栈是否为空
void Push(LinkStack &s, char e);     //入栈
bool Pop(LinkStack &s,char &e);      //出栈
void PrintStack(LinkStack s);          //打印链栈
void PrintStr(char str[]);           //打印表达式
bool infix_to_postfix(char infix[], char postfix[]);   //将中缀表达式转化为后缀表达式
int prior(char c);               //返回操作符的优先级
int computepost(char postfix[]);       //计算后缀表达式的值
bool IsOperator(char c);               //判断字符是否是操作符

#endif // _stack_H

