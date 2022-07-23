#include "core/type/instanceOf.hpp"
#include "core/opaquePointer.hpp"
#include "imgui/convert.hpp"
#include "texture.hpp"

#include <memory>

#include <fmt/format.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

using namespace core;
using namespace core::type::convert;
using namespace imgui;

Napi::FunctionReference Texture::m_ctor;

Napi::Object Texture::initialize(Napi::Env env, Napi::Object exports) {
    constexpr const char* className = "Texture";
    const auto class_ = DefineClass(env, className, {
        InstanceAccessor<&Texture::getTypeId>("typeId"),
        InstanceAccessor<&Texture::toDebugString>("debugString"),
        InstanceMethod<&Texture::ref>("ref"),
        InstanceMethod<&Texture::unref>("unref"),

        InstanceMethod<&Texture::equals>("equals"),
        InstanceMethod<&Texture::loadFromFile>("loadFromFile"),
        InstanceMethod<&Texture::loadFromMemory>("loadFromMemory"),
        InstanceMethod<&Texture::loadFromRGBA32>("loadFromRGBA32"),
        InstanceAccessor<&Texture::getId>("id"),
        InstanceAccessor<&Texture::getSize>("size")
    });

    m_ctor = Napi::Persistent(class_);
    m_ctor.SuppressDestruct();

    exports.Set(className, class_);
    return exports;
}

Texture::Texture(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Texture>{ info } {
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load(int width, int height, void* pixels) {
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_width = width;
    m_height = height;
}

Napi::Value Texture::getTypeId(const Napi::CallbackInfo& info) {
    return core::type::fromTypeId<Texture>(info.Env());
}

Napi::Value Texture::toDebugString(const Napi::CallbackInfo& info) {
    return fromStrUtf8(info.Env(), fmt::format("Texture (id={}; width={}; height={})", m_id, m_width, m_height));
}

Napi::Value Texture::ref(const Napi::CallbackInfo& info) {
    return fromU32(info.Env(), Ref());
}

Napi::Value Texture::unref(const Napi::CallbackInfo& info) {
    return fromU32(info.Env(), Unref());
}

Napi::Value Texture::equals(const Napi::CallbackInfo& info) {
    return fromBool(info.Env(), this == Texture::unwrap(info[0]));
}

Napi::Value Texture::loadFromFile(const Napi::CallbackInfo& info) {
    const auto filename = asStrUtf8(info[0]);
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{ IMG_Load(filename.c_str()), SDL_FreeSurface };
    if (!surface) throw Napi::Error::New(info.Env(), fmt::format("failed to load texture from file `{}`: {}", filename, IMG_GetError()));
    surface.reset(SDL_ConvertSurfaceFormat(surface.get(), SDL_PIXELFORMAT_RGBA32, 0));
    load(surface->w, surface->h, surface->pixels);
    return info.Env().Undefined();
}

Napi::Value Texture::loadFromMemory(const Napi::CallbackInfo& info) {
    auto data = info[0].As<Napi::Uint8Array>();
    std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{ IMG_Load_RW(SDL_RWFromMem(data.Data(), data.ByteLength()), true), SDL_FreeSurface };
    if (!surface) throw Napi::Error::New(info.Env(), fmt::format("failed to load texture from memory: {}", IMG_GetError()));
    surface.reset(SDL_ConvertSurfaceFormat(surface.get(), SDL_PIXELFORMAT_RGBA32, 0));
    load(surface->w, surface->h, surface->pixels);
    return info.Env().Undefined();
}

Napi::Value Texture::loadFromRGBA32(const Napi::CallbackInfo& info) {
    load(/* width */ asS32(info[0]),
         /* height */ asS32(info[1]),
         /* pixels */ info[2].As<Napi::Uint8Array>().Data());
    return info.Env().Undefined();
}

Napi::Value Texture::getId(const Napi::CallbackInfo& info) {
    void* ptr;
    std::memcpy(&ptr, &m_id, sizeof m_id);
    return OpaquePointer::create(info.Env(), ptr);
}

Napi::Value Texture::getSize(const Napi::CallbackInfo& info) {
    return fromVec2(info.Env(), m_width, m_height);
}
