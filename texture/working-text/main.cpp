/* Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* File for "Drawing Text" lesson of the OpenGL tutorial on
 * www.videotutorialsrock.com
 */



#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "text3d.h"

using namespace std;

//Computes a scaling value so that the strings
//Drawing text is fairly important on occasion. There are a few possible approaches to drawing text in OpenGL. I'll outline four approaches and their pros and cons.

/*You can use bitmaps, not the kind that uses an image file, but a certain
 OpenGL construct that I haven't shown yet.
 Each character is represented as a bitmap.
 Each pixel in the bitmap has a bit, which is 1 if the pixel is colored and 0 if it is transparent.
 Each frame, you'd send the bitmaps for the characters to the graphics card.
 The graphics card would then bypass the usual 3D transformations and just draw the pixels right on the top of the window.
 I'm not a fan of this approach.
 It's slow, as you have to send each bitmap to the graphics card each frame, which is a lot of data.
 The method is also inflexible; you can't scale or transform the characters very well.
 You can do it in GLUT using glutBitmapCharacter. But again, there are a lot of disadvantages to the technique.

 You can represent characters using textures. Each character would correspond to a certain part of some texture,
 with some of the pixels in the texture white and the rest transparent (which I haven't shown how to do yet).
 You would draw a quadrilateral for each character and map the appropriate part of the appropriate texture to it.
 This approach is alright; it gives you some flexibility as to how and where you draw characters in 3D. It's also pretty fast.
 But the characters wouldn't scale too well; they'll look pixelated if you zoom in too far.

You can draw a bunch of lines in 3D, using GL_LINES (which I also haven't shown yet,
although you can probably guess how GL_LINES works).
This technique is fast and does allow scaling and otherwise transforming characters.
 However, the characters would look better if they covered an area rather than a perimeter.
 Also, it's fairly tedious to figure out a set of lines to represent each character.
 You can draw outlined text in GLUT using glutStrokeCharacter.

You can draw a bunch of polygons in 3D. This technique also allows us to transform characters well.
It even lets us give the characters 3D depth, so that they look 3D rather than flat.
 However, it's slower than drawing lines and using textures.
 Also, it's even more annoying to figure out how to describe each character as a set of polygons than it is to
 figure out how to describe one as a set of lines.
*/

/*etails aside, the basic idea is that there is a file with all of the positions of the 3D polygons for the different characters. The t3dDraw2D and t3dDraw3D functions take care of drawing the appropriate triangles. The functions themselves use some OpenGL techniques I haven't show yet, in order to make them draw as quickly as possible.*/

//will figure out a scaling factor
float computeScale(const char* strs[4]) {
	float maxWidth = 0;
	for(int i = 0; i < 4; i++) {
		float width = t3dDrawWidth(strs[i]);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}

	return 2.6f / maxWidth;
}

float _angle = -30.0f;
float _scale;
//The four strings that are drawn
const char* STRS[4] = {"CSE", "4204", "Computer", "Graphics"};

void cleanup() {
	t3dCleanup();
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			cleanup();
			exit(0);
	}
}
/*n our initRendering function, we have to set up some stuff for drawing 3D text. Namely, we have to load the positions of the triangles for each character from the file "charset". So we call t3DInit(), which is also from text3d.h.*/
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	t3dInit();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -8.0f);

	GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
	GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glRotatef(20.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-_angle, 0.0f, 1.0f, 0.0f);

	//The first parameter is the string to draw. The second is the horizontal alignment of the string;
	//a negative number is a left alignment, 0 is a centered alignment, and a positive number is a right alignment.
//	The third parameter is the vertical alignment of the string; a negative number is a top alignment,
// 0 is a centered alignment, and a positive number is a bottom alignment.
//You could draw text with multiple lines if you wanted to, using newline characters.)
//The fourth parameter is the 3D depth of the character, as a multiple of the height of the font.
// The fifth parameter is the height of each line, as a multiple of the height of the font.
// It could be used to indicate the spacing between lines, if we were drawing text with multiple lines.
//But we're not, so we'll just use the default value of 1.5.
    //If you want to draw text without depth, where all of the polygons are in the same plane, you could call t3dDraw2D,
	//which has the same parameters, except that it omits the depth of the text (since there is no depth). This is faster, since there are fewer polygons to draw, but it doesn't give us the nice-looking 3D text.
	//Draw the strings along the sides of a square
	glScalef(_scale, _scale, _scale);
	glColor3f(0.3f, 1.0f, 0.3f);
	for(int i = 0; i < 4; i++) {
		glPushMatrix();
		glRotatef(90 * i, 0, 1, 0);
		glTranslatef(0, 0, 1.5f / _scale);
		t3dDraw3D(STRS[i], 0, 0, 0.2f);
		glPopMatrix();
	}

	glutSwapBuffers();
}

void update(int value) {
	_angle += 1.5f;
	if (_angle > 360) {
		_angle -= 360;
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);

	glutCreateWindow("Drawing Text - videotutorialsrock.com");
	initRendering();

	_scale = computeScale(STRS);

	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(25, update, 0);

	glutMainLoop();
	return 0;
}









