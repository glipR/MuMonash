// MuMonash

#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <vector>

using namespace std;

#define X real()
#define Y imag()

const double pi = acos(-1);
const double EPS = 1e-9;

typedef complex<double> point;
typedef pair<point, point> line;

double distance(point p1, point p2) {
    return sqrtl(powl(p1.X - p2.X, 2) + powl(p1.Y - p2.Y, 2));
}

point rotate(point p, double angle) {
    return point(cosl(angle) * p.X - sinl(angle) * p.Y, sinl(angle) * p.X + cosl(angle) * p.Y);
}

double det(point a, point b) {return (conj(a) * b).Y; }

pair<bool, point> intersecting(line l1, line l2) {
    point ab = l1.second - l1.first;
    point qp = l2.first - l2.second;
    point ap = l2.first - l1.first;
    double d = det(ab, qp);
    if (d == 0) {
        if ((abs(l1.first - l2.first) < EPS) || (abs(l1.first - l2.second) < EPS)) {
            return {true, l1.first};
        }
        return {false, point()};
    }
    double s = det(ap, qp)/d, t=det(ab, ap)/d;
    if (-EPS<s && s<1+EPS && -EPS<t && t<1+EPS) return {true, l1.first + s * ab};
    return {false, point()};
}

struct Circle {
    point centre;
    double radius;

    Circle(int x, int y, int r): centre(x, y), radius(r) {}
    vector<line> tangents(Circle other) {
        // Get the tangent lines with another circle.
        // There are two types, internal and external.
        vector<line> res;
        // EXTERNAL: Calculate required angle.
        double dist = distance(centre, other.centre);
        double angle = acosl(abs(radius - other.radius) / dist);
        point edge1 = (other.centre - centre) * (radius / dist);
        point edge2 = (centre - other.centre) * (other.radius / dist);
        if (radius > other.radius) {
            res.push_back(line(
                centre + rotate(edge1, angle),
                other.centre + rotate(edge2, angle-pi)
            ));
            res.push_back(line(
                centre + rotate(edge1, -angle),
                other.centre + rotate(edge2, pi-angle)
            ));
        } else {
            res.push_back(line(
                other.centre + rotate(edge2, angle),
                centre + rotate(edge1, angle-pi)
            ));
            res.push_back(line(
                other.centre + rotate(edge2, -angle),
                centre + rotate(edge1, pi-angle)
            ));
        }
        // INTERNAL: Calculate required angle.
        angle = acosl((radius + other.radius) / dist);
        res.push_back(line(
            centre + rotate(edge1, angle),
            other.centre + rotate(edge2, angle)
        ));
        res.push_back(line(
            centre + rotate(edge1, -angle),
            other.centre + rotate(edge2, -angle)
        ));
        return res;
    }
    vector<line> tangents(point p) {
        double angle = acosl(radius/abs(centre - p));
        point edge = (p - centre);
        edge *= radius / abs(edge);
        vector<line> res;
        res.push_back(line(
            p, centre + rotate(edge, angle)
        ));
        res.push_back(line(
            p, centre + rotate(edge, -angle)
        ));
        return res;
    }
};

struct Graph {
    int n;
    vector<vector<int> > adj;
    vector<int> parent;

    Graph(int n): n(n), adj(n, vector<int>()), parent(n, -1) {}
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int BFS(vector<int> starts, vector<int> ends) {
        vector<int> searching;
        for (auto i: starts) {
            parent[i] = -2;
            searching.push_back(i);
        }
        while(searching.size()) {
            vector<int> new_searching;
            for (auto i: searching) {
                for (auto j: adj[i]) {
                    if (parent[j] == -1) {
                        parent[j] = i;
                        new_searching.push_back(j);
                    }
                }
            }
            searching = new_searching;
            for (auto e: ends) {
                if (parent[e] == -2) return e;
                if (parent[e] != -1) return e;
            }
        }
        return -1;
    }
};

