#include <vector>
#include <string>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

class Visualizer {
private:
    int screen_width, screen_height;
    bool initialized = false;
    Font Arial;
    std::vector<int> global_dp;
    std::string Description;
    struct {
        std::pair<int, int> i;
        std::pair<int, int> j;
    } printing_range; 
    struct {
        int i;
        int j;
    } range_length; 

    float box_size, box_dist, font_size;
    
    void DrawArrow(Vector2 start, Vector2 end, Color color) {
        DrawLineEx(start, end, 7.0f, color);
        float angle;
        if (end.y - start.y == 0) angle = 0;
        else if (end.x - start.x == 0) angle = 90;
        else angle = atan2f(end.y - start.y, end.x - start.x);
        float arrowSize = 100.0f;
        DrawTriangle(
            end,
            { end.x - arrowSize * cosf(angle - 0.5f), end.y + arrowSize * sinf(angle - 0.5f) },
            { end.x - arrowSize * cosf(angle + 0.5f), end.y - arrowSize * sinf(angle + 0.5f) },
            color
        );
    }

public:
    void init(const std::vector<int>& dp, std::pair<int, int> range) {
        SetTraceLogLevel(LOG_ERROR);
        if (initialized) return;
        printing_range.i = range;
        range_length.i = range.second - range.first;
        if (range_length.i > 15 || range_length.i <= 0 || dp.empty()) {
            std::cerr << "DP size overflow or invalid, Cant Visualize\n";
            return;
        }
        box_size = 120;
        box_dist = 30;
        font_size = 40;
        screen_width = 100 + (range_length.i * (box_size + box_dist)); 
        screen_height = 500;
        InitWindow(screen_width, screen_height, "Single Dimension DP Visualizer");
        SetTargetFPS(60); 
        Arial = {}; //LoadFontEx(RESOURCE_PATH "Arial.ttf", 64, NULL, 0);
        initialized = true;
    }
    void update(const std::vector<int>& dp, std::vector<int>& prev, std::vector<int>& cur) {
        if (!initialized) return;
        bool next_step = false;
        auto [start, stop] = printing_range.i;
        std::vector<float> pos_x(range_length.i);
        float pos_y = 200.0f;
        while (!WindowShouldClose() && !next_step) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            //Calculate position
            for (int i = 0; i < range_length.i; i++) {
                pos_x[i] = 75.0f + ((box_size + box_dist) * i);
            }
            //Draw Blue Box (Normal)
            for (int i = 0; i < range_length.i; i++) {
                auto true_i = i + start;
                Color color = { 170, 220, 255, 255 }; //Light Blue
                DrawRectangleRounded({pos_x[i], pos_y, box_size, box_size}, 0.2, 6, color);
                DrawRectangleRoundedLinesEx({pos_x[i], pos_y, box_size, box_size}, 0.2, 10, 3, DARKBLUE);
            }
            //Draw green box (current dp)
            for (auto true_i : cur){
                int i = true_i - start;
                if (i >= range_length.i || i < 0) continue; //Out of bound
                Color color = { 170, 255, 220, 255 }; //Light green
                DrawRectangleRounded({pos_x[i], pos_y, box_size, box_size}, 0.2, 6, color);
            }
            //Draw purple box (previos dp)
            for (auto true_i : prev){
                int i = true_i - start;
                if (i >= range_length.i || i < 0) continue; //Out of bound
                Color color = { 207, 159, 255, 255 }; //Light Violet
                DrawRectangleRounded({pos_x[i], pos_y, box_size, box_size}, 0.2, 6, color);
            }
            //Draw Text (dp value)
            for (int i = 0; i < range_length.i; i++) {
                int true_i = i + start;
                std::string val = std::to_string(dp[true_i]);
                int textWidth = MeasureText(val.c_str(), font_size);
                DrawTextEx(Arial, val.c_str(), {pos_x[i] + (box_size/2 - textWidth/2), pos_y + (box_size/3)}, font_size, 5, BLACK);
                DrawTextEx(Arial, TextFormat("%d", true_i), {pos_x[i] + box_size/2 - 10, pos_y - 30}, 30, 3, DARKGRAY);
            }
            //Draw Description
            if (!Description.empty()) {
                DrawTextEx(Arial, Description.c_str(), {75, (float)screen_height - 100}, 50, 5, DARKGRAY);
            }
            DrawTextEx(Arial, "Press SPACE for next step", {20, (float)screen_height - 30}, 20, 5, LIGHTGRAY);
            EndDrawing();
            if (IsKeyPressed(KEY_SPACE)) next_step = true;
        }
    }

    void init2D(const std::vector<std::vector<int>>& dp, std::pair<int, int> range_i, std::pair<int, int> range_j) {
        SetTraceLogLevel(LOG_ERROR);
        if (initialized) return;
        printing_range.i = range_i;
        printing_range.j = range_j;
        range_length.i = range_i.second - range_i.first;
        range_length.j = range_j.second - range_j.first;
        if (dp.empty() || dp.at(0).empty() || range_length.i > 15 || range_length.i <= 0 || range_length.j > 10 || range_length.j <= 0) {
            std::cerr << "DP size overflow or invalid, Cant Visualize\n";
            return;
        }
        box_size = 100;
        box_dist = 30;
        font_size = 40;
        screen_width = 150 + (range_length.j * (box_size + box_dist)); 
        screen_height = 200 + (range_length.i * (box_size + box_dist));
        InitWindow(screen_width, screen_height, "Double Dimension DP Visualizer");
        SetTargetFPS(60); 
        Arial = {};//LoadFontEx("./arial.ttf", 64, NULL, 0);
        initialized = true;
    }
    void update2D(const std::vector<std::vector<int>>& dp, std::vector<std::pair<int, int>>& prev, std::vector<std::pair<int, int>>& cur) {
        if (!initialized) return;
        bool next_step = false;
        auto [start_i, stop_i] = printing_range.i;
        auto [start_j, stop_j] = printing_range.j;
        std::vector<float> pos_x(range_length.j), pos_y(range_length.i);
        while (!WindowShouldClose() && !next_step) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            //Calculate Position
            for (int j = 0; j < range_length.j; j++) {
                pos_x[j] = 90.0f + ((box_size + box_dist) * j);
            }
            for (int i = 0; i < range_length.i; i++) {
                pos_y[i] = 75.0f + ((box_size + box_dist) * i);
            }
            //Draw Blue Box (Default)
            for (int i = 0; i < range_length.i; i++) {
                for (int j = 0; j < range_length.j; j++) {
                    int true_i = i + start_i;
                    int true_j = j + start_j;
                    Color color = { 170, 220, 255, 255 }; 
                    DrawRectangleRounded({pos_x[j], pos_y[i], box_size, box_size}, 0.2, 6, color);
                    DrawRectangleRoundedLinesEx({pos_x[j], pos_y[i], box_size, box_size}, 0.2, 10, 3, DARKBLUE);
                }
            }
            for (auto [true_i, true_j] : cur){
                int i = true_i - start_i;
                int j = true_j - start_j;
                if (i >= range_length.i || i < 0 || j >= range_length.j || j < 0) continue; //Out of bound
                Color color = { 170, 255, 220, 255 }; //Light green
                DrawRectangleRounded({pos_x[j], pos_y[i], box_size, box_size}, 0.2, 6, color);
            }
            for (auto [true_i, true_j] : prev){
                int i = true_i - start_i;
                int j = true_j - start_j;
                if (i >= range_length.i || i < 0 || j >= range_length.j || j < 0) continue; //Out of bound
                Color color = { 207, 159, 255, 255 }; //Light Violet
                DrawRectangleRounded({pos_x[j], pos_y[i], box_size, box_size}, 0.2, 6, color);
            }
            // Y axis label
            for (int i = 0; i < range_length.i; i++) {
                int true_i = i + start_i;
                DrawTextEx(Arial, TextFormat("%d", true_i), {30, pos_y[i] + box_size/2 - 10}, 30, 3, DARKGRAY);
            }
            // X axis label
            for (int j = 0; j < range_length.j; j++) {
                int true_j = j + start_j;
                DrawTextEx(Arial, TextFormat("%d", true_j), {pos_x[j] + box_size/2 - 10,  30}, 30, 3, DARKGRAY);
            }
            for (int i = 0; i < range_length.i; i++) {
                for (int j = 0; j < range_length.j; j++) {
                    int true_i = i + start_i;
                    int true_j = j + start_j;
                    std::string val = std::to_string(dp[true_i][true_j]);
                    int new_font_size = font_size - (3 * val.length());
                    int textWidth = MeasureText(val.c_str(), new_font_size);
                    DrawTextEx(Arial, val.c_str(), {pos_x[j] + (box_size/2 - textWidth/2), pos_y[i] + (box_size/3)}, new_font_size, 5, BLACK);
                }
            }
            //Draw Description
            if (!Description.empty()) {
                DrawTextEx(Arial, Description.c_str(), {75, (float)screen_height - 120}, 50, 5, DARKGRAY);
            }
            DrawTextEx(Arial, "Press SPACE for next step", {20, (float)screen_height - 30}, 20, 5, GRAY);
            EndDrawing();
            if (IsKeyPressed(KEY_SPACE)) next_step = true;
        }
    }
    template<typename... Args>
    void updateDescription(std::string str, Args... args){
        Description = TextFormat(str.c_str(), args...);
    }
    void stop() {
        if (initialized) {
            CloseWindow();
            UnloadFont(Arial);
            initialized = false;
        }
    }
};

Visualizer viz;
void init(std::vector<int>& dp, std::pair<int, int> range) { viz.init(dp, range); }
void Visualize(std::vector<int>& dp, std::vector<int> prev, std::vector<int> cur) { viz.update(dp, prev, cur); }

void init(std::vector<std::vector<int>>& dp, std::pair<int, int> range_i, std::pair<int, int> range_j) { viz.init2D(dp, range_i, range_j); }
void Visualize(std::vector<std::vector<int>>& dp, std::vector<std::pair<int, int>> prev, std::vector<std::pair<int, int>> cur) { viz.update2D(dp, prev, cur); }

template<typename... Args>
void Describe(std::string description, Args... args) { viz.updateDescription(description, args...); }
void stop() { viz.stop(); }
