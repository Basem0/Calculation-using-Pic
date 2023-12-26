#include "infix_to_post.h"


// Stack structure for holding operators during parsing
static void initialize_t(stack_f *stack);
static void initialize(stack_i *stack);
static void push_t(stack_f *stack, float c);
static void push(stack_i *stack, char c);
static float pop_t(stack_f *stack);
static char pop(stack_i *stack);
static int precedence(char op);


void initialize_t(stack_f *stack) {
    stack->top = -1;
}

// Push an element onto the stack
void push_t(stack_f *stack, float c) {
    stack->data[++stack->top] = c;
}

// Pop an element from the stack
float pop_t(stack_f *stack) {
    return stack->data[stack->top--];
}
// Stack structure for holding operators during parsing


// Initialize the stack
void initialize(stack_i *stack) {
    stack->top = -1;
}

// Push an element onto the stack
void push(stack_i *stack, char c) {
    stack->data[++stack->top] = c;
}

// Pop an element from the stack
char pop(stack_i *stack) {
    return stack->data[stack->top--];
}

int check_digit (char c) {
	if ((c>='0') && (c<='9')) return 1;
	else return 0;
}

// Get the precedence of an operator
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0; // Assuming all other characters are operands
}

float doMath(char op, float op1, float op2){
    if (op == '*')
        return (float)(op1*op2);
    else if (op == '/')
        return (float)(op1/op2);
    else if (op == '+')
        return (float)(op1+op2);
    else if (op == '-')
        return (float)(op1-op2);
    return 0.0;
}

// Convert infix expression to postfix expression
void infixToPostfix(const char *infix, char *postfix) {
    stack_i operatorStack;
    initialize(&operatorStack);

    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        char current = infix[i];

        if (current == ' ') {
            i++;
            continue; // Skip spaces
        }

        if (check_digit(current) || current == '.') {
            while (check_digit(infix[i]) || infix[i] == '.') {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Space as a delimiter between operands
        } else { // Operator
            while (operatorStack.top != -1 && precedence(current) <= precedence(operatorStack.data[operatorStack.top])) {
                postfix[j++] = pop(&operatorStack);
            }
            push(&operatorStack, current);
            i++;
        }
    }

    while (operatorStack.top != -1) {
        postfix[j++] = pop(&operatorStack);
    }

    postfix[j] = '\0'; // Null-terminate the postfix string
}

// Evaluate postfix expression
void evaluatePostfix(const char *postfix, float *result) {
    stack_f operandStack;
    initialize_t(&operandStack);

    int i = 0;
    while (postfix[i] != '\0') {
        char current = postfix[i];

        if (check_digit(current) || current == '.') {
            float num = 0.0;
            int isFractional = 0;
            float fractionalMultiplier = 0.1;

            while (check_digit(postfix[i]) || postfix[i] == '.') {
                if (postfix[i] == '.') {
                    isFractional = 1;
                    i++;
                    continue;
                }

                if (!isFractional) {
                    num = num * 10 + (postfix[i] - '0');
                } else {
                    num += (postfix[i] - '0') * fractionalMultiplier;
                    fractionalMultiplier /= 10;
                }
                i++;
            }
            push_t(&operandStack, num);
            num = 0.0;
        } else if (current == ' ') {
            i++;
        } else {
            float operand2 = pop_t(&operandStack);
            float operand1 = pop_t(&operandStack);
            push_t(&operandStack, doMath(current, operand1, operand2));
            i++;
        }
    }

    *result = (float)pop_t(&operandStack);
}