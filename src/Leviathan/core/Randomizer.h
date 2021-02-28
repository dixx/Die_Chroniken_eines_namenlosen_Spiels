/*! \file Randomizer.h
 *  \brief Zufallszahlengenerator
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_RANDOMIZER_H
#define LEVIATHAN_CORE_RANDOMIZER_H

#include <cstdint>

namespace leviathan {
    namespace core {

        /*! \class Randomizer Randomizer.h "Randomizer.h"
         *  \brief Zufallszahlengenerator
         *         Die Berechnung basiert auf XORSHIFT mit 4 Seeds.
         */
        class Randomizer {
        public:
            /*! \brief Konstruktor.
             */
            Randomizer() = default;

            ~Randomizer() = default;
            Randomizer(const Randomizer&) = delete;
            Randomizer& operator=(const Randomizer&) = delete;

            /*! \brief Initialisiert den Zufallsgenerator.
             *  \attention Muss vor dem Benutzen der anderen Methoden aufgerufen werden,
             *             sonst werden bei jedem Programmstart dieselben Werte errechnet wie vorher!
             *  \param seed: Startwert
             */
            void start(const uint32_t seed);

            /*! \brief Berechnet eine Zufallszahl zwischen 0.0 und 0.9periode... (inklusive).
             *  \return Zufallszahl
             */
            float getFloat();

            /*! \brief Berechnet eine Zufallszahl zwischen min und max (inklusive).
             *  \return Zufallszahl
             */
            float getFloat(const float min, const float max);

            /*! \brief Berechnet eine Zufallszahl zwischen 0 und 4294967295 (inklusive).
             *  \return Zufallszahl
             */
            uint32_t getInt();

            /*! \brief Berechnet eine Zufallszahl zwischen min und max (inklusive).
             *  \return Zufallszahl
             */
            uint32_t getInt(const uint32_t min, const uint32_t max);

        private:
            uint32_t seed_, seed2_, seed3_, seed4_, tmp_;
        };
    }
}

#endif
