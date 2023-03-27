//spinesquare

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <chrono>

#include "Game.h"

using namespace std;


const int SC_WIDTH = 1600;
const int SC_HEIGHT = 1600;

/*Collects and passes data to python script / server
 */
void sendData(Game &game, string name){
    vector<string> playerData = game.gameInfo();
    playerData.insert(playerData.begin(), name);

    //Saves info to file
    ofstream spinSquare;
    spinSquare.open("../spinnysquare.txt", ios_base::app);
    spinSquare << "\n";
    for(int i = 0; i < playerData.size(); ++i){
        if(i < playerData.size() - 1) {
            spinSquare << playerData.at(i) << ", ";
        }else{
            spinSquare << playerData.at(i);
        }
    }
    spinSquare.close();

    system("py ../game.py playerData.at(0)");
}


int main(){
    //Lets user input a username so they can find their score on the server
    string name;
    cout << "Please enter a username for your score: ";
    cin >> name;

    while(name.length() > 20){
        cout << "Please enter a username under 20 characters: ";
        cin >> name;
    }

    //Window initialization:
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    GLFWwindow* window;
    window = glfwCreateWindow(SC_WIDTH, SC_HEIGHT, "Basic Game", NULL, NULL);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //make sure the window was created
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize glew to utilize OpenGl
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize glew" << endl;
        glfwTerminate();
        return -1;
    }

    //Create the Game:
    Game game = *new Game(SC_WIDTH, SC_HEIGHT);
    auto startTime = std::chrono::high_resolution_clock::now();

    //Game Loop:
    while(!glfwWindowShouldClose(window)){
        //calculate delta time between frames
        auto endTime = std::chrono::high_resolution_clock::now();
        double deltaTime = std::chrono::duration<double, std::milli>(endTime - startTime).count();
        deltaTime *= 0.001;

        startTime = std::chrono::high_resolution_clock::now();


        //get mouse position
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        yPos = SC_HEIGHT - yPos;

        //check inputs
        game.checkMouseInput(window, xPos, yPos, deltaTime);
        vector<bool> motion = game.checkKeyInput(window, deltaTime);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //run game time updates: collisions, movement, and rendering the characters
        game.checkCollisions(deltaTime);
        game.updateMotion(motion, deltaTime);
        game.renderAll();

        //refresh the window
        glfwSwapBuffers(window);
        glfwPollEvents();

        //check to see if the game is over
        game.gameOver(window);
    }
    sendData(game, name);
    glfwTerminate();
    return 0;
}
