#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"


int 
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  llvm::FunctionType *Template = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false);
  llvm::Function *Foo = llvm::Function::Create(Template, llvm::GlobalValue::ExternalLinkage, "foo", MyModule);

  llvm::BasicBlock *BB1 = llvm::BasicBlock::Create(Context, "BB1", Foo);
  llvm::ReturnInst *ReturnVal = llvm::ReturnInst::Create(Context, BB1);

  for (llvm::Instruction &MyInstruction : *BB1) {
    llvm::outs() << "Instruction: " << MyInstruction.getOpcodeName() << "\n";
    llvm::outs() << "Basic Block: " << MyInstruction.getParent()->getName() << "\n";
    llvm::outs() << "Function: " << BB1->getParent()->getName() << "\n";
    llvm::outs() << "Terminator: " << BB1->getTerminator()->getOpcodeName() << "\n";
  }

  MyModule.print(llvm::outs(), nullptr);
}