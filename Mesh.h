#if !defined(VERTEX)
#define VERTEX

#include "Global.h"

template <class T>
struct Mesh
{
    unsigned VBO, EBO, VAO, indexSize;

    Mesh(std::vector<T>& vertices, std::vector<unsigned>& indices);
    void attr(unsigned loc, unsigned sizeOfAttr, int type, int normalized, unsigned stride, unsigned offset);
    void bind();
    void draw();
    ~Mesh();
};
template <class T>
Mesh<T>::Mesh(std::vector<T>& vertices, std::vector<unsigned>& indices): indexSize(indices.size())
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
        
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(T), vertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned), indices.data(), GL_STATIC_DRAW);
    
}

template <class T>
void Mesh<T>::attr(unsigned loc, unsigned sizeOfAttr, int type,  int normalized, unsigned stride, unsigned offset) {
    
    glVertexAttribPointer(loc, sizeOfAttr, type, normalized, stride * sizeof(T), (void*)(offset * sizeof(T)));
    glEnableVertexAttribArray(loc);
    
}
template <class T>
inline void Mesh<T>::bind() {
    glBindVertexArray(VAO);
}
template <class T>
inline void Mesh<T>::draw() {
    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
}
template <class T>
Mesh<T>::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

#endif // VERTEX
