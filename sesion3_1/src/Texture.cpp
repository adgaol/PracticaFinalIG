#include "Texture.h"


//------------------------
// Constructor dela clase
//------------------------
Texture::Texture(GLuint idTexture, const char* pathTexture) {
        
 // Texture unit
    this->idTexture = idTexture;

 // Creamos la textura a configurar
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
 // Cargamos la imagen (SOIL)
    int textureW, textureH;
    unsigned char* imgTexture = SOIL_load_image(pathTexture, &textureW, &textureH, 0, SOIL_LOAD_RGB);
    
 // Creamos la textura
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureW, textureH, 0, GL_RGB, GL_UNSIGNED_BYTE, imgTexture);
    glGenerateMipmap(GL_TEXTURE_2D);
    
 // Liberamos memoria (SOIL)
    SOIL_free_image_data(imgTexture); 

 // Configuramos la textura
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
}


//------------------------------------------------------------------------------------------
// Activa una "unidad de textura" para que esta sea accesible desde el shader de fragmentos
//------------------------------------------------------------------------------------------
void Texture::Activate() {
    
    glActiveTexture(GL_TEXTURE0 + idTexture);
    glBindTexture(GL_TEXTURE_2D,texture);
    
}


//-----------------------------------------
// Devuelve el identificador de la textura
//-----------------------------------------
GLuint Texture::getIdTexture() {
    
    return idTexture;
    
}

//-----------------------
// Destructor dela clase
//-----------------------
Texture::~Texture() {
    
    glDeleteTextures(1,&texture);
    
}
