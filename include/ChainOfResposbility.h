#ifndef CHAINOFRESPOSBILITY_H
#define CHAINOFRESPOSBILITY_H

#include <memory>

class Handler {
public:
  virtual void HandleRequest(int request) = 0;
  virtual void SetNext(std::unique_ptr<Handler> next);
  virtual ~Handler() {}

protected:
  std::unique_ptr<Handler> m_next = nullptr;
};

class ConcreteHandler1 : public Handler {
public:
  void HandleRequest(int request) override;
};

class ConcreteHandler2 : public Handler {
public:
  void HandleRequest(int request) override;
};

#endif // CHAINOFRESPOSBILITY_H

/**
 * @brief 使用场景
 * 1. 当程序需要使用不同方式处理不同种类请求， 而且请求类型和顺序预先未知时，
 * 可以使用责任链模式。
 * 2. 当必须按顺序执行多个处理者时， 可以使用该模式。
 * 3. 如果所需处理者及其顺序必须在运行时进行改变， 可以使用责任链模式。
 */