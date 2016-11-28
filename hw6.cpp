#include <stdio.h>
#include <stdlib.h> 
#include <malloc.h>
#include <string.h>

#define MAXLEN 100

typedef struct StackNode
{
char data;
struct StackNode *next;
}osNode;

typedef struct numStackNode
{
int num; 
struct numStackNode *next;
}nsNode;

typedef struct stackHead
{
int count;
osNode *top;
}sHead;

typedef struct numStackHead
{
int count;
nsNode *top;
}nsHead;

sHead createStack()
{
sHead sInit;
sInit.count=0;
sInit.top=NULL;
return sInit;
}

nsHead createNumStack()
{
nsHead nsInit;
nsInit.count=0;
nsInit.top=NULL;
return nsInit;
}

char process();
char inToPostFix(char formula[MAXLEN]);
int pushStack(sHead *stack, char data); 
int pushStack(nsHead *stack, int integerData);
int popStack(sHead *stack, char *dataOut);
int popStack(nsHead *stack, int *operand);
int stackTop(sHead stack, char *dataOut);
int emptyStack(sHead stack);
int priority(char token);
int fullStack(sHead stack);
int postFixEvaluate(char expr[MAXLEN]);
int calculate(int num1, char _operator, int num2); 
int destroyStack(sHead *stack);
int destroyStack(nsHead *stack);

int main(int argc, char *argv[])
{
char character=NULL;

printf("\nWelcome to Calculator Micro Application\n");
printf("Usage Example : Input 3*7 and Press [Enter]\n");
printf("Input Q or q to halt\n\n");
while(character!='q' && character!='Q')
{
character=process();
}
printf("Halting Application..\n\n");
return 0;
}

char process()
{
char formula[MAXLEN]={'\0',};
fflush(stdin);
gets(formula);
if(formula[0]=='Q')
return 'Q';
else if(formula[0]=='q')
return 'q';
inToPostFix(formula);
return NULL;
}

char inToPostFix(char formula[MAXLEN])
{
sHead stack=createStack();

char postFix[MAXLEN]={'\0',};
char token;
char topToken;
char tokenOut;
int formulaLen = strlen(formula);
int looper=0;
int index=0;

while(looper < formulaLen)
{
token = formula[looper];
if(token == '(')
pushStack(&stack,token);
else if(token == ')')
{
popStack(&stack,&token);
while(token!='(')
{
postFix[index]=token;
index++;
popStack(&stack,&token);
}
}
else if(token == '+' || token == '-' || token == '*' || token == '/')
{
stackTop(stack,&topToken);
while(!emptyStack(stack) && priority(token) <= priority(topToken))
{
popStack(&stack,&tokenOut);
postFix[index]=tokenOut;
index++;
stackTop(stack,&topToken);
}
pushStack(&stack,token);
}
else
{
postFix[index]=token;
index++;
}

looper = looper + 1;
}

while(!emptyStack(stack))
{
popStack(&stack,&token);
postFix[index]=token;
index++;
}

destroyStack(&stack);
printf("=%d\n",postFixEvaluate(postFix));
return NULL;
}

int pushStack(sHead *stack, char data)
{
osNode *newPtr=NULL;
int success;
if(!(newPtr = (osNode *)malloc(sizeof(osNode))))
success = 0;
else
{
newPtr->data = data;
newPtr->next = stack->top;
stack->top = newPtr;
stack->count = stack->count+1;
success = 1;
}
return success;
}

int popStack(sHead *stack, char *dataOut)
{
osNode *dltPtr=NULL;
int success;
if(stack->count == 0)
success = 0;
else
{
dltPtr = stack->top;
*dataOut = stack->top->data;
stack->top = stack->top->next;
stack->count = stack->count-1;
free(dltPtr);
success = 1;
}
return success;
}
int stackTop(sHead stack, char *dataOut)
{
int success;
if(stack.count == 0)
success=0;
else
{
*dataOut = stack.top->data;
success = 1;
}

return success;
}

int emptyStack(sHead stack)
{
int result;
if(stack.count != 0)
result = 0;
else
result = 1;
return result;
}

int priority(char token)
{
int order;
switch(token)
{
case '+':
order=1;
break;
case '-':
order=1;
break;
case '*':
order=2;
break;
case '/':
order=2;
break;
default :
order=0;
break;
}
return order;
}
int destroyStack(sHead *stack)
{
osNode *temp=NULL;
while(stack->top!=NULL)
{
temp = stack->top;
stack->top = stack->top->next;
free(temp);
}
stack->count = 0;
return 1;
}

int fullStack(sHead stack)
{
osNode *temp=NULL;
temp = (osNode *)malloc(sizeof(osNode));
if(temp!=NULL)
{
free(temp);
return 0;
}
return 1;
}
int postFixEvaluate(char expr[MAXLEN])
{
int exprSize = strlen(expr);
nsHead stack=createNumStack();
int index=0;
int num1;
int num2;
char _operator;
int value;
int result;
while(index < exprSize)
{
if(expr[index]!='+' && expr[index]!='-' && expr[index]!='*' && expr[index]!='/')
pushStack(&stack,(expr[index]-'0'));
else
{
popStack(&stack,&num2);
popStack(&stack,&num1);
_operator = expr[index];
value = calculate(num1,_operator,num2);
pushStack(&stack,value);
}
index = index +1;
}
popStack(&stack,&result);
destroyStack(&stack);
return result;
}
int pushStack(nsHead *stack, int IntegerData)
{
nsNode *newPtr=NULL;
int success;
if(!(newPtr = (nsNode *)malloc(sizeof(nsNode))))
success = 0;
else
{
newPtr->num = IntegerData;
newPtr->next = stack->top;
stack->top = newPtr;
stack->count = stack->count+1;
success=1;
}
return success;
}
int popStack(nsHead *stack, int *operand)
{
nsNode *dltPtr=NULL;
int success;
if(stack->count==0)
success=0;
else
{
dltPtr = stack->top;
*operand = stack->top->num;
stack->top = stack->top->next;
stack->count = stack->count-1;
free(dltPtr);
success = 1;
}
return success;
}
int calculate(int num1, char _operator, int num2)
{
int result=0;
switch(_operator)
{
case '+':
result = num1+num2;
break;
case '-':
result = num1-num2;
break;
case '*':
result = num1*num2;
break;
case '/':
result = num1/num2;
break;
}
return result;
}
int destroyStack(nsHead *stack)
{
nsNode *temp=NULL;
while(stack->top!=NULL)
{
temp = stack->top;
stack->top = stack->top->next;
free(temp);
}
stack->count = 0;
return 1;
}