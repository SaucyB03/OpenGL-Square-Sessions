//
// Created by brado on 3/5/2023.
//

#include "Object.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


//Private////////////
void Object::assignBuffandArr(){
    glGenVertexArrays(1, &this->va);
    glGenBuffers(1, &this->vb);
    glGenBuffers(1, &this->eb);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->va);

    if(dynamic){
        glBindBuffer(GL_ARRAY_BUFFER, this->vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eb);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    }else {
        glBindBuffer(GL_ARRAY_BUFFER, this->vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eb);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3* sizeof(float)));
//    glEnableVertexAttribArray(1);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyway, so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

//Public//////////

Object::Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::mat4x3 vecColor, bool dynamic, int scWidth, int scHeight) : shader("../vertexShader.glsl", "../fragmentShader.glsl"){
    this->position = position;
    this->scale = scale;
    this->velocity = velocity;
    this->dynamic = dynamic;
    this->scWidth = scWidth;
    this->scHeight = scHeight;



//    float vertices[] = {
//            scale.x + position.x, position.y,               0.0f,  /* bottom right */  vecColor[0][0], vecColor[0][1], vecColor[0][2],
//            scale.x + position.x, scale.y + position.y,   0.0f,  /* top right */     vecColor[1][0], vecColor[1][1], vecColor[1][2],
//            position.x,            scale.y + position.y,  0.0f,  /* top left */     vecColor[2][0], vecColor[2][1], vecColor[2][2],
//            position.x,            position.y,              0.0f,   /* bottom left */ vecColor[3][0], vecColor[3][1], vecColor[3][2]
//    };
    float verts[] = {
            scale.x + position.x, position.y,               0.0f,  /* bottom right */
            scale.x + position.x, scale.y + position.y,   0.0f,  /* top right */
            position.x,            scale.y + position.y,  0.0f,  /* top left */
            position.x,            position.y,              0.0f   /* bottom left */
    };

    for(int i = 0; i < sizeof(vertices)/ sizeof(float ); ++i){
        vertices[i] = verts[i];
    }


    assignBuffandArr();
}

Object::~Object() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &this->eb);
}


void Object::move() {

}

void Object::display() {
    shader.bindShader();

    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(position, 0.0f));
    shader.setUniformMat4("transform", transform);

    glBindVertexArray(this->va); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
