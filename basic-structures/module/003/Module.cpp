#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

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

  llvm::FunctionType *Example = llvm::FunctionType::get(llvm::Type::getVoidTy(Context), false);

  llvm::Function *Foo = llvm::Function::Create(Example, llvm::GlobalValue::ExternalLinkage, "foo", MyModule);

  llvm::Function *Dummy = llvm::Function::Create(Example, llvm::GlobalValue::ExternalLinkage, "dummy", MyModule);

  int TotalFunctions = 0;

  for (llvm::Function &MyFunction : MyModule) {
    llvm::outs() << "Found Function: " << MyFunction.getName() << "\n";
    TotalFunctions++;
  }
  llvm::outs() << "Total Functions = " << TotalFunctions << "\n";

  MyModule.print(llvm::outs(), nullptr);
}