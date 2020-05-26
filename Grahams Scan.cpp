#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <math.h>

std::ifstream in("input.txt");
struct Point{
    int x, y;
};

Point p0;

void read(std::vector<Point> &points){
    Point tmp;
    while(in>>tmp.x>>tmp.y)
        points.push_back(tmp);
    if(points.size())
        p0=points[0];
}

void print(std::vector<Point> const &points){
    std::cout<<"The points in the vector are: "<<std::endl;
	for (int i = 0; i < points.size(); i++) {
		std::cout<<points.at(i).x<<","<<points.at(i).y<<std::endl;
	}
}

void swap(Point p1, Point p2){
    Point tmp=p1;
    p1 = p2;
    p2 = tmp;
}

bool lessThan(Point p1, Point p2){
    /// This compares the coordinates of the points and computes a value that represents a left or right turn
    int tmp = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
    if (tmp < 0) return 1;
    return 0;
}

bool equalAngle(Point p1, Point p2){
    int tmp = (p1.y - p0.y) * (p2.x - p1.x) - (p1.x - p0.x) * (p2.y - p1.y);
    if (!tmp) return 1;
    return 0;
}

bool leftTurn(Point p1, Point p2, Point p3){
    int tmp = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);
    if (tmp < 0) return 0;
    return 1;
    std::cout<<"ba";
}

Point nextToTop(std::stack<Point> &S){
    //std::cout<<S.top().x<<" "<<S.top().y<<std::endl;
    Point tmp = S.top();
    S.pop();
    Point tmp1= S.top();
    S.push(tmp);
    return tmp1;
}


int main(){
    std::vector<Point> points;
    read(points);
    print(points);
    //std::cout<<lessThan(points[1],points[2]);

    int minY = points[0].y, mini = 0, y;
    for (int i = 1; i < points.size(); i++) {
        y = points[i].y;
        if ((y < minY) || (minY == y && points[i].x < points[mini].x)){
            minY = points[i].y;
            mini = i;
        }
    }

    /// Set the starting point and sort the array
    swap(points[0], points[mini]);
    p0 = points[0];
    std::sort (points.begin(), points.end(), lessThan);

    /// If two points form the same angle with p0, we remove the closest one
    int new_size = 1;
    for (int i=1; i<points.size(); i++) {
        while (i < points.size()-1 && equalAngle(points[i], points[i+1]))
            i++;
        points[new_size] = points[i];
        new_size++;
    }

    if (new_size < 3) return -1;

    /// We push the firs three points to the stack and proceed to check the rest
    std::stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);
    /// std::cout<<"New_size: "<<new_size<<std::endl;
    for (int i = 3; i < new_size; i++){
        while (leftTurn(nextToTop(S), S.top(), points[i])){
            //std::cout<<S.top().x<<" "<<S.top().y<<std::endl;
            S.pop();
        }
        S.push(points[i]);
    }

    /// The points remaining on the stack represent the convex hull of the points
    std::cout<<"The convex hull is represented by the points: "<<std::endl;
    while (!S.empty()){
        Point p = S.top();
        std::cout<<"("<<p.x<<", "<<p.y <<")"<<std::endl;
        S.pop();
    }
}
