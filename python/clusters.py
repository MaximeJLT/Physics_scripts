import numpy as np
import matplotlib.pyplot as plt
import os

# Create snapshots directory
os.makedirs("snapshots", exist_ok=True)

# Parameters
N = 25
J = 1
k_BT = 1
T = 100000
M = np.zeros(T)

# Lattice setup
l = 2.866
a1 = np.array([l, 0])
a2 = np.array([l * np.cos(np.deg2rad(90)), l * np.sin(np.deg2rad(90))])
Nn = (2 * N + 1) ** 2

R = np.zeros((Nn, 2), dtype=int)
index = 0
for i in range(-N, N + 1):
    for j in range(-N, N + 1):
        R[index] = [i, j]
        index += 1

# Random initial spins ±1
S = np.sign(np.random.rand(Nn) - 0.5)

# Display setup
plt.ion()
fig, ax = plt.subplots()
im = ax.imshow(S.reshape((2 * N + 1, 2 * N + 1)), cmap='gray', vmin=-1, vmax=1)
plt.title("Spin configuration")
plt.axis("square")

# Simulation
for t in range(T):
    idx = np.random.randint(Nn)
    i, j = R[idx]

    def wrap(x): return -N if x > N else N if x < -N else x

    i_up = wrap(i + 1)
    i_down = wrap(i - 1)
    j_right = wrap(j + 1)
    j_left = wrap(j - 1)

    idx_up = np.where((R[:, 0] == i_up) & (R[:, 1] == j))[0][0]
    idx_down = np.where((R[:, 0] == i_down) & (R[:, 1] == j))[0][0]
    idx_right = np.where((R[:, 0] == i) & (R[:, 1] == j_right))[0][0]
    idx_left = np.where((R[:, 0] == i) & (R[:, 1] == j_left))[0][0]

    delta_E = 2 * J * S[idx] * (S[idx_up] + S[idx_down] + S[idx_right] + S[idx_left])

    if delta_E <= 0 or np.random.rand() < np.exp(-delta_E / k_BT):
        S[idx] *= -1

    M[t] = np.mean(S)

    if t % 500 == 0:
        im.set_data(S.reshape((2 * N + 1, 2 * N + 1)))
        plt.draw()
        plt.pause(0.001)

    if t % 10000 == 0:
        plt.imsave(f'snapshots/ising_k{t:06d}.png', S.reshape((2 * N + 1, 2 * N + 1)), cmap='gray', vmin=-1, vmax=1)

plt.ioff()

# Final magnetization average
M_mean = np.mean(M[T//2:])
print(f"Average magnetization in second half: {M_mean:.3f}")

# Plot magnetization over time
plt.figure()
plt.plot(range(T), M, 'b')
plt.xlabel("Iteration")
plt.ylabel("Magnetization")
plt.title("Magnetization over time")
plt.grid()

# Theoretical magnetization
T_c = 2 / np.log(1 + np.sqrt(2))
print(f"Theoretical Curie temperature: {T_c:.3f}")

T_vals = np.linspace(1, 4, 100)
M_theo = np.zeros_like(T_vals)
for i, T_val in enumerate(T_vals):
    if T_val <= T_c:
        M_theo[i] = (1 - (1 / (np.sinh(2 / T_val)**4)))**(1 / 8)

# Plot theoretical magnetization
plt.figure()
plt.plot(T_vals, M_theo, linewidth=2)
plt.xlabel("T")
plt.ylabel("M(T)")
plt.title("Theoretical average magnetization")
plt.grid()
plt.show()
