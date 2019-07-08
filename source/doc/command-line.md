# Command Line

## Help

To display the help, simply run `-h` or `--help`.

**Note** that when this is run, the main program will not be run. This is a
feature intended to allow you to read the help message without program related
print data hiding it.

## Motor

This command line option is activated by running `-m` or `--motor`. Information
can be viewed by observing the *help* argument. The following is to help you do
some basic debug work on the motors.

### Motor Status

The most basic command to get working is the "ping" command. This allows you to
do the following:

* Confirm the serial communications are correct, i.e. the baud rate, check
bits, bytes conversion, etc.
* Confirm the motors is correctly connected.

To perform this, run the following:

    ./robot FE 0 01 1

Breaking this down, `FE` is the broadcast motor ID and all motors will respond.
After this, `0` is the number of parameters (i.e. the payload), `01` is the
command byte for ping and `1` indicates that we are waiting for a response from
the motor.

**Note** that if more than one motor is attached, they will all respond. The
broadcast address `FE` should be used carefully.

All going well, the motor should respond with:

* Motor ID: The ID of the motor, by default `01`.
* Number of parameters: This should be `0`.
* Working status (command): If all is good, the motor will return `00`.

### Additional Information

For more information please see the [Protocol Manual](doc/protocol-handout.txt)
and the [Memory Table](doc/serial-bus-intelligent-servo.txt).

Some additional details that the manual doesn't mention:

* The default baud rate of a factory made motor is actually 115200 bits per
second.
* Many of the default values are completely different from what they document,
see our manual recording of [factory values](doc/sm30-default-values.md).
