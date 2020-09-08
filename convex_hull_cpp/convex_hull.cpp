#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class point {
private:
	double X;
	double Y;
public:
	void setInfo(double _x, double _y)
	{
		X = _x;
		Y = _y;
	}
	void showData()
	{
		cout << '(' << X << ',' << Y << ')' << endl;
	}
	double getX()
	{
		return X;
	}
	double getY()
	{
		return Y;
	}
};



double line_equationF(point pt1, point pt2, point target) {
	double val = 0;
	if (pt1.getX() - pt2.getX() == 0) {
		val = target.getX() - pt1.getX();
	}
	else if (pt1.getX() - pt2.getX() != 0) {
		double m = (pt1.getY() - pt2.getY()) / (pt1.getX() - pt2.getX());
		val = (-1) * m * (target.getX() - pt1.getX()) + (target.getY() - pt1.getY());
	}
	else
	{
		throw;
	}
	return val;
}

bool vector_inner_testF(vector<double> vec) {
	vec.erase(unique(vec.begin(), vec.end()), vec.end());
	return (vec.size() == 1);
}

int main() {
	random_device rng;
	uniform_real_distribution<double> dist(-10.0, 10.0);

	vector <point> vecPoint;
	for (int i = 0; i < 10; i++) {
		point temp1;
		temp1.setInfo(dist(rng), dist(rng));
		vecPoint.push_back(temp1);
	}

	vector<vector<point>> vecComb;
	for (int i = 0; i < 10; i++) {
		point ptA = vecPoint[i];
		for (int j = i + 1; j < 10; j++) {
			point ptB = vecPoint[j];
			vector<point> temp{ ptA,ptB };
			vecComb.push_back(temp);
		}
	}

	vector <vector<point>> convex_hull_2d;
	for (int i = 0; i < vecComb.size(); i++) {
		vector<double> dummy;
		for (int j = 0; j < vecPoint.size(); j++) {
			double test_val = line_equationF(vecComb[i][0], vecComb[i][1], vecPoint[j]);
			if (test_val > 0)
			{
				dummy.push_back(1);
			}
			else if (test_val < 0)
			{
				dummy.push_back(-1);
			}
		}
		if (bool A = vector_inner_testF(dummy))
		{
			convex_hull_2d.push_back(vecComb[i]);
		}
	}

	for (int i = 0; i < convex_hull_2d.size(); i++) {
		convex_hull_2d[i][0].showData();
		convex_hull_2d[i][1].showData();
	}
	return 0;
}