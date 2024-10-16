-- Haremos la division de reloj hasta tener 2 * Baudios. Esto para detectar el valor a la mitad de cada intervalo

-- MAQUINA DE ESTADOS FINITOS UART_RX --
-- X Entradas
    --
-- X Salidas
    --
-- x Estados --
    --
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity UART_RX is
	port
	(
		i_FPGA_CLK      : in STD_LOGIC;                         -- Oscilador de placa (50 MHz)
		i_RST           : in STD_LOGIC;                         -- Boton de reset (Para errores de paridad)
        
        i_RX            : in STD_LOGIC;                         -- Reception PIN
        o_EOR           : out STD_LOGIC;                        -- End Of Reception
        o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato receptado
	); 
end UART_RX;

architecture Reception of UART_RX is 
    
    -- Maquina de estado
    type States is (IDLE, S0, S1);
    signal act_state, next_state: States := IDLE; -- Ponemos en estado inicial la maquina
    
    -- Division de reloj
    signal count    : integer range 0 to 5208;      -- 9600 Baudios
    signal UART_CLK : STD_LOGIC;

begin
    ------------------------------------------------------------------------------
                -- DIVISION DE RELOJ PARA BAUDIOS DE RECEPCION --
    ------------------------------------------------------------------------------
    process (i_FPGA_clk)        -- En estado IDLE => UART_CLK = FPGA_CLK
    begin

        if act_state = IDLE then    -- Si estamos en modo de espera CLK esta a la maxima frecuencia para esperar bit de start
            UART_CLK <= i_FPGA_CLK;
        elsif rising_edge(i_FPGA_CLK) then      -- Si detectamos un flanco de subida    
            count <= count + 1;

            if count = 5208 then                -- 9600 Baudios
                UART_clk <= not UART_CLK;
                count <= 0;
            end if;
        end if;

    end process;

    ------------------------------------------------------------------------------
                            -- RECEPCION DE DATOS --
    ------------------------------------------------------------------------------ 
    process (UART_CLK)
    begin
        if rising_edge(UART_CLK) then           

            act_state <= next_state;    -- Actualizamos estado presente
    
            case act_state  is
                when IDLE =>
                    
                    -- Salida de estado actual
                    o_EOR <= not '1';       -- Se finalizo la recepcion
                    o_DVD <= not '1';       -- Hay validez con paridad
    
                    -- Estado futuro en funcion de entradas
                    if i_RX = '0' then        -- Se detecta bit de start
                        next_state <= S0;
                    else
                        next_state <= IDLE;
                    end if;
    
                when S0 =>      -- Recepcion de datos
                    
                    -- Tener un Booleano que conmutara los ciclos de reloj que usaremos, para solo activar lectura en medio del intervalo de dato, con una señal estable

                    -- Tener un indice de bit, cuando este haya llegado a 7, pasar a estado de comparacion de paridad
                    
                when S1 =>      -- Comparacion de bit de paridad
                    
                    -- Si no coincide la paridad enclavamos este estado hasta recibir señal RST
                    
                when others => null;
            end case;

        end if;
    end process;

end Reception;