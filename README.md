# Physics Script

This repository contains several physics simulations implemented in **MATLAB, Python, C, and C++**, covering core topics in statistical and condensed matter physics. Each simulation is assigned to a different language to demonstrate versatility and practical engineering skills in numerical methods.

---

## 🔬 Simulations included

### 1. 🧲 Monte Carlo Simulation – **2D Ising Model** (Python)
- Simulates ferromagnetic behavior on a 2D lattice using the Metropolis algorithm.
- Visualizes magnetization and critical behavior across temperatures.
- **Why Python?** Ideal for stochastic modeling, data visualization, and quantitative finance (e.g., option pricing, Gibbs sampling).

- It computes:
- Magnetization as a function of time
- Magnetic susceptibility as a function of temperature
- Theoretical magnetization curve
- 2D and 3D visualizations of the spin configuration

## Steps of the simulation

1. **Lattice creation**: A (2N + 1)² grid with periodic boundary conditions
2. **Initialization**: All spins set to +1 (up state)
3. **Monte Carlo loop**:
   - Randomly select a spin
   - Compute ΔE with nearest neighbors
   - Flip spin based on Metropolis acceptance rule
4. **Observables**:
   - Magnetization (M)
   - Magnetic susceptibility (χ)
5. **Plots**:
   - χ vs k_BT
   - Magnetization over time
   - Final 2D spin configuration
   - Theoretical M(T) curve
   - 3D spin arrow visualization
  
### ❄️ ising_clusters.py

A 2D Ising model simulation at low temperature (`kBT = 1`) using the Metropolis algorithm. Spins are initialized randomly, and clusters emerge over time as the system minimizes energy. Snapshots are saved every 10,000 iterations to visualize cluster formation. Also includes theoretical magnetization comparison vs. temperature.

📁 Output folder: `snapshots/`
📈 Plots:
- Real-time spin evolution
- Time evolution of magnetization
- Theoretical magnetization curve (Onsager solution)
  
---

### 2. 🧵 Freely-Jointed Chain – **Polymer Simulation** (C)
- Models a 2D random walk with directional constraints (no immediate reversal).
- Computes distance distributions and diffusion properties.
- **Why C?** Lightweight, fast, and perfectly suited for simple random walk mechanics and efficient memory control.

- ## Features

- Random generation of 3D segment vectors within a sphere of radius `b`
- Generation of `T` independent polymer conformations
- Calculation of the end-to-end distance for each conformation
- Export to `.xyz` file for visualization in VMD or PyMOL
- Histogram of end-to-end distances

## Output

- `polymere.xyz`: All conformations for visualization
- Printed:
  - Average end-to-end distance ⟨Q²⟩
  - Theoretical value for comparison
  - Histogram of `Q` over `T` conformations

## Applications

Useful for:
- Polymer physics and molecular simulations
- Monte Carlo methods and conformational sampling
- Developing statistical mechanics intuition

---

### 3. 🟢 **Brownian Motion** in 2D (MATLAB)
- Simulates thousands of independent walkers and visualizes their trajectories.
- Calculates probability distributions and mean square displacement over time.
- **Why MATLAB?** Excellent for matrix operations and scientific visualization; ideal for clear plots and quick prototyping.

- ## Key features

- Uniform random walk in 4 directions (up, down, left, right)
- Real-time animated trajectories of several walkers
- Final plot of displacement distribution from the origin
- Clean 2D visualization of motion patterns

## Main steps

1. Initialize all walkers at the origin (0, 0)
2. At each time step, move randomly in one of 4 directions
3. Track and plot the positions of `N_S` walkers in real time
4. Compute final distance from the origin and display histogram

## Output

- **Live 2D trajectories** of selected walkers
- **Final trajectories** with colored markers
- **Histogram** of end-to-end distances after `T` steps

## Relevance

This project illustrates:
- Brownian motion in discrete space
- Core concepts in statistical physics and diffusion
- Skills in real-time plotting and vectorized simulation

Applicable in:
- Statistical modeling
- Quantitative finance (random walk hypotheses)
- Physics education and numerical methods
  
---

### 4. 🧱 Cohesive Energy – **Crystal Structure & Potentials** (C++)
- Calculates the Lennard-Jones potential between an atom and a graphene sheet.
- Extracts equilibrium distance and energy profile over surface sites.
- **Why C++?** Best suited for multi-layered numerical computation with structured data and optimization loops. Relevant to R&D and molecular modeling.

- ## Outputs
- `graphene.xyz`: 3D lattice for visualization
- `V_z_profiles.csv`: Energy vs Z for each site

## Methods
- Lattice generation with two atoms per cell
- Lennard-Jones potential with 12-6 parameters
- Z-scan above selected adsorption sites

---

## 🛠️ Why this matters

These projects reflect practical skills in:
- **Monte Carlo methods** & probability (Ising)
- **Stochastic modeling** & diffusion (Brownian motion)
- **Lattice simulation** & chain modeling (Polymer)
- **Energy optimization** & physical potentials (Crystals)

➡️ Highly relevant to:
- **Quantitative finance** (Monte Carlo pricing, Brownian-based models)
- **Aerospace & materials R&D** (atomistic modeling, diffusion, simulation)

---

## 📧 Contact

Created by **Maxime Jolliot**, engineering student at **ISAE-ENSMA**.  
Open to internships in **quantitative finance** and **space R&D** (2026).  
📩 maxime.jolliot@gmail.com
Linkedin : https://www.linkedin.com/in/maxime-jolliot-🚀-1a3183342/


