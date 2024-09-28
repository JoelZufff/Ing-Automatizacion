library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FF_SR is
    Port ( 
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        S : in STD_LOGIC;
        R : in STD_LOGIC;
        Q : out STD_LOGIC
    );
end FF_SR;

architecture Behavioral of FF_SR is
    signal Q_int : STD_LOGIC := '0'; -- Señal interna para manejar el estado
begin
    process(clk, rst)
    begin
        if rst = '1' then
            Q_int <= '0'; -- Reset
        elsif rising_edge(clk) then
            if S = '1' and R = '0' then
                Q_int <= '1'; -- Set
            elsif S = '0' and R = '1' then
                Q_int <= '0'; -- Reset
            -- La condición S = '1' y R = '1' podría manejarla aquí si necesario
            end if;
        end if;
    end process;

    Q <= Q_int; -- Asigna la señal interna a la salida
end Behavioral;