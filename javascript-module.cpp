// A stable Node-API library containing the complete bundled module program.
// The implementation remains JavaScript; the installed entry is a real native
// library, without a second loose copy of the executable program.
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#define EXPORT __declspec(dllexport)
#else
#include <dlfcn.h>
#define EXPORT __attribute__((visibility("default")))
#endif
#include "javascript-program.inc"

using Env = void*;
using Value = void*;
using CreateString = int (*)(Env, const char*, size_t, Value*);
using RunScript = int (*)(Env, Value, Value*);
namespace {
void* api(const char* name) {
#ifdef _WIN32
  return reinterpret_cast<void*>(GetProcAddress(GetModuleHandleW(nullptr), name));
#else
  return dlsym(RTLD_DEFAULT, name);
#endif
}
}
extern "C" EXPORT int32_t node_api_module_get_api_version_v1() { return 8; }
extern "C" EXPORT Value napi_register_module_v1(Env env, Value) {
  const auto create = reinterpret_cast<CreateString>(api("napi_create_string_utf8"));
  const auto run = reinterpret_cast<RunScript>(api("napi_run_script"));
  if (!create || !run) return nullptr;
  Value source = nullptr, wrapper = nullptr;
  if (create(env, program, sizeof(program) - 1, &source) != 0 || run(env, source, &wrapper) != 0) return nullptr;
  return wrapper;
}
