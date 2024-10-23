#include "../../include/ir/opt/ConstantProp.hpp"
#include "../../include/lib/BaseCFG.hpp"
#include "../../include/lib/Type.hpp"
#include <cmath>
#include <set>
#include "../../include/ir/opt/DCE.hpp"


bool ConstantProp::Run() 
{
  /*
  要求：
  1. 顺序遍历function中的每个基本块,并顺序遍历基本块中的每个指令
  2. 如果一个指令是常量传播的结果，那么就将这个指令替换为常量，并删除这个指令
  */
  Function* func = Singleton<Module>().GetMainFunction();  
  for(auto bb:(*func))
  {
    for(auto inst:(*bb))
    {
      User* foldVale = ConstFoldInst(inst);
      if(foldVale)
      {
        inst->RAUW(foldVale);

        if(inst->GetUserListSize() == 0)
        {
          inst->EraseFromParent();
          delete inst;
        }
        // inst->EraseFromParent();
        // delete foldVale;
        // RemoveInst(inst);
      }
    }
  }

  return true;
}

User *ConstantProp::ConstFoldInst(User *inst) 
{
  /*
  要求：
  1. 考虑一条指令是否能进行常量折叠
  2. 如果能够进行常量折叠，那么返回折叠后的常量
  3. 正确判断指令的类型，对于不同的类型需要有不同的处理方法
  这个过程可以自行在 ConstantProp类中增加函数来实现功能
  */
  if(inst->IsBinary())
  {
   
 
    return inst;

    // int folded = FoldBinary(inst);
    // std::string s = std::to_string(folded);
    // inst->SetName(s);
    // auto it = Type:: NewTypeByEnum(IR_Value_INT);
    // inst->SetType(it);
  } 

  return nullptr;
}


int ConstantProp:: FoldBinary(User *inst)
{
  Operand op1 = inst->GetOperand(0);
  Operand op2 =inst->GetOperand(1);
  
  // switch (inst->GetInstId())
  // {
  // case User::OpID::Add:
  //     return op1->isConst()+op2;
  // case User::OpID::Sub:
  //     return num1-num2;
  // case User::OpID::Mul:
  //     return num1*num2;
  // case User::OpID::Div:
  //     return num1/num2;
  // case User::OpID::Mod:
  //     return num1%num2;
  // case User::OpID::And:
  //     return num1 & num2;
  // case User::OpID::Or:
  //     return num1 | num2;
  // case User::OpID::Xor:
  //     return num1^num2;
  // case User::OpID::Eq:
  //     return num1 == num2 ? 1: 0;
  // case User::OpID::Ne:
  //     return num1 != num2 ? 1: 0;
  // case User::OpID::Ge:
  //     return num1 >= num2 ? 1: 0;
  // case User::OpID::L:
  //     return num1 < num2 ? 1: 0;
  // case User::OpID::Le:
  //     return num1 <= num2 ? 1: 0;
  // case User::OpID::G:
  //     return num1 > num2 ? 1: 0;
  // default:
  //   break;
  // }

  return 0;
}



// int ConstantProp:: FoldBinary(User *inst)
// {
//   int size = inst->Getuselist().size();
//   Value* op1 = inst->GetOperand(0);
//   // op1.as();   
//   // int* num1 = op1->as_int();
//   int num1= std::stoi(op1->GetName());
//   // op1.as();
//   // Value* op2 = nullptr;
//   // int num2;
//   // if(size > 1)
//   // {
//   Value* op2 = inst->GetOperand(1);
//   int num2= std::stoi(op2->GetName());
//   // }
//   switch (inst->GetInstId())
//   {
//   case User::OpID::Add:
//       return num1+num2;
//   case User::OpID::Sub:
//       return num1-num2;
//   case User::OpID::Mul:
//       return num1*num2;
//   case User::OpID::Div:
//       return num1/num2;
//   case User::OpID::Mod:
//       return num1%num2;
//   case User::OpID::And:
//       return num1 & num2;
//   case User::OpID::Or:
//       return num1 | num2;
//   case User::OpID::Xor:
//       return num1^num2;
//   case User::OpID::Eq:
//       return num1 == num2 ? 1: 0;
//   case User::OpID::Ne:
//       return num1 != num2 ? 1: 0;
//   case User::OpID::Ge:
//       return num1 >= num2 ? 1: 0;
//   case User::OpID::L:
//       return num1 < num2 ? 1: 0;
//   case User::OpID::Le:
//       return num1 <= num2 ? 1: 0;
//   case User::OpID::G:
//       return num1 > num2 ? 1: 0;
//   default:
//     break;
//   }
//   return 0;
// }

void ConstantProp::RemoveInst(User *inst) 
{
      if(inst == nullptr)
        return;
      UserList List = inst->GetUserlist();
      // inst 作为value的时候
      for(auto e:List)
      {
         e->RemoveFromUserList(e->GetUser());
      }
      // inst 还要作为 user
      // user 获取 value
      int size = inst->Getuselist().size();
      for(int i = 1; i < size; i++)
      {
        Operand it = inst->GetOperand(i);
        UserList List = it->GetUserlist(); 
        for(auto e:List)
        {
          if(e->GetUser() == inst)
          {
            e->RemoveFromUserList(inst);
          }
        }

      }

      inst->EraseFromParent();
      delete inst;
}

