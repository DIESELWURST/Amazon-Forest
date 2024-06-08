// game.cpp
#include "game.hpp"

Game::Game() : window(nullptr), renderer(nullptr), running(true), st_levla(0), st_Ognjev(1.0f) ,SCREEN_HEIGHT(720),SCREEN_WIDTH(1280) {}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Blaze Busters: Amazon Rescue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Error: Window creation failed\nSDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Error: Renderer creation failed\nSDL Error: " << SDL_GetError() << std::endl;
        return false;
    }
    menu.init(renderer,window,SCREEN_HEIGHT,SCREEN_WIDTH,st_levla,player);
    if(st_levla==0){
        return false;
    } else if (st_levla == 4) {
        ReplayGame();
        return false; // Exit after replaying the game
    }else if(st_levla == 5) { // Load game option
        if (LoadGame()==false) {
            std::cout << "Failed to load game state!" << std::endl;
            return false;
        }
    } else {
        std::ofstream datao("replay.bin",std::ios::binary); //* če ni replay ali reload mode na začetku izvajanja odpremo datoteko, da bo lahko izrisali samo premike iz nazadnje igre
        datao.close();
        lvl.fillLevel(st_levla);
        vectBar.resize(lvl.getBar());
        Baraba Bar;
        Bar.fillBaraba(vectBar);
        vectOg.resize(lvl.getOg());
        Ogenj Og;
        Og.fillOgenj(vectOg,SCREEN_HEIGHT,SCREEN_WIDTH);
        vectStaro.resize(lvl.getStaro());
        Staroselci Staro;
        Staro.fillStaro(vectStaro);
        vectDrev.resize(9);
        Drevo Drev;
        Drev.fillDrev(vectDrev);
    }

    return true;
}

void Game::Run() {
    std::ofstream datao("replay.bin", std::ios::binary | std::ios::out | std::ios::app);
    if (!datao.is_open()) {
        std::cout << "Failed to open replay file for writing!" << std::endl;
        return;
    }

    while (running) {
    
        HandleEvents();
        Update();
        Render();
        datao.write((char*)&player, sizeof(player));

        if (st_Ognjev * 80 * 100 > 1280 * 720 * 0.7) {
            std::cout << "Skoraj! Zgleda kot da ti primanjkuje borbenega duha." << std::endl;
            break;
        }

        st_Ognjev >= vectOg.size() ? st_Ognjev = vectOg.size() : st_Ognjev++;
    }
    datao.close();
    updateLeaderboard();
    displayLeaderboard();
}

void Game::SaveGame() {
    std::ofstream saveFile("savegame.bin", std::ios::binary | std::ios::out);
    if (!saveFile.is_open()) {
        std::cout << "Failed to open save file for writing!" << std::endl;
        return;
    }

    saveFile.write((char*)&player, sizeof(player));
    size_t size = vectBar.size();
    saveFile.write((char*)&size, sizeof(size));
    saveFile.write((char*)vectBar.data(), size * sizeof(Baraba));

    size = vectStaro.size();
    saveFile.write((char*)&size, sizeof(size));
    saveFile.write((char*)vectStaro.data(), size * sizeof(Staroselci));

    size = vectOg.size();
    saveFile.write((char*)&size, sizeof(size));
    saveFile.write((char*)vectOg.data(), size * sizeof(Ogenj));

    size = vectDrev.size();
    saveFile.write((char*)&size, sizeof(size));
    saveFile.write((char*)vectDrev.data(), size * sizeof(Drevo));

    saveFile.write((char*)&st_levla, sizeof(st_levla));
    saveFile.write((char*)&st_Ognjev, sizeof(st_Ognjev));
    Uint32 cas_o = lvl.getCas();
    saveFile.write((char*)&cas_o, sizeof(cas_o));

    saveFile.close();
}

