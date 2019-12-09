//
// Created by ariel on 11/11/2019.
//

#ifndef BLACKSCHOLES_VOLSMILE_H
#define BLACKSCHOLES_VOLSMILE_H

#include <iostream>
#include "Date.h"
#include "BS.h"
#include "CubicSpline.h"

using std::vector;
using std::cout;
using std::endl;

class VolSmile : public CubicSpline{
private:
    Date settDate;
    Date maturity;
    double forward;
    double discount;

public:
    VolSmile(const Date &_maturity, const Date &_settDate, double _forward,double _discount):
    CubicSpline({},{}), maturity(_maturity), settDate(_settDate), forward(_forward), discount(_discount){}
    void newSpot(double K, double price, int flag = 1);
    void read(const string & file);
    void write(const string & file, int len = 1e5) const;
    void print() const;
    void calibrate();
};

#endif //BLACKSCHOLES_VOLSMILE_H
