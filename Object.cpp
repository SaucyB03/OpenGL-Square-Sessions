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
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eb);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_DYNAMIC_DRAW);
    }else {
        glBindBuffer(GL_ARRAY_BUFFER, this->vb);
        glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices), this->vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->eb);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->indices), this->indices, GL_STATIC_DRAW);
    }


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyway, so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

//Public//////////

Object::Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, bool dynamic, int scWidth, int scHeight){
    this->position = position;
    this->scale = scale;
    this->velocity = velocity;
    this->dynamic = dynamic;
    this->scWidth = scWidth;
    this->scHeight = scHeight;

    float verts[] = {
            scale.x + position.x - scWidth/2, position.y - scHeight/2,           0.0f,  // bottom right
            scale.x + position.x - scWidth/2, scale.y + position.y - scHeight/2, 0.0f,  // top right
            position.x - scWidth/2,           scale.y + position.y - scHeight/2, 0.0f,  // top left
            position.x - scWidth/2,           position.y - scHeight/2,          0.0f,   //bottom left
    };


    int i;
    for(i = 0; i < sizeof(vertices) / sizeof(float); ++i){
        if(i % 3 == 0){
            vertices[i] = verts[i] / (float) this->scWidth;
        }else{
            vertices[i] = verts[i] / (float) this->scHeight;
        }
    }

    assignBuffandArr();
}

Object::~Object() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &this->eb);
}


void Object::move(bool grounded, float speed, bool move, float deltaTime) {
    /*For move:
     * True = Right
     * False = Left */

    if(move){
        position.x += speed * deltaTime;
    }else{
        position.x -= speed * deltaTime;
    }

    if(!grounded && dynamic){
        velocity.y -= GRAVITY * deltaTime;
    }

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Object::display() {
    glBindVertexArray(this->va); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
