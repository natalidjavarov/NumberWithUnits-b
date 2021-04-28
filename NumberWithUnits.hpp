#include <string.h>
#include <iostream>
#include <stdbool.h>
#include <map>
#include <string>

#pragma once
namespace ariel
{

    class NumberWithUnits
    {

        static std::map<std::string, std::map<std::string, double>> units;

    private:
        double num;
        std::string unit;

    public:
        NumberWithUnits(double num, std::string unit);
        //  {
        //     this->num = num;
        //     this->unit = unit;
        // }

        static void read_units(std::ifstream &units_file);
        static double convert(const std::string &to, const std::string &from);
        NumberWithUnits operator+(const NumberWithUnits &num);
        NumberWithUnits &operator+=(const NumberWithUnits &num);
        NumberWithUnits operator+(); //onary
        NumberWithUnits operator-(const NumberWithUnits &num);
        NumberWithUnits &operator-=(const NumberWithUnits &num);
        NumberWithUnits operator-(); //onary

        friend bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2);
        friend bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2);

        friend NumberWithUnits &operator++(NumberWithUnits &n);
        friend NumberWithUnits operator++(NumberWithUnits &n, int);
        friend NumberWithUnits &operator--(NumberWithUnits &n);
        friend NumberWithUnits operator--(NumberWithUnits &n, int);
        friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &num);
        friend std::istream &operator>>(std::istream &in, NumberWithUnits &num);

        friend NumberWithUnits operator*(double a, const NumberWithUnits &n);
        friend NumberWithUnits operator*(const NumberWithUnits &n, double a);
        friend NumberWithUnits operator*=(NumberWithUnits &n, double a);
        friend NumberWithUnits operator*=(double a, NumberWithUnits &n);
    };

}