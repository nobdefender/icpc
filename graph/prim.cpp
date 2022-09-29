#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>

using namespace std;

int main()
{
    map <int, vector <pair<int, int>>> mass;
    vector <int> check;
    vector <int> result;
    vector <pair<int, int>> way;
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n = 0, m = 0, third = 0, temp = 10e5, top = 10e5, sum = 0, count = 0, first = 0, second = 0, parent = 0, child = 0;
    in >> n >> m;

    check.resize(n - 1);
    result.push_back(0);

    for (int i = 0; i < n - 1; i++) {
        check[i] = i + 1;
    }

    for (int i = 0; i < m; i++) {
        in >> first >> second >> third;
        first--;
        second--;
        mass[first].push_back(make_pair(second, third));
        mass[second].push_back(make_pair(first, third));
    }
    /*
    for (int i = 0; i < n; i++) {
        out << i << ": ";
        sort(mass[i].begin(), mass[i].end());
        for (int j = 0; j < mass[i].size(); j++) {
            out << mass[i][j].first << " ";
        }
        out << endl;
    }
    */

    while (!check.empty()) {
        for (int i = 0; i < result.size(); i++) {
            //temp = mass[result[i]][0].second;
            //top = mass[result[i]][0].first;
            for (int j = 0; j < mass[result[i]].size(); j++) {
                //out << "current = " << mass[result[i]][j].second << endl;
                if (mass[result[i]][j].second < temp && find(check.begin(), check.end(), mass[result[i]][j].first) != check.end()) {
                    temp = mass[result[i]][j].second;
                    top = mass[result[i]][j].first;
                    parent = result[i];
                }
            }
        }
        // way.push_back(make_pair(parent, top));
        result.push_back(top);

        for (int k = 0; k < check.size(); k++) {
            if (check[k] == top) {
                count = k;
                break;
            }
        }
        check.erase(check.begin() + count);
        /*
        out << "check" << endl;
        for (int k = 0; k < check.size(); k++) {
            out << check[k] << " ";
        }
        out << endl;
        out << "result" << endl;
        for (int k = 0; k < result.size(); k++) {
            out << result[k] << " ";
        }
        out << endl;
        */

        sum += temp;
        count = 0;
        temp = 10e5;
        top = 10e5;
    }
    //sum -= temp;
    out << sum << endl;

    // for (int i = 0; i < way.size(); i++) {
    //     out << way[i].first + 1 << " " << way[i].second + 1 << endl;
    // }

    return 0;
}
