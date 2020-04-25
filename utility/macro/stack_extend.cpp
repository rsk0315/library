#ifndef H_stack_extend
#define H_stack_extend

/**
 * @brief スタック拡張マクロ（魔法）
 * @author えびちゃん
 * @see http://sigma425.hatenablog.com/entry/2016/03/26/221844
 */

#include <cstdlib>

#define BEGIN_STACK_EXTEND(size)                                        \
  void* stack_extend_memory_ = malloc(size);                            \
  void* stack_extend_origin_memory_;                                    \
  char* stack_extend_dummy_memory_ = (char*)alloca((1+(int)(((long long)stack_extend_memory_)&127))*16); \
  *stack_extend_dummy_memory_ = 0;                                      \
  asm volatile ("mov %%rsp, %%rbx\n\tmov %%rax, %%rsp":"=b"(stack_extend_origin_memory_):"a"((char*)stack_extend_memory_+(size)-1024));

#define END_STACK_EXTEND                                                \
  asm volatile ("mov %%rax, %%rsp"::"a"(stack_extend_origin_memory_));  \
  free(stack_extend_memory_);

#endif  /* !defined(H_stack_extend) */
