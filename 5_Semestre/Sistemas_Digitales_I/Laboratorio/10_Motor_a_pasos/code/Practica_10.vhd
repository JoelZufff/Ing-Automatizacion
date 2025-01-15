library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Practica_10 is
    generic 
    (
        clk_freq        : INTEGER := 50000000   
    );
    port
    (
        i_FPGA_clk          : in STD_LOGIC;         -- Señal de reloj base
        i_RST               : in STD_LOGIC;         -- Reinicio total
        
        i_START             : in STD_LOGIC;
        i_STOP              : in STD_LOGIC;
        i_VEL               : in STD_LOGIC_VECTOR(1 downto 0);

        -- UART
        i_RX                : in STD_LOGIC;
        o_TX                : out STD_LOGIC;

        -- LCD
        o_RS, o_E, o_RW     : out STD_LOGIC;
        o_LCD_DATA          : out std_logic_vector(7 downto 0);      -- 8 Bits ASCII

        -- STEPPER MOTOR
        o_STEPS             : out STD_LOGIC_VECTOR(3 downto 0)      -- 4 pasos del motor a pasos
        --o_LED               : out STD_LOGIC
    );
end Practica_10;

architecture rtl of Practica_10 is
    -- DIVISION DE RELOJ --
        component CLK_DIV is
            generic 
            (
                clk_freq    : INTEGER          -- Frecuencia interna de FPGA (Hz)
            );
            port
            (
                i_out_freq      : INTEGER;              -- Frequencia deseada
                
                i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
                o_clk           : out STD_LOGIC    
            );
        end component;

        signal P10_CLK : STD_LOGIC;
        constant P10_freq : INTEGER := 1000000;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (LCD_SEND, TX_SEND, PRINT_IDLE, IDLE, PRINT_COUPLING, COUPLING, WAIT_2SEC, PRINT_STOP);
        signal act_state : states := PRINT_IDLE;

        signal LCD_nxt_state : states;
        signal TX_nxt_state : states;
        signal STOP_nxt_state : states;

    -- UART --
        component UART_TX_string
            generic 
            (
                baud_freq : INTEGER;
                clk_freq : INTEGER
            );
            port 
            (
                i_CLK : in STD_LOGIC;
                i_RST : in STD_LOGIC;
                i_string : in STD_LOGIC_VECTOR(623 downto 0);
                i_ST : in STD_LOGIC;
                o_RDY : out STD_LOGIC;
                o_TX : out STD_LOGIC
            );
        end component;

        signal TX_message  : STD_LOGIC_VECTOR(623 downto 0);
        signal TX_ST      : STD_LOGIC := '0';
        
        signal TX_RDY     : STD_LOGIC;

    -- LCD -- 
        component LCD_putstring is
            generic 
            (
                clk_freq    : INTEGER          -- Frecuencia del reloj (Hz)
            );
            port
            (
                i_RST               : in STD_LOGIC;                         -- Reinicio de maquina de estados
                i_CLK               : in STD_LOGIC;
                o_RS, o_E, o_RW     : out STD_LOGIC;
                o_LCD_DATA          : out std_logic_vector(7 downto 0);      -- 8 Bits ASCII
                i_ST                : in STD_LOGIC;                         -- Señal de start
                i_string            : in STD_LOGIC_VECTOR(255 downto 0);    -- Cadena de 33 caracteres (32 char y un salto de linea)
                o_RDY               : out STD_LOGIC                        -- Indicador de listo para imprimir
            );
        end component;
        
        signal LCD_ST : STD_LOGIC := '0';
        signal LCD_message : STD_LOGIC_VECTOR(255 downto 0) := STD_LOGIC_VECTOR(to_unsigned(0, 256)); 
        
        signal LCD_RDY : STD_LOGIC;

    -- Cola de distancias --
        component Distance_queue
            generic 
            (
                baud_freq : INTEGER;
                clk_freq : INTEGER
            );
            port 
            (
                i_CLK : in STD_LOGIC;
                i_RST : in STD_LOGIC;
                i_data_read : in STD_LOGIC;
                o_queue : out STD_LOGIC;
                o_dist : out STD_LOGIC_VECTOR(1 downto 0);
                i_RX : in STD_LOGIC
            );
        end component;

        signal QUEUE_RST : STD_LOGIC;
        signal QUEUE_RST_aux : STD_LOGIC;
        signal QUEUE_read : STD_LOGIC;
        signal QUEUE_queue : STD_LOGIC;
        signal QUEUE_dist : STD_LOGIC_VECTOR(1 downto 0);

    -- STEPPER MOTOR --
        component Stepper_motor
            generic 
            (
                clk_freq : INTEGER
            );
            port 
            (
                i_FPGA_clk : in STD_LOGIC;
                i_RST : in STD_LOGIC;
                i_ON : in STD_LOGIC;
                i_DIR : in STD_LOGIC;
                o_STEPS : out STD_LOGIC_VECTOR(3 downto 0);
                o_done_steps : out INTEGER;
                i_step_freq : in INTEGER
            );
        end component;

        signal STEP_ON      : STD_LOGIC;         -- Start
        signal STEP_DIR     : STD_LOGIC;        -- Direccion de giro
        signal STEP_done    : INTEGER;         -- Pasos recorridos
        signal STEP_freq    : INTEGER := 10;    -- Velocidad

        signal STEP_num : INTEGER;          -- Pasos a recorrer

