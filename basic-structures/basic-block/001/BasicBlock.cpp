#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/ADT/PostOrderIterator.h"


int 
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  llvm::FunctionType *Template = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false);
  llvm::Function *Foo = llvm::Function::Create(Template, llvm::GlobalValue::ExternalLinkage, "foo", MyModule);

  llvm::BasicBlock *BB1 = llvm::BasicBlock::Create(Context, "entry", Foo);
  llvm::BasicBlock *BB2 = llvm::BasicBlock::Create(Context, "exit", Foo);
  llvm::UncondBrInst *Branch = llvm::UncondBrInst::Create(BB2, BB1);
  llvm::ReturnInst *ReturnVal = llvm::ReturnInst::Create(Context, BB2);

  for (llvm::Instruction &MyInstruction : *BB1) {
    llvm::outs() << "Instruction: " << MyInstruction.getOpcodeName() << "\n";
    llvm::outs() << "Basic Block: " << MyInstruction.getParent()->getName() << "\n";
    llvm::outs() << "Function: " << BB1->getParent()->getName() << "\n";
    llvm::outs() << "Terminator: " << BB1->getTerminator()->getOpcodeName() << "\n";
  }

  llvm::ReversePostOrderTraversal<llvm::Function *> RPOT(Foo);
  llvm::outs() << "ORDER OF EXECUTION" << "\n";
  for (llvm::BasicBlock *BB : RPOT) {
    llvm::outs() << " -> " << BB->getName();
  }
  llvm::outs() << "\nEND OF PROGRAM" << "\n";

  MyModule.print(llvm::outs(), nullptr);
}