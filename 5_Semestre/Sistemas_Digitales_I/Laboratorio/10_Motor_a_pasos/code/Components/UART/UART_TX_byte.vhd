library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------
entity UART_TX_byte is
	generic 
    (
        clk_freq    : INTEGER;          -- Frecuencia del reloj (Hz)
        baud_freq   : INTEGER           -- Baudios de transmision (bit/s)
    );
    port
	(
		i_FPGA_clk      : in STD_LOGIC;                         -- Señal de reloj base
        i_data          : in STD_LOGIC_VECTOR(7 downto 0);      -- Caracter a transmitir
        i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision

        o_RDY           : out STD_LOGIC;        -- Indica si esta listo para transmitir 
        o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
	);
end UART_TX_byte;
------------------------------------------------------------------------------
architecture byte_tx of UART_TX_byte is

    component CLK_DIV is
        generic 
        (
            clk_freq    : integer          -- Frecuencia interna de FPGA (Hz)
        );
        port
        (
            i_out_freq      : integer;              -- Frequencia deseada
            
            i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
            o_clk           : out STD_LOGIC    
        );
    end component;

    -- Señal para division de reloj
    signal UART_clk     : STD_LOGIC;
    signal out_freq     : integer := clk_freq;
    
    -- Señales para transicion de estados
    type states is (IDLE, START_BIT, DATA_BITS, PARITY_BIT, STOP_BIT);
    signal act_state, next_state: states := IDLE; 

    signal data_index   : integer range 0 to 7 := 0;
    
begin
------------------------------------------------------------------------------
                            -- DIVISION DE RELOJ --
------------------------------------------------------------------------------

    c_UART_CLK : CLK_DIV 
        generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => out_freq, i_FPGA_clk => i_FPGA_clk, o_clk => UART_clk );
    

------------------------------------------------------------------------------
                        -- MAQUINA DE ESTADOS FINITOS --
------------------------------------------------------------------------------ 
    process (UART_clk)
    begin
        if rising_edge(UART_clk) then
            act_state <= next_state;        -- Ver si poner al final
    
            case act_state  is
                when IDLE =>
                    
                    o_TX        <= '1';             -- TX en 1
                    o_RDY       <= '1';             -- Esta listo para transmitir
                    
                    out_freq <= clk_freq;
    
                    -- Actualizamos estado futuro en funcion de las entradas
                    if i_ST = '1' then             -- Inicio de transmision
                        next_state <= START_BIT;
                    else
                        next_state <= IDLE;
                    end if;
            
                when START_BIT =>
                
                    o_TX     <= '0';                -- TX en 0 (Bit de start)
                    o_RDY   <= '0';                 -- No esta listo para transmitir
            
                    out_freq <= baud_freq;
    
                    next_state <= DATA_BITS;
                
                when DATA_BITS =>
                    
                    o_TX    <= i_data(data_index);  -- Enviamos cada bit del byte
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                    
                    -- Modificamos contadores e indices
                    data_index  <= data_index + 1;
                    out_freq <= baud_freq;
    
                    if data_index < 7 then
                        next_state <= DATA_BITS;
                    else
                        next_state <= PARITY_BIT;
                        data_index <= 0;
                    end if;
    
                when PARITY_BIT =>
    
                    o_TX     <= (i_data(0) xor i_data(1)) xor (i_data(2) xor i_data(3) xor (i_data(4) xor i_data(5) xor (i_data(6) xor i_data(7))));           -- Enviamos bit de paridad
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                    
                    out_freq <= baud_freq;
    
                    next_state <= STOP_BIT;
                    
                when STOP_BIT =>
                    
                    o_TX    <= '1';                 -- Enviamos bit de stop
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                    
                    out_freq <= baud_freq;
                    
                    next_state <= IDLE;
                    
                when others => null;
            end case;
        end if;
    end process;

end byte_tx;