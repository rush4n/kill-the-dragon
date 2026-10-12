#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"

int
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  llvm::Type *IntType = llvm::Type::getInt32Ty(Context);
  llvm::Constant *Initializer = llvm::ConstantInt::get(IntType, 42);

  new llvm::GlobalVariable(
    MyModule,
    IntType,
    false,
    llvm::GlobalValue::ExternalLinkage,
    Initializer,
    "Value"
  );

  llvm::FunctionType *Template = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false);

  llvm::Function *Foo = llvm::Function::Create(Template, llvm::GlobalValue::ExternalLinkage, "foo", MyModule);

  llvm::Function *Dummy = llvm::Function::Create(Template, llvm::GlobalValue::ExternalLinkage, "dummy", MyModule);

  llvm::BasicBlock *BB0 = llvm::BasicBlock::Create(Context, "entry", Foo);
  llvm::ReturnInst *ReturnVal = llvm::ReturnInst::Create(Context, BB0);

  for (llvm::Function &MyFunction : MyModule) {
    llvm::outs() << "Function = " << MyFunction.getName() << "\n";
    llvm::outs() << "Return type = ";
    MyFunction.getReturnType()->print(llvm::outs());
    llvm::outs() << "\n";
    llvm::outs() << "Is empty = " << (MyFunction.empty() ? "Y" : "N") << "\n";
    llvm::outs() << "Is Declaration = " << (MyFunction.isDeclaration() ? "Y" : "N") << "\n";
    llvm::outs() << "Function Module = " << MyFunction.getParent()->getName() << "\n\n";
  }

  for (llvm::Function &MyFunction : MyModule) {
    if (MyFunction.isDeclaration()) continue;
    for (llvm::BasicBlock &MyBasicBlock : MyFunction) {
      llvm::outs() << "Basic Block = " << MyBasicBlock.getName() << "\n";
      for (llvm::Instruction &MyInstruction : MyBasicBlock) {
        llvm::outs() << "Instruction = " << MyInstruction.getOpcodeName() << "\n\n";
      }
    }
  }

  MyModule.print(llvm::outs(), nullptr);
}