bool Game::LoadGame() {
    std::ifstream loadFile("savegame.bin", std::ios::binary | std::ios::in);
    if (!loadFile.is_open()) {
        std::cout << "Failed to open save file for reading!" << std::endl;
        return false;
    }

    loadFile.read((char*)&player, sizeof(player));
    size_t size;

    loadFile.read((char*)&size, sizeof(size));//*prebere 1.size,se nato pomakne na 2.ga
    vectBar.resize(size);
    loadFile.read((char*)vectBar.data(), size * sizeof(Baraba));//* .data() vrne prvi pointer vektorja , & se odmakne ker data() retruna pointer in ze pove kam rabmo shrant stvari

    loadFile.read((char*)&size, sizeof(size));//* -||-
    vectStaro.resize(size);
    loadFile.read((char*)vectStaro.data(), size * sizeof(Staroselci));

    loadFile.read((char*)&size, sizeof(size));
    vectOg.resize(size);
    loadFile.read((char*)vectOg.data(), size * sizeof(Ogenj));

    loadFile.read((char*)&size, sizeof(size));
    vectDrev.resize(size);
    loadFile.read((char*)vectDrev.data(), size * sizeof(Drevo));

    loadFile.read((char*)&st_levla, sizeof(st_levla));
    loadFile.read((char*)&st_Ognjev, sizeof(st_Ognjev));
    Uint32 cas_o;
    loadFile.read((char*)&cas_o, sizeof(cas_o));
    lvl.setCas(cas_o);
    loadFile.close();
    return true;
}

