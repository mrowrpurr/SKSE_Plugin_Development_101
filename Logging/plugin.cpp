#include <SKSE/SKSE.h>
#include <RE/C/ConsoleLog.h>

#include <Windows.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>

extern "C" __declspec(dllexport) constinit auto SKSEPlugin_Version = [](){
    SKSE::PluginVersionData version;
    version.PluginName("HelloLogging");
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

void SetupLogging() {
    auto path = SKSE::log::log_directory();
    if (!path) {
        SKSE::stl::report_and_fail("SKSE log directory not found.");
    }
    *path /= std::format("{}.log", SKSEPlugin_Version.pluginName);

    std::shared_ptr<spdlog::logger> log;
    if (IsDebuggerPresent()) {
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::msvc_sink_mt>());
    } else {
        log = std::make_shared<spdlog::logger>("Global", std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true));
    }
    log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::trace);

    spdlog::set_default_logger(std::move(log));
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [%t] [%s:%#] %v");
}

extern "C" __declspec(dllexport) bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* skse) {
    SetupLogging();
    SKSE::log::info("Loading plugin!");
    SKSE::log::info("Loading plugin!");
    SKSE::log::info("Loading plugin!");
    SKSE::log::info("Loading plugin!");
    SKSE::log::info("Loading plugin!");
    SKSE::log::info("Loading plugin!");

    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        SKSE::log::info("Loading plugin!");
        if (event->type == SKSE::MessagingInterface::kPostLoad) {
            SKSE::log::info("SKSE plugins loaded!");
        } else if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            SKSE::log::info("All data loaded!");
        } else if (event->type == SKSE::MessagingInterface::kNewGame) {
            SKSE::log::info("New game.");
        } else if (event->type == SKSE::MessagingInterface::kSaveGame) {
            SKSE::log::info("Save game.");
        } else if (event->type == SKSE::MessagingInterface::kPreLoadGame) {
            SKSE::log::info("Before a load game is loaded");
        } else if (event->type == SKSE::MessagingInterface::kPostLoadGame) {
            SKSE::log::info("After a load game has been loaded");
        }
    });
    return true;
}
