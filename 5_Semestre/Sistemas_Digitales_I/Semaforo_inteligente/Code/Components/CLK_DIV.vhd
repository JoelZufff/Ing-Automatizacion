-- Componente que recibe una señal de reloj, y la divide para obtener la frecuencia de salida deseada 
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity CLK_DIV is
	generic 
    (
        clk_freq    : INTEGER          -- Frecuencia interna de FPGA (Hz)
    );
    port
	(
        i_out_freq      : INTEGER;              -- Frequencia deseada
		
        i_CLK           : in STD_LOGIC;         -- Señal de reloj base
        o_CLK           : out STD_LOGIC
	);
end CLK_DIV;
------------------------------------------------------------------------------
architecture DIV of CLK_DIV is

    signal clks     : INTEGER := 0;
    signal clks_max : INTEGER := clk_freq / (2 * i_out_freq); -- Como conmutamos el reloj ocupamos que la frecuencia de conmutacion sea de 2 veces la deseada
	 signal CLK		  : STD_LOGIC;

begin

	o_CLK <= CLK;

    process (i_CLK)        -- Ciclo de reloj para cambio de estado
    begin
        if rising_edge(i_CLK) then     -- Division de reloj para baudios
            
            if clks < clks_max then
                clks <= clks + 1;
            else
                CLK <= not CLK;
                clks <= 0;
            end if;

        end if;
    end process;

end architecture;