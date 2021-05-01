/*
  ==============================================================================

    FrameSequence.h
    Created: 11 Dec 2019 11:37:27am
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include <vector>

struct FrameSequence
{
    std::vector<int> sequence;
    bool isLooped = false;
    bool hasRelease = false;
    int loopStartIndex = 0;
    int releaseSequenceStartIndex = 0;
    static const int SHOULD_RETIRE = 65535;

    int valueAt (int index)
    {
        if (index < 0 || index >= sequence.size())
        {
            return 0;
        }

        return sequence[index];
    }

    int nextIndexOf (int current)
    {
        if (current < releaseSequenceStartIndex)  // Hold
        {
            if (current == releaseSequenceStartIndex - 1)  // Reached to the end
            {
                if (isLooped)
                {
                    return loopStartIndex;
                }
                else
                {
                    return current; // Hold the last value
                }
            }
            else
            {
                return current + 1;
            }

            // No reach here
        }
        else     // Released
        {
            if (current >= sequence.size() - 1)  // Reached to the end
            {
                return SHOULD_RETIRE;
            }
            else
            {
                return current + 1;
            }

            // No reach here
        }

        // No reach here
    }
    
    bool isInRelease(int index) {
        return index >= releaseSequenceStartIndex;
    }
};
