#ifndef SCREENDISPLAYER_H_
#define SCREENDISPLAYER_H_

#include "Game.h"
#include "Platform.h"

namespace gameplay
{

/**
 * Used for displaying screens (i.e. splash or level loading screens).
 */
class ScreenDisplayer
{
public:

    /**
     * Constructor.
     */
    ScreenDisplayer();

    /**
     * Destructor.
     */
    ~ScreenDisplayer();

    /**
     * Displays a screen using the {@link Game#renderOnce} mechanism for at least the given amount of time.
     * 
     * @param instance See {@link Game#renderOnce}.
     * @param method See {@link Game#renderOnce}.
     * @param cookie See {@link Game#renderOnce}.
     * @param time The minimum amount of time to display the screen (in milliseconds).
     */
    template <typename T> void run(T* instance, void (T::*method) (void*), void* cookie, unsigned long time);

    /**
     * Starts a new screen displayer running; draws a screen using the {@link Game#renderOnce} mechanism for at least the given amount of time.
     * 
     * Note: this is intended for use from Lua scripts.
     * 
     * @param function See {@link Game#renderOnce(const char*)}.
     * @param time The minimum amount of time to display the screen (in milliseconds).
     */
    static void start(const char* function, unsigned long time);

    /**
     * Finishes running the current screen displayer.
     * 
     * Note: this is intended for use from Lua scripts.
     */
    static void finish();

private:

    long _time;
    double _startTime;
    static ScreenDisplayer* __scriptInstance;
};

template <typename T> void ScreenDisplayer::run(T* instance, void (T::*method) (void*), void* cookie, unsigned long time)
{
    _time = time;
    Game::getInstance()->renderOnce(instance, method, cookie);
    _startTime = Game::getInstance()->getGameTime();
}

/**
 * Displays a screen using the {@link Game#renderOnce} mechanism for at least the given amount
 * of time. This function is intended to be called at the beginning of a block of code that is be 
 * executed while the screen is displayed (i.e. Game#initialize). This function will block 
 * at the end of the block of code in which it is called for the amount of time that has not yet elapsed.
 * 
 * @param instance See {@link Game#renderOnce}.
 * @param method See {@link Game#renderOnce}.
 * @param cookie See {@link Game#renderOnce}.
 * @param time The minimum amount of time to display the screen (in milliseconds).
 */
#define displayScreen(instance, method, cookie, time) \
    ScreenDisplayer __##instance##ScreenDisplayer; \
    __##instance##ScreenDisplayer.run(instance, method, cookie, time)

}

#endif
