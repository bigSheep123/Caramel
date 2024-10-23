#include "../../include/ir/opt/DCE.hpp"
#include<vector>
bool DCE::Run() {
  /*
  要求：
  1. 顺序遍历function中的每个基本块,并顺序遍历基本块中的每个指令
  2. 如果一个指令没有副作用, 并且是一个"死"指令，那么就删除这个指令
  */

  // 思路： 我创建一个工作列表， 由于指令之间是相互影响的，如果一个指令被删除了，我将把它的工作数移动到该列表中
  // 对该列表进行遍历，知道该列表的内容为空时，程序结束运行。
  std::vector<Value*> WorkList;
  // std::cout<<"DCE "<<std::endl;
  Function* it = Singleton<Module>().GetMainFunction();
  if(!it)
  {
    return false;
  }

  for(BasicBlock* bb: *(it))
  {
    for(auto inst: *bb)
    {
      if(!HasSideEffect(inst))
      {

        int size = inst->Getuselist().size();
        for(int i = 0; i < size; i++)
        {   // 遍历要删除指令的操作数，把操作数全部移动进WorkList中
          Operand it = inst->GetOperand(i);
          WorkList.push_back(it);
        }
        RemoveInst(inst);
      }
    }
  }

  while(!WorkList.empty())
  {
    User* new_user = ((User*)(WorkList[0]));
    if(!HasSideEffect(new_user))
    {
        int size = new_user->Getuselist().size();
        for(int i = 0; i < size; i++)
        {   // 遍历要删除指令的操作数，把操作数全部移动进WorkList中
          Operand it = new_user->GetOperand(i);
          WorkList.push_back(it);
        }
        delete WorkList[0];
    }

    WorkList.erase(WorkList.begin());
  }

  return true;
}

bool DCE::HasSideEffect(User *inst) {
  /*
  要求：
  1. 判断一个指令是否有副作用
  2. 如果有副作用, 返回true, 否则返回false
  */
  // User u;
  // auto p = &u;
  // p->IsTerminateInst();
  // u.IsTerminateInst();
  // using UsePtr=std::unique_ptr<Use>;
  // auto UseList = inst.
  // UseList.empty()

  // printf("hello");
  UserList UserLt = inst->GetUserlist();
  if(UserLt.is_empty())
  {
      if(inst->IsTerminateInst())
          return true;
      if(inst->IsCondInst())
          return true;
      if(inst->IsUncondInst())
          return true;

      return false;
  }

  return true;
  /*
  思考：
  1. 什么情况下一条指令会有副作用？
  我猜测当一条指令产生的值，在下面会用到，即这个指令存在副作用

  2. 如何判断一条指令是否有副作用？
  */
}

void DCE::RemoveInst(User *inst) 
{
  /*
  要求：
  正确删除一条指令, 并使用User类中正确的函数维护关系。
  */

      // std::cout<<"remove "<<std::endl;

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
      for(int i = 0; i < size; i++)
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
      // inst->Getu
      // int size = inst->GetUserListSize();
      // for(int i =0; i<size;i++)
      // {
      //   auto List = inst->GetOperand(i)->GetUserlist();
      //   for(auto e:List)
      //   {
      //      e->RemoveFromUserList(inst);
      //   }
      // }
      inst->EraseFromParent();
      delete inst;
  /*
  思考：
  1. 如何删除一条指令？
  2. 如何维护一条指令的Use\User\Usee关系?
  */
}