pair<bool, line> extendLine(vector<Circle> circles, line l, int e1, int e2, double xl, double xr, double yl, double yr) {
    for (int i=0; i<circles.size(); i++) {
        if (i == e1 || i == e2) continue;
        // Check the circle doesn't intersect with the starting line.
        point v = l.second - l.first;
        Circle a = circles[i];
        a.centre = (a.centre-l.first)/v;
        a.radius /= abs(v);
        if (a.radius+EPS<abs(a.centre.Y)) continue;
        double offsq=norm(a.radius) - norm(a.centre.Y), off;
        double x1 = a.centre.X + sqrtl(powl(a.radius, 2) + powl(a.centre.Y, 2));
        double x2 = a.centre.X - sqrtl(powl(a.radius, 2) + powl(a.centre.Y, 2));
        if ((-EPS < x1 && x1 < 1 + EPS) || (-EPS < x2 && x2 < 1 + EPS)) return {false, line()};
    }
    // Now we can try to extrapolate.
    point midpoint = (l.first + l.second) / (double)2;
    point vec = (l.second - l.first);
    vec /= abs(vec);
    line new_line = l;
    if (l.first.X > l.second.X) {
        // Try moving l.second to xl, and l.first to xr.
        point tf = l.first - vec * (xr - l.first.X) / abs(vec.X);
        if (yl <= tf.Y && tf.Y <= yr) new_line.first = tf;
        point ts = l.second - vec * (xl - l.second.X) / abs(vec.X);
        if (yl <= ts.Y && ts.Y <= yr) new_line.second = ts;
    } else {
        point tf = l.first + vec * (xl - l.first.X) / abs(vec.X);
        if (yl <= tf.Y && tf.Y <= yr) new_line.first = tf;
        point ts = l.second + vec * (xr - l.second.X) / abs(vec.X);
        if (yl <= ts.Y && ts.Y <= yr) new_line.second = ts;
    } if (l.first.Y > l.second.Y) {
        // Try moving l.second to yl, and l.first to yr.
        point tf = l.first - vec * (yr - l.first.Y) / abs(vec.Y);
        if (xl <= tf.X && tf.X <= xr) new_line.first = tf;
        point ts = l.second - vec * (yl - l.second.Y) / abs(vec.Y);
        if (xl <= ts.X && ts.X <= xr) new_line.second = ts;
    } else {
        point tf = l.first + vec * (yl - l.first.Y) / abs(vec.Y);
        if (xl <= tf.X && tf.X <= xr) new_line.first = tf;
        point ts = l.second + vec * (yr - l.second.Y) / abs(vec.Y);
        if (xl <= ts.X && ts.X <= xr) new_line.second = ts;
    }
    //cerr << new_line.first << " " << new_line.second << endl;
    // Now we shorten the line on intersections
    for (int i=0; i<circles.size(); i++) {
        if (i == e1 || i == e2) continue;
        // Check the circle doesn't intersect with the starting line.
        point v = new_line.second - new_line.first;
        Circle a = circles[i];
        a.centre = (a.centre-new_line.first)/v;
        a.radius /= abs(v);
        if (a.radius+EPS<abs(a.centre.Y)) continue;
        double offsq=norm(a.radius) - norm(a.centre.Y), off;
        // Find the intersection point closest to midpoint, if it exists.
        double x1 = a.centre.X + sqrtl(powl(a.radius, 2) + powl(a.centre.Y, 2));
        double x2 = a.centre.X - sqrtl(powl(a.radius, 2) + powl(a.centre.Y, 2));
        // Translate back into real space
        point end1 = x1 * v + new_line.first;
        point end2 = x2 * v + new_line.first;
        if (-EPS < x1 && x1 < 1 + EPS) {
            // way more duped than it needs to be but eh.
            if (end1.X > midpoint.X + EPS) {
                if (new_line.first.X + EPS < new_line.second.X) {
                    if (end1.X < new_line.second.X + EPS) new_line.second = end1;
                } else {
                    if (end1.X < new_line.first.X + EPS) new_line.first = end1;
                }
            } else if (end1.X < midpoint.X - EPS) {
                if (new_line.first.X + EPS < new_line.second.X) {
                    if (end1.X > new_line.first.X - EPS) new_line.first = end1;
                } else {
                    if (end1.X > new_line.second.X - EPS) new_line.second = end1;
                }
            }
            if (end1.Y > midpoint.Y + EPS) {
                if (new_line.first.Y + EPS < new_line.second.Y) {
                    if (end1.Y < new_line.second.Y + EPS) new_line.second = end1;
                } else {
                    if (end1.Y < new_line.first.Y + EPS) new_line.first = end1;
                }
            } else if (end1.Y < midpoint.Y - EPS) {
                if (new_line.first.Y + EPS < new_line.second.Y) {
                    if (end1.Y > new_line.first.Y - EPS) new_line.first = end1;
                } else {
                    if (end1.Y > new_line.second.Y - EPS) new_line.second = end1;
                }
            }
        }
        if (-EPS < x2 && x2 < 1 + EPS) {
            // way more duped than it needs to be but eh.
            if (end2.X > midpoint.X + EPS) {
                if (new_line.first.X + EPS < new_line.second.X) {
                    if (end2.X < new_line.second.X + EPS) new_line.second = end2;
                } else {
                    if (end2.X < new_line.first.X + EPS) new_line.first = end2;
                }
            } else if (end2.X < midpoint.X - EPS) {
                if (new_line.first.X + EPS < new_line.second.X) {
                    if (end2.X > new_line.first.X - EPS) new_line.first = end2;
                } else {
                    if (end2.X > new_line.second.X - EPS) new_line.second = end2;
                }
            }
            if (end2.Y > midpoint.Y + EPS) {
                if (new_line.first.Y + EPS < new_line.second.Y) {
                    if (end2.Y < new_line.second.Y + EPS) new_line.second = end2;
                } else {
                    if (end2.Y < new_line.first.Y + EPS) new_line.first = end2;
                }
            } else if (end2.Y < midpoint.Y - EPS) {
                if (new_line.first.Y + EPS < new_line.second.Y) {
                    if (end2.Y > new_line.first.Y - EPS) new_line.first = end2;
                } else {
                    if (end2.Y > new_line.second.Y - EPS) new_line.second = end2;
                }
            }
        }
    }
    return {true, new_line};
}

