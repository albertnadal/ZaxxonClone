#include <iostream>
#include <thread>
#include <bitset>
#include <raylib/raylib.h>
#include <defines.h>
#include <entity_data_manager.h>
#include <game_manager.h>
#include <utils.h>

constexpr uint32_t SCR_WIDTH = 224;
constexpr uint32_t SCR_HEIGHT = 256;
constexpr uint32_t MAX_OBJECTS = 1000;

std::chrono::duration<float> computingTimePerUpdate;
uint8_t pressedKeys = Z_KEY_NONE;
bool exitGame = false;
bool isGameFinished = false;
EntityDataManager *entityTextureManager;
GameManager *gameManager;
int gameLoopFrequency = MILLISECONDS_PER_TICK;
bool paused = false;

inline void processKeyboardInput() {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyReleased(KEY_RIGHT)) pressedKeys ^= Z_KEY_RIGHT;
        if (IsKeyPressed(KEY_LEFT) || IsKeyReleased(KEY_LEFT)) pressedKeys ^= Z_KEY_LEFT;
        if (IsKeyPressed(KEY_UP) || IsKeyReleased(KEY_UP)) pressedKeys ^= Z_KEY_UP;
        if (IsKeyPressed(KEY_DOWN) || IsKeyReleased(KEY_DOWN)) pressedKeys ^= Z_KEY_DOWN;
        if (IsKeyPressed(KEY_SPACE) || IsKeyReleased(KEY_SPACE)) pressedKeys ^= Z_KEY_SPACE;
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyReleased(KEY_ESCAPE)) pressedKeys ^= Z_KEY_ESCAPE;

        if (DEBUG) {
                if (IsKeyPressed(KEY_P)) gameLoopFrequency += 10;
                if (IsKeyPressed(KEY_O)) gameLoopFrequency -= 10;
                if (IsKeyPressed(KEY_M)) paused = !paused;
        }
}

int main()
{
        if(!DEBUG) {
                SetTraceLogLevel(LOG_NONE);
        }

        srand(static_cast<unsigned>(time(0))); // Initialize the random seed to avoid deterministic behaviours. Just for debug purposes.

        InitWindow(SCR_WIDTH * ZOOM, SCR_HEIGHT * ZOOM, WINDOW_TITLE);
        //SetExitKey(0); // Disable close the application when pressing Esc key.

        // Camera configuration for scene game play screen
        Camera2D gameCamera;
        gameCamera.target = (Vector2){ 0, 0 };
        gameCamera.offset = (Vector2){ 0, 0 };
        gameCamera.rotation = 0.0f;
        gameCamera.zoom = ZOOM;

        // Camera configuration for level background
        Camera2D backgroundCamera;
        backgroundCamera.target = (Vector2){ 0, 0 };
        backgroundCamera.offset = (Vector2){ 0, 0 };
        backgroundCamera.rotation = 0.0f;
        backgroundCamera.zoom = ZOOM;

        entityTextureManager = new EntityDataManager();
        SpriteRectDoubleBuffer *spriteRectDoubleBuffer = new SpriteRectDoubleBuffer(MAX_OBJECTS);
        gameManager = new GameManager(entityTextureManager, spriteRectDoubleBuffer, MAX_OBJECTS);

        // Load texture atlas into GPU memory
        Texture2D textureAtlas = entityTextureManager->LoadTextureAtlas();
        Texture2D levelBackground = entityTextureManager->LoadLevelBackground();

        // Load level from file
        gameManager->LoadLevel();

        UpdateInfo info;

        while (!WindowShouldClose() && !exitGame)
        {
                        processKeyboardInput();

                        auto t0 = std::chrono::high_resolution_clock::now();
                        info = gameManager->Update(pressedKeys);
                        isGameFinished = info.gameFinished;

                        BeginDrawing();
                                ClearBackground(BLACK);

                                BeginMode2D(backgroundCamera);
                                        DrawTextureRec(levelBackground, {0,0,1816,1008}, {50.0f,-805.0f}, WHITE);
                                EndMode2D();
                                BeginMode2D(gameCamera);
                                        for(int i=0; i<spriteRectDoubleBuffer->consumer_buffer_length; i++) {
                                                auto position = spriteRectDoubleBuffer->consumer_buffer[i].position;
                                                auto source = spriteRectDoubleBuffer->consumer_buffer[i].source;
                                                auto tint = spriteRectDoubleBuffer->consumer_buffer[i].tint;
                                                DrawTextureRec(textureAtlas, source, position, tint);
                                        }
                                EndMode2D();

                                if (DEBUG) {
                                        DrawFPS(16, 16);
                                }
                        EndDrawing();

                        auto t1 = std::chrono::high_resolution_clock::now();
                        computingTimePerUpdate = t1 - t0;
                        std::this_thread::sleep_for(std::chrono::milliseconds(gameLoopFrequency) - computingTimePerUpdate);
        }

        exitGame = true;

        delete entityTextureManager;
        delete gameManager;
        delete spriteRectDoubleBuffer;

        UnloadTexture(textureAtlas);
        CloseWindow();

        return 0;
}
