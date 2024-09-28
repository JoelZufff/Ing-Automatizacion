library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity Candado_JK is
    port 
    (
        i_LD    : in std_logic;     -- Señal de reloj
        i_J     : in std_logic;
        i_K     : in std_logic;
        o_Q     : out std_logic;
        o_Qc    : out std_logic
    );
end Candado_JK;

architecture Candado of Candado_JK is
    signal Q  : std_logic;
    signal Qc : std_logic;
begin
    Q   <= (Q and i_K and i_LD) nor Qc;
    Qc  <= (Qc and i_J and i_LD) nor Q; 

    o_Q     <= Q;
    o_Qc    <= Qc;
end Candado;