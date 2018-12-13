/*
	make postfix_repl && ./postfix_repl
*/

#include "base.h"

#define STACK_SIZE  10

typedef enum {
	OPERATION, VALUE, EMPTY
} Tag;

typedef struct{
	Tag tag;
	
	union{
		int value;
		char operation;
	};
} StackElement;

typedef struct{
	StackElement elements[STACK_SIZE];
	int stack_pointer;
} Stack;

//checks if char c belongs to an operation
bool is_operation(char c){
	return c == '+' || c == '/' || c == '-' || c == '*';
}

//checks wheter c is a digit
bool is_digit(char c){
	return c >= '0' && c <= '9';
}

//todo:
StackElement make_StackElement(Tag tag){
	StackElement ele;
	ele.tag = tag;
	return ele;
} 
//todo:
StackElement make_Value(int value){
	
	StackElement ele = make_StackElement(VALUE);
	ele.value = value;
	return ele;
}
//todo:
StackElement make_Operation(char operation){
	StackElement ele = make_StackElement(OPERATION);
	ele.operation = operation;
	return ele;
}


bool is_empty(Stack* stack){
	return stack->stack_pointer < 0;
}


void push(StackElement element, Stack* stack, int n){ 
// eingegeben wird das Element, der Pointer auf den Stack auf den wir das Element pushen möchten und die Nummer des Elements welches auf den Stackgepusht werden soll. Ausgegeben wird nichts direkt. DerPointer zeigt auf das neu eingefügte Element.
	if(stack->stack_pointer < (n - 1)){
		stack->stack_pointer++;
		stack->elements[stack->stack_pointer] = element;
	}
}
//eingegeben wird der Pointer auf den Stack von dem wir ein Element entfernen möchten.
//ausgegeben wird das gepopte ( höhö ;) ) Element
StackElement pop(Stack* stack){
	StackElement ele = stack->elements[stack->stack_pointer ];
	stack->elements[stack->stack_pointer] = make_StackElement(EMPTY);
	stack->stack_pointer--;
	return ele;
}

//todo:
void clear_stack(Stack* stack, int n){
	for (int i=0; i <= n; i++){
		if (is_empty(stack)){
			break;
		}
		pop(stack);
	}
}

//todo:
void print_stackElement(StackElement ele){
	if (is_digit(ele.tag))printi(ele.value);
	else if (is_operation(ele.tag))	printc(ele.operation);
	else printf("%s\n", "[]");
}

//todo:
void print_stack(Stack* stack, int n){
	for (int i = 0; i <= n; i++){
		print_stackElement(pop(stack));
	}
}


void compute(Stack* stack, int n){
	StackElement ele0 = pop(stack);
	StackElement ele1 = pop(stack);
	StackElement ele2 = pop(stack);
	StackElement eletemp;
	if (ele0.operation == '+' && stack -> stack_pointer >=1){
		push(make_Value(ele2.value + ele1.value), stack, n - 2);
		eletemp = pop(stack);
		print_stackElement(eletemp);
		push(eletemp, stack, n-2);
	}else if (ele0.operation == '-' && stack -> stack_pointer >=1){
		push(make_Value(ele2.value + ele1.value), stack, n - 2);
		eletemp = pop(stack);
		print_stackElement(eletemp);
		push(eletemp, stack, n-2);
	}else if (ele0.operation == '*' && stack -> stack_pointer >=1){
	push(make_Value(ele2.value + ele1.value), stack, n - 2);
		eletemp = pop(stack);
		print_stackElement(eletemp);
		push(eletemp, stack, n-2);
	}else if (ele0.operation == '/' && stack -> stack_pointer >=1){
		push(make_Value(ele2.value + ele1.value), stack, n - 2);
		eletemp = pop(stack);
		print_stackElement(eletemp);
		push(eletemp, stack, n-2);
		}
}

int main (void){	
	Stack stack;
	
	clear_stack(&stack, STACK_SIZE);

	int c;
	String temp;
	while((c = getchar()) != 'q'){
		char cs[2];
		cs[0] = c;
		cs[1] = '\0';
		if (is_operation(c)){
			push(make_Operation(c),&stack,STACK_SIZE);
			compute(&stack, STACK_SIZE);
		}else{
			temp = cs;
			while (is_digit(c = getchar())){
				temp = s_concat(temp, cs);
			}
			push(make_Value(atoi(temp)), &stack, STACK_SIZE);
			if(c == '\n'){
				StackElement ele = pop(&stack);
					if (is_digit(ele.value) && is_empty(&stack)){ 
					//just to be sure I am checking if the Stack is empty
						print_stackElement(ele);
					}else{
						printf("%s\n", "Error 69: not enuff elemundos foundo / Sackeru not righteru");
					}
			}

		}
	}
	return 0;
}
