library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity BCD_byte is
    port 
    (
        i_DATA      : in STD_LOGIC_VECTOR(7 downto 0);
        o_DATA      : out STD_LOGIC_VECTOR(9 downto 0) 
    );
end BCD_byte;
------------------------------------------------------------------------------------------------------------------------------
architecture rtl of BCD_byte is
    -- DECODER BCD DE 4 BITS --
        component BCD_4bit
            port 
            (
                i_DATA : in std_logic_vector(3 downto 0);
                o_DATA : out std_logic_vector(3 downto 0)
            );
        end component;

        signal BCD_DATA_0, BCD_DATA_1, BCD_DATA_2, BCD_DATA_3, BCD_DATA_4, BCD_DATA_5, BCD_DATA_6 : STD_LOGIC_VECTOR(3 downto 0) := "0000";

begin
    ------------------------------------------------------------------------------
                                -- DECODER BCD BYTE --
    ------------------------------------------------------------------------------
    BCD_4bit_0 : BCD_4bit
        port map ( i_DATA => '0' & i_DATA(7 downto 5), o_DATA => BCD_DATA_0 );
    BCD_4bit_1 : BCD_4bit
        port map ( i_DATA => BCD_DATA_0(2 downto 0) & i_DATA(4), o_DATA => BCD_DATA_1 );
    BCD_4bit_2 : BCD_4bit
        port map ( i_DATA => BCD_DATA_1(2 downto 0) & i_DATA(3), o_DATA => BCD_DATA_2 );
    BCD_4bit_3 : BCD_4bit
        port map ( i_DATA => '0' & BCD_DATA_0(3) & BCD_DATA_1(3) & BCD_DATA_2(3), o_DATA => BCD_DATA_3 );
    BCD_4bit_4 : BCD_4bit
        port map ( i_DATA => BCD_DATA_2(2 downto 0) & i_DATA(2), o_DATA => BCD_DATA_4 );
    BCD_4bit_5 : BCD_4bit
        port map ( i_DATA => BCD_DATA_3(2 downto 0) & BCD_DATA_4(3), o_DATA => BCD_DATA_5 );
    BCD_4bit_6 : BCD_4bit
        port map ( i_DATA => BCD_DATA_4(2 downto 0) & i_DATA(1), o_DATA => BCD_DATA_6 );

    o_DATA <= BCD_DATA_3(3) & BCD_DATA_5 & BCD_DATA_6 & i_DATA(0); 

end rtl;