#pragma once

#include <vector>
#include <memory>

#include "../../components/include/component.hpp"

namespace setup {
    class List {
    private:
        std::vector<std::unique_ptr<Component>> lst;
    public:
        List();
        template<typename T> void ins(int, const T);
        template<typename T> void append(const T);
        void del(int);
        void swap(int, int);
        std::unique_ptr<Component>& elem(int);
        int getLength();
    };
}
