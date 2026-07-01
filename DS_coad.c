/*
 * ============================================================
 *   DATA STRUCTURES PROJECT — STACK IMPLEMENTATION IN C
 * ============================================================
 *  Topics Covered:
 *    - Stack using Array (Static)
 *    - Stack using Linked List (Dynamic)
 *    - Applications:
 *        1. Undo/Redo simulation
 *        2. Expression evaluation (Postfix)
 *        3. Function call / Recursion simulation
 *        4. Balanced Parentheses checker
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================================
 *  SECTION 1 — STACK USING ARRAY (Static)
 * ============================================================ */

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int top;
} ArrayStack;

/* Initialize the stack */
void initArrayStack(ArrayStack *s) {
    s->top = -1;
}

/* Check if stack is empty */
int isEmptyArray(ArrayStack *s) {
    return s->top == -1;
}

/* Check if stack is full (overflow condition) */
int isFullArray(ArrayStack *s) {
    return s->top == MAX_SIZE - 1;
}

/* Push: Add element to top */
void push(ArrayStack *s, int value) {
    if (isFullArray(s)) {
        printf("  [ERROR] Stack Overflow! Cannot push %d\n", value);
        return;
    }
    s->top++;
    s->data[s->top] = value;
    printf("  Pushed: %d  (top index = %d)\n", value, s->top);
}

/* Pop: Remove and return top element */
int pop(ArrayStack *s) {
    if (isEmptyArray(s)) {
        printf("  [ERROR] Stack Underflow! Stack is empty.\n");
        return -1;
    }
    int val = s->data[s->top];
    s->top--;
    printf("  Popped: %d  (top index = %d)\n", val, s->top);
    return val;
}

/* Peek: View top element without removing */
int peek(ArrayStack *s) {
    if (isEmptyArray(s)) {
        printf("  [ERROR] Stack is empty.\n");
        return -1;
    }
    return s->data[s->top];
}

/* Display the entire stack */
void displayArray(ArrayStack *s) {
    if (isEmptyArray(s)) {
        printf("  Stack is empty.\n");
        return;
    }
    printf("  Stack (top -> bottom): ");
    for (int i = s->top; i >= 0; i--) {
        printf("%d ", s->data[i]);
    }
    printf("\n");
}

/* Demo for Array Stack */
void demoArrayStack() {
    printf("\n========================================\n");
    printf("  SECTION 1: STACK USING ARRAY\n");
    printf("========================================\n");

    ArrayStack s;
    initArrayStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    push(&s, 40);

    displayArray(&s);
    printf("  Peek (top element): %d\n", peek(&s));

    pop(&s);
    pop(&s);

    displayArray(&s);

    /* Overflow test */
    printf("\n  -- Overflow Test --\n");
    ArrayStack full;
    initArrayStack(&full);
    for (int i = 0; i <= MAX_SIZE; i++) push(&full, i); // triggers overflow on last
}


/* ============================================================
 *  SECTION 2 — STACK USING LINKED LIST (Dynamic)
 * ============================================================ */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} LinkedStack;

void initLinkedStack(LinkedStack *s) {
    s->top = NULL;
    s->size = 0;
}

int isEmptyLinked(LinkedStack *s) {
    return s->top == NULL;
}

/* Push using dynamic memory */
void pushLinked(LinkedStack *s, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("  [ERROR] Memory allocation failed!\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
    s->size++;
    printf("  Pushed: %d  (size = %d)\n", value, s->size);
}

/* Pop using dynamic memory (frees node) */
int popLinked(LinkedStack *s) {
    if (isEmptyLinked(s)) {
        printf("  [ERROR] Stack Underflow! Stack is empty.\n");
        return -1;
    }
    Node *temp = s->top;
    int val = temp->data;
    s->top = temp->next;
    free(temp);
    s->size--;
    printf("  Popped: %d  (size = %d)\n", val, s->size);
    return val;
}

int peekLinked(LinkedStack *s) {
    if (isEmptyLinked(s)) return -1;
    return s->top->data;
}

void displayLinked(LinkedStack *s) {
    if (isEmptyLinked(s)) {
        printf("  Stack is empty.\n");
        return;
    }
    printf("  Stack (top -> bottom): ");
    Node *curr = s->top;
    while (curr) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

/* Free all memory */
void freeLinkedStack(LinkedStack *s) {
    while (!isEmptyLinked(s)) popLinked(s);
}

void demoLinkedStack() {
    printf("\n========================================\n");
    printf("  SECTION 2: STACK USING LINKED LIST\n");
    printf("========================================\n");

    LinkedStack s;
    initLinkedStack(&s);

    pushLinked(&s, 5);
    pushLinked(&s, 15);
    pushLinked(&s, 25);
    pushLinked(&s, 35);

    displayLinked(&s);
    printf("  Peek: %d\n", peekLinked(&s));

    popLinked(&s);
    displayLinked(&s);

    freeLinkedStack(&s);
    printf("  Stack freed (all nodes deallocated).\n");
}


/* ============================================================
 *  SECTION 3 — APPLICATION 1: BALANCED PARENTHESES CHECKER
 * ============================================================ */

int isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int isBalanced(const char *expr) {
    char stack[256];
    int top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '{' || ch == '[') {
            stack[++top] = ch;
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1 || !isMatching(stack[top], ch)) return 0;
            top--;
        }
    }
    return top == -1;
}

