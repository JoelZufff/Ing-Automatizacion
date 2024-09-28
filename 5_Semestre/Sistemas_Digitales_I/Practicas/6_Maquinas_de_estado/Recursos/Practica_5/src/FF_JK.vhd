library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FF_JK is
    Port ( 
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        J : in STD_LOGIC;
        K : in STD_LOGIC;
        Q : out STD_LOGIC
    );
end FF_JK;

architecture Behavioral of FF_JK is
    signal Q_int : STD_LOGIC := '0'; -- Señal interna para manejar el estado
begin
    process(clk, rst)
    begin
        if rst = '1' then
            Q_int <= '0'; -- Reset
        elsif rising_edge(clk) then
            if J = '0' and K = '0' then
                -- Mantener el estado actual, no se hace nada
            elsif J = '0' and K = '1' then
                Q_int <= '0'; -- Reset
            elsif J = '1' and K = '0' then
                Q_int <= '1'; -- Set
            elsif J = '1' and K = '1' then
                Q_int <= not Q_int; -- Toggle
            end if;
        end if;
    end process;

    Q <= Q_int; -- Asigna la señal interna a la salida
end Behavioral;