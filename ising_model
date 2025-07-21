import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Parameters
N = 25
J = 1
S_up = 1
T = 1000  # Reduced for speed
Nn = (2 * N + 1) ** 2

# Build the square lattice and index map
R = []
index_map = {}
idx = 0
for i in range(-N, N + 1):
    for j in range(-N, N + 1):
        R.append((i, j))
        index_map[(i, j)] = idx
        idx += 1
R = np.array(R)

# Temperature range
kBT_values = np.arange(1, 2.1, 0.2)
chi_values = []

for k_BT in kBT_values:
    S = S_up * np.ones(Nn)
    M = np.zeros(T)

    for k in range(T):
        idx = np.random.randint(Nn)
        i, j = R[idx]

        # Periodic neighbors
        i_up = ((i + N + 1) % (2 * N + 1)) - N
        i_down = ((i + N - 1) % (2 * N + 1)) - N
        j_right = ((j + N + 1) % (2 * N + 1)) - N
        j_left = ((j + N - 1) % (2 * N + 1)) - N

        idx_up = index_map[(i_up, j)]
        idx_down = index_map[(i_down, j)]
        idx_right = index_map[(i, j_right)]
        idx_left = index_map[(i, j_left)]

        # Energy variation
        delta_E = 2 * J * S[idx] * (S[idx_up] + S[idx_down] + S[idx_right] + S[idx_left])

        # Metropolis criterion
        if delta_E <= 0 or np.random.rand() < np.exp(-delta_E / k_BT):
            S[idx] = -S[idx]

        M[k] = np.sum(S) / Nn

    M_half = M[T // 2:]
    M_mean = np.mean(M_half)
    M2_mean = np.mean(M_half ** 2)
    chi = (1 / k_BT) * (M2_mean - M_mean ** 2)
    chi_values.append(chi)

    print(f"k_BT = {k_BT:.2f} --> Magnetic susceptibility = {chi:.4f}")

# Plot magnetic susceptibility
plt.figure()
plt.plot(kBT_values, chi_values, '-o', linewidth=2)
plt.xlabel("k_B T")
plt.ylabel("Susceptibility χ")
plt.title("Magnetic Susceptibility vs Temperature")
plt.grid(True)

# Final spin configuration
plt.figure()
plt.imshow(S.reshape((2 * N + 1, 2 * N + 1)), cmap='gray')
plt.title("Final Spin Configuration")

# Magnetization over time
plt.figure()
plt.plot(range(T), M, 'b')
plt.xlabel("Iterations")
plt.ylabel("Magnetization")
plt.title("Magnetization Over Time")

# Theoretical Curie temperature and comparison
Tc = 2 / np.log(1 + np.sqrt(2))
print(f"Theoretical Curie temperature: {Tc:.4f}")

T_values = np.linspace(1, 4, 100)
M_theo = np.zeros_like(T_values)
for i, T_val in enumerate(T_values):
    if T_val <= Tc:
        M_theo[i] = (1 - 1 / np.sinh(2 / T_val) ** 4) ** (1 / 8)
    else:
        M_theo[i] = 0

plt.figure()
plt.plot(T_values, M_theo, linewidth=2)
plt.xlabel("T")
plt.ylabel("M(T)")
plt.title("Theoretical Magnetization vs Temperature")
plt.grid(True)

# 3D spin visualization
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_title("3D Spin Visualization")
ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_zlabel("Spin")

x = R[:, 0]
y = R[:, 1]
z = np.zeros_like(S)

for i in range(Nn):
    color = 'r' if S[i] == 1 else 'b'
    ax.quiver(x[i], y[i], z[i], 0, 0, S[i], color=color, length=0.6, normalize=True)

plt.show()
