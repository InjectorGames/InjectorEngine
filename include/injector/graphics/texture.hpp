#pragma once
#include "Injector/Graphics/TextureType.hpp"
#include "Injector/Graphics/TextureWrap.hpp"
#include "Injector/Graphics/TextureFormat.hpp"
#include "Injector/Graphics/TextureFilter.hpp"
#include "Injector/Mathematics/IntVector3.hpp"

namespace Injector
{
    class Texture
    {
    protected:
        TextureType type;
        IntVector3 size;
        TextureFormat format;
        TextureFilter minFilter;
        TextureFilter magFilter;
        TextureWrap wrapU;
        TextureWrap wrapV;
        TextureWrap wrapW;
        bool useMipmap;
    public:
        Texture(TextureType type,
            IntVector3 size,
            TextureFormat format,
            TextureFilter minFilter,
            TextureFilter magFilter,
            TextureWrap wrapU,
            TextureWrap wrapV,
            TextureWrap wrapW,
            bool useMipmap);
        virtual ~Texture();

        TextureType getType() const noexcept;
        const IntVector3& getSize() const noexcept;
        TextureFormat getFormat() const noexcept;
        TextureFilter getMinFilter() const noexcept;
        TextureFilter getMagFilter() const noexcept;
        TextureWrap getWrapU() const noexcept;
        TextureWrap getWrapV() const noexcept;
        TextureWrap getWrapW() const noexcept;
        bool isUseMipmap() const noexcept;
    };
}
