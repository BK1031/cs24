//
// Created by Bharat Kathi (5938444) on 3/11/22.
//

#include "movies.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>

using namespace std;

string movies::getName() const {
    return name;
}

double movies::getRating() const {
    return rating;
}

void movies::operator=(const movies &m2) {
    name.assign(m2.name);
    rating = m2.rating;
}

ostream& operator<<(ostream& os, const movies &m) {
    os << m.name << ", " << fixed << setprecision(1) << m.rating;
    return os;
}