#include "TextureBuilder.h"
#include <GLUT/glut.h>
#include "math.h"
#include <iostream>
#define GLUT_KEY_ESCAPE 27

GLuint texID;
GLuint texID2;
GLuint scndCar;
GLuint gameOverImg;

int rep = 1;
int obsPwr = 5;
float ballX = 70.0f;
float ballY = 0.0f;
float ballZ = 0.0f;
float backGroundX = 0.0f;
float carPosionX=300.0f;
float carPosionY=0.0f;
float obstaclesX=600;
float obstacleX1=600;
float obstacleX2=600;
float obstacleX3=600;
float obstaclesY=0.0f;
float powerUpX=1300.0f;
float powerUpY=0.0f;
float pY1=0.0f;
float pY2=0.0f;
float oY1=0.0f;
float oY2=0.0f;
float oY3=0.0f;
float gameOverX=0.0f;
//bool pwrUp = true;
int t = 0;
int tries=0;


/*float carInitXmin = 50.0f;
 float carInitXmax =
 */
void drawBackground(void);
void drawCircle(int x, int y, float r);
void drawCar(void);
void Anim(void);
void specialKeys(int key, int x, int y);
void Key(unsigned char key, int x, int y);
void Display(void);
void drawChasedCar(void);
void drawObstacles(void);
void drawPowerUp(void);
void checkCollision(void);
void gameOver(void);
void displayText(float x ,float y ,float z ,char *string);
void Timer(int value);
bool GameOverF = false;

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    
    glutCreateWindow("Project Cars");
    glutDisplayFunc(Display);
    glutTimerFunc(0,Timer, 0);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glutSpecialFunc(specialKeys);
    
    glutIdleFunc(Anim);
    
    gluOrtho2D(0, 800, 0, 600);
    
    //    loadBMP(&texID,"metal.bmp",900,900, true);
    loadBMP(&texID,"day.bmp",600,246,true);
    loadBMP(&texID2,"night.bmp",600,246,true);
    loadBMP(&scndCar,"amxCar.bmp",600,169,true);
    //        loadBMP(&texID, "maxresdefault.bmp",600,300, true);
    
    glutMainLoop();
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawBackground();
    drawCar();
    drawChasedCar();
    //    if(obsPwr<=0){
    //        obsPwr = 5;
    //    }
    drawObstacles();
    //    obsPwr-=3;  //Anim
    //    obstaclesX-= 5.0f;  //Anim
    //    powerUpX-=5.0f;     //Anim
    
    if(obsPwr<=0){
        obsPwr = 5;
    }
    obsPwr-=3.0f;
    
    if(obsPwr<2)
    {
        drawPowerUp();
    }
        checkCollision();
    
    
    /*
     if(obsPwr==2){
     drawPowerUp();
     }else{
     drawObstacles();
     obsPwr-=3;
     obstaclesX-= 5.0f;
     }
     */
    glFlush();
}

void Anim(void){
    backGroundX-=10.0f; //Anim
//    obsPwr-=3;  //Anim
    obstaclesX-= 5.0f;  //Anim
    powerUpX-=5.0f;     //Anim
    // pwrUp=!pwrUp; // need to be revised
    if(obsPwr<=0){
        obsPwr = 5;
    }
    
//    checkCollision();
    
    for(int i=0;i<10000000;i++);
    glutPostRedisplay();
}

void displayText(float x ,float y ,float z ,char *string) {
    int length;
    glRasterPos3f(x, y, z);
    length = strlen(string);
    
    for(int i=0 ;i<length ;i++){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,string[i]);
    }
}

