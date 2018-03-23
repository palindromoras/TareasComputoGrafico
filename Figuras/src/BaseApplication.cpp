//

//  HelloCube

//

//  Created by Pedro  Cervantes Pintor on 11/Oct/14.

//
#include "stdafx.h"
#define GLM_FORCE_RADIANS
#include "BaseApplication.h"
#include <iostream>
#include <vector>

#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GLFW\glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ShaderFuncs.h"



BaseApplication::BaseApplication() : vEye(0.0f, 50.0f, 100.0f),
							_drawMode (0),
							shader(0),
							_currentBuffer(0),
							_nextBuffer(1)
							
{
}

BaseApplication::~BaseApplication()
{
	glDeleteTextures(2, texturesID);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(2, pboID);
}

void BaseApplication::initTextures()
{
	glGenTextures(2, texturesID);
	//Textura 0
	glBindTexture(GL_TEXTURE_2D, texturesID[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffers[0]);

	//Sin promediar
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Textura 1
	glBindTexture(GL_TEXTURE_2D, texturesID[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffers[1]);

	//Sin promediar
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	

}

void BaseApplication::initPBOs()
{
	// create 2 pixel buffer objects, you need to delete them when program exits.
	// glBufferData with NULL pointer reserves only memory space.
	glGenBuffers(2, pboID);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID[0]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, WIDTH * HEIGHT * RGBA, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID[1]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, WIDTH * HEIGHT * RGBA, 0, GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}


void BaseApplication::init()
{
	fakeBuffers();
	initTextures();
	initPBOs();
	GLfloat vertices[]
	{
		//triangulo 0


		-1.0f, -1.0f, 0.0f, 1.0f,

		1.0f, -1.0f, 0.0f, 1.0f,

		-1.0f, 1.0f, 0.0f, 1.0f,

		//triangulo2
		//-1.0f, 1.0f, 0.0f, 1.0f,

		//1.0f, -1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
	};
	GLfloat texCoords[] 
	{
		0.0f, 1.0f, 0.0f, 0.0f,  //TEX
		1.0f, 1.0f, 0.0f, 0.0f,//TEX
		0.0f, 0.0f, 0.0f, 0.0f, //TEX

		1.0f, 0.0f, 0.0f, 0.0f//TEX

		//0.0f, 1.0f, 0.0f, 0.0f,//TEX
		//1.0f, 0.0f, 0.0f, 0.0f,//TEX
	};

	vEye = glm::vec3(0.0f, 50.0f, 50.0f);

	std::string sVertex, sFragment;
	sVertex = loadTextFile("shaders/passThru.v");
	sFragment = loadTextFile("shaders/passThru.f");
	InitializeProgram(shaderID, sVertex, sFragment);
	
	uTransform = glGetUniformLocation(shaderID, "mTransform");
	sampler = glGetUniformLocation(shaderID, "theTexture");

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texCoords), texCoords);
	
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	setup();
}


void BaseApplication::display()
{
	processPBO();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(shaderID);

	mProjectionMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f);
	mTransform = glm::mat4(1.0f) * mProjectionMatrix;

	glUniformMatrix4fv(uTransform, 1, GL_FALSE, glm::value_ptr(mTransform));

	//pasamos parametros de textura
	glBindTexture(GL_TEXTURE_2D, texturesID[_currentBuffer]);
	glUniform1i(sampler, _currentBuffer);
	glActiveTexture(_currentBuffer==0? GL_TEXTURE0 : GL_TEXTURE1);
	//glActiveTexture(GL_TEXTURE0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	swapbuffers();
}

void BaseApplication::processPBO()
{
	// bind the texture and PBO
	glBindTexture(GL_TEXTURE_2D, texturesID[_currentBuffer]); //solo se necesita una textura
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID[_currentBuffer]);

	// copy pixels from PBO to texture object
	// Use offset instead of pointer.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, 0);


	// bind PBO to update texture source
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboID[_nextBuffer]);

	// Note that glMapBufferARB() causes sync issue.
	// If GPU is working with this buffer, glMapBufferARB() will wait(stall)
	// until GPU to finish its job. To avoid waiting (idle), you can call
	// first glBufferDataARB() with NULL pointer before glMapBufferARB().
	// If you do that, the previous data in PBO will be discarded and
	// glMapBufferARB() returns a new allocated pointer immediately
	// even if GPU is still working with the previous data.
	glBufferData(GL_PIXEL_UNPACK_BUFFER, WIDTH * HEIGHT * RGBA, 0, GL_STREAM_DRAW);

	// map the buffer object into client's memory

	_screenBuffer = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_READ_WRITE);
	if (_screenBuffer)
	{
		// update data directly on the mapped buffer
		//updatePixels(ptr);
		draw();
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER); // release the mapped buffer
	}

	// it is good idea to release PBOs with ID 0 after use.
	// Once bound with 0, all pixel operations are back to normal ways.
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void BaseApplication::reshape(int w, int h)
{
	//glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	//mProjectionMatrix = glm::perspective(45.0f, (float)w / (float)h, 1.0f, 10000.f);
}



									 
void BaseApplication::cursor_position(double xpos, double ypos)
{
	int width, heigth;

	glfwGetWindowSize(window, &width, &heigth);
}


