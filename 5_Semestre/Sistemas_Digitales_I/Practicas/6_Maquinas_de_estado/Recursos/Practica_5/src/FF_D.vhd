library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FF_D is
    Port ( 
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        D : in STD_LOGIC;
        Q : out STD_LOGIC
    );
end FF_D;

architecture Behavioral of FF_D is	

begin
    process(clk, rst)
    begin
        if rst = '1' then
            Q <= '0';
        elsif rising_edge(clk) then
            Q <= D;
        end if;
    end process;
end Behavioral;