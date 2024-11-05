-- Modificarlo, sera para una LCD de 16x2, recibira los 32 caracteres y los enviara secuencialmente en el LCD al recibir una señal de start

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
    generic 
    (
        clk_freq        : INTEGER    
    );
	port
	(
		i_FPGA_CLK          : in STD_LOGIC;
        i_RST               : in STD_LOGIC;

        i_ST                : in STD_LOGIC;                         -- Señal de start
        --i_DATA              : in STD_LOGIC_VECTOR(7 downto 0);
        i_text              : STRING(1 to 32);                      -- Cadena a escribir
        
		o_RS, o_E, o_RW     : out STD_LOGIC;
		o_LCD_DATA          : out std_logic_vector(7 downto 0)      -- 8 Bits ASCII
	); 
end LCD;
------------------------------------------------------------------------------
architecture char_print of LCD is 

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

    -- Señales para transicion de estados
    type States is (CONFIG0, CONFIG1, CONFIG2, CONFIG3, CONFIG4, IDLE, PUTCH0, PUTCH1, PUTCH2, PUTCH3);
    signal act_state : States := CONFIG0;

    -- Señal para division de reloj
    signal LCD_clk : STD_LOGIC;
    
    signal char_index : INTEGER := 0;

begin

    o_RW <= '0';

    ------------------------------------------------------------------------------
            -- DIVISION DE RELOJ PARA RETARDO ENTRE TRANSICIONES DE SM --
    ------------------------------------------------------------------------------
    
    c_LCD_clk : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => 1000, i_FPGA_clk => i_FPGA_clk, o_clk => LCD_clk );

    ------------------------------------------------------------------------------
                -- MAQUINA DE ESTADO PARA IMPRESION DE CARACTER --
    ------------------------------------------------------------------------------
    process (LCD_clk, i_RST)
    begin

        if (i_RST = '0') then               -- Se presiona RST

            act_state <= CONFIG0;
            char_index <= 0;
        
        elsif rising_edge(LCD_clk) then     -- Se detecta señal de reloj

            case act_state is
                -- ESTADOS DE CONFIGURACION --
                when CONFIG0 =>     -- SET(DATO, MATRIZ)
    
                    -- Señales de salida
                    o_LCD_DATA  <= X"38"; o_E <= '1'; o_RS <= '0';
                    
                    -- Estado futuro en funcion de entradas
                    act_state <= CONFIG1;
                    
                when CONFIG1 =>     -- BAJA SEÑAL
    
                    -- Señales de salida
                    o_LCD_DATA  <= "00000000"; o_E <= '0'; o_RS <= '0';

                    -- Estado futuro
                    act_state <= CONFIG2;
    
                when CONFIG2 =>     -- LIMPIA PANTALLA
    
                    -- Señales de salida
                    o_LCD_DATA  <= X"01"; o_E <= '1'; o_RS <= '0';
    
                    -- Estado futuro
                    act_state <= CONFIG3;
    
                when CONFIG3 =>     -- BAJA SEÑAL
                    
                    -- Señales de salida
                    o_LCD_DATA  <= "00000000";
                    o_E         <= '0'; -- Baja la señal
                    o_RS        <= '0'; -- Configuración del o_RS
    
                    -- Estado futuro
                    act_state <= CONFIG4;
    
                when CONFIG4 =>     -- ACTIVAR LCD Y CURSOR
                    
                    -- Señales de salida
                    o_LCD_DATA  <= X"0D"; o_E <= '1'; o_RS <= '0';
    
                    -- Estado futuro
                    act_state <= IDLE;
                
                -- ESTADOS DE ESPERA E IMPRESION --
                when IDLE =>        -- Estado inactivo cuando esperando señal de inicio
                    
                    -- Enviamos señales de salida de estado actual
                    o_LCD_DATA  <= "00000000"; o_E <= '0'; o_RS <= '0';
    
                    -- Actualizamos estado futuro en funcion de las entradas    
                    if i_ST = '1' then
                        act_state <= PUTCH0;
                    else
                        act_state <= IDLE;
                    end if;
                
                when PUTCH0 =>      -- BAJA SEÑAL
                    -- Enviamos señales de salida de estado actual
                    o_LCD_DATA  <= "00000000";
                    o_E         <= '0';
                    o_RS        <= '0';
    
                    -- Actualizamos estado futuro en funcion de las entradas    
                    if i_ST = '0' then
                        act_state <= PUTCH1;
                    else
                        act_state <= PUTCH0;
                    end if;
    
                when PUTCH1 =>      -- ENVIO DE CARACTER
    
                    -- Señales de salida
                    o_LCD_DATA  <= std_logic_vectorcomponent(i_text(0)); o_E <= '1'; o_RS <= '1';
                    
                    char_index <= char_index + 1;       -- Arreglar problema

                    -- Estado futuro
                    act_state <= PUTCH2;
                    
                when PUTCH2 =>      -- BAJA SEÑAL

                    -- Señales de salida
                    o_LCD_DATA  <= "00000000"; o_E <= '0'; o_RS <= '0'; -- Configuración del o_RS
    
                    -- Estado futuro
                    if(char_index < 16) then
                        act_state <= IDLE;
                    else
                        act_state <= PUTCH3;
                        char_index <= 0;
                    end if;
                
                when PUTCH3 =>      -- SALTO DE LINEA
                
                    -- Señales de salida
                    o_LCD_DATA  <= X"C0"; o_E <= '1'; o_RS <= '0';

                    -- Estado futuro
                    act_state <= IDLE;

                when others => null;
            end case;

        end if;

    end process;

end char_print;