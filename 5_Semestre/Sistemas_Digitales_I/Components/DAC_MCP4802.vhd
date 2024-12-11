-- Ocupo mandar 16 bits de datos para configurar el SPI
-- Algoritmo:
-- LDAC

-- 1. CS <= '0'     -- Esta en '1' todo el tiempo
-- 2. SCK <= CLK    -- Contamos 16 pulsos de cada bit (0 -> 15)
-- 3. SPI(i) <= Bits de datos       -- Cambia en cada flanco de subida de CLK
-- 4. Al finalizar de los 16 bits, enviamos LDAC <= '0', despues de 40 ns y por 100 ns minimo.
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity DAC_MCP4802 is
    generic 
    (
        CLK_FREQ    : INTEGER
    );
    port
    (
        i_CLK       : in STD_LOGIC;                         -- Señal de reloj base
        i_RST       : in STD_LOGIC;                         -- Reinicio total
        
        i_ST        : in STD_LOGIC;                         -- Señal de start
        i_DAC_CONF  : in STD_LOGIC_VECTOR(3 downto 0);      -- 4 Bits para configuracion de DAC
        i_DAC_VOLT  : in STD_LOGIC_VECTOR(7 downto 0);      -- 8 Bits para resolucion de voltaje analogico
        
        o_RDY       : out STD_LOGIC;                        -- Ready

        -- Salidas fisicas MCP4802
        o_SDI       : out STD_LOGIC;                        -- Datos seriales
        o_SCK       : out STD_LOGIC;                        -- Señal de reloj
        o_CS        : out STD_LOGIC;                        -- Chip select
        o_LDAC      : out STD_LOGIC                        	-- Latch DAC
    );
end DAC_MCP4802;
------------------------------------------------------------------------------
architecture rtl of DAC_MCP4802 is
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

        signal DAC_CLK : STD_LOGIC;
        constant DAC_FREQ : INTEGER := 1000000;       -- 8MHz

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE, WAIT_ST, SEND_DATA, LATCH_DAC);
        signal act_state : states := IDLE;

        signal DAC_DATA : STD_LOGIC_VECTOR(11 downto 0);        -- Datos
        signal bit_index : integer range 0 to 16;

        signal EN_SCK : STD_LOGIC := '0';                      -- Señal de reloj esta desactivada
begin

    o_SCK <= (not DAC_CLK) and EN_SCK;      -- Tiene la señal negada de reloj para hacer un desface

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    c_DAC_CLK : CLK_DIV
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_out_freq => DAC_FREQ, i_FPGA_clk => i_CLK, o_clk => DAC_CLK );

    process (DAC_CLK, i_RST)
    begin
        if (i_RST = '1') then           -- Detectamos señal RST
            act_state   <= IDLE;
            
        elsif (rising_edge(DAC_CLK)) then
            case act_state is
                when IDLE =>                        -- En espera de señal ST
                    -- Salidas de estado actual
                    o_RDY <= '1';
                    o_CS <= '1'; EN_SCK <= '0'; o_SDI <= '0'; o_LDAC <= '1';
                    -- NO señal Chip Select | NO señal de reloj | NO envio de bit | NO señal de latch 

                    bit_index   <= 0;             -- Reiniciamos indice de bit

                    -- Estado futuro
                    if (i_ST = '1') then
                        DAC_DATA <= i_DAC_CONF & i_DAC_VOLT;        -- Almacenamos valor de data al recibir señal de start
                        act_state <= WAIT_ST;
                    else
                        act_state <= IDLE;
                    end if;

                when WAIT_ST =>                     -- Esperamos desactivacion de pulso ST (Para evitar multiples activaciones no deseadas)
                    -- Salidas de estado actual
                    o_RDY <= '0';
                    o_CS <= '1'; EN_SCK <= '0'; o_SDI <= '0'; o_LDAC <= '1';
                    -- NO señal Chip Select | NO señal de reloj | NO envio de bit | NO señal de latch 
                    
                    -- Estado futuro
                    if (i_ST = '0') then
                        act_state <= SEND_DATA;
                    else
                        act_state <= WAIT_ST;
                    end if;
                
                when SEND_DATA =>                   -- Enviamos 16 bits de datos
                    -- Salidas de estado actual
                    o_RDY <= '0';
                    o_CS <= '0'; EN_SCK <= '1'; o_LDAC <= '1';
                    -- SI señal Chip Select | SI señal de reloj | SI envio de bit | NO señal de latch 

                    bit_index <= bit_index + 1;     -- Aumentamos indice para siguiente ciclo
                    
                    if (bit_index < 12) then               -- Bit 15 -> 4
                        o_SDI <= DAC_DATA(11 - bit_index);
                    else                                    -- Bit 3 -> 0
                        o_SDI <= '0';         
                    end if;

                    -- Estado futuro
                    if (bit_index = 15) then        -- Estamos en el ultimo bit
                        act_state <= LATCH_DAC;
                    else
                        act_state <= SEND_DATA;
                    end if;

                when LATCH_DAC =>                   -- Enviamos pulso Latch DAC
                    -- Salidas de estado actual
                    o_RDY <= '0';
                    o_CS <= '1'; EN_SCK <= '0'; o_SDI <= '0'; o_LDAC <= '0';
                    -- NO señal Chip Select | NO señal de reloj | NO envio de bit | SI señal de latch                     

                    -- Estado futuro
                    act_state <= IDLE;

                when others => null;
            end case;

        end if;

    end process;

end architecture;