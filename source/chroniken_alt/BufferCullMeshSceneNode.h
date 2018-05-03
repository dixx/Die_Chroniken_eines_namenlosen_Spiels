/*! \file BufferCullMeshSceneNode.h
 *  \brief Ableitung von IMeshSceneNode, mit Culling per MeshBuffer.
 */

#ifndef _BUFFERCULLMESHSCENENODE_HEADER
#define _BUFFERCULLMESHSCENENODE_HEADER

#include <irrlicht.h>
#include <CShadowVolumeSceneNode.h>
#include "Constants.h"

/*! \class BufferCullMeshSceneNode BufferCullMeshSceneNode.h "BufferCullMeshSceneNode.h"
 *  \brief  Ableitung von IMeshSceneNode, mit Culling per MeshBuffer.
 */
class BufferCullMeshSceneNode : public irr::scene::IMeshSceneNode
{

protected:
    // Validator, um Überschreiber mittels Breakpoints finden zu können
//    s32 validatorStart;

    // interne Hilfsfunktion
    void copyMaterials();

    // interne Variablen, die überschrieben werden müssen,
    // da sie in der Hauptklasse VIRTUAL sind.
    irr::core::array<irr::video::SMaterial> Materials;
	irr::core::aabbox3df Box;
	irr::video::SMaterial tmpReadOnlyMaterial;
	irr::scene::IMesh* Mesh;
	irr::scene::IShadowVolumeSceneNode* Shadow;
	irr::s32 PassCount;
	bool ReadOnlyMaterials;
    // vars for the rendering process
    irr::core::aabbox3df R_bufbox;
    irr::core::aabbox3df R_camBox;
    irr::scene::IMeshBuffer* R_mb;
    irr::video::IMaterialRenderer* R_rnd;
    irr::scene::ICameraSceneNode* cam;

public:

	//! constructor
	BufferCullMeshSceneNode(
	        irr::scene::IMesh* mesh,
	        irr::scene::ISceneNode* parent,
	        irr::scene::ISceneManager* mgr,
	        irr::s32 id,
	        const irr::core::vector3df& position = VEC_3DF_NULL,
	        const irr::core::vector3df& rotation = VEC_3DF_NULL,
	        const irr::core::vector3df& scale = irr::core::vector3df( 1.0f, 1.0f, 1.0f )
    );

	//! destructor
	virtual ~BufferCullMeshSceneNode();

	//! frame
	virtual void OnRegisterSceneNode();

	//! renders the node.
	virtual void render();

	//! returns the axis aligned bounding box of this node
	virtual const irr::core::aabbox3df& getBoundingBox() const;

	//! returns the material based on the zero based index i. To get the amount
	//! of materials used by this scene node, use getMaterialCount().
	//! This function is needed for inserting the node into the scene hirachy on a
	//! optimal position for minimizing renderstate changes, but can also be used
	//! to directly modify the material of a scene node.
	//! \param i (\a u32) index of desired material
	//! \return the material
	virtual irr::video::SMaterial& getMaterial( irr::u32 i );

	//! returns amount of materials used by this scene node.
	virtual irr::u32 getMaterialCount() const;

    //! Returns type of the scene node
    virtual irr::scene::ESCENE_NODE_TYPE getType() const;

	//! Creates a clone of this scene node and its children.
	virtual irr::scene::ISceneNode* clone( irr::scene::ISceneNode* newParent = 0,
	        irr::scene::ISceneManager* newManager = 0 );

    //! Sets a new mesh
    virtual void setMesh( irr::scene::IMesh* mesh );

    //! Returns the current mesh
    virtual irr::scene::IMesh *getMesh();

    //! Creates shadow volume scene node as child of this node
    //! and returns a pointer to it.
    //! \note Since Irrlicht 1.8 this must be implemented here.
    //! \param shadowMesh (\a const \a scene::IMesh*) Mesh des Schattens
    //! \param id
    //! \param zfailmethod
    //! \param infinity
    //! \return a 3d shadow scene node
    virtual irr::scene::IShadowVolumeSceneNode* addShadowVolumeSceneNode(
            const irr::scene::IMesh* shadowMesh,
            irr::s32 id,
            bool zfailmethod = true,
            irr::f32 infinity = 10000.0f
    );

    //! Sets if the scene node should not copy the materials of the mesh but use them in a read only style.
    /* In this way it is possible to change the materials a mesh causing all mesh scene nodes
    referencing this mesh to change too. */
    virtual void setReadOnlyMaterials( bool readonly );

    //! Returns if the scene node should not copy the materials of the mesh but use them in a read only style
    virtual bool isReadOnlyMaterials() const;

private:
//	void validateObject();
    BufferCullMeshSceneNode( const BufferCullMeshSceneNode& );
    void operator=( const BufferCullMeshSceneNode& );
protected:
    // Validator, um Ueberschreiber mittels Breakpoints finden zu koennen
//    s32 validatorEnd;

};

#endif
