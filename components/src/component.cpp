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
    vector<T>& Component<T>::getNormal(){
        return normal;
    }

    template<typename T>
    void Component<T>::setNormal(vector<T>& _normal){
        normal=_normal;
    }

    template<typename T>
    Component<T>::Component(vector<T>& _pos,vector<T>& _normal){
        Component<T>::setPos(_pos);
        Component<T>::setNormal(_normal);
    }
}