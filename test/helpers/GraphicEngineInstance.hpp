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

private:
    irr::IrrlichtDevice* graphicEngine_ = nullptr;

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
