-- MAQUINA DE ESTADOS DE LCD --
-- 2 Entradas
    -- ST: Indica el inicio de impresion al recibir un dato
    -- RST: Indica el reinicio del LCD, por ende limpieza de pantalla
-- 4 Salidas
    -- RS (Registro de Datos/Selección): Indica si los datos que se envían son datos de visualización o comandos.
    -- E (Enable): Activa la transferencia de datos desde el registro de datos a la pantalla.
    -- LCD_DATA: Son los pines de datos que se utilizan para enviar los bits de datos de 8 bits en codigo ASCII
-- 10 estados --
    -- 6 estados de configuracion, solo se ejecutaran al iniciar y al presionar RST
    -- 1 estado de espera, que espera la presion de ST para comenzar la impresion
    -- Los demas estados son de impresion de caracter
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity LCD is
	port
	(
		i_FPGA_CLK          : in STD_LOGIC;
        i_RST               : in STD_LOGIC;

        i_DATA              : in STD_LOGIC_VECTOR(7 downto 0);
        i_ST                : in STD_LOGIC;                         -- Señal de start
		o_RS, o_E, o_RW     : out STD_LOGIC;
		o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII

	); 
end LCD;
------------------------------------------------------------------------------
architecture char_print of LCD is 

    -- Señales para transicion de estados
    type States is (S0, S1, IDLE, S2, S3, S4, S5, S6, S7, S8);
    signal act_state, next_state: States := S0;

    -- Señal para division de reloj
    signal count: integer range 0 to 2500000 := 0;
    
begin

    o_RW <= '0';

    ------------------------------------------------------------------------------
            -- DIVISION DE RELOJ PARA RETARDO ENTRE TRANSICIONES DE SM --
    ------------------------------------------------------------------------------
    process (i_FPGA_CLK)
    begin
        if rising_edge(i_FPGA_CLK) then
            if count = 2500000 then
                act_state <= next_state;
                count <= 0;
            else
                count <= count + 1;
            end if;
        end if;
    end process;

    ------------------------------------------------------------------------------
                -- MAQUINA DE ESTADO PARA IMPRESION DE CARACTER --
    ------------------------------------------------------------------------------
    process (act_state)
    begin
        case act_state is

            -- ESTADOS DE CONFIGURACION --
            when S0 =>

                -- Señales de salida
                o_LCD_DATA <= X"38"; -- Set(dato, matriz)
                o_E <= '1'; -- Sube señal
                o_RS <= '0'; -- Configuración del o_RS
                
                -- Estado futuro en funcion de entradas
                next_state <= S1;
                
            when S1 =>      -- BAJA SEÑAL

                -- Señales de salida
                o_LCD_DATA <= "00000000"; -- Set(dato, matriz)
                o_E <= '0'; -- Baja la señal
                o_RS <= '0'; -- Configuración del o_RS

                -- Estado futuro
                next_state <= S2;

            when S2 =>  -- Limpia pantalla

                -- Señales de salida
                o_LCD_DATA <= X"01"; -- Clear LCD
                o_E <= '1';
                o_RS <= '0';

                -- Estado futuro
                next_state <= S3;

            when S3 =>
                
                -- Señales de salida
                o_LCD_DATA <= "00000000"; -- Set(dato, matriz)
                o_E <= '0'; -- Baja la señal
                o_RS <= '0'; -- Configuración del o_RS

                -- Estado futuro
                next_state <= S4;

            when S4 =>
                
                -- Señales de salida
                o_LCD_DATA <= X"0D"; -- Activar LCD y cursor
                o_E <= '1';
                o_RS <= '0';

                -- Estado futuro
                next_state <= S5;
                
            when S5 =>

                -- Señales de salida
                o_LCD_DATA <= "00000000"; -- Set(dato, matriz)
                o_E <= '0'; -- Baja la señal
                o_RS <= '0'; -- Configuración del o_RS

                -- Estado futuro
                next_state <= IDLE;
            
            -- ESTADOS DE ESPERA E IMPRESION --
            when IDLE =>        -- Estado inactivo cuando esperando señal de inicio
                
                -- Enviamos señales de salida de estado actual
                o_LCD_DATA <= "00000000";
                o_E <= '0';
                o_RS <= '0';

                -- Actualizamos estado futuro en funcion de las entradas    
                if i_RST = not '1' then
                    next_state <= S0;
                elsif i_ST = '1' then
                    next_state <= S6;
                else
                    next_state <= IDLE;
                end if;
            
            when S6 =>
                
                -- Enviamos señales de salida de estado actual
                o_LCD_DATA <= "00000000";
                o_E <= '0';
                o_RS <= '0';

                -- Actualizamos estado futuro en funcion de las entradas    
                if i_RST = not '1' then
                    next_state <= S0;
                elsif i_ST = '0' then
                    next_state <= S7;
                else
                    next_state <= S6;
                end if;

            when S7 =>

                -- Señales de salida
                o_LCD_DATA <= i_DATA;
                o_E <= '1';
                o_RS <= '1';

                -- Estado futuro
                next_state <= S8;
                
            when S8 =>

                -- Señales de salida
                o_LCD_DATA <= "00000000"; -- Set(dato, matriz)
                o_E <= '0'; -- Baja la señal
                o_RS <= '0'; -- Configuración del o_RS

                -- Estado futuro
                next_state <= IDLE;
            
            when others => null;
        end case;
    end process;

end char_print;