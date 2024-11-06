#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "board.h"
#include "pieces.h"

int selected_square = -1;
bool white_turn = true;

SDL_Texture* textures[12]; // 6 pieces * 2 colors = 12 textures

const SDL_Color light_square = {255, 255, 230, 255}; // RGBA for light squares
const SDL_Color dark_square = {76, 128, 76, 255}; // RGBA for dark squares

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* filename)
{
    // initialize SDL_image with support for png
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
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

    // load texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    // quit SDL_image
    IMG_Quit();

    return texture;
}

void load_textures(SDL_Renderer* renderer)
{
    textures[0] = load_texture(renderer, "../textures/white-king.png");
    textures[1] = load_texture(renderer, "../textures/white-queen.png");
    textures[2] = load_texture(renderer, "../textures/white-rook.png");
    textures[3] = load_texture(renderer, "../textures/white-bishop.png");
    textures[4] = load_texture(renderer, "../textures/white-knight.png");
    textures[5] = load_texture(renderer, "../textures/white-pawn.png");
    textures[6] = load_texture(renderer, "../textures/black-king.png");
    textures[7] = load_texture(renderer, "../textures/black-queen.png");
    textures[8] = load_texture(renderer, "../textures/black-rook.png");
    textures[9] = load_texture(renderer, "../textures/black-bishop.png");
    textures[10] = load_texture(renderer, "../textures/black-knight.png");
    textures[11] = load_texture(renderer, "../textures/black-pawn.png");
}

void draw_square(SDL_Renderer* renderer, int x, int y, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {x * 75, y * 75, 75, 75}; // each square is 75x75
    SDL_RenderFillRect(renderer, &rect);
}

void draw_piece(SDL_Renderer* renderer, int x, int y, wint_t piece)
{
    if (piece != EMPTY_SQUARE)
    {
        int texture_index = -1;

        switch (piece)
        {
            case WHITE_KING: texture_index = 0; break;
            case WHITE_QUEEN: texture_index = 1; break;
            case WHITE_ROOK: texture_index = 2; break;
            case WHITE_BISHOP: texture_index = 3; break;
            case WHITE_KNIGHT: texture_index = 4; break;
            case WHITE_PAWN: texture_index = 5; break;
            case BLACK_KING: texture_index = 6; break;
            case BLACK_QUEEN: texture_index = 7; break;
            case BLACK_ROOK: texture_index = 8; break;
            case BLACK_BISHOP: texture_index = 9; break;
            case BLACK_KNIGHT: texture_index = 10; break;
            case BLACK_PAWN: texture_index = 11; break;
            default: break;
        }

        if (texture_index != -1)
        {
            SDL_Rect dst_rect = {x * 75, y * 75, 75, 75};
            SDL_RenderCopy(renderer, textures[texture_index], NULL, &dst_rect);
        }
    }
}

void render_board(SDL_Renderer* renderer)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            int index = row * 8 + col;
            SDL_Color color = ((row + col) % 2 == 0) ? light_square : dark_square;

            draw_square(renderer, col, row, color);
            draw_piece(renderer, col, row, board[index]);
        }
    }
}

int get_square_from_mouse(int x, int y)
{
    int col = x / 75;
    int row = y / 75;
    return row * 8 + col;
}

void handle_mouse_click(SDL_Renderer* renderer, int x, int y)
{
    int square = get_square_from_mouse(x, y);

    if (selected_square == -1)
    {
        wint_t selected_piece = select_piece(square);

        if (selected_piece != EMPTY_SQUARE && ((selected_piece < BLACK_KING && white_turn) || (selected_piece >= BLACK_KING && !white_turn)))
        {
            selected_square = square;
            printf("Selected square: %d\n", square);
        }
        else
        {
            printf("Invalid piece selection\n");
        }
    }
    else
    {
        if (move_piece(selected_square, square, white_turn) == 0)
            white_turn = !white_turn;
        selected_square = -1;

        SDL_RenderClear(renderer);
        render_board(renderer);
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char* argv[])
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return -1;
    }

    // create SDL window
    SDL_Window* window = SDL_CreateWindow("Kleos Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);
    if (!window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    // create SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return -1;
    }

    initialize_board();
    load_textures(renderer);

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) // handle quitting
                running = false;
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) // handle mouse click
                handle_mouse_click(renderer, event.button.x, event.button.y);
        }

        SDL_RenderClear(renderer);
        render_board(renderer);
        SDL_RenderPresent(renderer);
    }

    // clean up textures
    for (int i = 0; i < 12; i++)
    {
        if (textures[i])
            SDL_DestroyTexture(textures[i]);
    }

    // clean up renderer and window before quitting SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
