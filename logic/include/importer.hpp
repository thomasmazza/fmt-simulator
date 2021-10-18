#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"
#include "config.hpp"
        class Importer {
    private:
        static bool isCorrectParameter(std::string&, const std::string&);
        static void getContentInBrackets(std::ifstream &, std::string &, const std::string);
        static void getContentInBrackets(std::ifstream &, std::string &);
        static void importNumber(std::ifstream& ,const  std::string&, int&);
        static void importNumber(std::ifstream& ,const  std::string&, double&);
        static void importBool(std::ifstream&, const std::string&, bool&);


    public:
        static void importVector(std::ifstream &, std::vector<double> &);

        static void importPosition(std::ifstream &, std::vector<double> &);

        static void importNormal(std::ifstream &, std::vector<double> &);

        static void importPointOnEdge(std::ifstream &, std::vector<double> &);

        static void importPosOfPrevComponent(std::ifstream &, std::vector<double> &);

        static void normalizeVector(std::vector<double> &);

        static void importStp(List &, std::string);

        static void importObject(Config::object& object, std::string filename);
    };

