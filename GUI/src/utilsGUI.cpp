#include "../include/utilsGUI.hpp"

//Zurhilfenahme von https://forum.qt.io/topic/16660/solved-remove-items-from-layout/5
void utilsGUI::removeItems(QLayout* layout){
    QLayoutItem* child;
    while(!(layout->isEmpty())) {
        child = layout->takeAt(0);
        if(child->layout() != 0) removeItems(child->layout());
        else if(child->widget() != 0) delete child->widget();
    delete child;
    }
}

