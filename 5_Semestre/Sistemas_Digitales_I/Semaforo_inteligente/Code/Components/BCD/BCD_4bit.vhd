library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity BCD_4bit is
    port 
    (
        i_DATA      : in STD_LOGIC_VECTOR(3 downto 0);
        o_DATA      : out STD_LOGIC_VECTOR(3 downto 0) 
    );
end BCD_4bit;
------------------------------------------------------------------------------------------------------------------------------
architecture rtl of BCD_4bit is
begin
    process (i_DATA)
    begin
        if (unsigned(i_DATA) >= 5) then
            o_DATA <= STD_LOGIC_VECTOR(unsigned(i_DATA) + 3);
        else
            o_DATA <= i_DATA;
        end if;

    end process;

end rtl;