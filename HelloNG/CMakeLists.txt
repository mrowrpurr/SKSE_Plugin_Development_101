cmake_minimum_required(VERSION 3.21)

project(HelloCpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CommonLibSSE CONFIG REQUIRED)

target_precompile_headers(
	"${PROJECT_NAME}"
	PRIVATE
		PCH.h
)

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES PCH.h Logging.h Plugin.cpp)

set(DLL_FOLDER "C:\\Users\\mrowr\\Dropbox\\Skyrim\\Purrrect Modlist\\Mods\\[Mrowr Purr] SKSE Dev\\SKSE\\Plugins")

add_custom_command(
	TARGET "${PROJECT_NAME}"
	POST_BUILD
	COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${DLL_FOLDER}/${PROJECT_NAME}.dll"
	VERBATIM
)