void BaseApplication::fakeBuffers()
{
	for (int i = 0; i < WIDTH*HEIGHT*RGBA; i+=4)
	{
		Buffers[1][i] = 255;
		Buffers[1][i + 1] = 0;
		Buffers[1][i + 2] = 0;
		Buffers[1][i + 3] = 255;

		Buffers[0][i] = 0;
		Buffers[0][i + 1] = 255;
		Buffers[0][i + 2] = 0;
		Buffers[0][i + 3] = 255;
	}
}

void BaseApplication::swapbuffers()
{
	_currentBuffer = 1 - _currentBuffer;
	_nextBuffer = 1 - _currentBuffer;
}


void BaseApplication::putPixel(GLubyte *buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
{
	int offset = (x + (y * WIDTH)) * RGBA;
	if (offset < 0 || offset > WIDTH * HEIGHT *RGBA)
		return;

	buffer[offset]	 = R;
	buffer[offset + 1] = G;
	buffer[offset + 2] = B;
	buffer[offset + 3] = A;

}

void BaseApplication::putPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
{
	putPixel(_screenBuffer, x, y, R, G, B, A);
}

void BaseApplication::line(int x0, int y0, int x1, int y1) {
	double dx = x1-x0;
	double dy = y0-y1;
	double a = dy / dx;
	float ang = (atan2(dy, dx)) * 180 / 3.1416;
	if (ang <= 0) {
		ang = 360 + ang;
	}
	if (ang > 0 && ang <= 45) {
		float A = -(y1 - y0);
		float B = x1 - x0;
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int y = y0;
		for (int x = x0 + 1; x <= x1; x++) {
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				y--;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	if (ang > 45 && ang <= 90) { //arriba en medio
		float A = (x1 - x0);
		float B = -(y1 - y0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int x = x0;
		for (int y = y0 + 1; y >= y1; y--) {
			//std::cout << "Linea Azul" << std::endl;
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				x++;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	
	if (ang > 90 && ang <= 135) { //arriba izquierda centro
		float A = -(x1 - x0);
		float B = -(y1 - y0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int x = x0;
		for (int y = y0 - 1; y >= y1; y--) {
			//std::cout << "90 - 135" << std::endl;
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				x--;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	if (ang > 135 && ang <= 180) {
		float A = -(y1 - y0);
		float B = -(x1 - x0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int y = y0;
		for (int x = x0 - 1; x >= x1; x--) {
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				y--;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	if (ang > 180 && ang <= 225) {
		float A = (y1 - y0);
		float B = -(x1 - x0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int y = y0;
		for (int x = x0 - 1; x >= x1; x--) {
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				y++;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	if (ang > 225 && ang <= 270) { //abajo izquierda centro
		float A = -(x1 - x0);
		float B = (y1 - y0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int x = x0;
		for (int y = y0 - 1; y < y1; y++) {
			//std::cout << "90 - 135" << std::endl;
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				x--;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	if (ang > 270 && ang <= 315) { //abajo en medio
		float A = (x1 - x0);
		float B = (y1 - y0);
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int x = x0;
		for (int y = y0 + 1; y < y1; y++) {
			//std::cout << "Linea Azul" << std::endl;
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				x++;
			}
			putPixel(x,y, 255, 255, 255, 255);
		}
	}
	if (ang > 315 && ang <= 360) {
		float A = (y1 - y0);
		float B = x1 - x0;
		float dinicial = 2 * A + B;
		float DE = A;
		float DNE = A - B;
		putPixel(x0, y0, 255, 255, 255, 255);
		float d = A - (B / 2);
		int y = y0;
		for (int x = x0 + 1; x <= x1; x++) {
			if (d < 0) {
				//std::cout << "ang: " << ang << " d: " << d << std::endl;
				d += DE;
			}
			else {
				d += DNE;
				y++;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}
	}
	/*if (ang > 0 && ang <= 45) {
		for (int x = x0 + 1; x <= x1; x++) {
			if (d < 0) {
				d += DE;
			}
			else {
				d += DNE;
				y++;
			}
			putPixel(x, y, 255, 255, 255, 255);
		}*/
		/*if(ang >45 && ang <=90){
			putPixel(-x, y, 255, 255, 255, 255);
		}*/
		/* 
			putPixel(-x, y, 255, 255, 255, 255);
			putPixel(-y, x, 255, 255, 255, 255);
			putPixel(y, x, 255, 255, 255, 255);
		*/
}

void BaseApplication::putPixel(const int& x, const int& y, Color c)
{
	putPixel(x, y, c.R(),c.G(), c.B(), c.A());
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

void BaseApplication::setup()
{
}

void BaseApplication::update()
{
}

void BaseApplication::draw()
{
}


void BaseApplication::keyboard(int key, int scancode, int action, int mods)
{
	const float inc = 1.0;
	switch (action)
	{		
	case GLFW_PRESS:
		switch (key)
		{
		
		case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(window, GL_TRUE); break;		
		case GLFW_KEY_T: _currentBuffer = 1 - _currentBuffer; break;
		case GLFW_KEY_P:
			_drawMode = ++_drawMode % 3;
			switch (_drawMode)
			{
				case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
				case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
				case 2:	glPolygonMode(GL_FRONT, GL_FILL);
						glPolygonMode(GL_BACK, GL_LINE);
						break;
			}
		}
		//break;
		
	} //switch (action)
}
