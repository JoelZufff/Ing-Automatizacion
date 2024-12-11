-- FALTA
-- COMPONENTE DE CUENTA DE FLUJO
-- BOTON PEATONAL
-- PANTALLA LCD Y COMUNICACION SERIAL
-- ADC PARA DETECTAR LED FUNDIDO

------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Smart_traffic_light is
    generic 
    (
        CLK_FREQ    : INTEGER := 50000000
    );
    port
    (
        i_CLK           : in STD_LOGIC;                             -- Señal de reloj base
        i_RST           : in STD_LOGIC;                             -- Reinicio total
        
        o_LEDS          : out STD_LOGIC_VECTOR(3 downto 0);         -- Para ver en que estado estamos

        -- Flujo NORTH-SOUTH
            -- Semaforos
            o_PTL_NS        : out STD_LOGIC_VECTOR(1 downto 0);     -- Semaforo peatonal
            o_TRLH_NS       : out STD_LOGIC_VECTOR(3 downto 0);     -- Semaforo vehicular 
            
            i_PBUTTON_NS    : in STD_LOGIC;                         -- Boton peatonal
            -- Sensores de flujo
            i_SENSOR_N      : in STD_LOGIC_VECTOR(1 downto 0);
            i_SENSOR_S      : in STD_LOGIC_VECTOR(1 downto 0);
        
        -- Flujo EAST_WEST
            -- Semaforos
            o_PTL_EW        : out STD_LOGIC_VECTOR(1 downto 0);     -- Semaforo peatonal
            o_TRLH_EW       : out STD_LOGIC_VECTOR(3 downto 0);     -- Semaforo vehicular
            
            i_PBUTTON_EW  : in STD_LOGIC;                           -- Boton peatonal
            -- Sensores de flujo
            i_SENSOR_E      : in STD_LOGIC_VECTOR(1 downto 0);
            i_SENSOR_W      : in STD_LOGIC_VECTOR(1 downto 0);
        
        -- I/O fisicos display QUITAR
            o_DISP_SEG  : out std_logic_vector(7 downto 0);         -- 7 segmentos
            o_DISP_COM  : out std_logic_vector(3 downto 0);         -- 4 comunes

        -- I/O fisicos ADC0804
            i_INTR0     : in STD_LOGIC;                             -- Interrupcion
            i_DATA0     : in STD_LOGIC_VECTOR(7 downto 0);          -- 8 Bits de datos
            o_CS0       : out STD_LOGIC;                            -- Chip select
            o_RD0       : out STD_LOGIC;                            -- Lectura
            o_WR0       : out STD_LOGIC;                            -- Escritura
            o_CLK_IN0   : out STD_LOGIC;                            -- Clock
        
        -- I/O fisicos ADC0804
            i_INTR1     : in STD_LOGIC;                             -- Interrupcion
            i_DATA1     : in STD_LOGIC_VECTOR(7 downto 0);          -- 8 Bits de datos
            o_CS1       : out STD_LOGIC;                            -- Chip select
            o_RD1       : out STD_LOGIC;                            -- Lectura
            o_WR1       : out STD_LOGIC;                            -- Escritura
            o_CLK_IN1   : out STD_LOGIC;                            -- Clock

        o_BUZZER        : out STD_LOGIC                             -- Buzzer peatonal
    );
end Smart_traffic_light;

