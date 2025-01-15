-- Se introduce un dato de 8 bits
-- Se introduce el dato en un decoder BCD 
-- Se imprime su valor entero en un multiplexado de un display de 7 segmentos.
------------------------------------------------------------------------------------------------------------------------------
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
------------------------------------------------------------------------------------------------------------------------------
entity DISPLAY_BCD is
    generic 
    (
        CLK_FREQ    : INTEGER
    );
    port 
    (
        i_CLK       : in STD_LOGIC;
        i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);
        
        -- I/O fisicos display
        o_DISP_SEG  : out STD_LOGIC_VECTOR(7 downto 0);     -- 7 segmentos
		o_DISP_COM  : out STD_LOGIC_VECTOR(3 downto 0)      -- 4 comunes
    );
end DISPLAY_BCD;
------------------------------------------------------------------------------------------------------------------------------
architecture rtl of DISPLAY_BCD is
    
    -- DIVISOR DE RELOJ --
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
        signal DISP_CLK : STD_LOGIC;
        signal SUM_CLK : STD_LOGIC;
    
    -- MULTIPLEXADO DE DISPLAY --
        -- Secuencia de comunes de display
        type array_4_t is array (0 to 3) of std_logic_vector(3 downto 0); -- Tipo para manejar los comunes
        constant com_array : array_4_t := 
        (
            "1110",
            "1101",
            "1011",
            "0111"
        );
        signal comun_index : integer range 0 to 4;
    
        -- Impresion de digitos en display
        type array_10_t is array (0 to 9) of std_logic_vector(7 downto 0);
        constant num_array : array_10_t := 
        (
            "11000000",  -- 0
            "11111001",  -- 1
            "10100100",  -- 2
            "10110000",  -- 3
            "10011001",  -- 4
            "10010010",  -- 5
            "10000010",  -- 6
            "11111000",  -- 7
            "10000000",  -- 8
            "10011000"   -- 9
        );

        type int_array is array (0 to 3) of integer;
        signal numbers : int_array := (0, 0, 0, 0);
    
    
    -- DECODER BCD DE 1 byte --
        component BCD_byte is
            port 
            (
                i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);
                o_DATA      : out STD_LOGIC_VECTOR(9 downto 0) 
            );
        end component;
        
        signal BCD_DATA     : std_logic_vector(9 downto 0) := "0000000000";     -- Salida de decoder

begin

    ------------------------------------------------------------------------------
                                -- DECODER BCD BYTE --
    ------------------------------------------------------------------------------
    c_BCD_byte : BCD_byte
        port map ( i_DATA => i_DATA, o_DATA => BCD_DATA );

    numbers(0) <= to_integer(unsigned(BCD_DATA(3 downto 0)));
    numbers(1) <= to_integer(unsigned(BCD_DATA(7 downto 4)));
    numbers(2) <= to_integer(unsigned(BCD_DATA(9 downto 8)));

    ------------------------------------------------------------------------------
                            -- MULTIPLEXADO DE DISPLAY --
    ------------------------------------------------------------------------------
    c_DISP_CLK : CLK_DIV                                    -- Divisor de reloj
        generic map ( clk_freq => CLK_FREQ )
        port map ( i_out_freq => 1000, i_CLK => i_CLK, o_CLK => DISP_CLK);
    
    multiplexado : process (DISP_CLK)
    begin
        if rising_edge(DISP_CLK) then
            -- Enviamos informacion a display seleccionado
            o_DISP_COM  <= com_array(comun_index);
            o_DISP_SEG  <= num_array(numbers(comun_index));

            -- Seleccionamos display para proxima impresion
            if (comun_index = 3) then
                comun_index <= 0;
            else
                comun_index <= comun_index + 1;
            end if;

        end if;

    end process;

end rtl;