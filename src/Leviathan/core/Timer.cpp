#include "Timer.h"

namespace leviathan {
    namespace core {

        Timer::Timer(const float maxValue) : mMaxValue(maxValue) {}

        Timer& Timer::tick(const float seconds) {
            if (mIsRunning && !mIsPaused) mCurrentValue += seconds;
            return *this;
        }

        void Timer::start() {
            mIsPaused = false;
            mIsRunning = true;
            mCurrentValue = 0.0f;
        }

        void Timer::restart() {
            mIsFull = false;
            start();
        }

        void Timer::stop() {
            mIsPaused = false;
            mIsRunning = false;
            mCurrentValue = 0.0f;
        }

        void Timer::pause() {
            if (mIsRunning) mIsPaused = true;
        }

        void Timer::resume() {
            if (mIsPaused) {
                mIsRunning = true;
                mIsPaused = false;
            }
        }

        bool Timer::isRunning() const {
            return mIsRunning;
        }

        bool Timer::isPaused() const {
            return mIsPaused;
        }

        bool Timer::isFull() {
            if (mCurrentValue >= mMaxValue) mIsFull = true;
            return mIsFull;
        }

        float Timer::getMaxValue() const {
            return mMaxValue;
        }
    }
}