architecture rtl of Smart_traffic_light is
    
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

        signal STL_CLK : STD_LOGIC;
        signal clks    : INTEGER := 0;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (STOP, FLOW_NORT_SOUTH, FLOW_EAST_WEST, YELLOW);
        signal act_state        : states := STOP;
        signal YW_next_state    : states;

    -- CONTADOR DE FLUJO --
        component Flow_counter is
            port
            (
                i_CLK               : in STD_LOGIC;
                i_RST               : in STD_LOGIC;                         -- Reinicio de maquina de estados
        
                i_ENTRY_SENSOR      : in STD_LOGIC;                         -- Sensor de entrada de carril
                i_FORW_SENSOR       : in STD_LOGIC;                         -- Sensor de salida de carril
                i_RIGHT_SENSOR      : in STD_LOGIC;                         -- Sensor de salida de carril
        
                i_TRLH              : in STD_LOGIC_VECTOR(3 downto 0);      -- Semaforo de carril
        
                o_CAR_FLOW          : out INTEGER
            );
        end component;

        signal NS_CAR_FLOW, SN_CAR_FLOW, EW_CAR_FLOW, WE_CAR_FLOW : INTEGER := 0;

    -- Señales PWM --
        component PWM is
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
        
                o_PWM           : out STD_LOGIC            -- Señal de salida con PWM
            );
        end component;

        signal PWM_DC : INTEGER range 0 to 100 := 0;

        signal PTL_NS_EN    : STD_LOGIC_VECTOR(1 downto 0);
        signal TRLH_NS_EN   : STD_LOGIC_VECTOR(3 downto 0);
        signal PTL_EW_EN    : STD_LOGIC_VECTOR(1 downto 0);
        signal TRLH_EW_EN   : STD_LOGIC_VECTOR(3 downto 0);

    -- DISPLAY CON DECODER BCD DE 8 BITS --
        component DISPLAY_BCD
            generic 
            (
                CLK_FREQ : INTEGER
            );
            port 
            (
                i_CLK : in STD_LOGIC;
                i_DATA : in STD_LOGIC_VECTOR(7 downto 0);
                o_DISP_SEG : out STD_LOGIC_VECTOR(7 downto 0);
                o_DISP_COM : out STD_LOGIC_VECTOR(3 downto 0)
            );
        end component;

    -- Modulo ADC0804LCN --
        component ADC_0804LCN is
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
        end component;

        signal ADC_POT  : STD_LOGIC_VECTOR(7 downto 0);
        signal ADC_TEMP : STD_LOGIC_VECTOR(7 downto 0);

        signal AUX  : STD_LOGIC_VECTOR(15 downto 0);
        signal TEMP : STD_LOGIC_VECTOR(7 downto 0);

