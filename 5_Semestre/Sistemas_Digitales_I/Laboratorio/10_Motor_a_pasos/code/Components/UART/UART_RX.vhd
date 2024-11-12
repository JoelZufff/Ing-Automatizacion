library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity UART_RX is
    generic 
    (
        baud_freq       : INTEGER;
        clk_freq        : INTEGER   
    );
	port
	(
		i_FPGA_CLK      : in STD_LOGIC;                         -- Oscilador de placa (50 MHz)
		i_RST           : in STD_LOGIC;                         -- Boton de reset (Para errores de paridad)

        i_RX            : in STD_LOGIC;                         -- Reception PIN
        o_RCV           : out STD_LOGIC;                        -- Indica que se recibio un nuevo dato
        o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato receptado
	); 
end UART_RX;

architecture Reception of UART_RX is     
    -- Division de reloj
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
        
        signal UART_CLK : STD_LOGIC;
        signal UART_CLK_freq : integer := clk_freq;

    -- Maquina de estado
        type States is (IDLE, DATA_RECEIVE);
        signal act_state : States := IDLE; -- Ponemos en estado inicial la maquina
    
    -- Señales para muestreo de dato
        signal middle   : STD_LOGIC := '0';
        signal data_index : integer range 0 to 9 := 0;
        signal DATA     : STD_LOGIC_VECTOR(7 downto 0) := X"41";
        signal parity   : STD_LOGIC;
    
begin    

    ------------------------------------------------------------------------------
                -- DIVISION DE RELOJ PARA BAUDIOS DE RECEPCION --
    ------------------------------------------------------------------------------
    c_UART_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => UART_CLK_freq, i_FPGA_clk => i_FPGA_clk, o_clk => UART_clk );

    ------------------------------------------------------------------------------
                        -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (UART_CLK, i_RST)
    begin
        if (i_RST = '1') then
            act_state <= IDLE;

        elsif rising_edge(UART_CLK) then      -- Si detectamos un flanco de subida
            case act_state  is
                when IDLE =>
                    -- Salida de estado actual
                    o_RCV <= '0';
    
                    UART_CLK_freq <= clk_freq;      -- Esperamos señal de start a maxima velocidad

                    -- Estado futuro en funcion de entradas
                    if (i_RX = '0') then        -- Se detecto bit de start
                        UART_CLK_freq <= baud_freq * 2;     -- Para detectar la mitar del bit
                        
                        data_index  <= 0;
                        middle <= '1';      -- El siguiente ciclo es la mitad del bit
                        
                        act_state  <= DATA_RECEIVE;
                    else
                        act_state <= IDLE;
                    end if;
    
                when DATA_RECEIVE =>
                    -- Salida de estado actual
                    o_RCV <= '0';
 
                    if (middle = '1') then      -- Nos ayuda a conmutar la lectura del dato
                        if (data_index = 0) then      -- Bit de start, ignorar
                            
                            data_index <= data_index + 1;

                            -- Estado siguiente
                            act_state <= DATA_RECEIVE;
                        
                        elsif data_index < 9 then
                            
                            DATA(data_index - 1) <= i_RX; -- Captura del bit
                            data_index <= data_index + 1;

                            -- Estado siguiente
                            act_state <= DATA_RECEIVE;
                        
                        elsif data_index = 9 then   -- Bit de paridad
                            
                            parity <= i_RX; -- Captura del bit de paridad
                            
                            o_DATA <= DATA;
                            o_RCV <= '1';       -- Enviamos señal de dato recibido

                            -- Estado siguiente
                            act_state <= IDLE;
                        
                        end if;
                    end if;

                    middle <= not middle;

                when others => null;
            end case;

        end if;
    end process;

end Reception;