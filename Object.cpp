//
// Created by brado on 3/5/2023.
//

#include "Object.h"
#include <GL/glew.h>
#include <glm/glm.hpp>


//Private////////////
/* assignBuffandArr
 * Assigned the Buffers and Vertex arrays for this object as well as store the information in a
 * Element array Buffer, which allows us to put 2 triangles together and have OpenGL know what to do
 */
void Object::assignBuffandArr(){
    //Assign Buffers and arrays
    glGenVertexArrays(1, &this->va);
    glGenBuffers(1, &this->vb);
    glGenBuffers(1, &this->eb);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(this->va);

    //If its dynamic tell OpenGl to draw it dynamically otherwise it will remain static
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

    //Assign vertex attribut pointer telling OpenGL how the array of verts is orgamized
    //i.e tell it if there is an offset or a stride it needs to be aware of
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    // Unbinds the buffer and vertex array now that we are done with them
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

//Public//////////
/* Object Constructor
 * Holds info about: position, scale, velocity, color, if its dynamic / static, and the screen size
 */
Object::Object(glm::vec2 position, glm::vec2 scale, glm::vec2 velocity, glm::vec3 color, bool dynamic, int scWidth, int scHeight){
    this->position = position;
    this->scale = scale;
    this->velocity = velocity;
    this->dynamic = dynamic;
    this->scWidth = scWidth;
    this->scHeight = scHeight;
    this->color = color;

    //Initializes verticies
    float verts[] = {
            scale.x, 0.0,      0.0f,  /* bottom right */
            scale.x, scale.y,  0.0f,  /* top right */
            0.0,     scale.y,  0.0f,  /* top left */
            0.0,     0.0,     0.0f   /* bottom left */
    };


    //Alters verts from being between 0 to scWidth or 0 to scHeight its between -1 - 1
    for(int i = 0; i < sizeof(vertices)/ sizeof(float); ++i){
        if(i % 3 == 0){
            vertices[i] = (verts[i] / (float)scWidth) * 2 - 1;
        }else if((i-1) % 3 == 0){
            vertices[i] = (verts[i] / (float)scHeight) * 2 - 1;
        }else{
            vertices[i] = verts[i];
        }
    }

    assignBuffandArr();
}

//Destructor:
Object::~Object() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &this->eb);
}

/* Basic move
 * if there's a velocity on the object then it updates it from the last frame
 */
void Object::move(float deltaTime) {
    if(dynamic) {
        if (velocity.x != 0) {
            position.x += velocity.x * deltaTime;
        }
        if (velocity.y != 0) {
            position.y += velocity.y * deltaTime;
        }
    }
}

/*Display
 * Applys any transformations the object has had and displays the object
 */
void Object::display(Shader* shader) {
    //Calculating Transforms:
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3((position.x * 2 / (float)scWidth), (position.y * 2 / (float)scHeight), 0.0f));

    //Applying transforms
    shader->setUniformMat4("transform", transform);
    shader->setVec3("color", color);

    //Displaying object
    glBindVertexArray(this->va); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

/*getPostion
 * returns the objects position as a vec2
 */
glm::vec2 Object::getPosition() {
    return position;
}

/*getVelocity
 * returns the objects velocity as a vec2
 */
glm::vec2 Object::getVelocity() {
    return velocity;
}

/*getScale
 * returns the objects scale as a vec2
 */
glm::vec2 Object::getScale() {
    return scale;
}

/* setVelocity
 * sets the velocity to the inputted vec2
 */
void Object::setVelocity(glm::vec2 newVelocity) {
    this->velocity = newVelocity;
}
