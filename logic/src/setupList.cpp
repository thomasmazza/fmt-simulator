#include "../incl/setupList.hpp"

namespace setup {
    template<typename T>
    void List::ins(int pos, const &T e){
        lst.insert(pos, std::make_unique<T>(e));
    }

    template<typename T>
    void List::append(const &T e){
        lst.push_back(std::make_unique<T>(e));
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
}
