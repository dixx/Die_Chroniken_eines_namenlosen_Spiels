/*! \file MapWithDefault.h
 *  \brief Einfacher std::map Wrapper mit Defaultwert.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_MAP_WITH_DEFAULT_H
#define LEVIATHAN_CORE_MAP_WITH_DEFAULT_H

#include <initializer_list>
#include <map>

namespace leviathan {
    namespace core {

        /*! \class MapWithDefault MapWithDefault.h "MapWithDefault.h"
         *  \brief std::map erweitert um einen Defaultwert für unbekannte Keys.
         */
        template<class Key, class Value>
        class MapWithDefault {
        public:
            /*! \brief Konstruktor. Wird mit Initialisierungsliste initialisiert.
             *  \note Der erste angegebene Wert wird als Defaultwert genutzt.
             */
            explicit MapWithDefault(std::initializer_list<std::pair<const Key, Value>> init)
            : map_(init), defaultValue_(init.begin()->second) {}

            /*! \brief Zugriffsoperator.
             *  \attention Anders als die std::map-Implementation liefert dieser Operator bei unbekanntem Key einen
             *             Defaultwert zurück und lässt die Map unverändert, anstatt einen neuen Eintrag anzulegen.
             *  \param key: Key für den zu suchenden Eintrag
             *  \return Referenz auf den gefundenen Eintrag oder den Defaultwert
             */
            const Value& operator[](const Key& key) {
                typename std::map<Key, Value>::const_iterator it = map_.find(key);
                return it == map_.end() ? defaultValue_ : it->second;
            };

        private:
            std::map<Key, Value> map_;
            Value defaultValue_;
        };
    }
}

#endif
