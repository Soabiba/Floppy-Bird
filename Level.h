#pragma once
#include <vector>

class Level
{
public:
    void init();
    void load_resources();
    void update();
    void draw();
    void close();

    int screenWidth = 600;
    int screenHeight = 700;

private:
    int score;
    int comboTimer;
    int combo;

    bool gameOver;
    bool mainScreen;

    struct ScoreDisplay
    {
        int value;
        Vector2 position;
        int lifetime;
        bool isDead;
    };

    std::vector<ScoreDisplay> scoreDisplays;

    struct Coin
    {
        Rectangle rec{ 0,0, 5,5 };;
        Vector2 velocity = { 0, 100 };
        bool isDead;
    };
    std::vector<Coin> coins;

    struct Enemy
    {
        Rectangle rec = { 0,0, 20,19 };
        Vector2 velocity = {};
        bool isDead;
    };
    std::vector<Enemy> enemies;

    struct Player
    {
        Rectangle rec = { 0,0, 45, 30 };
        int speed = 200;
        bool isDead;
    };
    Player player;

    // Textures
    //Texture2D Spaceship;
    

    //Sounds
   //Sound missileSound;

public:
    //Sound backgroundMusic;
};
