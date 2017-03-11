# LOGIC



### Description
        A not-so tiny library that simulates logic gates. and helps you
	simulate the working of circuit. This library does not simulate
	the operation of the logic gates itself but gives you the power
	to create different gates and opearate on them.

### DISCLAIMER:
	This library is at an alpha stage with no proper docs.
    If you are the type of guy who live on the edge, Read the
    source and experiment.

### To-do:
1. In implementation of gates, Handle the error safely when
allocation failure happens, currently it exits. Refer #F gates.c
ALLOC_WITH_FAILURE_EXIT.

2. get_pin_value returns false when an error occurs instead of sending an
 	error signal, this return value can be mistaken for pin's output. Handle this
 	exception in a better way.

3. When shorting output pins, sending the pin number of the source is redundant.
Find a workaround.
    
4. Write proper documentation.

5. Write test cases for all scenarios.

6. Decide what to do with char *gate_names[] in header file. Move it to implementation file?

7. update README.


### Author(s):
rmNULL.

### LICENSE:
see [LICENSE](https://github.com/rmNULL/logic/blob/master/LICENSE).

### REPORTING:
open an [issue](https://github.com/rmNULL/logic/issues) at github.
