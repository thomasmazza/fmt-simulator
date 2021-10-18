#pragma once

#include <vector>
#include <memory>

#include "../../components/include/component.hpp"


    class List {
    private:
        std::vector<std::unique_ptr<Component>> lst;
    public:
        template<typename T> void ins(int, const T&);
        template<typename T> void append(const T&);
        void del(int);
        void swap(int, int);
        std::unique_ptr<Component>& elem(int);
        int getLength();
    };

