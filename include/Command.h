/**
 * @file Command.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-06
 *
 * @copyright Copyright (c) 2024
 *
 * 命令模式是一种行为设计模式，它可将请求转换为一个包含与请求相关的所有信息的独立对象。
 * 该转换让你能根据不同的请求将方法参数化、
 * 延迟请求执行或将其放入队列中，且能实现可撤销操作。
 */

#include <iostream>

class Command {
public:
  virtual void Execute() = 0;
  virtual void UnExecute() = 0;
  virtual ~Command() {}

private:
  int m_value;
  int m_value2;
};

class Receiver {
public:
  void Action() { std::cout << "Action" << std::endl; }
  void UnAction() { std::cout << "UnAction" << std::endl; }
  ~Receiver() {}

private:
  int m_value;
};

class ConcreteCommand : public Command {
public:
  ConcreteCommand(Receiver *receiver) : m_receiver(receiver) {}
  void Execute() override { m_receiver->Action(); }
  void UnExecute() override { m_receiver->UnAction(); }

private:
  Receiver *m_receiver;
};

class Invoker {
public:
  void SetCommand(Command *command) { m_command = command; }
  void ExecuteCommand() { m_command->Execute(); }
  void UnExecuteCommand() { m_command->UnExecute(); }

private:
  Command *m_command;
};
