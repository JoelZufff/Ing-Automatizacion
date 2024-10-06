library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity Candado_D is
    port 
    (
        i_LD    : in std_logic;     -- Señal de reloj
        i_D     : in std_logic;
        o_Q     : out std_logic;
        o_Qc    : out std_logic
    );
end Candado_D;

architecture Candado of Candado_D is
    signal Q  : std_logic;
    signal Qc : std_logic;
begin 
    Q <= (i_D nand i_LD) nand Qc;
    Qc <= (i_LD nand (not i_D)) nand Q;

    o_Q     <= Q;
    o_Qc    <= Qc;
end Candado;