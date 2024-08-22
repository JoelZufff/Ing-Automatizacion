library ieee;                   -- Libreria estandar de VHDL
use ieee.std_logic_1164.all; 

-- La "entity" definen nuestras entradas y salidas. Debe tener el mismo nombre que el archivo
entity Clase_01 is
    port    -- Enumeramos entradas y salidas
    ( 
        variable1_i : in std_logic;         -- Entrada logica de 1 bit
        variable2_i : in std_logic;         -- Entrada logica de 1 bit
        variable3_o : out std_logic         -- Salida logica de 1 bit
    );
end entity Clase_01;

-- La "Architecture" es donde ponemos la mayoria de nuestros algoritmos logicos
architecture flujo_datos of Clase_01 is
begin
    
    variable3_o <= variable1_i and variable2_i;
    
    
    -- Un "Process" se ejecuta de forma secuencial, como un microcontrolador. No hay que abusar mucho de ellos para no perder la ventaja de los FPGA, de ejecutar procesos paralelamente.
    process is
    begin
        report "Hello World";
        wait;
    end process;

end architecture flujo_datos;