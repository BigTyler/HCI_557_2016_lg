//
//  main.cpp
//  OpenGL4Test
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
//

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"

// this line tells the compiler to use the namespace std.
// Each object, command without a namespace is assumed to be part of std. 
using namespace std;




static const string vs_string =
"#version 410 core                                                 \n"
"                                                                   \n"
"uniform mat4 projectionMatrix;                                    \n"
"uniform mat4 viewMatrix;                                           \n"
"uniform mat4 modelMatrix;                                          \n"
"in vec3 in_Position;                                               \n"
"                                                                   \n"
"in vec3 in_Color;                                                  \n"
"out vec3 pass_Color;                                               \n"
"                                                                  \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);  \n"
"    pass_Color = in_Color;                                         \n"
"}                                                                 \n";

// Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
static const string fs_string  =
"#version 410 core                                                 \n"
"                                                                  \n"
"in vec3 pass_Color;                                                 \n"
"out vec4 color;                                                    \n"
"void main(void)                                                   \n"
"{                                                                 \n"
"    color = vec4(pass_Color, 1.0);                               \n"
"}                                                                 \n";




/// Camera control matrices
glm::mat4 projectionMatrix; // Store the projection matrix
glm::mat4 viewMatrix; // Store the view matrix
glm::mat4 modelMatrix; // Store the model matrix




// The handle to the window object
GLFWwindow*         window;


// Define some of the global variables we're using for this sample
GLuint program;







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// Fill this functions with your model code.

// USE THESE vertex array objects to define your objects
unsigned int vaoID[2];

unsigned int vboID[4];

unsigned int vboID2[2];


/*!
 ADD YOUR CODE TO CREATE THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
unsigned int createTriangleStripModel(void)
{
    // use the vertex array object vaoID[0] for this model representation
    
	float triBottom01V[12] = { 2.5, -0.5, -0.5, -0.5, -0.5, -0.5, 2.5,	0.5, -0.5, -0.5, .5, -0.5 };
	float triBottom01C[12] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, };
	float triBottom02V[12] = { .5, .5, -.5, -.5, .5, -.5, .5, 2.5, -.5, -.5, 2.5, -.5 };
	float triBottom02C[12] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, };
	float Combo[174] = { 2.5, -0.5, -0.5, -0.5, -0.5, -0.5, 2.5, 0.5, -0.5, -0.5, .5, -0.5, .5, .5, -.5, -.5, .5, -.5, .5, 2.5, -.5, -.5, 2.5, -.5, -.5, 2.5, .5, -.5, .5, 1.5, -.5, .5, .5, -.5, -.5, 1.5, -.5, -.5, .5,-0.5, 2.5, 0.5, -0.5, 2.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, -0.5, 1.5, 0.5, -0.5, 1.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 2.5, -0.5, 0.5, 0.5, -0.5, -0.5, 2.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 2.5, 0.5, 2.5, -0.5, 0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, 0.5, -0.5, 0.5, 0.5, 0.5, 0.5, 2.5, 0.5, 0.5, 0.5, -0.5, 0.5, 2.5, -0.5, 2.5, 0.5, 0.5, 0.5, 0.5, 0.5, 2.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, -0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, -0.5, 2.5, -0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 1.5, -0.5, -0.5, 1.5, 0.5, 0.5, 1.5, -0.5, 0.5, 1.5, 0.5, 0.5, 1.5, 0.5, 2.5, 0.5, -0.5, 0.5, 1.5, -0.5, 2.5, 0.5 };
	float ComboC[174] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };

	glGenVertexArrays(1, &vaoID[0]);  // creates the vertex array
	glBindVertexArray(vaoID[0]);  //opens up so that following code works on THAT vertex array
	//glGenBuffers(2, vboID);
	glGenBuffers(1, &vboID[0]);
	glGenBuffers(1, &vboID[1]);

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Open up first Buffer object so that changes apply to it
	glBufferData(GL_ARRAY_BUFFER, 174 * sizeof(GLfloat), Combo, GL_STATIC_DRAW);
//	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), triBottom01V, GL_STATIC_DRAW); // allocate the memory needed for the buffer and give instructions about how it will be used
	//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), triBottom02V, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // buffer data attributes, start at 0, use three floats per vertex
	glEnableVertexAttribArray(0); // activate the verex atriubte array at the index passed as a paramter
	
    //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); 
	glBufferData(GL_ARRAY_BUFFER, 174 * sizeof(GLfloat), ComboC, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), triBottom01C, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), triBottom02C, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
	glEnableVertexAttribArray(1); // activate the verex atriubte array at the index passed as a paramter

	glBindVertexArray(0); // Disable our Vertex Buffer Object
	
    //TODO:
    //vaoID[0];
    
    return 1;
}

/*!
 ADD YOUR CODE TO CREATE A MODEL USING PRIMITIVES OF YOUR CHOISE TO THIS FUNCTION
 */
