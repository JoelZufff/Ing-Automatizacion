library	IEEE;
use	IEEE.std_logic_1164.all;

entity Sumador_1bit is
    port 
    (
        A 	: in std_logic;	
        B 	: in std_logic;	
        Ci 	: in std_logic;		-- Acarreo de entrada
        Co 	: out std_logic;  	-- Acarreo de salida
        S	: out std_logic	-- Resultado
    );
end entity;

architecture Sumador_1bit of Sumador_1bit is
begin

    S   <= A xor B xor Ci;
    Co  <= (A and B) or (A and Ci) or (B and Ci);

end Sumador_1bit;