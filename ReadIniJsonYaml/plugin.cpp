#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

template <class... Types>
void PrintToConsole(const std::string text, const Types&... args) {
    RE::ConsoleLog::GetSingleton()->Print(std::format(text, args...).c_str());
};

// .ini
#include <SimpleIni.h>

// .json

// .yaml

void ReadIni() {
    auto iniPath = "Data/example.ini";
    CSimpleIni ini;
    auto loadError = ini.LoadFile(iniPath);
    if (loadError == SI_OK) {
        auto bFoo1 = ini.GetBoolValue("ExampleSection1", "bFoo", false);
        auto fNum = ini.GetDoubleValue("ExampleSection1", "fNum", 0.0);
        auto bFoo2 = ini.GetBoolValue("ExampleSection2", "bFoo", true);
        auto sHello = ini.GetValue("ExampleSection2", "sHello", "");
        PrintToConsole("[ExampleSection1]");
        PrintToConsole("bFoo={}", bFoo1);
        PrintToConsole("fNum={}", fNum);
        PrintToConsole("[ExampleSection2]");
        PrintToConsole("bFoo={}", bFoo2);
        PrintToConsole("sHello={}", sHello);
    } else {
        PrintToConsole("Could not read .ini at path '{}'", iniPath);
    }
}

void ReadJson() {

}

void ReadYaml() {

}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            PrintToConsole("Data Loaded.");
            ReadIni();
            ReadJson();
            ReadYaml();
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
