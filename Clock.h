#if !defined(CLOCK_H)
#define CLOCK_H

#include "Global.h"

#ifdef LITTLEBENCH
    #define BENCH() {\
        float secs = clock.getElapsedTime().asSeconds();\
        fprintf(stdout,"FPS: %f latency: %f\n", 1.0f / secs, secs);\
	    clock.restart().asSeconds();\
    }
    #define INITBENCHSECS() float frames = 0, sumframes = 0, sumsecs = 0;
    #define BENCHSECS() {\
        float secs = clock.getElapsedTime().asSeconds();\
        float frame = 1.0f / secs;\
        sumsecs+=secs;\
        sumframes+=frame;\
        ++frames;\
        if(sumsecs >= 1.0f) {\
            fprintf(stdout,"FPS: %f %f\n", sumframes/frames, frames);\
            frames = sumframes = sumsecs = 0;\
        }\
	    clock.restart().asSeconds();\
    }
    #define BENCHSECSR() {\
        float secs = clock.getElapsedTime().asSeconds();\
        float frame = 1.0f / secs;\
        sumsecs+=secs;\
        sumframes+=frame;\
        ++frames;\
        if(sumsecs >= 1.0f) {\
            fprintf(stderr,"\rFPS: %f", sumframes/frames);\
            frames = sumframes = sumsecs = 0;\
        }\
	    clock.restart().asSeconds();\
    }
#else
    #define BENCH()
    #define INITBENCHSECS()
    #define BENCHSECS()
    #define BENCHSECSR()
#endif

#endif // CLOCK_H
