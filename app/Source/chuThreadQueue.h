/*
  ==============================================================================

    chuThreadQueue.h
    Created: 29 Dec 2015 4:06:19pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef PATTERNQUEUE_H_INCLUDED
#define PATTERNQUEUE_H_INCLUDED

#include <vector>
#include <mutex>

// Simple (and naive) container wrapper to provide appropriate locking behavior
// for reading and writing to the frame data structure from separate threads.
// Ripe for optimization later.

template <class T>
class chuThreadQueue
{
public:
    typedef typename std::vector<T> frame_type;

    chuThreadQueue() {
        frame_complete = false;
    }

    ~chuThreadQueue() {
    }

    void start_frame() {
        std::unique_lock<std::mutex> guard(mutex);
        frame.clear();
        frame_complete = false;
    }

    void push_item(T& item) {
        std::unique_lock<std::mutex> guard(mutex);
        frame.push_back(item);
    }

    void finish_frame() {
        frame_complete = true;
        cv.notify_one();
    }

    void process_frame(std::function<void(frame_type)> action) {
        std::unique_lock<std::mutex> guard(mutex);
        while (!frame_complete) {
            cv.wait(guard);
        }
        action(frame);
        frame.clear();
        frame_complete = false;
    }

private:
    bool frame_complete;
    frame_type frame;
    std::mutex mutex;
    std::condition_variable cv;
};



#endif  // PATTERNQUEUE_H_INCLUDED
