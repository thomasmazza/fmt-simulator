#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"
#include "config.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::string string;


    class Importer {
    private:
        static bool isCorrectParameter(std::string&, const std::string&);
        static void getContentInBrackets(std::ifstream &, std::string &, const std::string);
        static void getContentInBrackets(std::ifstream &, std::string &);
        static void importNumber(std::ifstream& ,const  std::string&, int&);
        static void importNumber(std::ifstream& ,const  std::string&, double&);
        static void importBool(std::ifstream&, const std::string&, bool&);


    public:
        Importer();

        static void importVector(std::ifstream &, vector &);

        static void importPosition(std::ifstream &, vector &);

        static void importNormal(std::ifstream &, vector &);

        static void normalizeVector(vector &);

        static void importStp(List &, std::string);
    };

