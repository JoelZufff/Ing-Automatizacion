library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity Expendedora is 	
    port
    (
        A       : in std_logic_vector(1 downto 0); -- Monedas
        clock   : in std_logic; -- El reloj es de 50Mhz 
        display : out std_logic_vector(7 downto 0); -- Mostrar número de monedas
        common  : out std_logic_vector(3 downto 0); -- Salida para el display de 7 segmentos
        LED     : out std_logic_vector(1 downto 0) -- Cambio y producto
    );
end Expendedora;

------------------------------------------------------------------------------ 
architecture expende of Expendedora is
    type Estados is (S0, S1, S2); -- Definir los estados en lista valores  a una variable
    signal estado_presen, estado_fut: Estados:=S0; -- Inicialización del estado a S0
    signal Moneda: integer range 0 to 5:=0; -- Inicializar contador de monedas (rango de 0 a 4)
    
    signal clock_div: std_logic; -- Señal del reloj dividido
    signal count: integer range 0 to (24999999*2); -- Contador para dividir el reloj a 5 segundos
	 --signal A:std_logic_vector(1 downto 0); -- Monedas para probar el process
begin
------------------------------------------------------------------------------ 
-- Proceso para dividir frecuencia de reloj a cada 5 segundos
divisor_frecuencia : process (clock)
begin
    if rising_edge(clock) then
        if count = (24999999*2) then -- Cada 250 millones de ciclos del reloj de 50 MHz = 5 segundos
            count <= 0; -- Reiniciar el contador
            clock_div <= not clock_div; -- Cambia el estado del reloj dividido
        else
            count <= count + 1;
        end if;
    end if;
end process;

------------------------------------------------------------------------------ 
-- Proceso para detectar la entrada de monedas (Accionado con la señal de reloj dividida)
monedas: process(clock_div)
begin
    if rising_edge(clock_div) then
				--A(0)<= '1'; probar el process
            if A(0) = '1' then -- Se ha presionado el botón de $1
                Moneda <= Moneda + 1;
            elsif A(1) = '1' then -- Se ha presionado el botón de $2
                Moneda <= Moneda + 2;
            else
                Moneda <= Moneda;
            end if;
    end if;

--comprobación
--if rising_edge(clock_div) then
--Moneda<=Moneda+1;
--end if;
end process;

-- Proceso de la máquina de estados (sincronizado con el reloj dividido a 5 segundos)
process (clock_div,Moneda,estado_presen)
begin
if rising_edge(clock_div) then
        case estado_presen is
            -- Caso inicial
            when S0 =>
                LED <= "00"; -- Apagar LEDs (anodo común)
                if Moneda = 1 then
                    estado_fut <= S1; -- Estado de una moneda
                elsif Moneda = 2 then
                    estado_fut <= S2; -- Estado de dos monedas
                else
                    estado_fut <= S0;
                end if;

            -- Caso una moneda ingresada
            when S1 =>
                LED <= "00"; -- Apagar LEDs
                if Moneda = 2 then -- Otra moneda de $1
                    estado_fut <= S2; -- Estado de dos monedas
                elsif Moneda = 3 then -- Se ingresó otra moneda de $2
                    LED <= "01"; -- Entrega de producto sin cambio
                    Moneda <= 0; -- Resetear contador de monedas
                    estado_fut <= S0; -- Volver al estado inicial
                else
                    estado_fut <= S1;
                end if;

            -- Caso dos monedas ingresadas
            when S2 =>
                LED <= "11"; -- Apagar LEDs
                if Moneda = 4 then -- Se ingresó otra moneda de $2
                    LED <= "00"; -- Entrega de producto con cambio
                    Moneda <= 0; -- Resetear contador de monedas
                    estado_fut <= S0; -- Volver al estado inicial
                elsif Moneda = 3 then -- Otra moneda de $1
                    LED <= "01"; -- Entrega de producto sin cambio
                    Moneda <= 0; -- Resetear contador de monedas
                    estado_fut <= S0; -- Volver al estado inicial
                else
                    estado_fut <= S2;
                end if;

            when others =>
                estado_fut <= S0;
        end case;
		end if;
end process;
------------------------------------------------------------------------------ 
common <= "1110";
with Moneda select
    display <= "11000000" when 0, -- Mostrar 0
               "11111001" when 1, -- Mostrar 1
               "10100100" when 2, -- Mostrar 2
               "10110000" when 3, -- Mostrar 3
               "10011001" when 4, -- Mostrar 4
               "11111111" when others; -- Default (apagar display)

end expende;

