namespace component {
    template<typename T>
    vector<T>& getPos(){
        return pos;
    }

    template<typename T>
    void setPos(vector<T>& _pos){
        pos=_pos;
    }

    template<typename T>
    Component(vector<T>& _pos){
        setPos<T>(_pos);
    }
}