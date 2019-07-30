#include <napi.h>
#include <uv.h>
using namespace Napi;

Function callback;

void on_connect(uv_connect_t* req, int status) {

}

Value Test(const CallbackInfo& info) {
    callback = info[0].As<Function>();
    auto loop = uv_default_loop();

    uv_tcp_t* socket = (uv_tcp_t*)malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);

    uv_connect_t* connect = (uv_connect_t*)malloc(sizeof(uv_connect_t));

    struct sockaddr_in dest;
    uv_ip4_addr("192.168.178.28", 8080, &dest);

uv_tcp_connect(connect, socket, (const struct sockaddr*)&dest, on_connect);
    return info.Env().Undefined();
}

Object Init(Env env, Object exports) {
    exports.Set(String::New(env, "test"), Function::New(env, Test));
    return exports;
}

const char* extension = "libuv";
NODE_API_MODULE(extension, Init)