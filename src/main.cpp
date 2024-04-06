#include "ChainOfResposbility.h"

int main() {
  auto handler1 = std::make_unique<ConcreteHandler1>();
  auto handler2 = std::make_unique<ConcreteHandler2>();

  handler1->SetNext(std::move(handler2));

  // 处理请求
  handler1->HandleRequest(1); // 输出：Handler1处理请求
  handler1->HandleRequest(2); // 输出：Handler2处理请求
  handler1->HandleRequest(10);
  handler1->HandleRequest(20);

  return 0;
}