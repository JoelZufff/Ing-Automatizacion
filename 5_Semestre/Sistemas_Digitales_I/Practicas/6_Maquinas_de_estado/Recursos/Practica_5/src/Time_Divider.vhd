library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ClockDivider is
    generic(
        DIVIDE_BY : natural := 50000000 -- Número de ciclos de reloj para dividir
    );
    Port (
        clk_in : in STD_LOGIC; -- Reloj de entrada de 100 MHz
        reset : in STD_LOGIC; -- Reset asincrónico
        clk_out : out STD_LOGIC -- Salida de reloj configurada
    );
end ClockDivider;

architecture Behavioral of ClockDivider is
    -- Contador para la división de reloj
    signal counter : unsigned(26 downto 0) := (others => '0');
    -- La señal de reloj dividida
    signal clk_div : STD_LOGIC := '0';	
	
begin
    -- Proceso de división de reloj
    clk_process: process(clk_in, reset)
    begin
		
        if reset = '1' then
            -- Reinicia el contador si se activa el reset
            counter <= (others => '0');
            clk_div <= '0';
			
        elsif rising_edge(clk_in) then
            -- Incrementa el contador en cada flanco ascendente del reloj
            if counter = DIVIDE_BY then
                counter <= (others => '0');
                clk_div <= not clk_div; -- Cambia el estado del reloj de salida
            else
                counter <= counter + 1;
            end if;
        end if;
    end process;

    -- Asigna la señal de reloj dividida a la salida
    clk_out <= clk_div;	  
	
end Behavioral;