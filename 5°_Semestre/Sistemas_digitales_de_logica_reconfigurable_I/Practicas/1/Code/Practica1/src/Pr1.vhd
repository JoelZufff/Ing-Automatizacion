library	IEEE;
use	IEEE.std_logic_1164.all;

-- We initialize the variables as inputs or outputs
entity P1 is 
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
end P1;

-- Based on the variables, we generate an architecture to relate the value of the outputs to the inputs
Architecture Pr1 of P1 is
begin			
	S1<= A or (B and C);
	S2<= (C and D) or (A and B);
	S3<= (B and A and C and D);
	S4<= C and ( A or B) and D;
	S5<= A or B or C or D;
end Pr1;