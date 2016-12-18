#include "DebugStatistics.h"
#include "Logfile.h"



DebugStatistics::DebugStatistics( irr::IrrlichtDevice* device )
: device_(device)
{
}



void DebugStatistics::writeStatisticsToLogfile()
{
    irr::core::stringw text = L"\n=== Statistiken ===";

    irr::video::IVideoDriver* driver = device_->getVideoDriver();
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

    irr::scene::ISceneManager* smgr = device_->getSceneManager();
    text += "\n-- scene manager --";
    text += "\n  mesh loaders: ";
    text += smgr->getMeshLoaderCount();
    text += "\n  scene loaders: ";
    text += smgr->getSceneLoaderCount();
    irr::scene::IMeshCache* mcache = smgr->getMeshCache();
    text += "\n  -- mesh cache --";
    text += "\n    meshes: ";
    text += mcache->getMeshCount();

    irr::io::IFileSystem* fs = device_->getFileSystem();
    text += "\n-- file system --";
    text += "\n  archive loaders: ";
    text += fs->getArchiveLoaderCount();
    text += "\n  archives: ";
    text += fs->getFileArchiveCount();

    irr::gui::IGUIEnvironment* gui = device_->getGUIEnvironment();
    text += "\n-- gui --";
    text += "\n  registered factories: ";
    text += gui->getRegisteredGUIElementFactoryCount();

    text += "\n°°°";
    Logfile::getInstance().writeLine( Logfile::DEBUG, text );
}
