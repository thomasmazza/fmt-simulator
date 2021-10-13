#pragma once

#include <string>
#include <fstream>

#include "setupList.hpp"
#include "../../components/include/component.hpp"

typedef typename boost::numeric::ublas::vector<double> vector;
typedef typename std::string string;


    class Importer {
    private:
        static const string FILTER_OPENING_TAG;
        static const string FILTER_CLOSING_TAG;
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
        static const string NORMAL_OPENING_TAG;
        static const string NORMAL_CLOSING_TAG;
        static const string LOWER_LIMIT_OPENING_TAG;
        static const string LOWER_LIMIT_CLOSING_TAG;
        static const string UPPER_LIMIT_OPENING_TAG;
        static const string UPPER_LIMIT_CLOSING_TAG;
        static const string RADIUS_H_OPENING_TAG;
        static const string RADIUS_H_CLOSING_TAG;
        static const string RADIUS_W_OPENING_TAG;
        static const string RADIUS_W_CLOSING_TAG;
        static const string REF_INDEX_OPENING_TAG;
        static const string REF_INDEX_CLOSING_TAG;
        static const string D_OPENING_TAG;
        static const string D_CLOSING_TAG;

        static bool isCorrectParameter(std::string&, const std::string&);
        static void getContentInBrackets(std::ifstream &, std::string &, const std::string);
        static void getContentInBrackets(std::ifstream &, std::string &);
        static double importNumber(std::ifstream& ,const  std::string&, int&);
        static double importNumber(std::ifstream& ,const  std::string&, double&);


    public:
        Importer();

        static void importVector(std::ifstream &, vector &);

        static void importPosition(std::ifstream &, vector &);

        static void importNormal(std::ifstream &, vector &);

        static void normalizeVector(vector &);

        static void importStp(List &, std::string);
    };

