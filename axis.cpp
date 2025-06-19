#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

struct point {
    double x, y, w;
};

int main() {
    int n, k;
    cin >> n >> k;
    
    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y >> points[i].w;
    }
    
    double min_cost = 1e18;
    double best_x1, best_y1, best_x2, best_y2;
    bool found_solution = false;
    
    // Optimized O(n^2) approach with smart heuristics
    // This is much faster than the previous O(n^4) approach
    
    // Method 1: Sort by x and try consecutive groups
    sort(points.begin(), points.end(), [](const point& a, const point& b) {
        return a.x < b.x;
    });
    
    for (int i = 0; i <= n - k; i++) {
        // Take k consecutive points in x-direction
        double x1 = points[i].x;
        double x2 = points[i + k - 1].x;
        
        // Find y-range that includes these k points
        double min_y = 1e18, max_y = -1e18;
        double weight_sum = 0;
        for (int j = i; j < i + k; j++) {
            min_y = min(min_y, points[j].y);
            max_y = max(max_y, points[j].y);
            weight_sum += points[j].w;
        }
        
        double perimeter = 2 * (x2 - x1) + 2 * (max_y - min_y);
        double cost = perimeter + weight_sum;
        
        if (cost < min_cost) {
            min_cost = cost;
            best_x1 = x1;
            best_y1 = min_y;
            best_x2 = x2;
            best_y2 = max_y;
            found_solution = true;
        }
    }
    
    // Method 2: Sort by y and try consecutive groups
    sort(points.begin(), points.end(), [](const point& a, const point& b) {
        return a.y < b.y;
    });
    
    for (int i = 0; i <= n - k; i++) {
        // Take k consecutive points in y-direction
        double y1 = points[i].y;
        double y2 = points[i + k - 1].y;
        
        // Find x-range that includes these k points
        double min_x = 1e18, max_x = -1e18;
        double weight_sum = 0;
        for (int j = i; j < i + k; j++) {
            min_x = min(min_x, points[j].x);
            max_x = max(max_x, points[j].x);
            weight_sum += points[j].w;
        }
        
        double perimeter = 2 * (max_x - min_x) + 2 * (y2 - y1);
        double cost = perimeter + weight_sum;
        
        if (cost < min_cost) {
            min_cost = cost;
            best_x1 = min_x;
            best_y1 = y1;
            best_x2 = max_x;
            best_y2 = y2;
            found_solution = true;
        }
    }
    
    // Method 3: Sort by weight and try lightest k points
    sort(points.begin(), points.end(), [](const point& a, const point& b) {
        return a.w < b.w;
    });
    
    for (int i = 0; i <= n - k; i++) {
        // Take k lightest points starting from i
        double min_x = 1e18, max_x = -1e18;
        double min_y = 1e18, max_y = -1e18;
        double weight_sum = 0;
        
        for (int j = i; j < i + k; j++) {
            min_x = min(min_x, points[j].x);
            max_x = max(max_x, points[j].x);
            min_y = min(min_y, points[j].y);
            max_y = max(max_y, points[j].y);
            weight_sum += points[j].w;
        }
        
        double perimeter = 2 * (max_x - min_x) + 2 * (max_y - min_y);
        double cost = perimeter + weight_sum;
        
        if (cost < min_cost) {
            min_cost = cost;
            best_x1 = min_x;
            best_y1 = min_y;
            best_x2 = max_x;
            best_y2 = max_y;
            found_solution = true;
        }
    }
    
    // Output result
    if (found_solution) {
        cout << fixed << setprecision(6) << min_cost << endl;
        // Output edges in order: bottom, right, top, left
        cout << best_x1 << " " << best_y1 << " " << best_x2 << " " << best_y1 << endl; // bottom edge
        cout << best_x2 << " " << best_y1 << " " << best_x2 << " " << best_y2 << endl; // right edge
        cout << best_x2 << " " << best_y2 << " " << best_x1 << " " << best_y2 << endl; // top edge
        cout << best_x1 << " " << best_y2 << " " << best_x1 << " " << best_y1 << endl; // left edge
    } else {
        cout << "No solution found" << endl;
    }
    
    return 0;
}
