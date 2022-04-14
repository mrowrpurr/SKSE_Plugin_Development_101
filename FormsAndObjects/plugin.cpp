#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>
#include <RE/P/PlayerCharacter.h>
#include <RE/T/TES.h>
#include <RE/T/TES.h>

void PrintOutObjectReferenceInformation(RE::TESObjectREFR& ref) {
    auto name = ref.GetName();
    if (std::string(name).empty()) {
        name = ref.GetBaseObject()->GetName();
        if (std::string(name).empty()) {
            name = ref.GetBaseObject()->GetObjectTypeName();
        }
    }
    if (! std::string(name).empty()) {
        RE::ConsoleLog::GetSingleton()->Print(std::format("Nearby Object: 0x{:x} '{}'", ref.formID, name).c_str());
    }
}

[[noreturn]] void ListenForNearbyObjects(const std::function<void(RE::TESObjectREFR& ref)>& objectCallback, float radiusUnits = 169, int intervalMs = 4000) {
    auto* playerRef = RE::PlayerCharacter::GetSingleton()->AsReference();
    while (true) {
        try {
            RE::TES::GetSingleton()->ForEachReferenceInRange(playerRef, radiusUnits, [objectCallback](RE::TESObjectREFR& ref) {
                try {
                    objectCallback(ref);
                } catch (...) {
                    RE::ConsoleLog::GetSingleton()->Print("Could not invoke object callback");
                }
                return true;
            });
        } catch (...) {
            RE::ConsoleLog::GetSingleton()->Print("Could not get nearby objects");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
    }
}

void OnNearbyObjectDetected(const std::function<void(RE::TESObjectREFR& ref)>& objectCallback) {
    std::thread objectListenerThread([objectCallback](){ ListenForNearbyObjects(objectCallback); });
    objectListenerThread.detach();
}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            OnNearbyObjectDetected([](RE::TESObjectREFR& ref){
                PrintOutObjectReferenceInformation(ref);
            });
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
