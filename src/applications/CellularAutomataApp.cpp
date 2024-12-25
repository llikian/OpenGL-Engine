/***************************************************************************************************
 * @file  CellularAutomataApp.cpp
 * @brief Implementation of the CellularAutomataApp class
 **************************************************************************************************/

#include "applications/CellularAutomataApp.hpp"

#include <cmath>
#include <ctime>
#include "maths/transformations.hpp"

CellularAutomataApp::CellularAutomataApp()
    : ApplicationBase("3D Game of Life"),
      wireframe(false), cullface(false), cursorVisible(false),
      shader(nullptr),
      projection(perspective(M_PI_4f, window.getRatio(), 0.1f, 200.0f)),
      camera(Point(0.0f, 2.0f, 5.0f)),
      ruleset("9-26/5-7,12-13,15/5/M"),
      cubeSize(50.0f),
      cube(Meshes::cube()) {

    /* ---- Repeatable Keys ---- */
    repeatableKeys.emplace(GLFW_KEY_W, false);
    repeatableKeys.emplace(GLFW_KEY_S, false);
    repeatableKeys.emplace(GLFW_KEY_A, false);
    repeatableKeys.emplace(GLFW_KEY_D, false);
    repeatableKeys.emplace(GLFW_KEY_SPACE, false);
    repeatableKeys.emplace(GLFW_KEY_LEFT_SHIFT, false);

    /* ---- GLFW Callbacks ---- */
    setCallbacks<CellularAutomataApp>(window, true, true, true, false, true, false);

    /* ---- Shaders ---- */
    std::string paths[2]{"shaders/cellular_automata/cellular_automata.vert", "shaders/cellular_automata/cellular_automata.frag"};
    shader = new Shader(paths, 2, "Game of Life");
    initUniforms();
}

CellularAutomataApp::~CellularAutomataApp() {
    delete shader;
}

