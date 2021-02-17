#if !defined(DEBUG_H)
#define DEBUG_H

#ifdef LITTLEBUG
#define DEBUG(str) fprintf(stderr,"\033[1;m%s:%d: \033[1;31merror:\033[0m %s\n", __FILE__, __LINE__, str)
#define GL_DEBUG() {\
    switch (glGetError())\
    {\
    case GL_INVALID_ENUM:\
        DEBUG("GL_INVALID_ENUM");\
        break;\
    case GL_INVALID_VALUE:\
        DEBUG("GL_INVALID_VALUE");\
        break;\
    case GL_INVALID_OPERATION:\
        DEBUG("GL_INVALID_OPERATION");\
        break;\
    case GL_STACK_OVERFLOW:\
        DEBUG("GL_STACK_OVERFLOW");\
        break;\
    case GL_STACK_UNDERFLOW:\
        DEBUG("GL_STACK_UNDERFLOW");\
        break;\
    case GL_OUT_OF_MEMORY:\
        DEBUG("GL_OUT_OF_MEMORY");\
        break;\
    case GL_INVALID_FRAMEBUFFER_OPERATION:\
        DEBUG("GL_INVALID_FRAMEBUFFER_OPERATION");\
        break;\
    case GL_NO_ERROR:\
        fprintf(stderr, "%s:%d: GL_NO_ERROR\n", __FILE__, __LINE__);\
        break;\
    default:\
        fprintf(stderr, "%s:%d: DEFAULT\n", __FILE__, __LINE__);\
        break;\
    }\
}
#define DEBUGARR(arr, n) for(unsigned i=0; i<n; ++i) std::cerr << "(" << i << ")" << arr[i] << " ";std::cerr << std::endl;
#define PRINT(...) fprintf(stderr, __VA_ARGS__)
#define DEBUGSHADER(shader) {\
    for (unsigned i = 0; i < shader.linked; ++i) {\
        glGetShaderInfoLog(shader.shaders[shader.linked], 512, NULL, shader.infoLog);\
        PRINT("shader%d: %s\n", i, shader.infoLog);\
    }\
}
#else
#define DEBUG(str)
#define GL_DEBUG()
#define DEBUGARR(arr, n)
#define PRINT(...)
#define DEBUGSHADER(shader)
#endif



#endif // DEBUG_H
