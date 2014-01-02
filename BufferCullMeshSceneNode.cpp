#include "BufferCullMeshSceneNode.h"



BufferCullMeshSceneNode::BufferCullMeshSceneNode(
        scene::IMesh* mesh,
        scene::ISceneNode* parent,
        scene::ISceneManager* mgr,
        s32 id,
        const core::vector3df& position,
        const core::vector3df& rotation,
		const core::vector3df& scale
)
: IMeshSceneNode(parent, mgr, id, position, rotation, scale),
  Mesh(0),
  PassCount(0),
  ReadOnlyMaterials(false)
{
//    validatorStart = 0;
//    validatorEnd = 0;
	#ifdef _DEBUG_MODE
	setDebugName( "LODMeshSceneNode" );
	#endif
	setMesh( mesh );
}



//void BufferCullMeshSceneNode::validateObject()
//{
//    // Breakpoint springt an, wenn einer oder beide Validatoren nicht mehr
//    // 0 sind
//    validatorStart;
//    validatorEnd;
//}



BufferCullMeshSceneNode::~BufferCullMeshSceneNode()
{
	if ( Mesh )
		Mesh->drop();
}



void BufferCullMeshSceneNode::OnRegisterSceneNode()
{
	if ( IsVisible )
	{
		// because this node supports rendering of mixed mode meshes consisting
	    // of transparent and solid material at the same time, we need to go
	    // through all materials, check of what type they are and register this
	    // node for the right render pass according to that.
		video::IVideoDriver* driver = SceneManager->getVideoDriver();
		PassCount = 0;
		bool isTransparent = false;
		bool isSolid = false;
		// count transparent and solid materials in this scene node
		if ( ReadOnlyMaterials && Mesh )
		{
			for ( register u32 i = 0; i < Mesh->getMeshBufferCount(); ++i )
			{
				scene::IMeshBuffer* mb = Mesh->getMeshBuffer( i );
				video::IMaterialRenderer* renderer =
				        mb ? driver->getMaterialRenderer(
				                mb->getMaterial().MaterialType )
				        : 0;
				if ( renderer && renderer->isTransparent() )
					isTransparent = true;
				else
					isSolid = true;
				if ( isSolid && isTransparent )
					break;
			}
		}
		else
		{
			for ( register u32 i = 0; i < Materials.size(); ++i )
			{
				video::IMaterialRenderer* renderer =
					driver->getMaterialRenderer( Materials[ i ].MaterialType );
				if ( renderer && renderer->isTransparent() )
				    isTransparent = true;
				else
				    isSolid = true;
				if ( isSolid && isTransparent )
					break;
			}
		}
		// register according to material types counted
		if ( isSolid )
			SceneManager->registerNodeForRendering( this, scene::ESNRP_SOLID );
		if ( isTransparent )
			SceneManager->registerNodeForRendering( this,
			        scene::ESNRP_TRANSPARENT );
		scene::ISceneNode::OnRegisterSceneNode();
	}
}



void BufferCullMeshSceneNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	if ( !Mesh || !driver )
		return;
	bool isTransparentPass =
		SceneManager->getSceneNodeRenderPass() == scene::ESNRP_TRANSPARENT;
	++PassCount;
	driver->setTransform( video::ETS_WORLD, AbsoluteTransformation );
	Box = Mesh->getBoundingBox();
	bool renderMeshes = true;
	if ( DebugDataVisible && PassCount == 1 )
	{
    	video::SMaterial mat;
		// overwrite half transparency
		if ( DebugDataVisible & scene::EDS_HALF_TRANSPARENCY )
		{
			for ( register u32 g = 0; g < Mesh->getMeshBufferCount(); ++g )
			{
				mat = Materials[ g ];
				mat.MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
				driver->setMaterial( mat );
                driver->drawMeshBuffer( Mesh->getMeshBuffer( g ) );
			}
			renderMeshes = false;
		}
	}
	// render original meshes with LOD
	if ( renderMeshes )
	{
        cam = SceneManager->getActiveCamera();
        R_camBox = cam->getBoundingBox();
		for ( register u32 i = 0; i < Mesh->getMeshBufferCount(); ++i )
		{
            R_mb = Mesh->getMeshBuffer( i );
			if ( R_mb )
			{
			    R_bufbox = R_mb->getBoundingBox();
			    AbsoluteTransformation.transformBoxEx( R_bufbox );
                if ( !R_bufbox.intersectsWithBox( R_camBox )
                        && !R_bufbox.isFullInside( R_camBox )
                ) continue;
                if ( cam->getPosition().getDistanceFrom(
                        R_bufbox.getCenter() )
                        > ( cam->getFarValue()
                                + R_bufbox.getExtent().getLength() / 2
                          )
                ) continue;/* entfernung + halbe diagonale... sehr ungenau */
				const video::SMaterial& material = 
                        ReadOnlyMaterials ? R_mb->getMaterial() : Materials[i];

				R_rnd = driver->getMaterialRenderer( material.MaterialType );
				bool transparent = ( R_rnd && R_rnd->isTransparent() );

				// only render transparent buffer if this is the
                // transparent render pass and solid only in solid pass
				if ( transparent == isTransparentPass )
				{
					driver->setMaterial( material );
                    driver->drawMeshBuffer( R_mb );
				}
			}
		}
	}
	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
	if ( DebugDataVisible && PassCount == 1 )
	{
		video::SMaterial m;
		m.Lighting = false;
		driver->setMaterial( m );
		if ( DebugDataVisible & scene::EDS_BBOX )
			driver->draw3DBox( Box, COL_WHITE );
		if ( DebugDataVisible & scene::EDS_BBOX_BUFFERS )
		{
			for ( register u32 g = 0; g < Mesh->getMeshBufferCount(); ++g )
			{
				driver->draw3DBox(
					Mesh->getMeshBuffer( g )->getBoundingBox(),
					video::SColor( 255, 190, 128, 128 )
				);
			}
		}
		if ( DebugDataVisible & scene::EDS_NORMALS )
		{
			core::vector3df normalizedNormal;
			const f32 DebugNormalLength =
			        SceneManager->getParameters()->getAttributeAsFloat(
			                scene::DEBUG_NORMAL_LENGTH );
			const video::SColor DebugNormalColor =
			        SceneManager->getParameters()->getAttributeAsColor(
			                scene::DEBUG_NORMAL_COLOR );
			for ( register u32 g = 0; g < Mesh->getMeshBufferCount(); ++g )
			{
				const scene::IMeshBuffer* mb = Mesh->getMeshBuffer( g );
				const u32 vSize = video::getVertexPitchFromType(
				        mb->getVertexType() );
				const video::S3DVertex* v =
				        (const video::S3DVertex*)mb->getVertices();
				const bool normalize = mb->getMaterial().NormalizeNormals;
				for ( register u32 i = 0; i != mb->getVertexCount(); ++i )
				{
					normalizedNormal = v->Normal;
					if ( normalize )
						normalizedNormal.normalize();
					driver->draw3DLine(
					        v->Pos,
					        v->Pos + ( normalizedNormal * DebugNormalLength ),
					        DebugNormalColor
					);
					v = (const video::S3DVertex*)( (u8*)v + vSize );
				}
			}
			driver->setTransform( video::ETS_WORLD, AbsoluteTransformation );
		}
		if ( DebugDataVisible & scene::EDS_MESH_WIRE_OVERLAY )
		{
			m.Wireframe = true;
			driver->setMaterial( m );
			for ( register u32 g = 0; g < Mesh->getMeshBufferCount(); ++g )
			{
				driver->drawMeshBuffer( Mesh->getMeshBuffer( g ) );
			}
		}
	}
}



