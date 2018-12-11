  #include "Shaders.h"
 
 
 //---------------------------------------------------------------------------------------
 // Constructor de la clase (llama a las funciones privadas createShader y createProgram)
 //---------------------------------------------------------------------------------------
 Shaders::Shaders(const GLchar* vShaderPath, const GLchar* fShaderPath) { 
 
     GLuint vShader = createShader(GL_VERTEX_SHADER  , vShaderPath);
     GLuint fShader = createShader(GL_FRAGMENT_SHADER, fShaderPath);
     program = createProgram(vShader, fShader);
     
 }
 
 
 //--------------------------------------
 // Crea un shader (vértices/fragmentos)
 //--------------------------------------
 GLuint Shaders::createShader(GLenum shader, const char* shaderFile) {
    
  // Se crea un objeto shader
     GLuint shaderID = glCreateShader(shader); 
     
  // Se asigna su código fuente
     const char *shaderSrc = readShader(shaderFile);
     glShaderSource(shaderID, 1, &shaderSrc, NULL);
     
  // Se compila con control de errores
     GLint compiled;    
     glCompileShader(shaderID);
     glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
     if(compiled == GL_FALSE) {
         GLint logSize;
         glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
         char* logMsg = new char[logSize];
         glGetShaderInfoLog(shaderID, logSize, NULL, logMsg);
         std::cout << "Error al compilar el Shader " << shaderFile << ": " << logMsg;
         delete[] logMsg;
         return 0;
     }
     
     return shaderID;
 }
 
 
 //-----------------------------------
 // Lee el código fuente de un shader
 //-----------------------------------
 const char* Shaders::readShader(const GLchar* shaderPath) {
    
     std::string   shaderCode;
     std::ifstream shaderFile(shaderPath, std::ios::in);
     if(shaderFile.is_open()) {
         std::string line = "";
         while(getline(shaderFile, line)) shaderCode += "\n" + line;
         shaderFile.close();
     }
     else {
         std::cout << "El fichero " << shaderPath << " no se puede abrir." << std::endl;
         return 0;
     }
     
     return shaderCode.c_str();
 }
 
 
 //-------------------------------------------------------------------
 // Crea un programa(identificador) que usa los shaders especificados
 //-------------------------------------------------------------------
 GLuint Shaders::createProgram(GLuint vShader, GLuint fShader) {
     
  // Se crea un objeto programa
     GLuint program = glCreateProgram();
     
  // Se adjuntan los shaders y se eliminan los objetos correspondientes
     glAttachShader(program, vShader);
     glAttachShader(program, fShader);
     glDeleteShader(vShader);
     glDeleteShader(fShader);
     
  // Se enlaza el programa con control de errores
     GLint linked;    
     glLinkProgram(program);
     glGetShaderiv(program, GL_COMPILE_STATUS, &linked);
     if(linked == GL_FALSE) {
         GLint logSize;
         glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logSize);
         char* logMsg = new char[logSize];
         glGetShaderInfoLog(program, logSize, NULL, logMsg);
         std::cout << "Error al enlazar el Shader: " << logMsg;
         delete[] logMsg;
         return 0;
     }
     
     return program;    
 }
 
 
 //-----------------------------------------------------
 // Fija el valor de una variable uniforme de tipo vec3
 //-----------------------------------------------------
 void Shaders::setVec3(const std::string &name, glm::vec3 value) {
     
    glUniform3fv(glGetUniformLocation(program,name.c_str()), 1, glm::value_ptr(value));
     
 }
 
 
 //-----------------------------------------------------
 // Fija el valor de una variable uniforme de tipo mat4
 //-----------------------------------------------------
 void Shaders::setMat4(const std::string &name, glm::mat4 value) {
     
    glUniformMatrix4fv(glGetUniformLocation(program,name.c_str()), 1, GL_FALSE, glm::value_ptr(value)); 
     
 }
 
 
 //------------------------------------------------------
 // Fija el valor de una variable uniforme de tipo Light
 //------------------------------------------------------
 void Shaders::setLight(const std::string &name, Light value) {
     
     glUniform3fv(glGetUniformLocation(program,(name+".position"   ).c_str()), 1, glm::value_ptr(value.position ));
     glUniform3fv(glGetUniformLocation(program,(name+".direction"  ).c_str()), 1, glm::value_ptr(value.direction));
     glUniform4fv(glGetUniformLocation(program,(name+".ambient"    ).c_str()), 1, glm::value_ptr(value.ambient  ));
     glUniform4fv(glGetUniformLocation(program,(name+".diffuse"    ).c_str()), 1, glm::value_ptr(value.diffuse  ));
     glUniform4fv(glGetUniformLocation(program,(name+".specular"   ).c_str()), 1, glm::value_ptr(value.specular ));
     glUniform1f (glGetUniformLocation(program,(name+".innerCutOff").c_str()), glm::cos(glm::radians(value.innerCutOff)));
     glUniform1f (glGetUniformLocation(program,(name+".outerCutOff").c_str()), glm::cos(glm::radians(value.outerCutOff)));
     glUniform1f (glGetUniformLocation(program,(name+".c0"         ).c_str()), value.c0);
     glUniform1f (glGetUniformLocation(program,(name+".c1"         ).c_str()), value.c1);
     glUniform1f (glGetUniformLocation(program,(name+".c2"         ).c_str()), value.c2);
             
 }
 
 
 //---------------------------------------------------------
 // Fija el valor de una variable uniforme de tipo Material
 //---------------------------------------------------------
 void Shaders::setMaterial(const std::string &name, Material value) {
     
     glUniform4fv(glGetUniformLocation(program,(name+".ambient"  ).c_str()), 1, glm::value_ptr(value.ambient ));
     glUniform4fv(glGetUniformLocation(program,(name+".diffuse"  ).c_str()), 1, glm::value_ptr(value.diffuse ));
     glUniform4fv(glGetUniformLocation(program,(name+".specular" ).c_str()), 1, glm::value_ptr(value.specular));
     glUniform1f (glGetUniformLocation(program,(name+".shininess").c_str()), value.shininess);
             
 }
 
 
 //--------------------------------------------------------------------
 // Fija el valor de una variable uniforme (sampler2D) de tipo Texture
 //--------------------------------------------------------------------
 void Shaders::setTexture(const std::string &name, GLuint value) {
     
     glUniform1i(glGetUniformLocation(program,name.c_str()),value);
             
}
 //--------------------------------------------------------
// Fija el valor de una variable uniforme de tipo GLfloat
//--------------------------------------------------------
void Shaders::setFloat(const std::string &name, GLfloat value) {
    
    glUniform1f(glGetUniformLocation(program,name.c_str()),value);
            
}
 //-----------------------------------------
// Usa el shader para renderizar la escena
//-----------------------------------------
 void Shaders::use() {
     
     glUseProgram(program);
     
 }
 
 
 //------------------------
 // Destructor de la clase
 //------------------------
 Shaders::~Shaders() { 
     
     glDeleteProgram(program);
 
 }