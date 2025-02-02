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
#include "gui/DebugWindow.h"
#include "gui/MenuControl.h"
#include "gui/MousePointerControl.h"
#include "input/Actions.h"
#include "input/EventReceiver.h"
#include "video/Camera.h"
#include "video/GraphicEngine.h"
#include "video/Textures.h"
#include "world/Collider.h"
#include "world/Ground.h"
#include "world/NodeManager.h"
#include <ILeviathanDevice.h>
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
    class LeviathanDevice final : public ILeviathanDevice {
    public:
        /*! \brief Konstruktor. Lädt die Konfiguration aus der angegebenen Datei und initialisiert alle Bestandteile
         *         der Engine.
         *  \param configFileName: Konfigdateiname
         */
        explicit LeviathanDevice(const char* configFileName);

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
        void run() override;

        /*! /brief Stoppt den Game-Loop und fährt die Engine herunter.
         *  /note Der aktuelle Game-Loop läuft noch zu Ende durch.
         */
        void halt() override;

        /*! \brief Zugriff auf die Helden.
         */
        characters::IHeroes& Heroes() override;

        /*! \brief Zugriff auf die TimeControl Instanz.
         */
        core::TimeControl& TimeControl();

        /*! \brief Zugriff auf den Logger.
         */
        core::ILogger& Logger() override;

        /*! \brief Zugriff auf die aktuelle Konfiguration.
         */
        core::IConfiguration& Configuration() override;

        /*! \brief Zugriff auf die Verwaltung der Spielzustände.
         */
        core::IGameStateManager& GameStateManager() override;

        /*! \brief Zugriff auf den Zufallszahlengenerator.
         */
        core::Randomizer& Randomizer();

        /*! \brief Zugriff auf Erstellen und Verwalten von Menüs.
         */
        gui::IMenuControl& MenuControl() override;

        /*! \brief Zugriff auf Mauszeiger.
         */
        gui::IMousePointerControl& MousePointerControl() override;

        /*! \brief Zugriff auf Input-Mappings.
         */
        input::IActions& Actions() override;

        /*! \brief Zugriff auf Input-Events.
         */
        input::EventReceiver& EventReceiver();

        /*! \brief Zugriff auf eine Kamera.
         */
        video::ICamera& Camera() override;

        /*! \brief Zugriff auf begehbaren Boden.
         */
        world::IGround& Ground() override;

        /*! \brief Zugriff auf die Kollisionserkennung
         */
        world::ICollider& Collider() override;

    private:
        core::Configuration mConfiguration;
        core::Logger mLogger;
        core::TimeControl mTimeControl;
        core::GameStateManager mGameStateManager;
        core::Randomizer mRandomizer;
        input::EventReceiver mEventReceiver;
        input::Actions mActions;
        video::GraphicEngine mGraphicEngine;
        std::unique_ptr<video::Textures> mTextures = nullptr;
        std::unique_ptr<gui::DebugWindow> mDebugWindow = nullptr;
        std::unique_ptr<gui::MenuControl> mMenuControl = nullptr;
        std::unique_ptr<gui::MousePointerControl> mMousePointerControl = nullptr;
        std::unique_ptr<video::Camera> mCamera = nullptr;
        std::unique_ptr<world::Collider> mCollider = nullptr;
        std::unique_ptr<world::NodeManager> mNodeManager = nullptr;
        std::unique_ptr<characters::Heroes> mHeroes = nullptr;
        std::unique_ptr<world::Ground> mGround = nullptr;

        void handleWindowInactivity();
        void updateGame(const float frameDeltaTime);
        void drawGame();
    };
}

#endif
