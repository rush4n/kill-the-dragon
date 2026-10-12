#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Constants.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/GlobalVariable.h"

int 
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  llvm::Type *IntType = llvm::Type::getInt32Ty(Context);
  llvm::Constant *InitialValue = llvm::ConstantInt::get(IntType, 42);

  new llvm::GlobalVariable(
    MyModule,
    IntType,
    false,
    llvm::GlobalValue::ExternalLinkage,
    InitialValue,
    "Value"
  );

  MyModule.print(llvm::outs(), nullptr);
}
