
#include <napi.h>
#include <lua.hpp>
static Napi::String Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  lua_State *L = luaL_newstate();//1.创建一个state
  lua_pushstring(L, "I am so cool~"); //2.入栈操作
  lua_tolstring str = lua_tostring(L,1);
  lua_close(L);
  return Napi::String::New(env, "Hello, world!");
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"),
              Napi::Function::New(env, Method));
  return exports;
}

NODE_API_MODULE(hello, Init)