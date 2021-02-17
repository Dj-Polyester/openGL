#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Clock.h"

int main(void)
{
    /* Create a windowed mode window and its OpenGL context */
    sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Hello World");
    sf::Clock clock;

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    
    Shader shader;
    shader.read("tri.vs", GL_VERTEX_SHADER);
    shader.read("tri.fs", GL_FRAGMENT_SHADER);
    shader.link();

    std::vector<float> vertices = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    std::vector<unsigned> indices = {
        0, 1, 3, // first triangle
        1, 2, 3 // second triangle
    };
    Mesh<float> triangle(vertices, indices);
    triangle.attr(0, 3, GL_FLOAT,GL_FALSE,8, 0);
    triangle.attr(1, 3, GL_FLOAT,GL_FALSE,8, 3);
    triangle.attr(2, 2, GL_FLOAT,GL_FALSE,8, 6);
    
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    Texture texture;
    texture.gen();
    texture.param(GL_TEXTURE_WRAP_S, GL_REPEAT);	
    texture.param(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture.param(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    texture.param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.load("wall.jpg");
    texture.gen();
    texture.param(GL_TEXTURE_WRAP_S, GL_REPEAT);	
    texture.param(GL_TEXTURE_WRAP_T, GL_REPEAT);
    texture.param(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    texture.param(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.load("laugh.png");
    texture.set(shader);

    bool running = true;
    INITBENCHSECS();
    while (running)
    {
        // handle events
        POLLEVENT();
        
        // clear the buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // draw...
        texture.bind(0);
        texture.bind(1);
        
        shader.use();
        triangle.bind();
        triangle.draw();

        BENCHSECSR();

        window.display();
    }
    return 0;
}