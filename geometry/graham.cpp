#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<cmath>
#include<iomanip>

#define int long long
#define all(x) (x).begin(), (x).end()

using namespace std;

struct point {
    int x, y;
};

point operator-(point a, point b) {
    return {
        a.x - b.x,
        a.y - b.y
    };
};

bool operator==(point a, point b) {
    return (a.x == b.x) && (a.y == b.y);
}

int operator^(point a, point b) {
    return a.x * b.y - a.y * b.x;
};

bool comp(point& a, point& b) {
    return ((a ^ b) > 0) || ((a ^ b) == 0 && a.x * a.x + a.y * a.y > b.x* b.x + b.y * b.y);
};

vector<point> graham(vector<point> points) {
    point p0 = points[0];
    for (point p : points) {
        if (p.y < p0.y || (p.y == p0.y && p.x > p0.x)) {
            p0 = p;
        }
    }

    // points.erase(remove(points.begin(), points.end(), p0), points.end());

    for (point& p : points) {
        p.x -= p0.x;
        p.y -= p0.y;
    }
    sort(all(points), comp);

    vector<point> hull;
    for (point p : points) {
        while (hull.size() >= 2 && ((p - hull.back()) ^ (hull[hull.size() - 2] - hull.back())) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    for (point& p : hull) {
        p.x += p0.x;
        p.y += p0.y;
    }

    return hull;
}

signed main()
{
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);

    long long t = 1;
    // cin >> t;

    while (t--) {
        int n = 0, temp_x = 0, temp_y = 0;
        cin >> n;
        vector<point> mass;
        for (int i = 0; i < n; i++) {
            cin >> temp_x >> temp_y;
            mass.push_back({ temp_x, temp_y });
        }

        vector<point> result = graham(mass);
        cout << result.size() << endl;
        for (point p : result) {
            cout << p.x << " " << p.y << endl;
        }
    }

    return 0;
}