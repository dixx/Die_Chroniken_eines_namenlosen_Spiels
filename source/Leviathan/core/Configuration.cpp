#include "Configuration.h"
#include <fstream>

namespace leviathan {
    namespace core {
        Configuration::Configuration(const irr::io::path& fileName) {
            params_.LoggingLevel = irr::ELL_WARNING;
            readFromFile(fileName);
        }

        void Configuration::readFromFile(const irr::io::path& fileName) {
            content_.clear();
            generateContent(fileName);
            params_.WindowSize.Width = irr::core::strtoul10(getItem("video", "screen_x", "800").c_str());
            params_.WindowSize.Height = irr::core::strtoul10(getItem("video", "screen_y", "600").c_str());
            params_.Bits = static_cast<uint8_t>(irr::core::strtoul10(getItem("video", "color_depth", "16").c_str()));
            params_.Fullscreen = getItem("video", "fullscreen", "false").equals_ignore_case("true");
            params_.DriverType = driverMap_[getItem("video", "driver", "OPENGL").c_str()];
            farValue_ = irr::core::strtof10(getItem("camera", "far_value", "300.0").c_str());
            loggingLevel_ = logLevelMap[getItem("general", "logging_level", "INFO").c_str()];
            maxFPS_ = irr::core::strtoul10(getItem("video", "max_fps", "60").c_str());
        }

        const irr::SIrrlichtCreationParameters& Configuration::getGraphicEngineParams() const {
            return params_;
        }

        float Configuration::getFarValue() const {
            return farValue_;
        }

        Logger::Level Configuration::getLoggingLevel() const {
            return loggingLevel_;
        }

        uint32_t Configuration::getMaxFPS() const {
            return maxFPS_;
        }

        int Configuration::getInt(const irr::core::stringc& section, const irr::core::stringc& key) {
            return static_cast<int>(irr::core::strtol10(getItem(section, key).c_str()));
        }

        /* private */

        void Configuration::generateContent(const irr::io::path& fileName) {
            std::fstream filestream(fileName.c_str(), std::fstream::in);
            if (filestream.fail()) {
                filestream.close();
                content_.push_back("");
                return;
            }
            filestream.seekg(0, filestream.end);
            std::streampos size = filestream.tellg();
            filestream.seekg(0, filestream.beg);
            if (size <= 0) {
                filestream.close();
                content_.push_back("");
                return;
            }
            irr::core::array<char> buffer(static_cast<uint32_t>(size) + 4);
            filestream.read(buffer.pointer(), static_cast<std::streamsize>(size));
            filestream.close();
            irr::core::stringc rawContent = buffer.const_pointer();
            rawContent.split(content_, "\n", 1, /* ignoreEmptyTokens = */ false);
        }

        const irr::core::stringc Configuration::getItem(
            const irr::core::stringc& section, const irr::core::stringc& key, const irr::core::stringc& defaultValue) {
            bool sectionFound = false;
            irr::core::stringc result;
            irr::core::stringc sectionIdent = "[";
            sectionIdent.append(section).append("]");
            for (auto& line : content_) {
                if (!sectionFound) {
                    if (line.find(sectionIdent.c_str()) == 0) sectionFound = true;
                } else {
                    if (line[0] == '[') break;
                    if (line[0] == '#' || line[0] == ';') continue;
                    if (line.find(key.c_str()) == -1) continue;
                    uint32_t valueStart = static_cast<uint32_t>(line.findFirstChar("=") + 1);
                    result = line.subString(valueStart, static_cast<int32_t>(line.size() - valueStart)).trim();
                    break;
                }
            }
            return result.empty() ? defaultValue : result;
        }
    }
}
