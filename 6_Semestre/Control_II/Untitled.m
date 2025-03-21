kp = 10
Ck = 132.7593
Cp = 3.2615
G = tf( [kp*Ck], [1 Cp 0])
bode(G)