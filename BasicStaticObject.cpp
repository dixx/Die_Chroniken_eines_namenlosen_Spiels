#include "BasicStaticObject.h"
#include "Collision.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "ObjectManager.h"
#include "Logfile.h"



BasicStaticObject::BasicStaticObject(
        const core::stringc& objectData,
        scene::ISceneManager* smgr,
        bool isParent
)
: Basic3DObject(objectData, smgr, true),
  node_(0),
  nextStep_(VEC_3DF_NULL)
{
    init();
    if ( !isParent )
        deleteExtractor();
}



BasicStaticObject::~BasicStaticObject()
{
    if ( node_ )
    {
        Collision::getInstance().removeNodeFromWorld( node_ );
        node_->getMesh()->drop();
        node_->remove();  // drop und delete werden implizit ausgeführt
        node_ = 0;
    }
}



BufferCullMeshSceneNode* BasicStaticObject::getNode() const
{
    return node_;
}



f32 BasicStaticObject::getCollisionRadius() const
{
    return 0.0f;
}



scene::ISceneNode* BasicStaticObject::nodeInterface() const
{
    return static_cast<scene::ISceneNode*>(node_);
}



const core::vector3df& BasicStaticObject::getNextStep() const
{
    return nextStep_;
}



core::stringc BasicStaticObject::getObjectData()
{
    return "";
}



/* protected */



scene::IMesh* BasicStaticObject::loadMesh()
{
    scene::IMesh* mesh = 0;
    if ( extractor_->tryToExtractValue( "MFILE" ) )
    {
        core::stringc meshFileName = extractor_->getExtractedValue();
        if ( meshFileName.size() == 0 )
        {
            createLogEntry( "Leerer Mesh-Dateiname" );
        }
        else
        {
            GenericHelperMethods::getInstance().validateFileExistence(
                    meshFileName );
            scene::IMesh* dummyMesh = smgr_->getMesh( meshFileName );
#ifdef _DEBUG_MODE
            if (meshFileName.find(core::stringc("zaunfeld01_material_test").c_str()) != -1)
            {
                Logfile& log= Logfile::getInstance();
                log.writeLine(0, "");
                log.writeLine(0, "Filename: ", meshFileName);
                for(register u32 i = 0; i < dummyMesh->getMeshBufferCount(); ++i)
                {
                    log.writeLine(0, "  Meshbuffer ", i);
                    scene::IMeshBuffer* m= dummyMesh->getMeshBuffer(i);
                    log.writeLine(0, "    - name: ", m->getDebugName());
                    log.writeLine(0, "    - Material:");
                    video::SMaterial& mat= m->getMaterial();
                    for (register u32 j = 0; j < 4; ++j)
                    {
                        if (mat.getTexture(j))
                        {
                            log.write(0, "      - Texture ", j);
                            log.writeLine(0, ": ", mat.getTexture(j)->getName());
                        }
                    }
                    log.writeLine(0, "      - Lighting: ", mat.Lighting ? "ja" : "nein");
                    log.writeLine(0, "      - Type: ", mat.MaterialType);
                    log.writeLine(0, "      - Shininess: ", mat.Shininess);
                    log.writeLine(0, "      - AmbientColor.Red: ", mat.AmbientColor.getRed());
                    log.writeLine(0, "      - AmbientColor.Green: ", mat.AmbientColor.getGreen());
                    log.writeLine(0, "      - AmbientColor.Blue: ", mat.AmbientColor.getBlue());
                    log.writeLine(0, "      - AmbientColor.Alpha: ", mat.AmbientColor.getAlpha());
                    log.writeLine(0, "      - EmissiveColor.Red: ", mat.EmissiveColor.getRed());
                    log.writeLine(0, "      - EmissiveColor.Green: ", mat.EmissiveColor.getGreen());
                    log.writeLine(0, "      - EmissiveColor.Blue: ", mat.EmissiveColor.getBlue());
                    log.writeLine(0, "      - EmissiveColor.Alpha: ", mat.EmissiveColor.getAlpha());
                    log.writeLine(0, "      - DiffuseColor.Red: ", mat.DiffuseColor.getRed());
                    log.writeLine(0, "      - DiffuseColor.Green: ", mat.DiffuseColor.getGreen());
                    log.writeLine(0, "      - DiffuseColor.Blue: ", mat.DiffuseColor.getBlue());
                    log.writeLine(0, "      - DiffuseColor.Alpha: ", mat.DiffuseColor.getAlpha());
                    log.writeLine(0, "      - SpecularColor.Red: ", mat.SpecularColor.getRed());
                    log.writeLine(0, "      - SpecularColor.Green: ", mat.SpecularColor.getGreen());
                    log.writeLine(0, "      - SpecularColor.Blue: ", mat.SpecularColor.getBlue());
                    log.writeLine(0, "      - SpecularColor.Alpha: ", mat.SpecularColor.getAlpha());
                }
            }
#endif
            mesh = smgr_->getMeshManipulator()->createMeshCopy(
                    dummyMesh ); // TODO test if you can remove this part!
            smgr_->getMeshCache()->removeMesh( dummyMesh );
        }
    }
    else
    {
        createLogEntry( "Kein Mesh-Dateiname" );
    }
    return mesh;
}



/* private */



void BasicStaticObject::init()
{
    scene::IMeshManipulator* meshManipulator = smgr_->getMeshManipulator();
    core::matrix4 matrix = core::matrix4();

    smgr_->getVideoDriver()->setTransform( video::ETS_WORLD, matrix );
    scene::IMesh* dummyMesh = loadMesh();
    if ( dummyMesh )
    {
        matrix.setScale( loadScale() );
        matrix.setTranslation( loadOffset() );
        meshManipulator->transform( dummyMesh, matrix );
        meshManipulator->recalculateNormals( dummyMesh, true );
        GenericHelperMethods::getInstance().pushMeshToVRAM( dummyMesh );
        node_ = new BufferCullMeshSceneNode(
                dummyMesh,
                ObjectManager::getInstance().getBaseNodeByType( type_ ),
                smgr_,
                ObjectManager::getInstance().getBaseIdByType( type_ )
        );
        dummyMesh->drop();
        node_->setName( name_ );
        node_->setRotation( loadRotation() );
        node_->setPosition( loadPosition() );
        node_->updateAbsolutePosition();
        node_->setMaterialTexture( 0, loadMainTexture() );
        for ( u32 i = 0; i < node_->getMaterialCount(); ++i )
            loadFilterAndEffects( node_->getMaterial( i ) );
        Collision::getInstance().addStaticMeshNodeToWorld( node_ );
        node_->setVisible( false );
    }
}
