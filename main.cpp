#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;
};

bool compareX(Point FirstNum, Point SecondNum) {
    return FirstNum.x<SecondNum.x;
}

bool compareY(Point FirstNum, Point SecondNum) {
    return FirstNum.y<SecondNum.y;
}

double distance(Point FirstNum, Point SecondNum) {
    return sqrt(pow(FirstNum.x-SecondNum.x, 2)+pow(FirstNum.y-SecondNum.y, 2));
}

double bruteForce(Point P[], int n) {
    double minDist = INFINITY;
    for (int i=0; i<n; ++i) {
        for (int j=i+1; j<n; ++j) {
            minDist = min(minDist, distance(P[i], P[j]));
        }
    }
    return minDist;
}

double stripClosest(Point strip[], int size, double d) {
    double minDist=d;
    sort(strip, strip+size, compareY);
    for (int i=0; i<size; ++i) {
        for (int j=i+1; j<size&&(strip[j].y-strip[i].y)<minDist; ++j) {
            minDist = min(minDist, distance(strip[i], strip[j]));
        }
    }
    return minDist;
}

double closestUtil(Point Px[], Point Py[], int n) {
    if (n <= 3)
        return bruteForce(Px, n);

    int mid = n / 2;

    Point midPoint = Px[mid];

    Point Pyl[mid + 1];
    Point Pyr[n - mid - 1];

    int li = 0, ri = 0;
    for (int i = 0; i < n; ++i) {
        if (Py[i].x <= midPoint.x && li <= mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    double dl = closestUtil(Px, Pyl, mid);
    double dr = closestUtil(Px + mid, Pyr, n - mid);

    double d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; ++i) {
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j++] = Py[i];
    }

    return min(d, stripClosest(strip, j, d));
}

double closest(Point P[], int n) {
    Point Px[n], Py[n];

    for (int i = 0; i < n; ++i) {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    sort(Px, Px + n, compareX);
    sort(Py, Py + n, compareY);

    return closestUtil(Px, Py, n);
}

int main() {
    Point P[]={{2,-1.4},{-1.7,-1.9},{-1.8,-2.5},{-3.5,-4.6},{-2.4,-3.8},{1.6,-2.9},{-4.7,-3.7}};
    int n=sizeof(P)/sizeof(P[0]);
    cout << "The smallest distance is " << closest(P,n) << endl;
    return 0;
}
