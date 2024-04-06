#include "ChainOfResposbility.h"
#include <iostream>
void Handler::SetNext(std::unique_ptr<Handler> next) {
  this->m_next = std::move(next);
}

void ConcreteHandler1::HandleRequest(int request) {
  if (request >= 0 && request < 10) {
    std::cout << "ConcreteHandler1 处理请求" << std::endl;
  } else if (m_next) {
    m_next->HandleRequest(request);
  }
}

void ConcreteHandler2::HandleRequest(int request) {
  if (request >= 10 && request < 20) {
    std::cout << "ConcreteHandler2 处理请求" << std::endl;
  } else if (m_next) {
    m_next->HandleRequest(request);
  } else {
    std::cout << "没有处理" << std::endl;
  }
}