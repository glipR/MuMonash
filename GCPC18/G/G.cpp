// MuMonash

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;
#define debug(a) cerr << #a << " = " << (a) << endl;

#define EARTH_RADIUS 6371
// Measured in km/s
#define SPEEDLIGHT 299792.458

void rotate_3d(long double theta, long double ux, long double uy, long double uz, long double p1, long double p2, long double p3, long double &n1, long double &n2, long double &n3) {
    long double ct = cos(theta);
    long double st = sin(theta);
    n1 = (
        p1 * (ct + powl(ux, 2) * (1 - ct)) +
        p2 * (ux * uy * (1 - ct) - uz * st) +
        p3 * (ux * uz * (1 - ct) + uy * st)
    );
    n2 = (
        p1 * (uy * ux * (1 - ct) + uz * st) +
        p2 * (ct + powl(uy, 2) * (1 - ct)) +
        p3 * (uy * uz * (1 - ct) - ux * st)
    );
    n3 = (
        p1 * (uz * ux * (1 - ct) - uy * st) +
        p2 * (uz * uy * (1 - ct) + ux * st) +
        p3 * (ct + powl(uz, 2) * (1 - ct))
    );
}

struct Satellite {
    long double ref_long, north_tilt, radius, portion;
    long double position[3];
    Satellite() {};

    void radiansify() {
        ref_long = ref_long * M_PI / (long double) 180;
        north_tilt = north_tilt * M_PI / (long double) 180;
    }

    void calculate_position() {
        if (radius == 0) {
            position[0] = 0;
            position[1] = 0;
            position[2] = 0;
            return;
        }
        // We assume 0, 0, 0 is the centre of the earth.
        // And longitude 0, latitude 0, position = [EARTH_RADIUS, 0, 0]
        // Find the starting position by rotating [r, 0, 0] long radians around [0, 0, 1]
        long double starting_pos[3];
        rotate_3d(ref_long, 0, 0, 1, radius, 0, 0, starting_pos[0], starting_pos[1], starting_pos[2]);
        // Generate the axis of rotation based on the radius and 2 angles.
        // Do this by rotating [0, 0, 1] w.r.t. our starting position (made into a unit vector)
        long double axis_of_rotation[3];
        rotate_3d(north_tilt, starting_pos[0] / radius, starting_pos[1] / radius, starting_pos[2] / radius, 0, 0, 1, axis_of_rotation[0], axis_of_rotation[1], axis_of_rotation[2]);
        // Now rotate starting pos around axis of rotation portion * 2pi radians.
        rotate_3d(portion * 2 * M_PI, axis_of_rotation[0], axis_of_rotation[1], axis_of_rotation[2], starting_pos[0], starting_pos[1], starting_pos[2], position[0], position[1], position[2]);
    }
};

double long euclid_dist(Satellite *s1, Satellite *s2) {
    return sqrtl(
        powl(s1->position[0] - s2->position[0], 2) +
        powl(s1->position[1] - s2->position[1], 2) +
        powl(s1->position[2] - s2->position[2], 2)
    );
}

int main() {

    // The centre of the earth has radius 0.
    // The rest doesn't matter
    Satellite centre;
    centre.radius = 0;
    centre.north_tilt = 0;
    centre.ref_long = 0;
    centre.portion = 0;
    centre.radiansify();
    centre.calculate_position();

    int num_satellites;
    cin >> num_satellites >> ws;

    Satellite satellites[num_satellites];

    long double longitude, latitude;
    cin >> longitude >> latitude >> ws;
    // We are a satellite, with ref_long = longitude, north_tilt = 90 degrees, radius = EARTH_RADIUS, portion = latitiude / 180
    // Enjoy that mindfuck haha
    Satellite me;
    me.ref_long = longitude;
    me.north_tilt = 90;
    me.radius = EARTH_RADIUS;
    me.portion = latitude / (long double)360;
    me.radiansify();
    me.calculate_position();

    // cerr << me.position[0] << ' ' << me.position[1] << ' ' << me.position[2] << endl;

    for (int i=0; i<num_satellites; i++) {
        cin >> satellites[i].ref_long >> satellites[i].north_tilt >> satellites[i].radius >> satellites[i].portion >> ws;
        satellites[i].radiansify();
        satellites[i].calculate_position();
        // The distance between and satellite and me should be less than
        // sqrt(|sat - earth|^2 + EARTH_RADIUS^2)
        // If we can see eachother!

        double long km_dist = euclid_dist(&me, &satellites[i]);
        double long longest_sat_dist = sqrtl(
            powl(euclid_dist(&centre, &satellites[i]), 2) -
            powl(EARTH_RADIUS, 2)
        );

        if (km_dist <= longest_sat_dist) {
            cout << fixed << setprecision(10) << km_dist / (long double) SPEEDLIGHT << endl;
        } else {
            cout << "no signal" << endl;
        }
    }

    return 0;
}
