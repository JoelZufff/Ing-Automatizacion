library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FF_T is
    Port ( 
        clk : in STD_LOGIC;
        rst : in STD_LOGIC;
        T : in STD_LOGIC; -- Entrada Toggle
        Q : out STD_LOGIC -- Salida
    );
end FF_T;

architecture Behavioral of FF_T is
    signal Q_int : STD_LOGIC := '0'; -- Señal interna para mantener el estado del flip-flop
begin
    process(clk, rst)
    begin
        if rst = '1' then
            Q_int <= '0'; -- Resetea el estado a 0
        elsif rising_edge(clk) then
            if T = '1' then
                Q_int <= not Q_int; -- Cambia el estado si T está activo
            end if;
        end if;
    end process;

    Q <= Q_int; -- Asigna el estado interno a la salida Q
end Behavioral;