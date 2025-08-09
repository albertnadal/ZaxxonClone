#ifndef MAIN_MENU_SCREEN_CPP
#define MAIN_MENU_SCREEN_CPP

#include <raylib/raylib.h>
#include <thread>
#include <chrono>
#include <defines.h>
#include <utils.h>

static inline void renderMainMenuScreen(Texture2D &textureAtlas, Camera2D &staticCamera, int highScore, float logoTransparency) {
    std::chrono::duration<float> computingTimePerLoop;
    auto t0 = std::chrono::high_resolution_clock::now();

    BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(staticCamera);
                    DrawTextureRec(textureAtlas, {0,237,224,256}, {0,0}, WHITE); // Background image
                    DrawTextureRec(textureAtlas, {0,493,139,35}, {73,9}, { 255, 255, 255, static_cast<unsigned char>(logoTransparency) }); // Logo
                    std::cout << "CAST - logoTransparency: " << static_cast<unsigned char>(logoTransparency) << std::endl;

                    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t0.time_since_epoch()).count();
                    int centiseconds = ms % 1000;
                    if (centiseconds >= 0 && centiseconds <= 700) {
                        Utils::renderTextAtPosition(textureAtlas, "PRESS SPACE TO START", 34, 180, WHITE); // Press space to start
                    }

                    Utils::renderNumberAtPosition(textureAtlas, 1982, 4, 187, 245, false, WHITE); // 1982
                    Utils::renderTextAtPosition(textureAtlas, "SEGA", 150, 245, WHITE); // SEGA
                    DrawTextureRec(textureAtlas, {289,229,9,8}, {138, 245}, WHITE); // Copyright symbol
            EndMode2D();

    if (DEBUG) {
        DrawFPS(16, 16);
    }
    EndDrawing();

    auto t1 = std::chrono::high_resolution_clock::now();
    computingTimePerLoop = t1 - t0;
    std::this_thread::sleep_for(std::chrono::milliseconds(MILLISECONDS_PER_TICK) - computingTimePerLoop);
}

#endif