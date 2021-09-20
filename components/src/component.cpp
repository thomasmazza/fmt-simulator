namespace component {
    template<typename T>
    vector<T>& Component<T>::getPos(){
        return pos;
    }

    template<typename T>
    void Component<T>::setPos(vector<T>& _pos){
        pos=_pos;
    }

    template<typename T>
    Component<T>::Component(vector<T>& _pos){
        Component<T>::setPos(_pos);
    }
}