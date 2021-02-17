#if !defined(WINDOW_H)
#define WINDOW_H

#include "Global.h"

#define POLLEVENT() \
sf::Event event; \
while (window.pollEvent(event)) \
{ \
    if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) \
    { \
        running = false; \
    } \
    else if (event.type == sf::Event::Resized) \
    { \
        glViewport(0, 0, event.size.width, event.size.height); \
    } \
} 

#endif // WINDOW_H
