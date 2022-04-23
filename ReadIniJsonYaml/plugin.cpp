#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

template <class... Types>
void PrintToConsole(const std::string text, const Types&... args) {
    RE::ConsoleLog::GetSingleton()->Print(std::format(text, args...).c_str());
};

// .ini
#include <SimpleIni.h>

// .json
#include <json/json.h>
#include <fstream>

// .yaml
#include <yaml-cpp/yaml.h>

// https://stackoverflow.com/a/40903508
std::string ReadTextFile(const std::filesystem::path& path) {
    // Open the stream to 'lock' the file.
    std::ifstream f(path, std::ios::in | std::ios::binary);

    // Obtain the size of the file.
    const auto sz = std::filesystem::file_size(path);

    // Create a buffer.
    std::string result(sz, '\0');

    // Read the whole file into the buffer.
    f.read(result.data(), sz);

    return result;
}

void ReadIni() {
    PrintToConsole("Read example.ini");
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
    PrintToConsole("Read example.json");
    std::ifstream jsonFile("Data/example.json", std::ifstream::binary);
    Json::Value root;
    jsonFile >> root;
    auto greeting = root.get("greeting", "").asString();
    auto someNumber = root.get("someNumber", 0.0).asFloat();
    PrintToConsole("greeting: {}", greeting);
    PrintToConsole("someNumber: {}", someNumber);
}

void ReadYaml() {
    PrintToConsole("Read example.yaml");
    auto yaml = YAML::Load(ReadTextFile("Data/example.yaml"));
    auto greeting = yaml["greeting"].Scalar();
    // 'someNumber' will also be returned as a string.
    // You need to parse/cast values from strings when reading from .yaml
    auto someNumber = yaml["someNumber"].Scalar();
    PrintToConsole("greeting: {}", greeting);
    PrintToConsole("someNumber: {}", someNumber);
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