const core::aabbox3df& BufferCullMeshSceneNode::getBoundingBox() const
{
	return Mesh ? Mesh->getBoundingBox() : Box;
}



video::SMaterial& BufferCullMeshSceneNode::getMaterial( u32 i )
{
	if ( Mesh && ReadOnlyMaterials && i < Mesh->getMeshBufferCount() )
	{
		tmpReadOnlyMaterial = Mesh->getMeshBuffer( i )->getMaterial();
		return tmpReadOnlyMaterial;
	}
	if ( i >= Materials.size() )
		return scene::ISceneNode::getMaterial( i );
	return Materials[ i ];
}



u32 BufferCullMeshSceneNode::getMaterialCount() const
{
	if ( Mesh && ReadOnlyMaterials )
		return Mesh->getMeshBufferCount();
	return Materials.size();
}



scene::ESCENE_NODE_TYPE BufferCullMeshSceneNode::getType() const
{
    return scene::ESNT_MESH;
}



void BufferCullMeshSceneNode::setMesh( scene::IMesh* mesh )
{
	if ( !mesh )
		return; // won't set null mesh
    mesh->grab();
	if ( Mesh )
		Mesh->drop();
	Mesh = mesh;
	copyMaterials();
}



scene::IMesh* BufferCullMeshSceneNode::getMesh()
{
    return Mesh;
}



void BufferCullMeshSceneNode::copyMaterials()
{
	Materials.clear();
	if ( Mesh )
	{
		video::SMaterial mat;
		for ( register u32 i = 0; i < Mesh->getMeshBufferCount(); ++i )
		{
		    scene::IMeshBuffer* mb = Mesh->getMeshBuffer( i );
			if ( mb )
				mat = mb->getMaterial();
			Materials.push_back( mat );
		}
	}
}



void BufferCullMeshSceneNode::setReadOnlyMaterials( bool readonly )
{
	ReadOnlyMaterials = readonly;
}



bool BufferCullMeshSceneNode::isReadOnlyMaterials() const
{
	return ReadOnlyMaterials;
}



//! Creates a clone of this scene node and its children.
scene::ISceneNode* BufferCullMeshSceneNode::clone( scene::ISceneNode* newParent,
        scene::ISceneManager* newManager )
{
	if ( !newParent )
	    newParent = Parent;
	if ( !newManager )
	    newManager = SceneManager;
	BufferCullMeshSceneNode* nb = new BufferCullMeshSceneNode(
	        Mesh,
	        newParent,
	        newManager,
	        ID,
	        RelativeTranslation,
	        RelativeRotation,
	        RelativeScale
	);
	nb->cloneMembers( this, newManager );
	nb->ReadOnlyMaterials = ReadOnlyMaterials;
	nb->Materials = Materials;
	nb->drop();
	return nb;
}



//! Creates shadow volume scene node as child of this node
//! and returns a pointer to it.
scene::IShadowVolumeSceneNode* BufferCullMeshSceneNode::addShadowVolumeSceneNode(
        const scene::IMesh* shadowMesh, s32 id, bool zfailmethod, f32 infinity )
{
    if ( !SceneManager->getVideoDriver()->queryFeature(
            video::EVDF_STENCIL_BUFFER ) )
        return 0;
    if ( !shadowMesh )
        shadowMesh = Mesh; // if null is given, use the mesh of node
    if ( Shadow )
        Shadow->drop();
    //! \todo remove dirty workaround as soon as Irrlicht supports this
    id++;
    zfailmethod = false;
    if ( !zfailmethod )
        infinity += 1.0f;
//    Shadow = new CShadowVolumeSceneNode(shadowMesh, this, SceneManager, id,
//            zfailmethod, infinity);
//    return Shadow;
    return 0;
}
//! \todo remove "C:\Users\dixx\Projekte\Ressourcen\Irrlicht\irrlicht-1.8\source\Irrlicht"
//!       from configuration and flags if no longer needed
