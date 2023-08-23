#include "functions.h"
using std::cin, std::cout, std::endl, std::ostream, std::string;

#define INFO(X)  cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " = " << X << endl;
#define INFO_STRUCT(X) cout << "[INFO] ("<<__FUNCTION__<<":"<<__LINE__<<") " << #X << " count = " << X.count << endl;

/**
 * ----- REQUIRED -----
 * Pushes number to top of stack. If stack is full, then resize stack's array.
 * @param   stack   Target stack.
 * @param   number  Number to push to stack.
 */
void push(Stack& stack, int number) {
  if(stack.count < stack.capacity){
    stack.numbers[stack.count++] = number;
  }
  else{
    stack.capacity *= 2;

    int *big_num = new int[stack.capacity];

    for(int i = 0; i < stack.count; i++){
      big_num[i] = stack.numbers[i];
    }

    delete[] stack.numbers;
    stack.numbers = big_num;
    stack.numbers[stack.count++] = number;
  }

  INFO_STRUCT(stack);
  INFO(number);
}

/**
 * ----- REQUIRED -----
 * Pops number from top of stack. If stack is empty, return INT32_MAX.
 * @param   stack   Target stack.
 * @return          Value of popped number.
 */
int pop(Stack& stack) {
  int popped_num = 0;

  if(stack.count <= 0){
    return INT32_MAX;
  }
  else{
    popped_num = stack.numbers[--stack.count];
    int *copy = new int[stack.capacity];

    for(int i = 0; i < stack.count; i++){
      copy[i] = stack.numbers[i];
    }

    delete[] stack.numbers;
    stack.numbers = copy;
  }

  INFO_STRUCT(stack);

  return popped_num;
}

/**
 * ----- OPTIONAL -----
 * Returns the number at top of stack without popping it. If stack is empty, return INT32_MAX.
 * @param   stack   Target statck.
 * @return          Number at top of stack.
 */
int peek(const Stack& stack) {
  INFO_STRUCT(stack);
  return stack.numbers[stack.count-1];
}
