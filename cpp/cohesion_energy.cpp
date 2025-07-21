#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

// Constants
const double pi = 3.14159265358979323846;
const double pm = 2.47;
const int N = 15;
const double A = 15.2;   // eV
const double B = 24100;
const string atom_name = "C";

// Generate lattice vectors
const double d = pm / (2 * cos(pi / 6)); // interatomic distance
const double D = sqrt(3.0 / 4.0) * d;    // distance hole–bridge
const double a[3] = {pm, 0, 0};
const double b[3] = {pm * cos(pi / 3), pm * sin(pi / 3), 0};

// Energy parameters
const double Z_H_min = 2.8;
const double Z_H_max = 6.8;
const double step = 0.01;

// Build graphene lattice
vector<vector<double>> generate_lattice() {
    vector<vector<double>> R;
    vector<double> motif1 = {0, 0, 0};
    vector<double> motif2 = {pm / 2, pm / 2 * tan(pi / 6), 0};

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= N; ++j) {
            vector<double> r1 = {
                i * a[0] + j * b[0] + motif1[0],
                i * a[1] + j * b[1] + motif1[1],
                motif1[2]
            };
            vector<double> r2 = {
                i * a[0] + j * b[0] + motif2[0],
                i * a[1] + j * b[1] + motif2[1],
                motif2[2]
            };
            R.push_back(r1);
            R.push_back(r2);
        }
    }
    return R;
}

// Export XYZ file
void export_xyz(const vector<vector<double>>& R, const string& filename) {
    ofstream file(filename);
    file << R.size() << "\nGraphene\n";
    for (const auto& atom : R) {
        file << atom_name << " "
             << fixed << setprecision(3)
             << atom[0] << " " << atom[1] << " " << atom[2] << "\n";
    }
    file.close();
}

// Lennard-Jones potential
double LJ(double R) {
    return B / pow(R, 12) - A / pow(R, 6);
}

// Compute potential V(z) above a site (X0, Y0)
vector<double> compute_Vz(const vector<vector<double>>& R, double X0, double Y0, const vector<double>& Z_vals) {
    vector<double> V(Z_vals.size(), 0.0);
    for (size_t j = 0; j < Z_vals.size(); ++j) {
        double Z = Z_vals[j];
        for (const auto& atom : R) {
            double dx = X0 - atom[0];
            double dy = Y0 - atom[1];
            double dz = Z;
            double r = sqrt(dx * dx + dy * dy + dz * dz);
            V[j] += LJ(r);
        }
    }
    return V;
}

int main() {
    // Build lattice and export
    auto R = generate_lattice();
    export_xyz(R, "graphene.xyz");

    // Get Xs and Ys
    vector<double> X_s, Y_s;
    for (const auto& atom : R) {
        X_s.push_back(atom[0]);
        Y_s.push_back(atom[1]);
    }

    // Adsorption sites
    double X_H = *max_element(X_s.begin(), X_s.end()) / 2.0;
    double Y_H = *max_element(Y_s.begin(), Y_s.end()) / 2.0;
    double X_T = X_H;
    double Y_T = Y_H + d;
    double X_B = X_H + D;
    double Y_B = Y_H;

    // Discretize Z
    vector<double> Z_vals;
    for (double z = Z_H_min; z <= Z_H_max; z += step) {
        Z_vals.push_back(z);
    }

    // Compute and print interaction profiles
    vector<double> V_H = compute_Vz(R, X_H, Y_H, Z_vals);
    vector<double> V_B = compute_Vz(R, X_B, Y_B, Z_vals);
    vector<double> V_T = compute_Vz(R, X_T, Y_T, Z_vals);

    ofstream out("V_z_profiles.csv");
    out << "Z,V_H,V_B,V_T\n";
    for (size_t i = 0; i < Z_vals.size(); ++i) {
        out << Z_vals[i] << "," << V_H[i] << "," << V_B[i] << "," << V_T[i] << "\n";
    }
    out.close();

    cout << "✅ XYZ and potential profiles generated.\n";
    return 0;
}