begin
    QUEUE_RST <= (not i_RST) or QUEUE_RST_aux;

    ------------------------------------------------------------------------------
                                     -- STEPPER MOTOR --
    ------------------------------------------------------------------------------
    STEPS : Stepper_motor
        generic map ( clk_freq => clk_freq )    
        port map ( i_RST => not i_RST, i_FPGA_clk => i_FPGA_clk, i_ON => STEP_ON, i_DIR => STEP_DIR, o_STEPS => o_STEPS, o_done_steps => STEP_done, i_step_freq => STEP_freq);
    
    ------------------------------------------------------------------------------
                                        -- L C D --
    ------------------------------------------------------------------------------
    c_LCD : LCD_putstring
        generic map ( clk_freq => clk_freq )
        port map ( i_RST => not i_RST, i_CLK => i_FPGA_clk, o_RS => o_RS, o_E => o_E, o_RW => o_RW, o_LCD_DATA => o_LCD_DATA, i_ST => LCD_ST, i_string => LCD_message, o_RDY => LCD_RDY );
    ------------------------------------------------------------------------------
                                    -- U A R T  T X --
    ------------------------------------------------------------------------------
    c_TX_message : UART_TX_string 
        generic map ( clk_freq => clk_freq, baud_freq => 9600 )
        port map ( i_RST => not i_RST, i_CLK => i_FPGA_clk, i_string => TX_message, i_ST => TX_ST, o_RDY => TX_RDY, o_TX => o_TX );
    ------------------------------------------------------------------------------
                                -- COLA DE DISTANCIAS --
    ------------------------------------------------------------------------------
    c_queue : Distance_queue
        generic map ( clk_freq => clk_freq, baud_freq => 9600 )
        port map ( i_RST => QUEUE_RST, i_CLK => i_FPGA_clk, i_data_read => QUEUE_read, o_queue => QUEUE_queue, o_dist => QUEUE_dist, i_RX => i_RX );    
    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    c_P10_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => P10_freq, i_FPGA_clk => i_FPGA_clk, o_clk => P10_CLK );

    process (P10_CLK, i_RST)
        variable clks : integer := 0;
        variable l_STN : STD_LOGIC_VECTOR(7 downto 0);
    begin
        if (i_RST = not '1') then                           -- Se presiono RST
            act_state <= PRINT_IDLE;

        elsif (rising_edge(P10_CLK)) then
            case act_state is
                when LCD_SEND =>                            -- Estado para mandar mensajes a LCD
                    -- Salidas del estado
                    LCD_ST <= '1'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0';

                    -- Estado futuro
                    if (LCD_RDY = '0') then                	-- Se esta imprimiendo el mensaje
                        act_state <= LCD_nxt_state;
                    else
                        act_state <= LCD_SEND;
                    end if;
                
                when TX_SEND =>                             -- Estado para mandar mensajes a TX
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '1'; STEP_ON <= '0'; QUEUE_read <= '0';

                    -- Estado futuro
                    if (TX_RDY = '0') then                      -- Se esta imprimiendo el mensaje
                        act_state <= TX_nxt_state;
                    else
                        act_state <= TX_SEND;
                    end if;

                when PRINT_IDLE =>                    -- Enviamos informacion correspondiente a LCD y/o UART      
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0';

                    LCD_message <= 
                        l_sp & l_MM & l_o & l_d & l_o & l_sp & l_d & l_e & l_sp & l_e & l_s & l_p & l_e & l_r & l_a & l_sp &
                        l_EE & l_n & l_v & l_i & l_a & l_r & l_sp & l_d & l_i & l_s & l_t & l_a & l_n & l_c & l_i & l_a;

                    TX_message <= l_PP & l_r & l_e & l_s & l_i & l_o & l_n & l_e & l_sp & l_e & l_l & l_sp & l_n & l_u &
                    l_m & l_e & l_r & l_o & l_sp & l_d & l_e & l_sp & l_l & l_a & l_sp & l_d & l_i & l_s & l_t & l_a & l_n & l_c & l_i & l_a & l_sp & l_a & l_sp & l_r & l_e & l_c & l_o & l_r & l_r & l_e & l_r & l_EL & l_1 & l_dot & l_sp & l_1 & l_sp & l_c & l_m & l_EL & l_2 & l_dot & l_sp & l_3 & l_sp & l_c & l_m & l_EL & l_3 & l_dot & l_sp & l_5 & l_sp & l_c & l_m & l_EL & l_4 & l_dot & l_sp & l_7 & l_sp & l_c & l_m & l_EL;

                    -- Estado futuro
                    if (LCD_RDY = '1' and TX_RDY = '1') then        -- Enviaremos un mensaje a LCD y UART
                        act_state       <= LCD_SEND;
                        LCD_nxt_state   <= TX_SEND;
                        TX_nxt_state    <= IDLE;
                    else
                        act_state <= PRINT_IDLE;
                    end if;
                
                when IDLE =>                                -- Esperamos a que haya distancias pendientes
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0';

                    -- Estado futuro
                    if (QUEUE_queue = '1' and i_START = '1') then -- Hay distancias pendientes y el motor esta listo
                        act_state <= PRINT_COUPLING;
                    else
                        act_state <= IDLE;
                    end if;
                    
                when PRINT_COUPLING =>
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0';

                    -- Almacenamos distancia de la cola de distnacia
                    case QUEUE_dist is
                        when "00" =>
                            STEP_num <= 19;
                            l_STN := l_1;                            
                        when "01" =>
                            STEP_num <= 54;
                            l_STN := l_3;                            
                        when "10" =>
                            STEP_num <= 89;
                            l_STN := l_5;                            
                        when "11" =>
                            STEP_num <= 124;                            
                            l_STN := l_7;                            
                        when others => null;
                    end case;
                    
                    LCD_message <= 
                        l_sp & l_sp & l_sp & l_SS & l_EE & l_LL & l_EE & l_CC & l_CC & l_II & l_OO & l_NN & l_OO & l_sp & l_sp & l_sp &
                        l_sp & l_sp & l_sp & l_sp & l_sp & l_sp & l_STN & l_sp & l_CC & l_MM & l_sp & l_sp & l_sp & l_sp & l_sp & l_sp;

                    -- Estado futuro
                    if (LCD_RDY = '1') then               -- Enviaremos un mensaje a LCD
                        QUEUE_read      <= '1';
                        STEP_DIR        <= '1';                             -- Direccion de acoplamiento

                        act_state       <= LCD_SEND;
                        LCD_nxt_state   <= COUPLING;
                    else
                        act_state <= PRINT_COUPLING;
                    end if;

                when COUPLING =>                        -- Tenemos distancia de acoplamiento
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '1'; QUEUE_read <= '0';
                    
                    -- Estado futuro
                    if (i_STOP = '1') then              -- Detectamos boton de stop
                        QUEUE_RST_aux <= '1';           -- Reiniciamos cola de distancias
                        
                        -- Establecemos distancia proxima
                        if (STEP_DIR = '1') then        -- Si estabamos avanzando
                            STEP_num <= STEP_done;
                            STOP_nxt_state <= WAIT_2SEC;
                        else
                            STEP_num <= STEP_num - STEP_done;
                            STOP_nxt_state <= COUPLING;
                        end if;

                        act_state <= PRINT_STOP;

                    elsif (STEP_done = STEP_num) then
                        clks := 0;
                        act_state <= WAIT_2SEC;
                    else
                        act_state <= COUPLING;
                    end if;

                when WAIT_2SEC =>                               -- Esperamos 2 segundos
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0';
                    -- DIR = '1' IDA | DIR = '0' VUELTA 

                    clks := clks + 1;
                        
                    if (QUEUE_queue = '0' and STEP_DIR = '0') then      -- No hay cola de distancias
                        act_state <= PRINT_IDLE;
                    elsif (clks = (P10_freq * 2) or i_STOP = '1') then                  -- Hay cola de distancias y pasaron 2 segundos
                        if (STEP_DIR = '1') then                        -- Se completo ida
                            act_state <= COUPLING;
                            STEP_DIR <= '0';
                        else                            -- Se completo vuelta y hay cola de distancias
                            act_state <= PRINT_COUPLING;
                        end if;
                        -- Posible error con condicion STOP
                    else
                        act_state <= WAIT_2SEC;
                    end if;

                when PRINT_STOP =>
                    -- Salidas del estado
                    LCD_ST <= '0'; TX_ST <= '0'; STEP_ON <= '0'; QUEUE_read <= '0'; 
                    QUEUE_RST_aux <= '1';
                    -- Se detiene el motor y se finaliza el reseteo de cola
                    
                    LCD_message <= 
                        l_sp & l_sp & l_sp & l_sp & l_PP & l_RR & l_EE & l_SS & l_II & l_OO & l_NN & l_OO & l_sp & l_sp & l_sp & l_sp &
                        l_sp & l_sp & l_sp & l_sp & l_sp & l_sp & l_SS & l_TT & l_OO & l_PP & l_sp & l_sp & l_sp & l_sp & l_sp & l_sp;

                    -- Estado futuro
                    if (LCD_RDY = '1' and i_STOP = '0') then               -- Enviaremos un mensaje a LCD
                        QUEUE_RST_aux   <= '0';

                        act_state       <= LCD_SEND;
                        LCD_nxt_state   <= STOP_nxt_state;
                    else
                        act_state <= PRINT_STOP;
                    end if;
            end case;
        end if;
    end process;

    process (i_VEL)         -- Si detecto un cambio de velocidad
    begin
        case i_VEL is
            when "01" =>        -- Velocidad baja
                STEP_freq <= 10;
            when "10" =>        -- Velocidad alta
                STEP_freq <= 30;
            when others => null;    -- Se presionaron ambos
        end case;
    end process;

end architecture;

-- FALTA BOTON DE STOP, definir pasos y velocidades