#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <fstream> 
#include <SOIL.h>

class Texture {
    
    public:
        
        Texture(GLuint idTexture, const char* pathTexture);
        
        void   Activate();    
        GLuint getIdTexture();

        virtual ~Texture();
           
    private:

        GLuint texture;
        GLuint idTexture;
        
};

#endif /* TEXTURE_H */
