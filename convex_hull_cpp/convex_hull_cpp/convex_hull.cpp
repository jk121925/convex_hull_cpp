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
	void setinfo(double _x, double _y)
	{
		X = _x;
		Y = _y;
	}
	void showData()
	{
		cout << '(' << X << ',' << Y << ')' << endl;
	}
	double x()
	{
		return X;
	}
	double y()
	{
		return Y;
	}
};



double test_line_equationF(point pt1, point pt2, point test_pt) {
	double val;
	if (pt1.x() - pt2.x() == 0) {
		val = test_pt.x() - pt1.x();
	}
	else if (pt1.x() - pt2.x() != 0) {
		double m = (pt1.y() - pt2.y()) / (pt1.x() - pt2.x());
		val = (-1) * m * (test_pt.x() - pt1.x()) + (test_pt.y() - pt1.y());
	}
	return val;
}


bool vector_inner_testF(vector<double> test_vector) {
	test_vector.erase(unique(test_vector.begin(), test_vector.end()), test_vector.end());
	return (test_vector.size() == 1);
}



int main() {
	random_device rng;
	uniform_real_distribution<double> dist(-10.0, 10.0);

	vector <point> vecPoint;
	for (int i = 0; i < 10; i++) {
		point temp1;
		temp1.setinfo(dist(rng), dist(rng));
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
		vector<double> test_dummy;
		for (int j = 0; j < vecPoint.size(); j++) {
			double test_val = test_line_equationF(vecComb[i][0], vecComb[i][1], vecPoint[j]);
			if (test_val > 0)
			{
				test_dummy.push_back(1);
			}
			else if (test_val < 0)
			{
				test_dummy.push_back(-1);
			}
		}
		if (bool A = vector_inner_testF(test_dummy))
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