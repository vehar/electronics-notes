#include <string>

namespace ISA {

enum OperandType {
    EMPTY,
    IMMEDIATE,
    REGISTER,
    REFERENCE_REGISTER,
    REFERENCE_REGISTER_OFFSET,
    REFERENCE_IMMEDIATE,
};
struct Operand {
    OperandType type;
    uint8_t reg;
    uint32_t immediate;
    uint16_t offset;
};

class InstructionImpl {
    friend class Instruction;
protected:
    uint32_t mEncoded = 0;
    std::string mOpcode;
    std::string mStrLOperand;
    std::string mStrROperand;

    Operand mLOperand;
    Operand mROperand;

    virtual void parseOpcode() = 0;
    void parseLeftOperand();
    void parseRightOperand();
    void parse();
    virtual void validate() = 0;
    virtual void encode() = 0;
public:
    InstructionImpl(const std::string opcode, const std::string leftOperand, const std::string rightOperand) :
        mOpcode(opcode), mStrLOperand(leftOperand), mStrROperand(rightOperand) {
    } ;
    uint32_t getEncoding() { return mEncoded;}; /* TODO: call parse() only on getEncoding() */
};

class LoadInstructionImpl : public InstructionImpl {
    friend class Instruction;
    /*
     * FIXME: is there a way to make the base class call the parse() method for the right type of class?
     */
    LoadInstructionImpl(const std::string opcode, const std::string leftOperand, const std::string rightOperand) : InstructionImpl(opcode, leftOperand, rightOperand) {
        this->parse();
    };
    size_t parseFlags();
    void parseOpcode();
    void validate();
    void encode();
};

class JumpInstructionImpl : public InstructionImpl {
    friend class Instruction;
    /*
     * FIXME: is there a way to make the base class call the parse() method for the right type of class?
     */
    JumpInstructionImpl(const std::string opcode, const std::string leftOperand, const std::string rightOperand) : InstructionImpl(opcode, leftOperand, rightOperand) {
        this->parse();
    };
    size_t parseFlags();
    void parseOpcode();
    void validate();
    void encode();
};


class Instruction {
public:
    typedef enum {
        LOAD,
        JUMP,
        STORE,
        ADD,
        XOR,
    } InstructionType;


    Instruction(const std::string mnemonic) : mMnemonic(mnemonic) {
        parse();
    }
    uint32_t getEncoding() { return mInstruction->getEncoding();};
    static Operand parseOperand(const std::string operand);

    private:
        InstructionType mType;
        InstructionImpl* mInstruction = nullptr;
        const std::string mMnemonic;

        void parse();
};

} // end namespace ISA