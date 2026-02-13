#include <set>

#include <amx/amx.h>
#include <plugincommon.h>

#include "common.hpp"
#include "natives.hpp"

logprintf_t logprintf;

extern "C" AMX_NATIVE_INFO amx_Natives[] = {
    {"RequestsClient", Natives::RequestsClient},
    {"RequestHeaders", Natives::RequestHeaders},
    {"Request", Natives::Request},
    {"RequestJSON", Natives::RequestJSON},

    {"WebSocketClient", Natives::WebSocketClient},
    {"WebSocketSend", Natives::WebSocketSend},
    {"JsonWebSocketClient", Natives::JsonWebSocketClient},
    {"JsonWebSocketSend", Natives::JsonWebSocketSend},

    {0, 0}};

std::set<AMX *> amx_List;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

    return true;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
    amx_List.insert(amx);
    return amx_Register(amx, amx_Natives, -1);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick()
{
    Natives::processTick(amx_List);
}

PLUGIN_EXPORT int PLUGIN_CALL Unload()
{
    return 1;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
    amx_List.erase(amx);
    return 1;
}
