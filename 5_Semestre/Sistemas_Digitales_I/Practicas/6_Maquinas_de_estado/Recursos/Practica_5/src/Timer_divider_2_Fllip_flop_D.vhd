library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DivisorFrecuencia is
    Port ( clk : in STD_LOGIC;
           rst : in STD_LOGIC;
           clk_out : out STD_LOGIC);
end DivisorFrecuencia;

architecture Behavioral of DivisorFrecuencia is

    signal q1, q2 : STD_LOGIC;

begin

    -- Primer flip-flop
    process(clk, rst)
    begin
        if rst = '1' then
            q1 <= '0';
        elsif rising_edge(clk) then
            q1 <= not q1;
        end if;
    end process;

    -- Segundo flip-flop
    process(clk, rst)
    begin
        if rst = '1' then
            q2 <= '0';
        elsif rising_edge(q1) then
            q2 <= not q2;
        end if;
    end process;

    -- Salida
    clk_out <= q2;

end Behavioral;