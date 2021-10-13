#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::string string;


    class Importer {
    private:
        static const string FILTER;
        static const string LENS_ONE_SIDED;
        static const string LENS_TWO_SIDED;
        static const string MIRROR_ELLIPTICAL;
        static const string MIRROR_CIRCLE;
        static const string MIRROR_RECTANGLE;
        static const string MIRROR_SQUARE;
        static const string SETUP_OPENING_TAG;
        static const string SETUP_CLOSING_TAG;
        static const string POSITION_OPENING_TAG;
        static const string POSITION_CLOSING_TAG;
        static bool isCorrectParameter(std::string&, const std::string&);
        static void getContentInBrackets(std::ifstream &, std::string &, const std::string);
        static void getContentInBrackets(std::ifstream &, std::string &);


    public:
        Importer();

        static void importVector(std::ifstream &, vector &);

        static void importPosition(std::ifstream &, vector &);

        static void importNormal(std::ifstream &, vector &);

        static void normalizeVector(vector &);

        static void importStp(List &, std::string);
    };

