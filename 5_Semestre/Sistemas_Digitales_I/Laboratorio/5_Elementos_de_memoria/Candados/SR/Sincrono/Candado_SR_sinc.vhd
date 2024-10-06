library IEEE;
use IEEE.std_logic_1164.all;

entity Candado_SR_sinc is
    port 
    (
        -- Entradas y salidas de candado SR con compuertas NOR
        i_R     : in std_logic;
        i_S     : in std_logic;
        i_LD    : in std_logic;     -- Señal de reloj
        o_Q     : out std_logic;
        o_Qc    : out std_logic
    );
end Candado_SR_sinc;

architecture Candado of Candado_SR_sinc is
    signal Q      : std_logic;
    signal Qc     : std_logic;
begin
    
    -- Candado SR con compuertas NOR
    Q       <= (i_R and i_LD) nor Qc;
    Qc      <= (i_S and i_LD) nor Q;
    
    o_Q     <= Q;
    o_Qc    <= Qc;
    
end Candado;