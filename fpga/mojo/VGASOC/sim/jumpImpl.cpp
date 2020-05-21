#include <stdexcept>
#include "assembly.h"


namespace ISA{

extern short opcodes[];

void JumpInstructionImpl::parseOpcode() {
    mEncoded  = opcodes[Instruction::JUMP] << 28;
}

void JumpInstructionImpl::validate() {
    if (mLOperand.type != OperandType::REGISTER) {
        throw std::runtime_error("jr needs a register as source operand");
    }
    if (mROperand.type != OperandType::EMPTY && mROperand.type != OperandType::REGISTER) {
        throw std::runtime_error("jr needs a register as destination operand");
    }
}

void JumpInstructionImpl::encode() {
    mEncoded |= mLOperand.reg << 20;
    mEncoded |= mROperand.type == OperandType::REGISTER ? mROperand.reg << 16 : 0; 
}

} // end namespace ISA