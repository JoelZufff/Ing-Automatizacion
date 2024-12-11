library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity UART_TX_string is
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
        i_string        : in STD_LOGIC_VECTOR(623 downto 0);    -- 79 caracteres maximo
        i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision
        o_RDY           : out STD_LOGIC;                        -- Indica si esta listo para transmitir 
        
        -- I/O Fisicas
        o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
	);
end UART_TX_string;
------------------------------------------------------------------------------
architecture transmit of UART_TX_string is    
    -- DIVISION DE RELOJ --
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

        signal UART_clk     : STD_LOGIC;
    
    -- UART_TX_byte --
        component UART_TX_byte is
            generic 
            (
                clk_freq    : INTEGER;          -- Frecuencia del reloj (Hz)
                baud_freq   : INTEGER           -- Baudios de transmision (bit/s)
            );
            port
            (
                i_FPGA_clk      : in STD_LOGIC;                         -- Señal de reloj base
                i_RST           : in STD_LOGIC;                         -- Señal de RST
                i_DATA          : in STD_LOGIC_VECTOR(7 downto 0);      -- Dato a enviar
                i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision
        
                o_RDY           : out STD_LOGIC;        -- Indica si esta listo para transmitir 
                o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
            );
        end component;
    
        signal UART_RDY     : STD_LOGIC;
        signal UART_ST      : STD_LOGIC;
        signal UART_DATA    : STD_LOGIC_VECTOR(7 downto 0);
            
        signal char_index   : integer := 0;
    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE, WAIT_RDY, SEND_CHAR);
        signal act_state : states := IDLE; 

begin
    ------------------------------------------------------------------------------
                                -- DIVISION DE RELOJ --
    ------------------------------------------------------------------------------
    c_UART_CLK : CLK_DIV
    generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => baud_freq, i_CLK => i_CLK, o_CLK => UART_clk );
    ------------------------------------------------------------------------------
                            -- COMPONENTE UART_TX_BYTE --
    ------------------------------------------------------------------------------
    TX_byte : UART_TX_byte
        generic map ( clk_freq => clk_freq, baud_freq => baud_freq )
        port map ( i_FPGA_clk => i_CLK, i_RST => i_RST, i_DATA => UART_DATA, i_ST => UART_ST, o_RDY => UART_RDY, o_TX => o_TX );
    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------ 
    process (UART_clk, i_RST, i_ST)                      
    begin
        if (i_RST = '1') then
            act_state <= IDLE;

        elsif rising_edge(UART_clk) then
            case act_state  is
                when IDLE =>
                    o_RDY       <= '1';             -- Esta listo para transmitir
                    UART_ST     <= '0';

                    char_index <= 0;

                    -- Actualizamos estado futuro en funcion de las entradas
                    if (i_ST = '1') then             -- Inicio de transmision
                        act_state <= WAIT_RDY;
                    else
                        act_state <= IDLE;
                    end if;
                
                when WAIT_RDY =>
                    o_RDY       <= '0';             -- Esta listo para transmitir
                    UART_ST     <= '0';

                    if (i_ST = '0' and UART_RDY = '1') then     -- Si recibimos señal de start 
                        act_state <= SEND_CHAR;
                    else
                        act_state <= WAIT_RDY;
                    end if;
                    
                when SEND_CHAR =>
                    o_RDY       <= '0';
                    UART_ST     <= '1'; UART_DATA <= i_string(623 - (char_index * 8) downto 616 - (char_index * 8));

                    
                    if (char_index = 79) then           -- Longitud maxima
                        act_state <= IDLE;
                    elsif (UART_RDY = '0') then         -- Se esta imprimiendo el caracter
                        char_index <= char_index + 1;
                        act_state <= WAIT_RDY;
                    else
                        act_state <= SEND_CHAR;
                    end if;

                when others => null;
            end case;

        end if;
    end process;

end transmit;