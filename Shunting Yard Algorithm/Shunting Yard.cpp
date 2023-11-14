#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int main() {
    LinkStack s;
    char infix[30], postfix[30];
    printf("C12214060余江睿\n");
    while (1) {
        scanf("%s", infix);
        if (infix[0] == '#')
            break;
        infix_to_postfix(infix, postfix);
        PrintStr(postfix);
        int result = computepost(postfix);
        printf("result: %d\n", result);
    }
}

//将中缀表达式转化为后缀表达式
bool infix_to_postfix(char infix[], char postfix[]) {
    LinkStack s;
    InitStack(s);
    int i = 0, j = 0;
    for (; infix[i] != '#'; i++)
    {
        if (!IsOperator(infix[i]))         //数字直接进入后缀表达式
            postfix[j++] = infix[i];
        else if (infix[i] == '(')           //遇到左括号入栈
            Push(s, infix[i]);
        else if (infix[i] == ')') {          //遇到右括号不断出栈直至遇到左括号，按出栈顺序进入后缀表达式，左右括号不进入
            char s_top;
            Pop(s, s_top);
            while (s_top != '(') {
                postfix[j++] = s_top;
                Pop(s, s_top);
            }
        }
        else {                  //遇到运算符，与栈顶符号比较，若栈顶符号运算优先级先于该符号，则将栈顶符号进入后缀表达式
            char s_top;                //等到栈顶符号运算优先级低于该符号或栈空，将该符号入栈
            if (IsEmptyStack(s))
                Push(s, infix[i]);
            else {
                while (Pop(s, s_top) && prior(s_top) >= prior(infix[i])) {
                    postfix[j++] = s_top;
                }
                Push(s, s_top);
                Push(s, infix[i]);
            }
        }
    }
    while (!IsEmptyStack(s)) {             //将栈内剩余符号进入后缀表达式
        char s_top;
        Pop(s, s_top);
        postfix[j++] = s_top;
    }
    postfix[j] = '\0';
    return true;
}
//计算后缀表达式的值
int computepost(char postfix[]) {
    // int num[100];             //用来保存数字
    // int j = 0;
    // for (int i = 0; postfix[i] != '\0';i++){           
    //     if(!IsOperator(postfix[i])){          //数字进入数组
    //         num[j++] = postfix[i]-'0';
    //     }
    //     else{                  //遇到运算符，将运算符前输入前的两个数字取出运算
    //         int result;                   //注意运算顺序是前一个数字+-*/后一个数字
    //         switch (postfix[i])
    //         {
    //         case '+':
    //             result = num[j-2] + num[j-1];
    //             j-=2;
    //             break;
    //         case '-':
    //             result = num[j-2] - num[j-1];
    //             j-=2;
    //             break;   
    //         case '*':
    //             result = num[j-2] * num[j-1];
    //             j-=2;
    //             break;
    //         case '/':
    //             result = num[j-2] / num[j-1];
    //             j-=2;
    //             break;
    //         }
    //         num[j++] = result;
    //     }
    // }
    // int final_result;
    // final_result = num[j-1];
    // return final_result;
    LinkStack s;
    InitStack(s);
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (!IsOperator(postfix[i]))
            Push(s, postfix[i] - '0');
        else {
            char num1, num2;
            Pop(s, num2);
            Pop(s, num1);
            switch (postfix[i]) {
            case '+':
                Push(s, num2 + num1);
                break;
            case '-':
                Push(s, num2 - num1);
                break;
            case '*':
                Push(s, num2 * num1);
                break;
            case '/':
                Push(s, num2 / num1);
                break;
            }
        }
    }
    char result;
    Pop(s, result);
    return (int)result;
}

void InitStack(LinkStack& s) {
    s = NULL;
}

bool IsEmptyStack(LinkStack s) {
    if (s == NULL)
        return true;
    else
        return false;
}

void Push(LinkStack& s, char e) {
    StackNode* p;
    p = (StackNode*)malloc(sizeof(StackNode));
    if (!p) {
        printf("内存分配失败\n");
        return;
    }
    p->data = e;
    p->next = s;
    s = p;
}

bool Pop(LinkStack& s, char& e)
{
    StackNode* p;
    if (IsEmptyStack((s))) {
        return false;
    }
    p = s;
    e = s->data;
    s = s->next;
    free(p);
    return true;
}
//打印链栈
void PrintStack(LinkStack s) {
    if (IsEmptyStack(s)) {
        printf("链栈为空\n");
        return;
    }
    LinkStack temp = s;
    while (temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
//打印表达式
void PrintStr(char str[]) {
    ;
    for (int i = 0; str[i] != '\0'; i++)
        printf("%c", str[i]);
    printf("\n");
}
//返回操作数的优先级
int prior(char c) {
    if (c == '(' || c == ')')
        return 1;
    if (c == '*' || c == '/')
        return 3;
    if (c == '+' || c == '-')
        return 2;
    return 0;
}
//判断是否为操作数
bool IsOperator(char c) {
    if (c >= '0' && c <= '9')
        return false;
    else
        return true;
}