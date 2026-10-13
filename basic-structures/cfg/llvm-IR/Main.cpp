#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

int
main() {
  llvm::LLVMContext Context;
  llvm::Module MyModule("Module", Context);

  /* TYPES DECLARATION */
  Type *Int32Ty = Type::getInt32Ty(Context);
  Type *VoidTy = Type::getVoidTy(Context);

  /* ADD FUNCTIONS */
  FunctionType *BazTy = FunctionType::get(Int32Ty, false);
  Function *BazFunc = cast<Function>(MyModule.getOrInsertFunction("baz", BazTy).getCallee()); 

  FunctionType *BarTy = FunctionType::get(Int32Ty, ArrayRef({Int32Ty}), false);
  Function *BarFunc = cast<Function>(MyModule.getOrInsertFunction("bar", BarTy).getCallee());

  FunctionType *FooTy = FunctionType::get(VoidTy, ArrayRef({Int32Ty, Int32Ty}), false);
  Function *FooFunc = cast<Function>(MyModule.getOrInsertFunction("foo", FooTy).getCallee());

  /* BASIC BLOCKS */
  BasicBlock *BB1 = BasicBlock::Create(Context, "", FooFunc);
  BasicBlock *BB2 = BasicBlock::Create(Context, "", FooFunc);
  BasicBlock *BB3 = BasicBlock::Create(Context, "", FooFunc);

  /* BASICK BLOCK 1 */
  IRBuilder Builder(BB1);
  Value *I = Builder.CreateAlloca(Int32Ty);
  Value *I2 = Builder.CreateAlloca(Int32Ty);
  Value *I3 = Builder.CreateAlloca(Int32Ty);

  Value *Arg1 = FooFunc->getArg(0);
  Value *Arg2 = FooFunc->getArg(1);

  Builder.CreateStore(Arg1, I);
  Builder.CreateStore(Arg2, I2);

  Value *I4 = Builder.CreateLoad(Int32Ty, I);
  Value *I5 = Builder.CreateLoad(Int32Ty, I2);

  Value *I6 = Builder.CreateAdd(I4, I5);
  Builder.CreateStore(I6, I3);
  Value *I7 = Builder.CreateLoad(Int32Ty, I3);

  Value *Const255 = ConstantInt::get(Int32Ty, 255);
  Value *I8 = Builder.CreateICmpEQ(I7, Const255);
  Builder.CreateCondBr(I8, BB2, BB3);

  /* BASIC BLOCK 2 */
  Builder.SetInsertPoint(BB2);

  Value *I10 = Builder.CreateLoad(Int32Ty, I3);
  Builder.CreateCall(BarFunc->getFunctionType(), BarFunc, ArrayRef(I10));
  Value *I11 = Builder.CreateCall(BazFunc->getFunctionType(), BarFunc);
  Builder.CreateStore(I11, I3);
  Builder.CreateBr(BB3);

  /* BASIC BLOCK 3 */
  Builder.SetInsertPoint(BB3);

  Value *I12 = Builder.CreateLoad(Int32Ty, I3);
  Value *I13 = Builder.CreateCall(BarFunc->getFunctionType(), BarFunc, ArrayRef(I12));
  Builder.CreateRetVoid();

  /* SPIT IR */
  MyModule.print(outs(), nullptr);
}