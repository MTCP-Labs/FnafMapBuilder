#include <raylib.h>
#include <string.h>

#define WIDTH 1920
#define HEIGHT 1080

void move_circle(int* center_x, int* center_y, float* radius) {
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { 
        *center_x = GetMouseX();
        *center_y = GetMouseY();    
    }

    DrawCircle(*center_x, *center_y, *radius, RED);
}

int main(void)
{
    InitWindow(WIDTH, HEIGHT, "MOVE CIRCLE");
    SetWindowState(FLAG_WINDOW_MAXIMIZED);
    SetTargetFPS(60);

    int center_x = WIDTH / 2, center_y = HEIGHT / 2;
    float radius = 50.0;

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawFPS(WIDTH - 6 * 12, 0);
            move_circle(&center_x, &center_y, &radius);        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}