#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <REL/Relocation.h>

//
#include <RE/C/ConsoleLog.h>

//
#include <RE/T/TESHitEvent.h>

//
#include <RE/S/ScriptEventSourceHolder.h>

// You do not need to understand this bit to make SKSE plugins :)
template <class... Types>
void PrintToConsole(const std::string text, const Types&... args) {
    RE::ConsoleLog::GetSingleton()->Print(std::format(text, args...).c_str());
};

//
class OnTESHitEventSink : public RE::BSTEventSink<RE::TESHitEvent> {
    std::function<void(const RE::TESHitEvent* event)> _eventCallback;

public:
    explicit OnTESHitEventSink(std::function<void(const RE::TESHitEvent* event)> eventCallback) : _eventCallback(std::move(eventCallback)) {}

    RE::BSEventNotifyControl ProcessEvent(const RE::TESHitEvent* event, RE::BSTEventSource<RE::TESHitEvent>*) override {
        _eventCallback(event);
        return RE::BSEventNotifyControl::kContinue;
    }
};

// 
std::vector<RE::TESObjectREFR*> HitAggressors;

//
std::unordered_map<RE::FormID, int> HitCountPerAggressor;

static void ListenForHitEvents() {
    auto* scriptEvents = RE::ScriptEventSourceHolder::GetSingleton();
    scriptEvents->AddEventSink<RE::TESHitEvent>(new OnTESHitEventSink([](const RE::TESHitEvent* event){
        PrintToConsole("Hit!");
        if (event->cause) {
            HitAggressors.emplace_back(event->cause.get());
            PrintToConsole("{} hit {}",
                event->cause.get()->GetBaseObject()->GetName(),
                event->target.get()->GetBaseObject()->GetName());
        }
    }));
}

void Sample() {

    bool b = false;
    int i = 420;
    float f = 6.9;
    std::string s = "Hello, world!";

    auto bAuto = false;
    auto iAuto = 420;
    auto dAuto = 6.9;
    auto cAuto = "Hello, world!";

    auto* console = RE::ConsoleLog::GetSingleton();

    auto output = std::format("{} {} {} {}", bAuto, iAuto, dAuto, cAuto);

    console->Print(output.c_str());

    // bool, int, float, std::string
    // Print to console including std::format

    // Array
    // OnHit Form IDs of every aggressor that's hit the player character
    // vector
    ListenForHitEvents();

    // Hash
    // Loop thru Forms, build Hash of incrementing count indexed by name
    // unordered_map


}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            Sample();
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
