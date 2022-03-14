//
// Created by Bharat Kathi (5938444) on 3/11/22.
//

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

#ifndef PA02_BK1031_MOVIES_H
#define PA02_BK1031_MOVIES_H

using namespace std;

class movies {
    public:
        movies(string name, double rating) : name(name), rating(rating) {}
        ~movies() {}
        movies(const movies &m) {
            name = m.name;
            rating = m.rating;
        }
        string getName() const;
        double getRating() const;
        void operator=(const movies &m2);
        friend ostream& operator<<(ostream& os, const movies &m);
    private:
        string name;
        double rating;
};

#endif //PA02_BK1031_MOVIES_H
