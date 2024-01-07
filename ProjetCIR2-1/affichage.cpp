#include "main.hpp"

void center_text_under_station(Station station, std::string text) {
    Vector center_coord = station.Coordinates;
    int len_text = MeasureText(text.c_str(), 10);
    DrawText(text.c_str(), center_coord.x - len_text / 2, center_coord.y + 20, 10, WHITE);
};


void Station::show_station() const {
    DrawCircle(this->Coordinates.x, this->Coordinates.y, 10, RED);
    center_text_under_station(*this, (this->name));
}

void Rame::show_rame() const {
    int y_coord, x_coord;
    if (this->whichVoie == 0) {
        y_coord = 2; x_coord = -25;
    }
    else {
        y_coord = -21; x_coord = -25;
    }
    DrawRectangle(this->Coordinates.x + x_coord, this->Coordinates.y + y_coord, 50, 20, BLUE);
}




void global_show(const std::vector<Station> ligneA, const std::vector<Rame> rames) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Metro Simulator", 10, 10, 20, WHITE);

    for (int i = 0; i < ligneA.size(); i++) {
        ligneA[i].show_station();
    }
    for (int i = 0; i < rames.size(); i++) {
        rames[i].show_rame();
    }
    //on relie toutes les stations par un trait jaune
    for (int i = 0; i < ligneA.size() - 1; i++) {
        int x1 = ligneA[i].Coordinates.x;
        int x2 = ligneA[i + 1].Coordinates.x;
        int y1 = ligneA[i].Coordinates.y;
        int y2 = ligneA[i + 1].Coordinates.y;
        DrawLine(x1 + (x1 - 600) * 0.01, y1 - 5 + (y1 - 300) * 0.01, x2 + (x2 - 600) * 0.01, y2 - 5 + (y2 - 300) * 0.01, YELLOW);
        DrawLine(x1 + (x1 - 600) * -0.01, y1 + 5 + (y1 - 300) * -0.01, x2 + (x2 - 600) * -0.01, y2 + 5 + (y2 - 300) * -0.01, GREEN);
    }
    EndDrawing();
}