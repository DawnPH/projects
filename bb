library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity CNT10 is
	port( fin: in std_logic;
		  clr: in std_logic;
		  ena: in std_logic;
		  cout: out std_logic;
		  dout:out std_logic_vector(3 downto 0)
		 );
end entity CNT10;
architecture bhv of CNT10 is
 begin
 process(fin,clr,ena)
 variable q: std_logic_vector(3 downto 0);
 begin
 	if clr='1' then q:="0000";
	  elsif fin'event and fin='1' then
	    if ena='1' then
			if q<9 then q:=q+1;
	        else q:="0000";
	      end if;
	    end if;
	end if;
	if q="1001" then cout<='1';
     else cout<='0';
   end if;
	 dout<=q;
 end process;
end architecture bhv;
