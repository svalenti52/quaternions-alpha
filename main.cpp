#include <cstdlib>
#include <iostream>
#include <boost/qvm/all.hpp>

using namespace std;
using namespace boost::qvm;

using qf = quat<float>;
using vf = vec<float, 3>;
using vf4 = vec<float, 4>;
using mf44 = mat<float, 4, 4>;

const float pi = 3.141593;
const float radians_per_degree = (2.0 * pi) / 360.0;

template <typename T>
void print_out(T &qvm_obj, const char *msg) {
    string qvm_obj_str = to_string(qvm_obj);
    cout << msg << qvm_obj_str << '\n';
}

/*
 *
 */
int main(int argc, char** argv) {

    // vectors to be rotated
    vf vx{ 2.0, 0.0, 0.0 };
    vf vy{ 0.0, 3.0, 0.0 };
    vf vz{ 0.0, 0.0, 4.0 };

    float theta(90.0f * radians_per_degree);

    // rotation matrices (3D)
    qf xrot, yrot, zrot;
    set_rotx(xrot, theta);
    set_roty(yrot, theta);
    set_rotz(zrot, theta);

    print_out(xrot, "quaternion xrot 90 deg = ");
    print_out(yrot, "quaternion yrot 90 deg = ");
    print_out(zrot, "quaternion zrot 90 deg = ");
    cout << '\n';

    vf rotxx = xrot * vx;
    vf rotxy = xrot * vy;
    vf rotxz = xrot * vz;

    print_out(vx, "original x-vector = ");
    print_out(rotxx, "rotated x-vector about x-axis (no change) = ");
    cout << "no change is correct\n\n";

    print_out(vy, "original y-vector = ");
    print_out(rotxy, "rotated y-vector about x-axis = ");
    cout << "positive y-vector changed into positive z-vector correct\n\n";

    print_out(vz, "original z-vector = ");
    print_out(rotxz, "rotated z-vector about x-axis = ");
    cout << "positive z-vector changed into negative y-vector correct\n\n";

    vf rotzy_z = zrot * yrot * vz;
    print_out(vz, "original z-vector");
    //string rotzy_z_str = to_string(rotzy_z);
    print_out(rotzy_z, "rotate about y axis then z axis = ");
    cout << "positive z-vector changed into positive y-vector correct\n\n";

    cout << "Spherical Linear Interpolation (SLERP) - half way\n";
    cout << "between x and y rotations.\n";
    qf slerp_res = slerp(xrot, yrot, 0.5);
    print_out(slerp_res, "slerp result = ");
    cout << '\n';

    vf xlat_v = { 1.0, 2.0, 3.0 };
    mf44 xlat_m = translation_mat(xlat_v);
    print_out(xlat_m, "xlat_m_str = ");
    vf4 vec4{ 2.0, 2.0, 2.0, 1.0 };
    vec4 = xlat_m * vec4;
    print_out(vec4, "vector 4 xlated = ");

    // use of mref
    float fmat[4][4];
    mref(fmat) = identity_mat<float, 4>();
    print_out(mref(fmat), "pod struct = ");

    return 0;
}
