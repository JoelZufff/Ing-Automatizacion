library	IEEE;
use	IEEE.std_logic_1164.all;
entity P1_TB is
end P1_TB;

-- We generate a new architecture with the same variables
architecture TB of P1_TB is
component P1
	port
	(
		A: in std_logic;
		B: in std_logic;
		C: in std_logic;
		D: in std_logic;
		S1: out std_logic;
		S2: out std_logic;
		S3: out std_logic;
		S4: out std_logic;
		S5: out std_logic
	);
end component;

-- We simulate de input and output values
signal A,B,C,D:std_logic;  			-- Inputs
signal S1,S2,S3,S4,S5:std_logic; 	-- Outputs

begin
	inicio: P1 port map (A=>A,B=>B,C=>C,D=>D,S1=>S1,S2=>S2,S3=>S3,S4=>S4,S5=>S5);
	Parasimu: process
	begin
		A<='0'; B<='0'; C<='0'; D<='0'; wait for 10ns;
		A<='0'; B<='0'; C<='0'; D<='1'; wait for 10ns;
		A<='0'; B<='0'; C<='1'; D<='0'; wait for 10ns;
		A<='0'; B<='0'; C<='1'; D<='1'; wait for 10ns;
		A<='0'; B<='1'; C<='0'; D<='0'; wait for 10ns;
		A<='0'; B<='1'; C<='0'; D<='1'; wait for 10ns;
		A<='0'; B<='1'; C<='1'; D<='0'; wait for 10ns;
		A<='0'; B<='1'; C<='1'; D<='1'; wait for 10ns;
		A<='1'; B<='0'; C<='0'; D<='0'; wait for 10ns;
		A<='1'; B<='0'; C<='0'; D<='1'; wait for 10ns;
		A<='1'; B<='0'; C<='1'; D<='0'; wait for 10ns;
		A<='1'; B<='0'; C<='1'; D<='1'; wait for 10ns;
		A<='1'; B<='1'; C<='0'; D<='0'; wait for 10ns;
		A<='1'; B<='1'; C<='0'; D<='1'; wait for 10ns;
		A<='1'; B<='1'; C<='1'; D<='0'; wait for 10ns;
		A<='1'; B<='1'; C<='1'; D<='1'; wait for 10ns;
		wait;
	end	process Parasimu;
end TB;