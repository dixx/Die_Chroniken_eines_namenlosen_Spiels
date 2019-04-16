#include "irrlicht.h"
#include "AttributesMock.hpp"
#include <cstdint>

// Fakeit keeps pointer to arguments beyond their lifetime and matches the given args too late, so we must implement
// our own mocks :(
namespace mocks {
    class VideoDriverMock : public irr::video::IVideoDriver {
    public:
        const irr::video::ITexture* mpTexture = nullptr;
        irr::core::vector2di mPosition = irr::core::vector2di();
        irr::core::recti mImageArea = irr::core::recti();
        uint32_t mDraw2DImageArgsCallCount = 0;
        const irr::core::recti* mClippingRectangle = nullptr;
        irr::video::SColor mBackgroundColor = irr::video::SColor(0, 0, 0, 0);
        bool mUseAlphaChannel = false;

        void draw2DImage(const irr::video::ITexture* texture, const irr::core::vector2di& position,
            const irr::core::recti& imageArea, const irr::core::recti* clippingRectangle = nullptr,
            irr::video::SColor backgroundColor = irr::video::SColor(0, 0, 0, 0), bool useAlphaChannel = false)
        {
            mpTexture = texture;
            mPosition = position;
            mImageArea = imageArea;
            mClippingRectangle = clippingRectangle;
            mBackgroundColor = backgroundColor;
            mUseAlphaChannel = useAlphaChannel;
            mDraw2DImageArgsCallCount++;
        }

        void ClearInvocationHistory() {
            mDraw2DImageArgsCallCount = 0;
        }

