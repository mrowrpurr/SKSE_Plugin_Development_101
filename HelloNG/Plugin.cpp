#include "Logging.h"

SKSEPluginLoad(const SKSE::LoadInterface* skse) {
    InitializeLog();
    logger::info("Well, hello there logger!");
    SKSE::Init(skse);
    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* event){
        if (event->type == SKSE::MessagingInterface::kPostLoad) {
            // SKSE plugins loaded!
            // The console is not available for printing messages until kDataLoaded
            // So do nothing here.
        } else if (event->type == SKSE::MessagingInterface::kDataLoaded) {
            RE::ConsoleLog::GetSingleton()->Print("Hello, SKSE! Main Menu & all plugins loaded. 3");
            logger::info("kDataLoaded!");
        } else if (event->type == SKSE::MessagingInterface::kNewGame) {
            RE::ConsoleLog::GetSingleton()->Print("New game.");
            logger::info("New game!");
        } else if (event->type == SKSE::MessagingInterface::kSaveGame) {
            RE::ConsoleLog::GetSingleton()->Print("Save game.");
        } else if (event->type == SKSE::MessagingInterface::kPreLoadGame) {
            RE::ConsoleLog::GetSingleton()->Print("Before a load game is loaded");
            logger::info("Game loading!");
        } else if (event->type == SKSE::MessagingInterface::kPostLoadGame) {
            RE::ConsoleLog::GetSingleton()->Print("After a load game has been loaded");
            logger::info("Game loaded!");
        }
    });
    return true;
}