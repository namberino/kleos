#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "board.h"
#include "pieces.h"

int selected_square = -1;
bool white_turn = true;

GLuint textures[12]; // 6 pieces * 2 colors = 12 textures

const float light_square[3] = {1.0f, 1.0f, 0.9f};
const float dark_square[3] = {0.3f, 0.5f, 0.3f};

GLuint load_texture(const char* filename)
{
    // initialize SDL_image with support for png
    int flags = IMG_INIT_PNG;

    if (!(IMG_Init(flags) & flags))
    {
        printf("Failed to initialize SDL_image %s\n", IMG_GetError());
        return 0;
    }

    // load image with SDL2_image
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface)
    {
        printf("Failed to load texture: %s\n", IMG_GetError());
        return 0;
    }

    // blend alpha to enable transparent background
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // convert SDL surface to an OpenGL texture
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // determine image format (RGB or RGBA)
    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    // upload image data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    // set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // unbind the texture and free the surface
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_FreeSurface(surface);

    // quit SDL_image
    IMG_Quit();

    return texture_id;
}

void load_textures(void)
{
    textures[0] = load_texture("../textures/black-king.png");
    textures[1] = load_texture("../textures/black-queen.png");
    textures[2] = load_texture("../textures/black-rook.png");
    textures[3] = load_texture("../textures/black-bishop.png");
    textures[4] = load_texture("../textures/black-knight.png");
    textures[5] = load_texture("../textures/black-pawn.png");
    textures[6] = load_texture("../textures/white-king.png");
    textures[7] = load_texture("../textures/white-queen.png");
    textures[8] = load_texture("../textures/white-rook.png");
    textures[9] = load_texture("../textures/white-bishop.png");
    textures[10] = load_texture("../textures/white-knight.png");
    textures[11] = load_texture("../textures/white-pawn.png");
}

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

void draw_piece(int x, int y, wint_t piece)
{
    if (piece != EMPTY_SQUARE)
    {
        int texture_index = -1;

        switch (piece)
        {
            case BLACK_KING: texture_index = 0; break;
            case BLACK_QUEEN: texture_index = 1; break;
            case BLACK_ROOK: texture_index = 2; break;
            case BLACK_BISHOP: texture_index = 3; break;
            case BLACK_KNIGHT: texture_index = 4; break;
            case BLACK_PAWN: texture_index = 5; break;
            case WHITE_KING: texture_index = 6; break;
            case WHITE_QUEEN: texture_index = 7; break;
            case WHITE_ROOK: texture_index = 8; break;
            case WHITE_BISHOP: texture_index = 9; break;
            case WHITE_KNIGHT: texture_index = 10; break;
            case WHITE_PAWN: texture_index = 11; break;
            default: break;
        }

        if (texture_index != -1)
        {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures[texture_index]);

            glColor3f(1.0f, 1.0f, 1.0f); // reset color for texture rendering
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(x + 1, y);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(x + 1, y + 1);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y + 1);
            glEnd();

            glDisable(GL_TEXTURE_2D);
        }
    }
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear screen

    // draw chessboard
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int index = (7 - row) * 8 + col;

            // alternate between light and dark squares
            if ((row + col) % 2 == 0)
                draw_square(col, row, light_square);
            else
                draw_square(col, row, dark_square);

            draw_piece(col, row, board[index]);
        }
    }

    glFlush(); // flush gl commands
    glutSwapBuffers(); // swap buffers for smooth rendering (double buffering)
}

int get_square_from_mouse(int x, int y)
{
    int col = x / (600 / 8);
    int row = y / (600 / 8);
    return row * 8 + col;
}

void mouse_click(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        int square = get_square_from_mouse(x, y);
        
        if (selected_square == -1)
        {
            // select source square
            wint_t selected_piece = select_piece(square);

            if (selected_piece != EMPTY_SQUARE && ((selected_piece < BLACK_KING && white_turn) || (selected_piece >= BLACK_KING && !white_turn)))
            {
                selected_square = square;
                printf("Square: %d\n", square);
            }
            else
            {
                printf("Invalid piece selection\n");
            }
        }
        else
        {
            // select destination square
            if (move_piece(selected_square, square, white_turn) == 0)
                white_turn = !white_turn;

            selected_square = -1;
            glutPostRedisplay(); // refresh the display after a move
        }
    }
}

int main(int argc, char* argv[])
{
    initialize_board();

    // initialize GLUT for rendering the chessboard
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Chess Game");

    gluOrtho2D(0, 8, 0, 8); // orthographic projection for an 8x8 grid
    load_textures();

    glutDisplayFunc(display);
    glutMouseFunc(mouse_click);

    glutMainLoop();

    return 0;
}
