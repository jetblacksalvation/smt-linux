#include "Common.hpp"
//static OnInit::InitList = {};
OnInit::OnInit(OnInitFuncT funcToAdd) 
{
	InitList.push_back(funcToAdd);
	//InitList = {};
}

OnInit::OnInit() 
{
	//InitList = {};

}
void OnInit::StartInit() 
{
	for(auto ptr : this->InitList)
	{
		ptr(this);
	}
}
