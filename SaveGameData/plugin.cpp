#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

struct SaveGameData {
    int SaveGameCount = 0;
};

namespace {
    SaveGameData SaveData;
}

void PrintSaveGameCount() {
    RE::ConsoleLog::GetSingleton()->Print(std::format("Save game count: {}", SaveData.SaveGameCount).c_str());
}

void OnSaveData(SKSE::SerializationInterface* serialization) {
    // Update the count
    SaveData.SaveGameCount++;

    // Save the SaveData to skse cosave

}

void OnLoadSaveData(SKSE::SerializationInterface* serialization) {
    // Load the SaveData from skse cosave

}

void OnRevertSaveData(SKSE::SerializationInterface* serialization) {
    SaveData.SaveGameCount = 0;
}

void InitializeSerialization() {
    auto* serialization = SKSE::GetSerializationInterface();
    serialization->SetUniqueID('MYID'); // Set this to a unique ID for your plugin
    serialization->SetSaveCallback(OnSaveData);
    serialization->SetLoadCallback(OnLoadSaveData);
    serialization->SetRevertCallback(OnRevertSaveData);
}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* message){
        if (message->type == SKSE::MessagingInterface::kDataLoaded) {
            InitializeSerialization();
        }
    });
    return true;
}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface*, SKSE::PluginInfo* info) {
    info->infoVersion = SKSE::PluginInfo::kVersion;
    info->name = "HelloSkse";
    info->version = 1;
    return true;
}

extern "C" __declspec(dllexport) constinit auto SKSEPlugin_Version = [](){
    SKSE::PluginVersionData version;
    version.PluginName("HelloSkse");
    version.PluginVersion({ 0, 0, 1 });
    version.CompatibleVersions({ SKSE::RUNTIME_LATEST });
    return version;
}();