int main() {

    int n, xl, xr, yl, yr;
    cin >> n >> xl >> yl >> xr >> yr;

    point start, end;
    double a, b;
    cin >> a >> b;
    start = {a, b};
    cin >> a >> b;
    end = {a, b};

    vector<Circle> sensors;

    for (int i=0; i<n; i++) {
        int x, y, r;
        cin >> x >> y >> r;
        sensors.emplace_back(x, y, r);
    }

    vector<line> all_lines;
    for (int i=0; i<n; i++) {
        for (int j=i+1; j<n; j++) {
            // cerr << "Tangents between " << i << " and " << j << endl;
            vector<line> tangents = sensors[i].tangents(sensors[j]);
            for (auto l: tangents) {
                pair<bool, line> extended = extendLine(sensors, l, i, j, xl, xr, yl, yr);
                if (extended.first) {
                    all_lines.push_back(extended.second);
                    // cerr << "Kept " << extended.second.first.X << " " << extended.second.first.Y << " to " << extended.second.second.X << " " << extended.second.second.Y << endl;
                } else {
                    // cerr << "Disregarded " << l.first.X << " " << l.first.Y << " to " << l.second.X << " " << l.second.Y << endl;
                }
            }
        }
    }

    vector<int> start_points;
    vector<int> end_points;

    // Add perimeter lines
    all_lines.push_back(line(point(xl, yl), point(xl, yr)));
    all_lines.push_back(line(point(xl, yl), point(xr, yl)));
    all_lines.push_back(line(point(xr, yr), point(xl, yr)));
    all_lines.push_back(line(point(xr, yr), point(xr, yl)));

    // Now all_lines is the max possible for each tangent. We need to also include tangent lines from start and end points.
    for (int i=0; i<n; i++) {
        // cerr << i << endl;
        vector<line> tangents1 = sensors[i].tangents(start);
        vector<line> tangents2 = sensors[i].tangents(end);
        for (auto l: tangents1) {
            pair<bool, line> extended = extendLine(sensors, l, i, -1, xl, xr, yl, yr);
            if (extended.first) {
                start_points.push_back(all_lines.size());
                all_lines.push_back(extended.second);
                // cerr << "Kept " << extended.second.first.X << " " << extended.second.first.Y << " to " << extended.second.second.X << " " << extended.second.second.Y << endl;
            } else {
                // cerr << "Disregarded " << l.first.X << " " << l.first.Y << " to " << l.second.X << " " << l.second.Y << endl;
            }
        }
        for (auto l: tangents2) {
            pair<bool, line> extended = extendLine(sensors, l, i, -1, xl, xr, yl, yr);
            if (extended.first) {
                end_points.push_back(all_lines.size());
                all_lines.push_back(extended.second);
                // cerr << "Kept " << extended.second.first.X << " " << extended.second.first.Y << " to " << extended.second.second.X << " " << extended.second.second.Y << endl;
            } else {
                // cerr << "Disregarded " << l.first.X << " " << l.first.Y << " to " << l.second.X << " " << l.second.Y << endl;
            }
        }
    }

    Graph search(all_lines.size());

    for (int i=0; i<all_lines.size(); i++) {
        for (int j=i; j<all_lines.size(); j++) {
            // Does line i and line j intersect? add an edge.
            if (intersecting(all_lines[i], all_lines[j]).first) {
                search.add_edge(i, j);
            }
        }
    }

    int final = search.BFS(start_points, end_points);
    if (final == -1) {
        cout << 0 << endl;
    } else {
        vector<line> path;
        while (1) {
            path.insert(path.begin(), all_lines[final]);
            final = search.parent[final];
            if (final == -2) {
                break;
            }
        }
        vector<point> points;
        for (int i=0; i<path.size()-1; i++) {
            point p = intersecting(path[i], path[i+1]).second;
            if (
                (
                    (points.size() == 0) ||
                    (
                        abs(points[points.size()-1].X - p.X) > EPS ||
                        abs(points[points.size()-1].Y - p.Y) > EPS
                    )
                ) && (
                    abs(start.X - p.X) > EPS ||
                    abs(start.Y - p.Y) > EPS
                ) && (
                    abs(end.X - p.X) > EPS ||
                    abs(end.Y - p.Y) > EPS
                )
            ) points.push_back(p);
        }
        cout << points.size() << endl;
        for (int i=0; i<points.size(); i++) {
            cout << std::setprecision(16) << points[i].X << " " << points[i].Y << endl;
        }
    }

    return 0;
}
