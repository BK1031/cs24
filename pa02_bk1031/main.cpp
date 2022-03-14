// Winter'22
// Instructor: Diba Mirza
// Student name: Bharat Kathi (5938444)

#include "movies.cpp"
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


bool parseLine(string &line, string &movieName, double &movieRating);

struct Name {
    bool operator()(const movies &m1, const movies &m2) const {
        return m1.getName() < m2.getName();
    }
};

struct Rating {
    bool operator()(const movies &m1, const movies &m2) const {
        if (m1.getRating() == m2.getRating()) {
            return m1.getName() < m2.getName();
        }
        return m1.getRating() > m2.getRating();
    }
};

int main(int argc, char** argv) {
    if(argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " filename prefix1 prefix2 ... prefix n " << endl;
        exit(1);
    }


    ifstream movieFile (argv[1]);


    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }

    //Create an object of a STL data-structure to store all the movies
    set<movies, Name> movieSet;

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        // Use std::string movieName and double movieRating
        // to construct your movies objects
        // cout << movieName << " has rating " << movieRating << endl;
        // insert elements into your data structure
        movies m(movieName, movieRating);
        movieSet.insert(m);
    }

    movieFile.close();

    if (argc == 2) {
        //print all the movies in ascending alphabetical order of movie names
        set<movies>::iterator i;
        for (i = movieSet.begin(); i != movieSet.end(); i++) {
            cout << *i << endl;
        }
        return 0;
    }

    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    for (int i = 2; i < argc; i++) {
        string prefix = argv[i];
        string prefixFull = prefix + "~";

        movies a(prefix, -1.0);
        movies b(prefixFull, -1.0);
        movies splitter("~", -1.0);

        movieSet.insert(splitter);
        set<movies>::iterator itlow,itup;
        itlow = movieSet.lower_bound(a);
        itup = movieSet.upper_bound(b);
        set<movies, Rating> movieSet2(movieSet.find(*itlow), movieSet.find(*itup));
        if (movieSet2.empty()) {
            cout<<"No movies found with prefix "<< prefix << endl;
        }
        else {
            set<movies, greater<movies>>::iterator i;
            for (i = movieSet2.begin(); i != movieSet2.end(); i++) {
                cout << *i << endl;
            }
        }
        cout << endl;
    }

//  For each prefix,
//  Print the highest rated movie with that prefix if it exists.
    for (int i = 2; i < argc; i++) {
        string prefix = argv[i];
        string prefixFull = prefix + "~";

        movies a(prefix, -1.0);
        movies b(prefixFull, -1.0);

        set<movies>::iterator itlow,itup;
        itlow = movieSet.lower_bound(a);
        itup = movieSet.upper_bound(b);
        set<movies, Rating> movieSet2(movieSet.find(*itlow), movieSet.find(*itup));

        if (!movieSet2.empty()) {
            movies first = *movieSet2.begin();
            cout << "Best movie with prefix "<< prefix <<" is: " << first.getName() <<" with rating " << fixed << setprecision(1) << first.getRating() << endl;
        }
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block

 The first loop (LINE 80) runs m times.
 For each of these m runs, the longest possible runtime would be [ 2 [O(log n)] + O(n log n + 2 log n) + O(k) ]
 Therefore, our first loop has a runtime of [ O(m * (n log n + 4 log n + k)) ]

 The second loop (LINE 109) also runs m times.
 For each of these m runs, the longest possible runtime would be [ 2 [O(log n)] + O(n log n + 2 log n) ]
 Therefore, our second loop has a runtime of [ O(m * (n log n + 4 log n) ]

 Finally, we can combine these 2 loops to get a run time of [ O(m (n log n + k) + m (n log n)) ]
 This simplifies to [ O(m(n log n + k)) ]

*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    if(line.length() <= 0) return false;
    string tempRating = "";

    bool flag = false;
    movieName = tempRating = "", movieRating = 0.0, flag = false;

    for (int i = 0; i < line.length(); i++){
        if(flag) tempRating += line[i];
        else if(line[i]==','&& line[0]!='"') flag = true;
        else {
            if(i==0 && line[0]=='"') continue;
            if(line[i]=='"'){ i++; flag=true; continue;}
            movieName += line[i];
        }
    }

    movieRating = stod(tempRating);
    return true;
}