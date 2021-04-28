
#include "NumberWithUnits.hpp"
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime>
#include <string>

using namespace std;

const double EPS = 0.001;

namespace ariel
{

        map<string, map<string, double>> NumberWithUnits::units = {};
        NumberWithUnits::NumberWithUnits(double num, string unit)
        {
                if (units.count(unit) == 0)
                {
                        throw invalid_argument("Ilegal unit!!: " + unit);
                }

                this->num = num;
                this->unit = unit;
        }
        //      1 ILS = 2 USD
        //      1 USD = 2 EURO
        //      1 EURO = 2 POUND
        void NumberWithUnits::read_units(ifstream &units_file)
        {
                double num1, num2;
                std::string unit1, wmp, unit2;
                while (units_file >> num1 >> unit1 >> wmp >> num2 >> unit2)
                {
                        // add to table units
                        units[unit1][unit1] = 1;
                        units[unit2][unit2] = 1;
                        units[unit1][unit2] = num2;
                        units[unit2][unit1] = 1 / num2;
                        for (auto &p : units[unit2])
                        {
                                double w = units[unit1][unit2] * p.second;
                                units[unit1][p.first] = w;
                                units[p.first][unit1] = 1 / w;
                        }
                        // add u1 ni to u2
                        for (auto &p : units[unit1])
                        {
                                double w = units[unit2][unit1] * p.second;
                                units[unit2][p.first] = w;
                                units[p.first][unit2] = 1 / w;
                        }
                }

                // add u2 ni to u1

                // print
                for (const auto &p : units)
                {
                        std::cout << p.first << "->";
                        for (const auto &p1 : units[p.first])
                        {
                                std::cout << "{" << p1.first << ", " << units[p.first][p1.first] << "}";
                        }
                        cout << endl;
                }
                cout << "** THE END **\n";
        }
        double NumberWithUnits::convert(const std::string &from, const std::string &to)
        {
                try
                {
                        double c = units.at(from).at(to);
                        return c;
                }
                catch (const exception &e)
                {
                        throw invalid_argument{"units are not of the same type!!!!!!!!!!!!!!!"};
                }
        }
        NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &num)
        {
                double a = convert(num.unit, this->unit)*num.num;
                return NumberWithUnits((this->num) + a, this->unit);
        }

        NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &num)
        {
                double a = convert(num.unit, this->unit) * num.num;
                return NumberWithUnits((this->num) - a, this->unit);
        }
        NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &num)
        {
                this->num += convert(num.unit, this->unit) * num.num;
                return *this;
        }
        NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &num)
        {
                this->num -= convert(num.unit, this->unit) * num.num;
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator+()
        {
                return NumberWithUnits(+(this->num), this->unit);
        }
        NumberWithUnits NumberWithUnits::operator-()
        {
                return NumberWithUnits(-(this->num), this->unit);
        }

        NumberWithUnits &operator++(NumberWithUnits &n)
        {
                n.num++;
                return n;
        }
        NumberWithUnits operator++(NumberWithUnits &n, int)
        {

                return NumberWithUnits(n.num++, n.unit);
        }
        NumberWithUnits &operator--(NumberWithUnits &n)
        {
                n.num--;
                return n;
        }
        NumberWithUnits operator--(NumberWithUnits &n, int)
        {

                return NumberWithUnits(n.num--, n.unit);
        }

        bool operator>(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                double num2_as_unit1 = NumberWithUnits::convert(num2.unit, num1.unit)*num2.num;
                bool ans = num1.num > num2_as_unit1 + EPS;
                return ans;
        }

        bool operator>=(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                bool ans = !(num1 < num2);
                return ans;
        }
        bool operator<(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                return !(num1 > num2) && !(num1 == num2);
        }
        bool operator<=(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                bool ans = !(num1 > num2);
                return ans;
        }
        bool operator==(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                bool ans = (num1.num + EPS >= NumberWithUnits::convert(num2.unit, num1.unit) * num2.num) && (num1.num - EPS <= NumberWithUnits::convert(num2.unit, num1.unit) * num2.num);
                return ans;
        }
        bool operator!=(const NumberWithUnits &num1, const NumberWithUnits &num2)
        {
                bool ans = !(num1 == num2);
                return ans;
        }

        NumberWithUnits operator*(double a, const NumberWithUnits &n)
        {
                return NumberWithUnits(n.num * a, n.unit);
        }
        NumberWithUnits operator*(const NumberWithUnits &n, double a)
        {
                return NumberWithUnits(n.num * a, n.unit);
        }

        NumberWithUnits operator*=(double a, NumberWithUnits &n)
        {
                return NumberWithUnits(n.num *= a, n.unit);
        }
        NumberWithUnits operator*=(NumberWithUnits &n, double a)
        {
                return NumberWithUnits(n.num *= a, n.unit);
        }

        std::ostream &operator<<(std::ostream &out, const NumberWithUnits &num)
        {
                return (out << num.num << "[" << num.unit << "]");
        }
        //2[km] >> NumberWithUnits(2,"km")
        //2[ km ] >> NumberWithUnits(2,"km")x`
        //2[ km] >> NumberWithUnits(2,"km")
        std::istream &operator>>(std::istream &in, NumberWithUnits &num)
        {
                std::string str;
                char c;
                double n;
                
                in >> n ;
                in >> c;
                in >> str;
                if (!(str[str.length()-1]==']') ){
                 char d;
                 in >> d;
        
                }
                else{
                 str=str.substr(0,str.length()-1);


                }
                if(str[0] == '['){
                  str=str.substr(1,str.length());
 
                }
                num = NumberWithUnits(n,str);
               

               return in;
                }
                }