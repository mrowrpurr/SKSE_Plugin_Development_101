#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

// You do not need to understand this bit to make SKSE plugins :)
template <class... Types>
void PrintToConsole(const std::string text, const Types&... args) {
    RE::ConsoleLog::GetSingleton()->Print(std::format(text, args...).c_str());
};

// 
std::vector<RE::FormID> HitAggressors;

//
std::unordered_map<RE::FormID, int> HitCountPerAggressor;

void Sample() {

    bool b = false;
    int i = 420;
    float f = 6.9;
    std::string s = "Hello, world!";

    auto a = false;
    auto b = 420;
    auto c = 6.9;
    auto d = "Hello, world!";

    auto* console = RE::ConsoleLog::GetSingleton();

    auto output = std::format("{} {} {} {}", a, b, c, d);

    console->Print(output.c_str());

    // bool, int, float, std::string
    // Print to console including std::format

    // Array
    // OnHit Form IDs of every aggressor that's hit the player character
    // vector

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
