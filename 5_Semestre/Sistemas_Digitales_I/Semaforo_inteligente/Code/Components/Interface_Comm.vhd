------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity Interface_Comm is
    generic 
    (
        CLK_FREQ    : INTEGER
    );
    port
    (
        i_CLK           : in STD_LOGIC;                         -- Señal de reloj base
        i_RST           : in STD_LOGIC;                         -- Señal de reset

        i_TEMP          : in STD_LOGIC_VECTOR(7 downto 0);      -- Variable de temperatura
        i_PTL_DIST      : in STD_LOGIC_VECTOR(7 downto 0);      -- Distancia de peaton

        -- Variables de flujo
        i_NS_CAR_FLOW   : in STD_LOGIC_VECTOR(7 downto 0);      -- Flujo NORTE-SUR
        i_SN_CAR_FLOW   : in STD_LOGIC_VECTOR(7 downto 0);      -- Flujo SUR_NORTE
        i_EW_CAR_FLOW   : in STD_LOGIC_VECTOR(7 downto 0);      -- Flujo ESTE-OESTE
        i_WE_CAR_FLOW   : in STD_LOGIC_VECTOR(7 downto 0);      -- Flujo OESTE-ESTE

        -- I/O fisicos UART
        i_RX        : in STD_LOGIC;                             -- Receptor
        o_TX        : out STD_LOGIC                             -- Transmisor
    );
end Interface_Comm;
------------------------------------------------------------------------------
architecture rtl of Interface_Comm is
    -- CONSTANTES --
        constant l_0 : STD_LOGIC_VECTOR(7 downto 0) := X"30";
        
        constant l_plus : STD_LOGIC_VECTOR(7 downto 0) := X"2B";
        constant l_sp : STD_LOGIC_VECTOR(7 downto 0) := X"20";
        constant l_EL : STD_LOGIC_VECTOR(7 downto 0) := X"0A";      -- End Line

    -- DIVISOR DE RELOJ --
        constant INT_FREQ : INTEGER := 1000000;

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

        signal INT_CLK : STD_LOGIC;
        signal clks : INTEGER := 0;

    -- MAQUINA DE ESTADOS FINITOS --
        type states is (TX_SEND, SEND_TEMP, SEND_NS_CAR_FLOW, SEND_SN_CAR_FLOW, SEND_EW_CAR_FLOW, SEND_WE_CAR_FLOW, SEND_PTL_DIST, WAIT_TIME );
        
        signal act_state : states := SEND_TEMP;
        signal TX_nxt_state : states;

    -- UART --
        component UART_TX_string is
            generic 
            (
                baud_freq   : INTEGER;          -- Frecuencia de transmision (bit/s)
                clk_freq    : INTEGER          -- Frecuencia del reloj (Hz)
            );
            port
            (
                i_CLK           : in STD_LOGIC;                         -- Señal de reloj base
                i_RST           : in STD_LOGIC;                         -- Señal de RST
                
                -- I/O
                i_string        : in STD_LOGIC_VECTOR(39 downto 0);    -- 79 caracteres maximo
                i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision
                o_RDY           : out STD_LOGIC;                        -- Indica si esta listo para transmitir 
                
                -- I/O Fisicas
                o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
            );
        end component;

        signal TX_message   : STD_LOGIC_VECTOR(39 downto 0);
        signal TX_ST        : STD_LOGIC;
        signal TX_RDY       : STD_LOGIC;

    -- DECODER BCD DE 1 byte --
        component BCD_byte is
            port 
            (
                i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);
                o_DATA      : out STD_LOGIC_VECTOR(9 downto 0) 
            );
        end component;
        
        signal BCD_TEMP         : std_logic_vector(9 downto 0) := "0000000000";
        signal BCD_PTL_DIST     : std_logic_vector(9 downto 0) := "0000000000";
        signal BCD_NS_CAR_FLOW  : std_logic_vector(9 downto 0) := "0000000000";
        signal BCD_SN_CAR_FLOW  : std_logic_vector(9 downto 0) := "0000000000";
        signal BCD_EW_CAR_FLOW  : std_logic_vector(9 downto 0) := "0000000000";
        signal BCD_WE_CAR_FLOW  : std_logic_vector(9 downto 0) := "0000000000";

