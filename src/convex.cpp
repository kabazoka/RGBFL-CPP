struct Point {
    float x, y;
    bool operator < (const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};

float cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

std::vector<Point> convexHull(std::vector<Point> points) {
    int n = points.size(), k = 0;
    if (n <= 3) return points;
    std::vector<Point> H(2*n);

    // Sort points lexicographically
    std::sort(points.begin(), points.end());

    // Build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], points[i]) <= 0) k--;
        H[k++] = points[i];
    }

    // Build upper hull
    for (int i = n-1, t = k+1; i > 0; --i) {
        while (k >= t && cross(H[k-2], H[k-1], points[i-1]) <= 0) k--;
        H[k++] = points[i-1];
    }

    H.resize(k-1);
    return H;
}


