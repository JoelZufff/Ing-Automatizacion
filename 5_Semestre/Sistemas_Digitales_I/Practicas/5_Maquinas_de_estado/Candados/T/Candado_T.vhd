library IEEE;
use IEEE.std_logic_1164.all;

entity Candado_T is
    port 
    (
        i_LD    : in std_logic;     -- Señal de reloj
        i_T     : in std_logic;
        o_Q     : out std_logic;
        o_Qc    : out std_logic
    );
end Candado_T;

architecture Candado of Candado_T is
    signal Q  : std_logic;
    signal Q2  : std_logic;
    signal Qc : std_logic;
    signal Qc2 : std_logic;
begin
    Q   <= Q2 nor Qc;
    Q2  <= (Q and i_T and i_LD);

    Qc  <= Qc2 nor Q;
    Qc2 <= (i_LD and i_T and Qc);

    o_Q     <= Q;
    o_Qc    <= Qc;
end Candado;