/*******************************************************************************************
*
*   raylib [core] example - Basic 3d example
*
*   Welcome to raylib!
*
*   To compile example, just press F5.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   
*
********************************************************************************************/

#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = { 0 };
Vector3 cubePosition = { 0 };
Vector2 ballPosition;
Vector2 ballSpeed;

Vector2 Player1Position;
Vector2 Player1Size;
Vector2 Player2Position;
Vector2 Player2Size;

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib pong");
    InitAudioDevice();


    
    //Ball variables
    ballPosition.x = 400;
    ballPosition.y = 225;
    ballSpeed.x = 1;
    ballSpeed.y = 1;

   int ballRadius = 20;
    ballPosition.x = 400;
    ballPosition.y = 225;
    
    //Player variables
    Vector2 PlayerSize = { 10, 70 };

    Player1Position.x = screenWidth - 50;
    Player1Position.y = 225;
    bool canP1MoveUp = true;
    bool canP1MoveDown = true;
    int pointsP1 = 0;
    bool winP1 = false;

    Player2Position.x = 50;
    Player2Position.y = 225;
    bool canP2MoveUp = true;
    bool canP2MoveDown = true;
    int pointsP2 = 0;
    bool winP2 = false;

    //Other Variables
    int framesCounter = 0;
    bool end = false;
    bool pause = false;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        //Check if the game is paused
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        //Player Movement & Limits
        if(canP1MoveUp){ if (IsKeyDown(KEY_W)) Player1Position.y -= 2.0f; }
        if(canP1MoveDown){ if (IsKeyDown(KEY_S)) Player1Position.y += 2.0f; }
        if(canP2MoveUp){ if (IsKeyDown(KEY_UP)) Player2Position.y -= 2.0f; }
        if(canP2MoveDown){ if (IsKeyDown(KEY_DOWN)) Player2Position.y += 2.0f; }
        
        if (Player1Position.x < 0) Player1Position.x = 0;
        else if (Player1Position.x >= GetScreenWidth()) Player1Position.x = GetScreenWidth() - 1;
        if (Player1Position.y < 0) Player1Position.y = 0;
        else if (Player1Position.y + PlayerSize.y >= GetScreenHeight()) Player1Position.y = GetScreenHeight() - PlayerSize.y;

        if (Player2Position.x < 0) Player2Position.x = 0;
        else if (Player2Position.x >= GetScreenWidth()) Player2Position.x = GetScreenWidth() - 1;
        if (Player2Position.y < 0) Player2Position.y = 0;
        else if (Player2Position.y + PlayerSize.y >= GetScreenHeight()) Player2Position.y = GetScreenHeight() - PlayerSize.y;

        if (!pause && !end)
        {
            if ((Player1Position.y >= (GetScreenHeight() - PlayerSize.y))) canP1MoveDown = false;
            if (Player1Position.y <= 0) canP1MoveUp = false;
           

            if ((Player2Position.y >= (GetScreenHeight() - PlayerSize.y))) canP2MoveDown = false;
            if (Player2Position.y <= 0) canP2MoveUp = false;
           

            //Ball Movement
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;
            if (ballSpeed.x >= 13.0f) ballSpeed.x *= 0.7f;
            if (ballSpeed.y >= 13.0f) ballSpeed.y *= 0.7f;
        }
        else framesCounter++;

        //Player Collision
        if ((ballPosition.x >= Player1Position.x - ballRadius) && (ballPosition.y >= Player1Position.y) && (ballPosition.y <= Player1Position.y + 70)) 
        {
            ballSpeed.x *= -1.15f;
            ballPosition.x = Player1Position.x - ballRadius + 1;
        }
        if ((ballPosition.x <= Player2Position.x + ballRadius) && (ballPosition.y >= Player2Position.y) && (ballPosition.y <= Player2Position.y + 70)) 
        {
            ballSpeed.x *= -1.15f;
            ballPosition.x = Player2Position.x + ballRadius - 1;
        }

        //Wall Collision
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.x *= -1.05f;
        if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) ballSpeed.y *= -1.05f;

        //Point Count
        if ((ballPosition.x <= ballRadius)) {
            pointsP1++;
            ballPosition.x = 400;
            ballPosition.y = 225;
            ballSpeed.x = -3.0f;
            ballSpeed.y = 2.0f;
        }
        if ((ballPosition.x >= (GetScreenWidth() - ballRadius))) 
        {
            pointsP2++;
            ballPosition.x = 400;
            ballPosition.y = 225;
            ballSpeed.x = 3.0f;
            ballSpeed.y = 2.0f;
        }

        //Check for win
        if (pointsP1 == 5) winP1 = true;
        if (pointsP2 == 5) winP2 = true;
        if (winP1 || winP2) end = true;
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            DrawRectangleV(Player1Position, PlayerSize, BLUE);
            DrawRectangleV(Player2Position, PlayerSize, GREEN);
            DrawCircleV(ballPosition, (float)ballRadius, RED);
            DrawText("Get 05 points to win!", 300, 15, 20, RAYWHITE);
            DrawText("Press Space to Pause.", 315, 40, 16, GRAY);
            if (pause && ((framesCounter/30)%2)) DrawText("PAUSED", 300, 200, 50, LIGHTGRAY);
            if (winP1) {
                DrawText("Player 1 Wins!!", 290, 170, 30, BLUE);
                if (end && ((framesCounter/30)%2)) DrawText("Press ESC to exit.", 310, 255, 20, GRAY);
            }
            if (winP2) {
                DrawText("Player 2 Wins!!", 290, 170, 30, GREEN);
                if (end && ((framesCounter/30)%2)) DrawText("Press ESC to exit.", 310, 255, 20, GRAY);
            }
            DrawText(TextFormat("Points P1: %02i", pointsP1), 640, 20, 18, RAYWHITE);
            DrawText(TextFormat("Points P2: %02i", pointsP2), 65, 20, 18, RAYWHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
