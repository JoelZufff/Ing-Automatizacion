-- Componente que al tener EN en alto, envia constantemente la distancia medida por un ultrasonico 

------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity US_HCSR_04 is
    generic 
    (
        CLK_FREQ    : INTEGER
    );
    port
    (
        i_CLK           : in STD_LOGIC;             -- Señal de reloj base
        i_RST           : in STD_LOGIC;             -- Señal de reset
        
        o_DIST          : out STD_LOGIC_VECTOR(7 downto 0);     -- Distancia medida
        
        -- I/O fisicas de sensor ultrasonico HCSR-04
        i_ECHO          : in STD_LOGIC;             -- Envio de pulso ECHO
        o_TRIG          : out STD_LOGIC             -- Trigger
    );
end US_HCSR_04;
------------------------------------------------------------------------------
architecture rtl of US_HCSR_04 is
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

        signal US_CLK           : STD_LOGIC;
        
        signal TRIG_clks        : INTEGER := 0;                         -- Cuenta de ciclos de reloj para señal trigger
        signal ECHO_clks        : INTEGER := 0;                         -- Cuenta de ciclos de reloj para señal echo

        constant us_10 : INTEGER := 10;                                 -- Ciclos de reloj de 10 us 
        constant ms_100 : INTEGER := 100000;                            -- Ciclos de reloj de 100 ms 
    
    -- MAQUINA DE ESTADOS FINITOS --
        type states_trigger is (SEND_TRIGGER, DELAY);
        signal TRIG_state : states_trigger := SEND_TRIGGER;      
        
        type states_echo is (WAIT_ECHO, GET_ECHO);
        signal ECHO_state : states_echo := WAIT_ECHO;      

begin
    ------------------------------------------------------------------------------
                                -- DIVISOR DE RELOJ --
    ------------------------------------------------------------------------------
    c_US_CLK : CLK_DIV
    generic map ( clk_freq => CLK_FREQ )
    port map ( i_out_freq => 1000000, i_CLK => i_CLK, o_CLK => US_CLK );

    ------------------------------------------------------------------------------
                            -- MAQUINAS DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (US_CLK, i_RST)
    begin
        if (i_RST = '1') then
            ECHO_clks <= 0;
            TRIG_clks <= 0;
            
            ECHO_state <= WAIT_ECHO;
            TRIG_state <= SEND_TRIGGER;
            
            o_DIST <= X"00";
                        
        elsif rising_edge(US_CLK) then
            
            -- Envio de señal TRIGGER
            case TRIG_state is
                when SEND_TRIGGER =>
                    -- Salidas del estado
                    o_TRIG <= '1';

                    -- Contador
                    TRIG_clks <= TRIG_clks + 1;                -- Contamos 10 us de ciclos de reloj
                    
                    -- Estado siguiente
                    if (TRIG_clks = us_10) then          -- Pasaron 10 us
                        TRIG_clks <= 0;                  -- Reiniciamos contador
                        TRIG_state <= DELAY;
                    else
                        TRIG_state <= SEND_TRIGGER;
                    end if;
                
                when DELAY =>
                    -- Salidas del estado
                    o_TRIG <= '0';

                    -- Contador
                    TRIG_clks <= TRIG_clks + 1;                -- Contamos 10 us de ciclos de reloj
                    
                    -- Estado siguiente
                    if (TRIG_clks = ms_100) then          -- Pasaron 100 ms
                        TRIG_clks <= 0;                  -- Reiniciamos contador
                        TRIG_state <= SEND_TRIGGER;
                    else
                        TRIG_state <= DELAY;
                    end if;

                when others => null;
            end case;

            -- Recepcion de señal ECHO
            case ECHO_state is
                when WAIT_ECHO =>
                    -- Estado siguiente
                    if (i_ECHO = '1') then          -- Si detectamos pulso ECHO
                        ECHO_clks <= 0;
                        ECHO_state <= GET_ECHO;
                    else
                        ECHO_state <= WAIT_ECHO;
                    end if;
                
                when GET_ECHO =>
                    -- Contador                    
                    ECHO_clks <= ECHO_clks + 1;                -- Contamos 10 ms de ciclos de reloj

                    -- Estado siguiente
                    if (i_ECHO = '0') then                      -- Finalizo pulso ECHO
                        o_DIST <= STD_LOGIC_VECTOR(to_unsigned(ECHO_clks * 343 / 20000, 8));     -- Convertimos ciclos en distancia

                        ECHO_clks <= 0;
                        ECHO_state <= WAIT_ECHO;

                    else
                        ECHO_state <= GET_ECHO;
                    end if;

                when others => null;
            end case;
        end if;

    end process;

end architecture;