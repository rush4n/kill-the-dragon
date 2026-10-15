#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Use.h"
#include "llvm/IR/Value.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

int
main() {
  LLVMContext Context;
  Module MyModule("Module", Context);

  /* TYPES */
  Type *Int32Ty = Type::getInt32Ty(Context);

  /* FUNCTIONS */
  FunctionType *FooTy = FunctionType::get(Int32Ty, ArrayRef({Int32Ty}), false);
  Function *Foo = cast<Function>(MyModule.getOrInsertFunction("foo", FooTy).getCallee());

  /* BASIC BLOCKS */
  BasicBlock *Entry = BasicBlock::Create(Context, "entry", Foo);

  /* POPULATE ENTRY */
  IRBuilder Builder(Entry);
  Value *A = Foo->getArg(0);
  Value *I = Builder.CreateAdd(A, A, "sum1");
  Value *I2 = Builder.CreateAdd(A, I, "sum2");
  Value *I3 = Builder.CreateAdd(I, A, "sum3");
  Builder.CreateRet(I3);

  outs() << "All Uses of %0: \n";
  for (Use &MyUse : A->uses()) {
    MyUse.get()->print(outs());
    outs() << " is used at " <<MyUse.getOperandNo() << " in\n";
    MyUse.getUser()->print(outs());
    outs() << "\n";
  }

  outs() << "\nAll Uses of %sum1: \n";
  for (Use &MyUse : I->uses()) {
    MyUse.get()->print(outs());
    outs() << " is used at " <<MyUse.getOperandNo() << " in\n";
    MyUse.getUser()->print(outs());
    outs() << "\n";
  }

    MyModule.print(outs(), nullptr);

}