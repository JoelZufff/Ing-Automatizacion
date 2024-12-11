-- Componente para recibir 1 byte por comunicacion serial
-- Al recibir 1 byte, envia un pulso en o_RCV para avisar una recepcion de dato
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity UART_RX_byte is
    generic 
    (
        BAUD_FREQ       : INTEGER;
        CLK_FREQ        : INTEGER   
    );
	port
	(
		i_CLK           : in STD_LOGIC;                         -- Señal de reloj
		i_RST           : in STD_LOGIC;                         -- Boton de reset

        i_RX            : in STD_LOGIC;                         -- Reception PIN
        
        o_RCV           : out STD_LOGIC;                        -- Envia un pulso indicando dato recibido
        o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato recibido
	); 
end UART_RX_byte;
------------------------------------------------------------------------------
architecture Reception of UART_RX_byte is
    -- Division de reloj
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
        
        signal UART_CLK : STD_LOGIC;
        signal UART_CLK_freq : integer := CLK_FREQ;

    -- Maquina de estado
        type States is (IDLE, DATA_RECEIVE);
        signal act_state : States := IDLE; -- Ponemos en estado inicial la maquina
    
    -- Señales para muestreo de dato
        signal MIDDLE       : STD_LOGIC := '0';
        signal DATA_INDEX   : integer range 0 to 9 := 0;

        signal DATA         : STD_LOGIC_VECTOR(7 downto 0);
        signal PARITY_BIT   : STD_LOGIC;
    
begin    

    ------------------------------------------------------------------------------
                -- DIVISION DE RELOJ PARA BAUDIOS DE RECEPCION --
    ------------------------------------------------------------------------------
    c_UART_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq ) 
        port map ( i_out_freq => UART_CLK_freq, i_CLK => i_CLK, o_clk => UART_CLK );

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

                    UART_CLK_freq <= CLK_FREQ;

                    -- Estado futuro en funcion de entradas
                    if (i_RX = '0') then        -- Se detecto bit de start
                        UART_CLK_freq <= BAUD_FREQ * 2;     -- Para detectar la mitar del bit
                        
                        DATA_INDEX  <= 0;
                        MIDDLE      <= '1';      -- El siguiente ciclo es la mitad del bit
                        
                        act_state   <= DATA_RECEIVE;
                    else
                        act_state   <= IDLE;
                    end if;
    
                when DATA_RECEIVE =>
                    -- Salida de estado actual
                    o_RCV <= '0';
 
                    if (MIDDLE = '1') then      -- Estamos en la mitad del bit
                        if (DATA_INDEX = 0) then        -- Bit de start
                            
                            DATA_INDEX <= DATA_INDEX + 1;

                            -- Estado siguiente
                            act_state <= DATA_RECEIVE;
                        
                        elsif DATA_INDEX < 9 then       -- Bits de datos
                            
                            DATA(DATA_INDEX - 1) <= i_RX;
                            DATA_INDEX <= DATA_INDEX + 1;

                            -- Estado siguiente
                            act_state <= DATA_RECEIVE;
                        
                        elsif DATA_INDEX = 9 then       -- Bit de paridad
                            
                            PARITY_BIT <= i_RX;
                            
                            o_DATA <= DATA;
                            o_RCV <= '1';       -- Enviamos señal de dato recibido

                            -- Estado siguiente
                            act_state <= IDLE;
                        
                        end if;
                    end if;

                    MIDDLE <= not MIDDLE;

                when others => null;
            end case;

        end if;
    end process;

end Reception;