#include "menu.hpp"



void Menu::init(SDL_Renderer * globalRenderer,SDL_Window * window,int & SCREEN_HEIGHT,int & SCREEN_WIDTH,int & st_levla, Player & player) {
    //* koda za vnos imena in velikosti okna
    SDL_Surface *ignSurface = IMG_Load("assets/ign.png");
    if (!ignSurface) {
        printf("Error: Failed to load image\nSDL_Image Error: '%s'\n", IMG_GetError());
        return; // Dodana vrnjena vrednost v primeru napake pri nalaganju slike
    }

    // Ustvarjanje teksture menija
    SDL_Texture *ignTexture = SDL_CreateTextureFromSurface(globalRenderer, ignSurface);
    if (!ignTexture) {
        printf("Error: Failed to create texture\n");
        SDL_FreeSurface(ignSurface);
        return; // Dodana vrnjena vrednost v primeru napake pri ustvarjanju teksture
    }

    if (TTF_Init() == -1) {
        printf("Error: Failed to initialize TTF\nSDL_ttf Error: '%s'\n", TTF_GetError());
        return;
    }

    TTF_Font* font = TTF_OpenFont("assets/font/Karma Future.otf", 24); 
    if (!font) {
        printf("Error: Failed to load font\nSDL_ttf Error: '%s'\n", TTF_GetError());
        return;
    }

    SDL_Color textColor = {243, 198, 89, 255};
    SDL_Event event;
    std::string playerName;
    std::string resolution=std::to_string(SCREEN_HEIGHT)+"x"+std::to_string(SCREEN_WIDTH);
    std::string fontString;
    SDL_StartTextInput(); // Start text input mode
    bool editingName=false;
    bool editingResolution=false;
    bool nameEntered =false;
    bool resolutionEntered=false;
    int prevHeight=SCREEN_HEIGHT;
    int prevWidth=SCREEN_WIDTH;
    // Name input loop
    while (nameEntered==false || resolutionEntered==false) {
        playerName=player.getIme();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_StopTextInput();
                TTF_CloseFont(font);
                TTF_Quit();
                return;
            } else if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym==SDLK_PERIOD){  // gumb za piko
                    editingName=true;
                } else if(event.key.keysym.sym==SDLK_COMMA){ // vejica
                    editingResolution=true;
                } else {
                    if(editingName==true){
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            nameEntered=true;
                            editingName=false;
                        } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                            playerName.pop_back();
                            if (playerName.empty()) {
                                playerName.append(" ");
                            }
                            player.setIme(playerName.c_str());
                        } else if (event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) {
                            playerName += (char)event.key.keysym.sym;
                            player.setIme(playerName.c_str());
                        } else if (event.key.keysym.sym == SDLK_SPACE){
                            playerName.append(" ");
                            player.setIme(playerName.c_str());
                        } else {

                        }
                    } else if (editingResolution){
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            resolutionEntered=true;
                            editingResolution=false;
                            break;
                        } else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                            resolution.pop_back();
                            if (resolution.empty()) {
                                resolution.append(" ");
                            }
                        } else if (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_z){
                            resolution+=(char)event.key.keysym.sym;
                        } else {

                        }
                    }
                }
            }
            

        if (std::string::npos == resolution.find('x')) {
            SCREEN_WIDTH = 10;
            if (resolution[0]=='\0'){
            SCREEN_HEIGHT=10;
            }
        } else if (resolution[resolution.find('x')+1]=='\0'){
            SCREEN_WIDTH=10;
        } else {
            SCREEN_HEIGHT = std::stoi(resolution.substr(0, resolution.find('x')));
            SCREEN_WIDTH = std::stoi(resolution.substr(resolution.find('x') + 1));
        }

        heightMod=SCREEN_HEIGHT/prevHeight;
        widthMod=SCREEN_WIDTH/prevWidth;
        prevHeight=SCREEN_HEIGHT;
        prevWidth=SCREEN_WIDTH;
        //* Pobrišemo ekran
        SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
        SDL_RenderClear(globalRenderer);
        //* Prikaz imena
        SDL_Surface* imeSurface = TTF_RenderText_Solid(font, player.getIme(), textColor);
        SDL_Texture* imeTexture = SDL_CreateTextureFromSurface(globalRenderer, imeSurface);
        int imeWidth = imeSurface->w;
        int imeHeight = imeSurface->h;
        SDL_FreeSurface(imeSurface);
        //*prikaz velikosti okna
        SDL_Surface* resSurface = TTF_RenderText_Solid(font, resolution.c_str(), textColor);
        SDL_Texture* resTexture = SDL_CreateTextureFromSurface(globalRenderer, resSurface);
        int resWidth = resSurface->w;
        int resHeight = resSurface->h;
        SDL_FreeSurface(resSurface);
        SDL_Rect imeDst = {260, 225, imeWidth, imeHeight};
        SDL_Rect ignDst = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        SDL_Rect resDst = {550,325,resWidth,resHeight};
        SDL_RenderCopy(globalRenderer, ignTexture, NULL, &ignDst);
        SDL_RenderCopy(globalRenderer, imeTexture, NULL, &imeDst);
        SDL_RenderCopy(globalRenderer, resTexture, NULL, &resDst);
        SDL_DestroyTexture(imeTexture);
        SDL_DestroyTexture(resTexture);
        //*Spremenimo velikost okna
        SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
        //*Updatamo renderer
        SDL_RenderPresent(globalRenderer);
    }
}
SDL_StopTextInput(); // Stop text input mode
TTF_CloseFont(font);
TTF_Quit();


    

 //*koda za levle
    SDL_Surface *menuSurface = IMG_Load("assets/menu.png");
    if (!menuSurface) {
        printf("Error: Failed to load image\nSDL_Image Error: '%s'\n", IMG_GetError());
        return; 
    }

    // Ustvarjanje teksture menija za levle
    SDL_Texture *menuTexture = SDL_CreateTextureFromSurface(globalRenderer, menuSurface);
    if (!menuTexture) {
        printf("Error: Failed to create texture\n");
        SDL_FreeSurface(menuSurface);
        return; 
    }

    // Ustvarjanje pravokotnika za renderiranje menija za levle
    SDL_Rect menuDst = { 
        .x = 0,
        .y = 0, 
        .w = SCREEN_WIDTH, 
        .h = SCREEN_HEIGHT
        };

    // Prikaz slike menija na zaslonu
    SDL_RenderCopy(globalRenderer, menuTexture, NULL, &menuDst);
    SDL_RenderPresent(globalRenderer);

    // Sprostitev uporabljenih virov
    SDL_FreeSurface(menuSurface);
    SDL_DestroyTexture(menuTexture);
    // Zanka za čakanje na pritisk tipke

    SDL_Event levels;
    while (true) {
    if (SDL_PollEvent(&levels)) {
        if (levels.type == SDL_KEYDOWN) {
            switch (levels.key.keysym.scancode) {
                case SDL_SCANCODE_1:
                    st_levla = 1;
                    break;
                case SDL_SCANCODE_2:
                    st_levla = 2;
                    break;
                case SDL_SCANCODE_3:
                    st_levla = 3;
                    break;
                case SDL_SCANCODE_4:
                    st_levla = 4;
                    break;
                case SDL_SCANCODE_5:
                    st_levla = 5;
                    break;
                case SDL_SCANCODE_ESCAPE:
                    st_levla=0;
                    break;
                default:
                    continue;//* to samo pomen da bo slo direktno v neslednjo iteracijo while loopa ce nepo uporabnik vpis 1-5 
            }
            
            break; // Exit the loop when a key is pressed
        }
    }
    SDL_Delay(100); // Added delay to reduce processor load
    }
}