-- Este componente recibe y maneja la cola de distancias recibidas
-- EL algoritmo es de la siguiente forma
-- 1. Hay una cola de distancias procesadas por este componente, por lo que o_queue = '1'
-- 2. Se completa una distancia y se recibe la señal i_data_read
-- 3. Se actualiza el ultimo dato de distancia y se manda una señal a 
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Distance_queue is
    generic 
    (
        baud_freq       : INTEGER;   
        clk_freq        : INTEGER   
    );
    port
    (
        i_CLK       : in STD_LOGIC;         -- Señal de reloj base
        i_RST       : in STD_LOGIC;         -- Reinicio total

        i_data_read  : in STD_LOGIC;         -- Indica si la distancia se leyo
        o_queue     : out STD_LOGIC;        -- Indica si hay distancias pendientes

        o_dist      : out STD_LOGIC_VECTOR(1 downto 0);     -- Indica cual de las 4 distancias se recibio (0-3)

        -- UART
        i_RX                : in STD_LOGIC
    );
end Distance_queue;

architecture rtl of Distance_queue is
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

        signal QUEUE_CLK : STD_LOGIC;   
    -- MAQUINA DE ESTADOS FINITOS --
        type states1 is (IDLE, STORE_DATA, WAIT_RCV);
        signal GET_act_state : states1 := IDLE;
        
        type states2 is (IDLE, UPT_DIST, WAIT_READ);
        signal SET_act_state : states2 := IDLE;
        
    -- UART RX --
        component UART_RX
            generic 
            (
                baud_freq : INTEGER;
                clk_freq : INTEGER
            );
            port 
            (
                i_FPGA_CLK : in STD_LOGIC;
                i_RST : in STD_LOGIC;
                i_RX : in STD_LOGIC;
                o_RCV : out STD_LOGIC;
                o_DATA : out STD_LOGIC_VECTOR(7 downto 0)
            );
        end component;

        signal RX_RCV : STD_LOGIC; 
        signal RX_DATA : STD_LOGIC_VECTOR(7 downto 0); 
    
    -- SEÑALES --
        type array_50 is array (0 to 49) of STD_LOGIC_VECTOR(1 downto 0);
        signal distance_queue   : array_50;
        signal stored_index     : INTEGER := 0;     -- Indice para almacenamiento de distancias
        signal send_index       : INTEGER := 0;     -- Indice para distancia enviada

begin
    ------------------------------------------------------------------------------
                                    -- UART RX --
    ------------------------------------------------------------------------------
    RX_Receive : UART_RX
        generic map( baud_freq => baud_freq, clk_freq => clk_freq )
        port map( i_FPGA_CLK => i_CLK, i_RST => i_RST, i_RX => i_RX, o_RCV => RX_RCV, o_DATA => RX_DATA );
    ------------------------------------------------------------------------------
            -- MAQUINA DE ESTADOS FINITOS PROCESADORA DE DATOS DE RX --
    ------------------------------------------------------------------------------
    c_QUEUE_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => 1000000, i_FPGA_clk => i_CLK, o_clk => QUEUE_CLK );
    
    process (QUEUE_CLK, i_RST)
    begin
        if (i_RST = '1') then                           -- Se presiono RST
            stored_index <= 0;
            GET_act_state <= IDLE;
        elsif (rising_edge(QUEUE_CLK)) then
            case GET_act_state is
                when IDLE =>
                    -- Estado proximo
                    if (RX_RCV = '1') then   -- Recibimos un dato del puerto serial
                        GET_act_state <= STORE_DATA;
                    else
                        GET_act_state <= IDLE;
                    end if;
                
                when STORE_DATA =>
                    
                    -- Salidas del estado
                    case RX_DATA is
                        when X"31" =>
                            distance_queue(stored_index) <= "00";
                            stored_index <= stored_index + 1;
                        when X"32" =>
                            distance_queue(stored_index) <= "01";
                            stored_index <= stored_index + 1;
                        when X"33" =>
                            distance_queue(stored_index) <= "10";
                            stored_index <= stored_index + 1;
                        when X"34" =>
                            distance_queue(stored_index) <= "11";
                            stored_index <= stored_index + 1;
                        when others => null;
                    end case; 
                    
                    -- Estado proximo
                    GET_act_state <= WAIT_RCV;

                when WAIT_RCV =>            -- Estado para esperar a que RCV se vuelva 0
                    
                    -- Estado proximo
                    if (RX_RCV = '0') then      -- Para evitar leer 2 veces el mismo dato
                        GET_act_state <= IDLE;
                    else
                        GET_act_state <= WAIT_RCV;
                    end if;

                when others => null;
            end case;
        end if;
    end process;

    ------------------------------------------------------------------------------
                -- MAQUINA DE ESTADOS FINITOS GESTORA DE COLA --
    ------------------------------------------------------------------------------
    process (QUEUE_CLK, i_RST)
    begin
        if (i_RST = '1') then                           -- Se presiono RST
            send_index <= 0;
            SET_act_state <= IDLE;
        elsif (rising_edge(QUEUE_CLK)) then
            case SET_act_state is
                when IDLE =>            -- En espera de datos en cola
                    -- Salidas del estado
                    o_queue <= '0';                 -- No sabemos si hay cola
                    o_dist <= "00";
                    
                    -- Estado proximo
                    if (stored_index > send_index and i_data_read = '0') then         -- Si detectamos que hay cola pendiente
                        SET_act_state <= UPT_DIST;
                    else
                        SET_act_state <= IDLE;
                    end if;
                    -- Stored index nos dice cuantas distancias almacenadas hay, al recibir DONE aumentamos send_index para indicar las distancias recorridas
                
                when UPT_DIST =>            -- Actualizamos distancia
                    -- Salidas del estado
                    o_queue <= '1';                             -- Indicamos que hay cola
                    o_dist <= distance_queue(send_index);       -- Actualizamos la distancia

                    send_index <= send_index + 1;

                    -- Estado proximo
                    SET_act_state <= WAIT_READ;
                    
                when WAIT_READ =>       -- Esperamos finalizacion de distancia
                    -- Salidas del estado
                    o_queue <= '1';
                    
                    -- Estado proximo
                    if (i_data_read = '1') then       -- Nos indican que se leyo la distancia                        
                        SET_act_state <= IDLE;
                    else
                        SET_act_state <= WAIT_READ;
                    end if;

                when others => null;
            end case;
        end if;
    end process;

end architecture;