        _IRR_DEPRECATED_ irr::video::IImage* createImage(
            irr::video::ECOLOR_FORMAT format, irr::video::IImage *imageToCopy) {
            (void)format; (void)imageToCopy; return nullptr; }
        _IRR_DEPRECATED_ irr::video::IImage* createImage(
            irr::video::IImage* imageToCopy, const irr::core::position2d<irr::s32>& pos,
            const irr::core::dimension2d<irr::u32>& size) { (void)imageToCopy; (void)pos; (void)size; return nullptr; }
        bool beginScene(bool backBuffer=true, bool zBuffer=true, irr::video::SColor color=irr::video::SColor(255,0,0,0), const irr::video::SExposedVideoData& videoData=irr::video::SExposedVideoData(), irr::core::rect<irr::s32>* sourceRect=0) { (void)backBuffer; (void)zBuffer; (void)color; (void)videoData; (void)sourceRect; return false; }
        bool checkDriverReset() { return false; }
        bool endScene() { return false; }
        bool getTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG flag) const { (void)flag; return false; }
        bool queryFeature(irr::video::E_VIDEO_DRIVER_FEATURE feature) const { (void)feature; return false; }
        bool setClipPlane(irr::u32 index, const irr::core::plane3df& plane, bool enable=false) {
            (void)index; (void)plane; (void)enable; return false; }
        bool setRenderTarget(const irr::core::array<irr::video::IRenderTarget>& texture, bool clearBackBuffer=true,
            bool clearZBuffer=true, irr::video::SColor color=irr::video::SColor(0,0,0,0)) {
            (void)texture; (void)clearBackBuffer; (void)clearZBuffer; (void)color; return false; }
        bool setRenderTarget(irr::video::E_RENDER_TARGET target, bool clearTarget=true, bool clearZBuffer=true,
            irr::video::SColor color=irr::video::SColor(0,0,0,0)) {
            (void)target; (void)clearTarget; (void)clearZBuffer; (void)color; return false; }
        bool setRenderTarget(irr::video::ITexture* texture, bool clearBackBuffer=true, bool clearZBuffer=true,
            irr::video::SColor color=irr::video::SColor(0,0,0,0)) {
            (void)texture; (void)clearBackBuffer; (void)clearZBuffer; (void)color; return false; }
        bool writeImageToFile(irr::video::IImage* image, const irr::io::path& filename, irr::u32 param = 0) {
            (void)image; (void)filename; (void)param; return false; }
        bool writeImageToFile(irr::video::IImage* image, irr::io::IWriteFile* file, irr::u32 param =0) {
            (void)image; (void)file; (void)param; return false; }
        const irr::c8* getMaterialRendererName(irr::u32 idx) const { (void)idx; return nullptr; }
        const irr::core::dimension2d<irr::u32>& getCurrentRenderTargetSize() const {
            return mDummyDimension2du; }
        const irr::core::dimension2d<irr::u32>& getScreenSize() const {
            return mDummyDimension2du; }
        const irr::core::matrix4& getTransform(irr::video::E_TRANSFORMATION_STATE state) const {
            (void)state; return mDummyMatrix4; }
        const irr::core::rect<irr::s32>& getViewPort() const { return mDummyRect; }
        const irr::io::IAttributes& getDriverAttributes() const { return mDummyAttributes; }
        const irr::video::SExposedVideoData& getExposedVideoData() { return mDummyExposedVideoData; }
        const irr::video::SLight& getDynamicLight(irr::u32 idx) const { (void)idx; return mDummySLight; }
        const wchar_t* getName() const {return nullptr;}
        irr::core::dimension2du getMaxTextureSize() const { return irr::core::dimension2du(); }
        irr::core::stringc getVendorInfo() { return irr::core::stringc(); }
        irr::io::IAttributes* createAttributesFromMaterial(const irr::video::SMaterial& material,
            irr::io::SAttributeReadWriteOptions* options=0) { (void)material; (void)options; return nullptr; }
        irr::s32 addDynamicLight(const irr::video::SLight& light) { (void)light; return 0; }
        irr::s32 addMaterialRenderer(irr::video::IMaterialRenderer* renderer, const irr::c8* name =0) { (void)renderer; (void)name; return 0; }
        irr::s32 getFPS() const { return 0; }
        irr::scene::IMeshManipulator* getMeshManipulator() { return nullptr; }
        irr::u32 getDynamicLightCount() const { return 0; }
        irr::u32 getImageLoaderCount() const { return 0; }
        irr::u32 getImageWriterCount() const { return 0; }
        irr::u32 getMaterialRendererCount() const { return 0; }
        irr::u32 getMaximalDynamicLightAmount() const { return 0; }
        irr::u32 getMaximalPrimitiveCount() const { return 0; }
        irr::u32 getOcclusionQueryResult(irr::scene::ISceneNode* node) const { (void)node; return 0; }
        irr::u32 getPrimitiveCountDrawn( irr::u32 mode =0 ) const { (void)mode; return 0; }
        irr::u32 getTextureCount() const { return 0; }
        irr::video::E_DRIVER_TYPE getDriverType() const { return irr::video::EDT_NULL; }
        irr::video::ECOLOR_FORMAT getColorFormat() const { return irr::video::ECF_R8G8B8; }
        irr::video::IGPUProgrammingServices* getGPUProgrammingServices() { return nullptr; }
        irr::video::IImage* createImage(irr::video::ECOLOR_FORMAT format, const irr::core::dimension2d<irr::u32>& size) { (void)format; (void)size; return nullptr; }
        irr::video::IImage* createImage(irr::video::ITexture* texture, const irr::core::position2d<irr::s32>& pos, const irr::core::dimension2d<irr::u32>& size) { (void)texture; (void)pos; (void)size; return nullptr; }
        irr::video::IImage* createImageFromData(irr::video::ECOLOR_FORMAT format, const irr::core::dimension2d<irr::u32>& size, void *data, bool ownForeignMemory=false, bool deleteMemory = true) { (void)format; (void)size; (void)data; (void)ownForeignMemory; (void)deleteMemory; return nullptr; }
        irr::video::IImage* createImageFromFile(const irr::io::path& filename) { (void)filename; return nullptr; }
        irr::video::IImage* createImageFromFile(irr::io::IReadFile* file) { (void)file; return nullptr; }
        irr::video::IImage* createScreenShot(irr::video::ECOLOR_FORMAT format=irr::video::ECF_UNKNOWN, irr::video::E_RENDER_TARGET target=irr::video::ERT_FRAME_BUFFER) { (void)format; (void)target; return nullptr; }
        irr::video::IImageLoader* getImageLoader(irr::u32 n) { (void)n; return nullptr; }
        irr::video::IImageWriter* getImageWriter(irr::u32 n) { (void)n; return nullptr; }
        irr::video::IMaterialRenderer* getMaterialRenderer(irr::u32 idx) { (void)idx; return nullptr; }
        irr::video::ITexture* addRenderTargetTexture(const irr::core::dimension2d<irr::u32>& size, const irr::io::path& name = "rt", const irr::video::ECOLOR_FORMAT format = irr::video::ECF_UNKNOWN) { (void)size; (void)name; (void)format; return nullptr; }
        irr::video::ITexture* addTexture(const irr::core::dimension2d<irr::u32>& size, const irr::io::path& name, irr::video::ECOLOR_FORMAT format = irr::video::ECF_A8R8G8B8) { (void)size; (void)name; (void)format; return nullptr; }
        irr::video::ITexture* addTexture(const irr::io::path& name, irr::video::IImage* image, void* mipmapData=0) { (void)name; (void)image; (void)mipmapData; return nullptr; }
        irr::video::ITexture* findTexture(const irr::io::path& filename) { (void)filename; return nullptr; }
        irr::video::ITexture* getTexture(const irr::io::path& filename) { (void)filename; return nullptr; }
        irr::video::ITexture* getTexture(irr::io::IReadFile* file) { (void)file; return nullptr; }
        irr::video::ITexture* getTextureByIndex(irr::u32 index) { (void)index; return nullptr; }
        irr::video::SMaterial& getMaterial2D() { return mDummySMaterial;}
        irr::video::SOverrideMaterial& getOverrideMaterial() { return mDummySOverrideMaterial; }
        void addExternalImageLoader(irr::video::IImageLoader* loader) { (void)loader; }
        void addExternalImageWriter(irr::video::IImageWriter* writer) { (void)writer; }
        void addOcclusionQuery(irr::scene::ISceneNode* node, const irr::scene::IMesh* mesh=0) { (void)node; (void)mesh; }
        void clearZBuffer() {}
        void convertColor(const void* sP, irr::video::ECOLOR_FORMAT sF, irr::s32 sN, void* dP, irr::video::ECOLOR_FORMAT dF) const { (void)sP; (void)sF; (void)sN; (void)dP; (void)dF; }
        void deleteAllDynamicLights() {}
        void disableFeature(irr::video::E_VIDEO_DRIVER_FEATURE feature, bool flag=true) { (void)feature; (void)flag; }
        void draw2DImage(const irr::video::ITexture* texture, const irr::core::position2d<irr::s32>& destPos) { (void)texture; (void)destPos; }
        void draw2DImage(const irr::video::ITexture* texture, const irr::core::rect<irr::s32>& destRect, const irr::core::rect<irr::s32>& sourceRect, const irr::core::rect<irr::s32>* clipRect =0, const irr::video::SColor * const colors=0, bool useAlphaChannelOfTexture=false) { (void)texture; (void)destRect; (void)sourceRect; (void)clipRect; (void)colors; (void)useAlphaChannelOfTexture; }
        void draw2DImageBatch(const irr::video::ITexture* texture, const irr::core::array< irr::core::position2d<irr::s32> >& positions, const irr::core::array< irr::core::rect<irr::s32> >& sourceRects, const irr::core::rect<irr::s32>* clipRect=0, irr::video::SColor color=irr::video::SColor(255,255,255,255), bool useAlphaChannelOfTexture=false) { (void)texture; (void)positions; (void)sourceRects; (void)clipRect; (void)color; (void)useAlphaChannelOfTexture; }
        void draw2DImageBatch(const irr::video::ITexture* texture, const irr::core::position2d<irr::s32>& pos, const irr::core::array< irr::core::rect<irr::s32> >& sourceRects, const irr::core::array<irr::s32>& indices, irr::s32 kerningWidth=0, const irr::core::rect<irr::s32>* clipRect=0, irr::video::SColor color=irr::video::SColor(255,255,255,255), bool useAlphaChannelOfTexture=false) { (void)texture; (void)pos; (void)sourceRects; (void)indices; (void)kerningWidth; (void)clipRect; (void)color; (void)useAlphaChannelOfTexture; }
        void draw2DLine(const irr::core::position2d<irr::s32>& start, const irr::core::position2d<irr::s32>& end, irr::video::SColor color=irr::video::SColor(255,255,255,255)) { (void)start; (void)end; (void)color; }
        void draw2DPolygon(irr::core::position2d<irr::s32> center, irr::f32 radius, irr::video::SColor color=irr::video::SColor(100,255,255,255), irr::s32 vertexCount=10) { (void)center; (void)radius; (void)color; (void)vertexCount; }
        void draw2DRectangle(const irr::core::rect<irr::s32>& pos, irr::video::SColor colorLeftUp, irr::video::SColor colorRightUp, irr::video::SColor colorLeftDown, irr::video::SColor colorRightDown, const irr::core::rect<irr::s32>* clip =0) { (void)pos; (void)colorLeftUp; (void)colorRightUp; (void)colorLeftDown; (void)colorRightDown; (void)clip; }
        void draw2DRectangle(irr::video::SColor color, const irr::core::rect<irr::s32>& pos, const irr::core::rect<irr::s32>* clip =0) { (void)color; (void)pos; (void)clip; }
        void draw2DRectangleOutline(const irr::core::recti& pos, irr::video::SColor color=irr::video::SColor(255,255,255,255)) { (void)pos; (void)color; }
        void draw2DVertexPrimitiveList(const void* vertices, irr::u32 vertexCount, const void* indexList, irr::u32 primCount, irr::video::E_VERTEX_TYPE vType=irr::video::EVT_STANDARD, irr::scene::E_PRIMITIVE_TYPE pType=irr::scene::EPT_TRIANGLES, irr::video::E_INDEX_TYPE iType=irr::video::EIT_16BIT) { (void)vertices; (void)vertexCount; (void)indexList; (void)primCount; (void)vType; (void)pType; (void)iType; }
        void draw3DBox(const irr::core::aabbox3d<irr::f32>& box, irr::video::SColor color = irr::video::SColor(255,255,255,255)) { (void)box; (void)color; }
        void draw3DLine(const irr::core::vector3df& start, const irr::core::vector3df& end, irr::video::SColor color = irr::video::SColor(255,255,255,255)) { (void)start; (void)end; (void)color; }
        void draw3DTriangle(const irr::core::triangle3df& triangle, irr::video::SColor color = irr::video::SColor(255,255,255,255)) { (void)triangle; (void)color; }
        void drawMeshBuffer(const irr::scene::IMeshBuffer* mb) { (void)mb; }
        void drawMeshBufferNormals(const irr::scene::IMeshBuffer* mb, irr::f32 length=10.f, irr::video::SColor color=0xffffffff) { (void)mb; (void)length; (void)color; }
        void drawPixel(irr::u32 x, irr::u32 y, const irr::video::SColor& color) { (void)x; (void)y; (void)color; }
        void drawStencilShadow(bool clearStencilBuffer=false, irr::video::SColor leftUpEdge = irr::video::SColor(255,0,0,0), irr::video::SColor rightUpEdge = irr::video::SColor(255,0,0,0), irr::video::SColor leftDownEdge = irr::video::SColor(255,0,0,0), irr::video::SColor rightDownEdge = irr::video::SColor(255,0,0,0)) { (void)clearStencilBuffer; (void)leftUpEdge; (void)rightUpEdge; (void)leftDownEdge; (void)rightDownEdge; }
        void drawStencilShadowVolume(const irr::core::array< irr::core::vector3df>& triangles, bool zfail=true, irr::u32 debugDataVisible=0) { (void)triangles; (void)zfail; (void)debugDataVisible; }
        void drawVertexPrimitiveList(const void* vertices, irr::u32 vertexCount, const void* indexList, irr::u32 primCount, irr::video::E_VERTEX_TYPE vType=irr::video::EVT_STANDARD, irr::scene::E_PRIMITIVE_TYPE pType=irr::scene::EPT_TRIANGLES, irr::video::E_INDEX_TYPE iType=irr::video::EIT_16BIT) { (void)vertices; (void)vertexCount; (void)indexList; (void)primCount; (void)vType; (void)pType; (void)iType; }
        void enableClipPlane(irr::u32 index, bool enable) { (void)index; (void)enable; }
        void enableMaterial2D(bool enable=true) { (void)enable; }
        void fillMaterialStructureFromAttributes(irr::video::SMaterial& outMaterial, irr::io::IAttributes* attributes) { (void)outMaterial; (void)attributes; }
        void getFog(irr::video::SColor& color, irr::video::E_FOG_TYPE& fogType, irr::f32& start, irr::f32& end, irr::f32& density, bool& pixelFog, bool& rangeFog) { (void)color; (void)fogType; (void)start; (void)end; (void)density; (void)pixelFog; (void)rangeFog; }
        void makeColorKeyTexture(irr::video::ITexture* texture, irr::core::position2d<irr::s32> colorKeyPixelPos, bool zeroTexels = false) const { (void)texture; (void)colorKeyPixelPos; (void)zeroTexels; }
        void makeColorKeyTexture(irr::video::ITexture* texture, irr::video::SColor color, bool zeroTexels = false) const { (void)texture; (void)color; (void)zeroTexels; }
        void makeNormalMapTexture(irr::video::ITexture* texture, irr::f32 amplitude=1.0f) const { (void)texture; (void)amplitude; }
        void OnResize(const irr::core::dimension2d<irr::u32>& size) { (void)size; }
        void removeAllHardwareBuffers() {}
        void removeAllOcclusionQueries() {}
        void removeAllTextures() {}
        void removeHardwareBuffer(const irr::scene::IMeshBuffer* mb) { (void)mb; }
        void removeOcclusionQuery(irr::scene::ISceneNode* node) { (void)node; }
        void removeTexture(irr::video::ITexture* texture) { (void)texture; }
        void renameTexture(irr::video::ITexture* texture, const irr::io::path& newName) { (void)texture; (void)newName; }
        void runAllOcclusionQueries(bool visible=false) { (void)visible; }
        void runOcclusionQuery(irr::scene::ISceneNode* node, bool visible=false) { (void)node; (void)visible; }
        void setAllowZWriteOnTransparent(bool flag) { (void)flag; }
        void setAmbientLight(const irr::video::SColorf& color) { (void)color; }
        void setFog(irr::video::SColor color=irr::video::SColor(0,255,255,255), irr::video::E_FOG_TYPE fogType=irr::video::EFT_FOG_LINEAR, irr::f32 start=50.0f, irr::f32 end=100.0f, irr::f32 density=0.01f, bool pixelFog=false, bool rangeFog=false) { (void)color; (void)fogType; (void)start; (void)end; (void)density; (void)pixelFog; (void)rangeFog; }
        void setMaterial(const irr::video::SMaterial& material) { (void)material; }
        void setMaterialRendererName(irr::s32 idx, const irr::c8* name) { (void)idx; (void)name; }
        void setMinHardwareBufferVertexCount(irr::u32 count) { (void)count; }
        void setTextureCreationFlag(irr::video::E_TEXTURE_CREATION_FLAG flag, bool enabled=true) { (void)flag; (void)enabled; }
        void setTransform(irr::video::E_TRANSFORMATION_STATE state, const irr::core::matrix4& mat) { (void)state; (void)mat; }
        void setViewPort(const irr::core::rect<irr::s32>& area) { (void)area; }
        void turnLightOn(irr::s32 lightIndex, bool turnOn) { (void)lightIndex; (void)turnOn; }
        void updateAllOcclusionQueries(bool block=true) { (void)block; }
        void updateOcclusionQuery(irr::scene::ISceneNode* node, bool block=true) { (void)node; (void)block; }

    private:
        irr::core::dimension2d<irr::u32> mDummyDimension2du = irr::core::dimension2d<irr::u32>();
        irr::core::matrix4 mDummyMatrix4 = irr::core::matrix4();
        irr::core::rect<irr::s32> mDummyRect = irr::core::rect<irr::s32>();
        AttributesMock mDummyAttributes = AttributesMock();
        irr::video::SExposedVideoData mDummyExposedVideoData = irr::video::SExposedVideoData();
        irr::video::SLight mDummySLight = irr::video::SLight();
        irr::video::SMaterial mDummySMaterial = irr::video::SMaterial();
        irr::video::SOverrideMaterial mDummySOverrideMaterial = irr::video::SOverrideMaterial();
    };
}
