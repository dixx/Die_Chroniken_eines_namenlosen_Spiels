/*  \file Textures.h
 *  \brief Einfaches laden von Texturen.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_VIDEO_TEXTURES_H
#define LEVIATHAN_VIDEO_TEXTURES_H

#include "../core/Logger.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include <string>
#include <unordered_map>

namespace leviathan {
    namespace video {
        struct Texture {
            bool alreadyColorKeyed = false;
            irr::video::ITexture* irrTexture = nullptr;
        };

        /*  \class Textures
         *  \brief Einfaches laden von Texturen
         */
        class Textures {
        public:
            /*  \brief Konstruktor.
             *  \param videoDriver: Zeiger auf den Videotreiber der Graphic Engine
             *  \param logger: Instanz eines Loggers
             */
            Textures(irr::video::IVideoDriver* videoDriver, leviathan::core::Logger& logger);

            ~Textures() = default;
            Textures() = delete;
            Textures(const Textures&) = delete;
            Textures& operator=(const Textures&) = delete;

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
            irr::video::IVideoDriver* videoDriver_ = nullptr;
            leviathan::core::Logger& logger_;
            std::unordered_map<std::string, Texture> textures_ = std::unordered_map<std::string, Texture>();
        };
    }
}

#endif
