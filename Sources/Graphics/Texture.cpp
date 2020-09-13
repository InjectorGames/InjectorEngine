#include "Injector/Graphics/Texture.hpp"

namespace Injector
{
    Texture::Texture(
        TextureType _type,
        IntVector3 _size,
        TextureFormat _format,
        TextureFilter _minFilter,
        TextureFilter _magFilter,
        TextureWrap _wrapU,
        TextureWrap _wrapV,
        TextureWrap _wrapW,
        bool _useMipmap) :
        type(_type),
        size(_size),
        format(_format),
        minFilter(_minFilter),
        magFilter(_magFilter),
        wrapU(_wrapU),
        wrapV(_wrapV),
        wrapW(_wrapW),
        useMipmap(_useMipmap)
    {}
    Texture::~Texture()
    {}

    TextureType Texture::getType() const noexcept
    {
        return type;
    }
    const IntVector3& Texture::getSize() const noexcept
    {
        return size;
    }
    TextureFilter Texture::getMinFilter() const noexcept
    {
        return minFilter;
    }
    TextureFilter Texture::getMagFilter() const noexcept
    {
        return magFilter;
    }
    TextureWrap Texture::getWrapU() const noexcept
    {
        return wrapU;
    }
    TextureWrap Texture::getWrapV() const noexcept
    {
        return wrapV;
    }
    TextureWrap Texture::getWrapW() const noexcept
    {
        return wrapW;
    }
    bool Texture::isUseMipmap() const noexcept
    {
        return useMipmap;
    }
}
