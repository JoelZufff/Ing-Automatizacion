------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Template is
    generic 
    (
        CLK_FREQ    : INTEGER := 50000000
    );
    port
    (
        i_CLK           : in STD_LOGIC;             -- Señal de reloj base
        i_RST           : in STD_LOGIC;             -- Señal de reset
    );
end Template;
------------------------------------------------------------------------------
architecture rtl of Template is
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

    signal TEM_CLK : STD_LOGIC;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE);
        signal act_state : states := IDLE;

begin
    
    ------------------------------------------------------------------------------
                                -- DIVISOR DE RELOJ --
    ------------------------------------------------------------------------------
    c_TEM_CLK : CLK_DIV
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_out_freq => 1, i_CLK => i_CLK, o_CLK => TEM_CLK );

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (TEM_CLK, i_RST)
    begin
        if (i_RST = '1') then
            
        elsif rising_edge(TEM_CLK) then
            case act_state is
                when IDLE =>
                    
            
                when others => null;
            end case;
        end if;

    end process;

end architecture;