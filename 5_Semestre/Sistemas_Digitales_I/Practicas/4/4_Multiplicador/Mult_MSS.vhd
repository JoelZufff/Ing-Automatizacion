library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity Mult_MSS is
    generic
    (
        n: integer := 2
    )
    port
    (
        A, B    : in std_logic_vector(n-1 downto 0);        -- Operandos
        output  : out std_logic_vector(2*n-1 downto 0)      -- Producto
    );
end Mult_MSS;

architecture Aritmetica of Mult_MSS is
begin
    process(A, B)
    variable MSS :   signed(2*n-1 downto 0);
    begin
        MSS     :=  signed(A) * signed(B);
        output  <=  std_logic_vector(MSS); -- LEDS
    end process;
end Aritmetica;