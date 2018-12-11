 #ifndef SHADERS_H
 #define SHADERS_H
 
 #include <GL/glew.h>
 #include <glm.hpp>
 #include <gtc/type_ptr.hpp>
 #include <iostream>
 #include <fstream> 
 
 struct Light {
     glm::vec3 position;
     glm::vec3 direction;
     glm::vec4 ambient;
     glm::vec4 diffuse;
     glm::vec4 specular;
     float innerCutOff;
     float outerCutOff;
     float c0;
     float c1;
     float c2;
 };
 
 struct Material {
     glm::vec4 ambient;
     glm::vec4 diffuse;
     glm::vec4 specular;
     float shininess;
 };
 
 class Shaders {
     
     public:
         
         Shaders(const GLchar* vShaderPath, const GLchar* fShaderPath);
 
         void setVec3    (const std::string &name, glm::vec3 value);
         void setMat4    (const std::string &name, glm::mat4 value);
        void setLight   (const std::string &name, Light     value);
        void setMaterial(const std::string &name, Material  value);
        void setTexture (const std::string &name, GLuint    value);
        void setFloat   (const std::string &name, GLfloat   value);
        void use();
         
        virtual ~Shaders();
                
     private:
                    
         GLuint program;
                 
         GLuint createShader (GLenum shader , const GLchar* shaderFile);
         GLuint createProgram(GLuint vShader, GLuint fShader);
         
         const char* readShader(const GLchar* filename);
 
 };
 
 #endif