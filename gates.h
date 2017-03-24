#ifndef GATES_H
#define GATES_H

#include <stdio.h>
#include <stdbool.h>


/* GATE CLASSES */
#define AND  (6)
#define OR   (5)
#define NOT  (4)

#define XNOR (3)
#define XOR  (2)

#define NOR  (1)
#define NAND (0)
/* END OF GATE CLASSES */

/* INPUT methods/types */
#define INTERNAL  ( 127)
#define SHORT_OUT (-128)
#define SHORT_IN  (-127)

/* END OF INPUT TYPES */


/* Basic Gates */
typedef struct gate *Or;
typedef struct gate *And;
typedef struct gate *Not;

/* Special Gates */
typedef struct gate *Xor;
typedef struct gate *Xnor;

/* Universal Gates */
typedef struct gate *Nor;
typedef struct gate *Nand;

static const char *gate_names[] = {
	"NAND", "NOR", "XOR", "XNOR", "NOT", "OR", "AND"
};

/* */
And create_And_gate(const char *tag, size_t total_ip_pins);
Or create_Or_gate(const char *tag, size_t total_ip_pins);
Not create_Not_gate(const char *tag);

Xor create_Xor_gate(const char *tag, size_t total_ip_pins);
Xnor create_Xnor_gate(const char *tag, size_t total_ip_pins);

Nor create_Nor_gate(const char *tag, size_t total_ip_pins);
Nand create_Nand_gate(const char *tag, size_t total_ip_pins);


/* sets the empty input slot of the given gate to the given truth value. This
 * function returns the slot number of the gate that was set. Returns a
 * negative value(s) on failure.
 * 
 * Return value:
 *  pin number of the currently set slot. 
 *
 *  Exception(s):
 *  '-1': Invalid gate passed.
 *  '-2': All slots are occupied.
 */
int set_pin(struct gate *gate, bool truth);

int unset_pin(struct gate *gate, int pin_number);

/*
 * get_pin_value:
 * 	Retrieves the value of the given pin slot. Pin slot is addressed using
 * 	the pin number.
 * Inputs:
 * 	struct gate * => The gate you to retrieve the value from.
 * 	pin_number    => The slot of which you want to retrieve the output.
 * 	Output:
 * 	  1: True
 * 	  0: False
 * 	 -1: Invalid gate passed.
 * 	 -2: Given pin slot is not set.
 */
int get_pin_value(const struct gate *, unsigned int pin_number);

void short_pins(struct gate *dst, int dst_pin, struct gate *src, int src_pin, char type);

/*
 * Description: Return the value of the output pin of given gate.
 *
 * INPUT:
 * 	valid pointer to struct gate.
 *
 * OUTPUT:
 * 	gate's ouput pin value.
 *
 * Usage:
 * 	e.g 1: bool xor_output = get_output(my_xor_gate);
 * 	e.g 2: printf("xor gate: %s", get_output(my_xor_gate) ? "truthy" : "falsi");
 */
bool get_output(struct gate *);


/* this need to be called after dealing with gate.
 * CALLING THIS IS MANDATORY(if you don't want memory leaks).
 */
void cleanup(struct gate *);


/* 
 * ginfo (gate info) functions to see/peek into gate's members.
 */

/* returns the total number of input pins. Returns 0 on invalid inputs. */
short ginfo_capacity(const struct gate *);
/* returns the class the given gate belongs to. (-1) is returned when unable to
 * identify the class.*/
short ginfo_class(const struct gate *);
/* get the name of the gate, set while creating a gate. */
char *ginfo_tag(const struct gate *);
/* checks if the given pin number is set.  Takes 'gate' and 'pin number' 
 * as parameters.  */
bool ginfo_is_pin_set(const struct gate *, unsigned int pin);

#endif
