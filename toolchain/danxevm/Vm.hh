#pragma once

#include "Error.hh"
#include "Instruction.hh"
#include "Value.hh"

namespace danxe::danxevm {
constexpr size_t STACK_CAPACITY = 2048;
constexpr size_t DATA_STACK_CAPACITY = 2048;
constexpr size_t CALL_STACK_CAPACITY = 1024;

class Vm {
 public:
    explicit Vm(const char* inputFilename);
    virtual ~Vm();

    Vm(const Vm&) = delete;
    Vm(Vm&&) = delete;
    Vm& operator=(const Vm&) = delete;
    Vm& operator=(Vm&&) = delete;

    DanxeVmErr run();

 protected:
    DanxeVmErr runInst();

    DanxeVmErr parse();
    DanxeVmErr parseInst();

    const danxe::Instruction& getCurrentInst() const;
    const danxe::Value* getStack() const;
    size_t getSp() const;
    const danxe::Value* getDataStack() const;
    size_t getDataSp() const;
    const size_t* getCallStack() const;
    size_t getCallSp() const;
    bool isHalt() const;

 private:
    void nextChar();

 private:
    const char* mSource;
    const char* mCurrent;
    const char* mPeek;
    bool mIsParseFinished;

    const char* mGlobalData;
    size_t mGlobalDataLen;

    danxe::Instruction* mInst;
    size_t mInstLen;
    size_t mIp;

    danxe::Value mStack[STACK_CAPACITY];
    size_t mSp;

    danxe::Value mDataStack[DATA_STACK_CAPACITY];
    size_t mDataSp;

    size_t mCallStack[CALL_STACK_CAPACITY];
    size_t mCallSp;

    bool mIsHalt;
};
}  // namespace danxe::danxevm
