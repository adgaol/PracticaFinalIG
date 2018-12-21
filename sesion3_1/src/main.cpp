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
void drawRoom(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTwoPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawPlaneP(glm::mat4 P, glm::mat4 V, glm::mat4 M); 
void drawPlaneT(glm::mat4 P, glm::mat4 V, glm::mat4 M); 
void drawPlaneS(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawCabinAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) ;
void drawAirPlaneWings(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlaneEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAirPlaneWithEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawAspa    (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawHelice  (glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawLegsCilinder(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawChair(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawTable(glm::mat4 P, glm::mat4 V, glm::mat4 M);
void drawLamp(glm::mat4 P, glm::mat4 V, glm::mat4 M);
// Viewport
   int w = 500;
   int h = 500;
   int speed = 20;
// Animaciones
   GLfloat rotX = 0.0f;
   GLfloat rotY = 0.0f;
   GLfloat rotZ = 0.0f;
   GLfloat rotF = 0.0f;
   GLfloat rotAY = 0.0f;
   GLfloat desZ = 0.0f;
   GLfloat desSZ = 0.0f;
   GLfloat desSY = 0.0f;
   GLfloat desX = 0.0f;
   GLfloat desY = 0.0f;
   GLfloat zoom = 1.0f;
   GLfloat Xc  =  0.0f;
   GLfloat Yc  =  0.0f;
   GLfloat luz  =  1.0f;
   bool    leftbutton = false;
// Shaders
   Shaders *objShaders;
   
// Modelos
   Mesh *object,*plane,*cube,*cilinder,*cone,*sphere;

// Luces
    #define NLD 1
    #define NLP 1
    #define NLF 2
    Light   lightG;
    Light   lightD[NLD];
    Light   lightP[NLP];
    Light   lightF[NLF];
    
 // Materiales
    Material matLuces;
    Material matRuby;
    Material matGold;
    
 // Texturas
    Texture *texLight;
    Texture *texChess;
    Texture *texEarth;
    Texture *texBox;
    Texture *texWood;
    Texture *texMetalAzul; 
    Texture *texMetalAmarillo; 
    Texture *texMetalRojo; 
    Texture *texfloor;
    Texture *texGotele;
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
   //plane1->setColor(glm::vec3(0.5f, 0.5f, 0.5f));
    plane->createVao();
    // Malla con el cubo
    const char* cubePath = "resources/models/cube.obj";
    cube= new Mesh(cubePath);
    cube->createVao();
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
//    plane2 = new Mesh(planePath);
//    plane2->setColor(glm::vec3(0.6f, 0.6f, 0.6f));
//    plane2->createVao();
  // Texturas
     texLight = new Texture(0,"resources/textures/imgLight.bmp");    
     texChess = new Texture(1,"resources/textures/imgChess.bmp");    
     texEarth = new Texture(2,"resources/textures/imgEarth.bmp");   
     texBox = new Texture(2,"resources/textures/imgDiffuse.bmp"); 
     texWood = new Texture(2,"resources/textures/imgMadera.bmp"); 
     texMetalAzul = new Texture(2,"resources/textures/imgMetalAzul.bmp");
     texMetalAmarillo = new Texture(2,"resources/textures/imgMetalAmarillo.bmp");
     texMetalRojo=new Texture(2,"resources/textures/imgMetalRojo.bmp");
     texfloor= new Texture(2,"resources/textures/imgWood.bmp");
     texGotele=new Texture(2,"resources/textures/imgGotele.bmp");
     
     // Luz ambiental global
     lightG.ambient      = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

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
}

void funDestroy() {
      
    delete objShaders;
    delete object;
    
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
    glm::mat4 Rx = glm::rotate   (I, glm::radians(rotX), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Rc1 = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rc2 = glm::rotate   (I, glm::radians(-100.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Tz = glm::translate(I, glm::vec3(0.0f, 0.0f, desSZ));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, desSY, 0.0f));
    glm::mat4 Tc1 = glm::translate(I, glm::vec3(-1.5f, 0.1875f, -0.8f));
    glm::mat4 Tt1 = glm::translate(I, glm::vec3(-1.5f, 0.1875f, -0.25f));
    glm::mat4 Tc2 = glm::translate(I, glm::vec3(1.5f, 0.1875f, -0.8f));
    glm::mat4 Tt2 = glm::translate(I, glm::vec3(1.5f, 0.1875f, -0.25f));
    glm::mat4 Tc3 = glm::translate(I, glm::vec3(-1.0f, 0.1875f, 1.25f));
    glm::mat4 Tc4 = glm::translate(I, glm::vec3(1.0f, 0.1875f, 1.0f));
    glm::mat4 Tt3 = glm::translate(I, glm::vec3(-0.25f, 0.1875f,1.0f));
    glm::mat4 Tl = glm::translate(I, glm::vec3(0.0f, 1.0f, -0.25f));
    glm::mat4 Ta = glm::translate(I, glm::vec3(0.0f, 2.5f, 0.0f));
    glm::mat4 Sa = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f,0.25f ,0.25f));
    glm::mat4 Sl = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f,0.5f ,0.25f));

   drawAirPlane(P,V,Ry*Rx*Tz*Ty*Ta*Sa);
   drawTwoPlane(P,V,Tz*Ty);
   drawChair(P,V,Tc1*Sa);
   drawTable(P,V,Tt1*Sa);
   drawChair(P,V,Tc2*Sa);
   drawTable(P,V,Tt2*Sa);
   drawLamp(P,V,Tl*Sl);
   drawChair(P,V,Tc3*Rc1*Sa);
   drawChair(P,V,Tc4*Rc2*Sa);
   drawTable(P,V,Tt3*Sa);
 // Intercambiamos los buffers
    glutSwapBuffers();
    
}

 void setLights(glm::mat4 P, glm::mat4 V) {
     
     objShaders->setLight("ulightG",lightG);
       // Luces direccionales
     lightD[0].direction = glm::vec3(0.0f, 0.0f, -1.0f);
     lightD[0].ambient   = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
     lightD[0].diffuse   = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
     lightD[0].specular  = glm::vec4(0.4f, 0.4f, 0.4f, 1.0f);
     for(int i=0; i<NLD; i++) objShaders->setLight("ulightD["+std::to_string(i)+"]",lightD[i]);
       // Luces posicionales
    lightP[0].position = glm::vec3(0.0f, 3.87f, 0.0f);
    lightP[0].ambient  = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
    lightP[0].diffuse  = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    lightP[0].specular = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    lightP[0].c0 = 1.00f;
    lightP[0].c1 = 0.22f;
    lightP[0].c2 = 0.20f;
     for(int i=0; i<NLP; i++) objShaders->setLight("ulightP["+std::to_string(i)+"]",lightP[i]);
     glm::mat4 Rf = glm::rotate   (I, glm::radians(rotF), glm::vec3(0.0f, 1.0f, 0.0f));
       // Luces focales
     lightF[0].position  = glm::vec3(0.1f,1.95f, -0.25f);
     lightF[0].direction =Rf* glm::vec4( 1.0f, -1.0f, 0.0f,1.0f);
     lightF[0].ambient   = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
     lightF[0].diffuse   = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     lightF[0].specular  = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     lightF[0].innerCutOff = 10.0f;
     lightF[0].outerCutOff = lightF[0].innerCutOff + 5.0f;
     lightF[0].c0 = 1.000f;
     lightF[0].c1 = 0.090f;
     lightF[0].c2 = 0.032f;
          lightF[1].position  = glm::vec3( -0.1f,1.95f, -0.25f);
     lightF[1].direction = Rf*glm::vec4(-1.0f, -1.0f, 0.0f,1.0f);
     lightF[1].ambient   = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
     lightF[1].diffuse   = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     lightF[1].specular  = glm::vec4(0.9f, 0.9f, 0.9f, 1.0f);
     lightF[1].innerCutOff = 10.0f;
     lightF[1].outerCutOff = lightF[1].innerCutOff + 5.0f;
     lightF[1].c0 = 1.000f;
     lightF[1].c1 = 0.090f;
     lightF[1].c2 = 0.032f;
     for(int i=0; i<NLF; i++) objShaders->setLight("ulightF["+std::to_string(i)+"]",lightF[i]);
   // glm::mat4 Rf = glm::rotate   (I, glm::radians(rotF), glm::vec3(0.0f, 1.0f, 0.0f));
    for(int i=0; i<NLP; i++) {
        glm::mat4 M = glm::scale(glm::translate(I,lightP[i].position),glm::vec3(0.10f));
       
        drawObject(cube,matLuces,texLight,0.0f,P,V,M);
    }
     for(int i=0; i<NLF; i++) {
        glm::mat4 M = glm::scale(glm::translate(I,lightF[i].position),glm::vec3(0.025f));
        
        drawObject(cube,matLuces,texLight,0.0f,P,V,M);
    }
 }

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
//void drawRoom(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
//      glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f)); 
//       drawObject(cube,matLuces,texLight,0.0f,P,V,M*S);
//}
void drawPlaneS(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
       drawObject(plane,matLuces,texfloor,0.4f,P,V,M*T);
}
void drawPlaneP(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
       drawObject(plane,matGold,texMetalAzul,0.4f,P,V,M*T);
}
void drawPlaneT(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
      glm::mat4 T = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f)); 
       drawObject(plane,matLuces,texEarth,0.5f,P,V,M*T);
}
void drawTwoPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 Tp = glm::translate(I, glm::vec3(0.0f, 2.0f, -2.0f));
    glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Ty = glm::translate(I, glm::vec3(0.0f, 4.0f, 0.0f));
    drawPlaneP(P,V,M*Tp*Rx);
    drawPlaneP(P,V,M*Ry*Tp*Rx);
    //drawPlaneP(P,V,M*Ry*Ry*Tp*Rx);
    drawPlaneP(P,V,M*Ry*Ry*Ry*Tp*Rx);
    drawPlaneT(P,V,M*Ty);
    drawPlaneS(P,V,M);
}
void drawAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.75f, 0.1f, 0.1f));
    glm::mat4 Sv = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.08f, 0.05f));
    glm::mat4 Sh = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f,0.05f ,0.3f));
    glm::mat4 Tv = glm::translate(I, glm::vec3(-0.60f, 0.2f, 0.0f));
    glm::mat4 Th = glm::translate(I, glm::vec3(-0.60f, 0.0f, 0.0f));
    drawObject(cube,matLuces,texMetalAzul,1.0f,P,V,M*S);
    drawObject(cube,matLuces,texMetalAzul,1.0f,P,V,M*Tv*Sv);
    drawObject(cube,matLuces,texMetalAzul,1.0f,P,V,M*Th*Sh);
}
void drawCabinAirPlaneBody(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.05f, 0.05f));
    glm::mat4 T = glm::translate(I, glm::vec3(0.25f, 0.15f, 0.0f));
    
    
    drawObject(cube,matLuces,texLight,0.0f,P,V,M*T*S);
    drawAirPlaneBody(P,V,M);
}
void drawAirPlaneWings(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 Ry = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Rx = glm::rotate   (I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    //glm::mat4 R=Rx*Ry;
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.75f, 0.15f));
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*Ry*Rx*S);
    drawCabinAirPlaneBody(P,V,M);
}
void drawAspa(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.15f, 0.06f)); 
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.15f, 0.0f));
    drawObject(cone,matLuces,texLight,0.0f,P,V,M*T*S);  
}
void drawHelice(glm::mat4 P, glm::mat4 V, glm::mat4 M) {
    
 // Hélice
    glm::mat4 R120 = glm::rotate(I, glm::radians(120.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    drawAspa(P,V,M);
    drawAspa(P,V,M*R120);
    drawAspa(P,V,M*R120*R120);
   // drawAspa(P,V,M*R90*R90*R90);
     
}
void drawAirPlaneEngine(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 RH = glm::rotate(I, glm::radians(rotZ), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 RC = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 Ry = glm::rotate(I, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.08f, 0.1f, 0.08f));
    glm::mat4 SH = glm::scale(glm::mat4(1.0f), glm::vec3(0.35f, 0.35f, 0.35f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.11f, 0.0f, 0.0f));
   

  
    drawHelice(P,V,M*T*Ry*RH*SH);
    
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*RC*S);
}

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
//void drawAirPlaneWithTail(glm::mat4 P, glm::mat4 V, glm::mat4 M){
//    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.05f, 0.1f));
//    drawCube(P,V,M);
//    drawCube(P,V,M);
//}
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
//void drawAirPlane(glm::mat4 P, glm::mat4 V, glm::mat4 M){
//    glm::mat4 Ra = glm::rotate   (I, glm::radians(rotAZ), glm::vec3(0.0f, 1.0f, 0.0f));
//    drawAirPlaneWithHelix(P,V,M*Ra);
//}
void drawLegsCilinder(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 T1 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 T2 = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    glm::mat4 T3 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.75f, 0.25f));
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*T1*S);
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*T2*S);
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*T3*S);
    drawObject(cilinder,matLuces,texLight,0.0f,P,V,M*S);
}
void drawChair(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.1f, 1.0f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.75f, 0.5f));
    glm::mat4 T1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 1.75f, -0.5f));
     glm::mat4 R = glm::rotate   (I, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    drawLegsCilinder(P,V,M);
    drawObject(cube,matLuces,texLight,0.0f,P,V,M*T*S);
    drawObject(cube,matLuces,texLight,0.0f,P,V,M*T1*R*S);
}
void drawTable(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.1f, 1.0f));
    glm::mat4 T = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.75f, 0.5f));
    drawLegsCilinder(P,V,M);
    drawObject(sphere,matLuces,texLight,0.0f,P,V,M*T*S);
}
void drawLamp(glm::mat4 P, glm::mat4 V, glm::mat4 M){
    glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 2.0f, 0.3f));
    drawObject(cube,matLuces,texEarth,0.0f,P,V,M*S);
}
void funKeyboard(unsigned char key, int x, int y) {
   
    switch(key) {
        case 'a': if(desY>-1.25)  desY -= 0.1f;  break;
        case 'A': if(desY<4)  desY += 0.1f;  break;
        case 'i':   rotAY+=90.0f;  break;
        case 'd':   rotAY-=90.0f;  break;
        case 'Q':   desSY+=0.5;    break;
        case 'q':   desSY-=0.5;    break;
        case 'W':   desSZ+=0.5;    break;
        case 'w':   desSZ-=0.5;    break;
        case 'f':   rotF-=5;    break;
        case 'F':   rotF+=5;    break;
        default:    desY  = 0.0f;  break;
        
        
    }
    glutPostRedisplay();
        
}

void funSpecial(int key, int x, int y) {

    switch(key) {
       case GLUT_KEY_UP:  if(desZ>-7)   desZ -= 0.1f;   break;
       case GLUT_KEY_DOWN: if(desZ<7)  desZ += 0.1f;   break;
       case GLUT_KEY_LEFT: if(desX>-7)  desX -= 0.1f;   break;
       case GLUT_KEY_RIGHT:if(desX<7)  desX += 0.1f;   break;
       default:                             
           desX = 0.0f;
           rotAY = 0.0f;
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
     //     GLfloat dx=0.0f;
//     GLfloat dy=0.0f;
//  //if (!valid) {
//    dx = w-x;
//    dy = h-y;
//    /* do something with dx and dy */
// // }
//  motX = dx/100;
//  motY= dy/100;
}
 void funTimer(int ignore) {
     /*if(animacion){*/
        rotZ+=5;
    /* }*/
     
    glutPostRedisplay();
    glutTimerFunc(speed,funTimer,0);
    
}