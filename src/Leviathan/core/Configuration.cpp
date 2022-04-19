#include "Configuration.h"

namespace leviathan {
    namespace core {
        Configuration::Configuration(const char* fileName) {
            mParams.LoggingLevel = irr::ELL_WARNING;
            loadFromFile(fileName);
        }

        void Configuration::loadFromFile(const char* fileName) {
            YAML::Node content;
            try {
                content = YAML::LoadFile(fileName);
            } catch (const YAML::BadFile& e) {
            } catch (const YAML::ParserException& e) {
            }
            if (!content) content = YAML::Load("---");

            setCameraValues(content);
            setGeneralValues(content);
            setVideoValues(content);
        }

        const irr::SIrrlichtCreationParameters& Configuration::getGraphicEngineParams() const {
            return mParams;
        }

        const float& Configuration::getFarValue() const {
            return mFarValue;
        }

        const ILogger::Level& Configuration::getLoggingLevel() const {
            return mLoggingLevel;
        }

        const uint32_t& Configuration::getMaxFPS() const {
            return mMaxFPS;
        }

        const video::Dimension2D& Configuration::getScreenSize() const {
            return mScreenSize;
        }

        void Configuration::setCameraValues(YAML::Node& content) {
            if (!content["camera"]) {
                setCameraDefaults();
                return;
            }

            mFarValue = content["camera"]["far_value"].as<float>(300.0f);
        }

        void Configuration::setGeneralValues(YAML::Node& content) {
            if (!content["general"]) {
                setGeneralDefaults();
                return;
            }

            mLoggingLevel = mLogLevelMap[content["general"]["logging_level"].as<std::string>("INFO")];
        }

        void Configuration::setVideoValues(YAML::Node& content) {
            if (!content["video"]) {
                setVideoDefaults();
            } else {
                mParams.WindowSize.Width = content["video"]["screen_x"].as<uint32_t>(800);
                mParams.WindowSize.Height = content["video"]["screen_y"].as<uint32_t>(600);
                mParams.Bits = content["video"]["color_depth"].as<uint8_t>(16) == 32 ? 32 : 16;
                mParams.Fullscreen = content["video"]["fullscreen"].as<bool>(false);
                mParams.DriverType = mDriverMap[content["video"]["driver"].as<std::string>("OPENGL")];
                mMaxFPS = content["video"]["max_fps"].as<uint32_t>(60);
            }
            mScreenSize = {mParams.WindowSize.Width, mParams.WindowSize.Height};
        }

        void Configuration::setCameraDefaults() {
            mFarValue = 300.0f;
        }

        void Configuration::setGeneralDefaults() {
            mLoggingLevel = mLogLevelMap["INFO"];
        }

        void Configuration::setVideoDefaults() {
            mParams.WindowSize.Width = 800;
            mParams.WindowSize.Height = 600;
            mParams.Bits = 16;
            mParams.Fullscreen = false;
            mParams.DriverType = mDriverMap["OPENGL"];
            mMaxFPS = 60;
        }
    }
}