void drawBackground(void){
    //The background
    
    if(backGroundX<-800){
        backGroundX = 0;
    }
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texID);
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(backGroundX, 0.0f, 0.0f);
    // day background
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(800, 0, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(800, 600, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(0, 600, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    // night background
    glBindTexture(GL_TEXTURE_2D, texID2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(800, 0, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(1600, 0, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(1600, 600, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(800, 600, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
    
}

void drawCircle(int x, int y, float r) {
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(x, y, 0);
    GLUquadric *quadObj = gluNewQuadric();
    gluDisk(quadObj, 0, r, 50, 50);
    glPopMatrix();
}

void drawCar(void){
    
    //The Object
    glPushMatrix();
    glTranslated(carPosionX,carPosionY,0.0f);
    glBegin(GL_POLYGON);
    glColor3f(1.0f,1.0f,1.0f);            // Set The Color To White
    glVertex3f(50.0f, 50.0f, 0.0f);        // bottom left
    glVertex3f(150.0f, 50.0f, 0.0f);        //bottom right
    glVertex3f(150.0f, 80.0f, 0.0f);       // Top Right
    glVertex3f(125.0f, 85.0f, 0.0f);
    glVertex3f(110.0f, 105.0f, 0.0f);
    glVertex3f(75.0f, 105.0f, 0.0f);
    glVertex3f(75.0f,  85.0f, 0.0f);
    glVertex3f(50.0f,82.0f, 0.0f);        // Top Left
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f, 0.0f);
    glVertex3f(76.0f,  83.0f, 0.0f);
    glVertex3f(122.0f, 83.0f, 0.0f);
    glVertex3f(110.0f, 103.0f, 0.0f);
    glVertex3f(78.0f, 103.0f, 0.0f);
    glVertex3f(78.0f, 83.0f, 0.0f);
    glEnd();
    
    drawCircle(70, 50, 10);
    drawCircle(130, 50, 10);
    
    glPopMatrix();
    
}

void drawChasedCar(void){
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, scndCar);
    glColor3f(1,1,1);
    glPushMatrix();
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(600, 50, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(750, 50, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(750, 150, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(600, 150, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    
}

void drawObstacles(void){
    
    
     if(obstaclesX<=-600){
     obstaclesX=600;
     }
    
    
    // 1st obstacle
    glPushMatrix();
    glTranslated(obstaclesX,obstaclesY,0.0f);
    // 1st obstacle
    glBegin(GL_POLYGON);
    glColor3f(0.5f,0.2f,1.0f);            // Set The Color To White
    glVertex3f((50.0f-50.0f), 50.0f, 0.0f);        // bottom left
    glVertex3f((150.0f-50.0f), 50.0f, 0.0f);        //bottom right
    glVertex3f((150.0f-50.0f), 80.0f, 0.0f);       // Top Right
    glVertex3f((125.0f-50.0f), 85.0f, 0.0f);
    glVertex3f((110.0f-50.0f), 105.0f, 0.0f);
    glVertex3f((75.0f-50.0f), 105.0f, 0.0f);
    glVertex3f((75.0f-50.0f),  85.0f, 0.0f);
    glVertex3f((50.0f-50.0f),82.0f, 0.0f);        // Top Left
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f, 0.0f);
    glVertex3f(76.0f-50.0f,  83.0f, 0.0f);
    glVertex3f(122.0f-50.0f, 83.0f, 0.0f);
    glVertex3f(110.0f-50.0f, 103.0f, 0.0f);
    glVertex3f(78.0f-50.0f, 103.0f, 0.0f);
    glVertex3f(78.0f-50.0f, 83.0f, 0.0f);
    glEnd();

    drawCircle(25, 50, 10);
    drawCircle(75, 50, 10);
    
    obstacleX1=obstaclesX-150;
    oY1=50.0f;
    
//    glBegin(GL_TRIANGLES);    //2nd Obstacles
//    glColor3f(0.0f,1.0f,0.0f);            // Set The Color To green
//    glVertex3f(300, 150.0f, 0.0f);        // bottom left
//    glVertex3f(350, 150.0f, 0.0f);        //bottom right
//    glVertex3f(300.0f,200.0f, 0.0f);        // Top Left
//    glEnd();
    
    // 2nd obstacle
    glBegin(GL_POLYGON);
    glColor3f(1.0f,0.5f,0.5f);            // Set The Color To White
    glVertex3f((50.0f-50.0f)+250, 50.0f+100, 0.0f);        // bottom left
    glVertex3f((150.0f-50.0f)+250, 50.0f+100, 0.0f);        //bottom right
    glVertex3f((150.0f-50.0f)+250, 80.0f+100, 0.0f);       // Top Right
    glVertex3f((125.0f-50.0f)+250, 85.0f+100, 0.0f);
    glVertex3f((110.0f-50.0f)+250, 105.0f+100, 0.0f);
    glVertex3f((75.0f-50.0f)+250, 105.0f+100, 0.0f);
    glVertex3f((75.0f-50.0f)+250,  85.0f+100, 0.0f);
    glVertex3f((50.0f-50.0f)+250,82.0f+100, 0.0f);        // Top Left
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f, 0.0f);
    glVertex3f((76.0f-50.0f)+250,  83.0f+100, 0.0f);
    glVertex3f((122.0f-50.0f)+250, 83.0f+100, 0.0f);
    glVertex3f((110.0f-50.0f)+250, 103.0f+100, 0.0f);
    glVertex3f((78.0f-50.0f)+250, 103.0f+100, 0.0f);
    glVertex3f((78.0f-50.0f)+250, 83.0f+100, 0.0f);
    glEnd();
    
    drawCircle(25+250, 50+100, 10);
    drawCircle(75+250, 50+100, 10);
    obstacleX2=obstacleX1+200;
    oY2=150.0f;
    
//    glBegin(GL_LINE_LOOP);    //3rd Obstacles
//    glColor3f(1.0f,0.0f,1.0f);            // Set The Color To green
//    glVertex3f(650, 50.0f, 0.0f);        // bottom left
//    glVertex3f(700, 50.0f, 0.0f);        //bottom right
//    glVertex3f(700, 100.0f, 0.0f);       // Top Right
//    glVertex3f(650,100.0f, 0.0f);        // Top Left
//    glEnd();
    
    // 3rd obstacle
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.5f,0.5f);            // Set The Color To White
    glVertex3f((50.0f-50.0f)+600, 50.0f, 0.0f);        // bottom left
    glVertex3f((150.0f-50.0f)+600, 50.0f, 0.0f);        //bottom right
    glVertex3f((150.0f-50.0f)+600, 80.0f, 0.0f);       // Top Right
    glVertex3f((125.0f-50.0f)+600, 85.0f, 0.0f);
    glVertex3f((110.0f-50.0f)+600, 105.0f, 0.0f);
    glVertex3f((75.0f-50.0f)+600, 105.0f, 0.0f);
    glVertex3f((75.0f-50.0f)+600,  85.0f, 0.0f);
    glVertex3f((50.0f-50.0f)+600,82.0f, 0.0f);        // Top Left
    glEnd();
    
    glBegin(GL_POLYGON);
    glColor3f(0.0f,0.0f, 0.0f);
    glVertex3f((76.0f-50.0f)+600,  83.0f, 0.0f);
    glVertex3f((122.0f-50.0f)+600, 83.0f, 0.0f);
    glVertex3f((110.0f-50.0f)+600, 103.0f, 0.0f);
    glVertex3f((78.0f-50.0f)+600, 103.0f, 0.0f);
    glVertex3f((78.0f-50.0f)+600, 83.0f, 0.0f);
    glEnd();
    
    drawCircle(25+600, 50, 10);
    drawCircle(75+600, 50, 10);
    
    obstacleX3=obstacleX2+350;
    oY3=50.0f;
    
    /*
     glBegin(GL_TRIANGLES);
     glVertex3f(150.0f, 50.0f, 0.0f);
     glVertex3f(150.0f, 100.0f, 0.0f);
     glVertex3f(200.0f, 50.4f, 0.0f);
     glEnd();
     
     glBegin(GL_LINE_LOOP);
     glVertex3f(75.0f, 100.0f, 0.0f);
     glVertex3f(90.0f, 100.0f, 0.0f);
     glVertex3f(90.0f, 120.4f, 0.0f);
     glVertex3f(75.0f, 120.4f, 0.0f);
     glEnd();
     
     
     drawCircle(70, 50, 10);
     drawCircle(130, 50, 10);
     */
    glPopMatrix();
    
}

void drawPowerUp(void){
    
    if(powerUpX<=0){
        powerUpX=1300;

    }
//    if (pwrUp) {
        glPushMatrix();
        glTranslated(powerUpX,powerUpY,0.0f);
        glBegin(GL_LINE_LOOP);    //1st PowerUp
        glColor3f(0.0f,0.0f,1.0f);            // Set The Color To blue
        glVertex3f(0, 150.0f, 0.0f);        // bottom left
        glVertex3f(50, 150.0f, 0.0f);        //bottom right
        glVertex3f(50, 200.0f, 0.0f);       // Top Right
        glVertex3f(0,200.0f, 0.0f);        // Top Left
        glEnd();
        glPopMatrix();
        pY1=150.0f;
    
//    }else{
    
//        glPushMatrix();
//        glTranslated(powerUpX-2200,powerUpY,0.0f);
//        glBegin(GL_LINE_LOOP);    //2nd PowerUp
//        glColor3f(0.0f,0.0f,1.0f);            // Set The Color To blue
//        glVertex3f(1350.0f+800, 50.0f, 0.0f);        // bottom left
//        glVertex3f(1400.0f+800, 50.0f, 0.0f);        //bottom right
//        glVertex3f(1350.0f+800, 100.0f, 0.0f);       // Top Right
//        glVertex3f(1400.0f+800,100.0f, 0.0f);        // Top Left
//        glEnd();
//        glPopMatrix();
//        pY2= 50.0f;
//    }
}

void checkCollision(void){
    
    // CHecking the powerUps
    if (( carPosionX < abs(powerUpX+1) && carPosionX > abs(powerUpX-1 )) && (carPosionY+51>pY1 && carPosionY+49<pY1)){
        
        carPosionX+=100.0f;
        if(carPosionX>=600){
            carPosionX=600.0f;
            printf("You've won");
            //you've won screen
        }
        printf("PWRUP");

    }
    if (( carPosionX < abs(obstacleX1+1) && carPosionX > abs(obstacleX1-1 )) && (carPosionY+51>oY1 && carPosionY+49<oY1))
    {
        //if((obstaclesX == carPosionX) && ((carPosionY+50==oY1) )){
     
        carPosionX-=100.0f;
        obstaclesX=1000;
        if(abs(carPosionX)>0.0f-1 && abs(carPosionX)<0.0f+1){
            GameOverF=true;
             gameOver();
            printf("GAME OVER!!!");
            // End The Game
        }
        printf("opps");
    }
    
    if (( carPosionX > abs(obstacleX2+1) && carPosionX > abs(obstacleX2-1 )) && (carPosionY+51>oY2 && carPosionY+49<oY2)){
        carPosionX-=100.0f;
        obstaclesX=1000;
        if(abs(carPosionX)>0.0f-1 && abs(carPosionX)<0.0f+1){
            GameOverF=true;
             gameOver();
            printf("GAME OVER!!!");
            // End The Game
        }
     
     printf("opps2");
     }
    
    if (( carPosionX > abs(obstacleX3+1) && carPosionX > abs(obstacleX3-1 )) && (carPosionY+51>oY3 && carPosionY+49<oY3)){
        carPosionX-=100.0f;
        obstaclesX=1000;
        if(abs(carPosionX)>0.0f-1 && abs(carPosionX)<0.0f+1){
            GameOverF=true;
            gameOver();
            
            printf("GAME OVER!!!");
            // End The Game
        }
        printf("opps3");
    }
     
    //
    //if (( carPosionX < obstaclesX+1 && carPosionX > obstaclesX-1 ) && (carPosionY+51>oY3 && carPosionY+49<oY3)){
    ////if((obstaclesX == carPosionX) && ((carPosionY+50==oY3) )){
    //    if(carPosionX==0.0f){
    //        printf("GAME OVER!!!");
    //    }else{
    //        carPosionX-=100.0f;
    //    }
    //    printf("opps3");
    //}
    
}
void gameOver(void){
    if(GameOverF){
        
    }
    glEnable(GL_TEXTURE_2D);
    loadBMP(&texID,"game_over.bmp",640,480,true);
    backGroundX=0;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gameOverImg);
    glColor3f(1,1,1);
    glPushMatrix();
    glTranslatef(gameOverX, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glTexCoord2f(rep, 0.0f);
    glVertex3f(800, 0, 0);
    glTexCoord2f(rep, rep);
    glVertex3f(800, 600, 0);
    glTexCoord2f(0.0f, rep);
    glVertex3f(0, 600, 0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    
    
        //loadBMP(&scndCar,"amxCar.bmp",600,169,true);

}

void Timer(int value){
    if(GameOverF){
    exit(EXIT_SUCCESS);
    }
    
    glutTimerFunc(5000000, Timer, 0);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            if(carPosionY==100.0f)
            {
                break;
            }else
            {
                carPosionY =+100.0f;
            }
            break;
            
        case GLUT_KEY_DOWN:
            if (carPosionY == 0.0f) {
                break;
            }else{
                carPosionY -=100.0f;
            }
            break;
            
        default:
            break;
    }
}
void Key(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
            
        default:
            break;
    }
}
