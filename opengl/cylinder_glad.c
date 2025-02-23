// https://gen.glad.sh/#generator=c&api=gl%3D3.3&profile=gl%3Dcore%2Cgles1%3Dcommon&options=HEADER_ONLY%2CLOADER
// https://gen.glad.sh/#generator=c&api=gl%3D3.3&profile=gl%3Dcore%2Cgles1%3Dcommon&options=LOADER
//gcc cylinder_glad.c glad_loader/src/gl.c -o cylinder_glad -Iglad_loader/include -lglfw -lGL -lm
//./cylinder_glad


#include <glad/gl.h> // Use GLAD instead of GLEW
#include <GLFW/glfw3.h>  // GLFW for window creation

#include <stdio.h>
#include <math.h>

// Vertex Shader Source Code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform float angle;\n"
    "void main() {\n"
    "   float c = cos(angle);\n"
    "   float s = sin(angle);\n"
    "   mat4 rotation = mat4(\n"
    "       c, 0.0, s, 0.0,\n"
    "       0.0, 1.0, 0.0, 0.0,\n"
    "      -s, 0.0, c, 0.0,\n"
    "       0.0, 0.0, 0.0, 1.0);\n"
    "   gl_Position = rotation * vec4(aPos, 1.0);\n"
    "}";

// Fragment Shader Source Code
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(0.0, 0.8, 1.0, 1.0);\n"
    "}";

// Function to compile shaders
GLuint createShader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Shader Compilation Error: %s\n", infoLog);
    }
    return shader;
}

// Function to create OpenGL program
GLuint createShaderProgram() {
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader Linking Error: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

// Cube vertex data
float cubeVertices[] = {
    // Front face
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

    // Back face
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f
};

// Indices for drawing the cube using GL_TRIANGLES
unsigned int cubeIndices[] = {
    // Front face
    0, 1, 2, 2, 3, 0,
    // Back face
    4, 5, 6, 6, 7, 4,
    // Left face
    4, 0, 3, 3, 7, 4,
    // Right face
    1, 5, 6, 6, 2, 1,
    // Top face
    3, 2, 6, 6, 7, 3,
    // Bottom face
    4, 5, 1, 1, 0, 4
};

// Function to initialize OpenGL and create a window
int initOpenGL(GLFWwindow **window) {
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return 0;
    }

    *window = glfwCreateWindow(800, 600, "Rotating Cube", NULL, NULL);
    if (!*window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(*window);

    if (!gladLoaderLoadGL()) {
        printf("Failed to initialize GLAD\n");
        return 0;
    }

    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    return 1;
}

int main() {
    GLFWwindow *window;
    if (!initOpenGL(&window)) return -1;

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);

    int angleLoc = glGetUniformLocation(shaderProgram, "angle");

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float angle = (float)glfwGetTime(); // Rotate over time
        glUniform1f(angleLoc, angle);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
