#include "player.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstring>

Player::Player() {
    x = 500;
    y = 500;
    radius = 50;
    tocke = 15;
    Prekoracen_cas = false;
    setIme("Nameless - press Enter to save the name (press . to start editing)");
}

bool Player::Borders(int minX, int maxX, int minY, int maxY) {
    return Mobs::Borders(minX, maxX, minY, maxY);
}

void Player::Update(int SCREEN_HEIGHT, int SCREEN_WIDTH, Uint32 Cas_o, int st_levla) {
    Uint32 now = SDL_GetTicks();
    if (!Prekoracen_cas && now > Cas_o) {
        tocke -= 5 + (3 * (st_levla - 1)); // Higher level, higher penalty
        Prekoracen_cas = true;
    }

    const int movementSpeed = 25;
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL); // Read the state of the keyboard
    if (currentKeyStates[SDL_SCANCODE_W])
        y -= movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_A])
        x -= movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_S])
        y += movementSpeed;
    if (currentKeyStates[SDL_SCANCODE_D])
        x += movementSpeed;
    Borders(0, SCREEN_WIDTH - 50, 0, SCREEN_HEIGHT - 50);
}

void Player::Render(SDL_Renderer* globalRenderer) {
    SDL_Surface* mcSurface = IMG_Load("assets/player_front.png");
    if (!mcSurface) {
        printf("Error: Failed to load player image\nSDL_Image Error: '%s'\n", IMG_GetError());
    }

    SDL_Texture* mc = SDL_CreateTextureFromSurface(globalRenderer, mcSurface);
    SDL_FreeSurface(mcSurface);
    if (!mc) {
        printf("Error: Failed to create texture\n");
    }
    SDL_Rect mcDst = {
        .x = x, // X position
        .y = y, // Y position
        .w = 50, // Width
        .h = 50  // Height
    };
    SDL_RenderCopy(globalRenderer, mc, NULL, &mcDst);
    SDL_RenderPresent(globalRenderer);
    SDL_DestroyTexture(mc);
}

void Player::setIme(const char* newName) {
    strncpy(ime, newName, sizeof(ime) - 1); // Use strncpy for safety
    ime[sizeof(ime) - 1] = '\0'; // Ensure null-termination
}

void Player::addTocke(int addedPoints){
    tocke+=addedPoints;
}