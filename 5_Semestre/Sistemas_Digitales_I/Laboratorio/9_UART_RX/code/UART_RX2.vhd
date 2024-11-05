-- Haremos la division de reloj hasta tener 2 * Baudios. Esto para detectar el valor a la mitad de cada intervalo

-- MAQUINA DE ESTADOS FINITOS UART_RX --
-- 2 Entradas
    -- RST : Reinicio de comunicacion serial en caso de error de paridad
    -- RX : Recepcion de dato de 8 bits
-- 3 Salidas
    -- DVD : Señal que nos indica si hubo error de paridad
    -- EOR (End Of Reception): 
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
        o_DVD           : out STD_LOGIC;
        o_RDY           : out STD_LOGIC;                        -- Bandera de finalizacion
        o_DATA          : out STD_LOGIC_VECTOR(7 downto 0)      -- Valor de dato receptado
	); 
end UART_RX;

architecture Reception of UART_RX is 
    
    -- Division de reloj
    constant clks_per_bit : integer := 5208;                    -- 50 MHz / 9600 baud

    signal count        : integer range 0 to clks_per_bit := 0;      -- 9600 Baudios
    signal parity       : STD_LOGIC := '0';

    -- Maquina de estado
    type States is (IDLE, S0, S1);
    signal act_state, next_state: States := IDLE; -- Ponemos en estado inicial la maquina
    

    signal middle : STD_LOGIC := '0';
    signal data_index : integer range 0 to 9 := 0;
    signal DATA     : STD_LOGIC_VECTOR(7 downto 0);
    signal RX : STD_LOGIC := '0';
    
begin    
    ------------------------------------------------------------------------------
                -- DIVISION DE RELOJ PARA BAUDIOS DE RECEPCION --
    ------------------------------------------------------------------------------
    process (i_FPGA_clk)
    begin
        if rising_edge(i_FPGA_CLK) then      -- Si detectamos un flanco de subida

            act_state <= next_state;    -- Actualizamos estado presente

            case act_state  is
                when IDLE =>
                    
                    -- Salida de estado actual
                    o_RDY <= '0';           -- No se finalizo transmision
                    o_DVD <= not '1';       -- Hay validez con paridad
    
                    -- Estado futuro en funcion de entradas
                    if i_RX = '0' then        -- Se detecta bit de start
                        middle      <= '0';
                        data_index  <= 0;
                        next_state  <= S0;
                    else
                        next_state <= IDLE;
                    end if;
    
                when S0 =>      -- Recepcion de datos
                    
                    -- Salida de estado actual
                    o_RDY <= '0';           -- No se ha finalizado recepcion
                    o_DVD <= not '1';       -- Hay validez con paridad

                    if count = (clks_per_bit / 2) then      -- Para tener 19200 Hz

                        if middle = '1' then      -- Nos ayuda a conmutar la lectura del dato
                            if data_index = 0 then      -- Bit de start, ignorar
                                
                                data_index <= data_index + 1;
    
                                -- Estado siguiente
                                next_state <= S0;
                            
                            elsif data_index < 9 then
                                
                                DATA(data_index - 1) <= i_RX; -- Captura del bit
                                data_index <= data_index + 1;
    
                                -- Estado siguiente
                                next_state <= S0;
                            
                            elsif data_index = 9 then   -- Bit de paridad
                                
                                parity <= i_RX; -- Captura del bit de paridad
                                o_DATA <= DATA;
    
                                -- Estado siguiente
                                next_state <= S1;
                            
                            end if;
                        end if;
                        middle <= not middle;
                        
                        count <= 0;
                    end if;

                    count <= count + 1;
                    
                when S1 =>      -- Comparacion de bit de paridad
                    
                    -- Salida de estado actual
                    o_RDY <= '1';           -- Se finalizo la recepcion
                    --o_DVD <= (((o_DATA(0) XOR o_DATA(1)) XOR (o_DATA(2) XOR o_DATA(3))) XOR ((o_DATA(4) XOR o_DATA(5)) XOR (o_DATA(6) XOR o_DATA(7)))) XNOR parity;       -- Calculamos validez de bit de paridad
                    
                    if i_RX = '1' then        -- Esperamos bit de stop
                        next_state <= IDLE;
                    else
                        next_state <= S1;
                    end if;

                when others => null;
            end case;

        end if;
    end process;

end Reception;