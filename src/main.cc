#include <iostream>
#include <string>

#include "Value.hh"
#include "Instruction.hh"
#include "DanxeVm.hh"

const danxe::Instruction inst[] = {
    danxe::Instruction{danxe::Opcode::Mov, 0ULL, danxe::Value{4ULL}},
    danxe::Instruction{danxe::Opcode::Mov, 3ULL, danxe::Value{6ULL}},
    danxe::Instruction{danxe::Opcode::PrintLn, 3ULL},
    danxe::Instruction{danxe::Opcode::PrintLn},
    danxe::Instruction{danxe::Opcode::PrintLn, 2ULL},
    danxe::Instruction{danxe::Opcode::Halt},
};

int main()
{
    danxe::DanxeVm vm(inst);

    while (vm.isHalt() == danxe::HaltState::Running)
        vm.run();

    return 0;
}
