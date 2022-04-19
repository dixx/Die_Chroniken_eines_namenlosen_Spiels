/*  \file Textures.h
 *  \brief Einfaches laden von Texturen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_TEXTURES_H
#define LEVIATHAN_VIDEO_TEXTURES_H

#include <string>
#include <unordered_map>

namespace irr {
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

namespace leviathan {
    namespace core {
        struct ILogger;
    }

    namespace video {
        /*  \class Textures
         *  \brief Einfaches laden von Texturen
         */
        class Textures {
        public:
            /*  \brief Konstruktor.
             *  \param videoDriver: Zeiger auf den Videotreiber der Graphic Engine
             *  \param logger: Instanz eines Loggers
             */
            Textures(irr::video::IVideoDriver* videoDriver, leviathan::core::ILogger& logger);

            ~Textures() = default;

            Textures() = delete;
            Textures(const Textures&) = delete;
            Textures(const Textures&&) = delete;
            Textures& operator=(const Textures&) = delete;
            Textures& operator=(const Textures&&) = delete;

            /*  \brief Lädt eine Textur, ohne weitere Features.
             *  \note Ist die Textur bereits geladen, wird sie nicht noch einmal geladen.
             *  \param fileName: Name und Pfad der Textur-Datei
             */
            irr::video::ITexture* get(const char* fileName);

            /*  \brief Lädt eine Textur und wandelt Magic Pink in Transparenz um, ansonsten ohne weitere Features.
             *  \note Ist die Textur bereits geladen, wird sie nicht noch einmal geladen.
             *  \param fileName: Name und Pfad der Textur-Datei
             */
            irr::video::ITexture* getWithColorKeyTransparency(const char* fileName);

        private:
            struct Texture {
                bool alreadyColorKeyed = false;
                irr::video::ITexture* irrTexture = nullptr;
            };

            irr::video::IVideoDriver* mVideoDriver = nullptr;
            leviathan::core::ILogger& mLogger;
            std::unordered_map<std::string, Texture> mTextures = std::unordered_map<std::string, Texture>();
        };
    }
}

#endif
