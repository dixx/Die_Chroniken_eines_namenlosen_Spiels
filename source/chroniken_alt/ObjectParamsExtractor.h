/*! \file ObjectParamsExtractor.h
 *  \brief Klasse stellt Methoden zur Extraktion von Parameter-Werten aus textuellen Objektbeschreibungen bereit.
 */

#ifndef _OBJECTPARAMSEXTRACTOR_HEADER
#define _OBJECTPARAMSEXTRACTOR_HEADER

#include <irrlicht.h>

/*! \class ObjectParamsExtractor ObjectParamsExtractor.h "ObjectParamsExtractor.h"
 *  \brief Schnittstelle für Extraktion von Parameter-Werten aus textuellen Objektbeschreibungen
 */
class ObjectParamsExtractor
{

public:

    /*! \brief Konstruktor.
     *  \param objectData (\a const \a core::stringc&) textuelle Beschreibung des Objects
     */
    ObjectParamsExtractor( const irr::core::stringc& objectData );

    /*! \brief Destruktor.
     */
    ~ObjectParamsExtractor();

    /*! \brief Extrahiert einen Wert passend zum Key aus der Objektbeschreibung, wenn möglich.
     *  \param key (\a const \a core::stringc&) Key
     *  \param separator (\a const \a core::stringc&) Trennzeichen für Werte-Auflistungen
     *  \param index (\a const \a u32) Index des Wertes (bei Werte-Auflistungen)
     *  \return `true` wenn ein oder mehrere Werte extrahiert wurden und der gewünschte Index vorhanden ist,
     *          ansonsten `false`
     */
    bool tryToExtractValue( const irr::core::stringc& key, const irr::core::stringc& separator = "", const irr::u32 index = 0 );

    /*! \brief Liefert den zuletzt extrahierten Wert zurück.
     *  \param -
     *  \return \a const \a core::stringc& zuletzt extrahierter Wert
     */
    const irr::core::stringc& getExtractedValue() const;

private:

    irr::core::array<irr::core::stringc> objectParams_;
    irr::core::array<irr::core::stringc> values_;
    irr::core::stringc extractedValue_;
    irr::core::stringc dummyValue_;
    bool result_;
    bool isUseless_;

    void clearMembers();

};

#endif
