#include "irrlicht.h"
#include <cstdint>

// Fakeit keeps pointer to arguments beyond their lifetime and matches the given args too late, so we must implement
// our own mocks :(
namespace mocks {
    class AttributesMock : public irr::io::IAttributes {
    public:
        bool existsAttribute(const irr::c8* attributeName) { (void)attributeName; return false; }
        bool getAttributeAsBool(const irr::c8* attributeName) { (void)attributeName; return false; }
        bool getAttributeAsBool(irr::s32 index) { (void)index; return false; }
        bool read(irr::io::IXMLReader* reader, bool readCurrentElementOnly=false, const wchar_t* nonDefaultElementName = 0) { (void)reader; (void)readCurrentElementOnly; (void)nonDefaultElementName; return false; }
        bool write(irr::io::IXMLWriter* writer, bool writeXMLHeader=false, const wchar_t* nonDefaultElementName=0) { (void)writer; (void)writeXMLHeader; (void)nonDefaultElementName; return false; }
        const irr::c8* getAttributeAsEnumeration(const irr::c8* attributeName) { (void)attributeName; return nullptr; }
        const irr::c8* getAttributeAsEnumeration(irr::s32 index) { (void)index; return nullptr; }
        const irr::c8* getAttributeName(irr::s32 index) { (void)index; return nullptr; }
        const wchar_t* getAttributeTypeString(const irr::c8* attributeName) { (void)attributeName; return nullptr; }
        const wchar_t* getAttributeTypeString(irr::s32 index) { (void)index; return nullptr; }
        irr::core::aabbox3df getAttributeAsBox3d(const irr::c8* attributeName) { (void)attributeName; return irr::core::aabbox3df(); }
        irr::core::aabbox3df getAttributeAsBox3d(irr::s32 index) { (void)index; return irr::core::aabbox3df(); }
        irr::core::array<irr::core::stringw> getAttributeAsArray(const irr::c8* attributeName) { (void)attributeName; return irr::core::array<irr::core::stringw>(); }
        irr::core::array<irr::core::stringw> getAttributeAsArray(irr::s32 index) { (void)index; return irr::core::array<irr::core::stringw>(); }
        irr::core::dimension2d<irr::u32> getAttributeAsDimension2d(const irr::c8* attributeName) { (void)attributeName; return irr::core::dimension2d<irr::u32>(); }
        irr::core::dimension2d<irr::u32> getAttributeAsDimension2d(irr::s32 index) { (void)index; return irr::core::dimension2d<irr::u32>(); }
        irr::core::line2df getAttributeAsLine2d(const irr::c8* attributeName) { (void)attributeName; return irr::core::line2df(); }
        irr::core::line2df getAttributeAsLine2d(irr::s32 index) { (void)index; return irr::core::line2df(); }
        irr::core::line3df getAttributeAsLine3d(const irr::c8* attributeName) { (void)attributeName; return irr::core::line3df(); }
        irr::core::line3df getAttributeAsLine3d(irr::s32 index) { (void)index; return irr::core::line3df(); }
        irr::core::matrix4 getAttributeAsMatrix(const irr::c8* attributeName) { (void)attributeName; return irr::core::matrix4(); }
        irr::core::matrix4 getAttributeAsMatrix(irr::s32 index) { (void)index; return irr::core::matrix4(); }
        irr::core::plane3df getAttributeAsPlane3d(const irr::c8* attributeName) { (void)attributeName; return irr::core::plane3df(); }
        irr::core::plane3df getAttributeAsPlane3d(irr::s32 index) { (void)index; return irr::core::plane3df(); }
        irr::core::position2di getAttributeAsPosition2d(const irr::c8* attributeName) { (void)attributeName; return irr::core::position2di(); }
        irr::core::position2di getAttributeAsPosition2d(irr::s32 index) { (void)index; return irr::core::position2di(); }
        irr::core::quaternion getAttributeAsQuaternion(const irr::c8* attributeName) { (void)attributeName; return irr::core::quaternion(); }
        irr::core::quaternion getAttributeAsQuaternion(irr::s32 index) { (void)index; return irr::core::quaternion(); }
        irr::core::rect<irr::s32> getAttributeAsRect(const irr::c8* attributeName) { (void)attributeName; return irr::core::rect<irr::s32>(); }
        irr::core::rect<irr::s32> getAttributeAsRect(irr::s32 index) { (void)index; irr::core::rect<irr::s32>(); return irr::core::rect<irr::s32>(); }
        irr::core::stringc getAttributeAsString(const irr::c8* attributeName) { (void)attributeName; return irr::core::stringc(); }
        irr::core::stringc getAttributeAsString(irr::s32 index) { (void)index; return irr::core::stringc(); }
        irr::core::stringw getAttributeAsStringW(const irr::c8* attributeName) { (void)attributeName; return irr::core::stringw(); }
        irr::core::stringw getAttributeAsStringW(irr::s32 index) { (void)index; return irr::core::stringw(); }
        irr::core::triangle3df getAttributeAsTriangle3d(const irr::c8* attributeName) { (void)attributeName; return irr::core::triangle3df(); }
        irr::core::triangle3df getAttributeAsTriangle3d(irr::s32 index) { (void)index; return irr::core::triangle3df(); }
        irr::core::vector2df getAttributeAsVector2d(const irr::c8* attributeName) { (void)attributeName; return irr::core::vector2df(); }
        irr::core::vector2df getAttributeAsVector2d(irr::s32 index) { (void)index; return irr::core::vector2df(); }
        irr::core::vector3df getAttributeAsVector3d(const irr::c8* attributeName) { (void)attributeName; return irr::core::vector3df(); }
        irr::core::vector3df getAttributeAsVector3d(irr::s32 index) { (void)index; return irr::core::vector3df(); }
        irr::io::E_ATTRIBUTE_TYPE getAttributeType(const irr::c8* attributeName) { (void)attributeName; return irr::io::EAT_UNKNOWN; }
        irr::io::E_ATTRIBUTE_TYPE getAttributeType(irr::s32 index) { (void)index; return irr::io::EAT_UNKNOWN; }
        irr::f32 getAttributeAsFloat(const irr::c8* attributeName) { (void)attributeName; return 0.0f; }
        irr::f32 getAttributeAsFloat(irr::s32 index) { (void)index; return 0.0f; }
        irr::s32 findAttribute(const irr::c8* attributeName) const { (void)attributeName; return 0; }
        irr::s32 getAttributeAsEnumeration(const irr::c8* attributeName, const irr::c8* const* enumerationLiteralsToUse) { (void)attributeName; (void)enumerationLiteralsToUse; return 0; }
        irr::s32 getAttributeAsEnumeration(irr::s32 index, const irr::c8* const* enumerationLiteralsToUse) { (void)index; (void)enumerationLiteralsToUse; return 0; }
        irr::s32 getAttributeAsInt(const irr::c8* attributeName) const { (void)attributeName; return 0; }
        irr::s32 getAttributeAsInt(irr::s32 index) const { (void)index; return 0; }
        irr::u32 getAttributeCount() const { return 0; }
        irr::video::ITexture* getAttributeAsTexture(const irr::c8* attributeName) { (void)attributeName; return nullptr; }
        irr::video::ITexture* getAttributeAsTexture(irr::s32 index) { (void)index; return nullptr; }
        irr::video::SColor getAttributeAsColor(const irr::c8* attributeName) { (void)attributeName; return irr::video::SColor(); }
        irr::video::SColor getAttributeAsColor(irr::s32 index) { (void)index; return irr::video::SColor(); }
        irr::video::SColorf getAttributeAsColorf(const irr::c8* attributeName) { (void)attributeName; return irr::video::SColorf(); }
        irr::video::SColorf getAttributeAsColorf(irr::s32 index) { (void)index; return irr::video::SColorf(); }
        void addArray(const irr::c8* attributeName, const irr::core::array<irr::core::stringw>& value) { (void)attributeName; (void)value; }
        void addBinary(const irr::c8* attributeName, void* data, irr::s32 dataSizeInBytes) { (void)attributeName; (void)data; (void)dataSizeInBytes; }
        void addBool(const irr::c8* attributeName, bool value) { (void)attributeName; (void)value; }
        void addBox3d(const irr::c8* attributeName, irr::core::aabbox3df v) { (void)attributeName; (void)v; }
        void addColor(const irr::c8* attributeName, irr::video::SColor value) { (void)attributeName; (void)value; }
        void addColorf(const irr::c8* attributeName, irr::video::SColorf value) { (void)attributeName; (void)value; }
        void addDimension2d(const irr::c8* attributeName, irr::core::dimension2d<irr::u32> value) { (void)attributeName; (void)value; }
        void addEnum(const irr::c8* attributeName, const irr::c8* enumValue, const irr::c8* const* enumerationLiterals) { (void)attributeName; (void)enumValue; (void)enumerationLiterals; }
        void addEnum(const irr::c8* attributeName, irr::s32 enumValue, const irr::c8* const* enumerationLiterals) { (void)attributeName; (void)enumValue; (void)enumerationLiterals; }
        void addFloat(const irr::c8* attributeName, irr::f32 value) { (void)attributeName; (void)value; }
        void addInt(const irr::c8* attributeName, irr::s32 value) { (void)attributeName; (void)value; }
        void addLine2d(const irr::c8* attributeName, irr::core::line2df v) { (void)attributeName; (void)v; }
        void addLine3d(const irr::c8* attributeName, irr::core::line3df v) { (void)attributeName; (void)v; }
        void addMatrix(const irr::c8* attributeName, const irr::core::matrix4& v) { (void)attributeName; (void)v; }
        void addPlane3d(const irr::c8* attributeName, irr::core::plane3df v) { (void)attributeName; (void)v; }
        void addPosition2d(const irr::c8* attributeName, irr::core::position2di value) { (void)attributeName; (void)value; }
        void addQuaternion(const irr::c8* attributeName, irr::core::quaternion v) { (void)attributeName; (void)v; }
        void addRect(const irr::c8* attributeName, irr::core::rect<irr::s32> value) { (void)attributeName; (void)value; }
        void addString(const irr::c8* attributeName, const irr::c8* value) { (void)attributeName; (void)value; }
        void addString(const irr::c8* attributeName, const wchar_t* value) { (void)attributeName; (void)value; }
        void addTexture(const irr::c8* attributeName, irr::video::ITexture* texture, const irr::io::path& filename = "") { (void)attributeName; (void)texture; (void)filename; }
        void addTriangle3d(const irr::c8* attributeName, irr::core::triangle3df v) { (void)attributeName; (void)v; }
        void addUserPointer(const irr::c8* attributeName, void* userPointer) { (void)attributeName; (void)userPointer; }
        void addVector2d(const irr::c8* attributeName, irr::core::vector2df value) { (void)attributeName; (void)value; }
        void addVector3d(const irr::c8* attributeName, irr::core::vector3df value) { (void)attributeName; (void)value; }
        void clear() { }
        void getAttributeAsBinaryData(const irr::c8* attributeName, void* outData, irr::s32 maxSizeInBytes) { (void)attributeName; (void)outData; (void)maxSizeInBytes; }
        void getAttributeAsBinaryData(irr::s32 index, void* outData, irr::s32 maxSizeInBytes) { (void)index; (void)outData; (void)maxSizeInBytes; }
        void getAttributeAsString(const irr::c8* attributeName, irr::c8* target) { (void)attributeName; (void)target; }
        void getAttributeAsStringW(const irr::c8* attributeName, wchar_t* target) { (void)attributeName; (void)target; }
        void getAttributeEnumerationLiteralsOfEnumeration(const irr::c8* attributeName, irr::core::array<irr::core::stringc>& outLiterals) { (void)attributeName; (void)outLiterals; }
        void getAttributeEnumerationLiteralsOfEnumeration(irr::s32 index, irr::core::array<irr::core::stringc>& outLiterals) { (void)index; (void)outLiterals; }
        void setAttribute(const irr::c8* attributeName, bool value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, const irr::c8* enumValue, const irr::c8* const* enumerationLiterals) { (void)attributeName; (void)enumValue; (void)enumerationLiterals; }
        void setAttribute(const irr::c8* attributeName, const irr::c8* value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, const irr::core::array<irr::core::stringw>& value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, const irr::core::matrix4& v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, const wchar_t* value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, irr::core::aabbox3df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::dimension2d<irr::u32> v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::line2df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::line3df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::plane3df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::position2di v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::quaternion v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::rect<irr::s32> v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::triangle3df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::vector2df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::core::vector3df v) { (void)attributeName; (void)v; }
        void setAttribute(const irr::c8* attributeName, irr::f32 value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, irr::s32 value) { (void)attributeName; (void)value; }
        void setAttribute(const irr::c8* attributeName, irr::video::ITexture* texture, const irr::io::path& filename = "") { (void)attributeName; (void)texture; (void)filename; }
        void setAttribute(const irr::c8* attributeName, irr::video::SColor color) { (void)attributeName; (void)color; }
        void setAttribute(const irr::c8* attributeName, irr::video::SColorf color) { (void)attributeName; (void)color; }
        void setAttribute(const irr::c8* attributeName, void* data, irr::s32 dataSizeInBytes) { (void)attributeName; (void)data; (void)dataSizeInBytes; }
        void setAttribute(const irr::c8* attributeName, void* userPointer) { (void)attributeName; (void)userPointer; }
        void setAttribute(irr::s32 index, bool value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, const irr::c8* enumValue, const irr::c8* const* enumerationLiterals) { (void)index; (void)enumValue; (void)enumerationLiterals; }
        void setAttribute(irr::s32 index, const irr::c8* value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, const irr::core::array<irr::core::stringw>& value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, const irr::core::matrix4& v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, const wchar_t* value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, irr::core::aabbox3df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::dimension2d<irr::u32> v) { (void)index; (void)v;  }
        void setAttribute(irr::s32 index, irr::core::line2df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::line3df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::plane3df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::position2di v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::quaternion v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::rect<irr::s32> v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::triangle3df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::vector2df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::core::vector3df v) { (void)index; (void)v; }
        void setAttribute(irr::s32 index, irr::f32 value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, irr::s32 value) { (void)index; (void)value; }
        void setAttribute(irr::s32 index, irr::video::ITexture* texture, const irr::io::path& filename = "") { (void)index; (void)texture; (void)filename; }
        void setAttribute(irr::s32 index, irr::video::SColor color) { (void)index; (void)color; }
        void setAttribute(irr::s32 index, irr::video::SColorf color) { (void)index; (void)color; }
        void setAttribute(irr::s32 index, void* data, irr::s32 dataSizeInBytes) { (void)index; (void)data; (void)dataSizeInBytes; }
        void setAttribute(irr::s32 index, void* userPointer) { (void)index; (void)userPointer; }
        void* getAttributeAsUserPointer(const irr::c8* attributeName) { (void)attributeName; return nullptr; }
        void* getAttributeAsUserPointer(irr::s32 index) { (void)index; return nullptr; }
    };
}
