#include "includes/3rd-party/lua/LuaInterprete.hpp"


LuaInterpreter::LuaInterpreter(){
    L = luaL_newstate();
    luaL_openlibs(L);
}


void LuaInterpreter::init_script(const char * filepath){
	int ret = luaL_dofile(L, filepath);
	if (ret){
		throw std::runtime_error("Error en el script: " + std::string(lua_tostring(L, ret)));
	}
}

void LuaInterpreter::call_function(const char * fname, int params, int outparams){
  lua_call(L, params, outparams);
}

void LuaInterpreter::get_function_name(const char * fname){
	lua_getglobal(L, fname);
}



void LuaInterpreter::operator<<(const std::string &str){
	lua_pushlstring(L, str.c_str(), str.size());
}

void LuaInterpreter::operator<<(int num){
		lua_pushnumber(L, num);
}

void LuaInterpreter::operator<<(float num){
		lua_pushnumber(L, num);
}

void LuaInterpreter::operator<<(bool b){
		lua_pushboolean(L, b);
}

LuaInterpreter::~LuaInterpreter(){
    if(L){
    	lua_close(L);
	}
}