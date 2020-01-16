/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/


#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <iostream>
#include <cstdio>

#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint rockTex;
GLuint paperTex;
GLuint scissorTex;
GLuint bombTex;


GLuint TextureLoader::loadTexture(const char* filename){
	glClearColor(0.0, 0.0, 0.0, 0.0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 3);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return texture;
}




void FreeTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
}

void square(GLuint texture) {

	glPushMatrix();

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);


	// tilt the square a bit
	glRotatef(160, 1.0f, 0.0f, 0.0f);


	// solid/wire cube size = 0.2f
	glBegin(GL_QUADS);
	 glTexCoord2d(0.0, 0.0);
	 glVertex2d(-0.1, -0.1);

	 glTexCoord2d(1.0, 0.0);
	 glVertex2d(+0.1, -0.1);

	 glTexCoord2d(1.0, 1.0);
	 glVertex2d(+0.1, +0.1);

	 glTexCoord2d(0.0, 1.0);
	 glVertex2d(-0.1, +0.1);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glPopMatrix();
}


TextureLoader::TextureLoader() {

	rockTex = loadTexture("rock.png");
	paperTex = loadTexture("paper.png");
	scissorTex = loadTexture("scissors.png");
	bombTex = loadTexture("tnt.png");

}


void TextureLoader::drawTiltedSquare(int choice){
	switch(choice){
		case 1:		//ROCK
			square(rockTex);
			break;
		case 2:		//PAPER
			square(paperTex);
			break;
		case 3:		//SCISSOR
			square(scissorTex);
			break;
		case 6:
			square(bombTex);
	}
}

