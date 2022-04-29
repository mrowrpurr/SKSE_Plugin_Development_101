#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

extern "C" __declspec(dllexport) constinit auto SKSEPlugin_Version = [](){
    SKSE::PluginVersionData version;
    version.PluginName("HelloSKSE");
    version.PluginVersion({ 0, 0, 1 });
    version.CompatibleVersions({ SKSE::RUNTIME_LATEST });
    version.UsesAddressLibrary(true);
    return version;
}();

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface*, SKSE::PluginInfo* info) {
    info->name = SKSEPlugin_Version.pluginName;
    info->version = SKSEPlugin_Version.pluginVersion;
    info->infoVersion = SKSE::PluginInfo::kVersion;
    return true;
}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kPostLoad) {
            // SKSE plugins loaded. The console is not available for printing messages until kDataLoaded
        } else if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            RE::ConsoleLog::GetSingleton()->Print("Hello, SKSE! Main Menu & all plugins loaded.");
        } else if (event->type == SKSE::MessagingInterface::kNewGame) {
            RE::ConsoleLog::GetSingleton()->Print("New game.");
        } else if (event->type == SKSE::MessagingInterface::kSaveGame) {
            RE::ConsoleLog::GetSingleton()->Print("Save game.");
        } else if (event->type == SKSE::MessagingInterface::kPreLoadGame) {
            RE::ConsoleLog::GetSingleton()->Print("Before a load game is loaded");
        } else if (event->type == SKSE::MessagingInterface::kPostLoadGame) {
            RE::ConsoleLog::GetSingleton()->Print("After a load game has been loaded");
        }
    });
    return true;
}