unsigned int createPolygonModel(void)
{
    // use the vertex array object vaoID[1] for this model representation
	float polyBottomV[270] = { 2.5, -0.5, -0.5, -0.5, -0.5, -0.5, 2.5, 0.5, -0.5, -0.5, -0.5, -0.5, 2.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 2.5, -0.5, 0.5, 0.5, -0.5, -0.5, 2.5, -0.5, 0.5, 2.5, -0.5, -0.5, 2.5, 0.5, -0.5, 0.5, 1.5, -0.5, 0.5, 0.5, -0.5, 0.5, 1.5, -0.5, 0.5, 0.5, -0.5, -0.5, 1.5, -0.5, 0.5, 0.5, -0.5, -0.5, 1.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, -0.5, -0.5, 2.5, 0.5, -0.5, -0.5, -0.5, -0.5, 2.5, -0.5, -0.5, 2.5, 0.5, -0.5, -0.5, 1.5, 0.5, -0.5, 1.5, -0.5, -0.5, -0.5, 0.5, -0.5, 1.5, -0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, -0.5, 0.5, -0.5, 0.5, 2.5, -0.5, -0.5, 0.5, -0.5, 0.5, 2.5, -0.5, 0.5, 2.5, -0.5, -0.5, 2.5, -0.5, 0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, 0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, 1.5, 0.5, 0.5, 0.5, 0.5, -0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1.5, 0.5, 2.5, 0.5, 0.5, 0.5, 0.5, 0.5, 2.5, 0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, 0.5, 0.5, -0.5, 0.5, 2.5, -0.5, 2.5, 0.5, 0.5, 0.5, 0.5, 0.5, 2.5, 0.5, -0.5, 0.5, 0.5, 0.5, 2.5, 0.5, -0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, -0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, 0.5, 0.5, 2.5, -0.5, -0.5, 2.5, -0.5, 2.5, -0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, 0.5, 0.5, -0.5, 0.5, 2.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, -0.5, 1.5, -0.5, -0.5, 1.5, 0.5, 0.5, 1.5, -0.5, -0.5, 1.5, 0.5, 0.5, 1.5, -0.5, 0.5, 1.5, 0.5, 0.5, 1.5, -0.5, 0.5, 1.5, 0.5, 2.5, 0.5, -0.5, 0.5, 1.5, 0.5, 2.5, 0.5, -0.5, 2.5, 0.5 };  //The vertices for the bottom of the polygon primitive
	float polyBottomC[270] = { 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 };  //colors for the vertices for the bottom of the polygon primitive 
	
	glGenVertexArrays(1, &vaoID[1]);  //create the vertex array
	glBindVertexArray(vaoID[1]);  //bind/open it up for editing
	glGenBuffers(1, &vboID2[0]);  //create bufer object for vertices
	glGenBuffers(1, &vboID2[1]);  // create buffer object for colors

	// vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboID2[0]); // open/bind verex bufer object
	glBufferData(GL_ARRAY_BUFFER, 270 * sizeof(GLfloat), polyBottomV, GL_STATIC_DRAW); // allocate space and add array

	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // tell bufer how to use data
	glEnableVertexAttribArray(0); // activate vao buffer
	
	
								  //Color
	glBindBuffer(GL_ARRAY_BUFFER, vboID2[1]);
	glBufferData(GL_ARRAY_BUFFER, 270 * sizeof(GLfloat), polyBottomC, GL_STATIC_DRAW);

	glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
    //TODO:
    //vaoID[1];
    
    return 1;
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderTriangleStripModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[0]);
        
	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY TRIANGLES / VERTICES YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLE_STRIP, 0 , 4 );  //Bottom A
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);  //Bottom B
	glDrawArrays(GL_TRIANGLE_STRIP, 8, 5);  //Right Side A
	glDrawArrays(GL_TRIANGLE_STRIP, 13, 4);  //Right Side B
	glDrawArrays(GL_TRIANGLE_STRIP, 17, 4);  //Back A
	glDrawArrays(GL_TRIANGLE_STRIP, 21, 4);  //Back B
	glDrawArrays(GL_TRIANGLE_STRIP, 25, 5);  //Left A
	glDrawArrays(GL_TRIANGLE_STRIP, 30, 4);  //Left B
	glDrawArrays(GL_TRIANGLE_STRIP, 34, 4); // Left C
	glDrawArrays(GL_TRIANGLE_STRIP, 38, 4);  // Front A

	glDrawArrays(GL_TRIANGLE_STRIP, 42, 4);  // Front B
	glDrawArrays(GL_TRIANGLE_STRIP, 46, 4);  // Top A
	glDrawArrays(GL_TRIANGLE_STRIP, 50, 4);  // Top B
	glDrawArrays(GL_TRIANGLE_STRIP, 54, 4);  //Top C
    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



