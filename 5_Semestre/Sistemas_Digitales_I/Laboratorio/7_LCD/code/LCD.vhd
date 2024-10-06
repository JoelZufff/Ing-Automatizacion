library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity LCD is
	port
	(
		CLK         : in STD_LOGIC;
		RS, E, RW   : out STD_LOGIC;
		Datos       : out std_logic_vector(7 downto 0);

		LEDS        : out std_logic_vector(1 downto 0);
        Botones     : in std_logic_vector(1 downto 0);
        ST          : in std_logic
	); 
end LCD;
------------------------------------------------------------------------------
architecture logica of LCD is 

    -- Señales para transicion de estados
    type Estados is (E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16, E17, E18, E19, E20, E21, E22, E23, IDLE);
    signal Estado_pre, Estado_fut: Estados := E0;       --Ponemos en estado inicial la maquina

    -- Señal para division de reloj
    signal count: integer range 0 to (2500000 * 2 - 1);
    
    -- Señal para transicion de palabra en funcion de botones presionados
    type array_4_t is array(0 to 3) of std_logic_vector(7 downto 0);
    type nombres_t is array(0 to 3) of array_4_t;
    
    constant nombres : nombres_t := 
    (
        0 => (0 => X"4F", 1 => X"6D", 2 => X"61", 3 => X"72"), -- Omar
        1 => (0 => X"44", 1 => X"61", 2 => X"6E", 3 => X"69"), -- Dani
        2 => (0 => X"4A", 1 => X"6F", 2 => X"65", 3 => X"6C"), -- Joel
        3 => (0 => X"4A", 1 => X"6F", 2 => X"73", 3 => X"73")  -- Joss
    );
    signal nombres_index: integer range 0 to 3;

begin
    LEDS <= not Botones;
    RW <= '0';
    nombres_index <= to_integer(unsigned(Botones));

------------------------------------------------------------------------------
        -- DIVISION DE RELOJ PARA RETARDO ENTRE TRANSICIONES DE SM --
------------------------------------------------------------------------------
    process (CLK)
    begin
        if rising_edge(CLK) then
            if count = (2500000 * 2 - 1) then
                Estado_pre <= Estado_fut;
                count <= 0;
            else
                count <= count + 1;
            end if;
        end if;
    end process;

    process (Estado_pre)
    begin
        case Estado_pre is
            -- Configuración del LCD
            when E0 =>
                Datos <= X"38"; -- Set(dato, matriz)
                E <= '1'; -- Sube señal
                RS <= '0'; -- Configuración del RS
                Estado_fut <= E1;

            when E1 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E2;

            -- Limpiado del LCD
            when E2 =>
                Datos <= X"01"; -- Clear LCD
                E <= '1';
                RS <= '0';
                Estado_fut <= E3;

            when E3 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E4;

            -- Activar Display y Cursor
            when E4 =>
                Datos <= X"0D"; -- Activar LCD y cursor
                E <= '1';
                RS <= '0';
                Estado_fut <= E5;
                
            when E5 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E6;
            
            -- Caracter 1
            when E6 =>
                Datos <= nombres(nombres_index)(0); -- Letra O en ASCII
                E <= '1';
                RS <= '1';
                Estado_fut <= E7;
            
            when E7 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E8;
            
            -- Caracter 2
            when E8 =>
                Datos <= nombres(nombres_index)(1); -- Letra M en ASCII
                E <= '1';
                RS <= '1';
                Estado_fut <= E9;
            
            when E9 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E10;
            
            -- Caracter 3
            when E10 =>
                Datos <= nombres(nombres_index)(2); -- Letra A en ASCII
                E <= '1';
                RS <= '1';
                Estado_fut <= E11;
            
            when E11 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= E12;
            
            -- Caracter 4
            when E12 =>
                Datos <= nombres(nombres_index)(3); -- Letra R en ASCII y en hexadecimal
                E <= '1';
                RS <= '1';
                Estado_fut <= E13;
            
            when E13 =>
                E <= '0'; -- Baja la señal
                Estado_fut <= IDLE;
            
            when IDLE =>        -- Estado inactivo cuando esperando boton de start
                if ST = '1' then
                    Estado_fut <= E0;
                else
                    Estado_fut <= IDLE;
                end if;
            when others => null;
        end case;
    end process;

end logica;