begin
    ------------------------------------------------------------------------------
                                -- DIVISOR DE RELOJ --
    ------------------------------------------------------------------------------
    c_STL_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => 1000, i_CLK => i_CLK, o_CLK => STL_CLK );

    ------------------------------------------------------------------------------
                        -- CONTADORES DE FLUJO VEHICULAR --
    ------------------------------------------------------------------------------    
    NORTH_SOUTH : Flow_counter
        port map ( i_CLK => STL_CLK, i_RST => not i_RST, i_ENTRY_SENSOR => i_SENSOR_N(1), i_FORW_SENSOR => i_SENSOR_S(1), i_RIGHT_SENSOR => i_SENSOR_W(1), i_TRLH => TRLH_NS_EN, o_CAR_FLOW => NS_CAR_FLOW);

    SOUTH_NORTH : Flow_counter
        port map ( i_CLK => STL_CLK, i_RST => not i_RST, i_ENTRY_SENSOR => i_SENSOR_S(0), i_FORW_SENSOR => i_SENSOR_N(0), i_RIGHT_SENSOR => i_SENSOR_E(0), i_TRLH => TRLH_NS_EN, o_CAR_FLOW => SN_CAR_FLOW);

    EAST_WEST : Flow_counter
        port map ( i_CLK => STL_CLK, i_RST => not i_RST, i_ENTRY_SENSOR => i_SENSOR_E(1), i_FORW_SENSOR => i_SENSOR_W(1), i_RIGHT_SENSOR => i_SENSOR_N(0), i_TRLH => TRLH_EW_EN, o_CAR_FLOW => EW_CAR_FLOW);

    WEST_EAST : Flow_counter
        port map ( i_CLK => STL_CLK, i_RST => not i_RST, i_ENTRY_SENSOR => i_SENSOR_W(0), i_FORW_SENSOR => i_SENSOR_E(0), i_RIGHT_SENSOR => i_SENSOR_S(1), i_TRLH => TRLH_EW_EN, o_CAR_FLOW => WE_CAR_FLOW);

    ------------------------------------------------------------------------------
                        -- SEÑALES PWM PARA LEDS DE SEMAFOROS --
    ------------------------------------------------------------------------------
    PWM_DC <= to_integer(unsigned(ADC_POT) * 100 / 255);
    
    PTL_NS_0 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => PTL_NS_EN(0), i_DC => PWM_DC, o_PWM => o_PTL_NS(0));

    PTL_NS_1 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => PTL_NS_EN(1), i_DC => PWM_DC, o_PWM => o_PTL_NS(1));

    TRLH_NS_0 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_NS_EN(0), i_DC => PWM_DC, o_PWM => o_TRLH_NS(0));
    
    TRLH_NS_1 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_NS_EN(1), i_DC => PWM_DC, o_PWM => o_TRLH_NS(1));

    TRLH_NS_2 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_NS_EN(2), i_DC => PWM_DC, o_PWM => o_TRLH_NS(2));

    TRLH_NS_3 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_NS_EN(3), i_DC => PWM_DC, o_PWM => o_TRLH_NS(3));

        
    PTL_EW_0 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => PTL_EW_EN(0), i_DC => PWM_DC, o_PWM => o_PTL_EW(0));

    PTL_EW_1 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => PTL_EW_EN(1), i_DC => PWM_DC, o_PWM => o_PTL_EW(1));

    TRLH_EW_0 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_EW_EN(0), i_DC => PWM_DC, o_PWM => o_TRLH_EW(0));
    
    TRLH_EW_1 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_EW_EN(1), i_DC => PWM_DC, o_PWM => o_TRLH_EW(1));

    TRLH_EW_2 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_EW_EN(2), i_DC => PWM_DC, o_PWM => o_TRLH_EW(2));

    TRLH_EW_3 : PWM
        generic map ( CLK_FREQ => CLK_FREQ, PWM_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_EN => TRLH_EW_EN(3), i_DC => PWM_DC, o_PWM => o_TRLH_EW(3));

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (STL_CLK, i_RST)
    begin
        if (i_RST = '0') then               -- Se presiona RST
            clks <= 0;
            act_state <= STOP;
        elsif rising_edge(STL_CLK) then     -- Se detecta señal de reloj
            case act_state is
                when STOP =>
                    -- Señales de salida
                    PTL_NS_EN <= "01";      PTL_EW_EN <= "01";              -- Semaforos peatonales
                    TRLH_NS_EN <= "1000";   TRLH_EW_EN <= "1000";           -- Semaforos vehiculares
                    o_LEDS <= "0111";

                    -- Contador
                    if(clks < 3000) then
                        clks <= clks + 1;
                    end if;
                                            
                    -- Estado futuro
                    if (((NS_CAR_FLOW + SN_CAR_FLOW) > 0) and (clks >= 3000)) then
                        act_state <= FLOW_NORT_SOUTH;
                    elsif (((EW_CAR_FLOW + WE_CAR_FLOW) > 0) and (clks >= 3000)) then
                        act_state <= FLOW_EAST_WEST;
                    else
                        act_state <= STOP;
                    end if;

                when FLOW_NORT_SOUTH =>
                    -- Señales de salida
                    PTL_NS_EN <= "10";      PTL_EW_EN <= "01";              -- Semaforos peatonales
                    TRLH_NS_EN <= "0011";   TRLH_EW_EN <= "1000";           -- Semaforos vehiculares
                    o_LEDS <= "1011";

                    -- Estado futuro
                    if((EW_CAR_FLOW + WE_CAR_FLOW) > (NS_CAR_FLOW + SN_CAR_FLOW)) then  -- Hay mas flujo EW que NS
                        -- Lo ponemos en amarillo
                        TRLH_NS_EN <= "0100";       -- Ponermos el semaforo en amarillo
                        clks <= 0;

                        act_state <= YELLOW;
                        YW_next_state <= FLOW_EAST_WEST;
                        
                    elsif (((NS_CAR_FLOW + SN_CAR_FLOW) = 0) or (i_PBUTTON_NS = '1')) then      -- Ya no hay flujo
                        -- Lo ponemos en amarillo
                        TRLH_NS_EN    <= "0100";       -- Ponermos el semaforo en amarillo
                        clks <= 0;

                        act_state <= YELLOW;
                        YW_next_state <= STOP;
                    else
                        act_state <= FLOW_NORT_SOUTH;
                    end if;

                when FLOW_EAST_WEST =>
                    -- Señales de salida
                    PTL_NS_EN <= "01";      PTL_EW_EN <= "10";              -- Semaforos peatonales
                    TRLH_NS_EN <= "1000";   TRLH_EW_EN <= "0011";           -- Semaforos vehiculares
                    o_LEDS <= "1101";

                    -- Estado futuro
                    if((NS_CAR_FLOW + SN_CAR_FLOW) > (EW_CAR_FLOW + WE_CAR_FLOW)) then  -- Hay mas flujo NS que EW
                        -- Lo ponemos en amarillo
                        TRLH_EW_EN  <= "0100";       -- Ponermos el semaforo en amarillo
                        clks <= 0;

                        act_state <= YELLOW;
                        YW_next_state <= FLOW_NORT_SOUTH;
                        
                    elsif (((EW_CAR_FLOW + WE_CAR_FLOW) = 0) or (i_PBUTTON_EW = '1')) then      -- Ya no hay flujo
                        -- Lo ponemos en amarillo
                        TRLH_EW_EN  <= "0100";       -- Ponermos el semaforo en amarillo
                        clks <= 0;

                        act_state <= YELLOW;
                        YW_next_state <= STOP;

                    else
                        act_state <= FLOW_EAST_WEST;
                    end if;

                when YELLOW =>
                    -- Señales de salida
                    o_LEDS <= "1110";

                    -- Contador
                    clks <= clks + 1;

                    -- Estado futuro
                    if(clks = 5000 - 1) then
                        clks <= 0;
                        act_state <= YW_next_state;
                    else
                        act_state <= YELLOW;
                    end if;

                when others => null;
            end case;
        end if;
    end process;

    ------------------------------------------------------------------------------
                            -- IMPRESION DE DISPLAY BCD --
    ------------------------------------------------------------------------------
    c_DISPLAY_BCD : DISPLAY_BCD
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_CLK => i_CLK, i_DATA => TEMP, o_DISP_SEG => o_DISP_SEG, o_DISP_COM => o_DISP_COM );

    ------------------------------------------------------------------------------
                                -- MODULO ADC0804LCN --
    ------------------------------------------------------------------------------
    c_ADC_POT : ADC_0804LCN
        generic map ( CLK_FREQ => CLK_FREQ, SAMPLING_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_RST => not i_RST, o_DATA => ADC_POT, i_INTR => i_INTR0, i_DATA => i_DATA0, o_CS => o_CS0, o_RD => o_RD0, o_WR => o_WR0, o_CLK_IN => o_CLK_IN0 );
    
    c_ADC_TEMP : ADC_0804LCN
        generic map ( CLK_FREQ => CLK_FREQ, SAMPLING_FREQ => 1000 )
        port map ( i_CLK => i_CLK, i_RST => not i_RST, o_DATA => ADC_TEMP, i_INTR => i_INTR1, i_DATA => i_DATA1, o_CS => o_CS1, o_RD => o_RD1, o_WR => o_WR1, o_CLK_IN => o_CLK_IN1 );

    TEMP <= std_logic_vector(to_unsigned((to_integer(unsigned(ADC_TEMP)) * 330) / 255, 8));

end architecture;