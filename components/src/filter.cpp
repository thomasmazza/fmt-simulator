namespace component {
    template<typename T>
    int Filter<T>::getLowerLim(){
        return lowerLim;
    }

    template<typename T>
    void Filter<T>::setLowerLim(int _lowerLim){
        lowerLim=_lowerLim;
    }

    template<typename T>
    int Filter<T>::getUpperLim(){
        return upperLim;
    }

    template<typename T>
    void Filter<T>::setUpperLim(int _upperLim){
        upperLim=_upperLim;
    }

    template<typename T>
    bool Filter<T>::inRange(int lambda){
        if(lambda>upperLim||lambda<lowerLim) return false;
        return true;
    }

    template<typename T>
    Filter<T>::Filter(vector<T>& _pos,vector<T>& _normal,int _lowerLim,int _upperLim):
        Filter<T>::Component(_pos,_normal),
        lowerLim(_lowerLim),
        upperLim(_upperLim){
    }
}