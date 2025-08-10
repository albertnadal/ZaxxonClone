#include <iostream>
#include <algorithm>
#include <thread>
#include <bitset>
#include <raylib/raylib.h>
#include <defines.h>
#include <entity_data_manager.h>
#include <game_manager.h>
#include <utils.h>
#include <main_menu_screen.cpp>

constexpr float SCR_WIDTH = 224.0f;
constexpr float SCR_HEIGHT = 256.0f;
constexpr uint32_t MAX_OBJECTS = 1000;

std::chrono::duration<float> computingTimePerUpdate;
uint8_t pressedKeys = Z_KEY_NONE;
bool exitGame = false;
bool isGameFinished = false;
int highScore = 0;
int lifeCounter = 3;
float logoTransparency = 0;
GameScreenType currentGameScreen;
EntityDataManager *entityTextureManager;
GameManager *gameManager;
int gameLoopFrequency = MILLISECONDS_PER_TICK;
bool paused = false;
char textBuffer[128]; // TODO: Must be eliminated in the future. Its used only for debug purposes.

inline void drawBoundaries(const ProjectedBoundaries &boundaries, Color color) {
        DrawLineV(boundaries.a, boundaries.b, color);
        DrawLineV(boundaries.b, boundaries.c, color);
        DrawLineV(boundaries.c, boundaries.d, color);
        DrawLineV(boundaries.d, boundaries.a, color);
        DrawLineV(boundaries.e, boundaries.f, color);
        DrawLineV(boundaries.f, boundaries.g, color);
        DrawLineV(boundaries.g, boundaries.h, color);
        DrawLineV(boundaries.h, boundaries.e, color);
        DrawLineV(boundaries.a, boundaries.e, color);
        DrawLineV(boundaries.b, boundaries.f, color);
        DrawLineV(boundaries.c, boundaries.g, color);
        DrawLineV(boundaries.d, boundaries.h, color);
}

inline void processKeyboardInput() {
        if (IsKeyPressed(KEY_RIGHT) || IsKeyReleased(KEY_RIGHT)) pressedKeys ^= Z_KEY_RIGHT;
        if (IsKeyPressed(KEY_LEFT) || IsKeyReleased(KEY_LEFT)) pressedKeys ^= Z_KEY_LEFT;
        if (IsKeyPressed(KEY_UP) || IsKeyReleased(KEY_UP)) pressedKeys ^= Z_KEY_UP;
        if (IsKeyPressed(KEY_DOWN) || IsKeyReleased(KEY_DOWN)) pressedKeys ^= Z_KEY_DOWN;
        if (IsKeyPressed(KEY_SPACE) || IsKeyReleased(KEY_SPACE)) pressedKeys ^= Z_KEY_SPACE;
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyReleased(KEY_ESCAPE)) pressedKeys ^= Z_KEY_ESCAPE;

        if (DEBUG) {
                if (IsKeyPressed(KEY_P)) paused = !paused;
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

        // Camera configuration
        Camera2D gameCamera;
        gameCamera.target = (Vector2){ 0, 0 };
        gameCamera.offset = (Vector2){ 0, 0 };
        gameCamera.rotation = 0.0f;
        gameCamera.zoom = ZOOM;

        Camera2D staticCamera;
        staticCamera.target = (Vector2){ 0, 0 };
        staticCamera.offset = (Vector2){ 0, 0 };
        staticCamera.rotation = 0.0f;
        staticCamera.zoom = ZOOM;

        currentGameScreen = GameScreenType::MAIN_MENU;
        entityTextureManager = new EntityDataManager();
        SpriteRectBuffer *spriteRectBuffer = new SpriteRectBuffer(MAX_OBJECTS);
        gameManager = new GameManager(entityTextureManager, spriteRectBuffer, MAX_OBJECTS);

        // Load texture atlas into GPU memory
        Texture2D textureAtlas = entityTextureManager->LoadTextureAtlas();

        // Load level
        LevelInfo levelInfo = gameManager->LoadLevel();

        UpdateInfo info;

        while (!WindowShouldClose() && !exitGame)
        {
                if (currentGameScreen == GameScreenType::GAME_PLAY) {
                        processKeyboardInput();

                        auto t0 = std::chrono::high_resolution_clock::now();
                        if (!paused) {
                                info = gameManager->Update(pressedKeys);
                                isGameFinished = info.gameFinished;

                                // Update game camera position
                                gameCamera.offset = info.cameraPosition.GetProjectedCoordinate();
                        }

                        BeginDrawing();
                                ClearBackground(BLACK);
                                BeginMode2D(gameCamera);
                                        // Draw game background
                                        DrawTextureRec(levelInfo.bgTexture, levelInfo.bgSource, levelInfo.bgPosition.GetProjectedCoordinate(), WHITE);

                                        // Draw game objects
                                        for(int i=0; i<spriteRectBuffer->bufferLength; i++) {
                                                auto position = spriteRectBuffer->buffer[i].position;
                                                auto source = spriteRectBuffer->buffer[i].source;
                                                auto tint = spriteRectBuffer->buffer[i].tint;
                                                DrawTextureRec(textureAtlas, source, position, tint);
                                                if (DEBUG) {
                                                        drawBoundaries(spriteRectBuffer->buffer[i].boundaries, (Color){ 0, 255, 68, 255 });
                                                }
                                        }
                                EndMode2D();

                                BeginMode2D(staticCamera);
                                        DrawTextureRec(textureAtlas, {224,238,75,20}, {145,232}, WHITE); // Fuel bar
                                        DrawTextureRec(textureAtlas, {299,238,24,10}, {187,214}, WHITE); // Life indicator
                                        Utils::renderNumberAtPosition(textureAtlas, lifeCounter, 1, 212, 216, false, WHITE); // Life counter
                                EndMode2D();

                                if (DEBUG) {
                                        DrawFPS(16, 16);
                                        Vector3 coord = info.shadowPosition.GetCoordinates();
                                        snprintf(textBuffer, sizeof(textBuffer), "X: %.2f, Y: %d, Z: %.2f", coord.x, GROUND_LEVEL_Y, coord.z); // TODO: To be deleted in the future.
                                        DrawText(textBuffer, 16, 50, 20, WHITE);
                                }
                        EndDrawing();

                        auto t1 = std::chrono::high_resolution_clock::now();
                        computingTimePerUpdate = t1 - t0;
                        std::this_thread::sleep_for(std::chrono::milliseconds(gameLoopFrequency) - computingTimePerUpdate);
                } else if (currentGameScreen == GameScreenType::MAIN_MENU) {
                        if (logoTransparency < 255.0f) {
                                logoTransparency = std::min(255.0f, logoTransparency + (MILLISECONDS_PER_TICK * 2.5f) / 16.0f);
                        }

                        renderMainMenuScreen(textureAtlas, staticCamera, highScore, logoTransparency);

                        if (IsKeyPressed(KEY_ESCAPE)) {
                                exitGame = true;
                        } else if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                                isGameFinished = false;
                                currentGameScreen = GameScreenType::GAME_PLAY;
                                pressedKeys = Z_KEY_NONE;
                                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        }
                }
        }

        exitGame = true;

        delete entityTextureManager;
        delete gameManager;
        delete spriteRectBuffer;

        UnloadTexture(textureAtlas);
        CloseWindow();

        return 0;
}