/*!
 ADD YOUR CODE TO RENDER THE TRIANGLE STRIP MODEL TO THIS FUNCTION
 */
void renderPolygonModel(void)
{

    // Bind the buffer and switch it to an active buffer
    glBindVertexArray(vaoID[1]);
        

	// HERE: THIS CAUSES AN ERROR BECAUSE I DO NOT KNOW HOW MANY POLYGONS YOU HAVE.
	// COMPLETE THE LINE
    // Draw the triangles
    glDrawArrays(GL_TRIANGLES, 0 , 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDrawArrays(GL_TRIANGLES, 6, 3); 
	glDrawArrays(GL_TRIANGLES, 9, 3);  //this line up is bottom
	glDrawArrays(GL_TRIANGLES, 12, 3);
	glDrawArrays(GL_TRIANGLES, 15, 3);
	glDrawArrays(GL_TRIANGLES, 18, 3);
	glDrawArrays(GL_TRIANGLES, 21, 3);
	glDrawArrays(GL_TRIANGLES, 24, 3);  //this line up is right side
	glDrawArrays(GL_TRIANGLES, 27, 3);
	glDrawArrays(GL_TRIANGLES, 30, 3);
	glDrawArrays(GL_TRIANGLES, 33, 3);  
	glDrawArrays(GL_TRIANGLES, 36, 3);  //this line up is the back
	glDrawArrays(GL_TRIANGLES, 39, 3);
	glDrawArrays(GL_TRIANGLES, 42, 3);  //this line up left A
	glDrawArrays(GL_TRIANGLES, 45, 3);
	glDrawArrays(GL_TRIANGLES, 48, 3);
	glDrawArrays(GL_TRIANGLES, 51, 3);
	glDrawArrays(GL_TRIANGLES, 54, 3);
	glDrawArrays(GL_TRIANGLES, 57, 3); //this line p left B
	glDrawArrays(GL_TRIANGLES, 60, 3);
	glDrawArrays(GL_TRIANGLES, 63, 3); //this line up Front A
	glDrawArrays(GL_TRIANGLES, 66, 3);
	glDrawArrays(GL_TRIANGLES, 69, 3); // this line up front B
	glDrawArrays(GL_TRIANGLES, 72, 3);
	glDrawArrays(GL_TRIANGLES, 75, 3); //this line up top A
	glDrawArrays(GL_TRIANGLES, 78, 3);
	glDrawArrays(GL_TRIANGLES, 81, 3);
	glDrawArrays(GL_TRIANGLES, 84, 3);
	glDrawArrays(GL_TRIANGLES, 87, 3);  //this line up Top B

	

    // Unbind our Vertex Array Object
    glBindVertexArray(0);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*!
 This function creates the two models
 */
void setupScene(void) {
    
    createTriangleStripModel();
	createPolygonModel();
    //renderTriangleStripModel();
    
}




int main(int argc, const char * argv[])
{
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
	// Prepares some defaults
	CoordSystemRenderer* coordinate_system_renderer = new CoordSystemRenderer(10.0);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// The Shader Program starts here
    
    // Vertex shader source code. This draws the vertices in our window. We have 3 vertices since we're drawing an triangle.
    // Each vertex is represented by a vector of size 4 (x, y, z, w) coordinates.
    static const string vertex_code = vs_string;
    static const char * vs_source = vertex_code.c_str();
    
    // Fragment shader source code. This determines the colors in the fragment generated in the shader pipeline. In this case, it colors the inside of our triangle specified by our vertex shader.
    static const string fragment_code = fs_string;
    static const char * fs_source = fragment_code.c_str();
    
    // This next section we'll generate the OpenGL program and attach the shaders to it so that we can render our triangle.
    program = glCreateProgram();
    
    // We create a shader with our fragment shader source code and compile it.
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    
    // We create a shader with our vertex shader source code and compile it.
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    
    // We'll attach our two compiled shaders to the OpenGL program.
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    
    glLinkProgram(program);
    
    // We'll specify that we want to use this program that we've attached the shaders to.
    glUseProgram(program);
    
    //// The Shader Program ends here
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    /// IGNORE THE NEXT PART OF THIS CODE
    // It controls the virtual camera
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.6f, 0.7f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    
    projectionMatrix = glm::perspective(1.1f, (float)800 / (float)600, 0.1f, 100.f);
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); // Create our model matrix which will halve the size of our model
    viewMatrix = glm::lookAt(glm::vec3(1.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    int projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrix"); // Get the location of our projection matrix in the shader
    int viewMatrixLocation = glGetUniformLocation(program, "viewMatrix"); // Get the location of our view matrix in the shader
    int modelMatrixLocation = glGetUniformLocation(program, "modelMatrix"); // Get the location of our model matrix in the shader
    
    
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
    
    
	 //// The Shader Program ends here
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    //// START TO READ AGAIN
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    


    glBindAttribLocation(program, 0, "in_Position");
    glBindAttribLocation(program, 1, "in_Color");
    

    
    // this creates the scene
    setupScene();
    
    int i=0;

    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
        // this draws the coordinate system
		coordinate_system_renderer->draw();
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This generate the object
        // Enable the shader program
        glUseProgram(program);
        
        // this changes the camera location
        glm::mat4 rotated_view = viewMatrix * GetRotationMatrix();
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &rotated_view[0][0]); // send the view matrix to our shader
        

        // This moves the model to the right
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        

		// This line renders your triangle strip model
        renderTriangleStripModel();
        

        // This moves the model to the left
        modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, -0.0f, 0.0f));
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
        
		// This line renders your Ppolygon model
        renderPolygonModel();
        
        
		// disable the shader program
        glUseProgram(0);


        //// This generate the object
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
	// delete the coordinate system object
	delete coordinate_system_renderer;

    // Program clean up when the window gets closed.
    glDeleteVertexArrays(2, vaoID);
    glDeleteProgram(program);
}

