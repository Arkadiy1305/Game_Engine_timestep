#include "CMakeProject3.h"

Game game;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

GLfloat vertices[] = {
    200.f, 150.f,
    400.f, 500.f,
    600.f, 150.f,
};



int main()
{   
    const auto sizeOfScreen { glm::vec2 { 800.f, 600.f } };
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(sizeOfScreen.x, sizeOfScreen.y, "LearnOpenGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    // Set the required callback functions
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    // Define the viewport dimensions
    glViewport(0, 0, 800, 600);

    ShaderProgram mainShader("./resources/shaders/VertexShader.txt", "./resources/shaders/FragmentShader.txt");
    // Game loop
    VAO vao{};
    vao.create_vbo(sizeof(vertices), vertices);

    auto proj = glm::ortho(0.f, sizeOfScreen.x, 0.f, sizeOfScreen.y, -1.f, 1.f);
    mainShader.activate();
    mainShader.setMat4("proj", proj);
    auto speed { 0.f };
    auto amplitude { 100.f };
    const auto mat1 = glm::mat4 { 1.f };
    game.init();
    while (!glfwWindowShouldClose(window))
    {
        game.update();
        game.render();
        // Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();    
        auto now = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            speed += 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            speed -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            amplitude += 0.1f;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            amplitude -= 0.1f;
        }

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        mainShader.activate();
        vao.bind();
        auto model = glm::translate(mat1, glm::vec3(std::sin(now) * amplitude, std::cos(now) * amplitude, 0.f));
        model = glm::translate(model, glm::vec3(400.f, 250.f, 0.f));
        model = glm::rotate(model, static_cast<float>(now * speed), glm::vec3 { 0.f, 0.f, 1.f });
        model = glm::translate(model, glm::vec3(-400.f, -250.f, 0.f));       
        
        
        mainShader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    
    // Terminates GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    game.set_key(key, action);
}