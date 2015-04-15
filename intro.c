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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "shaderSetup.h"


#define INITIAL_HEIGHT 512
#define INITIAL_WIDTH 512

// I am defining these as globals but yea
// Just don't want to pay attention to them or work with
// C "Object Oriented Design" 
// Define my OpenGL buffers and shader program
GLuint vbuffer, ebuffer;
GLuint program; // This is the "id" of the shader program

// the location pointers of shader program code
GLuint vPosition;
GLuint transformLocation;

// Define my transform matrix here since this is for seminar
// Column Major identity matrix
float transformMatrix[] = { 1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1 };



// Define my vertexArray and elementArray
// This holds vertex data 4 entries make one vertex
// Create my vertex data for definining a square
// I need 24 values because 4 define a point and I have two triangles of 3 points each
float vertexArray[] = { -0.5,  0.5, 0.0, 1.0,
                         0.5, -0.5, 0.0, 1.0,
                        -0.5, -0.5, 0.0, 1.0,

                        -0.5,  0.5, 0.0, 1.0,
                         0.5,  0.5, 0.0, 1.0,
                         0.5, -0.5, 0.0, 1.0 };

// This is how the points should be connected
// or which points make a triangle by default
// I believe it just goes the next three points make a triangle. 
// since a square is only made out of 4 points we can actually
// tell openGL to use other points again, this is sometimes called an
// index buffer also, and it saves repeated data
// other connectivity: 0, 1, 2, 0, 4, 1
GLushort elementArray[] = { 0, 1, 2, 3, 4, 5 };

int numVerts = 6; // this is the total number of verticies

int time = 0;



void createBuffers( )
{
    // get and load the verticies for your shape
    float *points = vertexArray;
    int dataSize = numVerts * 4 * sizeof( float );

    // get and load the element data or connectivity
    GLushort *elements = elementArray;
    int elementDataSize = numVerts * sizeof( GLushort );

    // ask OpenGL for ONE  buffer object ID
    glGenBuffers( 1, &vbuffer );

    // State what kind of buffer we want to refer to
    // OpenGL can only have have one type of buffer be the current one
    // This is have the vbuffer be our current GL_ARRAY_BUFFER
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );

    // Load our data and connect it to our vbuffer object so we can
    // refer to it later just by binding the vbuffer object
    // type of data, the size in bytes, the data itself, how to draw it
    glBufferData( GL_ARRAY_BUFFER, dataSize, points, GL_STATIC_DRAW );

    // Some programs at this point have a global value of whether we have
    // initialized our buffer yet and this would be done right here


    // Similar process for the connectivity/element data
    glGenBuffers( 1, &ebuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, elementDataSize, elements, GL_STATIC_DRAW );


    // Stop having these buffers bound to the current OpenGL buffers
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


// This will be the place where we call the shader program creation
// Connect CPU variables to shader variables
// and set the initial values for our shader variables
void initPipeline( void )
{

    program = shaderSetup( "shader.vert", "shader.frag" );
    if( !program )
    {
        perror( "ERROR SETTING UP SHADERS\n" );
        exit(1);
    }

    // Get the location of our matrix and vertex variables after the
    // shader program has been compiled and linked
    //
    // glGetUniformLocation( shader program, "variableName" );
    // glGetAttribLocation( shader program, "variableName" );
    //
    // uniform variables are ones that can be changed or user controled
    // like the movement matrix or a simple boolean value
    //
    // attrib variables are ones that are refering to vertex data
    // these are not loaded but simply said how to load them/ interpret from the
    // ARRAY_BUFFER that is being used
    vPosition = glGetAttribLocation( program, "currentVertex" ); // the current vertex of shape
    transformLocation = glGetUniformLocation( program, "transform" ); // transformation matrix


    // set the current shader program to use
    glUseProgram( program );


    // create the scene I want to draw
    createBuffers();
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
* glFlush(); // glutSwapBuffers does this
*
* swapBuffers
**/
void display( void )
{
    // clear your frame buffers
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // bind the vertex buffer you want to use
    glBindBuffer( GL_ARRAY_BUFFER, vbuffer );

    // bind the element buffer you want to use
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebuffer );

    // Which shader program should I use and what data will it be getting
    glUseProgram( program );

    // This is where you give the data to uniform variables and state how arrib
    // variables should get their data

    // how to look at my GL_ARRAY_BUFFER for vertex data
    // the object data ID, how many make up one, data type, should I transpose?,
    // step, beginning offset

    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glUniformMatrix4fv( transformLocation, 1, GL_FALSE, &transformMatrix );


    // everything is loaded now draw the shape with current buffers and shader program
    glDrawElements( GL_TRIANGLES, numVerts, GL_UNSIGNED_SHORT, (void *)0);


    // update my global transform
    //time += 1;
    //transformMatrix[12] = cos( time / 50.0 );

    /* Show the rotation around y axis  */
    //transformMatrix[0] = cos( time / 70.0 );

    //transformMatrix[2] = sin( time / 70.0 );
    //transformMatrix[8] = -sin( time / 70.0 );
    //transformMatrix[10] = cos( time / 70.0 );
    /*                                  */

    // swap the buffers -> makes what you rendered to the screen facing buffer
    glutSwapBuffers();
    glutPostRedisplay();
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
    // glShadeModel( GL_SMOOTH ); // This is by default but wanted to show this exists

    // Set the background color
    glClearColor( 101.0/255, 156.0/255, 239.0/255, 1.0 );

    // Sets the color of the cull faces to the background color
    glCullFace( GL_FRONT );

    // Want to draw wire frames us GL_LINE
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    // Initialize my shaders and shapes to draw
    initPipeline();


    // Sets up the display function
    glutDisplayFunc( display );

    glutMainLoop();

    return 0; // This is actually never called
    // When glutMainLoop(); ends it will exit the program
}

/* SIDE NOTES:                                                            */
// Sidenote here triangles should be defined counter clockwise if you want
// them to show up propperly. As OpenGL Defines it the front of a triangle
// is face that you want when you look at it head on. Define the triangle in
// counter clockwise vertex ordering so the front face is facing you our out.
//
// GLUT is bad because currently it renders as fast as it is allowed and
// with different/better or slower processors your rendering time will
// be skewed the timings you set to follow given the frames
// The propper way to do it is to have a separate thread run then call
// when to update your frames call a rerender.


