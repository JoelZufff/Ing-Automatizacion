-- Con 50 Mhz solo podre tener un PWM de maximo 500 kHz
-- Este PWM esta invertido con el fin de encender los LED's
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity PWM is
    generic 
    (
        CLK_FREQ    : INTEGER;
        PWM_FREQ    : INTEGER
    );
    port
    (
        i_CLK           : in STD_LOGIC;                 -- Señal de reloj base

        i_EN            : in STD_LOGIC;                 -- Enable de señal de salida
        i_DC            : in INTEGER range 0 to 100;    -- Valor deseado de Duty cicle

        o_PWM           : out STD_LOGIC                 -- Señal de salida con PWM
    );
end PWM;
------------------------------------------------------------------------------
architecture rtl of PWM is
    -- DIVISOR DE RELOJ --
        component CLK_DIV is
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
        end component;

        signal PWM_CLK : STD_LOGIC;
        signal clks    : INTEGER range 0 to 100 := 0;

    signal PWM : STD_LOGIC;
begin

    c_PWM_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => PWM_FREQ * 100, i_CLK => i_CLK, o_CLK => PWM_CLK );

    process (PWM_CLK)
    begin
        if (rising_edge(PWM_CLK)) then

            -- Contador
            if (clks = 100 - 1) then
                clks <= 0;
            else
                clks <= clks + 1;
            end if;

            -- Comparador
            if ((clks < i_DC) and (i_EN = '1')) then
                o_PWM <= '1';
            else
                o_PWM <= '0';
            end if;
            
        end if;

    end process;

end architecture;