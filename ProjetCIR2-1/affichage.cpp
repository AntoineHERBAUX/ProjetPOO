#include "main.hpp"


void center_text_under_station(Station station, std::string text) {
    Vector center_coord = station.Coordinates;
    int len_text = MeasureText(text.c_str(), 10);
    DrawText(text.c_str(), center_coord.x - len_text / 2, center_coord.y + 20, 10, WHITE);
};


void Station::show_station() const {
    DrawCircle(this->Coordinates.x, this->Coordinates.y, 10, RED);
    center_text_under_station(*this, (this->name));
    char string[20];
    DrawText(itoa(this->passagers, string, 10), this->Coordinates.x, this->Coordinates.y-15, 20, ORANGE);
}

void Rame::show_rame() {
    this->texture = LoadTextureFromImage(this->image);
    int y_coord, x_coord;
    if (this->whichVoie == 0) {
        y_coord = 0; x_coord = -10;
    }
    else {
        y_coord = -19; x_coord = -10;
    }
    //ImageDraw();
    //DrawRectangle(this->Coordinates.x + x_coord, this->Coordinates.y + y_coord, 50, 20, BLUE);
    DrawTexture(texture, this->Coordinates.x + x_coord, this->Coordinates.y + y_coord, WHITE);
    char string[20];
    DrawText(itoa(this->number, string, 10), this->Coordinates.x + x_coord, this->Coordinates.y + y_coord, 10, GREEN);
    DrawText(itoa(this->passagers, string, 10), this->Coordinates.x + x_coord, this->Coordinates.y - 15 + y_coord, 5, ORANGE);
}






void global_show(const std::vector<Station> ligneA, std::vector<Rame> rames, bool menu, Rame *target_rame) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Metro Simulator", 10, 10, 20, WHITE);

    //on relie toutes les stations par un trait jaune
    for (int i = 0; i < ligneA.size() - 1; i++) {
        int x1 = ligneA[i].Coordinates.x;
        int x2 = ligneA[i + 1].Coordinates.x;
        int y1 = ligneA[i].Coordinates.y;
        int y2 = ligneA[i + 1].Coordinates.y;
        DrawLine(x1 + (x1 - 600) * 0.01, y1 - 5 + (y1 - 300) * 0.01, x2 + (x2 - 600) * 0.01, y2 - 5 + (y2 - 300) * 0.01, YELLOW);
        DrawLine(x1 + (x1 - 600) * -0.01, y1 + 5 + (y1 - 300) * -0.01, x2 + (x2 - 600) * -0.01, y2 + 5 + (y2 - 300) * -0.01, GREEN);


    for (int i = 0; i < ligneA.size(); i++) {
        ligneA[i].show_station();
    }
    
        }for (int i = 0; i < rames.size(); i++) {
        rames[i].show_rame();
    }
    if(menu==true){
        DrawText("Metro Simulator", 10, 10, 20, WHITE);

        DrawText("0: Informations de la rame", 10, 50, 20, WHITE);
        DrawText("1: Arret d'urgence", 10, 100, 20, WHITE);
        DrawText("2: Passer une station", 10, 150, 20, WHITE);
        DrawText("3: Vider la rame", 10, 200, 20, WHITE);
        DrawText("4: Reprendre l'avancée", 10, 250, 20, WHITE);
        DrawText("5: Quitter", 10, 300, 20, WHITE);
    }
    EndDrawing();
    for (int i = 0; i < rames.size(); i++) {
        UnloadTexture(rames[i].texture);
    }



}