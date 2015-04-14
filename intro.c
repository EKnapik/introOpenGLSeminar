// This is an introduction to openGL in C
// This particular tutorial in written for
// Mac using depricated GLUT but can easily be
// converted to using freeGlut and windows or Linux


/**
* These are the two main includes that are required
* to open a window using openGL, the GLUT is a windowing
* API which will actually make openGL calls for you, but
* since they are very terse and will change depending on the system
* I just use GLUT.
*
*
* As for gl.h this is the openGL header file found under OpenGL
* Mac maintains the current version of openGL and is backwards compatible
* I think
**/
#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>


#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH 512

// I am defining these as globals but yea
// Just don't want to pay attention to them or work with
// C "Object Oriented Design" 
// Define my OpenGL buffers and shader program
GLuint vbuffer, ebuffer;
GLuint program; // This is the "id" of the shader program

// Define my vertexArray and elementArray
float *vertexArray; // This holds vertex data 4 entries make one vertex
float *elementArray; // This is how the points should be connected
                     // or which points make a triangle by default
                     // I believe it just goes the next three points make
                     // a triangle. 

int numVerts; // this is the total number of verticies




void initPipeline( void )
{


}


void initBuffers( void )
{

}



// The shader program we are adding this to is global
void initShader( GLenum type, char *file );
{

}





/**
* Clear our frame buffers
* load the values/data for shaders, when loading these it is assumed
* that the shader program you are loading to is the one currently in use
*
* Bind the buffer you want to get your points from
* draw the points from the buffer in some way
*
* load next buffer if you want (draw another object)
*
* update your internal representation of object position for collisions and stuff
* perform all checks that you want
*
* unbind any currently bound buffers
* glFlush();
*
* swapBuffers
**/
void display( void )
{
    // clear your frame buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // swap the buffers -> makes what you rendered to the screen facing buffer
    glutSwapBuffers();
}



int main( int argc, char *argv[] )
{

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

    // INITIAL_HEIGHT this is used to set how big the window is
    glutInitWindowSize( INITIAL_HEIGHT, INITIAL_WIDTH );
    glutCreateWindow( "Intro Seminar" ); // look at that nice title <-

    glEnable( GL_DEPTH_TEST );
    glEnable( GL_CULL_FACE );
    glShadeModel( GL_SMOOTH ); // This is by default but wanted to show this exists

    // Set the background color
    glClearColor( 101.0/255, 156.0/255, 239.0/255, 1.0 );

    // Sets the color of the cull faces to the background color
    glCullFace( GL_BACK );

    // Want to draw wire frames
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Sets up the display function
    glutDisplayFunc( display );

    glutMainLoop();

    return 0; // This is actually never called
    // When glutMainLoop(); ends it will exit the program
}


// Sidenote here triangles should be defined counter clockwise if you want
// them to show up propperly. As OpenGL Defines it the front of a triangle
// is face that you want when you look at it head on. Define the triangle in
// counter clockwise vertex ordering so the front face is facing you our out.


