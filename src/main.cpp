#include "Command.h"

int main() {
  Receiver *receiver = new Receiver();
  Command *command = new ConcreteCommand(receiver);
  Invoker *invoker = new Invoker();
  invoker->SetCommand(command);
  invoker->ExecuteCommand();
  invoker->UnExecuteCommand();
  delete invoker;
  delete command;
  delete receiver;

  return 0;
}