#define __USE_MINGW_ANSI_STDIO 0

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shaders.h"
#include "Mesh.h"
#include "Texture.h"
#define I glm::mat4(1.0f)

void funInit();
void funDestroy();
void funReshape(int w, int h);
void funDisplay();
void funTimer(int ignore); 
void funKeyboard(unsigned char key, int x, int y);
void funSpecial(int key, int x, int y);
void mousefunc(int button, int state, int x, int y);
void motionFunc(int x, int y);

void setLights (glm::mat4 P, glm::mat4 V);
void drawObject(Mesh *object, Material material, Texture *texture, GLfloat mixValue, glm::mat4 P, glm::mat4 V, glm::mat4 M);
//sala
void drawRoom(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPlaneP(glm::mat4 P, glm::mat4 V, glm::mat4 M); 
void drawPlaneT(glm::mat4 P, glm::mat4 V, glm::mat4 M); 
void drawPlaneS(glm::mat4 P, glm::mat4 V, glm::mat4 M);
//avion
void drawAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCabinAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) ;
void drawAirPlaneWings(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlaneEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlaneWithEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAspa    (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHelice  (glm::mat4 P, glm::mat4 V, glm::mat4 M);
//sillas y mesas
void drawLegsCilinder(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawChair(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTable(glm::mat4 P, glm::mat4 V, glm::mat4 M);
//lampara
void drawLamp(glm::mat4 P, glm::mat4 V, glm::mat4 M);
//dron
void drawMolino(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawBrazo(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawMolinoFour(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPost    (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawElipsoide(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawDron(glm::mat4 P, glm::mat4 V, glm::mat4 M); 
//ventilador
void drawBombilla(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAspaVent(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHeliceVent(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHeliceVentT(glm::mat4 P, glm::mat4 V, glm::mat4 M);
//vitrina
void drawBase(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPicture(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCristal(glm::mat4 P, glm::mat4 V, glm::mat4 M);
// Viewport
   int w = 500;
   int h = 500;
   int speed = 20;
// Animaciones
   GLfloat rotX = 0.0f;
   GLfloat rotY = 0.0f;
   GLfloat rotZ = 0.0f;
   GLfloat rotAY = 0.0f;
   GLfloat desZ = 0.0f;
   GLfloat desX = 0.0f;
   GLfloat desY = 0.0f;
   GLfloat zoom = 1.0f;
   GLfloat Xc  =  0.0f;
   GLfloat Yc  =  0.0f;
   GLfloat luz  =  1.0f;
   GLfloat luz1  =  1.0f;
   GLfloat techo  =  1.0f;
   GLfloat activador  =  1.0f;
   //Texture * pantalla= new Texture(2,"resources/textures/imgEarth.bmp");
   bool    leftbutton = false;
   bool    mActivado =false;
   bool    encendidaTele=true;
   bool    focal1Encendida=true;
   bool    focal2Encendida=true;
   bool    techoEncendida=true;
// Shaders
   Shaders *objShaders;
   
// Modelos
   Mesh *object,*plane,*cube,*cilinder,*cone,*sphere;//, *triangle;

// Luces
    #define NLD 1
    #define NLP 2
    #define NLF 2
    Light   lightG;
    Light   lightD[NLD];
    Light   lightP[NLP];
    Light   lightF[NLF];
    
 // Materiales
    Material matLuces;
    Material matTrasparencia;
    Material matRuby;
    Material matGold;
    Material matObsidian;
    
 // Texturas
    Texture *texLight;
    Texture *texArtistico;
    Texture *texEarth;
    Texture *texWood;
    Texture *texfloor;
    Texture *texGotele;
    Texture *texbodyDron;
int main(int argc, char** argv) {

 // Inicializamos GLUT y el contexto de OpenGL
    glutInit(&argc, argv);
    glutInitContextVersion(3,3);   
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE); 
    glutInitContextProfile(GLUT_CORE_PROFILE);
    
 // Inicializamos el FrameBuffer y la ventana   
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,50);
    glutCreateWindow("Sesion 06");
    
 // Inicializamos GLEW
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
    const GLubyte *oglVersion = glGetString(GL_VERSION);
    std::cout <<"This system supports OpenGL Version: " << oglVersion << std::endl;
    
 // Inicializaciones específicas
    funInit();
    
 // Configuración CallBacks
    glutReshapeFunc(funReshape);
    glutDisplayFunc(funDisplay);
    glutKeyboardFunc(funKeyboard);
    glutSpecialFunc(funSpecial);
    glutMouseFunc(mousefunc);
    glutMotionFunc(motionFunc);
    glutTimerFunc(speed,funTimer,0);
 // Bucle principal
    glutMainLoop();
    
 // Liberamos memoria
    funDestroy();
    
    return 0;
}

void funInit() {
   
 // Test de profundidad
    glEnable(GL_DEPTH_TEST); 
    
 // Shaders
  objShaders = new Shaders("resources/shaders/vshader_phong.glsl","resources/shaders/fshader_phong.glsl");
 
 //Malla plano
    const char* planePath = "resources/models/plane.obj";
    plane = new Mesh(planePath);
    plane->createVao();
    // Malla con el cubo
    const char* cubePath = "resources/models/cube.obj";
    cube= new Mesh(cubePath);
    cube->createVao();
    // Malla con el triangulo
    //const char* trianglePath = "resources/models/tringle.obj";
    //triangle= new Mesh(trianglePath);
    //triangle->createVao();
    // Malla con el cilindro
    const char* cilinderPath = "resources/models/cilinder.obj";
    cilinder= new Mesh(cilinderPath);
    cilinder->createVao();
    // Malla con el cubo
    const char* conePath = "resources/models/cone.obj";
    cone= new Mesh(conePath);
    cone->createVao();
     //Malla esfera
    sphere = new Mesh("resources/models/sphere.obj");
    sphere->createVao();
  // Texturas
     texLight = new Texture(0,"resources/textures/imgLight.bmp");     
     texEarth = new Texture(2,"resources/textures/imgEarth.bmp");  
     texWood = new Texture(2,"resources/textures/imgMadera.bmp"); 
     texfloor= new Texture(2,"resources/textures/imgWood.bmp");
     texGotele=new Texture(2,"resources/textures/imgPared.bmp");
     texArtistico=new Texture(2,"resources/textures/artistico.bmp");
     texbodyDron = new Texture(0,"resources/textures/floor3.bmp");
     // Luz ambiental global
     lightG.ambient      = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

  // Materiales
     matLuces.ambient   = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
     matLuces.diffuse   = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     matLuces.specular  = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
     matLuces.shininess = 10.0f;
     matRuby.ambient    = glm::vec4(0.174500f, 0.011750f, 0.011750f, 0.55f);
     matRuby.diffuse    = glm::vec4(0.614240f, 0.041360f, 0.041360f, 0.55f);
     matRuby.specular   = glm::vec4(0.727811f, 0.626959f, 0.626959f, 0.55f);
     matRuby.shininess  = 76.8f;
     matGold.ambient    = glm::vec4(0.247250f, 0.199500f, 0.074500f, 1.00f);
     matGold.diffuse    = glm::vec4(0.751640f, 0.606480f, 0.226480f, 1.00f);
     matGold.specular   = glm::vec4(0.628281f, 0.555802f, 0.366065f, 1.00f);
     matGold.shininess  = 51.2f;   
     matObsidian.ambient    = glm::vec4(0.05375f, 0.05f, 0.06625f, 0.82f );
     matObsidian.diffuse    = glm::vec4(0.18275f, 0.17f, 0.22525f, 0.82f);
     matObsidian.specular   = glm::vec4(0.332741f, 0.328634f, 0.346435f, 0.82f );
     matObsidian.shininess  = 38.4f;   
     matTrasparencia.ambient   = glm::vec4(0.5f, 0.5f, 0.5f, 0.05f);
     matTrasparencia.diffuse   = glm::vec4(0.9f, 0.9f, 0.9f, 0.05f);
     matTrasparencia.specular  = glm::vec4(0.5f, 0.5f, 0.5f, 0.05f);
     matTrasparencia.shininess = 10.0f;
}

void funDestroy() {
      
    delete objShaders;
    delete object,plane,cube,cilinder,cone,sphere;
    
}

void funReshape(int wnew, int hnew) {
    
 // Configuración del Viewport
    glViewport(0, 0, wnew, hnew);

 // Captura de w y h
    w = wnew;
    h = hnew;
    
}

void funDisplay() {

//     lightF[2].position  = glm::vec3(0.0f,1.95f, -0.25f);
//     lightF[2].direction = glm::vec3(0.0f, -1.0f, 0.0f);
//     lightF[2].ambient   = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
//     lightF[2].diffuse   = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
//     lightF[2].specular  = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
//     lightF[2].innerCutOff = 5.0f;
//     lightF[2].outerCutOff = lightF[1].innerCutOff + 1.0f;
//     lightF[2].c0 = 1.000f;
//     lightF[2].c1 = 0.090f;
//     lightF[2].c2 = 0.032f;
 // Borramos el buffer de color
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
 // Matriz de Proyección P (Perspectiva)
    GLfloat fovy   = 60.0f;
    GLfloat nplane =  0.1f;
    GLfloat fplane = 25.0f;
    GLfloat aspectRatio = (GLfloat)w/(GLfloat)h;
    glm::mat4 P = glm::perspective(glm::radians(fovy*zoom), aspectRatio, nplane, fplane); 

 // Matriz de Vista V (Cámara)
     GLfloat PI = glm::pi<float>();
     GLfloat x  = 10.0f*glm::cos(Yc*PI/180.0f)*glm::sin(Xc*PI/180.0f);
     GLfloat y  = 10.0f*glm::sin(Yc*PI/180.0f);
     GLfloat z  = 10.0f*glm::cos(Yc*PI/180.0f)*glm::cos(Xc*PI/180.0f);
     glm::vec3 pos   (   x,    y,    z);
     glm::vec3 lookat(0.0f, 0.0f,-1.0f);
     glm::vec3 up    (0.0f, 1.0f, 0.0f);
     glm::mat4 V = glm::lookAt(pos, lookat, up); 
     // Fijamos los shaders a utilizar junto con la posición de la cámara
     objShaders->use();
     objShaders->setVec3 ("uposc",pos);
     
  // Fijamos las luces
     setLights(P,V);
    
 // Dibujamos la escena
    glm::mat4 Ry = glm::rotate   (I, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rc1 = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rc2 = glm::rotate   (I, glm::radians(-100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Tc1 = glm::translate(I, glm::vec3(-1.5f, 0.1875f, -0.8f));
    glm::mat4 Tt1 = glm::translate(I, glm::vec3(-1.5f, 0.1875f, -0.25f));
    glm::mat4 Tc2 = glm::translate(I, glm::vec3(1.5f, 0.1875f, -0.8f));
    glm::mat4 Tt2 = glm::translate(I, glm::vec3(1.5f, 0.1875f, -0.25f));
    glm::mat4 Tc3 = glm::translate(I, glm::vec3(-1.0f, 0.1875f, 1.25f));
    glm::mat4 Tc4 = glm::translate(I, glm::vec3(1.0f, 0.1875f, 1.0f));
    glm::mat4 Tt3 = glm::translate(I, glm::vec3(-0.25f, 0.1875f,1.0f));
    glm::mat4 Tl = glm::translate(I, glm::vec3(0.0f, 1.0f, -0.25f));
    glm::mat4 Ta = glm::translate(I, glm::vec3(0.0f, 2.5f, 0.0f));
    glm::mat4 Td = glm::translate(I, glm::vec3(0.7f, 1.5f, 0.0f));
    glm::mat4 Tv = glm::translate(I, glm::vec3(-1.0f, 0.6f, -1.4f));
    glm::mat4 Sa = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f,0.25f ,0.25f));
    glm::mat4 Sl = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f,0.5f ,0.25f));
    glm::mat4 Sd = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f,0.25f ,0.25f));
   drawAirPlane(P,V,Ta*Sa);
   drawRoom(P,V,I);
   drawChair(P,V,Tc1*Sa);
   drawTable(P,V,Tt1*Sa);
   drawChair(P,V,Tc2*Sa);
   drawTable(P,V,Tt2*Sa);
   drawLamp(P,V,Tl*Sl);
   drawChair(P,V,Tc3*Rc1*Sa);
   drawChair(P,V,Tc4*Rc2*Sa);
   drawTable(P,V,Tt3*Sa);
   drawDron(P,V,Ry*Td*Sd);
   drawBombilla(P,V,Tl);
   drawHeliceVentT(P,V,Tl);
   drawCristal(P,V,Tv);
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}
//fija las luces
 void setLights(glm::mat4 P, glm::mat4 V) {
     
     objShaders->setLight("ulightG",lightG);
       // Luces direccionales
     lightD[0].direction = glm::vec3(0.0f, 0.0f, -1.0f);
     lightD[0].ambient   = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
     lightD[0].diffuse   = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);
     lightD[0].specular  = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
     for(int i=0; i<NLD; i++) objShaders->setLight("ulightD["+std::to_string(i)+"]",lightD[i]);
     // Luces posicionales
     lightP[0].position = glm::vec3(0.0f, 3.87f, 0.0f);
     lightP[0].ambient  = glm::vec4(techo*0.1f,techo* 0.1f,techo* 0.1f, 1.0f);
     lightP[0].diffuse  = glm::vec4(techo*0.9f,techo* 0.9f,techo* 0.9f, 1.0f);
     lightP[0].specular = glm::vec4(techo*0.2f,techo* 0.2f,techo* 0.2f, 1.0f);
     lightP[0].c0 = 1.00f;
     lightP[0].c1 = 0.22f;
     lightP[0].c2 = 0.20f;
    
     glm::mat4 Ry = glm::rotate   (I, glm::radians(rotY), glm::vec3(0.0f, 1.0f, 0.0f));
     lightP[1].position =Ry* glm::vec4(0.7f, 1.45f, 0.0f,1.0f);
     lightP[1].ambient  = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
     lightP[1].diffuse  = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     lightP[1].specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
     lightP[1].c0 = 1.00f;
     lightP[1].c1 = 0.22f;
     lightP[1].c2 = 0.20f;
     for(int i=0; i<NLP; i++) objShaders->setLight("ulightP["+std::to_string(i)+"]",lightP[i]);
     
       // Luces focales
     lightF[0].position  = glm::vec3(0.1f,1.95f, -0.25f);
     lightF[0].direction = glm::vec4(1.0f, -1.0f, 0.0f,1.0f);
     lightF[0].ambient   = glm::vec4(luz*0.1f,luz* 0.1f,luz* 0.1f, 1.0f);
     lightF[0].diffuse   = glm::vec4(luz*0.9f,luz* 0.9f,luz* 0.9f, 1.0f);
     lightF[0].specular  = glm::vec4(luz*0.9f,luz* 0.9f,luz* 0.9f, 1.0f);
     lightF[0].innerCutOff = 10.0f;
     lightF[0].outerCutOff = lightF[0].innerCutOff + 5.0f;
     lightF[0].c0 = 1.000f;
     lightF[0].c1 = 0.090f;
     lightF[0].c2 = 0.032f;
     
     lightF[1].position  = glm::vec3( -0.1f,1.95f, -0.25f);
     lightF[1].direction = glm::vec4(-1.0f, -1.0f, 0.0f,1.0f);
     lightF[1].ambient   = glm::vec4(luz1*0.1f,luz1* 0.1f,luz1* 0.1f, 1.0f);
     lightF[1].diffuse   = glm::vec4(luz1*0.9f,luz1* 0.9f,luz1* 0.9f, 1.0f);
     lightF[1].specular  = glm::vec4(luz1*0.5f,luz1* 0.5f,luz1* 0.5f, 1.0f);
     lightF[1].innerCutOff = 10.0f;
     lightF[1].outerCutOff = lightF[1].innerCutOff + 5.0f;
     lightF[1].c0 = 1.000f;
     lightF[1].c1 = 0.090f;
     lightF[1].c2 = 0.032f;
     for(int i=0; i<NLF; i++) objShaders->setLight("ulightF["+std::to_string(i)+"]",lightF[i]);
 
     for(int i=0; i<NLP; i++) {
        glm::mat4 M1 = glm::scale(glm::translate(I,lightP[i].position),glm::vec3(0.10f));
        glm::mat4 M2 = glm::scale(glm::translate(I,lightP[i].position),glm::vec3(0.01f));
        if (i==1)
        drawObject(cube,matLuces,texLight,0.0f,P,V,M2);   
        else
        drawObject(cube,matLuces,texLight,0.0f,P,V,M1);
     }
     
     for(int i=0; i<NLF; i++) {
        glm::mat4 M = glm::scale(glm::translate(I,lightF[i].position),glm::vec3(0.025f));       
        drawObject(cube,matLuces,texLight,1.0f,P,V,M);
     }
 }
//dibuja los modelos
void drawObject(Mesh *object, Material material, Texture *texture, GLfloat mixValue, glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    
    objShaders->setMat4("uN",glm::transpose(glm::inverse(M)));
    objShaders->setMat4("uM",M);
    objShaders->setMat4("uPVM",P*V*M);
    objShaders->setMaterial("umaterial",material);
    texture->Activate();
    objShaders->setTexture("utex",texture->getIdTexture());
    objShaders->setFloat("umixValue",mixValue);
    object->render(GL_FILL);
    
}

//Dibuja el suelo
void drawPlaneS(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
       drawObject(plane,matLuces,texfloor,0.4f,P,V,M*T);
}
//dibuja una pared
void drawPlaneP(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
       drawObject(plane,matObsidian,texGotele,0.5f,P,V,M*T);
}
//dibuja el techo
void drawPlaneT(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
      drawObject(plane,matLuces,texEarth/*pantalla*/,activador*1.0f,P,V,M*T);
}
//dibuja la sala
void drawRoom(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 Tp = glm::translate(I, glm::vec3(0.0f, 2.0f, -2.0f));
    glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, 4.0f, 0.0f));
    drawPlaneP(P,V,M*Tp*Rx);
    drawPlaneP(P,V,M*Ry*Tp*Rx);
    drawPlaneP(P,V,M*Ry*Ry*Ry*Tp*Rx);
    drawPlaneT(P,V,M*Ty);
    drawPlaneS(P,V,M);
}
//dibuja el poste del molino que va ha hacer de brazo
void drawPost(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    
    glm::mat4 S = glm::scale(I, glm::vec3(0.05f, 0.5f, 0.05f));
    glm::mat4 T = glm::translate(I, glm::vec3(0.0f, -0.5f, 0.0f));
     drawObject(cilinder,matGold,texWood,0.2f,P,V,M*T*S); 
}
//dibuja 4 brazos  
void drawMolinoFour(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 R90y = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    drawBrazo(P,V,M*R90);
    drawBrazo(P,V,M*R90y*R90);
    drawBrazo(P,V,M*R90y*R90y*R90);
    drawBrazo(P,V,M*R90y*R90y*R90y*R90);
}

void drawMolino(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T = glm::translate(I, glm::vec3(0.0f, 0.1f, 0.0f));
    glm::mat4 T2 = glm::translate(I, glm::vec3(0.0f, 0.1f, 0.0f));
    glm::mat4 R45 = glm::rotate(I, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 RH = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    drawHelice(P,V,M*T*T2*R90*R45*RH);
    glm::mat4 Sc = glm::scale(I, glm::vec3(0.025f, 0.1f, 0.025f));
    drawObject(cilinder,matObsidian,texbodyDron,0.0f,P,V,M*T*Sc);
}
//dibuja un brazo del dron
void drawBrazo(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T = glm::translate(I, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate(I, glm::radians(-rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 R90 = glm::rotate(I, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 S = glm::scale(I, glm::vec3(0.075f, 0.075f, 0.075f));
    drawMolino(P,V,M*T*R90*Rx);
    drawObject(sphere,matObsidian,texbodyDron,0.3f,P,V,M*T*Rx*S);
    drawPost(P,V,M*T);
}
//dibuja el cuerpo del dron
void drawElipsoide(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.5f, 0.2f, 0.5f));
    drawObject(sphere,matObsidian,texbodyDron,0.2f,P,V,M*S);
}
void drawBombilla(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(I, glm::vec3(0.3f, 0.125f, 0.3f));
    glm::mat4 TBom = glm::translate(I, glm::vec3(0.0f, 2.75f, 0.25f));
    drawObject(sphere,matObsidian,texLight,0.2f,P,V,M*TBom*S);
}
void drawAspaVent(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.4f, 0.002f)); 
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,-0.5f, 0.3f));
    glm::mat4 RAspa = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    drawObject(cone,matObsidian,texfloor,0.5f,P,V,M*RAspa*T*S);  
}
void drawHeliceVent(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 R90 = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f,0.0f));
    drawAspaVent(P,V,M);
    drawAspaVent(P,V,M*R90);
    drawAspaVent(P,V,M*R90*R90);
    drawAspaVent(P,V,M*R90*R90*R90);
}
void drawHeliceVentT(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 TBom = glm::translate(I, glm::vec3(0.0f, 3.05f, 0.25f));
    glm::mat4 RH = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0f, 1.0f, 0.0f));
    drawHeliceVent(P,V,M*TBom*RH);
}
//dibuja el dron
void drawDron(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    
    drawElipsoide(P,V,M);
    drawMolinoFour(P,V,M);
}
//dibuja el cuerpo del avion
void drawAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.1f, 0.1f));
    glm::mat4 Sv = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.08f, 0.05f));
    glm::mat4 Sh = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f,0.05f ,0.3f));
    glm::mat4 Tv = glm::translate(I, glm::vec3(-0.60f, 0.2f, 0.0f));
    glm::mat4 Th = glm::translate(I, glm::vec3(-0.60f, 0.0f, 0.0f));
    drawObject(cube,matObsidian,texWood,0.5f,P,V,M*S);
    drawObject(cube,matObsidian,texWood,0.4f,P,V,M*Tv*Sv);
    drawObject(cube,matObsidian,texWood,0.4f,P,V,M*Th*Sh);
}
//dibuja la cabina al avion
void drawCabinAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f));
    glm::mat4 T = glm::translate(I, glm::vec3(0.25f, 0.15f, 0.0f));
    
    
    drawObject(cube,matObsidian,texLight,0.1f,P,V,M*T*S);
    drawAirPlaneBody(P,V,M);
}
//dibuja las alas al avion
void drawAirPlaneWings(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 R=Rx*Ry;
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.75f, 0.15f));
    drawObject(cilinder,matObsidian,texWood,0.4f,P,V,M*Ry*Rx*S);
    drawCabinAirPlaneBody(P,V,M);
}
//dibuja una aspa
void drawAspa(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.15f, 0.06f)); 
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.15f, 0.0f));
    drawObject(cone,matObsidian,texfloor,1.0f,P,V,M*T*S);  
}
//dibuja una helice
void drawHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    
 
    glm::mat4 R120 = glm::rotate(I, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    drawAspa(P,V,M);
    drawAspa(P,V,M*R120);
    drawAspa(P,V,M*R120*R120);
   
     
}
//dibuja motores de avion
void drawAirPlaneEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RH = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 RC = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Ry = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f, 0.1f, 0.08f));
    glm::mat4 SH = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 0.35f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f, 0.0f, 0.0f));
   

  
    drawHelice(P,V,M*T*Ry*RH*SH);
    
    drawObject(cilinder,matObsidian,texWood,0.5f,P,V,M*RC*S);
}
//dibuja los motores al avion
void drawAirPlaneWithEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Ry = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 RH = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Sh = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.6f));
   glm::mat4 Tdh = glm::translate(glm::mat4(1.0f), glm::vec3(0.75f, 0.0f, 0.0f));
    glm::mat4 Ti = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, -0.08f, -0.5f));
    glm::mat4 Td = glm::translate(glm::mat4(1.0f), glm::vec3(0.15f, -0.08f, 0.5f));
    drawHelice(P,V,M*Tdh*Ry*RH*Sh);
    drawAirPlaneEngine(P,V,M*Ti);
    drawAirPlaneEngine(P,V,M*Td);
    drawAirPlaneWings(P,V,M);
}

