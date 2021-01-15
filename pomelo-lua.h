#include <napi.h>
#include <lua.hpp>
class PomeloLua: public Napi::ObjectWrap<PomeloLua> {
public:
    static Napi::Object init(Napi::Env env, Napi::Object exports);
    PomeloLua(const Napi::CallbackInfo &info);
    ~PomeloLua();
private:
    static Napi::FunctionReference m_constructor;
    lua_State* m_luaState;
    Napi::Value DoString(const Napi::CallbackInfo& info);
    // Napi::Value Status(const Napi::CallbackInfo& info);
    // Napi::Value CallGlobalFunction(const Napi::CallbackInfo& info);
    Napi::Value Close(const Napi::CallbackInfo &info);
};