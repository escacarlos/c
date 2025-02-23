// gcc main.c -o cylinder -lGLEW -lglfw -lGL -lm

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define NUM_SEGMENTS 36

// Vertex Shader
const char *vertexShaderSrc = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "layout(location = 1) in vec2 aTexCoord;\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "out vec2 TexCoord;\n"
    "void main() {\n"
    "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "}\n";

// Fragment Shader
const char *fragmentShaderSrc = "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D texture1;\n"
    "void main() {\n"
    "   FragColor = texture(texture1, TexCoord);\n"
    "}\n";

// Shader Compilation Function
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

// Create Shader Program
GLuint createShaderProgram() {
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

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

// Generate Cylinder
void generateCylinder(float **vertices, unsigned int **indices, int *vertexCount, int *indexCount) {
    int numVertices = (NUM_SEGMENTS + 1) * 2;
    int numIndices = NUM_SEGMENTS * 6;
    
    *vertices = (float *)malloc(numVertices * 5 * sizeof(float));
    *indices = (unsigned int *)malloc(numIndices * sizeof(unsigned int));

    float angleStep = 2.0f * M_PI / NUM_SEGMENTS;
    for (int i = 0; i <= NUM_SEGMENTS; i++) {
        float angle = i * angleStep;
        float x = cosf(angle);
        float z = sinf(angle);

        (*vertices)[i * 5] = x;
        (*vertices)[i * 5 + 1] = 1.0f;
        (*vertices)[i * 5 + 2] = z;
        (*vertices)[i * 5 + 3] = (float)i / NUM_SEGMENTS;
        (*vertices)[i * 5 + 4] = 1.0f;

        (*vertices)[(NUM_SEGMENTS + 1 + i) * 5] = x;
        (*vertices)[(NUM_SEGMENTS + 1 + i) * 5 + 1] = -1.0f;
        (*vertices)[(NUM_SEGMENTS + 1 + i) * 5 + 2] = z;
        (*vertices)[(NUM_SEGMENTS + 1 + i) * 5 + 3] = (float)i / NUM_SEGMENTS;
        (*vertices)[(NUM_SEGMENTS + 1 + i) * 5 + 4] = 0.0f;
    }

    for (int i = 0; i < NUM_SEGMENTS; i++) {
        (*indices)[i * 6] = i;
        (*indices)[i * 6 + 1] = i + 1;
        (*indices)[i * 6 + 2] = NUM_SEGMENTS + 1 + i;

        (*indices)[i * 6 + 3] = i + 1;
        (*indices)[i * 6 + 4] = NUM_SEGMENTS + 1 + i + 1;
        (*indices)[i * 6 + 5] = NUM_SEGMENTS + 1 + i;
    }

    *vertexCount = numVertices;
    *indexCount = numIndices;
}

int main() {
    if (!glfwInit()) return -1;
    GLFWwindow *window = glfwCreateWindow(800, 600, "Rotating Cylinder", NULL, NULL);
    if (!window) return -1;
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);  // ✅ Enable depth buffer

    float *vertices;
    unsigned int *indices;
    int vertexCount, indexCount;
    generateCylinder(&vertices, &indices, &vertexCount, &indexCount);

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * 5 * sizeof(float), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint shaderProgram = createShaderProgram();
    glUseProgram(shaderProgram);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        printf("Texture Data Loaded: %p\n", data);
    } else {
        printf("Failed to load texture\n");
    }
    stbi_image_free(data);

    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

    float viewMatrix[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, -3,  // Move back to see the cylinder
        0, 0, 0, 1
    };
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewMatrix);

    float aspectRatio = 800.0f / 600.0f;
    float projectionMatrix[16] = {
        1.0f / aspectRatio, 0, 0, 0,
        0, 1.0f, 0, 0,
        0, 0, -1.01f, -1,
        0, 0, -0.02f, 0
    };
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projectionMatrix);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float angle = (float)glfwGetTime();
        GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
        float rotationMatrix[16] = {
            cosf(angle), 0, sinf(angle), 0,
            0, 1, 0, 0,
            -sinf(angle), 0, cosf(angle), 0,
            0, 0, 0, 1
        };
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, rotationMatrix);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    free(vertices);
    free(indices);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