//dibuja el avion
void drawAirPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M){

   glm::mat4 Ty = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, desY+0.0f, 0.0f));
   glm::mat4 Tx = glm::translate(glm::mat4(1.0f), glm::vec3(desX+0.0f, 0.0f, 0.0f));
   glm::mat4 Tz = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, desZ+0.0f));
   glm::mat4 Ra = glm::rotate   (I, glm::radians(rotAY), glm::vec3(0.0f, 1.0f, 0.0f));
   //drawCube(P,V,M*T*S);
   //drawCube(P,V,M*T*S);
  // drawHelice(P,V,M*Td*Ty*Tx*Ry*RH*S);
   drawAirPlaneWithEngine(P,V,M*Ty*Tx*Tz*Ra);
}

//dibuja cuatro cilindros equidistantes
void drawLegsCilinder(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 T2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    glm::mat4 T3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.75f, 0.25f));
    drawObject(cilinder,matObsidian,texWood,0.5f,P,V,M*T1*S);
    drawObject(cilinder,matObsidian,texWood,0.5f,P,V,M*T2*S);
    drawObject(cilinder,matObsidian,texWood,0.5f,P,V,M*T3*S);
    drawObject(cilinder,matObsidian,texWood,0.5f,P,V,M*S);
}
//dibuja el asiento y el respaldo de la silla
void drawChair(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.1f, 1.0f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.75f, 0.5f));
    glm::mat4 T1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 1.75f, -0.5f));
     glm::mat4 R = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    drawLegsCilinder(P,V,M);
    drawObject(cube,matObsidian,texWood,0.4f,P,V,M*T*S);
    drawObject(cube,matObsidian,texWood,0.5f,P,V,M*T1*R*S);
}
//dibuja la tabla de la mesa
void drawTable(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.1f, 1.0f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.75f, 0.5f));
    drawLegsCilinder(P,V,M);
    drawObject(cilinder,matObsidian,texWood,0.4f,P,V,M*T*S);
}
//Dibuja la lampara
void drawLamp(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 2.0f, 0.3f));
    drawObject(cube,matRuby,texWood,0.2f,P,V,M*S);
}
void drawBase(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.6f, 0.4f));
    drawObject(cube,matObsidian,texWood,0.5f,P,V,M*S);
}
void drawPicture(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.3f, 0.05f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.0f, 1.030f));
    drawObject(cube,matLuces,texArtistico,1.0f,P,V,M*S);
    
}
void drawCristal(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.1f, 0.0f));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.5f, 0.4f));
     glm::mat4 R = glm::rotate   (I, glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    drawBase(P,V,M);
    drawPicture(P,V,M*T*R);
    glEnable (GL_BLEND) ;
    glBlendFunc (GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask (GL_FALSE) ;
    drawObject(cube,matTrasparencia,texEarth,0.0f,P,V,M*T*S);
    glDisable(GL_BLEND) ;
    glDepthMask(GL_TRUE) ;
}
void funKeyboard(unsigned char key, int x, int y) {
   
    switch(key) {
        //bajar avion
        case 'a': if(desY>-1.25)  desY -= 0.1f;  break;
        //subir avion
        case 'A': if(desY<4)  desY += 0.1f;  break;
        //girar dron en sentido antihorario
        case 'H': rotY+=5;  break;
        //girar dron en sentido horario
        case 'h': rotY-=5;  break; 
        //girar avion a la izquierda
        case 'i': rotAY+=90.0f;  break;
        //girar avion a la derecha
        case 'd': rotAY-=90.0f;  break;
       // case 'm': if(mActivado=false){pantalla=texEarth; mActivado=true;} else  {pantalla=texMetro; mActivado=false;} break;
       //apagar/encender textura del techo 
        case 'M': if(encendidaTele==false){activador=1; encendidaTele=true;} else  {activador=0; encendidaTele=false;}break;
        //apagar/encender focal derecha
        case 'f': if(focal1Encendida==false){luz=1; focal1Encendida=true;} else  {luz=0; focal1Encendida=false;}break;
        //apagar/encender focal izquierda
        case 'F': if(focal2Encendida==false){luz1=1; focal2Encendida=true;} else  {luz1=0; focal2Encendida=false;}break;
        case 't': if(techoEncendida==false){techo=1; techoEncendida=true;} else  {techo=0; techoEncendida=false;}break;
        default:     break;
        
        
    }
    glutPostRedisplay();
        
}

void funSpecial(int key, int x, int y) {

    switch(key) {
        //mover avion hacia atras
       case GLUT_KEY_UP:  if(desZ>-7)   desZ -= 0.1f;   break;
       //mover avion hacia delante
       case GLUT_KEY_DOWN: if(desZ<7)  desZ += 0.1f;   break;
       //mover avion hacia la izquierda
       case GLUT_KEY_LEFT: if(desX>-7)  desX -= 0.1f;   break;
       //mover avion hacia la derecha
       case GLUT_KEY_RIGHT:if(desX<7)  desX += 0.1f;   break;
       default:                             
          
           break;
    }    
    glutPostRedisplay();
        
}

 void mousefunc (int button, int state, int x, int y) {
  
leftbutton = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
     switch(button) {
         case 3: zoom += (zoom<0.05) ?  0.05f : -0.05f; break;
         case 4: zoom += (zoom>1.55) ? -0.05f :  0.05f; break;
     }
     glutPostRedisplay();
 
}
 void motionFunc (int x, int y) {
     
     if(leftbutton) {  
         GLfloat Xo = (GLfloat)w/2.0f;
         GLfloat Yo = (GLfloat)h/2.0f;
         Xc = ((GLfloat)x - Xo)/-5.0f;
         Yc = (Yo - (GLfloat)y)/-5.0f;
         glutPostRedisplay();
     }
}
 void funTimer(int ignore) {
        rotZ+=5;
    glutPostRedisplay();
    glutTimerFunc(speed,funTimer,0);
    
}