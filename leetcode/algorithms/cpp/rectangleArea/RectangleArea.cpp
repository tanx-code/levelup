    // 常规方法
    // 思路：通过判断maxleft,minright,maxbottom,mintop来看是否相交
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C - A) * (D - B);
        int area2 = (G - E) * (H - F);
        int total = area1 + area2;
        int maxLeft = max(A, E);
        int minRight = min(C, G);
        int maxBottom = max(B, F);
        int minTop = min(D, H);
        if(maxLeft >= minRight || maxBottom >= minTop){
            return total;
        }
        return total - (minRight - maxLeft) * (minTop - maxBottom);
    }
// 挺有趣的一个方法，通过观察图像来思考的。
int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) 
{
    int total = (C-A) * (D-B) + (G-E) * (H-F);

    if (C<=E || A>=G || B>=H || D<=F )
        return total;
    else
    {
        vector <int> h;
        h.push_back(A);
        h.push_back(C);
        h.push_back(E);
        h.push_back(G);

        vector <int> v;
        v.push_back(B);
        v.push_back(D);
        v.push_back(F);
        v.push_back(H);

        sort(h.begin(), h.end());
        sort(v.begin(), v.end());

        total = total - (h[2] - h [1]) * (v[2] - v[1]);
        return total;
    }
}


// Source : https://leetcode.com/problems/rectangle-area/
// Author : Hao Chen
// Date   : 2015-06-12

/********************************************************************************** 
 * 
 * Find the total area covered by two rectilinear rectangles in a 2D plane.
 * Each rectangle is defined by its bottom left corner and top right corner as shown in the figure.
 * 
 *                      Y                                        
 *                      ^                                        
 *                      |                                        
 *                      |                                        
 *                      |                                        
 *                      |                                        
 *                      |     (C,D):(3,4)                        
 *            +------------------+                               
 *            |         |        |                               
 *            |         |        |                               
 *            |         |        |               (G,H):(9,2)     
 *            |         +----------------------------+           
 *            |         |        |                   |           
 *            |         |        |                   |           
 *            |         |        |                   |           
 *            +---------|--------+-------------------|---------> X
 *      (A,B):(-3,0)    |                            |           
 *                      +----------------------------+           
 *                  (E,F):(0,-1)                                 
 *      
 *      
 *      
 * Assume that the total area is never beyond the maximum possible value of int.
 * 
 * Credits:Special thanks to @mithmatt for adding this problem, creating the above image and all test cases.
 *               
 **********************************************************************************/
#include <iostream>
using namespace std;

namespace leetcode 
{
    class Point {
        public:
            Point(int _x, int _y):x(_x),y(_y) {}
            int x, y;
    };

    class Rectangle {
        public:
            Rectangle(int a, int b, int c, int d):topLeft(a,d), bottomRight(c,b) { }
            int Area(){
                return (bottomRight.x - topLeft.x)*(topLeft.y - bottomRight.y); 
            }

            int InclusiveArea (Rectangle &r){
                // I include it
                if (r.topLeft.x >= topLeft.x && r.bottomRight.x <= bottomRight.x &&
                        r.topLeft.y <= topLeft.y && r.bottomRight.y >= bottomRight.y ) {
                    return this->Area();
                }
                // it includes me
                if (r.topLeft.x <= topLeft.x && r.bottomRight.x >= bottomRight.x &&
                        r.topLeft.y >= topLeft.y && r.bottomRight.y <= bottomRight.y ) {
                    return r.Area();
                }
                // 0 - no inclusive
                return 0;
            }

            int OverlappedArea(Rectangle &r) {
                int overlap_x = max(0, min(r.bottomRight.x, bottomRight.x) - max(r.topLeft.x, topLeft.x));
                int overlap_y = max(0, min(r.topLeft.y, topLeft.y) - max(r.bottomRight.y, bottomRight.y));
                return overlap_x * overlap_y;
            }

            Point topLeft;
            Point bottomRight;
    };
};


int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    using namespace leetcode;
    Rectangle r1(A,B,C,D);
    Rectangle r2(E,F,G,H);
    int area = r1.InclusiveArea(r2);
    if (area > 0) return area;
    return r1.Area() + r2.Area() - r1.OverlappedArea(r2);
}



int main() 
{
    //16
    cout << "16 : " << computeArea(-1, -1, 1, 1, -2, -2, 2, 2) << endl;
    //16
    cout << "16 : " << computeArea(-2, -2, 2, 2, -1, -1, 1, 1) << endl;
    //17
    cout << "17 : " << computeArea(-2, -2, 2, 2, -4, 3, -3, 4) << endl;
    //45
    cout << "45 : " << computeArea(-3, -0, 3, 4, 0, -1, 9, 2) << endl;
    //24
    cout << "24 : " << computeArea(-2, -2, 2, 2, -3, -3, 3, -1) << endl;
    return 0;
}
