library	IEEE;
use	IEEE.std_logic_1164.all;

entity Restador_1bit is
    port 
    (
        A 	: in std_logic;	
        B 	: in std_logic;	
        Ci 	: in std_logic;		-- Acarreo de entrada
        Co 	: out std_logic;  	-- Acarreo de salida
        S	: out std_logic	-- Resultado
    );
end entity;

architecture Restador_1bit of Restador_1bit is
begin

    S   <= A xor B xor Ci;
    Co  <= ((not A) and B) or ((not A) and Ci) or (B and Ci);

end Restador_1bit;