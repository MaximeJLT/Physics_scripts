# Physics Script

This repository contains several physics simulations implemented in **MATLAB, Python, C, and C++**, covering core topics in statistical and condensed matter physics. Each simulation is assigned to a different language to demonstrate versatility and practical engineering skills in numerical methods.

---

## 🔬 Simulations included

## 📚 Table of Contents
- [1. Monte Carlo Simulation – 2D Ising Model (Python)](#1--monte-carlo-simulation--2d-ising-model-python)
- [2. Freely-Jointed Chain – Polymer Simulation (C)](#2--freely-jointed-chain--polymer-simulation-c)
- [3. Brownian Motion in 2D (MATLAB)](#3--brownian-motion-in-2d-matlab)
- [4. Cohesive Energy – Crystal Potentials (C++)](#4--cohesive-energy--crystal-structure--potentials-c)

### 1. 🧲 Monte Carlo Simulation – **2D Ising Model** (Python)
- Simulates ferromagnetic behavior on a 2D lattice using the Metropolis algorithm.
- Visualizes magnetization and critical behavior across temperatures.
- **Why Python?** Ideal for stochastic modeling, data visualization, and quantitative finance (e.g., option pricing, Gibbs sampling).

- It computes:
- Magnetization as a function of time
- Magnetic susceptibility as a function of temperature
- Theoretical magnetization curve
- 2D and 3D visualizations of the spin configuration

  ## 📚 Physical Background

  The Ising model describes a lattice of spins ( $$S_i = \pm 1 $$), interacting only with their nearest neighbors. The Hamiltonian is given by:

$$
\mathcal{H} = -J \sum_{\langle i,j \rangle} S_i S_j
$$

The system evolves using the **Metropolis algorithm**, where a spin flip is accepted with probability:

$$
P = 
\begin{cases}
1 & \text{if } \Delta E \leq 0 \\
e^{-\Delta E / k_B T} & \text{otherwise}
\end{cases}
$$

Key quantities:

- Magnetization:
  $$
  M = \frac{1}{N} \sum_i S_i
  $$
- Magnetic susceptibility:
  $$
  \chi = \frac{\langle M^2 \rangle - \langle M \rangle^2}{k_B T}
  $$

Theoretical magnetization below the Curie temperature $$( T_c )$$:

$$
M(T) = \left[1 - \sinh^{-4}\left( \frac{2J}{k_B T} \right) \right]^{1/8}, \quad \text{for } T < T_c
$$

Where ( $$T_c = \frac{2J}{\ln(1+\sqrt{2})} \approx 2.269$$ ).


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
  
 ### File location

This script is stored in:  
`physics_scripts/python/ising_model.py`
  
### ❄️ clusters.py

A 2D Ising model simulation at low temperature (`kBT = 1`) using the Metropolis algorithm. Spins are initialized randomly, and clusters emerge over time as the system minimizes energy. Snapshots are saved every 10,000 iterations to visualize cluster formation. Also includes theoretical magnetization comparison vs. temperature.

### Physical background

In the low-temperature regime (k_BT < T_c), spins tend to align, forming large clusters.
We simulate this using:
- Random spin flips accepted via the Metropolis criterion
- Periodic boundary conditions
- Magnetization M(t) and theoretical magnetization M(T) based on Onsager’s solution:

$$
M(T) = \left[1 - \sinh^{-4}(2J/k_BT) \right]^{1/8} \quad \text{for } T < T_c
$$

### Mathematical Definitions

...

- Theoretical magnetization \( M(T) \) (Onsager's solution):

  $$
  M(T) = \left[1 - \frac{1}{\sinh^4\left(\frac{2J}{k_B T}\right)}\right]^{\frac{1}{8}}, \quad \text{for } T < T_c
  $$

Where ( $$T_c = \frac{2J}{\ln(1+\sqrt{2})} \approx 2.269$$ ) is the theoretical Curie temperature for the 2D Ising model (Onsager's solution).

📁 Output folder: `snapshots/`
📈 Plots:
- Real-time spin evolution
- Time evolution of magnetization
- Theoretical magnetization curve (Onsager solution)

  ### File location

This script is stored in:  
`physics_scripts/python/cluster.py`
  
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

  ### File location

This script is stored in:  
`physics_scripts/c/polymer_chain.c`

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

  ## 📚 Physical Background

  The freely-jointed chain models a polymer as ( $$N$$ ) rigid segments of length ( $$b$$ ), randomly oriented in 3D. The end-to-end vector is:

$$
\vec{Q} = \sum_{i=1}^{N} \vec{b}_i
$$

And its mean squared length is:

$$
\langle Q^2 \rangle = N b^2
$$

Applications:
- Conformational statistics of polymers
- Entropic elasticity
- Monte Carlo sampling in statistical physics

The simulation verifies this relation numerically and compares it to the theoretical prediction.


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

 ### File location

This script is stored in:  
`physics_scripts/matlab/brownian_motion/brownian_motion.m`

## Constrained 2D Brownian Motion (MATLAB)

This script simulates a 2D Brownian motion with a constraint: the walker cannot move in the same direction in two consecutive steps. This adds memory to the process, breaking the Markovian assumption and introducing nontrivial correlations.

### Features

- **N = 3** walkers
- **T = 500** time steps
- 4 possible directions (up, down, left, right), chosen randomly but **not allowed to repeat immediately**
- Real-time visualization of trajectories
- Computation of the Mean Squared Displacement (MSD) for increasing lag τ
- Linear fit on MSD for small τ to estimate the diffusion coefficient

  ## 📚 Physical Background

  Here, the random walker **cannot repeat the same direction in two consecutive steps**. This introduces **temporal correlations** and breaks the Markov property.

MSD is computed as a function of lag $$( \tau )$$:

$$
\text{MSD}(\tau) = \frac{1}{T - \tau} \sum_{t=1}^{T - \tau} \left[ (X_{t+\tau} - X_t)^2 + (Y_{t+\tau} - Y_t)^2 \right]
$$

From the linear region of MSD(τ), the diffusion coefficient is estimated as:

$$
D = \frac{\text{slope}}{2d}
$$

with ( $$d = 2$$ ) the dimensionality of the system.

### Mathematical Definitions

- Let $$((X_t^i, Y_t^i))$$ be the position of walker $$(i)$$ at time $$(t)$$
- For a given walker, the MSD at lag \(\tau\) is computed as:

  
  $$\text{MSD}(\tau) = \frac{1}{T - \tau} \sum_{t=1}^{T - \tau} \left[ (X_{t+\tau} - X_t)^2 + (Y_{t+\tau} - Y_t)^2 \right]$$
  

- A linear fit is applied to the MSD for small τ values, and the diffusion coefficient is extracted via:

  
  $$D = \frac{\text{slope}}{2d}$$
  

  where $$(d = 2)$$ is the dimension of the motion.

### File location

This script is stored in:  
`physics_scripts/matlab/brownian_motion/Constrain.m`
  
---

### 4. 🧱 Cohesive Energy – **Crystal Structure & Potentials** (C++)
- Calculates the Lennard-Jones potential between an atom and a graphene sheet.
- Extracts equilibrium distance and energy profile over surface sites.
- **Why C++?** Best suited for multi-layered numerical computation with structured data and optimization loops. Relevant to R&D and molecular modeling.

  ## 📚 Physical Background

  This script evaluates the interaction between an atom and a graphene surface using the Lennard-Jones potential:

$$
V(r) = 4\epsilon \left[ \left( \frac{\sigma}{r} \right)^{12} - \left( \frac{\sigma}{r} \right)^6 \right]
$$

The script:
- Constructs a graphene-like lattice
- Evaluates $$( V(z) )$$ above adsorption sites (Top, Bridge, Hollow)
- Computes and plots the cohesive energy profile

This method is widely used in:
- Molecular dynamics
- Surface science
- Adsorption studies

  

- ## Outputs
- `graphene.xyz`: 3D lattice for visualization
- `V_z_profiles.csv`: Energy vs Z for each site

## Methods
- Lattice generation with two atoms per cell
- Lennard-Jones potential with 12-6 parameters
- Z-scan above selected adsorption sites

 ### File location

This script is stored in:  
`physics_scripts/cpp/cohesion_energy.cpp`

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

## 🎯 Relevance to Quantitative Finance and Aerospace R&D

The simulations in this repository—ranging from Ising models and constrained Brownian motion to cohesive energy calculations—demonstrate the application of core methods in **statistical physics**, **stochastic processes**, and **numerical modeling**. These techniques are directly transferable to **quantitative finance**, where Monte Carlo methods, Brownian motion, and diffusion equations underpin option pricing, risk modeling, and market dynamics analysis. In parallel, the **cohesion energy simulation** and **polymer chain modeling** reflect key competencies required in **aerospace R&D**, especially in areas like material science, molecular dynamics, and instrument calibration in microgravity environments.

By developing these codes during my undergraduate studies in physics, I’ve laid a solid foundation for future work as a **quantitative researcher** or **space R&D engineer**, with the ability to adapt scientific computing skills across both high-tech and financial sectors.

---

## 📧 Contact

Created by **Maxime Jolliot**, engineering student at **ISAE-ENSMA**.  
Open to internships in **quantitative finance** and **space R&D** (2026).  
📩 maxime.jolliot@gmail.com
Linkedin : https://www.linkedin.com/in/maxime-jolliot-🚀-1a3183342/


