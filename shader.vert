#version 120

// This is our vector which is a point of our shape
// because of version 120 this is a attribute
// later versions have this as an "in" type
attribute vec4 currentVertex;

// Our Transformation matrix
uniform mat4 transform;


void main()
{

    gl_Position = transform * currentVertex;

}

