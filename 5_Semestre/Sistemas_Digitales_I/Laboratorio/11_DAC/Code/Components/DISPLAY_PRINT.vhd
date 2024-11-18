------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity DISPLAY_PRINT is
    generic 
    (
        CLK_FREQ    : INTEGER
    );
    port
    (
        i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
        i_RST       : in STD_LOGIC;                         -- Reinicio total

        i_NUM0      : in STD_LOGIC_VECTOR(7 downto 0);
        i_NUM1      : in STD_LOGIC_VECTOR(7 downto 0);

        -- I/O fisicos display
        o_DISP_SEG  : out STD_LOGIC_VECTOR(7 downto 0);     -- 7 segmentos
		o_DISP_COM  : out STD_LOGIC_VECTOR(1 downto 0)      -- 2 comunes
    );
end DISPLAY_PRINT;

architecture rtl of DISPLAY_PRINT is
    -- DIVISOR DE RELOJ --
        component CLK_DIV
            generic 
            (
                clk_freq : INTEGER
            );
            port 
            (
                i_out_freq :  INTEGER;
                i_FPGA_clk : in STD_LOGIC;
                o_clk : out STD_LOGIC
            );
        end component;

        signal DISP_CLK : STD_LOGIC;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (NUM0, NUM1);
        signal act_state : states := NUM0;
    
begin

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    c_DISP_CLK : CLK_DIV
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_out_freq => 1000, i_FPGA_clk => i_CLK, o_clk => DISP_CLK );

    process (DISP_CLK, i_RST)
    begin
        if (i_RST = '1') then           -- Detectamos señal RST
            act_state   <= NUM0;

        elsif (rising_edge(DISP_CLK)) then
            case act_state is
                when NUM0 =>                            -- Multiplexado de 1er display
                    -- Salidas de estado actual
                    o_DISP_SEG <= i_NUM0; o_DISP_COM <= "01";

                    -- Estado de siguiente ciclo
                    act_state <= NUM1;
                    
                when NUM1 =>                            -- Multiplexado de 2do display
                    -- Salidas de estado actual
                    o_DISP_SEG <= i_NUM1; o_DISP_COM <= "10";

                    -- Estado de siguiente ciclo
                    act_state <= NUM0;
                    
                when others => null;
            end case;

        end if;

    end process;

end architecture;