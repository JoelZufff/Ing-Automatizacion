-- Simplificar despues
------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity LCD_putstring is
	generic 
    (
        clk_freq    : INTEGER          -- Frecuencia del reloj (Hz)
    );
    port
	(
        i_RST               : in STD_LOGIC;                         -- Reinicio de maquina de estados
        i_CLK               : in STD_LOGIC;
        
        -- I/O fisicas de LCD
		o_RS, o_E, o_RW     : out STD_LOGIC;
		o_LCD_DATA          : out std_logic_vector(7 downto 0);      -- 8 Bits ASCII
        
        -- I/O virtuales
        i_ST                : in STD_LOGIC;                         -- Señal de start
        i_string            : in STD_LOGIC_VECTOR(255 downto 0);    -- Cadena de 33 caracteres (32 char y un salto de linea)

        o_RDY               : out STD_LOGIC                        -- Indicador de listo para imprimir
	);
end LCD_putstring;
------------------------------------------------------------------------------
architecture string_print of LCD_putstring is 
    -- SEÑALES PARA MAQUINA DE ESTADOS FINITOS --
        type States is (DOWN_SIGNAL, CONFIG0, CONFIG1, IDLE, CLEAR_DISP, SEND_CHAR, NEW_LINE);
        signal act_state    : States := CONFIG0;
        signal stored_state   : States;       -- Para ahorrar el uso multiple de down signal
    -- DIVISION DE RELOJ --
        component CLK_DIV is
            generic 
            (
                clk_freq    : integer          -- Frecuencia interna de FPGA (Hz)
            );
            port
            (
                i_out_freq      : integer;              -- Frequencia deseada
                
                i_FPGA_clk      : in STD_LOGIC;         -- Señal de reloj base
                -- Ver si poner RST
                o_clk           : out STD_LOGIC    
            );
        end component;

        signal LCD_clk     : STD_LOGIC;
    
    signal char_index   : INTEGER := 0;

begin

    o_RW <= '0';

    c_LCD_CLK : CLK_DIV
        generic map ( clk_freq => clk_freq )
        port map ( i_out_freq => 1000, i_FPGA_clk => i_CLK, o_clk => LCD_CLK );

    ------------------------------------------------------------------------------
                            -- MAQUINA DE ESTADOS FINITOS --
    ------------------------------------------------------------------------------
    process (LCD_CLK, i_RST)
    begin
        if (i_RST = '1') then               -- Se presiona RST
            act_state <= CONFIG0;
        elsif rising_edge(LCD_CLK) then     -- Se detecta señal de reloj
            case act_state is

                when DOWN_SIGNAL =>
                    -- Señales de salida
                    o_E <= '0'; o_RS <= '0'; 
                    o_RDY <= '0';
    
                    -- Estado futuro
                    act_state <= stored_state;

                -- ESTADOS DE CONFIGURACION --
                when CONFIG0 =>     -- SET(DATO, MATRIZ)
                    -- Señales de salida
                    o_E <= '1'; o_RS <= '0'; o_LCD_DATA  <= X"38";
                    o_RDY <= '0';
                    
                    -- Estado futuro en funcion de entradas
                    act_state <= DOWN_SIGNAL;
                    stored_state <= CONFIG1;

                when CONFIG1 =>     -- ACTIVAR LCD Y CURSOR
                    -- Señales de salida
                    o_E <= '1'; o_RS <= '0'; o_LCD_DATA  <= X"0D";
                    o_RDY <= '0';
    
                    -- Estado futuro
                    act_state <= IDLE;

                -- ESTADO DE ESPERA E IMPRESION --
                when IDLE =>        -- Estado inactivo cuando esperando señal de inicio
                    -- Enviamos señales de salida de estado actual
                    o_E <= '0'; o_RS <= '0';
                    o_RDY <= '1';
    
                    -- Actualizamos estado futuro en funcion de las entradas    
                    if (i_ST = '1') then
                        act_state <= CLEAR_DISP;
                    else
                        act_state <= IDLE;
                    end if;

                when CLEAR_DISP =>     -- LIMPIA PANTALLA
                    -- Señales de salida
                    o_E <= '1'; o_RS <= '0'; o_LCD_DATA  <= X"01";
                    o_RDY <= '0';

                    char_index <= 0;

                    -- Estado futuro
                    if (i_ST = '0') then
                        act_state <= DOWN_SIGNAL;
                        stored_state <= SEND_CHAR;
                    else
                        act_state <= CLEAR_DISP;
                    end if;

                when SEND_CHAR =>     -- ENVIAMOS CARACTERES
                    -- Señales de salida
                    o_E <= '1'; o_RS <= '1'; o_LCD_DATA <= i_string(255 - (char_index * 8) downto 248 - (char_index * 8));
                    o_RDY <= '0';

                    char_index <= char_index + 1;

                    -- Estado futuro
                    if (char_index = 15) then        -- Se requiere salto de linea
                        act_state <= DOWN_SIGNAL;
                        stored_state <= NEW_LINE;
                    elsif (char_index = 31) then   -- Se finalizo el envio
                        act_state <= IDLE;
                    else
                        act_state <= DOWN_SIGNAL;
                        stored_state <= SEND_CHAR;
                    end if;
                    
                when NEW_LINE =>
                    -- Señales de salida
                    o_E <= '1'; o_RS <= '0'; o_LCD_DATA <= X"C0";
                    o_RDY <= '0';
                    
                    -- Estado futuro
                    act_state <= DOWN_SIGNAL;
                    stored_state <= SEND_CHAR;
                    
                when others => null;
            end case;
        end if;
    end process;

end string_print;