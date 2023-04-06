#pragma once

#include "Error.hh"
#include "Vm.hh"

namespace danxe::danxevm {
class Debugger : public Vm {
 public:
    explicit Debugger(const char* source);
    ~Debugger() override = default;

    Debugger(const Debugger&) = delete;
    Debugger(Debugger&&) = delete;
    Debugger& operator=(const Debugger&&) = delete;
    Debugger& operator=(Debugger&&) = delete;

    DanxeVmErr run();

 private:
    DanxeVmErr runArgument(bool* isQuit, char ch);
};
}  // namespace danxe::danxevm