void demoBalancedParentheses() {
    printf("\n========================================\n");
    printf("  APPLICATION 1: BALANCED PARENTHESES\n");
    printf("========================================\n");

    const char *exprs[] = {
        "{[()]}",
        "((a+b)*c",
        "[{()}]",
        "({[}])",
        "((()))"
    };
    int n = 5;

    for (int i = 0; i < n; i++) {
        printf("  Expression: %-15s -> %s\n",
               exprs[i],
               isBalanced(exprs[i]) ? "BALANCED" : "NOT BALANCED");
    }
}


/* ============================================================
 *  SECTION 4 — APPLICATION 2: POSTFIX EXPRESSION EVALUATION
 * ============================================================ */

int evaluatePostfix(const char *expr) {
    int stack[64], top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        if (ch == ' ') continue;

        if (isdigit(ch)) {
            stack[++top] = ch - '0';
        } else {
            if (top < 1) {
                printf("  [ERROR] Invalid postfix expression.\n");
                return 0;
            }
            int b = stack[top--];
            int a = stack[top--];
            int result;
            switch (ch) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) { printf("  [ERROR] Division by zero.\n"); return 0; }
                    result = a / b;
                    break;
                default:
                    printf("  [ERROR] Unknown operator: %c\n", ch);
                    return 0;
            }
            stack[++top] = result;
        }
    }
    return stack[top];
}

void demoPostfix() {
    printf("\n========================================\n");
    printf("  APPLICATION 2: POSTFIX EVALUATION\n");
    printf("========================================\n");

    struct { const char *expr; int expected; } tests[] = {
        {"23+",       5},   // 2+3
        {"53-2*",     4},   // (5-3)*2
        {"23*4+",    10},   // 2*3+4
        {"82/",       4},   // 8/2
        {"234*+",    14},   // 2+3*4
    };

    for (int i = 0; i < 5; i++) {
        int result = evaluatePostfix(tests[i].expr);
        printf("  Postfix: %-12s -> Result: %d  (expected: %d) %s\n",
               tests[i].expr, result, tests[i].expected,
               result == tests[i].expected ? "OK" : "MISMATCH");
    }
}


/* ============================================================
 *  SECTION 5 — APPLICATION 3: UNDO / REDO SIMULATION
 * ============================================================ */

#define HIST_SIZE 20

typedef struct {
    char actions[HIST_SIZE][64];
    int top;
} ActionStack;

void initAction(ActionStack *s) { s->top = -1; }
int isEmptyAction(ActionStack *s) { return s->top == -1; }

void pushAction(ActionStack *s, const char *action) {
    if (s->top == HIST_SIZE - 1) {
        printf("  [WARN] History limit reached.\n");
        return;
    }
    strcpy(s->actions[++s->top], action);
}

const char *popAction(ActionStack *s) {
    if (isEmptyAction(s)) return NULL;
    return s->actions[s->top--];
}

void demoUndoRedo() {
    printf("\n========================================\n");
    printf("  APPLICATION 3: UNDO / REDO SIMULATION\n");
    printf("========================================\n");

    ActionStack undoStack, redoStack;
    initAction(&undoStack);
    initAction(&redoStack);

    /* Simulate actions */
    const char *ops[] = {"Type 'Hello'", "Bold text", "Insert image", "Change font"};
    for (int i = 0; i < 4; i++) {
        printf("  DO   : %s\n", ops[i]);
        pushAction(&undoStack, ops[i]);
    }

    printf("\n  -- Undo 2 actions --\n");
    for (int i = 0; i < 2; i++) {
        const char *a = popAction(&undoStack);
        if (a) {
            printf("  UNDO : %s\n", a);
            pushAction(&redoStack, a);
        }
    }

    printf("\n  -- Redo 1 action --\n");
    const char *r = popAction(&redoStack);
    if (r) {
        printf("  REDO : %s\n", r);
        pushAction(&undoStack, r);
    }

    printf("\n  Undo stack (top->bottom): ");
    for (int i = undoStack.top; i >= 0; i--)
        printf("[%s] ", undoStack.actions[i]);
    printf("\n");
}


/* ============================================================
 *  SECTION 6 — APPLICATION 4: FUNCTION CALL STACK SIMULATION
 * ============================================================ */

void demoRecursionStack() {
    printf("\n========================================\n");
    printf("  APPLICATION 4: FUNCTION CALL STACK\n");
    printf("========================================\n");

    char callStack[10][32];
    int top = -1;

    /* Simulate factorial(4) call stack */
    const char *calls[] = {
        "main()",
        "factorial(4)",
        "factorial(3)",
        "factorial(2)",
        "factorial(1) -> returns 1"
    };

    printf("  Pushing calls (simulating factorial(4)):\n");
    for (int i = 0; i < 5; i++) {
        strcpy(callStack[++top], calls[i]);
        printf("    CALL  : %s\n", callStack[top]);
    }

    printf("\n  Returning (popping):\n");
    int result = 1;
    int factors[] = {1, 2, 3, 4};
    int fi = 0;
    while (top >= 0) {
        printf("    RETURN: %s\n", callStack[top--]);
        if (fi < 4) result *= factors[fi++];
    }
    printf("  Final result of factorial(4) = %d\n", result);
}


/* ============================================================
 *  MAIN — Run all demos
 * ============================================================ */

int main() {
    printf("\n");
    printf("**********************************************\n");
    printf("*    DATA STRUCTURES PROJECT — STACK        *\n");
    printf("*    Implementation in C Language           *\n");
    printf("**********************************************\n");

    demoArrayStack();
    demoLinkedStack();
    demoBalancedParentheses();
    demoPostfix();
    demoUndoRedo();
    demoRecursionStack();

    printf("\n========================================\n");
    printf("  END OF PROJECT OUTPUT\n");
    printf("========================================\n\n");

    return 0;
}
