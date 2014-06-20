#include "ObjectParamsExtractor.h"



ObjectParamsExtractor::ObjectParamsExtractor( const core::stringc& objectData )
: extractedValue_(""),
  dummyValue_(""),
  result_(false),
  isUseless_(true)

{
    values_.clear();
    objectParams_.clear();
	if ( objectData.size() != 0 )
	{
	    objectData.split( objectParams_, "@" );
	    if ( objectParams_.size() != 0 )
	        isUseless_ = false;
	}
}



ObjectParamsExtractor::~ObjectParamsExtractor()
{
    values_.clear();
    objectParams_.clear();
}



void ObjectParamsExtractor::clearMembers()
{
    extractedValue_ = "";
    dummyValue_ = "";
    values_.clear();
    result_ = false;
}



bool ObjectParamsExtractor::tryToExtractValue(
        const core::stringc& key,
        const core::stringc& separator,
        const u32 index
)
{
    if ( key.size() == 0 || isUseless_ )
        return false;
    clearMembers();
    for ( register u32 i = 0; i < objectParams_.size(); ++i )
    {
        if ( objectParams_[ i ].equalsn( key, 5 ) == false )
            continue;
        if ( objectParams_[ i ].size() > 5 )
        {
            dummyValue_ = objectParams_[ i ].subString( 5, objectParams_[ i ].size() - 1 );
            if ( separator.size() != 0 )
            {
                dummyValue_.split( values_, separator.c_str() );
                if ( index < values_.size() )
                {
                    extractedValue_ = values_[ index ];
                    result_ = true;
                }
            }
            else
            {
                extractedValue_ = dummyValue_;
                result_ = true;
            }
        }
        else
        {
            result_ = true;
        }
        if ( result_ )
            break;
    }
    return result_;
}



const core::stringc& ObjectParamsExtractor::getExtractedValue() const
{
    return extractedValue_;
}
