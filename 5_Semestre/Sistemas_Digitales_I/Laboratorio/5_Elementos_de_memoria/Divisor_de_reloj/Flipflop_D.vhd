library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;

entity Flipflop_D is
    port 
    (
        i_LD    : in std_logic;     -- Señal de reloj
        i_D     : in std_logic;
        o_Q     : out std_logic
    );
end Flipflop_D;

architecture Candado of Flipflop_D is
    signal Q  : std_logic;
begin
    process (i_LD)
    begin
        if rising_edge(i_LD) then
            Q   <= i_D;
        end if;
    end process;
    
    o_Q     <= Q;
end Candado;