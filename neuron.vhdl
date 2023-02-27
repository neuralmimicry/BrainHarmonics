-- Define inputs and outputs
entity neuron_chain is
    Port ( input_data : in std_logic_vector(7 downto 0);
           input_valid : in std_logic;
           output_data : out std_logic_vector(7 downto 0);
           output_valid : out std_logic);
end neuron_chain;

architecture Behavioral of neuron_chain is
    -- Define internal signals
    signal weights : std_logic_vector(7 downto 0);
    signal inputs : std_logic_vector(7 downto 0);
    signal input_count : integer range 0 to 7 := 0;
    signal input_valid_reg : std_logic := '0';
    signal input_valid_delay : std_logic_vector(7 downto 0) := (others => '0');
    signal neuron_state : std_logic_vector(7 downto 0) := (others => '0');
begin
    -- Compute weighted sum of inputs
    process (weights, inputs, input_count)
        variable sum : integer range -128 to 127 := 0;
    begin
        sum := 0;
        for i in 0 to 7 loop
            if i < input_count then
                sum := sum + to_integer(signed(weights(i) & inputs(i)));
            end if;
        end loop;
        neuron_state <= std_logic_vector(to_signed(sum, 8));
    end process;

    -- Output the neuron state when input is valid
    process (input_valid_reg, input_valid_delay, neuron_state)
    begin
        if input_valid_reg = '1' and input_valid_delay = "00000001" then
            output_data <= neuron_state;
            output_valid <= '1';
        else
            output_data <= (others => '0');
            output_valid <= '0';
        end if;
    end process;

    -- Update input count and delay input valid signal
    process (input_valid)
    begin
        if input_valid = '1' then
            input_count <= input_count + 1;
            input_valid_reg <= '1';
            input_valid_delay <= input_valid_delay(6 downto 0) & '1';
        else
            input_count <= 0;
            input_valid_reg <= '0';
            input_valid_delay <= (others => '0');
        end if;
    end process;
end Behavioral;
