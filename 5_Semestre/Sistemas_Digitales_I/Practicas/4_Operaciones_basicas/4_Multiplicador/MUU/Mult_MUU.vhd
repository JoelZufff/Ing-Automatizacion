library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity Mult_MUU is
    generic
    (
        n: integer := 2
    );
    port
    (
        A, B    : in std_logic_vector(n-1 downto 0);        -- Operandos
        output  : out std_logic_vector(2*n-1 downto 0)      -- Producto
    );
end Mult_MUU;

architecture Aritmetica of Mult_MUU is
begin
    process(A, B)
    variable MUU : unsigned(2*n-1 downto 0);
    begin
        MUU     :=  unsigned(A) * unsigned(B);
        output  <=  not std_logic_vector(MUU); -- LEDS
    end process;
end Aritmetica;