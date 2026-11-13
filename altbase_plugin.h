#ifndef ALTBASE_PLUGIN_H
#define ALTBASE_PLUGIN_H
#include <stdint.h>
#ifdef _WIN32
#define ALTBASE_PLUGIN_EXPORT __declspec(dllexport)
#define ALTBASE_PLUGIN_CALL __cdecl
#else
#define ALTBASE_PLUGIN_EXPORT __attribute__((visibility("default")))
#define ALTBASE_PLUGIN_CALL
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* UTF-8 JSON; no C++ objects cross the ABI. All calls are serialized.
 * The manifest is static. request returns plugin-owned memory, freed by free.
 * Each response is {"ok":true,"result":...} or {"ok":false,"error":"..."}.
 * Exceptions MUST NOT cross this boundary. ALTBASE_PLUGIN_DATA_DIR is a private
 * persistent directory provided by the host. Never write secrets to logs.
 */
ALTBASE_PLUGIN_EXPORT uint32_t ALTBASE_PLUGIN_CALL altbase_plugin_abi_version(void);
ALTBASE_PLUGIN_EXPORT const char* ALTBASE_PLUGIN_CALL altbase_plugin_manifest(void);
ALTBASE_PLUGIN_EXPORT char* ALTBASE_PLUGIN_CALL altbase_plugin_request(const char* method, const char* params_json);
ALTBASE_PLUGIN_EXPORT void ALTBASE_PLUGIN_CALL altbase_plugin_free(char* response);
#ifdef __cplusplus
}
#endif
#endif
