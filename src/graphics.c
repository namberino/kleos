#include <GL/glut.h>

#include "board.h"
#include "util.h"

const float lightSquare[3] = {1.0f, 1.0f, 0.9f};
const float darkSquare[3] = {0.3f, 0.5f, 0.3f};

void draw_square(int x, int y, const float color[3])
{
    glColor3fv(color); // set the color for square
    glBegin(GL_QUADS); // draw a quadrilateral
    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear screen

    // draw chessboard
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            // alternate between light and dark squares
            if ((row + col) % 2 == 0)
                draw_square(col, row, lightSquare);
            else
                draw_square(col, row, darkSquare);
        }
    }

    glFlush(); // flush gl commands
    glutSwapBuffers(); // swap buffers for smooth rendering (double buffering)
}

void init(void)
{
    glMatrixMode(GL_PROJECTION); // set up projection matrix
    glLoadIdentity();
    gluOrtho2D(0, 8, 0, 8); // orthographic projection for an 8x8 grid
    glMatrixMode(GL_MODELVIEW); // switch back to model-view matrix
}

int main(int argc, char* argv[])
{
    // initialize GLUT for rendering the chessboard
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Chess Board Graphics Test");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
