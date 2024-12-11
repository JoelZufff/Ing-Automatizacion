-- Maquina de estados finitos
-- GET_ADC0 : Bajamos CS para indicar que solicitaremos una escritura
-- GET_ADC1 : Bajamos WR para solicitar un muestreo de dato
-- WAIT_INTR : Esperamos señal INTR bajo
-- READ_ADC0 : Bajamos CS para indicar que solicitaremos una lectura
-- READ_ADC1 : Bajamos RD para solicitar una lectura de dato, mantenemos hasta recibir INTR en alto
-- READ_ADC1 : Subimos RD y leemos el dato recibido

-- Frecuencia maxima de muestreo: 1460 kHz
------------------------------------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------------------------------------------------------
entity ADC_0804LCN is
    generic 
    (
        CLK_FREQ        : INTEGER;
        SAMPLING_FREQ   : INTEGER
    );
    port 
    (
        i_CLK       : in STD_LOGIC;
        i_RST       : in STD_LOGIC;

        o_DATA      : out STD_LOGIC_VECTOR(7 downto 0);

        -- I/O fisicos ADC0804
        i_INTR      : in STD_LOGIC;                         -- Interrupcion
        i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);      -- 8 Bits de datos
        o_CS        : out STD_LOGIC;                        -- Chip select
        o_RD        : out STD_LOGIC;                        -- Lectura
        o_WR        : out STD_LOGIC;                        -- Escritura
        o_CLK_IN    : out STD_LOGIC                         -- Clock
    );
end ADC_0804LCN;
------------------------------------------------------------------------------------------------------------------------------
architecture rtl of ADC_0804LCN is

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

        signal ADC_CLK : STD_LOGIC;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (GET_ADC0, GET_ADC1, WAIT_INTR, READ_ADC0, READ_ADC1, READ_ADC2);
        signal act_state : states := GET_ADC0;

begin

    o_CLK_IN <= ADC_CLK;

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    c_ADC_CLK : CLK_DIV
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_out_freq => SAMPLING_FREQ, i_CLK => i_CLK, o_CLK => ADC_CLK );

    process (ADC_CLK, i_RST)
    begin
        if (i_RST = '1') then           -- Detectamos señal RST
            act_state   <= GET_ADC0;
            
        elsif (rising_edge(ADC_CLK)) then
            case act_state is
                when GET_ADC0 =>
                    -- Salidas del estado
                    o_CS <= '0'; o_WR <= '1'; o_RD <= '1';
                    -- SI chip select | NO write | NO read

                    -- Estado proximo
                    act_state <= GET_ADC1;
                
                when GET_ADC1 =>
                    -- Salidas del estado
                    o_CS <= '0'; o_WR <= '0'; o_RD <= '1'; 
                    -- SI chip select | SI write | NO read

                    -- Estado proximo
                    act_state <= WAIT_INTR;
                    
                when WAIT_INTR =>
                    -- Salidas del estado
                    o_CS <= '1'; o_WR <= '1'; o_RD <= '1'; 
                    -- NO chip select | NO write | NO read

                    -- Estado proximo
                    if (i_INTR = '0') then              -- Si se almaceno el dato
                        act_state <= READ_ADC0;
                    else
                        act_state <= WAIT_INTR;
                    end if;

                when READ_ADC0 =>
                    -- Salidas del estado
                    o_CS <= '0'; o_WR <= '1'; o_RD <= '1'; 
                    -- SI chip select | NO write | SI read

                    -- Estado proximo
                    act_state <= READ_ADC1;
                    
                when READ_ADC1 => 
                    -- Salidas del estado
                    o_CS <= '0'; o_WR <= '1'; o_RD <= '0'; 
                    -- SI chip select | NO write | SI read

                    -- Estado proximo
                    if (i_INTR = '1') then              -- Si comenzo la conversion
                        act_state <= READ_ADC2;
                    else
                        act_state <= READ_ADC1;
                    end if;
                    
                when READ_ADC2 => 
                    -- Salidas del estado
                    o_CS <= '0'; o_WR <= '1'; o_RD <= '1'; 
                    -- SI chip select | NO write | SI read
                    
                    o_DATA <= i_DATA;

                    -- Estado proximo
                    act_state <= GET_ADC0;

                when others => null;
            end case;

        end if;
    
    end process;
    

end architecture;