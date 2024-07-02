#ifndef COMMON_SMT
#define COMMON_SMT

#include <functional>
#include <vector>

class OnInit
{
public:

	using OnInitFuncT = void(OnInit*);
	
	OnInit(OnInitFuncT);
	OnInit();
	void StartInit();

private:
	using OnInitFuncTWrapper = std::function<OnInitFuncT>;
	static inline std::vector<OnInitFuncTWrapper> InitList = {};

};

#endif // !COMMON_SMT