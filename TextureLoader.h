/*
* Derekas Panagiwths 4014
* Thoma Athanasios 2979
*/


#ifndef TEXTURELOADER_H_
#define TEXTURELOADER_H_



class TextureLoader {
public:
	TextureLoader();
	static void drawTiltedSquare(int choice);
	GLuint loadTexture(const char* filename);



};

#endif /* TEXTURELOADER_H_ */
