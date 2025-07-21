clear all; close all; clc;

N = 3; % Nombre de simulations
T = 500; % Nombre de pas
deltaX = 1;
deltaY = 1;
d = 2;

X = zeros(T, N);
Y = zeros(T, N);

prev_direction = randi(4, 1, N); % Initialiser une direction aléatoire au départ

% Couleurs pour affichage
colors = rand(N, 3);

figure;
hold on;
plot(0, 0, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k'); % Origine
xlabel('X'); ylabel('Y');
title('Marche Aléatoire 2D sans double mouvement consécutif');
grid on; axis equal;

for t = 2:T  
    X(t, :) = X(t-1, :);
    Y(t, :) = Y(t-1, :); % On initialise à la position précédente
    
    % Générer une nouvelle direction différente de la précédente
    directions(t, :) = randi(4, 1, N);

    while any(directions(t, :) == directions(t-1, :)) 
        directions(t, directions(t, :) == directions(t-1, :)) = ...
            randi(4, 1, sum(directions(t, :) == directions(t-1, :)));
    end

    % Mise à jour de la position selon la direction
    X(t, directions(t, :) == 1) = X(t, directions(t, :) == 1) + deltaX;
    X(t, directions(t, :) == 2) = X(t, directions(t, :) == 2) - deltaX;
    Y(t, directions(t, :) == 3) = Y(t, directions(t, :) == 3) + deltaY;
    Y(t, directions(t, :) == 4) = Y(t, directions(t, :) == 4) - deltaY;
end


% Affichage final des trajectoires
for i = 1:N
    plot(X(:, i), Y(:, i), 'LineWidth', 1, 'Color', colors(i, :));
    plot(X(end, i), Y(end, i), 'o', 'MarkerFaceColor', colors(i, :), ...
        'MarkerEdgeColor', colors(i, :), 'MarkerSize', 8);
end

X_d = X(:, N); % Coordonnées X
Y_d = Y(:, N); % Coordonnées Y

% Initialisation du vecteur de MQS (Moyenne Quadratique des déplacements)
MQS = zeros(T-1, 1);

% Calcul de la MQS pour chaque valeur de tau
for tau = 1:T-1  % Tau varie de 1 à T-1
    sum_MQS = 0;  % Initialiser la somme des déplacements au carré pour ce tau

    % Calcul des déplacements pour chaque valeur de tau
    for t = 1:(T-tau)  % On commence à t=1 et on fait des pas de tau jusqu a T-tau
        % Calcul des différences au carré
        sum_MQS = sum_MQS + (X_d(t + tau) - X_d(t))^2 + (Y_d(t + tau) - Y_d(t))^2;
    end
    
    % Calcul de la moyenne quadratique des déplacements pour ce tau
    MQS(tau) = sum_MQS / (T - tau);
end

% Tracé de la MQS en fonction de tau
figure;
plot(1:T-1, MQS, 'LineWidth', 2);
xlabel('Tau');
ylabel('Moyenne Quadratique des Déplacements (MQS)');
title('Moyenne Quadratique des Déplacements en fonction de Tau');

indices_tau = find((1:T-1) >= 0 & (1:T-1) <= 50); 
tau_filtered = indices_tau;  
MQS_filtered = MQS(indices_tau); 

% Ajustement linéaire
p = polyfit(tau_filtered, MQS_filtered, 1);
pente = p(1);

% Calcul du coefficient de diffusion
Diff = pente / (2 * d);

% Tracé du MDS filtré
figure;
plot(tau_filtered, MQS_filtered, 'o', 'MarkerFaceColor', 'b'); 
hold on;
plot(tau_filtered, polyval(p, tau_filtered), 'r-', 'LineWidth', 2); 
xlabel('Tau');
ylabel('MQS filtrée');
title('Moyenne Quadratique des Déplacements filtrée');
legend('Données filtrées', 'Ajustement linéaire');
hold off;
