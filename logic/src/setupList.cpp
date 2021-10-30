#include "../include/setupList.hpp"

#include "filter.hpp"
#include "lensTwoSided.hpp"
#include "lensOneSided.hpp"
#include "mirrorRectangle.hpp"
#include "mirrorCircle.hpp"
#include "mirrorElliptical.hpp"
#include "mirrorSquare.hpp"
#include "detector.hpp"
#include "aperture.hpp"

template<typename T> void List::ins(int pos, const T& _e){
    auto it = lst.begin();
    for(int i = 1; i < pos; i++) it++;
    lst.insert(it, std::make_unique<T>(_e));
}

template<typename T> void List::append(const T& _e){
    lst.push_back(std::make_unique<T>(_e));
}

void List::del(int pos){
    auto it = lst.begin();
    for(int i = 1; i < pos; i++) it++;
    lst.erase(it);
}

void List::swap(int pos1, int pos2){
    lst[pos1].swap(lst[pos2]);
}

std::unique_ptr<Component>& List::elem(int pos){
    return lst[pos];
}

int List::getLength(){
    return lst.size();
}

template void List::ins<Filter>(int, const  Filter&);
template void List::ins<MirrorCircle>(int, const MirrorCircle&);
template void List::ins<MirrorRectangle>(int, const MirrorRectangle&);
template void List::ins<MirrorElliptical>(int, const MirrorElliptical&);
template void List::ins<MirrorSquare>(int, const MirrorSquare&);
template void List::ins<LensTwoSided>(int, const LensTwoSided&);
template void List::ins<LensOneSided>(int, const LensOneSided&);
template void List::ins<Detector>(int, const Detector&);
template void List::ins<Aperture>(int, const Aperture&);

template void List::append<Filter>(const  Filter&);
template void List::append<MirrorCircle>(const MirrorCircle&);
template void List::append<MirrorRectangle>(const MirrorRectangle&);
template void List::append<MirrorElliptical>(const MirrorElliptical&);
template void List::append<MirrorSquare>(const MirrorSquare&);
template void List::append<LensTwoSided>(const LensTwoSided&);
template void List::append<LensOneSided>(const LensOneSided&);
template void List::append<Detector>(const Detector&);
template void List::append<Aperture>(const Aperture&);
