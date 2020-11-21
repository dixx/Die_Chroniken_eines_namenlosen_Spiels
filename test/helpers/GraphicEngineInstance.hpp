#include <cstdint>
#include <string>

// TODO: try to move to TestHelper
class GraphicEngineInstance {
public:
    static irr::IrrlichtDevice* get() {
        static GraphicEngineInstance instance;
        return instance.engine();
    }

    GraphicEngineInstance(GraphicEngineInstance const&) = delete;
    void operator=(GraphicEngineInstance const&) = delete;

    irr::IrrlichtDevice* engine() {
        return graphicEngine_;
    }

    static std::string uniqueName() {
        static GraphicEngineInstance instance;
        return std::to_string(instance.uniqueId++);
    }

private:
    irr::IrrlichtDevice* graphicEngine_ = nullptr;
    uint32_t uniqueId = 0;

    GraphicEngineInstance() {
        irr::SIrrlichtCreationParameters params;
        params.DriverType = irr::video::EDT_NULL;
        params.LoggingLevel = irr::ELL_WARNING;
        graphicEngine_ = irr::createDeviceEx(params);
    }
    ~GraphicEngineInstance() {
        if (graphicEngine_) graphicEngine_->drop();
    }
};
