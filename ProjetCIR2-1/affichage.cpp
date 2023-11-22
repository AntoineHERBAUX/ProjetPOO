#include "main.hpp"

void center_text_under_station(Station station, std::string text){
    Vector2 center_coord=station.Coordinates;
    int len_text=MeasureText(text.c_str(),10);
    DrawText(text.c_str(),center_coord.x-len_text/2,center_coord.y+20,10,WHITE);
};


void Station::show_station() const {
    DrawCircle(this->Coordinates.x,this->Coordinates.y,10,RED);
    center_text_under_station(*this,(this->name));
}

void Rame::show_rame() const {
    DrawRectangle(this->Coordinates.x,this->Coordinates.y,50,20,BLUE);
    DrawText(std::to_string(this->number).c_str(),this->Coordinates.x+20,this->Coordinates.y+5,10,WHITE);
}




void global_show(const std::vector<Station> ligneA, const std::vector<Rame> rames) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Metro Simulator", 10, 10, 20, WHITE);
    for(int i=0; i<ligneA.size(); i++){
        ligneA[i].show_station();
    }
    for(int i=0; i<rames.size(); i++){
        rames[i].show_rame();
    }
    EndDrawing();
}
