#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

int main() {
    const int N = 25;
    const int Nn = (2 * N + 1) * (2 * N + 1);
    const int T = 100000;
    const double J = 1.0;
    const double k_BT = 1.0;

    vector<int> S(Nn);
    vector<int> X(Nn), Y(Nn);
    vector<double> M(T, 0.0);

    // Initialisation aléatoire des spins à ±1
    srand(time(0));
    for (int idx = 0, i = -N; i <= N; ++i) {
        for (int j = -N; j <= N; ++j, ++idx) {
            X[idx] = i;
            Y[idx] = j;
            S[idx] = (rand() % 2 == 0) ? 1 : -1;
        }
    }

    for (int k = 0; k < T; ++k) {
        int idx = rand() % Nn;
        int i = X[idx];
        int j = Y[idx];

        auto wrap = [&](int val) {
            return (val > N) ? -N : (val < -N) ? N : val;
        };

        int iu = wrap(i + 1), id = wrap(i - 1);
        int jr = wrap(j + 1), jl = wrap(j - 1);

        int idx_up = -1, idx_down = -1, idx_right = -1, idx_left = -1;

        for (int n = 0; n < Nn; ++n) {
            if (X[n] == iu && Y[n] == j) idx_up = n;
            if (X[n] == id && Y[n] == j) idx_down = n;
            if (X[n] == i && Y[n] == jr) idx_right = n;
            if (X[n] == i && Y[n] == jl) idx_left = n;
        }

        int Delta_E = 2 * J * S[idx] * (S[idx_up] + S[idx_down] + S[idx_right] + S[idx_left]);

        if (Delta_E <= 0 || (rand() / (double)RAND_MAX) < exp(-Delta_E / k_BT)) {
            S[idx] *= -1;
        }

        int sumM = 0;
        for (int s : S) sumM += s;
        M[k] = sumM / (double)Nn;
    }

    // Sauvegarde de l'évolution de la magnétisation
    ofstream file("magnetization.csv");
    for (int k = 0; k < T; ++k)
        file << k << "," << M[k] << "\n";
    file.close();

    cout << "Simulation done. Data saved to magnetization.csv.\n";
    return 0;
}
