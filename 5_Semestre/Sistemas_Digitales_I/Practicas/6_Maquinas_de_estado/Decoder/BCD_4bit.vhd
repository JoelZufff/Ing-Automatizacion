library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity BCD_4bit is
    port 
    (
        input   : in std_logic_vector(3 downto 0);
        output  : out std_logic_vector(3 downto 0) 
    );
end BCD_4bit;

architecture rtl of BCD_4bit is
begin
    process (input)
    begin
        if (unsigned(input) >= 5) then 
            output <= std_logic_vector(unsigned(input) + 3);
        else
            output <= input; 
        end if;
    end process;
end rtl;