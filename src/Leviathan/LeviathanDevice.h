/*! \file LeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_DEVICE_H
#define LEVIATHAN_DEVICE_H

#include "characters/Heroes.h"
#include "core/Configuration.h"
#include "core/GameStateManager.h"
#include "core/Logger.h"
#include "core/Randomizer.h"
#include "core/TimeControl.h"
#include "gui/MenuControl.h"
#include "gui/MousePointerControl.h"
#include "input/Actions.h"
#include "input/EventReceiver.h"
#include "video/Camera.h"
#include "video/GraphicEngine.h"
#include "video/Textures.h"
#include "world/Ground.h"
#include "world/NodeManager.h"
#include <core/IGameStateManager.h>
#include <memory>

#ifndef NDEBUG
#define LOG_FILE_NAME "game.log"
#else
#define LOG_FILE_NAME "debug.log"
#endif

namespace leviathan {

    /*! \class LeviathanDevice LeviathanDevice.h "LeviathanDevice.h"
     *  \brief Die eigentliche Engine.
     */
    class LeviathanDevice {
    public:
        /*! \brief Konstruktor. Lädt die Konfiguration aus der angegebenen Datei und initialisiert alle Bestandteile
         *         der Engine.
         *  \param filename: Konfigdateiname
         */
        explicit LeviathanDevice(const char* fileName);

        /*! \brief Destruktor.
         */
        ~LeviathanDevice() = default;

        LeviathanDevice() = delete;
        LeviathanDevice(const LeviathanDevice&) = delete;
        LeviathanDevice& operator=(const LeviathanDevice&) = delete;

        /*! \brief Der eigentliche Game-Loop.
         *         Diese Methode kümmert sich um das Aktualisieren und Zeichnen des aktuellen Spielzustandes,
         *         Berechnen der Zeit, Entscheiden ob die KI aktualisiert werden muss usw.
         */
        void run();

        /*! /brief Stoppt den Game-Loop und fährt die Engine herunter.
         *  /note Der aktuelle Game-Loop läuft noch zu Ende durch.
         */
        void halt();

        /*! \brief Zugriff auf die Helden.
         */
        characters::Heroes& Heroes();

        /*! \brief Zugriff auf die TimeControl Instanz.
         */
        core::TimeControl& TimeControl();

        /*! \brief Zugriff auf den Logger.
         */
        core::Logger& Logger();

        /*! \brief Zugriff auf die aktuelle Konfiguration.
         */
        core::Configuration& Configuration();

        /*! \brief Zugriff auf die Verwaltung der Spielzustände.
         */
        core::IGameStateManager& GameStateManager();

        /*! \brief Zugriff auf den Zufallszahlengenerator.
         */
        core::Randomizer& Randomizer();

        /*! \brief Zugriff auf Erstellen und Verwalten von Menüs.
         */
        gui::MenuControl& MenuControl();

        /*! \brief Zugriff auf Mauszeiger.
         */
        gui::MousePointerControl& MousePointerControl();

        /*! \brief Zugriff auf Input-Mappings.
         */
        input::IActions& Actions();

        /*! \brief Zugriff auf Input-Events.
         */
        input::EventReceiver& EventReceiver();

        /*! \brief Zugriff auf eine Kamera.
         */
        video::Camera& Camera();

        /*! \brief Zugriff auf begehbaren Boden.
         */
        world::Ground& Ground();

    private:
        core::Configuration configuration_;
        core::Logger logger_;
        core::TimeControl timeControl_;
        core::GameStateManager gameStateManager_;
        core::Randomizer randomizer_;
        input::EventReceiver eventReceiver_;
        input::Actions actions_;
        video::GraphicEngine graphicEngine_;
        std::unique_ptr<video::Textures> textures_ = nullptr;
        std::unique_ptr<gui::MenuControl> menuControl_ = nullptr;
        std::unique_ptr<gui::MousePointerControl> mousePointerControl_ = nullptr;
        std::unique_ptr<video::Camera> camera_ = nullptr;
        std::unique_ptr<world::NodeManager> nodeManager_ = nullptr;
        std::unique_ptr<characters::Heroes> heroes_ = nullptr;
        std::unique_ptr<world::Ground> ground_ = nullptr;

        void handleWindowInactivity();
        void updateGame(const float frameDeltaTime);
        void drawGame();
    };
}

#endif