void CellularAutomataApp::run() {
    Mesh wireframeCube = Meshes::wireframeCube();

    srand(std::time(nullptr));

    for(int i = 0 ; i < 8 ; ++i) {
        for(int j = 0 ; j < 8 ; ++j) {
            for(int k = 0 ; k < 8 ; ++k) {
                if(rand() % 2) {
                    cells[CELL_SIZE / 2 + i][CELL_SIZE / 2 + j][CELL_SIZE / 2 + k].state = ruleset.getStatesAmount() - 1;
                }
            }
        }
    }

    while(!glfwWindowShouldClose(window)) {
        handleEvents();

        glClearColor(0.1, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        updateUniforms();

        shader->setUniform("wireframeCube", false);
        for(int i = 0 ; i < CELL_SIZE ; ++i) {
            shader->setUniform("cellX", i);

            for(int j = 0 ; j < CELL_SIZE ; ++j) {
                shader->setUniform("cellY", j);

                for(int k = 0 ; k < CELL_SIZE ; ++k) {
                    shader->setUniform("cellZ", k);

                    if(cells[i][j][k].state > 0) {
                        cube.draw();
                    }
                }
            }
        }

        shader->use();
        shader->setUniform("wireframeCube", true);
        wireframeCube.draw();

        glfwSwapBuffers(window);
    }
}

void CellularAutomataApp::handleWindowSizeCallback(int width, int height) {
    ApplicationBase::handleWindowSizeCallback(width, height);

    projection[0][0] = 1.0f / (tanf(M_PI_4f / 2.0f) * window.getRatio());
}

void CellularAutomataApp::handleCursorPositionCallback(double xPos, double yPos) {
    if(!cursorVisible) {
        camera.look(vec2(xPos - mousePos.x, yPos - mousePos.y));
    }

    ApplicationBase::handleCursorPositionCallback(xPos, yPos);
}

void CellularAutomataApp::handleKeyEvent(int key) {
    switch(key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        case GLFW_KEY_Z:
            glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
            wireframe = !wireframe;
            break;
        case GLFW_KEY_C:
            (cullface ? glDisable : glEnable)(GL_CULL_FACE);
            cullface = !cullface;
            break;
        case GLFW_KEY_TAB:
            glfwSetInputMode(window, GLFW_CURSOR, cursorVisible ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
            cursorVisible = !cursorVisible;
            break;
        case GLFW_KEY_W:
            camera.move(CameraControls::forward, delta);
            break;
        case GLFW_KEY_S:
            camera.move(CameraControls::backward, delta);
            break;
        case GLFW_KEY_A:
            camera.move(CameraControls::left, delta);
            break;
        case GLFW_KEY_D:
            camera.move(CameraControls::right, delta);
            break;
        case GLFW_KEY_SPACE:
            camera.move(CameraControls::upward, delta);
            break;
        case GLFW_KEY_LEFT_SHIFT:
            camera.move(CameraControls::downward, delta);
            break;
        case GLFW_KEY_N:
            nextGeneration();
            break;
    }
}

void CellularAutomataApp::initUniforms() {
    shader->use();
}

void CellularAutomataApp::updateUniforms() {
    shader->setUniform("vpMatrix", camera.getVPmatrix(projection));
    shader->setUniform("cubeSize", cubeSize);
    shader->setUniform("cellSize", cubeSize / CELL_SIZE);
}

void CellularAutomataApp::nextGeneration() {
    unsigned int ip, jp, kp;
    unsigned int im, jm, km;

    for(unsigned int i = 0 ; i < CELL_SIZE ; ++i) {
        ip = (i + 1 + CELL_SIZE) % CELL_SIZE;
        im = (i - 1 + CELL_SIZE) % CELL_SIZE;

        for(unsigned int j = 0 ; j < CELL_SIZE ; ++j) {
            jp = (j + 1 + CELL_SIZE) % CELL_SIZE;
            jm = (j - 1 + CELL_SIZE) % CELL_SIZE;

            for(unsigned int k = 0 ; k < CELL_SIZE ; ++k) {
                Cell& cell = cells[i][j][k];

                kp = (k + 1 + CELL_SIZE) % CELL_SIZE;
                km = (k - 1 + CELL_SIZE) % CELL_SIZE;

                cell.neighbors = cells[ip][jp][kp].state > 0;
                cell.neighbors += cells[ip][jp][k].state > 0;
                cell.neighbors += cells[ip][jp][km].state > 0;
                cell.neighbors += cells[ip][j][kp].state > 0;
                cell.neighbors += cells[ip][j][k].state > 0;
                cell.neighbors += cells[ip][j][km].state > 0;
                cell.neighbors += cells[ip][jm][kp].state > 0;
                cell.neighbors += cells[ip][jm][k].state > 0;
                cell.neighbors += cells[ip][jm][km].state > 0;

                cell.neighbors += cells[i][jp][kp].state > 0;
                cell.neighbors += cells[i][jp][k].state > 0;
                cell.neighbors += cells[i][jp][km].state > 0;
                cell.neighbors += cells[i][j][kp].state > 0;
                cell.neighbors += cells[i][j][km].state > 0;
                cell.neighbors += cells[i][jm][kp].state > 0;
                cell.neighbors += cells[i][jm][k].state > 0;
                cell.neighbors += cells[i][jm][km].state > 0;

                cell.neighbors += cells[im][jp][kp].state > 0;
                cell.neighbors += cells[im][jp][k].state > 0;
                cell.neighbors += cells[im][jp][km].state > 0;
                cell.neighbors += cells[im][j][kp].state > 0;
                cell.neighbors += cells[im][j][k].state > 0;
                cell.neighbors += cells[im][j][km].state > 0;
                cell.neighbors += cells[im][jm][kp].state > 0;
                cell.neighbors += cells[im][jm][k].state > 0;
                cell.neighbors += cells[im][jm][km].state > 0;

                if(cell.state > 0) { // Cell is not dead
                    if(cell.state == ruleset.getStatesAmount() - 1) { // Cell is alive
                        if(!ruleset.survives(cell.neighbors)) { // Cell starts to die
                            cell.next = cell.state - 1;
                        }
                    } else { // Cell is dying
                        cell.next = cell.state - 1;
                    }
                } else if(ruleset.isBorn(cell.neighbors)) { // Cell will be born
                    cell.next = ruleset.getStatesAmount() - 1;
                }
            }
        }
    }

    for(unsigned int i = 0 ; i < CELL_SIZE ; ++i) {
        for(unsigned int j = 0 ; j < CELL_SIZE ; ++j) {
            for(unsigned int k = 0 ; k < CELL_SIZE ; ++k) {
                cells[i][j][k].flip();
            }
        }
    }
}
