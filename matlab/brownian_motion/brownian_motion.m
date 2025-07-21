clear all; close all; clc;

N = 1000;         % Number of simulations (walkers)
X_1 = 0;
Y_1 = 0;
T = 1000;         % Number of time steps
deltaX = 1;
deltaY = 1;
N_S = 4;          % Number of walkers shown in real-time display
d = 2;            % Dimension of the space

X = zeros(T, N);
Y = zeros(T, N);  % Position matrices (T time steps × N walkers)

% Generate random directions: 1 = right, 2 = left, 3 = up, 4 = down
directions = randi(4, T, N);

% Real-time plot setup
figure;
hold on;
plot(0, 0, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k');  % Origin marker
xlabel('X'); ylabel('Y');
title('2D Random Walk');
grid on; axis equal;

colors = rand(N, 3);  % Assign random colors to each walker

% Simulate the walk step by step
for t = 2:T
    X(t, :) = X(t-1, :);
    Y(t, :) = Y(t-1, :);

    X(t, directions(t, :) == 1) = X(t, directions(t, :) == 1) + deltaX;
    X(t, directions(t, :) == 2) = X(t, directions(t, :) == 2) - deltaX;
    Y(t, directions(t, :) == 3) = Y(t, directions(t, :) == 3) + deltaY;
    Y(t, directions(t, :) == 4) = Y(t, directions(t, :) == 4) - deltaY;

    for i = 1:N_S
        plot(X(1:t, i), Y(1:t, i), 'LineWidth', 1, 'Color', colors(i, :));
    end
    pause(0.0001);  % Real-time animation
end

% Final trajectory display
for i = 1:N_S
    plot(X(:, i), Y(:, i), 'LineWidth', 1, 'Color', colors(i, :));
    plot(X(end, i), Y(end, i), 'o', 'MarkerFaceColor', colors(i, :), ...
        'MarkerEdgeColor', colors(i, :), 'MarkerSize', 8);
end

% Histogram of distances after T steps
D = sqrt(X(T, :).^2 + Y(T, :).^2);
[H, edges] = histcounts(D, 1:100);
figure(2);
bar(edges(1:end-1), H);
xlabel('Distance from origin at final time T');
ylabel('Probability');
