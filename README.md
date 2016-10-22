# simulate the computation of CRC(circlyic redundence check) and test the detection capability of CRC

# Usage

Run command

    ./compile

to make to programs.

# Program

## crc

Given the original message you want to sent and the generator, return the CRC and the message will be transmitted.

You need to put appropriate generator and the message you want to transmitted in file "generator" and "original Message" before you run the program.

To run the program, run

    ./crc

in the terminal.

## experimentation

Given a generator in the file "generator", test how many errors can be detected among much of simulation.

You can edit:

	- the generator in file "generator"
	- the length (in bits) of original message in the line 9 of "experimentation.cpp"
	- the length (in bits) of noise in the line 10 of "experimentation.cpp"
	- the number of experimentation in the line 11 of "experimentation.cpp"

# After Using

Run

    ./cleanAux

to clean unnecessary files.
