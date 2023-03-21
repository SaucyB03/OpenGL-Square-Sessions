//
// Created by brado on 3/21/2023.
//

#ifndef M3OE_BKSOUCY_SHADER_H
#define M3OE_BKSOUCY_SHADER_H


#include "iostream"
using namespace std;

class Shader {
private:
    unsigned int program;

public:
    Shader(const string &vertexSource, const string &fragSource);
    ~Shader();

    string readFile(const string &fileName);
    void createShader(const char* sVert, const char* sFrag);
    void findErrors(unsigned int errorCheck, char type);

    void bindShader();

    //Uniforms:

};


#endif //M3OE_BKSOUCY_SHADER_H
