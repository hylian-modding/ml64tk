#include "core/largeInteger.hpp"
#include "core/opaquePointer.hpp"
#include "gui/gui.hpp"
#include "imgui/imgui.hpp"
#include "appWindow.hpp"
#include "texture.hpp"

#include <fmt/format.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#ifdef _WIN32
#include <shellscalingapi.h>
#pragma comment(lib, "shcore.lib")

static struct AutoDpiAware {
    AutoDpiAware() {
        if (SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE) != S_OK)
            SetProcessDpiAwareness(PROCESS_SYSTEM_DPI_AWARE);
    }
} autoDpiAware;

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
extern "C" __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
#else
#include <gtk/gtk.h>
namespace gui::theme { void initialize(Napi::Env env); }
#endif

static void initialize(Napi::Env env) {
    SDL_SetMainReady();
    SDL_SetHint(SDL_HINT_APP_NAME, "ml64tk");
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw Napi::Error::New(env, fmt::format("failed to initialize sdl2: {}", SDL_GetError()));
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        throw Napi::Error::New(env, fmt::format("failed to initialize sdl2 image: {}", IMG_GetError()));
    if (TTF_Init() != 0)
        throw Napi::Error::New(env, fmt::format("failed to initialize sdl2 ttf: {}", TTF_GetError()));
    SDL_DisableScreenSaver();
#ifndef _WIN32
    if (setenv("GSK_RENDERER", "cairo", true) != 0)
        throw Napi::Error::New(env, "failed to override GSK_RENDERER environment variable");
    if (!gtk_init_check())
        throw Napi::Error::New(env, "failed to initialize gtk");
    gui::theme::initialize(env);
#endif
}

static void deinitialize() {
    SDL_EnableScreenSaver();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

Napi::Object initModule(Napi::Env env, Napi::Object exports) {
    initialize(env);
    std::atexit(deinitialize);

    core::SignedLargeInteger::initialize(env, exports);
    core::UnsignedLargeInteger::initialize(env, exports);
    core::OpaquePointer::initialize(env, exports);
    exports.Set("ImGui", imgui::initialize(env, Napi::Object::New(env)));
    exports.Set("Gui", gui::initialize(env, Napi::Object::New(env)));
    AppWindow::initialize(env, exports);
    Texture::initialize(env, exports);

    return exports;
}

NODE_API_MODULE(ml64tkModule, initModule)
