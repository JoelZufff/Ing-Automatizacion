-- Creado para enviar maximo 35 caracteres
-----------------------------------------------------------------------------
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
        i_CLK           : in STD_LOGIC;                         -- Señal de reloj base
        i_RST           : in STD_LOGIC;                         -- Señal de RST
        i_DATA          : in STD_LOGIC_VECTOR(7 downto 0);      -- Dato a enviar
        i_ST            : in STD_LOGIC;                         -- Señal para indicar inicio de transmision

        o_RDY           : out STD_LOGIC;        -- Indica si esta listo para transmitir 
        o_TX            : out STD_LOGIC         -- Pin TX de transmision serial 
	);
end UART_TX_byte;

------------------------------------------------------------------------------
architecture TX_BYTE of UART_TX_byte is    
    -- DIVISION DE RELOJ --
        component CLK_DIV is
            generic 
            (
                clk_freq    : integer          -- Frecuencia interna de FPGA (Hz)
            );
            port
            (
                i_out_freq      : integer;              -- Frequencia deseada
                
                i_CLK      : in STD_LOGIC;         -- Señal de reloj base
                -- Ver si poner RST
                o_clk           : out STD_LOGIC    
            );
        end component;

        signal UART_clk     : STD_LOGIC;
    
    -- MAQUINA DE ESTADOS FINITOS --
        type states is (IDLE, START_BIT, DATA_BITS, PARITY_BIT, STOP_BIT);
        signal act_state : states := IDLE; 

    signal data_index   : integer range 0 to 7 := 0;

begin
    ------------------------------------------------------------------------------
                                -- DIVISION DE RELOJ --
    ------------------------------------------------------------------------------
    c_UART_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => baud_freq, i_CLK => i_CLK, o_clk => UART_clk );
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
                    o_TX        <= '1';             -- TX en 1
                    o_RDY       <= '1';             -- Esta listo para transmitir
    
                    -- Actualizamos estado futuro en funcion de las entradas
                    if i_ST = '1' then             -- Inicio de transmision
                        data_index <= 0;
                        act_state <= START_BIT;
                    else
                        act_state <= IDLE;
                    end if;
            
                when START_BIT =>
                    o_TX     <= '0';                -- TX en 0 (Bit de start)
                    o_RDY   <= '0';                 -- No esta listo para transmitir
            
                    act_state <= DATA_BITS;
                
                when DATA_BITS =>
                    
                    o_TX    <= i_DATA(data_index);  -- Enviamos cada bit del byte
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                    
                    -- Modificamos contadores e indices
                    data_index  <= data_index + 1;
    
                    if data_index < 7 then
                        act_state <= DATA_BITS;
                    else
                        act_state <= PARITY_BIT;
                    end if;
    
                when PARITY_BIT =>
    
                    o_TX     <= (i_DATA(0) xor i_DATA(1)) xor (i_DATA(2) xor i_DATA(3) xor (i_DATA(4) xor i_DATA(5) xor (i_DATA(6) xor i_DATA(7))));           -- Enviamos bit de paridad
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                    
                    act_state <= STOP_BIT;
                    
                when STOP_BIT =>
                    
                    o_TX    <= '1';                 -- Enviamos bit de stop
                    o_RDY   <= '0';                 -- No esta listo para transmitir
                                    
                    if (i_ST = '0') then            -- Para evitar multiples envios involuntarios
                        act_state <= IDLE;
                    else
                        act_state <= STOP_BIT;
                    end if;
                    
                when others => null;
            end case;

        end if;
    end process;

end TX_BYTE;