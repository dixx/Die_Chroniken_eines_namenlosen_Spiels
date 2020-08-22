#include "irrlicht.h"

// Fakeit cannot mock classes with multiple inheritance, so we must implement our own mocks :(
namespace mocks {
    class ICameraSceneNodeMock : public irr::scene::ICameraSceneNode {
    public:
        irr::f32 mFarValue = 0.0f;

        ICameraSceneNodeMock(irr::scene::ISceneNode* parent = nullptr, irr::scene::ISceneManager* mgr = nullptr,
            irr::s32 id = -1, const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0))
        : irr::scene::ICameraSceneNode(parent, mgr, id, position) {}
        void setProjectionMatrix(const irr::core::matrix4& projection, bool isOrthogonal = false) {
            (void)projection;
            (void)isOrthogonal;
        }
        const irr::core::matrix4& getProjectionMatrix() const {
            return mDummyMatrix;
        }
        const irr::core::matrix4& getViewMatrix() const {
            return mDummyMatrix;
        }
        void setViewMatrixAffector(const irr::core::matrix4& affector) {
            (void)affector;
        }
        const irr::core::matrix4& getViewMatrixAffector() const {
            return mDummyMatrix;
        }
        bool OnEvent(const irr::SEvent& event) {
            (void)event;
            return false;
        }
        void setTarget(const irr::core::vector3df& pos) {
            (void)pos;
        }
        void setRotation(const irr::core::vector3df& rotation) {
            (void)rotation;
        }
        const irr::core::vector3df& getTarget() const {
            return mDummyVector;
        }
        void setUpVector(const irr::core::vector3df& pos) {
            (void)pos;
        }
        const irr::core::vector3df& getUpVector() const {
            return mDummyVector;
        }
        irr::f32 getNearValue() const {
            return 0.0f;
        }
        irr::f32 getFarValue() const {
            return 0.0f;
        }
        irr::f32 getAspectRatio() const {
            return 0.0f;
        }
        irr::f32 getFOV() const {
            return 0.0f;
        }
        void setNearValue(irr::f32 zn) {
            (void)zn;
        }
        void setFarValue(irr::f32 zf) {
            mFarValue = zf;
        }
        void setAspectRatio(irr::f32 aspect) {
            (void)aspect;
        }
        void setFOV(irr::f32 fovy) {
            (void)fovy;
        }
        const irr::scene::SViewFrustum* getViewFrustum() const {
            return nullptr;
        }
        void setInputReceiverEnabled(bool enabled) {
            (void)enabled;
        }
        bool isInputReceiverEnabled() const {
            return false;
        }
        bool isOrthogonal() const {
            return false;
        }
        void bindTargetAndRotation(bool bound) {
            (void)bound;
        }
        bool getTargetAndRotationBinding(void) const {
            return false;
        }
        void serializeAttributes(irr::io::IAttributes* out, irr::io::SAttributeReadWriteOptions* options = 0) const {
            (void)out;
            (void)options;
        }
        void deserializeAttributes(irr::io::IAttributes* in, irr::io::SAttributeReadWriteOptions* options = 0) {
            (void)in;
            (void)options;
        }
        void render() {}
        const irr::core::aabbox3d<irr::f32>& getBoundingBox() const {
            return mDummyBBox;
        }

    private:
        irr::core::vector3df mDummyVector = irr::core::vector3df();
        irr::core::matrix4 mDummyMatrix = irr::core::matrix4();
        irr::core::aabbox3d<irr::f32> mDummyBBox = irr::core::aabbox3d<irr::f32>();
    };
}
