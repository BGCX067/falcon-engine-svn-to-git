#include "stdafx.h"
#include "LuaVirtualMachine.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "BaseApp.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Mesh.h"
#include "Scene.h"
#include "DiffuseTextureShader.h"
#include "BasicColorShader.h"
#include "SkyBox.h"
#include "FalconMath.h"
#include "vmath.h"
#include "InputState.h"
#include "FalconLuaBind.h"
#include "FalconBulletBind.h"
#include "PhysicsBox.h"
#include "Button.h"
#include "Element2D.h"
#include "Menu.h"
#include "Callable.h"
#include "Element2DManager.h"


//Debug Class
class DebugPrinter
{
public:

	DebugPrinter(){};
	~DebugPrinter(){};

	static luabind::scope Register()
	{
		return 
			luabind::class_<DebugPrinter>("DebugPrinter")
			.def(luabind::constructor<>())
			.def("printInt", &DebugPrinter::printInt)
			.def("printFloat", &DebugPrinter::printFloat)
			.def("printString", &DebugPrinter::printString)
			.def("printVector3", &DebugPrinter::printVector3)
			.def("printBool", &DebugPrinter::printBool)
			.def("printMesh", &DebugPrinter::printMesh);
	}

	void printInt(const unsigned int& debugline)
	{
		printFloat((float)debugline);
	}

	void printFloat(const float& debugline)
	{
		std::stringstream buffer;
		buffer << debugline << "\n";
		OutputDebugString(buffer.str().c_str());
	}

	void printString(const std::string& debugline)
	{
		std::stringstream buffer;
		buffer << debugline << "\n";
		OutputDebugString(buffer.str().c_str());
	}

	void printVector3(const falcon::Vec3& debugline)
	{
		std::stringstream buffer;
		buffer << "Vector3 = {" << debugline.x << "," << debugline.y << "," << debugline.z << "}\n";
		OutputDebugString(buffer.str().c_str());
	}

	void printBool(const bool debugline)
	{
		std::stringstream buffer;
		buffer << debugline << "\n";
		OutputDebugString(buffer.str().c_str());
	}

	void printMesh(falcon::Mesh* debugline)
	{
		std::stringstream buffer;
		buffer << "MeshPtr = " << debugline << "\n";
		OutputDebugString(buffer.str().c_str());
	}
};

falcon::LuaVirtualMachine::LuaVirtualMachine()
{
	LogManager::Create();
}

falcon::LuaVirtualMachine::~LuaVirtualMachine()
{
	LogManager::Destroy();
}

int falcon::LuaVirtualMachine::load()
{
	using namespace luabind;
	lua_State* luaState = lua_open();

   // open the new state with luabind
   luabind::open(luaState);

   // import all of the functions from lua in our luastate
   luaL_openlibs(luaState);

   // export the functions we want
	luabind::module(luaState)
    [
		BaseApp::Register(),
		DebugPrinter::Register(),
		Mesh::Register(),
		Scene::Register(),
		GameObjectWrapper::Register(),
		Shader::Register(),
		ShaderData::Register(),
		ResourceManager::Register(),
		InputState::Register(),
		SkyBox::Register(),
		PhysicsBox::Register(),
		Element2D::Register(),
		Button::Register(),
		CallableWrapper::Register(),

		// Registration of some math templates
		class_<Vector3<float> >("Vec3")
		.def(constructor<float, float, float>())
		.property("x", &Vector3<float>::x, &Vector3<float>::x)
		.property("y", &Vector3<float>::y, &Vector3<float>::y)
		.property("z", &Vector3<float>::z, &Vector3<float>::z)
		.def(self + Vec3()),

		class_<Vec2>("Vec2")
		.def(constructor<float, float>()),

		class_<Matrix3<float> >("Matrix3")
		.def(constructor<>())
		.scope
		[
			def("createRotationAroundAxis", &Matrix3<float>::createRotationAroundAxis)
		]
    ];

   // Open our external .lua file and run it
	int status(luaL_loadfile(luaState, "./Game/Game.lua"));

	if( status == 0)
	{
		int returnstatus;
		returnstatus = lua_pcall(luaState, 0, LUA_MULTRET, 0);

		if (returnstatus == LUA_ERRRUN)
		{
			OutputDebugString("Serializing Dump!");
			stackDump(luaState);
	
			std::stringstream buffer;
			buffer << "ERROR (Dump created @ Dump/dump.txt) \n\n" << lua_tostring(luaState, -1); 
			LOG(LOG_Error, buffer.str());
		}
	}
	// close the lua state
	OutputDebugString(" \n Closing LuaState! \n");
	lua_close(luaState);
	return status;
}

static void stackDump (lua_State* state)
{
	std::ofstream dump;
	dump.open("Dump/dump.txt");

	int i;
	int top = lua_gettop(state);
	for (i = 1; i <= top; ++i)
	{
		// Repeat for each level
		int t = lua_type(state, i);
		switch (t)
		{
		case LUA_TSTRING:
			// Strings
			dump << lua_tostring(state, i);
			break;
		case LUA_TBOOLEAN:
			// Booleans
			dump << (lua_toboolean(state, i) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			// Numbers
			dump << lua_tonumber(state, i);
			break;
		default:
			// Other values
			dump << lua_typename(state, t);
			break;
		}

		dump << "\n";
	}
	dump.close();
}