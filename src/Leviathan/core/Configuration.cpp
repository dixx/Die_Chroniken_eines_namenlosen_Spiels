#include "Configuration.h"

namespace leviathan {
    namespace core {
        Configuration::Configuration(const char* fileName) {
            params_.LoggingLevel = irr::ELL_WARNING;
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
            return params_;
        }

        const float& Configuration::getFarValue() const {
            return farValue_;
        }

        const Logger::Level& Configuration::getLoggingLevel() const {
            return loggingLevel_;
        }

        const uint32_t& Configuration::getMaxFPS() const {
            return maxFPS_;
        }

        const video::Dimension2D& Configuration::getScreenSize() const {
            return screenSize_;
        }

        void Configuration::setCameraValues(YAML::Node& content) {
            if (!content["camera"]) {
                setCameraDefaults();
                return;
            }

            farValue_ = content["camera"]["far_value"].as<float>(300.0f);
        }

        void Configuration::setGeneralValues(YAML::Node& content) {
            if (!content["general"]) {
                setGeneralDefaults();
                return;
            }

            loggingLevel_ = logLevelMap[content["general"]["logging_level"].as<std::string>("INFO")];
        }

        void Configuration::setVideoValues(YAML::Node& content) {
            if (!content["video"]) {
                setVideoDefaults();
            } else {
                params_.WindowSize.Width = content["video"]["screen_x"].as<uint32_t>(800);
                params_.WindowSize.Height = content["video"]["screen_y"].as<uint32_t>(600);
                params_.Bits = content["video"]["color_depth"].as<uint8_t>(16) == 32 ? 32 : 16;
                params_.Fullscreen = content["video"]["fullscreen"].as<bool>(false);
                params_.DriverType = driverMap_[content["video"]["driver"].as<std::string>("OPENGL")];
                maxFPS_ = content["video"]["max_fps"].as<uint32_t>(60);
            }
            screenSize_ = {params_.WindowSize.Width, params_.WindowSize.Height};
        }

        void Configuration::setCameraDefaults() {
            farValue_ = 300.0f;
        }

        void Configuration::setGeneralDefaults() {
            loggingLevel_ = logLevelMap["INFO"];
        }

        void Configuration::setVideoDefaults() {
            params_.WindowSize.Width = 800;
            params_.WindowSize.Height = 600;
            params_.Bits = 16;
            params_.Fullscreen = false;
            params_.DriverType = driverMap_["OPENGL"];
            maxFPS_ = 60;
        }
    }
}
