#ifndef FALCONENGINE_LUAVIRTUALMACHINE_H
#define FALCONENGINE_LUAVIRTUALMACHINE_H

#include "FalconLuaBind.h"

namespace falcon
{

	class LuaVirtualMachine
	{
	public:
		LuaVirtualMachine();
		virtual ~LuaVirtualMachine();

		int load();
	private:
		LuaVirtualMachine(const LuaVirtualMachine& t);
		LuaVirtualMachine& operator=(const LuaVirtualMachine& t);
	};
}

static void stackDump (lua_State* state);
#endif //FALCONENGINE_LUAVIRTUALMACHINE_H