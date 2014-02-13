#include "DebugStatistics.h"
#include "Logfile.h"



DebugStatistics::DebugStatistics( IrrlichtDevice* device ) : device_(device)
{
}



DebugStatistics* DebugStatistics::writeStatisticsToLogfile()
{
    core::stringw text = L"\n=== Statistiken ===";

    video::IVideoDriver* driver = device_->getVideoDriver();
    text += "\n-- video driver --";
    text += "\n  dynamic lights: ";
    text += driver->getDynamicLightCount();
    text += "\n  textures: ";
    text += driver->getTextureCount();
    text += "\n  drawn primitives: ";
    text += driver->getPrimitiveCountDrawn();
    text += "\n  image loaders: ";
    text += driver->getImageLoaderCount();
    text += "\n  image writers: ";
    text += driver->getImageWriterCount();
    text += "\n  material renderers: ";
    text += driver->getMaterialRendererCount();

    scene::ISceneManager* smgr = device_->getSceneManager();
    text += "\n-- scene manager --";
    text += "\n  mesh loaders: ";
    text += smgr->getMeshLoaderCount();
    text += "\n  scene loaders: ";
    text += smgr->getSceneLoaderCount();
    scene::IMeshCache* mcache = smgr->getMeshCache();
    text += "\n  -- mesh cache --";
    text += "\n    meshes: ";
    text += mcache->getMeshCount();

    io::IFileSystem* fs = device_->getFileSystem();
    text += "\n-- file system --";
    text += "\n  archive loaders: ";
    text += fs->getArchiveLoaderCount();
    text += "\n  archives: ";
    text += fs->getFileArchiveCount();

    gui::IGUIEnvironment* gui = device_->getGUIEnvironment();
    text += "\n-- gui --";
    text += "\n  registered factories: ";
    text += gui->getRegisteredGUIElementFactoryCount();

    text += "\n°°°";
    Logfile::getInstance().writeLine( Logfile::DEBUG, text );
    return this;
}



void DebugStatistics::drop()
{
    delete this;
}



/* private */



DebugStatistics::~DebugStatistics()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}