begin

    ------------------------------------------------------------------------------
                                -- DECODER's BCD BYTE --
    ------------------------------------------------------------------------------
    c_BCD_TEMP : BCD_byte
        port map ( i_DATA => i_TEMP, o_DATA => BCD_TEMP );

    c_BCD_PTL_DIST : BCD_byte
        port map ( i_DATA => i_PTL_DIST, o_DATA => BCD_PTL_DIST );

    c_BCD_NS_CAR_FLOW : BCD_byte
        port map ( i_DATA => i_NS_CAR_FLOW, o_DATA => BCD_NS_CAR_FLOW );
    
    c_BCD_SN_CAR_FLOW : BCD_byte
        port map ( i_DATA => i_SN_CAR_FLOW, o_DATA => BCD_SN_CAR_FLOW );

    c_BCD_EW_CAR_FLOW : BCD_byte
        port map ( i_DATA => i_EW_CAR_FLOW, o_DATA => BCD_EW_CAR_FLOW );

    c_BCD_WE_CAR_FLOW : BCD_byte
        port map ( i_DATA => i_WE_CAR_FLOW, o_DATA => BCD_WE_CAR_FLOW );
    
    ------------------------------------------------------------------------------
                                    -- U A R T  T X --
    ------------------------------------------------------------------------------
    c_TX_message : UART_TX_string 
        generic map ( clk_freq => clk_freq, baud_freq => 9600 )
        port map ( i_RST => i_RST, i_CLK => i_CLK, i_string => TX_message, i_ST => TX_ST, o_RDY => TX_RDY, o_TX => o_TX );

    ------------------------------------------------------------------------------
                                -- DIVISOR DE RELOJ --
    ------------------------------------------------------------------------------
    c_TEM_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => INT_FREQ, i_CLK => i_CLK, o_CLK => INT_CLK );

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (INT_CLK, i_RST)
    begin
        if (i_RST = '1') then
            act_state <= SEND_TEMP;

        elsif rising_edge(INT_CLK) then
            case act_state is
                when TX_SEND =>                             -- Estado para mandar mensajes a TX
                    -- Salidas del estado
                    TX_ST <= '1';

                    -- Estado futuro
                    if (TX_RDY = '0') then                      -- Se esta imprimiendo el mensaje
                        act_state <= TX_nxt_state;
                    else
                        act_state <= TX_SEND;
                    end if;
                
                when SEND_TEMP =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= l_plus & X"30" & STD_LOGIC_VECTOR(unsigned("0000" & BCD_TEMP(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_TEMP(3 downto 0)) + 48) & l_EL;

                        act_state <= TX_SEND;
                        TX_nxt_state <= SEND_NS_CAR_FLOW;
                    else
                        act_state <= SEND_TEMP;
                    end if;

                when SEND_NS_CAR_FLOW =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= X"30" & STD_LOGIC_VECTOR(unsigned("0000" & BCD_NS_CAR_FLOW(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_NS_CAR_FLOW(3 downto 0)) + 48) & l_sp & l_EL;

                        act_state <= TX_SEND;
                        TX_nxt_state <= SEND_SN_CAR_FLOW;
                    else
                        act_state <= SEND_NS_CAR_FLOW;
                    end if;

                when SEND_SN_CAR_FLOW =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= X"30" & STD_LOGIC_VECTOR(unsigned("0000" & BCD_SN_CAR_FLOW(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_SN_CAR_FLOW(3 downto 0)) + 48) & l_sp & l_EL;

                        act_state <= TX_SEND;
                        TX_nxt_state <= SEND_EW_CAR_FLOW;
                    else
                        act_state <= SEND_SN_CAR_FLOW;
                    end if;

                when SEND_EW_CAR_FLOW =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= X"30" & STD_LOGIC_VECTOR(unsigned("0000" & BCD_EW_CAR_FLOW(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_EW_CAR_FLOW(3 downto 0)) + 48) & l_sp & l_EL;

                        act_state <= TX_SEND;
                        TX_nxt_state <= SEND_WE_CAR_FLOW;
                    else
                        act_state <= SEND_EW_CAR_FLOW;
                    end if;

                when SEND_WE_CAR_FLOW =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= X"30" & STD_LOGIC_VECTOR(unsigned("0000" & BCD_WE_CAR_FLOW(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_WE_CAR_FLOW(3 downto 0)) + 48) & l_sp & l_EL;

                        act_state <= TX_SEND;
                        TX_nxt_state <= SEND_PTL_DIST;
                    else
                        act_state <= SEND_WE_CAR_FLOW;
                    end if;

                when SEND_PTL_DIST =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    -- Estado futuro
                    if (TX_RDY = '1') then
                        TX_message <= STD_LOGIC_VECTOR(unsigned("000000" & BCD_PTL_DIST(9 downto 8)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_PTL_DIST(7 downto 4)) + 48) & STD_LOGIC_VECTOR(unsigned("0000" & BCD_PTL_DIST(3 downto 0)) + 48) & l_sp & l_EL;

                        clks <= 0;

                        act_state <= TX_SEND;
                        TX_nxt_state <= WAIT_TIME;
                    else
                        act_state <= SEND_PTL_DIST;
                    end if;

                when WAIT_TIME =>
                    -- Salidas del estado
                    TX_ST <= '0';

                    clks <= clks + 1;

                    -- Estado futuro
                    if (clks = (INT_FREQ / 4)) then           -- Esperamos 1/4 segundo entre transmision
                        act_state <= SEND_TEMP;
                    else
                        act_state <= WAIT_TIME;
                    end if;
            
                when others => null;
            end case;
        end if;

    end process;

end architecture;