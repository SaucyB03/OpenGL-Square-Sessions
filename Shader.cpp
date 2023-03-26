//
// Created by brado on 3/21/2023.
//

#include "Shader.h"
#include <fstream>
#include <sstream>


Shader::Shader(const string &vertexSource, const string &fragSource) {
    string vert = readFile(vertexSource);
    string frag = readFile(fragSource);

    createShader(vert.c_str(),frag.c_str());
}

Shader::~Shader() {
    glDeleteProgram(program);
}

string Shader::readFile(const string &fileName) {
    ifstream stream(fileName);

    string line;
    stringstream ss;

    while(getline(stream, line)){
        ss << line << '\n';
    }
    return ss.str();
}

void Shader::createShader(const char *vertSource, const char *fragSource) {
    unsigned int vert, frag;
    const char* version = "#version 330";
    const char* vSources[] = {
            version,
            vertSource
    };
    const char* fSources[] = {
            version,
            fragSource
    };

    vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 2, vSources, NULL);
    glCompileShader(vert);
    findErrors(vert, 'v');

    frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 2, fSources, NULL);
    glCompileShader(frag);
    findErrors(frag, 'f');

    this->program = glCreateProgram();
    glAttachShader(this->program, vert);
    glAttachShader(this->program, frag);
    glLinkProgram(this->program);
    findErrors(program, 'p');

    glDeleteShader(vert);
    glDeleteShader(frag);
}

void Shader::findErrors(unsigned int errorCheck, char type) {
    int success;
    char infoLog[512];

    if(type == 'p'){
        glGetProgramiv(errorCheck, GL_LINK_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(errorCheck, 512, NULL, infoLog);
            cout << "ERROR : Shader : Program-Compile error\n" << infoLog << endl;
        }
    }else{
        glGetShaderiv(errorCheck, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(errorCheck, 512, NULL, infoLog);
            cout << "ERROR : Shader : Shader-Link error of Type: " << (type == 'v' ? "Vertex" : "Fragment") << "\n" << infoLog << endl;
        }
    }
}

void Shader::bindShader() {
    glUseProgram(this->program);
}

void Shader::setUniformMat4(const char *variableName, glm::mat4 &matrix) {
    glUniformMatrix4fv(glGetUniformLocation(this->program, variableName), 1, false, glm::value_ptr(matrix));
}

void Shader::setVec3(const char *variableName, glm::vec3 &vector) {
    glUniform3f(glGetUniformLocation(this->program, variableName), vector.x, vector.y, vector.z);
}



