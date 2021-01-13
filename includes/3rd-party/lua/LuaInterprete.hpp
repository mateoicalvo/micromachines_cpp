#ifndef __LUA_INTERPRETER_H_
#define __LUA_INTERPRETER_H_

extern "C" {
  #include "lua.h"
  #include "lualib.h"
  #include "lauxlib.h"	
}

#include <exception>
#include <string>
#include <iostream>

class LuaInterpreter {
	private:
	    lua_State * L = NULL;
	public:
		LuaInterpreter();

		void init_script(const char * filepath);

		void call_function(const char * fname, int params, int outparams);
		
		void get_function_name(const char * fname);

		~LuaInterpreter();


/* push */
		void operator<<(const std::string &str);

		void operator<<(int num);

		void operator<<(float num);

		void operator<<(bool b);




/* get */
	    template<typename T>
	    T lua_get() {
	      return 0;
	    }


		template<typename T>
		T get() {
		  int stackSize = lua_gettop(L);
		  if (!stackSize){
		  	throw std::runtime_error("No hay elementos en el stack");
		  }
		  T element;
		  element = lua_get<T>();
		  lua_pop(L, -1);

		  return element;
		}
};


	    template <> 
		inline bool LuaInterpreter::lua_get<bool>() {
		    return (bool)lua_toboolean(L, -1);
		}

		template <> 
		inline float LuaInterpreter::lua_get<float>() {
		    return (float)lua_tonumber(L, -1);
		}

		template <>
		inline int LuaInterpreter::lua_get<int>() {
		    return (int)lua_tonumber(L, -1);
		}

		template <>
		inline std::string LuaInterpreter::lua_get<std::string>() {
		    return std::string(lua_tostring(L, -1));
		}

#endif