void Game::HandleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    SaveGame();
                    running = false;
                } else if (event.key.keysym.sym == SDLK_e) {
                    float distance=0;
                    for (int i = 0; i < vectDrev.size(); ++i) {//* regrow
                        distance = std::sqrt(std::pow(player.getX() - vectDrev[i].getX(), 2) + std::pow(player.getY() - vectDrev[i].getY(), 2));
                        if (distance < player.getRadius()) {
                            vectDrev[i].je_posekan = false;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }

}


void Game::Update() {
    if (st_levla < 4) {
        Update_Mobs(vectBar, player, vectStaro, vectOg, vectDrev, st_levla,lvl.getCas(),SCREEN_HEIGHT,SCREEN_WIDTH);
    }
}

void Game::Render() {
    if (st_levla < 4) {
        Render_Mobs(vectBar, player, vectStaro, vectOg, st_Ognjev, vectDrev, st_levla, renderer,SCREEN_HEIGHT,SCREEN_WIDTH);
    } else {
        Render_Mobs(vectBar, player, vectStaro, vectOg, st_Ognjev, vectDrev, st_levla, renderer,SCREEN_HEIGHT,SCREEN_WIDTH);
    }
}

void Game::ReplayGame() {
    std::ifstream replayFile("replay.bin", std::ios::binary | std::ios::in);
    if (!replayFile.is_open()) {
        std::cout << "Failed to open replay file for reading!" << std::endl;
        return;
    }
    Back back;
    Player replayPlayer;
    while (replayFile.read((char*)&replayPlayer, sizeof(replayPlayer))) {
        back.Render(renderer,SCREEN_HEIGHT,SCREEN_WIDTH);
        replayPlayer.Render(renderer);
        SDL_Delay(100); // Delay to simulate real-time replay
    }
    replayFile.close();
}

void Game::updateLeaderboard() {
    Player p;
    bool inserted = false;
    std::ofstream datao("copy.bin", std::ios::binary);
    std::ifstream datai("leaderboard.bin", std::ios::binary);
    
    if (!datai.is_open() || !datao.is_open()) {
        std::cout << "Error opening leaderboard file!" << std::endl;
        return;
    }

    while (datai.read((char*)&p, sizeof(p))) {
        if (player.getTocke() > p.getTocke() && !inserted) {
            datao.write((char*)&player, sizeof(player));
            inserted = true;
        }
        datao.write((char*)&p, sizeof(p));
    }

    //* v primeru če je datoteka prazna samo vpišemo run, ki se je glihkar zaključil
    if (!inserted) {
        datao.write((char*)&player, sizeof(player));
    }

    datai.close();
    datao.close();

    //* zdaj mamo urejeno datoteko z razredi tipa Player in spodaj samo še pustimo 5 najboljših runnov v datoteki
    std::vector<Player> leaderboard;
    std::ifstream copyi("copy.bin", std::ios::binary);
    std::ofstream leaderboardo("leaderboard.bin", std::ios::binary | std::ios::trunc);
    
    if (!copyi.is_open() || !leaderboardo.is_open()) {
        std::cout << "Error opening temporary leaderboard file!" << std::endl;
        return;
    }

    while (copyi.read((char*)&p, sizeof(p))) {
        leaderboard.push_back(p);
    }
    copyi.close();

    if (leaderboard.size() > 5) {
        leaderboard.resize(5);
    }

    for (std::vector<Player>::iterator it = leaderboard.begin(); it != leaderboard.end(); ++it) {
        leaderboardo.write((char*)&(*it), sizeof(Player));
    }

    leaderboardo.close();
    remove("copy.bin"); //* izbiršemo tmp file
}



void Game::displayLeaderboard() {
    SDL_Surface *leadSurface = IMG_Load("assets/leaderboard.png");
    if (!leadSurface) {
        printf("Error: Failed to load image\nSDL_Image Error: '%s'\n", IMG_GetError());
        return; // Dodana vrnjena vrednost v primeru napake pri nalaganju slike
    }

    // Ustvarjanje teksture menija
    SDL_Texture *leadTexture = SDL_CreateTextureFromSurface(renderer, leadSurface);
    if (!leadTexture) {
        printf("Error: Failed to create texture\n");
        SDL_FreeSurface(leadSurface);
        return; // Dodana vrnjena vrednost v primeru napake pri ustvarjanju teksture
    }

    // Read the top 5 entries from the leaderboard.bin
    std::ifstream leaderboardFile("leaderboard.bin", std::ios::binary);
    if (!leaderboardFile.is_open()) {
        std::cout << "Failed to open leaderboard file!" << std::endl;
        SDL_DestroyTexture(leadTexture);
        return;
    }

    std::vector<Player> leaderboard;
    Player p;
    while (leaderboardFile.read((char*)&p, sizeof(p)) && leaderboard.size() < 5) {
        leaderboard.push_back(p);
    }
    leaderboardFile.close();

    // Render the background
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, leadTexture, NULL, NULL);

    // Set up TTF for text rendering
    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(leadTexture);
        return;
    }

    TTF_Font* font = TTF_OpenFont("assets/font/Karma Future.otf", 24);
    if (!font) {
        std::cout << "Failed to load font: " << TTF_GetError() << std::endl;
        SDL_DestroyTexture(leadTexture);
        TTF_Quit();
        return;
    }

    SDL_Color color = {243, 198, 89, 255}; // White color for text

    // Render the leaderboard text
    int y_offset = 50;
    for (std::vector<Player>::iterator it = leaderboard.begin(); it != leaderboard.end(); ++it) {
        std::string text = std::to_string(std::distance(leaderboard.begin(), it) + 1) + ". " + it->getIme() + " - " + std::to_string(it->getTocke()) + " points";
        
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
        if (!textSurface) {
            std::cout << "Failed to create text surface: " << TTF_GetError() << std::endl;
            continue;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            std::cout << "Failed to create text texture: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            continue;
        }

        SDL_Rect textRect = {300, y_offset+250, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);

        y_offset += textSurface->h + 10; // Adjust spacing between lines
    }

    // Clean up
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_RenderPresent(renderer);

    // Wait for a few seconds before closing the leaderboard display
    SDL_Delay(5000);

    SDL_DestroyTexture(leadTexture);
}


