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
    int y_coord;
    if(this->whichVoie==0) y_coord=10;
    else y_coord=-10;
    DrawRectangle(this->Coordinates.x,this->Coordinates.y+y_coord,50,20,BLUE);
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
    //on relie toutes les stations par un trait jaune
    for(int i=0; i<ligneA.size()-1; i++){
        DrawLine(ligneA[i].Coordinates.x+3,ligneA[i].Coordinates.y+3,ligneA[i+1].Coordinates.x+3,ligneA[i+1].Coordinates.y+3,YELLOW);
        DrawLine(ligneA[i].Coordinates.x-3, ligneA[i].Coordinates.y-3, ligneA[i + 1].Coordinates.x-3, ligneA[i + 1].Coordinates.y-3, GREEN);
    }
    EndDrawing();
}
