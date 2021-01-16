#include "pomelo-lua.h"
Napi::FunctionReference PomeloLua::m_constructor;
Napi::Object PomeloLua::init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    Napi::Function funcs = DefineClass(env,
                                       "PomeloLua",
                                       {
                                           InstanceMethod("close", &PomeloLua::Close),
                                           InstanceMethod("doString", &PomeloLua::DoString),
                                       });

    m_constructor = Napi::Persistent(funcs);
    m_constructor.SuppressDestruct();
    exports.Set("PomeloLua", funcs);
    return exports;
}

PomeloLua::PomeloLua(const Napi::CallbackInfo &info) : Napi::ObjectWrap<PomeloLua>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() < 1 || !info[0].IsNumber())
    {
        Napi::TypeError::New(env, "Arguments must be (value).")
            .ThrowAsJavaScriptException();
    }
    m_luaState = luaL_newstate();
}

Napi::Value PomeloLua::DoString(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() < 1 || !info[0].IsString())
    {
        Napi::TypeError::New(env, "Arguments must be (value).")
            .ThrowAsJavaScriptException();
    }
    lua_settop(m_luaState, 0);
    Napi::String str = info[0].ToString();
    int32_t ret = luaL_dostring(m_luaState, str.Utf8Value().c_str());
    if (ret)
    {
        char error[127];
        snprintf(error, 100, "lua exec error: %d", ret);
        Napi::TypeError::New(env, error)
            .ThrowAsJavaScriptException();
    }
    lua_getglobal(m_luaState, "result");
    const double result = lua_tonumber(m_luaState, -1);
    lua_getglobal(m_luaState, "message");
    const char *message = lua_tostring(m_luaState, -1);
    Napi::Object resp = Napi::Object::New(env);
    resp.Set("result", Napi::Number::New(env, result));
    Napi::String msg = Napi::String::New(env, message ? message : "");
    resp.Set("message", msg);
    return resp;
}

Napi::Value PomeloLua::Close(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    lua_close(m_luaState);
    return Napi::Boolean::New(env, true);
}

Napi::Object init_all(Napi::Env env, Napi::Object exports)
{
    return PomeloLua::init(env, exports);
}

PomeloLua::~PomeloLua()
{
}

NODE_API_MODULE(pomelolua, init_all)