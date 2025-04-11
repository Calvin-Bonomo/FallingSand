/*
 *  Real Time Image processing
 *  Demonstrates post-processing of video images
 *
 *  Relies on OpenCV VideoIO module to snarf video
 *
 *  On Ubuntu install OpenCV VideoIO with
 *    apt-get install libopencv-videoio-dev
 *
 *  On MSYS2 install OpenCV with
 *    pacman -S mingw-w64-x86_64-opencv
 *
 *  Key bindings:
 *  m          Toggle shader
 *  o          Change objects
 *  arrows     Change location
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx239.h"

#define SIM_TICK_TIME 0.016666667
// #define SIM_TICK_TIME 2
#define AIR 0x00000000
#define WALL 0x01007f01
#define SAND 0x00000f02
#define WATER 0x02000e03
#define SMOKE 0x04008004

float asp=1;   //  Aspect ratio
//  Images
double scale = 10;
int simWidth, simHeight;
int width,height;          //  Original image size
unsigned int* rgba;       //  Working array
unsigned int img=0; //  Image textures
//  Shader programs
int shader[2] = {0, 0};
unsigned int frameBuffer;
unsigned int iteration = 0;

unsigned int material = 1;
unsigned int num_mats = 4;
unsigned int materials[4] = {WALL, SAND, WATER, SMOKE};

int mouseHeld = 0;
double mouseX = 0, mouseY = 0;

//
//  Refresh display
//
void display(GLFWwindow* window)
{
   int wid,hgt;
   //  Set projection and view
   glfwGetFramebufferSize(window,&wid,&hgt);
   glViewport(0,0,wid,hgt);
   //  Set projection and view
   glUseProgram(shader[1]);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, img);
   int loc = glGetUniformLocation(shader[1], "buf");
   glUniform1i(loc, 0);
   loc = glGetUniformLocation(shader[1], "texelSize");
   glUniform2f(loc, 1.0/simWidth, 1.0/simHeight);

   glBegin(GL_TRIANGLE_STRIP);
   glVertex2f(-1,-1);
   glVertex2f(-1,1);
   glVertex2f(1,-1);
   glVertex2f(1,1);
   glEnd();
   glUseProgram(0);

   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glfwSwapBuffers(window);
}

//
//  Key pressed callback
//
void key(GLFWwindow* window,int key,int scancode,int action,int mods)
{
   //  Discard key releases (keeps PRESS and REPEAT)
   if (action==GLFW_RELEASE) return;

   //  Exit on ESC
   if (key == GLFW_KEY_ESCAPE)
     glfwSetWindowShouldClose(window,1);
   else if (key == GLFW_KEY_SPACE)
      material = (material + 1) % num_mats;
}

void mouseMove(GLFWwindow *window, double xpos, double ypos) {
   mouseX = xpos;
   mouseY = ypos;
}

void mouseDown(GLFWwindow *window, int button, int action, int mods) {
   mouseHeld = action == GLFW_PRESS;
}

void drawStuff() {
   if (mouseHeld) {
      double x = mouseX, y = mouseY;
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, img);
      glGetTextureSubImage(img, 0, 0, 0, 0, simWidth, simHeight, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, simWidth * simHeight * 4, rgba);
      if (x > 0 || x < width || y > 0 || y < height)
      {
         x /= scale;
         y /= -scale;
         y += simHeight;
         if (rgba[(int)x + (int)y * simWidth] == AIR)
            rgba[(int)x + (int)y * simWidth] = materials[material];
         int start = x, dist = 1;
         if ((int)x != 0 && rgba[(int)(x - 1) + (int)y * simWidth] == AIR) {
            rgba[(int)(x - 1) + (int)y * simWidth] = materials[material];
            start--;
            dist++;
         }
         if ((int)x != simWidth - 1 && rgba[(int)(x + 1) + (int)y * simWidth] == AIR) {
            rgba[(int)(x + 1) + (int)y * simWidth] = materials[material];
            dist++;
         }
         glTexSubImage2D(GL_TEXTURE_2D, 0, start, y, dist, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &rgba[start + (int)y * simWidth]);
         glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT);
      }

      glBindTexture(GL_TEXTURE_2D, 0);
   }
}

//
//  Window resized callback
//
void reshape(GLFWwindow* window,int w,int h)
{
   //  Ratio of the width to the height of the window
   // asp = (height>0) ? (double)width/height : 1;
   glViewport(0, 0, w, h);
   width = w;
   height = h;
}

//
//  Main program with GLFW event loop
//
int main(int argc,char* argv[])
{
   //  Initialize GLFW
   simWidth = 65;
   simHeight = 65;

   width = simWidth * scale;
   height = simHeight * scale;
   GLFWwindow* window = InitWindow("Calvin HW09",0,width,height,&reshape,&key,&mouseDown,&mouseMove);

   //  Working array
   rgba = (unsigned int*)calloc(1, sizeof(unsigned int)*simWidth*simHeight);
   if (!rgba) Fatal("Cannot allocate %d bytes for image\n",4*simHeight*simHeight);

   for (int i = 0; i < simWidth; i++) {
      for (int j = 0; j < simHeight; j++) {
         if (i == 0 || i == simWidth - 1 || j == 0 || j == simHeight - 1)
            rgba[i + j * simWidth] = WALL;
         else rgba[i + j * simWidth] = AIR;
      }
   } 

   //  Allocate frame buffers and textures
   glGenTextures(1,&img);

   glBindTexture(GL_TEXTURE_2D,img);
   glTexImage2D(GL_TEXTURE_2D,0,GL_R32UI,simWidth,simHeight,0,GL_RED_INTEGER,GL_UNSIGNED_INT,rgba);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
   glBindTexture(GL_TEXTURE_2D, 0);

   ErrCheck("Image");

   //  Load shaders
   shader[0] = CreateComputeShader("fallingsand.comp");
   shader[1] = CreateShaderProg("default.vert", "finaldraw.frag");
   //  Event loop
   ErrCheck("init");
   double lastTime = glfwGetTime(), now = lastTime;
   while(!glfwWindowShouldClose(window))
   {
      now = glfwGetTime();
      if (now - lastTime >= SIM_TICK_TIME)
      {
         glUseProgram(shader[0]);
         glMemoryBarrier(GL_TEXTURE_UPDATE_BARRIER_BIT);
         glBindImageTexture(0, img, 0, GL_TRUE, 0, GL_READ_WRITE, GL_R32UI);
         int loc = glGetUniformLocation(shader[0], "buf");
         glUniform1i(loc, 0);
         loc = glGetUniformLocation(shader[0], "iteration");
         glUniform1ui(loc, iteration++);
         loc = glGetUniformLocation(shader[0], "simSize");
         glUniform2i(loc, simWidth, simHeight);
         glDispatchCompute(1, 1, 1);
         glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
         lastTime = now;
      }

      drawStuff();

      ErrCheck("Comp");

      display(window);
      //  Process any events
      glfwPollEvents();
   }
   //  Shut down GLFW
   glfwDestroyWindow(window);
   glfwTerminate();
   return 0;
}
