/*
* Copyright (c) 2010-2017 OTClient <https://github.com/edubart/otclient>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "declarations.h"

#include <framework/core/declarations.h>
#include <framework/core/timer.h>

enum AnimationPhase : int16
{
    AnimPhaseAutomatic = -1,
    AnimPhaseRandom = 254,
    AnimPhaseAsync = 255,
};

enum AnimationDirection : uint8
{
    AnimDirForward = 0,
    AnimDirBackward = 1
};

using PhaseDurations = std::vector<std::pair<int, int>>;

class Animator : public std::enable_shared_from_this<Animator>
{
public:
    Animator();

    void unserialize(int animationPhases, const FileStreamPtr& fin);
    void serialize(const FileStreamPtr& fin);
    void copy(const AnimatorPtr& other);

    void setPhase(int phase);
    int getPhase();
    int getPhaseAt(Timer& timer, uint32_t randomSeed, int lastPhase = 0);

    int getStartPhase();
    int getAnimationPhases() { return m_animationPhases; }
    bool isAsync() { return m_async; }
    bool isComplete() { return m_isComplete; }

    ticks_t getTotalDuration(uint32_t randomSeed);

    void resetAnimation();

private:
    int getPingPongPhase();
    int getLoopPhase();
    int getPhaseDuration(int phase);
    void calculateSynchronous();

    int m_animationPhases;
    int m_startPhase;
    int m_loopCount;
    bool m_async;
    std::shared_ptr<PhaseDurations> m_phaseDurations;

    int m_currentDuration;
    AnimationDirection m_currentDirection;
    int m_currentLoop;

    ticks_t m_lastPhaseTicks;
    bool m_isComplete;

    int m_phase;
};

#endif
