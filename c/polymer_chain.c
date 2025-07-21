#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define B 3.0       // Segment length
#define N 10        // Number of segments
#define T 1000      // Number of conformations
#define NB_BINS 50  // Number of bins for histogram

// Function to generate a random point in a sphere
void random_vector_in_sphere(double *x, double *y, double *z) {
    double dx, dy, dz, norm2;
    do {
        dx = (2.0 * rand() / RAND_MAX - 1.0);
        dy = (2.0 * rand() / RAND_MAX - 1.0);
        dz = (2.0 * rand() / RAND_MAX - 1.0);
        norm2 = dx * dx + dy * dy + dz * dz;
    } while (norm2 > 1.0);
    *x = B * dx;
    *y = B * dy;
    *z = B * dz;
}

int main() {
    srand(time(NULL));
    double R[N + 1][3];
    double Q[T];
    double QA_squared = 0.0;
    double QA_theoretical = N * B * B;

    FILE *fp = fopen("polymere.xyz", "w");

    for (int t = 0; t < T; t++) {
        R[0][0] = 0.0; R[0][1] = 0.0; R[0][2] = 0.0;

        for (int i = 1; i <= N; i++) {
            double vx, vy, vz;
            random_vector_in_sphere(&vx, &vy, &vz);
            R[i][0] = R[i - 1][0] + vx;
            R[i][1] = R[i - 1][1] + vy;
            R[i][2] = R[i - 1][2] + vz;
        }

        double dx = R[N][0] - R[0][0];
        double dy = R[N][1] - R[0][1];
        double dz = R[N][2] - R[0][2];
        Q[t] = sqrt(dx * dx + dy * dy + dz * dz);
        QA_squared += Q[t] * Q[t];

        // Write .xyz file for visualization
        fprintf(fp, "%d\n", N + 1);
        fprintf(fp, "Conformation %d\n", t + 1);
        for (int i = 0; i <= N; i++) {
            fprintf(fp, "C %8.3f %8.3f %8.3f\n", R[i][0], R[i][1], R[i][2]);
        }
    }

    fclose(fp);

    QA_squared /= T;

    printf("Average Q² = %.3f\n", QA_squared);
    printf("Theoretical Q² = %.3f\n", QA_theoretical);

    // Histogram of Q
    double Qmin = Q[0], Qmax = Q[0];
    for (int i = 1; i < T; i++) {
        if (Q[i] < Qmin) Qmin = Q[i];
        if (Q[i] > Qmax) Qmax = Q[i];
    }

    double bin_width = (Qmax - Qmin) / NB_BINS;
    int hist[NB_BINS] = {0};

    for (int i = 0; i < T; i++) {
        int bin = (int)((Q[i] - Qmin) / bin_width);
        if (bin >= NB_BINS) bin = NB_BINS - 1;
        hist[bin]++;
    }

    printf("\nHistogram (bin center | probability):\n");
    for (int i = 0; i < NB_BINS; i++) {
        double center = Qmin + (i + 0.5) * bin_width;
        double prob = (double)hist[i] / T;
        printf("%6.2f | %.4f\n", center, prob);
    }

    return 0;
}
